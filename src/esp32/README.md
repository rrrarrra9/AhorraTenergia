# ESP32 — Simulador de telemetría energética

Este directorio contiene el código C++ utilizado por la ESP32 de AhorraTenergia durante el Sprint 2.

El objetivo actual es simular mediciones energéticas de una vivienda y enviarlas posteriormente al Backend ASP.NET Core.

## Tecnologías utilizadas

### ESP32

La ESP32 es la placa utilizada para representar el dispositivo IoT del sistema.

Se ha escogido porque permite ejecutar código en C++, dispone de conectividad Wi-Fi integrada y puede comunicarse con el Backend mediante HTTP.

Durante el Sprint 2 se utiliza principalmente para generar telemetría simulada. No se conecta a una instalación eléctrica real.

### C++ y Arduino Framework

El programa de la ESP32 está desarrollado en C++ utilizando Arduino Framework.

Arduino Framework proporciona funciones y librerías que simplifican tareas habituales en la ESP32, como:

- comunicación mediante puerto serie;
- conexión Wi-Fi;
- control del tiempo mediante `millis()`;
- generación y envío de datos.

Se utiliza C++ porque es uno de los lenguajes habituales para desarrollar firmware en ESP32 y permite trabajar directamente con los recursos de la placa.

### Visual Studio Code

Visual Studio Code es el editor utilizado para desarrollar el código del simulador.

Permite trabajar con el repositorio Git del proyecto y utilizar PlatformIO mediante una extensión integrada.

### PlatformIO

PlatformIO es una herramienta de desarrollo para sistemas embebidos y placas como ESP32.

Se utiliza dentro de Visual Studio Code para:

- configurar el modelo de placa;
- gestionar Arduino Framework;
- compilar el código;
- cargar el firmware en la ESP32;
- detectar puertos serie;
- utilizar el monitor serie;
- gestionar las dependencias del proyecto.

Se ha escogido PlatformIO porque permite mantener una estructura de proyecto clara y reproducible dentro del repositorio y facilita trabajar con ESP32 desde Visual Studio Code sin depender exclusivamente de Arduino IDE.

La configuración del entorno se guarda en `platformio.ini`, por lo que otro integrante puede conocer qué plataforma, placa y framework utiliza el proyecto.

### Wokwi

Wokwi es un simulador de sistemas electrónicos que permite ejecutar firmware de ESP32 de forma virtual.

Durante el desarrollo se ha utilizado para probar el simulador antes de disponer físicamente de la placa.

Permite comprobar:

- que el firmware arranca correctamente;
- que la telemetría se genera periódicamente;
- que el JSON se muestra correctamente por el terminal;
- que el comportamiento básico del programa funciona sin necesitar hardware físico.

Se ha escogido porque permite continuar desarrollando y realizando pruebas incluso cuando la ESP32 física no está disponible.

Wokwi no sustituye las pruebas con hardware real. En este Sprint se han realizado pruebas tanto en Wokwi como en una ESP32 física.

## Arquitectura

La ESP32 forma parte del siguiente flujo:

```text
ESP32 → ASP.NET Core → Supabase → ASP.NET Core → React
```

La ESP32 no se conecta directamente a Supabase ni al dashboard React.

Su responsabilidad es generar la telemetría y enviarla al Backend ASP.NET Core.

## Datos generados

El simulador genera periódicamente:

- `homeId`
- `deviceId`
- `timestamp`
- `consumptionPowerKw`
- `solarProductionPowerKw`
- `batteryLevelPercent`
- `batteryPowerKw`
- `gridPowerKw`

Ejemplo:

```json
{
  "homeId": "home-01",
  "deviceId": "esp32-01",
  "timestamp": "2026-11-08T20:00:00Z",
  "consumptionPowerKw": 2.35,
  "solarProductionPowerKw": 1.80,
  "batteryLevelPercent": 68,
  "batteryPowerKw": 0.40,
  "gridPowerKw": 0.15
}
```

Las potencias se expresan en kW y el nivel de batería en porcentaje.

## Interpretación de batería y red

### `batteryPowerKw`

- Valor positivo: la batería entrega energía.
- Valor negativo: la batería se está cargando.
- Valor cero: no existe intercambio.

### `gridPowerKw`

- Valor positivo: se importa energía de la red.
- Valor negativo: se exporta energía.
- Valor cero: no existe intercambio.

## Configuración del proyecto

El proyecto utiliza PlatformIO con Arduino Framework.

La configuración principal se encuentra en:

```text
platformio.ini
```

Configuración utilizada:

```ini
[env:esp-wrover-kit]
platform = espressif32
board = esp-wrover-kit
framework = arduino
monitor_speed = 115200
```

Durante las pruebas, esta configuración ha permitido compilar el firmware y cargarlo correctamente en la ESP32 física utilizada por el equipo.

## Compilar el proyecto

Abrir `src/esp32/` como proyecto PlatformIO en Visual Studio Code.

Ejecutar:

```text
Build
```

La compilación debe finalizar con:

```text
SUCCESS
```

## Ejecución mediante Wokwi

El proyecto incluye:

```text
wokwi.toml
diagram.json
```

`wokwi.toml` indica a Wokwi qué firmware generado por PlatformIO debe ejecutar.

`diagram.json` define la placa virtual utilizada en la simulación.

Para realizar la prueba:

1. Compilar el proyecto mediante PlatformIO.
2. Iniciar la simulación de Wokwi.
3. Comprobar la salida del terminal.
4. Verificar que se genera una medición aproximadamente cada 5 segundos.

La simulación permite trabajar sin tener conectada físicamente la ESP32.

## Ejecución en ESP32 física

Conectar la ESP32 mediante USB.

PlatformIO debe detectar el puerto serie correspondiente.

Durante las pruebas del Sprint 2 la placa fue detectada mediante un adaptador USB-SERIAL CH340.

Para cargar el programa:

```text
Upload
```

El proceso debe finalizar con:

```text
SUCCESS
```

Para comprobar la ejecución:

```text
Monitor
```

El monitor serie está configurado a:

```text
115200 baudios
```

Durante las pruebas se verificó correctamente:

- compilación del firmware;
- carga del programa;
- arranque de la ESP32;
- generación periódica de telemetría;
- salida JSON mediante puerto serie;
- conexión Wi-Fi.

## Configuración Wi-Fi

Las credenciales Wi-Fi se almacenan únicamente de forma local en:

```text
include/secrets.h
```

Ejemplo:

```cpp
#pragma once

#define WIFI_SSID "NOMBRE_DE_LA_RED"
#define WIFI_PASSWORD "CONTRASENA"
```

Este archivo está excluido mediante `.gitignore`.

Por tanto, las credenciales utilizadas durante el desarrollo no deben añadirse al repositorio.

Nunca deben publicarse contraseñas, tokens, API keys ni otras credenciales.

## Gestión de errores Wi-Fi

El programa intenta conectarse a la red Wi-Fi durante un tiempo limitado.

Si consigue conectarse, muestra mediante el monitor serie la dirección IP asignada a la ESP32.

Si después del tiempo establecido no existe conexión, informa del error pero continúa ejecutando el simulador.

Esto evita que una caída de red bloquee permanentemente la generación de telemetría.

Durante el Sprint 2 se comprobó este comportamiento utilizando también una red Wi-Fi inexistente como prueba controlada.

## Frecuencia de generación

Actualmente se genera una nueva medición aproximadamente cada 5 segundos.

El programa utiliza `millis()` para controlar el intervalo de generación sin utilizar un bloqueo permanente del bucle principal.

## Sincronización de fecha y hora mediante NTP

La ESP32 sincroniza su reloj mediante NTP después de conectarse correctamente a Internet.

NTP permite obtener la fecha y hora real desde servidores de tiempo disponibles en Internet.

Se utiliza porque las mediciones energéticas necesitan incluir un `timestamp` real y coherente con el contrato de datos del proyecto.

Los timestamps se generan en UTC utilizando formato ISO 8601:

```text
2026-11-10T17:49:45Z
```

Si no se puede realizar la sincronización NTP, el programa informa del problema sin bloquear permanentemente la ejecución del simulador.

## Envío de telemetría al Backend

Cuando existe conexión Wi-Fi, la ESP32 envía cada medición al Backend ASP.NET Core mediante:

```text
POST /api/telemetry
```

La comunicación utiliza HTTP y el contenido se envía como:

```text
Content-Type: application/json
```

El JSON enviado utiliza exactamente los campos definidos en el contrato común del Sprint 2.

La dirección concreta del Backend se configura localmente y no se almacena junto con las credenciales Wi-Fi públicas del repositorio.

Durante las pruebas de integración se comprobó el siguiente flujo:

```text
ESP32 física
    ↓
Wi-Fi
    ↓
POST /api/telemetry
    ↓
ASP.NET Core
    ↓
201 Created
```

El Backend recibe los datos generados por la ESP32 y añade los campos que son responsabilidad del servidor:

- `electricityPriceEurKwh`
- `systemMode`

También se verificó posteriormente la medición mediante:

```text
GET /api/energy/current
```

El Backend devolvió correctamente la última medición enviada por la ESP32.

Si el Backend no responde o se pierde la conexión, el fallo de comunicación no debe detener permanentemente el simulador.

## Pruebas realizadas

Hasta el momento se han realizado las siguientes pruebas:

- compilación mediante PlatformIO;
- ejecución mediante Wokwi;
- generación del JSON en Wokwi;
- carga del firmware en una ESP32 física;
- ejecución mediante monitor serie;
- generación de telemetría en hardware real;
- conexión de la ESP32 a una red Wi-Fi;
- obtención de una dirección IP;
- prueba de fallo de conexión Wi-Fi;
- comprobación de que el simulador continúa funcionando sin conexión.

## Estado actual del Sprint 2

Implementado:

- generación simulada de consumo;
- producción solar;
- nivel de batería;
- potencia de batería;
- intercambio con la red;
- timestamps;
- JSON compatible con el contrato;
- salida mediante puerto serie;
- frecuencia periódica de generación;
- simulación mediante Wokwi;
- ejecución en ESP32 física;
- conexión Wi-Fi;
- gestión básica de errores Wi-Fi.
- sincronización de hora real mediante NTP;
- envío HTTP mediante POST /api/telemetry;
- integración con Backend ASP.NET Core;
- respuesta HTTP 201 Created;
- comprobación mediante GET /api/energy/current.