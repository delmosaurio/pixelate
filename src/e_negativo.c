/*
 *      e_negativo.c
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
 *      Descripción: Implementacion del las funciones para aplicar el efecto
 *                   negativo en una imagen_mapabit.
 */


#ifndef E_NEGATIVO
#define E_NEGATIVO

#include "e_negativo.h"
/*Prototipo para aplicar efecto negativo a mapabit <=8*/
int negativo_1(paleta_t *, uint32_t);
int negativo_4(paleta_t *, uint32_t);
int negativo_8(paleta_t *, uint32_t);

/*Prototipo para aplicar efecto negativo a mapabit <=8*/
int negativo_p(paleta_t *, uint32_t, int (*)(paleta_t *, uint32_t));


/*Prototipo para aplicar efecto negativo a mapabit >8*/
int negativo_16(mapa_t *, uint32_t, uint32_t);
int negativo_24(mapa_t *, uint32_t, uint32_t);
int negativo_32(mapa_t *, uint32_t, uint32_t);

/*Prototipo para aplicar efecto negativo a mapabit >8*/
int negativo_m(mapa_t *, uint32_t, uint32_t, int (*)(mapa_t *, uint32_t, uint32_t));

/*
 * 
 * name negativo
 *   Crea el efecto negativo en la imagen_mapabit.
 *   Recuerde que se debe pasar la paleta de la misma
 *   para las imagenes bitCount <=8
 * 
 * @param imagen_mapabit** - Imagen  la cual se aplicara el efecto
 * 
 * @return int - Retorna 1 si se logro el efecto, 0 en caso contrario
 * 
 */
int negativo(imagen_mapabit** imagen)
{

  int result;
   /*Funcion para crear el efecto en la paleta
     para las imagenes de bitCount <=8  */
   int (*n_p)(paleta_t *, uint32_t);

   /*Funcion para crear en efecto al mapa bit*/
   int (*n_m)(mapa_t *, uint32_t, uint32_t);

   switch ((*imagen)->bitCount)
   {
       case 1: n_p = negativo_1;
               break;
       case 4: n_p = negativo_4;
               break;
       case 8: n_p = negativo_8;
               break;
       case 16: n_m = negativo_16;
               break;
       case 24: n_m = negativo_24;
               break;
       case 32: n_m = negativo_32;
               break;
       default: return 0;
   }
 
   if ((*imagen)->bitCount<=8)
   {
      result = negativo_p((*imagen)->paleta, (*imagen)->colorsUsed, n_p);

   }
   else
   {
      result = negativo_m( &(*imagen)->mapa, (*imagen)->width, (*imagen)->height, n_m);
         

   }
   
   return result;
   
}

/*
 * Implementacion para aplicar efecto negativo a mapabit <=8
 *  
 * name negativo_X
 *   Crea el efecto negativo para las imagenes de X bitCount
 *   donde X<=8
 * @param paleta_t * - paleta de la imagen.
 * @param uint32_t - Cantidad de colores usados.
 * 
 * @return int - Retorna 1 si se pudo efectuar el efecto, 0 e caso contrario
 * 
 */
int negativo_1(paleta_t *paleta, uint32_t colorsUsed)
{
    int i;
    uint32_t colores;
    
    
    colores=(colorsUsed==0)?2:colorsUsed;
    
    for(i=0;i<colores;i++)
    { 
       (paleta+i)->red = 255-(paleta+i)->red;
       (paleta+i)->green = 255-(paleta+i)->green;
       (paleta+i)->blue = 255-(paleta+i)->blue;

    }

  return 1;

} /*Fin negativo_1*/

int negativo_4(paleta_t *paleta, uint32_t colorsUsed)
{
    int i;

    uint32_t colores;
    colores=(colorsUsed==0)?16:colorsUsed;

    for(i=0;i<colores;i++)
    { 
       (paleta+i)->red = 255-(paleta+i)->red;
       (paleta+i)->green = 255-(paleta+i)->green;
       (paleta+i)->blue = 255-(paleta+i)->blue;
      
    }

  return 1;    

}/*Fin negativo_4*/

int negativo_8(paleta_t *paleta, uint32_t colorsUsed)
{
    int i;

    uint32_t colores;
       
    colores=(colorsUsed==0)?256:colorsUsed;
   
    for(i=0;i<colores;i++)
    { 
       (paleta+i)->red = 255-(paleta+i)->red;
       (paleta+i)->green = 255-(paleta+i)->green;
       (paleta+i)->blue = 255-(paleta+i)->blue;
    }

  return 1;

} /*Fin negativo_8*/

/*Implementacion para aplicar efecto negativo a mapabit <=8*/
int negativo_p(paleta_t *paleta, uint32_t colorsUsed, int (*negativo)(paleta_t *, uint32_t))
{
    return negativo(paleta, colorsUsed);
}/*Fin negativo_p*/





/*
 * Implementacion para aplicar efecto negativo a mapabit >8
 *  
 * name negativo_X
 *   Crea el efecto negativo para las imagenes de X bitCount
 *   donde X>8
 * 
 * @param *mapa - Mapa de la imagen.
 * @param uint32_t - Ancho del mapabit.
 * @param uint32_t - Alto del mapabit.
 * 
 * @return int - Retorna 1 si se pudo efectuar el efecto, 0 e caso contrario
 * 
 */
int negativo_16(mapa_t *mapa, uint32_t w, uint32_t h)
{
 int i;
    
 pixel_16 *inicio;
 inicio = mapa->map_16;
 for(i=0;i<(w*h);i++)
 {  
   (inicio+i)->r = 32-(inicio+i)->r;
   (inicio+i)->g = 64-(inicio+i)->g;
   (inicio+i)->b = 32-(inicio+i)->b;
 }
 return 1;
}/*Fin negativo_16*/

int negativo_24(mapa_t *mapa, uint32_t w, uint32_t h)
{
 int i;
    
   
 pixel_24 *inicio;
 inicio = mapa->map_24;
 for(i=0;i<(w*h);i++)
 { 
         
   (inicio+i)->r = 255-(inicio+i)->r;
   (inicio+i)->g = 255-(inicio+i)->g;
   (inicio+i)->b = 255-(inicio+i)->b;
   
 }
 
 return 1;
 
}/*Fin negativo_24*/

int negativo_32(mapa_t *mapa, uint32_t w, uint32_t h)
{
 int i;

 pixel_32 *inicio;
 inicio = mapa->map_32;
 for(i=0;i<(w*h);i++)
 {  
   (inicio+i)->c = 255-(inicio+i)->c;
   (inicio+i)->m = 255-(inicio+i)->m;
   (inicio+i)->y = 255-(inicio+i)->y;
   /*(inicio+i)->y = 255-(inicio+i)->y; Canal alpha no se modifica.*/

 }

return 1;

}/*Fin negativo_32*/

/*Implementacion para aplicar efecto negativo a mapabit >8*/
int negativo_m(mapa_t *mapa, uint32_t w, uint32_t h, int (*negativo)(mapa_t *, uint32_t, uint32_t))
{
  return negativo(mapa, w, h);
}


#endif /*E_NEGATIVO*/
