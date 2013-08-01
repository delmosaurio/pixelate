/*
 *      e_lineas.c
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
 *      Descripción: Implementacion de las funciones para dibujar lineas
 *                   en una imagen_mapabit.
 */

#include "e_lineas.h"

#ifndef E_LINEAS
#define E_LINEAS


/*Prototipo de la funciones para dibujar lineas*/
int linea_1(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);
int linea_4(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);
int linea_8(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);
int linea_16(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);
int linea_24(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);
int linea_32(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);

/*Prototipo para aplicar la linea.*/
int linea(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char, \
            int (*)(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char));



/*
 * 
 * name dibujarLinea
 *   Dibuja lineas en una imagen_mapabit, esta pueden ser
 *   verticales y/o horizontales.
 *   Esta funcion enrealidad, es la encargada de seleccionar
 *   la funcion correcta para el dibujo de la linea,
 *   dependiendo del bitCount de la imagen.
 *   
 * @param imagen_mapabit** - imagen para dibujar las lineas.
 * @param int - ancho de la linea.
 * @param int - espacio entre linea y linea.
 * 
 *   //Si el color sobrepasa los limites del pixel se tomara
 *   //el menor o el mayor respectivamente.
 * @param uint32_t - color de la linea.
 * @param char - tipo de linea ( 'v'ertical , 'h'orizontal, 'b'oth)
 * 
 * @return int - retorna 1 si se puedo realizar la operacion, 0 en caso contrario
 * 
 */
int dibujarLinea(imagen_mapabit** imagen,int ancho, int espacio, uint32_t color,char tipo)
{
   /*Funcion que se encarga de ejecutar la funcion
    correcta para dibujar las lineas.*/
   int (*func)(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char);

   switch ((*imagen)->bitCount)
   {
       case 1:func = linea_1;
              break;
       case 4:func = linea_4;
              break;
       case 8:func = linea_8;
              break;
       case 16:func = linea_16;
               break;
       case 24:func = linea_24;
               break;
       case 32:func = linea_32;
               break;
      default: return 0;
   }

   return  linea(&(*imagen)->mapa, (*imagen)->width, (*imagen)->height, ancho, espacio, color, tipo, func);
   
} /*Fin dibujarLinea*/

/* 
 * Implementacion de la funciones para dibujar lineas
 * 
 * name linea_X
 *  Funciones para dibujar lineas, donde X indica el bitCount de la imagen.
 * 
 * @param mapa_t * - mapa donde se dibujara la linea.
 * @param uint32_t - ancho del mapa.
 * @param uint32_t - alto del mapa.
 * @param int - ancho de la linea.
 * @param int - espacion entre lineas.
 * @param uint32_t - color de la linea.
 * @param char - tipo de linea. ( 'v'ertical , 'h'orizontal, 'b'oth)
 * 
 * @return - retorna 1 si se puedo realizar la operacion, 0 en caso contrario
 * 
 */

int linea_1(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo)
{
        int i, c, f, pos;
        pixel_1 *temp=mapa->map_1;/*Se el inicio del bitmap.*/
        color=(color>1)?1:color; /*Maximo valor*/

         i=0;

         if (tipo=='h' || tipo=='b')
         {
           for(f=(espacio/2);f<h;f++)
           {
             for(c=0;c<w;c++)
             {
                pos = c+(f*w); 
                (temp+pos)->p = color;
              }
              if (i==ancho) {f+=espacio;i=0;}
              i++;
            }
          }
          if (tipo=='v' || tipo=='b')
          {
            for(c=(espacio/2);c<w;c++)
            {
              for(f=0;f<h;f++)
              {
                 pos = c+(f*w); 
                 (temp+pos)->p = color;
               }
               if (i==ancho) {c+=espacio;i=0;}
               i++;
             }
           }

  return 1;

}/*Fin linea_1*/

int linea_4(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo)
{
         int i, c, f, pos;
         pixel_4 *temp=mapa->map_4;/*Se el inicio del bitmap.*/
   
         color=(color>15)?15:color; /*Maximo valor*/
         i=0;

         if (tipo=='h' || tipo=='b')
         {
           for(f=(espacio/2);f<h;f++)
           {
             for(c=0;c<w;c++)
             {
                pos = c+(f*w); 
                (temp+pos)->p = color;
              }
              if (i==ancho) {f+=espacio;i=0;}
              i++;
            }
          }
          if (tipo=='v' || tipo=='b')
          {
            for(c=(espacio/2);c<w;c++)
            {
              for(f=0;f<h;f++)
              {
                 pos = c+(f*w); 
                 (temp+pos)->p = color;
               }
               if (i==ancho) {c+=espacio;i=0;}
               i++;
             }
           }

  return 1;

}/*Fin linea_4*/

int linea_8(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo)
{
         int i, c, f, pos;
         pixel_8 *temp=mapa->map_8;/*Se el inicio del bitmap.*/
    
         color=(color>255)?255:color; /*Maximo valor*/
         i=0;

         if (tipo=='h' || tipo=='b')
         {
           for(f=(espacio/2);f<h;f++)
           {
             for(c=0;c<w;c++)
             {
                pos = c+(f*w); 
                (temp+pos)->g = color;
               }
              if (i==ancho) {f+=espacio;i=0;}
              i++;
            }
          }
          if (tipo=='v' || tipo=='b')
          {
            for(c=(espacio/2);c<w;c++)
            {
              for(f=0;f<h;f++)
              {
                pos = c+(f*w); 
                 (temp+pos)->g = color;
               }
               if (i==ancho) {c+=espacio;i=0;}
               i++;
             }
           }
           
  return 1;

}/*Fin linea_8*/

int linea_16(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo)
{
         int i, c, f, pos;
         pixel_16 *temp=mapa->map_16;/*Se el inicio del bitmap.*/

         color=(color>65536)?65536:color; /*Maximo valor*/
         i=0;

         if (tipo=='h' || tipo=='b')
         {
           for(f=(espacio/2);f<h;f++)
           {
             for(c=0;c<w;c++)
             {
                pos = c+(f*w); 
                (temp+pos)->r = R16(color);
                (temp+pos)->g = G16(color);
                (temp+pos)->b = B16(color);
                            
              }
              if (i==ancho) {f+=espacio;i=0;}
              i++;
            }
          }
          if (tipo=='v' || tipo=='b')
          {
            for(c=(espacio/2);c<w;c++)
            {
              for(f=0;f<h;f++)
              {
                pos = c+(f*w); 
                 (temp+pos)->r = R16(color);
                 (temp+pos)->g = G16(color);
                 (temp+pos)->b = B16(color);
                             
               }
               if (i==ancho) {c+=espacio;i=0;}
               i++;
             }
           }

  return 1;

}/*Fin linea_16*/

int linea_24(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo)
{
         int i, c, f, pos;
         pixel_24 *temp=mapa->map_24;/*Se el inicio del bitmap.*/
         i=0;
         color=(color>16777216)?16777216:color; /*Maximo valor*/
         if (tipo=='h' || tipo=='b')
         {
           for(f=(espacio/2);f<h;f++)
           {
             for(c=0;c<w;c++)
             {

                pos = c+(f*w); 
                (temp+pos)->r = R(color);
                (temp+pos)->g = G(color);
                (temp+pos)->b = B(color);
                             
              }
              if (i==ancho) {f+=espacio;i=0;}
              i++;
            }
          }
          if (tipo=='v' || tipo=='b')
          {
            for(c=(espacio/2);c<w;c++)
            {
              for(f=0;f<h;f++)
              {
                 pos = c+(f*w); 
                 (temp+pos)->r = R(color);
                 (temp+pos)->g = G(color);
                 (temp+pos)->b = B(color);
               }
               if (i==ancho) {c+=espacio;i=0;}
               i++;
             }
           }
   return 1;

}/*Fin linea_24*/

int linea_32(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo)
{
         int i, c, f, pos;
         pixel_32 *temp=mapa->map_32;/*Se el inicio del bitmap.*/
    
         i=0;

         if (tipo=='h' || tipo=='b')
         {
           for(f=(espacio/2);f<h;f++)
           {
             for(c=0;c<w;c++)
             {
                pos = c+(f*w); 
                (temp+pos)->c = C(color);
                (temp+pos)->m = M(color);
                (temp+pos)->y = Y(color);
                (temp+pos)->k = K(color);
  
              }
              if (i==ancho) {f+=espacio;i=0;}
              i++;
            }
          }
          if (tipo=='v' || tipo=='b')
          {
            for(c=(espacio/2);c<w;c++)
            {
              for(f=0;f<h;f++)
              {
                pos = c+(f*w); 
                 (temp+pos)->c = C(color);
                 (temp+pos)->m = M(color);
                 (temp+pos)->y = Y(color);
                 (temp+pos)->k = K(color);
                               
               }
               if (i==ancho) {c+=espacio;i=0;}
               i++;
             }
           }
   return 1;
}/*Fin linea_32*/

/*Implementacion de la funcion para ejecutar la funcion adecuada para el dibujo de lineas.*/
int linea(mapa_t *mapa, uint32_t w, uint32_t h, int ancho, int espacio, uint32_t color, char tipo, \
            int (*linea)(mapa_t *, uint32_t, uint32_t, int, int, uint32_t, char))
{
   return linea(mapa, w, h, ancho, espacio, color, tipo);
}/*Fin linea*/


#endif /*E_LINEAS*/
