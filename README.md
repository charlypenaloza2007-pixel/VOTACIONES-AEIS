# Sistema de Gestión de Elecciones en C

## Descripción

Este proyecto es un sistema de votaciones desarrollado en lenguaje C que simula un proceso electoral básico. Permite la creación de elecciones, el registro de candidatos, la emisión de votos por parte de los estudiantes, la generación de resultados y la administración de usuarios.

El sistema almacena la información mediante archivos de texto, permitiendo mantener un registro de candidatos, votantes y resultados de la elección.

---

## Características

### Módulo de Administrador

* Crear una nueva elección.
* Registrar hasta 5 candidatos.
* Generar actas y reportes de resultados.
* Visualizar resultados de la elección.
* Administrar usuarios registrados.
* Consultar la lista de votantes.
* Desbanear usuarios eliminándolos de la lista de votantes.
* Verificar si existe una elección activa.

### Módulo de Estudiantes

* Ingresar la edad y número de cédula.
* Validar la cédula ecuatoriana.
* Evitar votos duplicados.
* Emitir voto por un candidato.
* Registrar votos en blanco y votos nulos.
* Almacenar cada voto de forma individual.

---

## Tecnologías Utilizadas

* Lenguaje de programación: C
* Librerías:

  * stdio.h
  * conio.h
  * string.h
  * windows.h

---

## Estructura de Archivos

El sistema genera y utiliza los siguientes archivos:

### candidatos.txt

Almacena los nombres de los candidatos registrados.

Ejemplo:
Candidato 1: Juan Pérez
Candidato 2: María López

---

### cedulas.txt

Guarda las cédulas de los usuarios que ya han votado para evitar votos duplicados.

Ejemplo:
1723456789
1712345678

---

### datos0.txt, datos1.txt, ...

Cada archivo almacena la información de un voto registrado.

Ejemplo:
Edad: 20
Cédula: 1723456789
Voto: 2

---

### acta.txt

Contiene el resumen final de la elección.

Ejemplo:
==============ACTA DE RESULTADOS================
Candidato 1: Juan Pérez, votos: 5
Candidato 2: María López, votos: 3
Votos en blanco: 1
Votos nulos: 0
El ganador es: Juan Pérez con 5 votos

---

## Funcionamiento General

### Inicio del programa

El usuario puede seleccionar una de las siguientes opciones:

1. Módulo de estudiantes
2. Módulo de administrador
3. Salir

---

### Flujo del Administrador

1. Inicia sesión.
2. Crea una nueva elección.
3. Registra candidatos.
4. Consulta resultados.
5. Genera el acta de la elección.
6. Administra usuarios.

Credenciales predeterminadas:

Usuario:
Administrador1

Contraseña:
123456

---

### Flujo del Estudiante

1. Ingresa su edad.
2. Ingresa su número de cédula.
3. El sistema valida la información.
4. Se muestran los candidatos disponibles.
5. El estudiante emite su voto.
6. El sistema registra el voto y bloquea futuros intentos de votar con la misma cédula.

---

## Validaciones Implementadas

### Validación de cédula ecuatoriana

* Debe contener exactamente 10 dígitos.
* Solo puede contener números.
* El código de provincia debe estar entre 01 y 24 o ser 30.

### Validación de votación

* No permite votar dos veces con la misma cédula.
* Solo las personas mayores o iguales a 18 años pueden votar.
* Permite:

  * Voto en blanco (0)
  * Voto nulo (-1)
  * Voto por candidatos registrados.

---

## Algoritmos Implementados

* Búsqueda binaria recursiva para localizar usuarios.
* Ordenamiento por inserción (Insertion Sort) para ordenar candidatos según la cantidad de votos obtenidos.
* Ordenamiento burbuja (Bubble Sort) para ordenar las cédulas antes de realizar la búsqueda binaria.

---

## Estructura Principal del Programa

main()
│
├── panelAdministrador()
│ ├── controlarPanel()
│ ├── generarActa()
│ ├── administrarUsuarios()
│ └── resultadosFinales()
│
└── panelEstudiantes()
├── validarCedulaEcuatoriana()
├── yaVoto()
└── registro del voto

---

## Posibles Mejoras Futuras

* Encriptar las contraseñas del administrador.
* Implementar una interfaz gráfica.
* Permitir más de cinco candidatos.
* Utilizar una base de datos en lugar de archivos de texto.
* Generar estadísticas y gráficos de resultados.
* Implementar múltiples elecciones simultáneas.
* Mejorar el sistema de auditoría de archivos.

---

## Autor

Carlos Luis Peñaloza Orellana / 
Daniel Alejandro Urbina Arteaga / Erick Alexander Aguayo Almagro

      
Proyecto académico desarrollado para simular un sistema básico de gestión electoral utilizando estructuras, archivos y algoritmos fundamentales en lenguaje C.
