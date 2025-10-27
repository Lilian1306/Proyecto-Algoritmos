# Sistema de Gestión de Envíos "Envíos Garantizados, S.A." (Consola C++)

## Descripción

Este es un sistema simple desarrollado en C++ para la gestión de operaciones básicas de una empresa de envíos ficticia, "Envíos Garantizados, S.A.". El programa se ejecuta en la consola y permite administrar usuarios con diferentes roles (Cliente, Administrador, Controlador, Mensajero) y el ciclo de vida de los paquetes, desde su solicitud hasta la entrega. Los datos se manejan en memoria durante la ejecución del programa.

## Características Principales

El sistema ofrece diferentes funcionalidades según el rol del usuario que inicie sesión:

**Generales:**
* Inicio de sesión basado en correo electrónico y contraseña.
* Menús interactivos en consola.

**Cliente:**
* Auto-registro de nuevas cuentas.
* Solicitar un nuevo envío con descripción y peso (límite de 15 lbs).
* Cálculo automático del costo del envío (tarifa normal o doble según la hora).
* Visualizar el estado de todos sus envíos solicitados (incluyendo mensajero asignado si aplica).
* Realizar un "pago en línea" (simulado) que cambia el estado del paquete a "En Tránsito".

**Administrador:**
* Crear nuevas cuentas de usuario (tipo Cliente por defecto en `altaUsuario`, aunque el constructor inicializa otros roles).
* Ver un listado de todos los clientes registrados.
* Dar de baja (eliminar) a un cliente especificando su nombre completo.
* Generar un reporte general que muestra la cantidad de paquetes en cada estado (Solicitado, En Tránsito, Entregado).

**Controlador:**
* Visualizar todas las solicitudes de envío que están pendientes de asignación (estado "Solicitado").
* Asignar un envío pendiente a un mensajero registrado, cambiando el estado del paquete a "En recolección".

**Mensajero:**
* Visualizar la lista de entregas que tiene asignadas.
* Marcar un paquete asignado como "Entregado".

## Tecnologías Utilizadas

* **Lenguaje:** C++
* **Bibliotecas Estándar (STL):**
    * `iostream` para entrada/salida de consola.
    * `string` para manejo de texto.
    * `vector` para almacenar usuarios y paquetes en memoria.
    * `ctime` para obtener la hora actual (cálculo de costo).
    * `limits` para validación de entrada numérica.
    * `algorithm` para la función `remove_if` (baja de usuario).
* **Compilador:** g++ (MinGW) o compatible con C++ estándar.
* **Control de Versiones:** Git / GitHub

## Cómo Compilar y Ejecutar

1.  **Requisitos:** Necesitas un compilador de C++ (como g++ instalado a través de MinGW en Windows, o el compilador estándar en Linux/macOS).
2.  **Compilación:** Abre una terminal o línea de comandos en la carpeta donde están los archivos fuente y ejecuta:
    ```bash
    g++ Proyecto.cpp SistemaEnvios.cpp Usuario.cpp Paquete.cpp -o proyecto.exe -std=c++11
    ```
    *Nota: `-std=c++11` es recomendable, aunque podría compilar sin él.*
3.  **Ejecución:** Una vez compilado, ejecuta el programa:
    * En Windows: `.\proyecto.exe` o `proyecto.exe`
    * En Linux/macOS: `./proyecto.exe` (o el nombre que le hayas dado)

## Uso

Al ejecutar el programa, se presentará un menú principal para elegir el tipo de usuario con el que deseas ingresar.

**Credenciales por Defecto (definidas en `SistemaEnvios.cpp`):**

* **Administrador:** `admin@envios.com` / `12345`
* **Cliente:** `tony@email.com` / `tony123`
* **Mensajero:** `mensajero@email.com` / `mensajero123`
* **Controlador:** `control@envios.com` / `ctrl123`

Los clientes también pueden crear sus propias cuentas desde el menú de cliente. Sigue las instrucciones en pantalla para navegar por los menús y utilizar las funcionalidades.

## Estructura del Proyecto

* `Proyecto.cpp`: Contiene la función `main`, los menús principales y la lógica de interacción con el usuario.
* `SistemaEnvios.h` / `SistemaEnvios.cpp`: Clase principal que encapsula toda la lógica de negocio (gestión de usuarios, paquetes, estados, etc.).
* `Usuario.h` / `Usuario.cpp`: Clase que define la estructura y datos de un usuario.
* `Paquete.h` / `Paquete.cpp`: Clase que define la estructura y datos de un paquete/envío.
* `proyecto.exe`: (Opcional) El ejecutable compilado.

## Posibles Mejoras (Trabajo Futuro)

* Persistencia de datos (guardar/cargar usuarios y paquetes en archivos o base de datos).
* Interfaz gráfica de usuario (GUI).
* Reportes más detallados (por fecha, por cliente, ingresos).
* Validaciones de entrada más robustas.
* Notificaciones (simuladas) para el cliente/mensajero.

## Autor(a)

* Lilian Elizabeth Tuyuc Tzaj

