
# AhorraTenergia - Dashboard Web

## 1. Descripción

Este proyecto contiene el dashboard web de AhorraTenergia,
desarrollado con React y Vite durante el Sprint 2.

Su objetivo es mostrar el estado energético de una vivienda
mediante datos simulados y, posteriormente, mediante la API
del Backend ASP.NET Core.

**Responsable principal:** Noa Abril Casas.

## 2. Funcionalidades desarrolladas

Actualmente, el dashboard permite:

- Mostrar el consumo eléctrico actual en kW.
- Mostrar la producción solar actual en kW.
- Consultar el porcentaje de batería.
- Mostrar si la batería carga o descarga energía.
- Mostrar la importación o exportación hacia la red.
- Consultar el precio eléctrico simulado.
- Mostrar el modo del sistema.
- Mostrar la fecha y hora de la última medición.
- Visualizar un gráfico histórico de consumo y producción solar.
- Gestionar los estados de carga, datos disponibles,
  error y ausencia de datos.
- Adaptar la distribución de las tarjetas a diferentes pantallas.

## 3. Tecnologías

- React: interfaz de usuario.
- JavaScript y JSX: lógica y componentes.
- Vite: entorno de desarrollo y compilación.
- CSS: diseño visual y responsive.
- SVG: representación del gráfico histórico.
- ESLint: revisión del código.

## 4. Instalación

Es necesario tener instalados Node.js y npm.

Desde la carpeta principal del repositorio:

```powershell
cd src/web
npm install
```

## 5. Ejecutar el dashboard

Para iniciar el servidor de desarrollo:

```powershell
npm run dev
```

Vite mostrará la dirección local del proyecto.

La dirección habitual es:

http://localhost:5173/

## 6. Comprobar el proyecto

Para revisar el código:

```powershell
npm run lint
```

Para generar la versión de producción:

```powershell
npm run build
```

Los archivos generados se guardan en `dist/`.

La carpeta `dist/` no debe subirse al repositorio.

## 7. Estructura del frontend

```text
src/web/
├── public/
├── src/
│   ├── components/
│   │   ├── EnergyCard.jsx
│   │   └── EnergyChart.jsx
│   ├── mocks/
│   │   └── energyData.js
│   ├── services/
│   │   └── energyService.js
│   ├── App.jsx
│   ├── App.css
│   ├── index.css
│   └── main.jsx
├── index.html
├── package.json
└── vite.config.js
```

### Componentes

**EnergyCard.jsx**

Componente reutilizable para mostrar indicadores energéticos.

**EnergyChart.jsx**

Gráfico SVG con el histórico de consumo y producción solar.

**App.jsx**

Pantalla principal del dashboard. Organiza los componentes
y gestiona los estados de la interfaz.

**energyData.js**

Contiene los datos simulados utilizados durante el desarrollo.

**energyService.js**

Centraliza la obtención de información energética.

## 8. Datos simulados

Durante la primera fase utilizamos datos mock.

El contrato JSON acordado por el equipo incluye:

- homeId
- deviceId
- timestamp
- consumptionPowerKw
- solarProductionPowerKw
- batteryLevelPercent
- batteryPowerKw
- gridPowerKw
- electricityPriceEurKwh
- systemMode

Las potencias instantáneas se expresan en kW.

El precio eléctrico se expresa en EUR/kWh.

El nivel de batería se expresa en porcentaje.

### Interpretación de los valores

batteryPowerKw:

- Positivo: batería descargando.
- Negativo: batería cargando.
- Cero: sin intercambio.

gridPowerKw:

- Positivo: importación desde la red.
- Negativo: exportación hacia la red.
- Cero: sin intercambio.

## 9. Estados del dashboard

La aplicación contempla cuatro situaciones:

1. Cargando: estamos obteniendo los datos.
2. Disponible: mostramos tarjetas y gráfico.
3. Error: no ha sido posible obtener los datos.
4. Sin datos: todavía no existen mediciones disponibles.

Durante el desarrollo existe un selector para simular
diferentes estados de la interfaz.

Este selector no se muestra en la compilación de producción.

## 10. Integración con ASP.NET Core

El dashboard React está preparado para obtener información energética desde el backend ASP.NET Core.

La arquitectura utilizada es:

React → ASP.NET Core

React no accede directamente a Supabase ni a ESP32.

### Endpoints comprobados

Se han realizado pruebas locales satisfactorias con los siguientes endpoints:

- `GET /api/health`
- `GET /api/energy/current`
- `GET /api/energy/history?limit=20`

La integración inicial se ha comprobado visualmente en el dashboard, utilizando los datos simulados que proporciona el backend.

### Configuración

La aplicación admite dos modos:

- `mock`: utiliza los datos simulados del frontend.
- `api`: consulta el backend ASP.NET Core.

Las variables de entorno son:

- `VITE_ENERGY_SOURCE`
- `VITE_API_BASE_URL`

El archivo `.env.example` contiene un ejemplo de configuración.

Para utilizar el backend local con el proxy de Vite, se puede configurar `.env.local` con:

```env
VITE_ENERGY_SOURCE=api
VITE_API_BASE_URL=
```

El proxy de `vite.config.js` envía las peticiones `/api` al backend local configurado en `http://localhost:5052`.

Este puerto corresponde al entorno de pruebas utilizado y puede variar en otros equipos.

### Pruebas realizadas

- `npm run lint`: correcto.
- `npm run build`: correcto.
- Consulta de datos energéticos actuales: correcta.
- Consulta del histórico energético: correcta.
- Visualización de datos del backend en React: correcta.

## 11. Trabajo pendiente

- Revisar y obtener aprobación formal de la Pull Request #42.
- Verificar la integración completa con la telemetría de ESP32.
- Comprobar posteriormente la persistencia de datos con Supabase.
- Realizar las pruebas adicionales que solicite el equipo.

## 12. GitHub

Issue principal:

https://github.com/rrrarrra9/AhorraTenergia/issues/14

Rama de desarrollo:

feature/react-dashboard-sprint2

Los cambios deben realizarse en esta rama.

Antes de integrar el trabajo en `main`, la Pull Request
debe recibir una aprobación formal de otro integrante.

## 13. Funcionalidades fuera del alcance

Durante este sprint no se implementan:

- Autenticación y gestión de usuarios.
- Aplicación Android.
- Tarifas eléctricas reales.
- Control físico de instalaciones.
- Notificaciones avanzadas.
- Conexión directa con Supabase.
- Conexión directa de React con ESP32.