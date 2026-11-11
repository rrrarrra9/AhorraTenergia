
/*
 * energyService.js
 *
 * Este archivo se encarga de obtener los datos energéticos.
 *
 * Durante la primera fase utilizamos datos simulados.
 * Cuando el backend de Raúl esté preparado, podremos
 * cambiar a la API sin modificar las tarjetas ni el gráfico.
 *
 * React solo se comunicará con ASP.NET Core.
 * Nunca accederemos directamente a Supabase ni a la ESP32.
 */

import {
  currentEnergyMock,
  energyHistoryMock
} from '../mocks/energyData'

// Por defecto utilizamos los datos simulados.
// Más adelante podremos cambiarlo con una variable de entorno.
const useMocks = import.meta.env.VITE_ENERGY_SOURCE !== 'api'

// Dirección del backend, que definiremos cuando esté disponible.
// Si está vacío, usaremos rutas relativas al mismo servidor.
const apiBaseUrl = import.meta.env.VITE_API_BASE_URL || ''

/*
 * Función para simular un pequeño tiempo de espera.
 *
 * Así podemos comprobar que el estado "Cargando"
 * aparece correctamente en nuestro dashboard.
 */
function simulateDelay() {
  return new Promise((resolve) => {
    setTimeout(resolve, 800)
  })
}

/*
 * Función común para consultar el backend.
 *
 * Si el servidor devuelve un error, lo comunicamos
 * para que App.jsx pueda mostrar "Error de conexión".
 */
async function fetchFromApi(endpoint) {
  const response = await fetch(`${apiBaseUrl}${endpoint}`)

  if (!response.ok) {
    throw new Error(
      `Error al consultar el backend: HTTP ${response.status}`
    )
  }

  // Una respuesta sin contenido representa ausencia de datos.
  if (response.status === 204) {
    return null
  }

  return response.json()
}

/*
 * Obtiene el estado energético actual de la vivienda.
 *
 * Con mocks: devuelve nuestros datos simulados.
 * Con API: consulta GET /api/energy/current.
 */
export async function getCurrentEnergy() {

  if (useMocks) {
    await simulateDelay()

    return currentEnergyMock
  }

  return fetchFromApi('/api/energy/current')
}

/*
 * Obtiene las mediciones históricas.
 *
 * Con mocks: devuelve el histórico simulado.
 * Con API: consulta GET /api/energy/history?limit=20.
 *
 * El contrato actual contempla una lista de mediciones.
 */
export async function getEnergyHistory() {

  if (useMocks) {
    await simulateDelay()

    return energyHistoryMock
  }

  return fetchFromApi('/api/energy/history?limit=20')
}
