# Plantilla para proyectos con SDL en Visual Studio

Instrucciones
-------------

* Al a�adir un proyecto a la soluci�n recuerda a�adir la p�gina de propiedades ProyectosSDL.props al nuevo proyecto: en el men� Ver -> Otras ventanas -> Administrador de propiedades -> Agregar hoja de propiedades existente, busca el archivo ProyectosSDL.props para incorporarlo. Sin hacer esto es posible que el compilador no encuentre la biblioteca SDL o se produzcan otros errores de compilaci�n.

* Si quieres a�adir una nueva biblioteca, copia su directorio en la soluci�n y a�ade los nuevos elementos al archivo ProyectoSDL.props: IncludePath, LibraryPath, AdditionalDependencies y LocalDebuggerEnvironment.

* Los proyectos se deber�an ejecutar sin problemas desde Visual Studio, pero los programas compilados que quedan en la carpeta bin (*Debug.exe y *Release.exe) al ejecutarse directamente mostrar�n un mensaje de error indicando que la biblioteca SDL2.dll u otras no est�n disponibles. Esto se puede evitar copiando los archivos .dll en SDL2* a la carpeta bin del proyecto.

* Para la comprobaci�n de fugas de memoria, incluye el archivo "checkML.h" en todos los archivos .cpp del proyecto antes que cualquier otro #include. Las fugas detectadas aparecer�n en la consola del depurador de Visual Studio. El archivo checkML.h puede producir un error si la versi�n del est�ndar de C++ es anterior a C++17. En tal caso accede a las propiedades del proyecto y selecciona esa versi�n del est�ndar.


Bibliotecas
-----------

* SDL2 2.28.2
* SDL2_image 2.6.3

M�s informaci�n sobre las bibliotecas en https://www.libsdl.org/.
