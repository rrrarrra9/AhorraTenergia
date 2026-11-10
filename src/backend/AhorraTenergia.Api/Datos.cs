public class Datos
{
    //datos recibidos por la placa
    public string HomeId { get; set; } = "";
    public string DeviceId { get; set; } = "";
    public DateTimeOffset Timestamp { get; set; }
    public double ConsumptionPowerKw { get; set; }
    public double SolarProductionPowerKw { get; set; }
    public double BatteryLevelPercent { get; set; }
    public double BatteryPowerKw { get; set; }
    public double GridPowerKw { get; set; }

    //datos internos del backend
    public double ElectricityPriceEurKwh { get; set; }
    public string SystemMode { get; set; } = "";
}
