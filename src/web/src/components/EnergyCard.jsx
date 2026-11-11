
/*
 * EnergyCard.jsx
 *
 * Este componente sirve para mostrar un dato energético
 * dentro de una tarjeta.
 *
 * Lo hacemos reutilizable para no tener que escribir
 * el mismo código cada vez que queramos mostrar
 * el consumo, la producción solar o la batería.
 */

function EnergyCard({ title, value, unit }) {
  return (
    <article className="energy-card">

      {/* Nombre del dato que estamos mostrando. */}
      <h2 className="energy-card-title">
        {title}
      </h2>

      {/* Valor energético y su unidad de medida. */}
      <div className="energy-card-value">
        <span>{value}</span>
        <span className="energy-card-unit">
          {unit}
        </span>
      </div>

    </article>
  )
}

// Exportamos el componente para utilizarlo en App.jsx.
export default EnergyCard