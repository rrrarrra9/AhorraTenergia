using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddOpenApi();
var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.MapOpenApi();
}

//datos simulados para probar la API; se pueden quitar mas adelante
var mediciones = new List<Datos>
{
    new Datos { HomeId = "home-01", DeviceId = "esp32-01", Timestamp = DateTimeOffset.Parse("2026-11-09T10:00:00Z"), ConsumptionPowerKw = 1.5, SolarProductionPowerKw = 0.8, BatteryLevelPercent = 50, BatteryPowerKw = 0.2, GridPowerKw = 0.5, ElectricityPriceEurKwh = 0.18, SystemMode = "automatic" },
    new Datos { HomeId = "home-01", DeviceId = "esp32-01", Timestamp = DateTimeOffset.Parse("2026-11-09T11:00:00Z"), ConsumptionPowerKw = 1.8, SolarProductionPowerKw = 1.2, BatteryLevelPercent = 55, BatteryPowerKw = 0.3, GridPowerKw = 0.3, ElectricityPriceEurKwh = 0.18, SystemMode = "automatic" },
    new Datos { HomeId = "home-01", DeviceId = "esp32-01", Timestamp = DateTimeOffset.Parse("2026-11-09T12:00:00Z"), ConsumptionPowerKw = 2.0, SolarProductionPowerKw = 1.5, BatteryLevelPercent = 60, BatteryPowerKw = 0.4, GridPowerKw = 0.1, ElectricityPriceEurKwh = 0.18, SystemMode = "automatic" }
};

app.MapGet("/api/health", () => Results.Ok(new { status = "ok" }));

app.MapGet("/api/energy/current", () =>
{
    lock (mediciones)
    {
        //si no hay datos devolvemos un 404
        if (mediciones.Count == 0) return Results.NotFound();

        //buscamos la medicion mas reciente
        Datos reciente = mediciones[0];
        foreach (Datos medicion in mediciones)
        {
            if (medicion.Timestamp > reciente.Timestamp) reciente = medicion;
        }
        return Results.Ok(reciente);
    }
});

app.MapGet("/api/energy/history", (HttpRequest request) =>
{
    int limit = 20;
    if (request.Query.ContainsKey("limit"))
    {
        if (request.Query["limit"].Count != 1 || !int.TryParse(request.Query["limit"].ToString(), out limit) || limit <= 0)
            return Results.BadRequest();
    }

    lock (mediciones)
    {
        //ordenamos una copia para no modificar la lista original
        var ordenadas = new List<Datos>(mediciones);
        ordenadas.Sort((a, b) => a.Timestamp.CompareTo(b.Timestamp));
        var resultado = new List<Datos>();
        int inicio = Math.Max(0, ordenadas.Count - limit);
        for (int i = inicio; i < ordenadas.Count; i++) resultado.Add(ordenadas[i]);
        return Results.Ok(resultado);
    }
});

app.MapPost("/api/telemetry", (JsonElement json) =>
{
    //comprobamos que el JSON tenga todos los datos de la placa
    if (json.ValueKind != JsonValueKind.Object ||
        !json.TryGetProperty("homeId", out JsonElement home) || home.ValueKind != JsonValueKind.String ||
        !json.TryGetProperty("deviceId", out JsonElement device) || device.ValueKind != JsonValueKind.String ||
        !json.TryGetProperty("timestamp", out JsonElement fecha) || fecha.ValueKind != JsonValueKind.String ||
        !json.TryGetProperty("consumptionPowerKw", out JsonElement consumo) || consumo.ValueKind != JsonValueKind.Number || !consumo.TryGetDouble(out double consumoValor) || !double.IsFinite(consumoValor) ||
        !json.TryGetProperty("solarProductionPowerKw", out JsonElement solar) || solar.ValueKind != JsonValueKind.Number || !solar.TryGetDouble(out double solarValor) || !double.IsFinite(solarValor) ||
        !json.TryGetProperty("batteryLevelPercent", out JsonElement bateria) || bateria.ValueKind != JsonValueKind.Number || !bateria.TryGetDouble(out double bateriaValor) || !double.IsFinite(bateriaValor) ||
        !json.TryGetProperty("batteryPowerKw", out JsonElement potenciaBateria) || potenciaBateria.ValueKind != JsonValueKind.Number || !potenciaBateria.TryGetDouble(out double potenciaBateriaValor) || !double.IsFinite(potenciaBateriaValor) ||
        !json.TryGetProperty("gridPowerKw", out JsonElement red) || red.ValueKind != JsonValueKind.Number || !red.TryGetDouble(out double redValor) || !double.IsFinite(redValor))
        return Results.BadRequest();

    string? homeId = home.GetString();
    string? deviceId = device.GetString();
    string? fechaTexto = fecha.GetString();

    //comprobamos el dispositivo, la fecha UTC y los valores recibidos
    if (string.IsNullOrWhiteSpace(homeId) || string.IsNullOrWhiteSpace(deviceId) ||
        homeId != "home-01" || deviceId != "esp32-01" ||
        fechaTexto == null || !fechaTexto.Contains('T') ||
        !(fechaTexto.EndsWith("Z") || fechaTexto.EndsWith("+00:00")) ||
        !fecha.TryGetDateTimeOffset(out DateTimeOffset timestamp) || timestamp.Offset != TimeSpan.Zero ||
        consumoValor < 0 || solarValor < 0 || bateriaValor < 0 || bateriaValor > 100)
        return Results.BadRequest();

    //el precio y el modo solo los establece el backend
    foreach (JsonProperty propiedad in json.EnumerateObject())
    {
        if (propiedad.Name.Equals("electricityPriceEurKwh", StringComparison.OrdinalIgnoreCase) ||
            propiedad.Name.Equals("systemMode", StringComparison.OrdinalIgnoreCase))
            return Results.BadRequest();
    }

    var medicion = new Datos
    {
        HomeId = homeId, DeviceId = deviceId, Timestamp = timestamp,
        ConsumptionPowerKw = consumoValor, SolarProductionPowerKw = solarValor,
        BatteryLevelPercent = bateriaValor, BatteryPowerKw = potenciaBateriaValor,
        GridPowerKw = redValor, ElectricityPriceEurKwh = 0.18, SystemMode = "automatic"
    };

    //guardamos los datos recibidos
    lock (mediciones) mediciones.Add(medicion);
    return Results.Created("/api/energy/current", medicion);
});

app.Run();
