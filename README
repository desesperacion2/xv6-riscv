# Implementación de Lottery Scheduling en XV6-RISC-V

## 1. Funcionamiento y lógica de la implementación

Se reemplazó el planificador Round-Robin original de XV6 por un sistema de **Lottery Scheduling**, donde cada proceso recibe CPU proporcional a la cantidad de tickets asignados. El scheduler sigue los siguientes pasos:

1. Calcular la suma total de tickets de todos los procesos RUNNABLE.
2. Generar un número aleatorio `r` entre 1 y total de tickets.
3. Recorrer la lista de procesos acumulando tickets hasta que la suma acumulada sea mayor o igual a `r`.
4. Seleccionar ese proceso para ejecutarlo.
5. Incrementar el contador `cpu_slices` del proceso seleccionado para monitoreo.

Se utiliza un generador de números pseudoaleatorios tipo LCG para seleccionar el ticket ganador.


## 2. Explicación de las modificaciones realizadas

### Archivos modificados:

- **`proc.h`**: Se agregó el campo `int tickets;` para almacenar la cantidad de tickets de cada proceso y `int cpu_slices;` para llevar la contabilidad de CPU.
- **`proc.c`**: Se reemplazó la función `scheduler()` por la versión de Lottery Scheduling. Se añadió la función `lcg_rand()` para generar números aleatorios.
- **`sysproc.c`**: Se implementó la syscall `sys_settickets()` para que los procesos puedan cambiar su cantidad de tickets.
- **`user/user.h`**: Se agregó la declaración `int settickets(int);`.
- **`user/usys.pl`**: Se agregó `entry("settickets");` para exponer la syscall al espacio de usuario.
- **`user/demo.c`**: Programa de prueba que crea múltiples procesos, asigna tickets distintos y simula carga de CPU.

### Inicializaciones importantes:
- En `allocproc()`, `tickets` se inicializa a 100 y `cpu_slices` a 0.


## 3. Dificultades encontradas y soluciones implementadas

- **Error `void value not ignored`** al usar `argint()` con `if`: Solucionado eliminando la comparación y usando solo `argint(0, &n);`.
- **Errores de RISC-V vs x86**: `switchuvm` y `switchkvm` no existen, se reemplazaron con `swtch(&mycpu()->context, &p->context);`.
- **Error `struct proc has no member 'cpu_slices'`**: Se agregó el campo `cpu_slices` a `struct proc`.
- **Ejecución de programas de usuario**: Se incluyó `_demo` en `UPROGS` del Makefile y se recompiló para incluirlo en `fs.img`.
- **Errores de tipo `uint`**: Se agregó `typedef unsigned int uint;` al inicio de `user/user.h`.
- **Salida desordenada en `printf()`**: Normal por concurrencia de procesos en XV6; se puede mejorar con sincronización, aunque no es obligatorio para la tarea.


## 4. Posibles problemas de Lottery Scheduling

- **Variabilidad por azar**: La fracción de CPU real de cada proceso puede variar a corto plazo debido a la naturaleza aleatoria del scheduler.
- **Starvation**: Procesos con pocos tickets podrían esperar mucho tiempo si hay procesos con muchos tickets, aunque la probabilidad nunca es cero.
- **No determinista**: El orden de ejecución cambia en cada corrida, lo que puede dificultar pruebas reproducibles.
- **Overhead en generación de números aleatorios**: Si se generan muchos números o hay muchos procesos, puede introducir un pequeño overhead.

---

**Conclusión:** Se implementó exitosamente un scheduler de tipo Lottery Scheduling en XV6-RISC-V, incluyendo syscall para asignar tickets, contabilidad de CPU y un programa de prueba que valida la proporcionalidad entre tickets y tiempo de CPU.

