/*
 *      arg_main.h
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
 *      Descripción: Prototipo de funciones y estructuras, esta libreria
 *                   esta desarrollada para comprobar los argumentos del
 *                   main. La forma de uso, es dar a conocer todos las
 *                   operaciones que soporta la aplicacion usando  las
 *                   estructuras arg_t y argumentos_t, y luego comprobarlas
 *                   con los parametros recibidos en el main.
 *                   Notese que no existe una funcion para eliminar un 
 *                   argumento de la estructura, ya que esta libreria
 *                   es para comprobar argumentos, pero estos van a ser
 *                   una sola vez configurados al comenzar el programa
 *                   y no modificado durante el mismo. Lo que se intenta
 *                   es facilitar el trabajo de comprobacion de argumentos
 *                   para una aplicacion.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef ARG_MAIN_H
#define ARG_MAIN_H


/* ESTRUCTURAS */

/*
 *  arg_t abstrae un argumento con sus caracteristicas.
 */
typedef struct
{
   char* arg;              /*Argumento ejemplo '-r' o '-lv'*/
   unsigned int min;       /*Minimo de sub argumentos*/
   unsigned int max;       /*Maximo de sub argumentos*/
   unsigned int prioridad; /*Prioridad del argumento (0 = sin prioridad)*/
   
   /* Cupo es utilizado cuando los sub argumentos son limitados
    * ejemplo: -r puede tomar (90, -90, 180)
    */
   unsigned int cupo;     
   /*Aqui se indican los sub argumentos propiamente dichos
    * para el ejemplo: {90, -90, 180}
    */
   char** sub;
} arg_t;

/*
 * Esta estructura contendra todos los argumentos.
 * Usando las funciones definidas a continuacion
 * se pueden crear nuevos argumentos, y el campo cant
 * se ira incrementando automaticamente cuando agrega uno.
 */
typedef struct
{
  unsigned int cant; /*Cantidad de argumentos*/
  unsigned int min; /*Cantidad minima de argumentos*/
  arg_t *args; /*Argumentos.*/
} argumentos_t;


/* PROTOTIPOS */

/*
 * 
 * name arg_nuevo
 *   Crea un nuevo argumento.
 * 
 * @param char* - Argumento.
 * @param uint8_t - Minima cantidad de sub-argumentos (si es que tiene)
 * @param uint8_t - Maxima cantidad de sub-argumentos (si es que tiene)
 * @param uint8_t - Prioridad del argumento.
 * @param uint8_t - Cantidad de sub argumentos (si es que tiene)
 * @param char* ... - Sub-argumentos.
 * 
 * @return arg_t - Nuevo argumento
 * 
 * @example - Ejemplo que muestra como crear el argumento -r (rotado)
 *   Codigo C:
 *     arg_t Nuevo = arg_nuevo("-r", 0, 1, 2, 3, "90", "-90", "180");
 * 
 */
arg_t arg_nuevo(char*, uint8_t, uint8_t, uint8_t, uint8_t, ...); /*Implementada*/

/*
 * 
 * name arg_esOpcion
 *   Esta funcion comprueba si una cadena de caracteres 
 *   es una opcion.
 *   Recuerde que debe haber una configuracion previa de los argumentos,
 *   es decir deben darse de alta todos los argumentos y sus caractersticas.
 * 
 * @param argumentos_t * - Estructura que contiene los argumentos.
 * @param char* - Cadena para la comprobacion.
 * 
 * @return int - Retorna 1 si es una opcion o 0 en caso contrario.
 * 
 */
int arg_esOpcion(argumentos_t *, char*);

/*
 * 
 * name arg_crear
 *   Inicializa una estructura, con cant en 0, el minimo
 *   con la variable pasada por argumento y args en NULL
 * 
 * @param uint8_t - Minima cantidad de argumentos para el main.
 * 
 * @return argumentos_t - Retorna una extructura inicializada.
 * 
 */
argumentos_t arg_crear( uint8_t ); /*Implementada*/ /*Inicializa estructura argumetos.*/

/*
 * 
 * name arg_agregar
 *   Agrega un argumento a la estructura, reallocando memoria
 *   para el nuvo argumento.
 * 
 * @param argumentos_t - Estructura a la cual se agregara el argumento.
 * @param arg_t - Nuevo argumento a agregar.
 * 
 * @return void - Utilizada como proceso.
 * 
 */
void arg_agregar(argumentos_t *, arg_t); /*Implementada*/ /*Agrega un argumento.*/

/*
 * 
 * name arg_comprobar
 *   Esta funcion conprueba los argumentos deribados del main.
 *   Tambien indica avisos en pantalla sobre posibles errores.
 *   Antes de llamar a esta funcion, compruebe que la cantidad de
 *   argumentos sia mayor a la minima.
 * 
 * @param argumentos_t * - Estructura que contiene los argumentos
 * 
 *  //Los siguientes parametros son deribados del main
 *  //recude no modificarlos al pasarlos.
 * @param int - Cantidad de argumetos a comprobar.
 * @param char* [] - Argumentos y sub-argumentos.
 * 
 * @return int - Retorna 1 si son correctos los argmentos y subargumentos 
 *               y 0 en caso contrario.
 * 
 */
int arg_comprobar(argumentos_t *, int argc, char* argv[]); /*Implementada*/ /*Comprueba los argumentos*/

#endif /*Fin ARG_MAIN_H*/
