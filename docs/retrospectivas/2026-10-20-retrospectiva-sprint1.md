# Sprint 1 Retrospective — AhorraTenergia

**Proyecto:** AhorraTenergia  
**Sprint:** 1 — Arranque y planificación inicial  
**Periodo:** 06/10/2026 – 20/10/2026  
**Fecha de cierre:** 20/10/2026  
**Estado:** Retrospectiva realizada y conclusiones confirmadas por los tres integrantes.

## 1. Participantes

- Raúl Sánchez Ortiz.
- Noa Abril Casas.
- Hebert Alberto Calderon Torres.

Los tres integrantes confirman estas conclusiones como resultado de la Retrospectiva del Sprint 1.

## 2. ¿Qué ha funcionado bien?

El equipo considera que durante el Sprint 1 ha funcionado correctamente:

- La organización inicial del repositorio.
- El reparto de responsabilidades entre los integrantes.
- La creación y utilización del tablero Kanban.
- La documentación del proyecto y de las evidencias.
- La elaboración de la memoria técnica en LaTeX.
- La definición de la arquitectura inicial.
- La propuesta gráfica inicial del dashboard.

Estos elementos han permitido disponer de una base común para comenzar el desarrollo técnico en los siguientes sprints.

## 3. ¿Qué dificultades hemos encontrado?

Se identifican principalmente las siguientes dificultades:

- El uso inicial de GitHub Projects resultó más complejo de lo previsto.
- Varias Pull Requests fueron fusionadas sin que GitHub registrara una revisión formal `APPROVED` previa.
- Parte de la documentación y de las evidencias se actualizó de forma posterior, en lugar de registrarse de manera continua.
- El comentario del profesor sobre la carpeta `tests/` requiere revisar cómo se organizarán las pruebas y qué contenido debe mantenerse en la rama principal.

## 4. ¿Qué vamos a mejorar?

El equipo acuerda aplicar las siguientes mejoras:

1. **Revisar las Pull Requests antes del merge.**  
   Una persona distinta al autor deberá revisar la PR y registrar la aprobación formal en GitHub cuando corresponda.

2. **Mantener actualizado GitHub Projects.**  
   El estado de cada Issue debe reflejar el trabajo real: Backlog, Por hacer, En curso, En revisión o Hecho.

3. **Registrar evidencias de forma continua.**  
   Commits, PR, capturas, decisiones y bloqueos se documentarán durante el sprint y no únicamente al final.

4. **Revisar la organización de las pruebas.**  
   Se analizará la observación recibida sobre `tests/` y se evitará introducir en el repositorio cualquier secreto, credencial, dato personal real o configuración sensible.

## 5. Responsables de las mejoras

- **Raúl:** coordinar el procedimiento de revisión técnica y de Pull Requests.
- **Noa:** ayudar a mantener actualizado el tablero Kanban y el estado de las tareas.
- **Hebert:** mantener la trazabilidad documental, las evidencias y el seguimiento de los criterios de aceptación.
- **Todo el equipo:** aplicar las revisiones cruzadas, mantener GitHub actualizado y registrar los bloqueos.

## 6. Aplicación en el Sprint 2

Las mejoras anteriores se aplicarán desde el inicio del Sprint 2.

El equipo propone comenzar con un primer incremento funcional basado en:

- API ASP.NET Core con datos energéticos simulados.
- Dashboard React.
- Simulación de telemetría energética mediante ESP32 y C++.

La planificación concreta se encuentra en el Issue de Sprint 2 y queda pendiente de asociar a las fechas oficiales que determine el profesor.

## 7. Conclusión

El Sprint 1 ha permitido establecer la organización, documentación y arquitectura inicial de AhorraTenergia. La principal mejora de proceso para los siguientes sprints será aumentar la trazabilidad de las revisiones, mantener actualizado el tablero y registrar las evidencias durante el desarrollo.

Las conclusiones de esta retrospectiva han sido confirmadas por Raúl, Noa y Hebert.
