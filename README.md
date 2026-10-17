# AhorraTenergia

**Controla tu energía, optimiza tu consumo y ahorra en tu factura eléctrica.**

## 1. ¿Qué es AhorraTenergia?

AhorraTenergia es un proyecto de gestión energética inteligente orientado a viviendas que disponen de placas solares y sistemas de almacenamiento mediante baterías.

Nuestro objetivo es desarrollar un sistema capaz de supervisar el consumo eléctrico de una vivienda y gestionar de manera automática o manual el aprovechamiento de las diferentes fuentes de energía.

El sistema tendrá en cuenta factores como:

- El precio actual de la electricidad.
- La energía generada por las placas solares.
- El nivel de carga disponible en la batería.
- El consumo energético de la vivienda.

A partir de estos datos, el sistema determinará cómo aprovechar las fuentes de energía disponibles para reducir la dependencia de la red eléctrica durante las horas de mayor coste.

**La primera versión del proyecto funcionará mediante una simulación**, sin realizar cambios físicos en la instalación eléctrica de una vivienda.

## 2. Objetivos del proyecto

### Objetivo general

Desarrollar una solución de gestión energética que permita supervisar, controlar y optimizar de forma simulada el consumo eléctrico de una vivienda, mediante una aplicación web, una aplicación móvil y un dispositivo ESP32.

### Objetivos específicos

- Desarrollar un Backend centralizado encargado de gestionar los datos y las decisiones del sistema.
- Crear una aplicación web para visualizar el consumo, la producción solar y el estado de la batería.
- Desarrollar una aplicación Android que permita consultar la información energética.
- Integrar una placa ESP32 para simular la recopilación de datos y la ejecución de órdenes.
- Implementar una base de datos para almacenar información energética e historiales.
- Desarrollar un sistema automático de toma de decisiones basado en el precio de la electricidad y la disponibilidad energética.
- Permitir que el usuario pueda consultar y modificar el modo de funcionamiento del sistema simulado.

## 3. Tecnologías utilizadas

El proyecto estará formado por diferentes componentes tecnológicos:

| Componente | Tecnología |
|---|---|
| Backend | ASP.NET Core (C#) |
| Frontend web | React |
| Aplicación móvil | Android (Java) |
| Base de datos | Supabase (PostgreSQL) |
| Hardware | ESP32 |
| Programación de la placa | C++ |
| Control de versiones | Git y GitHub |
| Gestión del proyecto | GitHub Projects |
| Documentación técnica | LaTeX |

### Arquitectura general

El Backend desarrollado en ASP.NET Core será el componente central del sistema.

Su función será recibir y procesar los datos, gestionar la lógica de negocio, almacenar la información y coordinar la comunicación entre los diferentes componentes.

El funcionamiento general será:

1. **ESP32:** genera y transmite los datos de la simulación energética.
2. **Backend:** recibe los datos, aplica las reglas de gestión y determina las acciones correspondientes.
3. **Base de datos:** almacena mediciones, estados y decisiones del sistema.
4. **Frontend web:** permite al usuario visualizar la información y controlar las funcionalidades disponibles.
5. **Aplicación Android:** permite consultar el estado del sistema desde un dispositivo móvil.

La comunicación entre los Frontends y la ESP32 se realizará mediante el Backend, que actuará como controlador principal.

## 4. Equipo de desarrollo

**Proyecto Intermodular — Curso 2026-2027**

**Ciclo formativo:** DAM2.

### Integrantes

- **Raúl Sánchez Ortiz** — Programación y desarrollo de software.
- **Hebert Alberto Calderon Torres** — Electrónica e integración con ESP32.
- **Noa Abril** — Diseño y experiencia de usuario (UI/UX).

### Organización y colaboración

Aunque cada integrante tiene asignada un área principal de responsabilidad, **todos participaremos activamente en el desarrollo del Backend y Frontend del proyecto**.

El trabajo se realizará de manera colaborativa, participando en:

- Desarrollo e implementación de funcionalidades.
- Programación del Backend y Frontend.
- Integración de los diferentes componentes.
- Resolución de problemas técnicos.
- Pruebas y validación del sistema.
- Documentación y mejora continua del proyecto.

Esta organización permitirá distribuir las tareas, compartir conocimientos y garantizar que todos los integrantes participen en las diferentes fases del desarrollo.

## 5. Objetivo del repositorio

Este repositorio de GitHub tiene como finalidad centralizar y organizar todo el desarrollo del proyecto AhorraTenergia.

Se utilizará para:

- Almacenar y gestionar el código fuente.
- Organizar las tareas y responsabilidades del equipo.
- Documentar la arquitectura y las decisiones técnicas.
- Mantener la memoria técnica del proyecto.
- Registrar los avances de cada sprint.
- Gestionar cambios mediante ramas y Pull Requests.
- Llevar un seguimiento de los errores, mejoras y funcionalidades pendientes.

### Estructura prevista del repositorio

- `docs/` — Documentación general y técnica.
- `docs/memoria/` — Memoria del proyecto en LaTeX.
- `docs/adr/` — Registro de decisiones de arquitectura.
- `docs/actas/` — Actas de reuniones y planificación.
- `docs/retrospectivas/` — Retrospectivas de los sprints.
- `design/` — Diseños, prototipos e interfaces.
- `src/backend/` — Código del Backend ASP.NET Core.
- `src/web/` — Código del Frontend React.
- `src/android/` — Aplicación Android en Java.
- `src/esp32/` — Código C++ de la ESP32.
- `tests/` — Pruebas del sistema.

## 6. Metodología de trabajo

Utilizaremos una metodología ágil organizada mediante sprints.

Las tareas se gestionarán con GitHub Projects, utilizando un tablero Kanban con los siguientes estados:

1. **Backlog:** tareas identificadas pendientes de planificación.
2. **Por hacer:** tareas seleccionadas para realizar.
3. **En curso:** tareas que se están desarrollando.
4. **En revisión:** tareas pendientes de validación.
5. **Hecho:** tareas completadas y verificadas.

Cada integrante trabajará desde su cuenta de GitHub, registrando sus contribuciones mediante commits y utilizando Pull Requests para incorporar cambios relevantes al proyecto.

## 7. Estado actual del proyecto

### Sprint 1 — Arranque y planificación inicial

**Periodo:** 06/10/2026 - 20/10/2026.

Actualmente, AhorraTenergia se encuentra en su primera fase de organización y planificación.

Los objetivos principales de este sprint son:

- Configurar el repositorio y la estructura inicial del proyecto.
- Incorporar a todos los integrantes y al profesorado.
- Crear el tablero de gestión mediante GitHub Projects.
- Definir los roles y responsabilidades del equipo.
- Elaborar el backlog inicial de funcionalidades.
- Documentar la arquitectura general del sistema.
- Iniciar la memoria técnica en LaTeX.
- Delimitar las funcionalidades de la primera versión del proyecto.

**Estado:** Sprint 1 en curso. Las tareas se considerarán completadas únicamente cuando estén realizadas y verificadas en GitHub.

### Seguimiento y entregables del Sprint 1

El trabajo del equipo puede consultarse en:

- [GitHub Project — Tablero Kanban](https://github.com/users/rrrarrra9/projects/1)
- [Product Backlog — Issue #10](https://github.com/rrrarrra9/AhorraTenergia/issues/10)
- [Evidencias del Sprint 1 — Issue #12](https://github.com/rrrarrra9/AhorraTenergia/issues/12)
- [Acta de planificación](docs/actas/2026-10-08-planning-sprint1.md)
- [Arquitectura inicial](docs/adr/ADR-001-arquitectura.md)
- [Roles y Definition of Done](docs/roles-y-definition-of-done.md)
- [Memoria técnica en LaTeX](docs/memoria/main.tex)
- [Memoria en PDF](docs/memoria/memoria-sprint1.pdf)
- [Diseño inicial del dashboard](design/dashboard-inicial.png)
- [Documento de evidencias](docs/sprint1/estado-y-evidencias.md)

**Estado a 17/10/2026:**

- 17 tareas organizadas en GitHub Projects.
- Prioridades asignadas: 13 P1 y 4 P2.
- Validación final del backlog pendiente por parte del equipo.
- Sprint Review y Retrospectiva previstas para el 20/10/2026.

El Sprint 1 permanece en curso. Sus resultados definitivos se documentarán después de las reuniones de cierre.

## 8. Alcance inicial

Durante las primeras fases nos centraremos en desarrollar un prototipo funcional basado en la simulación del sistema energético.

El objetivo es validar la comunicación entre la ESP32, el Backend, la base de datos y las interfaces de usuario.

No se realizarán conexiones ni conmutaciones sobre una instalación eléctrica doméstica real.

En futuras fases se podrán estudiar mejoras y ampliaciones del sistema en función de los resultados obtenidos y la viabilidad técnica.

---

**AhorraTenergia — Proyecto Intermodular 2026-2027.**
