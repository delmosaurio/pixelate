/*
 *      img.h
 *      
 *      Copyright (c) 2008 Delmo Carrozzo <dcardev@gmail.com>
 *      
 *      Este archivo es parte de pixelate.
 *      
 *      pixelate es Software Libre; Usted puede redistribuirlo y/o modificarlo 
 *      bajo los términos de la Licencia Pública General de la GNU según los 
 *      datos publicados por la Free Software Foundation, de la versión 2
 *      de la Licencia,o bien (a su elección) cualquier versión posterior.
 *      
 *      Usted debe haber recibido una copia de la Licencia Pública General
 *      de la GNU junto con este programa, si no es asi, ingrese en 
 *      <http://www.gnu.org/licenses/>.
 *      
 *      
 *      Realizado para: Grupo 11 - Taller C
 *      
 *      Descripción: Esta libreria es la encargada de ejecutar las acciones
 *                   sobre los archivos y mapas de bit dependiendo del tipo
 *                   del archivo que se quiera manipular, es decir, si la imagen
 *                   que queremos modificar es del tipo bmp, se llamaran a las 
 *                   funciones necesarias para manipular este tipo de archivo. 
 *                  
 *                   En esta version solo se acepatan imagenes del tipo BMP, 
 *                   pero si esta lista para comprender otros tipos de extensiones
 *                   se tendria que desarrollar nuevas librerias para la comprension
 *                   de otros tipos de archivos como jpeg, png, tif, etc. Lo unico
 *                   que tendria que hacerse es la extracion de los nuevos archivos
 *                   de la forma en que hace bmp_encabezado y bmp_mapabit.
 *                  
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include "bitmaps.h"
#include "bmp_encabezado.h"
#include "bmp_mapabit.h"

#include "e_blur.h"
#include "e_lineas.h"
#include "e_negativo.h"
#include "e_redimensionar.h"
#include "e_rotar.h"


#ifndef IMG_H
#define IMG_H

/*Codigos para tipos de imagenes*/
 #ifndef COD_BMP
  #define COD_BMP 0 /*Soportado*/
 #endif

 #ifndef COD_JPG
  #define COD_JPG 1 /*No soportado*/
 #endif

 #ifndef COD_PNG
  #define COD_PNG 2 /*No soportado*/
 #endif
 
/*Codigos Efectos*/
 #ifndef EFECTO_BLUR
  #define EFECTO_BLUR 0
 #endif

 #ifndef EFECTO_LINEAS
  #define EFECTO_LINEAS 1
 #endif
 
 #ifndef EFECTO_NEGATIVO
  #define EFECTO_NEGATIVO 2
 #endif
 
 #ifndef EFECTO_REDIMENSION
  #define EFECTO_REDIMENSION 3
 #endif
 
 #ifndef EFECTO_ROTAR
  #define EFECTO_ROTAR 4
 #endif

/*
 * 
 * name img_obtener_ext
 *   Esta funcion obtiene la extension de un archivo de imagen 
 *   desde una cadena.
 * 
 * @param char* - cadena donde se extraera la extension.
 * 
 * @return int - retorna el codigo de la extension, en caso de que no exista retorna -1
 * 
 */
int img_obtener_ext(char* ); /*Implementada*/


/*
 * 
 * name img_extraer_encabezado
 *   Esta funcion es la encargada de ejecutar la funcion correcta
 *   para la extraccion de un encabezado de imagen.
 * 
 * @param FILE* - Archivo del cual se extraera el encabezado
 * @param int - codigo de extension
 * @param ... Este parametro va a depender del tipo de codigo de extecion.
 *            Si estamos en un bmp, este recibira un encabezado de bmp
 *            y asi con las demas extensiones.
 * 
 * @return int retorna 1 si la operacion pudo realizarse o 0 en caso contrario
 * 
 */
int img_extraer_encabezado(FILE*, int, ...); /*Implementada*/

/*
 * 
 * name img_extraer_mapa
 *   Es el puente entre la funcion de la extraccion de un mapa bit
 *   de un archivo de imagen con la imgen_mapabit, por ejemplo, si el 
 *   archivo de imagen es un bmp, llamara a la funcion para la extraccion
 *   del mapa bit de un bmp.
 * 
 * @param FILE* - archivo del cual se extraera el mapa.
 * @param imagen_mapabit ** - lugar donde se guardara el mapa.
 * @param int - codigo de extension. 
 * @param ... - Este parametro va a depender del tipo de codigo de extecion.
 *              Si estamos en un bmp, este recibira un encabezado de bmp
 *              y asi con las demas extensiones.
 * 
 * @return imagen_mapabit - imagen_mapabit extraido.
 * 
 */
imagen_mapabit *img_extraer_mapa(FILE*, imagen_mapabit **, int, ...); /*Implementada*/

/*
 * 
 * name img_guardar
 *   Esta funcion llamara a las funcionesmo correspondientes al tipo de archivo
 *   conocido por el codigo de extension, para guardar el encabezado y el mapa de bit
 *   en el archivo.
 *  
 * 
 * @param FILE* - Archivo donde se guardara el mapabit
 * @param imagen_mapabit ** - imagen a guardar
 * @param int - codigo de extension
 * @param ... Este parametro dependera de cod, por ejemplo,
 *            si se quiere guardar una imagen bmp, se recibira el 
 *            encabezado del mismo.
 * 
 * @return int - Retorna 1 si la operacion fue correcta, 0 en caso contrario.
 * 
 */
int img_guardar(FILE*, imagen_mapabit **, int, ...); /*Implementada*/

/*
 * 
 * name img_mostrar_encabezado
 *   Muetra en encabezado de un archivo de imagen.
 * 
 * @param int - Condigo de extension
 * @param ... - Estructuras necesarias para mostrar el encabezado del archivo de
 *              imagen del tipo Cod
 * 
 * @return int - Retorna 1 si la operacion fue correcta, 0 en caso contrario.
 * 
 */
int img_mostrar_encabezado(int, ...); /*Implementada*/

/*
 * 
 * name img_efecto
 *   Aplica el efecto definido por el codigo de efecto.
 *   Los codigos de efecto.
 * 
 * @param imagen_mapabit ** - Imagen a la que se aplicara el efecto.
 * @param int - codigo de extension.
 * @param ... - Este parametro recibira las estructuras que se tengan
 *              que modificar junto con el efecto, ejemplo, el encabezado
 *              de un bmp cuando se rota.
 *              
 * @return int - Retorna 1 si la pudo hacer la operacion, 0 de lo contrario.
 * 
 */
int img_efecto(imagen_mapabit **, int, ...); /*Implementada*/

#endif /*Fin IMG_H*/

