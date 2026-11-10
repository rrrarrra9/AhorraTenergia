
/*
 * Datos simulados del dashboard de AhorraTenergia.
 *
 * Utilizamos estos datos mientras el backend de Raúl
 * todavía no esté conectado con nuestra aplicación.
 *
 * Los nombres de los campos son exactamente los acordados
 * por el equipo para no tener problemas al integrar la API.
 */

// Estado energético actual de una vivienda de prueba.
export const currentEnergyMock = {
  homeId: "home-01",
  deviceId: "esp32-01",
  timestamp: "2026-11-03T16:30:00Z",

  // Potencia que consume la vivienda en este momento (kW).
  consumptionPowerKw: 2.35,

  // Potencia que están produciendo las placas solares (kW).
  solarProductionPowerKw: 1.80,

  // Porcentaje de carga de la batería.
  batteryLevelPercent: 68,

  // Positivo: la batería entrega energía.
  // Negativo: la batería se está cargando.
  batteryPowerKw: 0.40,

  // Positivo: importamos electricidad de la red.
  // Negativo: exportamos electricidad a la red.
  gridPowerKw: 0.15,

  // Precio simulado de la electricidad en euros por kWh.
  electricityPriceEurKwh: 0.18,

  // Modo de funcionamiento del sistema.
  systemMode: "automatic",
};

// Histórico simulado para representar en un gráfico.
// Cada elemento contiene una medición realizada en un momento.
export const energyHistoryMock = [
  {
    timestamp: "2026-11-03T16:10:00Z",
    consumptionPowerKw: 1.95,
    solarProductionPowerKw: 1.45,
  },
  {
    timestamp: "2026-11-03T16:15:00Z",
    consumptionPowerKw: 2.05,
    solarProductionPowerKw: 1.55,
  },
  {
    timestamp: "2026-11-03T16:20:00Z",
    consumptionPowerKw: 2.10,
    solarProductionPowerKw: 1.60,
  },
  {
    timestamp: "2026-11-03T16:25:00Z",
    consumptionPowerKw: 2.25,
    solarProductionPowerKw: 1.70,
  },
  {
    timestamp: "2026-11-03T16:30:00Z",
    consumptionPowerKw: 2.35,
    solarProductionPowerKw: 1.80,
  },
];