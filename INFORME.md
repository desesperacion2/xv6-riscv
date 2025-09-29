# INFORME — Tarea 1: Implementación de Llamadas al Sistema en xv6

## I. Funcionamiento de las Llamadas al Sistema

---

### 1. `int getppid(void)`

#### Funcionalidad

La llamada al sistema `getppid()` (*get parent process ID*) está diseñada para **retornar el ID del proceso padre** del proceso que la invoca.

| Aspecto | Descripción General |
| :--- | :--- |
| **Llamada desde usuario** | `int ppid = getppid();` |
| **Número de syscall** | `SYS_getppid` |
| **Función kernel** | `sys_getppid()` obtiene el proceso actual (`myproc()`) y retorna `p->parent->pid`. |
| **Resultado** | PID del proceso padre, o **-1** si no tiene. |

#### Implementación en el Kernel (`sys_getppid`)

La función se implementó en `kernel/sysproc.c` siguiendo esta lógica:
* **Obtener el Proceso Actual**: Se utiliza `myproc()` para obtener un puntero a la estructura `struct proc` del proceso que realiza la llamada.
* **Acceder al Padre**: Se accede al campo `parent` dentro de la estructura `struct proc` del proceso actual.
* **Retorno del PID**: Si el proceso tiene un padre (`p->parent`), se retorna el valor del campo `pid` del proceso padre (`p->parent->pid`).
* **Manejo de Errores**: Si el puntero al padre es **nulo** (como en el caso del proceso inicial o *init* en xv6), la función retorna **-1**.

---

### 2. `int getancestor(int n)`

#### Funcionalidad

La llamada al sistema `getancestor(int n)` retorna el **ID del proceso ancestro** ubicado a **`n` niveles de distancia** del proceso que realiza la llamada.

| Aspecto | Descripción General |
| :--- | :--- |
| **Llamada desde usuario** | `int pid = getancestor(2);` (Ejemplo) |
| **Número de syscall** | `SYS_getancestor` |
| **Función kernel** | `sys_getancestor()` recorre hacia arriba `n` veces en la cadena de padres y retorna el PID correspondiente, o **-1** si no existe. |
| **Resultado** | PID del ancestro solicitado. |

#### Implementación en el Kernel (`sys_getancestor`)

La lógica central se implementó en `kernel/sysproc.c` (`sys_getancestor`):
1.  **Obtención de Argumento**: Se utiliza `argint(0, &n)` para obtener el número de generaciones `n`.
2.  **Validación Inicial**: Se retorna **-1** si `n` es negativo.
3.  **Iteración**: Se inicializa un puntero al proceso actual (`struct proc *p = myproc();`) y se ejecuta un bucle `n` veces.
    * En cada iteración, el puntero `p` se mueve al proceso padre (`p = p->parent`).
    * Si se encuentra que el puntero al padre es **nulo** antes de completar las `n` iteraciones, se retorna **-1**.
4.  **Retorno del PID**: Si el bucle termina, se retorna el `pid` del ancestro deseado al que apunta `p`.

---

## II. Explicación de las Modificaciones Realizadas y Dificultades

### Parte I — Implementación de `getppid()`

| Archivo | Modificación | Código (Extracto) |
| :--- | :--- | :--- |
| **`kernel/syscall.h`** | Definición del número de syscall. | `#define SYS_getppid 23` |
| **`kernel/sysproc.c`** | Implementación de la lógica de la función. | ```c uint64 sys_getppid(void) { struct proc *p = myproc(); if (p->parent) return p->parent->pid; return -1; } ``` |
| **`kernel/syscall.c`** | Declaración externa y registro en la tabla de syscalls. | `extern uint64 sys_getppid(void);` <br> `[SYS_getppid] sys_getppid,` |
| **`user/user.h`** | Exposición de la función al espacio de usuario. | `int getppid(void);` |
| **`user/usys.pl`** | Generación de la *stub* de la llamada al sistema. | `entry("getppid");` |
| **Archivos de prueba** | Creación del programa de prueba y adición al `Makefile`. | `Archivo: user/yosoytupadre.c` <br> `UPROGS: $U/_yosoytupadre` |

#### Dificultades y Soluciones
* La principal dificultad inicial fue encontrar y entender el funcionamiento de la syscall `getpid()` como referencia.
* Hubo errores de compilación por errores de sintaxis (ej. omisión de punto y coma, mal uso de la barra invertida).
* Se olvidó inicialmente **declarar la función `sys_getppid`** con `extern uint64 sys_getppid(void);` en `kernel/syscall.c`, ya que era una parte del kernel no explorada previamente.

### Parte II — Implementación de `getancestor(int n)`

| Archivo | Modificación | Código (Extracto) |
| :--- | :--- | :--- |
| **`kernel/syscall.h`** | Definición del número de syscall. | `#define SYS_getancestor 24` |
| **`kernel/sysproc.c`** | Implementación de la lógica de la función. | ```c uint64 sys_getancestor(void) { int n; struct proc *p = myproc(); argint(0, &n); if (n < 0) return -1; for (int i = 0; i < n; i++) { if (p->parent) p = p->parent; else return -1; } return p->pid; } ``` |
| **`kernel/syscall.c`** | Declaración externa y registro en la tabla de syscalls. | `extern uint64 sys_getancestor(void);` <br> `[SYS_getancestor] sys_getancestor,` |
| **`user/user.h`** | Exposición de la función al espacio de usuario. | `int getancestor(int n);` |
| **`user/usys.pl`** | Generación de la *stub* de la llamada al sistema. | `entry("getancestor");` |
| **Archivos de prueba** | Creación del programa de prueba y adición al `Makefile`. | `Archivo: user/ancestors.c` <br> `UPROGS: $U/_ancestors` |

#### Dificultades y Soluciones

* La implementación de `getancestor` fue relativamente más fácil, ya que la Parte I permitió identificar todos los archivos clave del sistema y las secciones a modificar.
* Se encontraron algunos errores de sintaxis (corchetes mal puestos, errores en el código del programa de prueba `ancestors.c`), los cuales se resolvieron rápidamente.

---

## III. Conclusión

Ambas *syscalls* (`getppid()` y `getancestor(int n)`) se implementaron correctamente, cumpliendo con los objetivos de la tarea.

Este proceso permitió comprender los pasos esenciales en el desarrollo de xv6: definir el número de syscall, implementar la función en el kernel, registrarla en la tabla del sistema, exponerla al espacio de usuario, y crear programas de prueba para verificar su funcionamiento. El sistema compiló y ejecutó sin errores, confirmando el éxito de la implementación.
