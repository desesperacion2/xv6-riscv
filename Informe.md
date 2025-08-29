Pasos seguidos (siguiendo el video subido a webc)
  1. Hacer un fork del repositorio de XV6
  2. Una vez en el directorio del proyecto, creé una nueva rama con mi nombre para trabajar en ella.
  3. Crear una VM en google cloud
  4. Instale Git
  5. Inicie sesion con github creando el token
  6. Clone mi repositorio de XV6 en la VM
  7. Instale las dependencias (make, qemu, bc y gcc)
  8. Compile XV6
Problemas:
  Tuve problemas para realizar el make qemu luego de instalar todas las dependencias, pregunte por el error que arrojaba la consola a una IA, la respuesta fue una falta en las herramientas de compilacion.
  El problema se soluciono instalando el paquete build-essential, el cual incluye varias herramientas de compilacion ademas de gcc.
