
/*
 * App.jsx
 *
 * Pantalla principal del dashboard AhorraTenergia.
 *
 * Los datos se obtienen mediante energyService.js.
 * Por ahora utilizamos mocks, pero después podremos
 * conectar la API de Raúl sin cambiar las tarjetas.
 *
 * También gestionamos los cuatro estados:
 * cargando, disponible, error y sin datos.
 */

import { useEffect, useState } from 'react'

import EnergyCard from './components/EnergyCard'
import EnergyChart from './components/EnergyChart'

import {
  getCurrentEnergy,
  getEnergyHistory
} from './services/energyService'

import './App.css'

function App() {

  // Estado inicial: esperamos la primera carga.
  const [status, setStatus] = useState('loading')

  // Datos energéticos que mostraremos en pantalla.
  const [energy, setEnergy] = useState(null)
  const [history, setHistory] = useState([])

  // Selector para probar los estados durante el desarrollo.
  const [testMode, setTestMode] = useState('available')

  // Este contador nos permite repetir una petición.
  const [reloadKey, setReloadKey] = useState(0)

  /*
   * Cuando cambian el modo de prueba o el contador,
   * solicitamos de nuevo los datos.
   *
   * Los cambios de estado se realizan después de
   * esperar las funciones asíncronas del servicio.
   *
   * Así evitamos el error de ESLint que teníamos.
   */
  useEffect(() => {

    // Nos permite ignorar respuestas de cargas anteriores.
    let cancelled = false

    async function loadEnergy() {

      try {

        // Obtenemos la medición y el histórico a la vez.
        const [currentData, historyData] = await Promise.all([
          getCurrentEnergy(),
          getEnergyHistory()
        ])

        // Si el usuario ha cambiado de estado,
        // ignoramos esta respuesta.
        if (cancelled) return

        // Comprobamos el error simulado.
        if (import.meta.env.DEV && testMode === 'error') {
          throw new Error('Error de conexión simulado')
        }

        // Comprobamos el escenario sin datos.
        if (import.meta.env.DEV && testMode === 'empty') {
          setEnergy(null)
          setHistory([])
          setStatus('empty')
          return
        }

        // Si no hay medición actual, no mostramos tarjetas.
        if (!currentData) {
          setEnergy(null)
          setHistory([])
          setStatus('empty')
          return
        }

        // Guardamos los datos que devuelve el servicio.
        setEnergy(currentData)

        setHistory(
          Array.isArray(historyData) ? historyData : []
        )

        // Indicamos que ya podemos mostrar el dashboard.
        setStatus('available')

      } catch (error) {

        // No mostramos errores de una carga cancelada.
        if (cancelled) return

        console.error(
          'Error al cargar los datos energéticos:',
          error
        )

        setEnergy(null)
        setHistory([])
        setStatus('error')
      }
    }

    // Iniciamos la carga asíncrona.
    loadEnergy()

    // Evitamos que una carga anterior actualice la pantalla.
    return () => {
      cancelled = true
    }

  }, [testMode, reloadKey])

  /*
   * Cuando cambiamos el escenario de prueba,
   * indicamos que empieza una nueva carga.
   *
   * Estos cambios se realizan desde un evento
   * del usuario y no dentro de useEffect.
   */
  function changeTestMode(newMode) {
    setStatus('loading')
    setEnergy(null)
    setHistory([])
    setTestMode(newMode)
  }

  /*
   * El botón de reintento repite la petición.
   */
  function retryLoad() {
    setStatus('loading')
    setEnergy(null)
    setHistory([])
    setReloadKey((previous) => previous + 1)
  }

  return (
    <main className="dashboard">

      {/* Título y descripción de nuestra aplicación. */}
      <header className="dashboard-header">
        <h1>AhorraTenergia</h1>
        <p>Dashboard de gestión energética doméstica</p>
      </header>

      {/*
       * Selector exclusivo de desarrollo.
       * No aparecerá en la versión de producción.
       */}
      {import.meta.env.DEV && (
        <div className="dashboard-tests">

          <label htmlFor="test-mode">
            Estado de prueba:
          </label>

          <select
            id="test-mode"
            value={testMode}
            onChange={(event) => {
              changeTestMode(event.target.value)
            }}
          >
            <option value="available">
              Datos disponibles
            </option>

            <option value="error">
              Error de conexión
            </option>

            <option value="empty">
              Sin datos
            </option>
          </select>

        </div>
      )}

      {/* Estado 1: cargando información. */}
      {status === 'loading' && (
        <section
          className="dashboard-message"
          role="status"
        >
          <h2>Cargando datos energéticos...</h2>
          <p>Estamos obteniendo la información.</p>
        </section>
      )}

      {/* Estado 2: error de conexión. */}
      {status === 'error' && (
        <section
          className="dashboard-message error"
          role="alert"
        >
          <h2>Error de conexión</h2>

          <p>
            No hemos podido obtener los datos energéticos.
          </p>

          <button
            type="button"
            onClick={retryLoad}
          >
            Volver a intentar
          </button>
        </section>
      )}

      {/* Estado 3: todavía no existen mediciones. */}
      {status === 'empty' && (
        <section
          className="dashboard-message"
          role="status"
        >
          <h2>No hay datos disponibles</h2>

          <p>
            Todavía no tenemos mediciones energéticas
            para esta vivienda.
          </p>
        </section>
      )}

      {/* Estado 4: tenemos información disponible. */}
      {status === 'available' && energy && (
        <>

          {/* Tarjetas con las principales medidas energéticas. */}
          <section
            className="energy-grid"
            aria-label="Estado energético"
          >

            <EnergyCard
              title="Consumo actual"
              value={energy.consumptionPowerKw}
              unit="kW"
            />

            <EnergyCard
              title="Producción solar"
              value={energy.solarProductionPowerKw}
              unit="kW"
            />

            <EnergyCard
              title="Nivel de batería"
              value={energy.batteryLevelPercent}
              unit="%"
            />

            {/*
             * Una potencia positiva significa que la
             * batería está entregando energía.
             */}
            <EnergyCard
              title={
                energy.batteryPowerKw > 0
                  ? 'Batería descargando'
                  : energy.batteryPowerKw < 0
                    ? 'Batería cargando'
                    : 'Potencia de batería'
              }
              value={Math.abs(energy.batteryPowerKw)}
              unit="kW"
            />

            {/*
             * Valores positivos indican importación.
             * Valores negativos indican exportación.
             */}
            <EnergyCard
              title={
                energy.gridPowerKw < 0
                  ? 'Exportación a la red'
                  : 'Consumo de la red'
              }
              value={Math.abs(energy.gridPowerKw)}
              unit="kW"
            />

            <EnergyCard
              title="Precio eléctrico"
              value={energy.electricityPriceEurKwh}
              unit="€/kWh"
            />

          </section>

          {/* Gráfico de las mediciones históricas. */}
          <EnergyChart history={history} />

          {/* Información adicional del sistema. */}
          <section className="dashboard-info">

            <p>
              <strong>Modo del sistema: </strong>
              {energy.systemMode}
            </p>

          </section>

        </>
      )}

    </main>
  )
}

export default App
