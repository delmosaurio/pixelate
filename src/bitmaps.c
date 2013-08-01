/*
 *      bitmaps.c
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
 *      Descripción: Implementacion de las funciones para la manipulacion
 *                   de mapa de bits.
 */

#include "bitmaps.h"

#ifndef BITMAPS_C
#define BITMAPS_C

/*
 * 
 * name nueva_imagen
 *   Crea una nueva imagen_mapabit alocando memoria para sus elementos.
 * 
 * @param uint32_t - Ancho del mapa de bits
 * @param uint32_t - Alto del mapa de bits.
 * @param uint16_t - bit por pixels del mapa de bits.
 * @param uint32_t - colores usados del mapa de bits.
 * 
 * @return imagen_mapabit - Nueva estructura inicializada.
 * 
 */
imagen_mapabit nueva_imagen(uint32_t width, uint32_t height, uint16_t bitCount, uint32_t colorsUsed)
{
   imagen_mapabit nueva;

   nueva.width = width;
   nueva.height = height;
   nueva.bitCount = bitCount;
   nueva.colorsUsed = colorsUsed;

  
   /*Para las imagenes de bitCount<=8 debemos alocal memoria para la
     paleta tambien, y para las imagenes de 16 bit, si bien no 
     contienen paleta despues del encabezado, continen una serie 
     de datos, los cuales contiene informacion de como se
     manipulara el bitmap, nosotros lo tomaremos como si es una paleta.*/
   switch (bitCount)
    /*Inicializamos la estrucuta.*/
   {
        case 1:{ 
                 int colores=(colorsUsed==0)?2:colorsUsed;
                 nueva.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                 nueva.mapa.map_1 = (pixel_1*)malloc((width*height)*sizeof(pixel_1));
               }
               break;
        case 4:{
                 int colores=(colorsUsed==0)?16:colorsUsed;
                 nueva.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                 nueva.mapa.map_4 = (pixel_4*)malloc((width*height)*sizeof(pixel_4));
               }
               break;
        case 8:{
                 int colores=(colorsUsed==0)?256:colorsUsed;
                 nueva.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                 nueva.mapa.map_8 = (pixel_8*)malloc((width*height)*sizeof(pixel_8));
               }
               break;
        case 16:{
                 int colores=16;
                  nueva.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                  nueva.mapa.map_16 = (pixel_16*)malloc((width*height)*sizeof(pixel_16));
                }
               break;
        case 24:nueva.mapa.map_24 = (pixel_24*)malloc((width*height)*sizeof(pixel_24));
               break;
        case 32:nueva.mapa.map_32 = (pixel_32*)malloc((width*height)*sizeof(pixel_32));
               break;
   } 

   return nueva;
}


/*Prototipo de funciones para promedio.*/
uint32_t prom_P1(mapa_t *, int, int, int, uint32_t, uint32_t);
uint32_t prom_P4(mapa_t *, int, int, int, uint32_t, uint32_t);
uint32_t prom_P8(mapa_t *, int, int, int, uint32_t, uint32_t);
uint32_t prom_P16(mapa_t *, int, int, int, uint32_t, uint32_t);
uint32_t prom_P24(mapa_t *, int, int, int, uint32_t, uint32_t);
uint32_t prom_P32(mapa_t *, int, int, int, uint32_t, uint32_t);

/*divide y redondea  (suma, elementos)  - utilizado para el promedio.*/
uint32_t div_redondeo(uint32_t, int);

/*Prototipo para la funcion del calculo del promedio.*/
uint32_t calc_prom(mapa_t *, int, int, int, uint32_t, uint32_t \
               , uint32_t (*)(mapa_t *, int, int, int, uint32_t, uint32_t));


/*
 * 
 * name promPixels
 *   Calcula el promedio de pixeles en un radio especificado.
 * 
 * @param mapa_t * - mapa del cual se extraera el promedio
 * @param uint32_t - ancho de mapa.
 * @param uint32_t - alto del mapa.
 * @param uint16_t - bits por pixels del mapa.
 * @param int - columna de inicio.
 * @param int - fila para el inicio.
 * @param int - radio.
 * 
 * @return uint32_t - Promedio calculado, luego para dividir el los difirentes colores
 *                    consulte los macros definidos en colores.h.
 * 
 */
uint32_t promPixels(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t bc, int col, int fil, int radio)
{
   /*Funcion para la ejecucion del calculo
     que va a depender de los bit por pixels*/
   uint32_t (*func)(mapa_t *, int, int, int, uint32_t, uint32_t);

   switch(bc)
   {
      /*Obtenemos la direccion correcta de la funcion para el calculo.*/
      case 1:func = prom_P1;
             break;
      case 4:func = prom_P4;
             break;
      case 8:func = prom_P8;
             break;
      case 16:func = prom_P16;
              break;
      case 24:func = prom_P24;
              break;
      case 32:func = prom_P32;
              break;
   }
   
   /*retornamos el calculo del promedio.*/
   return calc_prom(mapa, col, fil, radio, w, h, func);
} /*Fin promPixels*/


/*Implementacion de funciones para el calculo de promedio.*/

/*
 * Divide prom con cont y redondea.
 * 
 */
uint32_t div_redondeo(uint32_t prom, int cont)
{
  float res;
  
  cont=(cont==0)?1:cont;/*Consultamos si el contador no este en cero.*/
  
  /*Parte fraccionaria*/   
  res =(((float)prom/cont)-((int)prom/cont));
  /*parte entera*/
  prom = (uint32_t)(prom/cont);

  if (res>0.5) prom++;

  return prom;  

}




/*
 * 
 * name prom_PX
 *   cualcula el promedio de pixeles, dependiendo del bitCount
 *   indicando prom_PX donde X es el bitsCount.
 *   Los siguientes parametros se deriban de promPixels().
 * 
 * 
 * @param mapa_t * - mapa para el calculo
 * @param int - columna
 * @param int - fila
 * @param int - radio
 * @param uint32_t - ancho
 * @param uint32_t - alto
 * 
 * @return uint32_t
 * 
 */

uint32_t prom_P1(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h)
{
   uint32_t result; /*Variable de retorno.*/
   uint32_t prom; /*Variable para calcular el promedio*/
   pixel_1 *inicio;/*Estructuras para referenciar el pixel adecuado.*/
   
   int lc, lf, i_f, i_c,cont, c,f, pos; 

   lc=(col+radio>(w))?(w):col+radio;/*calculmos el limite para columnas.*/
   lf=(fil+radio>(h))?(h):fil+radio;/*calculamos el limite para filas.*/
   i_f=(fil-radio<0)?0:(fil-radio); /*Limite principio filas */
   i_c=(col-radio<0)?0:(col-radio); /*Limite principio columnas*/

   prom =0; /*Variable donde se calculara el promedio*/

   inicio=mapa->map_1;
   
   if (inicio == NULL) return 0; /*Si no existe mapa de bit salimos.*/
   cont=0;
   for(f=i_f;f<lf;f++)/*empezamos el recorrido*/
   {
     for(c=i_c;c<lc;c++)
     {
       pos = c+(f*w); /*Calculamos la posicion dentro del bitmap*/
       prom+=(inicio+pos)->p;/*Incrementamos promedio con el contenido.*/
       cont++;/*Contamos.*/
      }
    }

    result= div_redondeo(prom, cont);/*Calculamos y guardamos el promedio.*/
   
    return result;

}/*Fin prom_P1*/

uint32_t prom_P4(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h)
{
   uint32_t result; /*Variable de retorno.*/
   uint32_t prom; /*Variable para calcular el promedio*/
   pixel_4 *inicio;/*Estructuras para referenciar el pixel adecuado.*/
   int lc, lf, i_f, i_c,cont, c,f, pos; 

   lc=(col+radio>(w))?(w):col+radio;/*calculmos el limite para columnas.*/
   lf=(fil+radio>(h))?(h):fil+radio;/*calculamos el limite para filas.*/
   i_f=(fil-radio<0)?0:(fil-radio); /*Limite principio filas */
   i_c=(col-radio<0)?0:(col-radio); /*Limite principio columnas*/

   inicio=mapa->map_4;
   
   if (inicio == NULL) return 0; /*Si no existe mapa de bit salimos.*/
   cont=0;
   prom =0;
   for(f=i_f;f<lf;f++)/*empezamos el recorrido*/
   {
     for(c=i_c;c<lc;c++)
     {
       pos = c+(f*w); /*Calculamos la posicion dentro del bitmap*/
       prom+=(inicio+pos)->p;/*Incrementamos promedio con el contenido.*/
       cont++;/*Contamos.*/
      }
    }

    result= div_redondeo(prom, cont);/*Calculamos y guardamos el promedio.*/
   
    return result;

}/*Fin prom_P4*/

uint32_t prom_P8(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h)
{
   uint32_t result; /*Variable de retorno.*/
   int lc, lf, i_f, i_c,cont, c,f, pos; 
   uint32_t prom; /*Variable para calcular el promedio*/
   pixel_8 *inicio;/*Estructuras para referenciar el pixel adecuado.*/
  
   lc=(col+radio>(w))?(w):col+radio;/*calculmos el limite para columnas.   */
   lf=(fil+radio>(h))?(h):fil+radio;/*calculamos el limite para filas.*/
   i_f=(fil-radio<0)?0:(fil-radio); /*Limite principio filas */
   i_c=(col-radio<0)?0:(col-radio); /*Limite principio columnas*/

   prom=0; /*Variable donde se calculara el promedio*/

   inicio=mapa->map_8;
   
   if (inicio == NULL) return 0; /*Si no existe mapa de bit salimos.*/
   cont=0;
   for(f=i_f;f<lf;f++)/*empezamos el recorrido*/
   {
     for(c=i_c;c<lc;c++)
     {
       pos = c+(f*w); /*Calculamos la posicion dentro del bitmap*/
       prom+=(inicio+pos)->g;/*Incrementamos promedio con el contenido.*/
       cont++;/*Contamos.*/
      }
    }

    result= div_redondeo(prom, cont);/*Calculamos y guardamos el promedio.*/
   
    return result;
}/*Fin prom_P8*/

uint32_t prom_P16(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h)
{
   uint32_t result; /*Variable de retorno.*/
   uint32_t prom[3]; /*Variable para calcular el promedio*/
   int lc, lf, i_f, i_c,cont, c,f, pos; 
   /*Estructuras para referenciar el pixel adecuado.*/
   pixel_16 *inicio;
   
   lc=(col+radio>(w))?(w):col+radio;/*calculmos el limite para columnas.   */
   lf=(fil+radio>(h))?(h):fil+radio;/*calculamos el limite para filas.*/
   i_f=(fil-radio<0)?0:(fil-radio); /*Limite principio filas */
   i_c=(col-radio<0)?0:(col-radio); /*Limite principio columnas*/

   prom[0]=0;
   prom[1]=0;
   prom[2]=0;



   inicio=mapa->map_16;
   
   if (inicio == NULL) return 0; /*Si no existe mapa de bit salimos.*/
   cont=0;
   for(f=i_f;f<lf;f++)
   {
     for(c=i_c;c<lc;c++)
     {
       pos = c+(f*w); 
       prom[0]+=(inicio+pos)->r;
       prom[1]+=(inicio+pos)->g;
       prom[2]+=(inicio+pos)->b;
       cont++;
      }
    }
    prom[0]= div_redondeo(prom[0], cont);/*Calculamos y guardamos el promedio.*/
    prom[1]= div_redondeo(prom[1], cont);
    prom[2]= div_redondeo(prom[2], cont);

    result = RGB16(prom[0], prom[1], prom[2]);
   
    return result;
}/*Fin prom_P16*/

uint32_t prom_P24(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h)
{
   uint32_t result; /*Variable de retorno.*/
   int lc, lf, i_f, i_c,cont, c,f, pos; 
   uint32_t prom[3]; /*Variable para calcular el promedio*/
   pixel_24 *inicio;/*Estructuras para referenciar el pixel adecuado.*/
  
   lc=(col+radio>(w))?(w):col+radio;/*calculmos el limite para columnas.   */
   lf=(fil+radio>(h))?(h):fil+radio;/*calculamos el limite para filas.*/
   i_f=(fil-radio<0)?0:(fil-radio); /*Limite principio filas*/
   i_c=(col-radio<0)?0:(col-radio); /*Limite principio columnas*/

   prom[0]=0;
   prom[1]=0;
   prom[2]=0;

   inicio=mapa->map_24;
   cont=0;
   if (inicio == NULL) return 0; /*Si no existe mapa de bit salimos.*/
   for(f=i_f;f<lf;f++)
   {
     for(c=i_c;c<lc;c++)
     {
       pos = c+(f*w); 
       prom[0]+=(inicio+pos)->r;
       prom[1]+=(inicio+pos)->g;
       prom[2]+=(inicio+pos)->b;
       cont++;
      }
    }
    prom[0]= div_redondeo(prom[0], cont);/*Calculamos y guardamos el promedio.*/
    prom[1]= div_redondeo(prom[1], cont);
    prom[2]= div_redondeo(prom[2], cont);

    result = RGB(prom[0], prom[1], prom[2]);

    return result;
}/*Fin prom_P24*/

uint32_t prom_P32(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h)
{
   uint32_t result; /*Variable de retorno.*/
   int lc, lf, i_f, i_c,cont, c,f, pos; 
   uint32_t prom[4]; /*Variable para calcular el promedio*/
   pixel_32 *inicio;/*Estructuras para referenciar el pixel adecuado.*/

   lc=(col+radio>(w))?(w):col+radio;/*calculmos el limite para columnas.  */
   lf=(fil+radio>(h))?(h):fil+radio;/*calculamos el limite para filas.*/
   i_f=(fil-radio<0)?0:(fil-radio); /*Limite principio filas */
   i_c=(col-radio<0)?0:(col-radio); /*Limite principio columnas*/

   prom[0]=0;
   prom[1]=0;
   prom[2]=0;
   prom[3]=0;
   inicio=mapa->map_32;
   
   if (inicio == NULL) return 0; /*Si no existe mapa de bit salimos.*/
   cont=0;
            for(f=i_f;f<lf;f++)
            {
              for(c=i_c;c<lc;c++)
              {
                 pos = c+(f*w); 
                 prom[0]+=(inicio+pos)->c;
                 prom[1]+=(inicio+pos)->m;
                 prom[2]+=(inicio+pos)->y;
                 prom[3]+=(inicio+pos)->k;
                 cont++;
               }
            }

    prom[0]= div_redondeo(prom[0], cont);/*Calculamos y guardamos el promedio.*/
    prom[1]= div_redondeo(prom[1], cont);
    prom[2]= div_redondeo(prom[2], cont);
    prom[3]= div_redondeo(prom[3], cont);

    result = CMYK(prom[0], prom[1], prom[2], prom[3]);

    return result;
}/*Fin prom_P32*/

/*
 * Esta funcion ejecuta una funcion de la implementadas anteriormente.
 * 
 */

uint32_t calc_prom(mapa_t *mapa, int col, int fil, int radio, uint32_t w, uint32_t h\
               , uint32_t (*prom)(mapa_t *, int, int, int, uint32_t, uint32_t))
{

   return (prom(mapa, col, fil, radio, w, h));

} /*Fin calc_prom*/

#endif /*Fin BITMAPS_C*/

