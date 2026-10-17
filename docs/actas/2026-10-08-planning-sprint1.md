# Acta de reunión — Sprint 1 Planning

**Proyecto:** AhorraTenergia  
**Fecha:** 08/10/2026  
**Horario:** 16:45 – 18:30  
**Sprint:** 1 — Arranque y planificación inicial  
**Periodo del sprint:** 06/10/2026 – 20/10/2026  
**Tipo de reunión:** Planificación inicial del proyecto  
**Estado del acta:** Documentada posteriormente y pendiente de revisión final del equipo.

## 1. Asistentes

A la reunión asistieron los tres integrantes del equipo AhorraTenergia:

- **Raúl Sánchez Ortiz** — Coordinación y arquitectura del software.
- **Hebert Alberto Calderon Torres** — Electrónica, integración con ESP32 y documentación técnica.
- **Noa Abril** — Diseño UI/UX y organización de Issues.

La asistencia de los tres miembros ha sido confirmada por Hebert.

## 2. Objetivo de la reunión

Establecer las bases de organización y planificación del proyecto intermodular AhorraTenergia, definiendo el alcance inicial, las tecnologías previstas, las responsabilidades principales del equipo y las primeras tareas necesarias para comenzar el desarrollo.

El objetivo del Sprint 1 es preparar una estructura de trabajo que permita desarrollar el producto mínimo viable (MVP) en los siguientes sprints.

## 3. Descripción del proyecto

AhorraTenergia es un proyecto de gestión energética doméstica orientado a viviendas que cuentan con placas solares, batería y conexión a la red eléctrica.

La finalidad es desarrollar un sistema que permita visualizar información energética y simular decisiones de gestión teniendo en cuenta:

- La producción de energía solar.
- El consumo eléctrico de la vivienda.
- El nivel de carga de la batería.
- El precio de la electricidad.
- El uso de la energía procedente de la red eléctrica.

La primera versión del proyecto será un **prototipo basado en simulación**, sin realizar conexiones ni maniobras sobre una instalación eléctrica doméstica real.

## 4. Arquitectura técnica inicial

Las tecnologías previstas para desarrollar AhorraTenergia son:

| Componente | Tecnología | Responsabilidad |
|---|---|---|
| Backend | ASP.NET Core (C#) | Gestionar la API, los datos y la lógica de negocio |
| Frontend web | React | Mostrar el dashboard y la información energética |
| Aplicación móvil | Android Java | Permitir la consulta de información desde un móvil |
| Base de datos | Supabase PostgreSQL | Almacenar mediciones, estados e información histórica |
| Dispositivo | ESP32 con C++ | Generar datos simulados y representar la recepción de órdenes |

El **Backend será el componente central de la arquitectura**.

Las aplicaciones web y Android se comunicarán con el Backend. Este coordinará las operaciones relacionadas con la base de datos y la ESP32.

Los protocolos concretos de comunicación y las reglas de decisión se definirán durante las siguientes fases del proyecto.

## 5. Organización inicial del equipo

Se establece la siguiente distribución general de responsabilidades:

### Raúl Sánchez Ortiz — Coordinación y arquitectura

- Coordinar el desarrollo técnico.
- Gestionar la organización general del repositorio.
- Configurar y administrar GitHub Projects.
- Documentar la arquitectura inicial.
- Participar en el desarrollo Backend y Frontend.
- Colaborar en la revisión e integración de cambios.

### Hebert Alberto Calderon Torres — Electrónica e integración

- Coordinar el trabajo relacionado con ESP32.
- Estudiar la simulación de variables energéticas.
- Documentar aspectos técnicos.
- Colaborar en la organización del repositorio.
- Participar en el desarrollo Backend y Frontend.
- Contribuir a las pruebas de integración.

### Noa Abril — Diseño y experiencia de usuario

- Diseñar las interfaces y el dashboard.
- Elaborar bocetos y propuestas visuales.
- Organizar y documentar Issues.
- Colaborar en la planificación del backlog.
- Participar en el desarrollo Backend y Frontend.
- Revisar la usabilidad y coherencia visual del sistema.

**Responsabilidad compartida:** los tres integrantes participarán en el desarrollo Backend y Frontend, la documentación, las pruebas y la integración del proyecto.

## 6. Acuerdos de trabajo del Sprint 1

Los siguientes acuerdos están recogidos en la planificación del sprint y son coherentes con la organización adoptada por el equipo:

1. **GitHub como herramienta principal.** Utilizar el repositorio para gestionar el código fuente, la documentación y el historial de cambios.

2. **Gestión de tareas mediante Issues.** Cada tarea debe disponer de una descripción clara, un responsable, etiquetas y criterios de aceptación.

3. **Organización mediante GitHub Projects.** Utilizar un tablero Kanban con los estados Backlog, Por hacer, En curso, En revisión y Hecho.

4. **Trabajo con ramas independientes.** Desarrollar los cambios relevantes en ramas específicas, evitando modificar directamente `main`.

5. **Uso de Pull Requests.** Solicitar revisiones a otros integrantes antes de integrar cambios relevantes.

6. **Documentación continua.** Mantener actualizados el README, las actas, la memoria técnica y las decisiones importantes.

7. **Participación de todo el equipo.** Cada integrante realizará aportaciones propias y colaborará en las distintas áreas del proyecto.

8. **Prioridad al prototipo simulado.** Desarrollar inicialmente un sistema demostrativo sin intervenir en instalaciones eléctricas reales.

9. **Seguimiento del trabajo.** Registrar avances, bloqueos y tareas pendientes durante las reuniones del sprint.

Estos acuerdos reflejan el sistema de trabajo documentado para el Sprint 1. El acta ha sido redactada posteriormente, por lo que no se atribuye una fecha exacta de aprobación a cada acuerdo individual.

## 7. Tareas planificadas para el Sprint 1

Las actividades previstas para este sprint son:

- [ ] Configurar el repositorio GitHub y los accesos necesarios.
- [ ] Crear la estructura inicial de carpetas.
- [ ] Configurar el GitHub Project y sus estados Kanban.
- [ ] Crear el Milestone Sprint 1.
- [ ] Elaborar un backlog mínimo de 15 historias de usuario o tareas.
- [ ] Documentar las responsabilidades del equipo.
- [ ] Definir la Definition of Done.
- [ ] Preparar el README inicial.
- [ ] Elaborar el diseño inicial del dashboard.
- [ ] Documentar la arquitectura general.
- [ ] Redactar el capítulo 1 de la memoria técnica en LaTeX.
- [ ] Compilar la memoria correctamente a PDF.
- [ ] Registrar las evidencias de los avances.
- [ ] Preparar la Sprint Review y la Retrospectiva.

Esta lista representa los objetivos planificados. Su estado de realización se registra mediante los Issues y el GitHub Project, sin considerar estas tareas finalizadas automáticamente.

## 8. Planificación de reuniones

Durante el Sprint 1 se ha establecido el siguiente calendario de trabajo:

| Fecha | Horario | Actividad |
|---|---|---|
| 08/10/2026 | 16:45 – 18:30 | Planificación inicial |
| 13/10/2026 | 16:45 – 18:30 | Seguimiento y organización del repositorio |
| 15/10/2026 | 16:45 – 18:30 | Seguimiento de tareas y documentación |
| 19/10/2026 | 15:30 – 16:30 | Seguimiento previsto antes del cierre |

El cierre oficial del Sprint 1 está previsto para el **20/10/2026**.

La Sprint Review y la Retrospectiva se documentarán después de celebrarse, utilizando las evidencias reales de los resultados obtenidos.

## 9. Riesgos y aspectos pendientes

Durante la planificación inicial se identifican las siguientes cuestiones que deben gestionarse:

- Posibles dificultades para integrar varias tecnologías.
- Necesidad de distribuir las tareas de forma equilibrada.
- Riesgo de ampliar demasiado el alcance del MVP.
- Dependencia de servicios externos como Supabase.
- Necesidad de definir el protocolo de comunicación entre ESP32 y Backend.
- Importancia de mantener documentación actualizada y evidencias verificables.

Se priorizará la simulación energética para reducir la complejidad inicial y mantener el proyecto dentro del plazo académico.

## 10. Resultados de la planificación

Como resultado de esta fase se dispone de una definición inicial del proyecto que incluye:

- Objetivos generales del producto.
- Identificación del usuario objetivo.
- Tecnologías previstas.
- Arquitectura centralizada propuesta.
- Distribución inicial de responsabilidades.
- Metodología de trabajo con GitHub.
- Relación de tareas que deberán gestionarse durante el Sprint 1.

Estos elementos constituyen una base de planificación. Su implementación y finalización deben demostrarse posteriormente mediante los entregables correspondientes.

## 11. Observaciones

El Sprint 1 comenzó oficialmente el 06/10/2026, mientras que la primera reunión de planificación documentada se celebró el **08/10/2026**.

El acta se ha elaborado posteriormente utilizando la planificación registrada en GitHub y la confirmación de asistencia de los tres integrantes.

Se distingue entre los trabajos planificados, los acuerdos de trabajo documentados y las tareas realmente completadas, para mantener la trazabilidad de la información.

## 12. Referencias

- [Repositorio AhorraTenergia](https://github.com/rrrarrra9/AhorraTenergia)
- [Issue #5 — Sprint 1 Planning](https://github.com/rrrarrra9/AhorraTenergia/issues/5)
- [GitHub Project — Gestión del proyecto](https://github.com/users/rrrarrra9/projects/1)
- [Roles y Definition of Done](https://github.com/rrrarrra9/AhorraTenergia/blob/main/docs/roles-y-definition-of-done.md)

---

**AhorraTenergia — Proyecto Intermodular — Curso 2026-2027**

**Acta de planificación del Sprint 1 — 08/10/2026**
