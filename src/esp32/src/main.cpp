#include <Arduino.h>
#include <time.h>

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

/*
 * Esta función genera una fecha en formato ISO 8601 UTC.
 *
 * Se suma a la fecha inicial el tiempo que lleva encendida
 * la ESP32 utilizando millis().
 */
String createTimestamp()
{
    /*
     * millis() devuelve los milisegundos transcurridos desde
     * que comenzó el programa.
     *
     * Dividimos entre 1000 para obtener segundos.
     */
    time_t simulatedTime =
        BASE_TIMESTAMP
        + static_cast<time_t>(millis() / 1000);

    /*
     * La estructura tm permite separar internamente
     * año, mes, día, hora, minutos y segundos.
     */
    struct tm timeInfo;

    /*
     * gmtime_r convierte el timestamp a UTC.
     */
    gmtime_r(&simulatedTime, &timeInfo);

    /*
     * Reservamos espacio para almacenar la fecha como texto.
     */
    char timestampBuffer[25];

    /*
     * Creamos el formato:
     *
     * YYYY-MM-DDTHH:MM:SSZ
     */
    strftime(
        timestampBuffer,
        sizeof(timestampBuffer),
        "%Y-%m-%dT%H:%M:%SZ",
        &timeInfo
    );

    return String(timestampBuffer);
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