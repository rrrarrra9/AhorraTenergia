
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

El dashboard utiliza un servicio independiente para obtener
los datos energéticos.

La arquitectura acordada es:

React -> ASP.NET Core

React no se conecta directamente con Supabase ni con ESP32.

Los endpoints previstos son:

GET /api/energy/current

GET /api/energy/history?limit=20

Por defecto, la aplicación utiliza datos simulados.

Cuando el backend esté preparado se podrá configurar
el servicio mediante variables de entorno de Vite:

- VITE_ENERGY_SOURCE=api
- VITE_API_BASE_URL=direccion_del_backend

La dirección real y el puerto deben confirmarse con Raúl.

La integración real deberá comprobarse antes de darla
por completada.

## 11. Trabajo pendiente

- Confirmar los endpoints operativos del backend.
- Configurar la dirección de ASP.NET Core.
- Validar las respuestas reales del contrato JSON.
- Comprobar la integración completa.
- Realizar las pruebas finales.
- Solicitar revisión formal mediante Pull Request.

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