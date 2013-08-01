/*
 *      arg_main.c
 *      
 *      Copyright (c) 2008 Delmo Carrozzo <dcardev@gmail.com>
 *      
 *      Este archivo es parte de pixelate.
 *      
 *      pixelate es Software Libre; Usted puede redistribuirlo y/o modificarlo 
 *      bajo los términos de la Licencia Pública General de la GNU según los 
 *      datos publicados por la Free Software Foundation, de la versión 3
 *      de la Licencia,o bien (a su elección) cualquier versión posterior.
 *      
 *      Usted debe haber recibido una copia de la Licencia Pública General
 *      de la GNU junto con este programa, si no es asi, ingrese en 
 *      <http://www.gnu.org/licenses/>.
 *      
 *      
 *      Realizado para: Grupo 11 - Taller C
 *      
 *      Descripción: Implementacion de la funciones para la comprobacion de
 *                   argumentos al main. 
 * 
 */



#include "arg_main.h"

#ifndef ARG_MAIN_C
#define ARG_MAIN_C

/*
 * 
 * name arg_nuevo
 *   Esta funcion crea un nuevo argumento.
 * 
 * @param char* - Argumento ejemplo ("-r" o "-lv")
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
arg_t arg_nuevo(char* arg, uint8_t min, uint8_t max, uint8_t pri, uint8_t cupo, ...)
{
  
  va_list pa; /*Lista de argumentos variables*/
  int i;
  
  arg_t nuevo; /*Nuevo argumento usado para el retorno.*/
  
  va_start(pa, cupo); /*Inicio de argumentos variables.*/

  
  /*Alocamos memoria para guardar el nombre del argumento*/
  nuevo.arg=(char*)malloc((strlen(arg)+1)*sizeof(char));
  
  /*Copiamos las caracteristicas del argumento.*/
  strcpy(nuevo.arg, arg); 
  nuevo.min = min;
  nuevo.max = max;
  nuevo.prioridad = pri;
  nuevo.cupo = cupo;
  nuevo.sub = NULL;
  
  if (cupo >= 1) /*Si hay sub-argumentos.*/
  { 
     char* temp;
     /*Alocamos memoria para los sub-argumentos*/
     nuevo.sub = (char**)malloc(cupo*sizeof(char*));
     
     
     for(i=0;i<cupo;i++) /*Copiamos los sub-argumentos.*/
     {
       temp=va_arg(pa, char*);
       *(nuevo.sub+i) = (char*)malloc((strlen(temp)+1)*sizeof(char));
       strcpy(*(nuevo.sub+i), temp);
       *(*(nuevo.sub+i)+strlen(temp)) = 0;
     }
  }
  va_end(pa);
  
  return nuevo; /*Retornamos el nuevo argumento.*/
}

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
int arg_esOpcion(argumentos_t *args, char* cad)
{
  int result=0;
  int i=0;
  
  /*
   * Recorremos la estructura hasta encontrar el argumento,
   * Si no existe, la variable result nunca se hara 1 por
   * lo tante se retornara que no es una opcion.
   * 
   */
  while (i<args->cant && !result)
  {
    result = (strcmp((args->args+i)->arg, cad)==0);
    i++;
  }
  
  return result;
}

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
argumentos_t arg_crear(uint8_t min)
{
  argumentos_t nuevo;
  
  /*Inicializamos */
  nuevo.cant = 0;
  nuevo.min = min;
  nuevo.args = NULL;
  
  return nuevo; /*Retornamos.*/
}

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
void arg_agregar(argumentos_t *args, arg_t nuevo)
{
  /*
   * Comproamos si ya se ah dado de alta un argumento
   * si no alocamos memoria para el primer elemento,
   * si no reallocamos.
   */
  if (args->cant==0)
  {
    args->args = (arg_t*)malloc(sizeof(arg_t));
  }
  else
  {
    args->args = (arg_t*)realloc(args->args, (args->cant+1)*sizeof(arg_t));
  }

  /*Agregamos el nuevo argumento.*/
  *(args->args+args->cant) = nuevo;
  args->cant++;  
}

/*
 * 
 * name arg_buscar
 *   Busca una opcion dentro de la estructura no se comprueba
 *   si existe, o si es opcion, para esto utilice la funcion 
 *   arg_esOpcion.
 * 
 * @param argumentos_t * - Estructura la cual se extraera el argumento.
 * @param char* - Nombre del argumento.
 * 
 * @return arg_t - argumento buscado.
 * 
 */
arg_t arg_buscar(argumentos_t *args, char* cad)
{
  int i=0;
  /*
   * Buscamos el argumento y lo retornamos.
   */
  while((!strcmp((args->args+i)->arg, cad)==0)) i++; 
  return *(args->args+i);
  
}

/*
 * 
 * name arg_sub_exist
 *   Busca dentro de un argumento un sub-argumento.
 * 
 * @param arg_t - argumento donde se buscara.
 * @param char* - sub-argumento.
 * 
 * @return int - 1 si existe y 0 en caso contrario.
 * 
 */
int arg_sub_exist(arg_t arg, char* cad)
{
  int i=0;
  int ok=0;
  
  /*
   * Miestras hay sub-argumentos y no se haya encontrado.
   * 
   */
  while(i<arg.cupo && !ok)
  {
    ok=((strcmp(*(arg.sub+i), cad)==0));
    i++;
  }
  return ok;
  
}

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
int arg_comprobar(argumentos_t *args, int argc, char* argv[])
{
  int i=1;/*Indice del array de argumentos
            no es 0 ya que el elemnto 0
            es el nombre del programa.*/
  int c_sub, j;
  
  int u_pri=0; /*Ultima prioridad.*/
  
  /*Estructura que usaremos para ir sacando los argumentos
  de la estructura args.*/
  arg_t aux;
  
  /*Comprobamos si la cantidad de argumentos es correcta.*/
  if((args->min+1)>argc) return 0;

  /*
   * Reccoremos todos los argumentos, en caso de error 
   * se retornara 0 dentro del ciclo while.
   */
  while(i<argc)
  {
    /*
     * En el ciclo se era comprobando de a argumento.
     * es decir, se comprueba un argumento, y sus caracteristicas,
     * incluyendo los sub-argumentos y luego se pasara al siguiente
     * argumento siempre y cuando el comprobado sea correcto.
     * 
     */
    
    /*Si no es opcion, avisamos que se esperaba una y salimos*/
    if (!arg_esOpcion(args, argv[i]))
    {
      printf("Se esperaba una opcion en lugar de '%s'.\n", argv[i]);
      return 0;
    }
    /*Buscamos el argumentos para trabajar con el.*/
    aux = arg_buscar(args, argv[i]);
    
    /*Cumprobamos la prioridad del argumento
      siempre y cuando tengasmos que hacerlo
      es decir cuando sea distinta de 0;
      Guardamos la prioridad como ultima
      para comprobar el sig argumento.*/
    if (aux.prioridad!=0)
    {
      if ( u_pri > aux.prioridad)
      {
        printf("Error en la prioridad de los argumentos para '%s'.\n", argv[i]);
        return 0;
      } 
      u_pri = aux.prioridad;
    }
    
    c_sub=0;  /*Variable para contar los sub-argumentos en el array*/
    j=(i+1);  /* inicializamos la variable para el ciclo
                   en el lugar donde estamos en el array + 1*/
    
    /*Contamos los sub-argumentos. si no hay la variable queda en cero*/
    while (j<argc && !arg_esOpcion(args, argv[j]))
    {
      c_sub++;j++;
    }

    /*Comprobamos la cantidad de sub-argumentos
      con el minimo y el maximo del argumento.
      si hay un error avisamos y retornamos 0*/
    if (aux.min > c_sub)
    {
      printf("Se esperaban mas agumentos para '%s'.\n", argv[i]);
      return 0;
    }
    if (aux.max < c_sub)
    {
      printf("Se esperaban menos agumentos para '%s'.\n", argv[i]);
      return 0;
    }
    
    /*si llegamos aqui quiere decir que los sub-argumentos
      estan en cantidad adecuada para comprbar
      conprobamos los sub-argumentos
      en caso de error avisamos y retornamos 0*/
    if (aux.cupo > 0)
    {
      int k=1;
      int control=1;
      while(k<=c_sub && control)
      {
        control = arg_sub_exist(aux, argv[i+k]);
        k++;
      }
      if (!control)
      {
        printf("Error en los argumentos para '%s' \n", argv[i]);
        return 0;
      }
    }
    /*incrementamos en indice del array para posisionarnos en el 
      proximo argumento.*/
    i+=c_sub+1;
  }
 
    /*Si llegamos aqui quiere decir que los argumentos son correctos.*/
  return 1;
}

#endif /*Fin ARG_MAIN_C*/
