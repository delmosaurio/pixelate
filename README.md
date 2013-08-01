# pixelate

Es una sencilla interfaz de línea de órdenes para manipular archivos
de imágenes, desarrollado como trabajo final para la materia
'Seminario de lenguajes - Taller C' de la Universidad Nacional de 
La Plata (UNLP), en su versión 0.5 sólo acepta archivos de tipo 
BMP sin compresión.

Es Software Libre; Usted puede redistribuirlo y/o modificarlo 
bajo los términos de la Licencia Pública General de la GNU según los 
datos publicados por la Free Software Foundation, de la versión 2
de la Licencia, o bien, a su elección, cualquier versión posterior.
      
Usted debe haber recibido una copia de la Licencia Pública General
de la GNU junto con este programa, si no es asi, ingrese en 
<http://www.gnu.org/licenses/>.

## Descripción

Para Usuarios:

  Está probado en plataformas Linux (en distribuciones Debian) y Windows (XP);
  para comenzar a utilizar el programa, lea el archivo de ayuda help bmp,
  o utilice `$:pixelate -? 0 -h`


Para Desarrolladores:

  El 99% del proyecto fue desarrollado bajo Linux (Ubuntu 8.04, para ser más 
preciso). En esta versión '0.5' sólo soporta imágenes del tipo BMP sin compresión; 
están desarrollados los módulos para comprender este tipo de archivo. Pero 
también está listo para que en un futuro se implementen módulos para la 
manipulación de otros tipos de imágenes, como pueden ser jpeg, png, tif, etc...
  Para compilar la aplicación, se recomienda Utilizar GCC (GNU Compiler Collection),
ya que ésta fue probada y depurada sobre este compilador en su versión 4.2.3, 
puede utilizar el archivo makefile para su compilacion en GCC.
Para los desarroladores en plataforma Windows, podrían utilizar DEV C++, creando un proyecto
para su compilación.


  La forma interna de cómo trabaja el programa es la siguiente:
Se ha desarrollado una estructura genérica para cuaquier tipo de imagen (mapa bits), 
la cual actua de puente entre el archivo de ENTRADA y el de SALIDA, es decir, cuando 
se extrae el mapa de bits se guarda en esta estructura; los módulos que se encargan 
de aplicar efectos al mapa, conocen sólo este tipo de estructura, así se logra modificar
cualquier tipo de imagen con un mismo módulo. Luego, dependiendo del tipo de archivo 
de salida, se guarda el mapa modificado en su forma correcta.
  Como comentamos antes, están desarrollados los módulos para comprender archivos BMP, 
pero implementando nuevos módulos para extraer y guardar el mapa de bits de otros archivos,
 obtendríamos las mismas acciones que con los de tipo BMP.

Informacion adicional:

 - Dentro de la carpeta bin estan los ejecutables para windows y linux.
 - Dentro de src esta el codigo de la aplicacion.
 - Dentro de test hay imagenes de prueba y archivos shell para testear.

## Ayuda

                      PIXELATE

      -= Copyright 2008 'Grupo 11 - Taller C' =-

   Pixelate una sencilla interfaz de línea de órdenes para manipular archivos
   de imágenes, desarrollado como trabajo final para la materia
   'Seminario de lenguajes - Taller C' de la Universidad Nacional de 
   La Plata (UNLP), en su versión 0.5 sólo acepta archivos de tipo 
   BMP sin compresión.


   -? o -h                - Muestra ayuda en pantalla.
   -r                     - Rota la imagen a 90°.
   -r  N                  - Rota la imagen a N° (90°, -90° ,180°).
   -n                     - Genera un negativo a la imagen.
   -d                     - Duplica el tamaño de la imagen.
   -f                     - Reduce a la mitad el tamaño de la imagen.
   -x   %%                - Redimensiona la imagen en un porcentaje dado.
   -b RADIO               - Produce un efecto blur de RADIO pixeles.
   -lh ANCHO SPACIO COLOR - Dibuja lineas de COLOR horizontales de ANCHO pixeles, 
                            separadas por ESPACIO pixeles.
   -lv ANCHO SPACIO COLOR - Dibuja lineas verticales de COLOR de ANCHO pixeles,
                            separadas por ESPACIO pixeles.
   -lb ANCHO SPACIO COLOR - Dibuja lineas verticales y horizontales de COLOR de ANCHO pixeles,
                              separadas por ESPACIO pixeles.
   -o SALIDA              - Especifica el nombre del archivo de imagen salida.
   -i ENTRADA             - Especifica el nombre del archivo de imagen con el cual se trabajara.
                            Si no se indica el archivo de salida y se guardara por defecto como
                            out.ext.
 
## Copyright

Copyright (c) 2008 Delmo Carrozzo <dcardev@gmail.com>

2008 'Grupo 11 - Taller C'
