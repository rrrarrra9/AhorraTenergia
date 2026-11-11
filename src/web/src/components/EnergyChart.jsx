
/*
 * EnergyChart.jsx
 *
 * Este componente muestra un gráfico histórico de
 * consumo eléctrico y producción solar.
 *
 * Recibe los datos desde App.jsx y utiliza SVG
 * para dibujar dos líneas sin bibliotecas externas.
 */

function EnergyChart({ history }) {

  // Si no hay mediciones, mostramos un mensaje.
  if (!history || history.length === 0) {
    return (
      <section className="chart-container">
        <h2>Histórico energético</h2>
        <p>No hay datos históricos disponibles.</p>
      </section>
    )
  }

  // Medidas del dibujo SVG.
  const width = 600
  const height = 260
  const margin = {
    top: 20,
    right: 20,
    bottom: 45,
    left: 45,
  }

  const chartWidth = width - margin.left - margin.right
  const chartHeight = height - margin.top - margin.bottom

  // Buscamos el valor más alto para ajustar la escala.
  const maxValue = Math.max(
    1,
    ...history.map((item) => item.consumptionPowerKw),
    ...history.map((item) => item.solarProductionPowerKw)
  ) * 1.2

  // Calculamos dónde colocar cada medición horizontalmente.
  function getX(index) {
    if (history.length === 1) {
      return margin.left + chartWidth / 2
    }

    return margin.left + (index / (history.length - 1)) * chartWidth
  }

  // Convertimos los kW en una posición vertical.
  function getY(value) {
    return margin.top + chartHeight -
      (value / maxValue) * chartHeight
  }

  // Generamos los puntos de una línea utilizando
  // el nombre del campo del contrato JSON.
  function createLine(dataKey) {
    return history
      .map((item, index) => {
        return `${getX(index)},${getY(item[dataKey])}`
      })
      .join(' ')
  }

  // Preparamos las líneas del consumo y de la producción.
  const consumptionLine = createLine('consumptionPowerKw')
  const solarLine = createLine('solarProductionPowerKw')

  // Mostramos las horas de las mediciones.
  function formatHour(timestamp) {
    return new Date(timestamp).toLocaleTimeString('es-ES', {
      hour: '2-digit',
      minute: '2-digit',
    })
  }

  return (
    <section className="chart-container">

      <h2>Histórico energético</h2>
      <p className="chart-description">
        Evolución del consumo y la producción solar
      </p>

      {/* Leyenda para identificar las dos líneas. */}
      <div className="chart-legend">
        <span className="legend-consumption">
          Consumo
        </span>

        <span className="legend-solar">
          Producción solar
        </span>
      </div>

      {/* Dibujamos el gráfico mediante SVG. */}
      <svg
        viewBox={`0 0 ${width} ${height}`}
        className="energy-chart"
        role="img"
        aria-label="Gráfico histórico de consumo y producción solar en kilovatios"
      >

        {/* Líneas horizontales de referencia. */}
        {[0, 1, 2, 3, 4].map((step) => {

          const value = (maxValue / 4) * step
          const y = getY(value)

          return (
            <g key={step}>
              <line
                x1={margin.left}
                y1={y}
                x2={width - margin.right}
                y2={y}
                stroke="#e0e7e2"
              />

              <text
                x={margin.left - 8}
                y={y + 4}
                fontSize="11"
                fill="#536158"
                textAnchor="end"
              >
                {value.toFixed(1)}
              </text>
            </g>
          )
        })}

        {/* Línea que representa el consumo eléctrico. */}
        <polyline
          points={consumptionLine}
          fill="none"
          stroke="#2e6b4f"
          strokeWidth="3"
          strokeLinecap="round"
          strokeLinejoin="round"
        />

        {/* Línea que representa la producción solar. */}
        <polyline
          points={solarLine}
          fill="none"
          stroke="#e5a44b"
          strokeWidth="3"
          strokeLinecap="round"
          strokeLinejoin="round"
        />

        {/* Puntos y horas de cada medición. */}
        {history.map((item, index) => (
          <g key={`${item.timestamp}-${index}`}>

            <circle
              cx={getX(index)}
              cy={getY(item.consumptionPowerKw)}
              r="4"
              fill="#2e6b4f"
            />

            <circle
              cx={getX(index)}
              cy={getY(item.solarProductionPowerKw)}
              r="4"
              fill="#e5a44b"
            />

            <text
              x={getX(index)}
              y={height - 15}
              textAnchor="middle"
              fontSize="11"
              fill="#536158"
            >
              {formatHour(item.timestamp)}
            </text>

          </g>
        ))}

        {/* Unidad de medida del eje vertical. */}
        <text
          x="8"
          y="14"
          fontSize="12"
          fill="#536158"
        >
          kW
        </text>

      </svg>
    </section>
  )
}

export default EnergyChart