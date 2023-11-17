# Plantilla para proyectos con SDL en Visual Studio

Instrucciones
-------------

* Al añadir un proyecto a la solución recuerda añadir la página de propiedades ProyectosSDL.props al nuevo proyecto: en el menú Ver -> Otras ventanas -> Administrador de propiedades -> Agregar hoja de propiedades existente, busca el archivo ProyectosSDL.props para incorporarlo. Sin hacer esto es posible que el compilador no encuentre la biblioteca SDL o se produzcan otros errores de compilación.

* Si quieres añadir una nueva biblioteca, copia su directorio en la solución y añade los nuevos elementos al archivo ProyectoSDL.props: IncludePath, LibraryPath, AdditionalDependencies y LocalDebuggerEnvironment.

* Los proyectos se deberían ejecutar sin problemas desde Visual Studio, pero los programas compilados que quedan en la carpeta bin (*Debug.exe y *Release.exe) al ejecutarse directamente mostrarán un mensaje de error indicando que la biblioteca SDL2.dll u otras no están disponibles. Esto se puede evitar copiando los archivos .dll en SDL2* a la carpeta bin del proyecto.

* Para la comprobación de fugas de memoria, incluye el archivo "checkML.h" en todos los archivos .cpp del proyecto antes que cualquier otro #include. Las fugas detectadas aparecerán en la consola del depurador de Visual Studio. El archivo checkML.h puede producir un error si la versión del estándar de C++ es anterior a C++17. En tal caso accede a las propiedades del proyecto y selecciona esa versión del estándar.


Bibliotecas
-----------

* SDL2 2.28.2
* SDL2_image 2.6.3

Más información sobre las bibliotecas en https://www.libsdl.org/.
