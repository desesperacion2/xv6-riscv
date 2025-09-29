# INFORME.md  
## Tarea 1 — Implementación de Llamadas al Sistema en xv6  
### Parte I: Implementación Básica — `getppid()`

---

### 🔹 Objetivo
Implementar una nueva llamada al sistema en xv6 llamada `getppid()`, la cual retorna el **PID del proceso padre** del proceso que la invoca.

---

### 🔹 Descripción de la Implementación

Para agregar una nueva syscall en xv6 se deben realizar varios pasos en diferentes archivos del sistema operativo. A continuación se detalla el procedimiento seguido:

#### 1. Definición del número de syscall
Archivo: `kernel/syscall.h`

Se agregó una nueva constante para identificar la llamada:

```c
#define SYS_getppid  23
