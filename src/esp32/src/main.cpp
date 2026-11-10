#include <Arduino.h>
#include <time.h>
// Librería oficial de ESP32 para conectarse a redes Wi-Fi.
#include <WiFi.h>

// Archivo local con el nombre y contraseña de la red.
// Este archivo está ignorado por Git para no subir credenciales.
#include "secrets.h"

// Libreria que permite realizar peticiones HTTP desde la ESP32.
#include <HTTPClient.h>

/*
 * AhorraTenergia
 * Sprint 2 - Simulador de telemetría energética
 *
 * Responsable principal: Hebert
 *
 * Este programa simula los datos energéticos de una vivienda.
 *
 * Durante esta primera fase:
 * - No se utilizan sensores reales.
 * - No se controla ninguna instalación eléctrica.
 * - No se conecta todavía con Supabase.
 * - No se conecta directamente con React.
 *
 * La ESP32 genera los datos que posteriormente enviará
 * al Backend ASP.NET Core mediante HTTP.
 */


/* =========================================================
   IDENTIFICACIÓN DEL DISPOSITIVO
   ========================================================= */

/*
 * Durante el Sprint 2 trabajaremos inicialmente con una
 * única vivienda y una única ESP32.
 *
 * Estos identificadores forman parte del contrato común
 * definido por el equipo.
 */
const char* HOME_ID = "home-01";
const char* DEVICE_ID = "esp32-01";


/* =========================================================
   CONFIGURACIÓN DE LA SIMULACIÓN
   ========================================================= */

/*
 * Generaremos una medición cada 5 segundos.
 *
 * Se utiliza unsigned long porque millis(), función propia
 * de Arduino, devuelve este tipo de dato.
 */
const unsigned long MEASUREMENT_INTERVAL_MS = 5000;

/*
 * Guardamos el momento en el que se generó la última
 * medición para saber cuándo han pasado 5 segundos.
 */
unsigned long lastMeasurementMs = 0;


/* =========================================================
   TIMESTAMP SIMULADO
   ========================================================= */

/*
 * En el contrato del proyecto hemos definido que las fechas
 * deben utilizar UTC y formato ISO 8601.
 *
 * Ejemplo:
 * 2026-11-08T20:00:00Z
 *
 * En esta primera fase todavía no conectamos la ESP32
 * a Internet para obtener la hora mediante NTP.
 *
 * Por eso utilizamos una fecha base simulada.
 *
 * Más adelante, cuando incorporemos Wi-Fi, podremos
 * sustituir esta parte por una hora obtenida de Internet.
 */
const time_t BASE_TIMESTAMP = 1794168000;

// Indica si la ESP32 ha conseguido obtener la hora real desde Internet.
bool timeSynchronized = false;


/* =========================================================
   ESTADO INICIAL DE LA BATERÍA
   ========================================================= */

/*
 * El nivel de batería se representa mediante porcentaje.
 *
 * Según el contrato:
 * batteryLevelPercent debe mantenerse entre 0 y 100.
 */
float batteryLevelPercent = 68.0;


/* =========================================================
   FUNCIÓN PARA GENERAR VALORES DECIMALES ALEATORIOS
   ========================================================= */

/*
 * Arduino dispone de random(), pero devuelve números enteros.
 *
 * Esta función nos permite generar valores float dentro
 * de un rango.
 *
 * Por ejemplo:
 *
 * randomFloat(0.8, 4.5)
 *
 * puede producir:
 *
 * 1.32
 * 2.87
 * 4.01
 *
 * Estos valores se utilizan únicamente para simular
 * el comportamiento energético de una vivienda.
 */
float randomFloat(float minValue, float maxValue)
{
    long randomValue = random(0, 10001);

    /*
     * Convertimos el número entero generado a un valor
     * entre 0.0 y 1.0.
     */
    float normalizedValue = randomValue / 10000.0;

    /*
     * Adaptamos ese valor al rango solicitado.
     */
    return minValue
        + normalizedValue * (maxValue - minValue);
}


/* =========================================================
   GENERACIÓN DEL TIMESTAMP
   ========================================================= */

// Esta función genera la fecha y hora actual en formato ISO 8601.
// Ejemplo del resultado:
// 2026-11-10T17:25:30Z
//
// La letra Z del final indica que la hora está expresada en UTC.
String createTimestamp()
{
    // Obtenemos la hora actual que tiene guardada la ESP32.
    // Esta hora se habrá sincronizado previamente mediante NTP.
    time_t now = time(nullptr);

    // Comprobamos que la hora sea válida.
    // Si NTP no ha funcionado o la ESP32 todavía no tiene una fecha correcta,
    // devolvemos una fecha por defecto para evitar generar datos incorrectos.
    if (!timeSynchronized || now < 100000)
    {
        return "1970-01-01T00:00:00Z";
    }

    // Creamos una estructura tm.
    // Esta estructura separa la fecha en partes:
    // año, mes, día, hora, minutos y segundos.
    struct tm timeInfo;

    // Convertimos la hora actual a UTC.
    // gmtime_r toma el valor de "now" y guarda el resultado en "timeInfo".
    gmtime_r(&now, &timeInfo);

    // Creamos un espacio de memoria donde guardaremos
    // el timestamp convertido a texto.
    char timestamp[25];

    // Convertimos la fecha de timeInfo a texto.
    //
    // El formato utilizado es:
    // %Y = año con 4 cifras
    // %m = mes
    // %d = día
    // %H = hora
    // %M = minutos
    // %S = segundos
    //
    // La T separa la fecha de la hora.
    // La Z indica que estamos usando UTC.
    strftime(
        timestamp,
        sizeof(timestamp),
        "%Y-%m-%dT%H:%M:%SZ",
        &timeInfo
    );

    // Convertimos el array de caracteres "timestamp"
    // a un String de Arduino para poder utilizarlo fácilmente
    // al construir el JSON de telemetría.
    return String(timestamp);
}


/* =========================================================
   GENERACIÓN DE TELEMETRÍA
   ========================================================= */

/*
 * Esta función genera una medición completa.
 *
 * Los nombres y unidades siguen el contrato acordado
 * para el Sprint 2.
 */

// Declaramos la función antes de usarla dentro de generateTelemetry().
void sendTelemetry(
    String timestamp,
    float consumptionPowerKw,
    float solarProductionPowerKw,
    float batteryLevelPercent,
    float batteryPowerKw,
    float gridPowerKw
);

 void generateTelemetry()
{
    /* -----------------------------------------------------
       CONSUMO DE LA VIVIENDA
       ----------------------------------------------------- */

    /*
     * consumptionPowerKw representa la potencia instantánea
     * consumida por la vivienda.
     *
     * Unidad: kW
     *
     * Para la simulación utilizamos valores entre
     * 0.8 kW y 4.5 kW.
     */
    float consumptionPowerKw =
        randomFloat(0.8, 4.5);


    /* -----------------------------------------------------
       PRODUCCIÓN SOLAR
       ----------------------------------------------------- */

    /*
     * solarProductionPowerKw representa la potencia
     * instantánea generada por las placas solares.
     *
     * Unidad: kW
     *
     * Se simulan valores entre 0 y 3.5 kW.
     */
    float solarProductionPowerKw =
        randomFloat(0.0, 3.5);


    /* -----------------------------------------------------
       POTENCIA DE BATERÍA
       ----------------------------------------------------- */

    /*
     * Inicialmente suponemos que la batería no está
     * cargando ni descargando.
     */
    float batteryPowerKw = 0.0;

    /*
     * Calculamos la diferencia entre consumo y producción.
     */
    float energyDifference =
        consumptionPowerKw
        - solarProductionPowerKw;


    /*
     * Según el contrato:
     *
     * batteryPowerKw > 0
     * batería entregando energía.
     *
     * batteryPowerKw < 0
     * batería cargándose.
     *
     * batteryPowerKw = 0
     * sin intercambio.
     */


    /*
     * Si la vivienda consume más energía de la que producen
     * las placas y tenemos batería suficiente, simulamos
     * una descarga de batería.
     */
    if (
        energyDifference > 0.0
        && batteryLevelPercent > 20.0
    )
    {
        /*
         * Limitamos la potencia máxima simulada de batería
         * a 1.2 kW.
         */
        batteryPowerKw =
            min(energyDifference, 1.2f);
    }

    /*
     * Si las placas producen más que el consumo y la batería
     * todavía no está llena, utilizamos el excedente solar
     * para simular su carga.
     */
    else if (
        energyDifference < 0.0
        && batteryLevelPercent < 95.0
    )
    {
        float solarSurplus =
            -energyDifference;

        /*
         * El valor es negativo porque el contrato define
         * que una batería cargándose utiliza potencia negativa.
         */
        batteryPowerKw =
            -min(solarSurplus, 1.2f);
    }


    /* -----------------------------------------------------
       POTENCIA DE RED ELÉCTRICA
       ----------------------------------------------------- */

    /*
     * Aplicamos un balance energético simplificado:
     *
     * consumo = solar + batería + red
     *
     * Por tanto:
     *
     * red = consumo - solar - batería
     */
    float gridPowerKw =
        consumptionPowerKw
        - solarProductionPowerKw
        - batteryPowerKw;


    /*
     * Según el contrato:
     *
     * gridPowerKw > 0
     * estamos importando energía de la red.
     *
     * gridPowerKw < 0
     * estamos exportando excedente.
     *
     * gridPowerKw = 0
     * no existe intercambio con la red.
     */


    /* -----------------------------------------------------
       ACTUALIZACIÓN DEL NIVEL DE BATERÍA
       ----------------------------------------------------- */

    /*
     * Esta fórmula no pretende representar todavía
     * una batería física real.
     *
     * Su objetivo es que el porcentaje evolucione de forma
     * coherente durante la demostración.
     *
     * batteryPowerKw positivo:
     * la batería descarga y el porcentaje disminuye.
     *
     * batteryPowerKw negativo:
     * la batería carga y el porcentaje aumenta.
     */
    batteryLevelPercent -=
        batteryPowerKw * 0.05;


    /*
     * constrain() garantiza que el porcentaje nunca
     * salga del intervalo 0 - 100.
     */
    batteryLevelPercent =
        constrain(
            batteryLevelPercent,
            0.0f,
            100.0f
        );


    /* -----------------------------------------------------
       FECHA DE LA MEDICIÓN
       ----------------------------------------------------- */

    String timestamp =
        createTimestamp();


    /* -----------------------------------------------------
       GENERACIÓN DEL JSON
       ----------------------------------------------------- */

    /*
     * De momento mostramos el JSON mediante puerto serie.
     *
     * Esto permite comprobar que la ESP32 genera exactamente
     * el formato acordado antes de añadir Wi-Fi y HTTP.
     */

    Serial.println("{");

    Serial.printf(
        "  \"homeId\": \"%s\",\n",
        HOME_ID
    );

    Serial.printf(
        "  \"deviceId\": \"%s\",\n",
        DEVICE_ID
    );

    Serial.printf(
        "  \"timestamp\": \"%s\",\n",
        timestamp.c_str()
    );

    Serial.printf(
        "  \"consumptionPowerKw\": %.2f,\n",
        consumptionPowerKw
    );

    Serial.printf(
        "  \"solarProductionPowerKw\": %.2f,\n",
        solarProductionPowerKw
    );

    Serial.printf(
        "  \"batteryLevelPercent\": %.2f,\n",
        batteryLevelPercent
    );

    Serial.printf(
        "  \"batteryPowerKw\": %.2f,\n",
        batteryPowerKw
    );

    Serial.printf(
        "  \"gridPowerKw\": %.2f\n",
        gridPowerKw
    );

    Serial.println("}");

    /*
     * Línea vacía para separar visualmente las mediciones
     * en el monitor serie.
     */
    Serial.println();

    // Enviamos al Backend exactamente la misma medición
    // que acabamos de generar y mostrar por el monitor serie.
    sendTelemetry(
        timestamp,
        consumptionPowerKw,
        solarProductionPowerKw,
        batteryLevelPercent,
        batteryPowerKw,
        gridPowerKw
);
}

// Envía una medición energética al Backend ASP.NET Core.
// Recibe los mismos datos que ya genera el simulador
void sendTelemetry(
    String timestamp,
    float consumptionPowerKw,
    float solarProductionPowerKw,
    float batteryLevelPercent,
    float batteryPowerKw,
    float gridPowerKw
) {
    // Si no hay conexión Wi-Fi, no intentamos hacer la petición.
    // El simulador podrá seguir funcionando normalmente.
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("No hay Wi-Fi. No se envia la telemetria.");
        return;
    }
    // Creamos el cliente HTTP que realizará la petición al Backend.
    HTTPClient http;

    // Indicamos la URL del endpoint guardada en secrets.h.
    http.begin(BACKEND_URL);

    // Indicamos que vamos a enviar datos en formato JSON.
    http.addHeader("Content-Type", "application/json");

    // Construimos el JSON utilizando los mismos campos
    // definidos en el contrato del Sprint 2.
    String json = "{";

    json += "\"homeId\":\"home-01\",";
    json += "\"deviceId\":\"esp32-01\",";
    json += "\"timestamp\":\"" + timestamp + "\",";

    json += "\"consumptionPowerKw\":";
    json += String(consumptionPowerKw, 2);
    json += ",";

    json += "\"solarProductionPowerKw\":";
    json += String(solarProductionPowerKw, 2);
    json += ",";

    json += "\"batteryLevelPercent\":";
    json += String(batteryLevelPercent, 2);
    json += ",";

    json += "\"batteryPowerKw\":";
    json += String(batteryPowerKw, 2);
    json += ",";

    json += "\"gridPowerKw\":";
    json += String(gridPowerKw, 2);

    json += "}";

    // Mostramos qué vamos a enviar para poder comprobarlo.
    Serial.println("Enviando telemetria al Backend:");
    Serial.println(json);

    // Realizamos la petición POST.
    int httpResponseCode = http.POST(json);

    // Si el código es mayor que 0 significa que
    // hemos recibido una respuesta HTTP del servidor.
    if (httpResponseCode > 0) {

        Serial.print("Codigo HTTP recibido: ");
        Serial.println(httpResponseCode);

        // Leemos la respuesta que devuelve ASP.NET Core.
        String response = http.getString();

        Serial.println("Respuesta del Backend:");
        Serial.println(response);

    } else {

        // Si falla la petición mostramos el error,
        // pero no detenemos el simulador.
        Serial.print("Error enviando telemetria. Codigo: ");
        Serial.println(httpResponseCode);
    }

    // Cerramos la conexión HTTP para liberar recursos.
    http.end();
}

    // Intenta obtener la fecha y hora real mediante un servidor NTP.
    // NTP permite que la ESP32 sincronice su reloj utilizando Internet.
    void synchronizeTime() 
    {
        Serial.println("Sincronizando hora mediante NTP...");

        // Configuramos la zona horaria en UTC
        configTime(
            0,              // Diferencia respecto a UTC
            0,              // Horario de verano
            "pool.ntp.org", // Servidor NTP principal
            "time.nist.gov" // Servidor NTP alternativo
        );

        // Guardamos cuando empieza el intento para evitar
        // quedarnos esperando indefinidamente.
        unsigned long startTime = millis();

        // Esperamos como máximo 10 segundos.
        while(time(nullptr) < 100000 && 
                millis() - startTime < 10000) 
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println();

        // Comprobamos si hemos recibido una fecha válida.
        if(time(nullptr) >= 100000) 
        {
            timeSynchronized = true;
            Serial.println("Hora sincronizada correctamente.");
            
        } 
        else 
        {
            timeSynchronized = false;
            Serial.println("No se pudo sincronizar la hora.");
            Serial.println("El simulador continuará funcionando.");
        }

    }

/* =========================================================
   SETUP
   ========================================================= */

/*
 * setup() se ejecuta una única vez cuando:
 *
 * - se enciende la ESP32;
 * - se reinicia;
 * - se carga un programa nuevo.
 */
void setup()
{
    /*
     * Iniciamos la comunicación serie a 115200 baudios.
     *
     * Esta velocidad es habitual en ESP32 y permite
     * visualizar los mensajes desde PlatformIO.
     */
    Serial.begin(115200);

    // Informamos por el monitor serie de que empieza la conexión.
    Serial.println("Conectando a Wi-Fi...");

    // Intentamos conectarnos usando las credenciales de secrets.h.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Guardamos el momento en el que empezamos a intentar la conexión.
    unsigned long wifiStartTime = millis();

    // Damos un máximo de 10 segundos para conectarnos.
    // Así evitamos que el programa se quede bloqueado indefinidamente
    // si la red Wi-Fi no está disponible.
    while (WiFi.status() != WL_CONNECTED && 
            millis() - wifiStartTime < 10000)
    {
        delay(500);
        Serial.print(".");
    }

    // Comprobamos el resultado del intento de conexión.
    if (WiFi.status() == WL_CONNECTED)
    {
        // La conexión se ha realizado correctamente.
        Serial.println();
        Serial.println("Wi-Fi conectado");

        // Mostramos la IP asignada por el router.
        Serial.print("Dirección IP: ");
        Serial.println(WiFi.localIP());

        // Una vez tenemos internet, sincronizamos la fecha y la hora
        synchronizeTime();
    }
    else
    {
        // Si después de 10 segundos no hay conexión,
        // informamos del error pero dejamos que el simulador continue.
        Serial.println();
        Serial.println("No se pudo conectar a Wi-Fi.");
        Serial.println("El simulador continuará funcionando sin conexión.");
    }

    /*
     * Pequeña espera para permitir que el puerto serie
     * termine de inicializarse.
     */
    delay(1000);


    /*
     * Inicializamos la semilla de números aleatorios
     * utilizando micros().
     *
     * Esto ayuda a que las secuencias de valores simulados
     * no sean siempre iguales después de cada reinicio.
     */
    randomSeed(micros());


    Serial.println(
        "AhorraTenergia - Simulador ESP32"
    );

    Serial.println(
        "Generando telemetria cada 5 segundos..."
    );

    Serial.println();
}


/* =========================================================
   LOOP
   ========================================================= */

/*
 * loop() se ejecuta continuamente mientras la ESP32
 * permanece encendida.
 */
void loop()
{
    /*
     * Obtenemos cuánto tiempo lleva funcionando la placa.
     */
    unsigned long currentMs =
        millis();


    /*
     * Comprobamos si han pasado cinco segundos desde
     * la última medición.
     *
     * No utilizamos delay(5000) porque bloquearía
     * completamente el programa durante ese tiempo.
     *
     * millis() permitirá añadir posteriormente otras
     * funciones, como Wi-Fi o comunicación HTTP, sin
     * detener todo el programa.
     */
    if (
        currentMs - lastMeasurementMs
        >= MEASUREMENT_INTERVAL_MS
    )
    {
        /*
         * Guardamos el instante de esta medición.
         */
        lastMeasurementMs =
            currentMs;

        /*
         * Generamos la telemetría.
         */
        generateTelemetry();
    }
}