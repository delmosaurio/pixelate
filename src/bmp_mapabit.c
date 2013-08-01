/*
 *      bmp_mapabit.c
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
 *      Descripción: Implementacion de las funciones para extraccion y 
 *                   guardado de bitmaps en archivos bmp.
 * 
 */

#include "bmp_mapabit.h"

#ifndef BMP_MAPABIT_C
#define BMP_MAPABIT_C

/*
 * Constante usada para el agrego de bytes en cero,
 * para el relleno (Padding).
 */
const uint8_t P_CERO = 0;

/*
 * 
 * name _BMP_relleno
 *   Calcula el relleno de una fila de un archivo bmp.
 *   El relleno (padding) es utilizado para hacer multiplo de
 *   32 una fila.
 * 
 * @param uint32_t - Ancho de la fila.
 * @param uint16_t - bits por pixel de la imagen.
 * 
 * @return int - Retorana la el padding en Bytes
 * 
 */
int _BMP_relleno(uint32_t width, uint16_t bitCount)
{
  /*Declaramos e inicializamos el contador*/
  int npad=0;
  /*Obtenemos la cantidad de Bytes totales de una fila.*/
  width=width*bitCount;

  /*Mientras no sea multiplo de 32 incrementamos*/
  while((width+npad)%32)
  {
    npad++;
  }

  int res=((float)npad/8-((int)npad/8))*100;
  npad/=8;
  if (res>0) npad++;
  return (npad); /*Retorno en Bytes del padding.*/
}

 /*Prototipo de funciones para extraer el bitmap del archivo BMB*/
void _BMP_extraer_1( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);
void _BMP_extraer_4( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);
void _BMP_extraer_8( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);
void _BMP_extraer_16( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);
void _BMP_extraer_24( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);
void _BMP_extraer_32( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);

 /*Prtotipo para la funcion que ejecuta la funciones de extraccion*/
void _BMP_extraer( FILE * , mapa_t*, uint32_t, uint32_t, uint16_t, void (*) \
                                  (FILE * , mapa_t*, uint32_t, uint32_t, uint16_t));


/*
 * 
 * name _BMP_extraerMapabit
 *   Extrae el mapa de bit del archivo bmp.
 *   Asegurese de haber extraido el encabezado del
 *   bmp anteriormente.
 * 
 * @param FILE* - Archivo bmp del cual se extraera el mapa.
 * @param _BMP_Header- Encabezado del bmp.
 * 
 * @return imagen_mapabit - Retorno de la imagen_mapabit extraida del bmp.
 * 
 */
imagen_mapabit _BMP_extraerMapabit(FILE* archivo, _BMP_Header encabezado)
{

  /*Funcion para ejecutar la extraccion dependiendo del bitCount*/
  void (*func)(FILE * , mapa_t*, uint32_t, uint32_t, uint16_t);

  imagen_mapabit imagen;

  /*Obtenemos los datos de la imagen en el encabezado.
   y los guardamos en la estructura.*/
  uint32_t w=encabezado.infoEncabezado.width;
  uint32_t h=encabezado.infoEncabezado.height;
  uint16_t bc=encabezado.infoEncabezado.bitCount;

  imagen = nueva_imagen(w, h, bc, encabezado.infoEncabezado.colorsUsed); /*Creamos la nueva imagen.*/
   switch(bc)
   {
      case 1:func = _BMP_extraer_1;
             break;
      case 4:func = _BMP_extraer_4;
             break;
      case 8:func = _BMP_extraer_8;
             break;
      case 16:func = _BMP_extraer_16;
              break;
      case 24:func = _BMP_extraer_24;
              break;
      case 32:func = _BMP_extraer_32;
              break;
     }

  int posa=ftell(archivo); /*Guarda la posiocion del archivo*/
  fseek(archivo, encabezado.encabezado.offSet, 0L);/*Se posiciona en el comienzo del bitmap*/

  _BMP_extraer(archivo, &imagen.mapa, w, h , bc, func);

  fseek(archivo, 0L, posa); /*devolvemos el archivo como ingerso.*/
  
  return imagen;

}

/*
 * Implementacion de funciones para extraer el bitmap del archivo BMB
 *  
 * name _BMP_extraer_X
 *   Extracion del mapa bit, donde X indica el bitCount de la imagen.
 * 
 * @param FILE * - Archivo del cual se extraera el mapa.
 * @param mapa_t* - Lugar donde se guardara el mapa.
 * @param uint32_t - ancho de la imagen.
 * @param uint32_t - alto de la imagen.
 * @param uint16_t - bitCount de la imagen.
 * 
 * @return void - utilizada como proceso.
 * 
 */

void _BMP_extraer_1( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc)
{
  int c, f;
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
  /*Catindad de bytes de relleno.
   Esta estructura la utilizaremos como espacio temporal 
   para extraer el relleno (padding), pero este no va a
   utilizado.*/          
  int npad = _BMP_relleno(w, bc);

  
  int col  = ((int)(w/8))+npad;
  uint8_t t[col];
  uint8_t mask;
 
  pixel_1* temp;
  temp=mapa->map_1; 
  /*Obtenemos la direccion de primer elemento, para 
	  comenzar a guardar desde ahi.
    Con las imagenes de un bit por pixel
    necesitamos un lugar donde extraer de
    un bytes en la del archivo.*/
  int i, e;
  for(f=(h-1);f>=0;f--)
  {  
    e=7; 
    mask=0x80;
    fread(&t,col,1,archivo); /*Lee una fila completa incluyendo el padding si es que tiene.*/
    i=0; 
    for(c=0;c<w;c++)
    { 
      pos=(c+(f*w));
      (temp+pos)->p=(t[i]&mask)>>e; /*Obtiene el bit aplicando la mascara.*/
      if (e==0) /*Si recorrimos todo un Bytes, reiniciamos los contadores y mascara, 
                  y incrementamos la columna.*/
      {
        e=7;
        i++;
        mask=0x80;
      }
      else 
      {
        e--;
        mask=mask>>1;
      }
    }
  }

} /*Fin _BMP_extraer_1*/

void _BMP_extraer_4( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc)
{
  int c, f;
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/

  int npad = _BMP_relleno(w, bc);/*Catindad de bytes de relleno.
    Esta estructura la utilizaremos como espacio temporal 
    para extraer el relleno (padding), pero este no va a
    utilizado.*/

  pixel_4* temp;
  
  int col  = ((int)(w/2))+npad;
  uint8_t t[col];
  uint8_t mask;
 
  temp=mapa->map_4; /*Obtenemos la direccion de primer elemento, para 
                      comenzar a guardar desde ahi.*/
  int i, e;
  for(f=(h-1);f>=0;f--)
  {  
    e=4; 
    mask=0xF0;
    fread(&t,col,1,archivo); 
    i=0; 
    for(c=0;c<w;c++)
    { 
       pos=(c+(f*w));
       (temp+pos)->p=(t[i]&mask)>>e; 
       if (e==0) 
       {
         e=4;
         i++;
         mask=0xF0;
       }
       else 
       {
         e-=4;
         mask=mask>>4;
       }
    }
  }
} /*Fin _BMP_extraer_4*/

void _BMP_extraer_8( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc)
{
  int c, f;
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
              
              
  /*Catindad de bytes de relleno.
    Esta estructura la utilizaremos como espacio temporal 
    para extraer el relleno (padding), pero este no va a
    utilizado.*/
  int npad = _BMP_relleno(w, bc);

  uint8_t t_pad[npad];

  pixel_8* temp;

 temp=mapa->map_8;
 for(f=(h-1);f>=0;f--)
 {  
   for(c=0;c<w;c++)
   { 
     pos = c+(f*w); 
     fread((temp+pos),sizeof(pixel_8),1,archivo);
   }
   /*Extraemos el relleno.
     Pero no hacemos nada con el.*/
   if (npad>0) fread(&t_pad,npad,1,archivo);
 }
} /*Fin _BMP_extraer_8*/

void _BMP_extraer_16( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc)
{
  int c, f;
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/

  /*Catindad de bytes de relleno.
    Esta estructura la utilizaremos como espacio temporal 
    para extraer el relleno (padding), pero este no va a
    utilizado.*/
  int npad = _BMP_relleno(w, bc);

  uint8_t t_pad[npad];

  pixel_16* temp;

  temp=mapa->map_16;

  pixel_16 te;
  uint16_t t;

  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      pos = c+(f*w); 
      fread(&t ,2,1,archivo);
      te.r=R16(t);
      te.g=G16(t);
      te.b=B16(t);
      *(temp+pos)=te;
    }
    /*Extraemos el relleno.
      Pero no hacemos nada con el.*/
    if (npad>0) fread(&t_pad,npad,1,archivo);
  }
} /*Fin _BMP_extraer_16*/

void _BMP_extraer_24( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc)
{
  int c, f;
  int pos=0; /*Lugar donde vamos ir calculando
              la posicion del bit map.*/

  
  int npad = _BMP_relleno(w, bc);/*Catindad de bytes de relleno.
    Esta estructura la utilizaremos como espacio temporal 
    para extraer el relleno (padding), pero este no va a
    utilizado.*/
  uint8_t t_pad[npad];
  pixel_24* temp;

  temp=mapa->map_24;
  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      pos = c+(f*w);
      fread((temp+pos),sizeof(pixel_24),1,archivo);
    }
    /*Extraemos el relleno.
      Pero no hacemos nada con el.*/
    if (npad>0) fread(&t_pad,npad,1,archivo);
  }
} /*Fin _BMP_extraer_24*/

void _BMP_extraer_32( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc)
{
  int c, f;
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
        

  pixel_32* temp;
  temp=mapa->map_32;
  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      pos = c+(f*w);
      fread((temp+pos),sizeof(pixel_32),1,archivo);
    }
    /*Nota: En las imagenes de 32 bits no hay relleno,
          ya que las filas siempre son multiplos de 32.*/
  }
} /*Fin _BMP_extraer_32*/


/*Implementacion de la funcion que ejecuta la funciones de extraccion*/
void _BMP_extraer( FILE * archivo, mapa_t* mapa, uint32_t w, uint32_t h, uint16_t bc, void (*extraer) \
                                  (FILE*, mapa_t*, uint32_t, uint32_t, uint16_t))
{
    extraer(archivo, mapa, w, h, bc);
} /*Fin _BMP_extraer*/


 /*Prototipo de funciones para guardar el bitmap del archivo BMB*/

int _BMP_guardar_1( FILE * , mapa_t * ,uint32_t, uint32_t, int);
int _BMP_guardar_4( FILE * , mapa_t * ,uint32_t, uint32_t, int);
int _BMP_guardar_8( FILE * , mapa_t * ,uint32_t, uint32_t, int);
int _BMP_guardar_16( FILE * , mapa_t * ,uint32_t, uint32_t, int);
int _BMP_guardar_24( FILE * , mapa_t * ,uint32_t, uint32_t, int);
int _BMP_guardar_32( FILE * , mapa_t * ,uint32_t, uint32_t, int);

 /*Prototipo para la funcion que ejecuta la funciones de guardado*/
int _BMP_guardar(FILE * , mapa_t *, uint32_t, uint32_t, int, \
                       int (*)(FILE*, mapa_t *, uint32_t, uint32_t, int));



/*
 * 
 * name _BMP_guardarMapabit
 *   Guarda un mapa de bits dentro de un archivo de imagen bmp.
 * 
 * @param FILE* - Archivo donde se guardara la imagen.
 * @param imagen_mapabit* - imagen_mapabit que se guardara
 * @param uint32_t - comienzo en el archivo donde se empieza a guardar
 *                   el mapa, es obtenido del encabezado del bmp.
 * 
 * @return int - Retorna 1 si se realizo la operacion, 0 en caso contrario.
 * 
 */
int  _BMP_guardarMapabit(FILE* archivo, imagen_mapabit* imagen, uint32_t offSet)
{
  int result=0;
  int (*func)(FILE * , mapa_t*, uint32_t, uint32_t, int);

  /*Obtenemos los datos de la imagen en el encabezado.
   y los guardamos en la estructura.*/
  uint32_t w=imagen->width;
  uint32_t h=imagen->height;
  uint16_t bc=imagen->bitCount;

  int npad = _BMP_relleno(w, bc);/*Catindad de bytes de relleno.*/

   switch(bc)
   {
      case 1:func = _BMP_guardar_1;
             break;
      case 4:func = _BMP_guardar_4;
             break;
      case 8:func = _BMP_guardar_8;
             break;
      case 16:func = _BMP_guardar_16;
              break;
      case 24:func = _BMP_guardar_24;
              break;
      case 32:func = _BMP_guardar_32;
              break;
      default: return 0;
     }

  int posa=ftell(archivo); /*Guarda la posiocion del archivo*/
  fseek(archivo, offSet, 0L);/*Se posiciona en el comienzo del bitmap*/

  result = _BMP_guardar(archivo, &imagen->mapa, w, h , npad, func);

  fseek(archivo, 0L, posa); /*devolvemos el archivo como ingerso.*/

  return result;
  
}

 /*Implementacion de funciones para guardar el bitmap del archivo BMB*/

/*
 * 
 * name _BMP_guardar_X
 *   Guarda el mapa bit, donde X es el bitCount de la imagen a guardar.
 * 
 * @param FILE* - Archivo (Debe pasarse el puntero al archivo en la posicion 
 *                        listo para empezar a guardar el mapa bit)
 * @param mapa_t * - ancho de la imagen.
 * @param uint32_t - alto de la imagen.
 * @param uint32_t - Padding para la imagen.
 * 
 * @return int - Retorna 1 si se realizo la operacion, 0 en caso contrario.
 * 
 */

int _BMP_guardar_1( FILE* archivo, mapa_t *mapa,uint32_t w, uint32_t h, int npad)
{

  int pos=0; /*Lugar donde vamos ir calculando
              la posicion del bit map.*/
  int col=  ((int)(w/8))+npad; 
  uint8_t t[col]; 

  pixel_1 *temp=mapa->map_1;

  int i, b ,e, j, c, f;

  for(f=(h-1);f>=0;f--)
  {  
     i=0;j=0;b=0;e=7;
     /*Inicializa el vector.*/
     for(;j<col;j++)
     {
       t[j]=0;
     }
     for(c=0;c<w;c++)
     { 
       pos=c+(f*w);
       t[i] |= (((temp+pos)->p&0x01)<<e); /*Va rellenado un Byte.*/
       b++;
       if (e==0) /*Si ya completo un byte reiniciamos e incrementamos la columna.*/
       {            
         e=7;
       }
       else 
       {
         e--;
       }
       if(b==8) {i++;b=0;}
     } 
     /*Guarda una fila incluyendo el padding si es que hay.*/
     fwrite(&t,col,1,archivo);
  }
  
  return 1;
  
} /*Fin _BMP_guardar_1*/

int _BMP_guardar_4( FILE* archivo, mapa_t *mapa,uint32_t w, uint32_t h, int npad)
{
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/

  int col=  col = ((int)(w/2))+npad;
  uint8_t t[col]; 

  pixel_4 *temp;

  temp=mapa->map_4;

  int i, b ,e, j, c, f;

  temp=mapa->map_4;
  for(f=(h-1);f>=0;f--)
  {  
     i=0;j=0;b=0;e=4;
     /*Inicializa el vector.*/
     for(;j<col;j++)
     {
       t[j]=0;
     }
     for(c=0;c<w;c++)
     { 
       pos=c+(f*w);
       t[i] |= (((temp+pos)->p&0x0F)<<e); /*Va rellenado un Byte.*/
       b++;
       if (e==0) /*Si ya completo un byte reiniciamos e incrementamos la columna.*/
       {
         e=4;
       }
       else 
       {
         e-=4;
       } 
       if(b==2) {i++;b=0;}
     }
     /*Guarda una fila incluyendo el padding si es que hay.*/
     fwrite(&t,col,1,archivo);
  }
  
  return 1;
  
}/*Fin _BMP_guardar_4*/

int _BMP_guardar_8( FILE* archivo, mapa_t *mapa,uint32_t w, uint32_t h, int npad)
{
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
  pixel_8 *temp;

  temp=mapa->map_8;

  int c, f;

  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      pos = c+(f*w);
      fwrite((temp+pos),sizeof(pixel_8),1,archivo);
    }
    /*Guardamos el relleno si que tenemos.*/
    if (npad>0) fwrite(&P_CERO,npad,1,archivo);
  }
  
  return 1;
  
} /*Fin _BMP_guardar_8*/

int _BMP_guardar_16( FILE* archivo, mapa_t *mapa,uint32_t w, uint32_t h, int npad)
{
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
  pixel_16 *temp;

  temp=mapa->map_16;

  int c, f;

  uint16_t t;
  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      t=0;
      pos = c+(f*w);
      t = RGB16( (temp+pos)->r, (temp+pos)->g, (temp+pos)->b );
      fwrite(&t,2,1,archivo);
    }
    /*Guardamos el relleno si que tenemos.*/
    if (npad>0) fwrite(&P_CERO,npad,1,archivo);
  }
  
  return 1;
  
} /*Fin _BMP_guardar_16*/

int _BMP_guardar_24( FILE* archivo, mapa_t *mapa,uint32_t w, uint32_t h, int npad)
{
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
  pixel_24 *temp;

  temp=mapa->map_24;

  int c, f;

  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      pos = c+(f*w);
      fwrite((temp+pos),3,1,archivo);
    }
     /*Guardamos el relleno si que tenemos.*/
    if (npad>0) fwrite(&P_CERO,npad,1,archivo);
  }
  
  return 1;
  
} /*Fin _BMP_guardar_24*/

int _BMP_guardar_32( FILE* archivo, mapa_t *mapa,uint32_t w, uint32_t h, int npad)
{
  int pos=0; /*Lugar donde vamos ir calculando
               la posicion del bit map.*/
  pixel_32 *temp;

  temp=mapa->map_32;

  int c, f;
  for(f=(h-1);f>=0;f--)
  {  
    for(c=0;c<w;c++)
    { 
      pos = c+(f*w);
      fwrite((temp+pos),sizeof(pixel_32),1,archivo);
    }
  }
  
  return 1;
  
} /*Fin _BMP_guardar_32*/

 /*Implementacion para la funcion que ejecuta la funciones de guardado*/
int _BMP_guardar(FILE *archivo, mapa_t *mapa, uint32_t w, uint32_t h, int npad, \
                                   int (*guardar)(FILE*, mapa_t *, uint32_t, uint32_t, int))
{
    return guardar(archivo, mapa, w, h, npad);
}

#endif /*Fin BMP_MAPABIT_C*/
