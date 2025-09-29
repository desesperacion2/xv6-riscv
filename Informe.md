# INFORME.md  
## Tarea 1 — Implementación de Llamadas al Sistema en xv6  
### Parte I: Implementación Básica — `getppid()`

---

### 🔹 Objetivo
Implementar una nueva llamada al sistema en xv6 llamada `getppid()`, la cual retorna el **PID del proceso padre** del proceso que la invoca.  
Esta tarea tiene como propósito comprender el flujo de implementación de una syscall dentro del kernel de xv6 y su integración con el espacio de usuario.

---

### 🔹 Contexto Inicial
El entorno de trabajo ya se encontraba completamente configurado:  
- Máquina virtual Linux con compiladores y dependencias instaladas (`riscv64-linux-gnu-gcc`, `qemu`, `make`, etc).  
- Repositorio `xv6-riscv` clonado desde GitHub y funcional.  
- Rama creada específicamente para la tarea:  
  ```bash
  git checkout -b emilio_suazo_t1
