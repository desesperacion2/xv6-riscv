## Pasos de Configuración

### 1.Fork del Repositorio
Realicé un fork del repositorio oficial de XV6 para tener mi propia copia del proyecto.

### 2.Creación de Rama de Trabajo
Una vez en el directorio del proyecto, creé una nueva rama con mi nombre.

### 3.Configuración de VM en Google Cloud
Creé una nueva máquina virtual en Google Cloud.

### 4.Instalación de Git
Instalé Git en la VM para el control de versiones:

### 5.Autenticación con GitHub
Configuré la autenticación con GitHub creando un token de acceso personal

### 6.Clonación del Repositorio
Cloné mi fork del repositorio XV6 en la VM:

### 7.Instalación de Dependencias
Instalé las herramientas necesarias para compilar XV6
(sudo apt install make qemu bc gcc)

### 8.Compilación de XV6
Compilé el sistema operativo XV6

## Problemas Encontrados y Soluciones

#### Error en `make qemu`

**Problema:** 
Después de instalar todas las dependencias listadas, el comando `make qemu` fallaba con errores de compilación. 
Consulté el error con una IA, que identificó una falta de herramientas de compilación completas.

**Solución:** 
El problema se resolvió instalando el paquete `build-essential`, que incluye un conjunto completo de herramientas de compilación además de gcc:


`sudo apt install build-essential`


### Verificación Final
Una vez instalado `build-essential`, el comando `make qemu` funcionó correctamente y XV6 se ejecutó sin problemas.
