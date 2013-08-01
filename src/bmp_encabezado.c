/*
 *      bmp_encabezado.c
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
 *      Descripción: Implementacion de la funciones para la manipulacion
 *                   de encabezados de archivos bmp.
 */

#include "bmp_encabezado.h"

#ifndef ENCABEZADO_C
#define ENCABEZADO_C


/*
 * 
 * name _BMP_extraerEncabezado
 *   Extrae un encabezado de un archivo bmp, tambien si
 *   la imagene es con bits por pixels menor o igual a 8
 *   extraera la paleta de colores correspondiente.
 * 
 * @param FILE* - Archivo bmp del cual se extraera el encabezado.
 * 
 * @return _BMP_Header - Encabezado extraido
 * 
 */
_BMP_Header _BMP_extraerEncabezado(FILE* archivo)
{
        
          _BMP_Header encabezado;
          uint32_t colorsUsed;
          int pos=ftell(archivo); /*Guarda la posiocion del archivo*/
          rewind(archivo); /*Se posiciona al principio del archivo.*/

          /*Lee el encabezado y la guarda.*/
          fread(&encabezado.encabezado.type, 2, 1, archivo);
          fread(&encabezado.encabezado.fileSize, 4, 1, archivo);
          fread(&encabezado.encabezado.reserved, 4, 1, archivo);          
          fread(&encabezado.encabezado.offSet, 4, 1, archivo);

          /*Lee la informacion del encabezado y la guarda.*/
          fread(&encabezado.infoEncabezado.size, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.width, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.height, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.planes, 2, 1, archivo);
          fread(&encabezado.infoEncabezado.bitCount, 2, 1, archivo);
          fread(&encabezado.infoEncabezado.compresion, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.imageSize, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.xPixelsPerM, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.yPixelsPerM, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.colorsUsed, 4, 1, archivo);
          fread(&encabezado.infoEncabezado.colorsImportant, 4, 1, archivo);

          colorsUsed = encabezado.infoEncabezado.colorsUsed;

          /*Cuando se trabaja con archivos BMP con bits por pixeles <= 8
            estos acontinuacion continen una tabla de colores, la cual
            indica los colores que esta usara.*/

          switch (encabezado.infoEncabezado.bitCount)
          {
            case 1:{ 
                     int colores=(colorsUsed==0)?2:colorsUsed;
                     encabezado.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                     fread(encabezado.paleta, colores*4, 1, archivo);
                   }
                   break;
            case 4:{
                     int colores=(colorsUsed==0)?16:colorsUsed;
                     encabezado.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                     fread(encabezado.paleta, colores*4, 1, archivo);
                   }
                   break;
            case 8:{
                     int colores=(colorsUsed==0)?256:colorsUsed;
                     encabezado.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                     fread(encabezado.paleta, colores*4, 1, archivo);
                   }
                   break;
            case 16:{
                      int colores=16;
                      encabezado.paleta=(paleta_t*)malloc(colores*sizeof(paleta_t));
                      fread(encabezado.paleta, 16, 1, archivo);
                    }
           }       
          fseek( archivo, 0L, pos); /*Posiciona el archivos en la posiocion en que entro. */
          return encabezado;
}

/*
 * 
 * name _BMP_guardarEncabezado
 *   Guarda un encabezado dentro de un archivo bmp
 *   guardando tabien su paleta si es que tiene.
 * 
 * @param FILE* - 
 * @param _BMP_Header - 
 * 
 * @return int - Retorna 1 si se pudo realizar la operacion 0 en caso contrario
 * 
 */
int _BMP_guardarEncabezado(FILE* archivo, _BMP_Header encabezado)
{
          uint32_t colorsUsed;
  
          rewind(archivo); /*Se posiciona al principio del archivo.*/
          
          /*Guardamos el encabezado.*/
          fwrite(&encabezado.encabezado.type, 2, 1, archivo);
          fwrite(&encabezado.encabezado.fileSize, 4, 1, archivo);
          fwrite(&encabezado.encabezado.reserved, 4, 1, archivo);          
          fwrite(&encabezado.encabezado.offSet, 4, 1, archivo);

          /*Guardamos la informacion del encabezado.*/
          fwrite(&encabezado.infoEncabezado.size, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.width, 4, 1, archivo);        
          fwrite(&encabezado.infoEncabezado.height, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.planes, 2, 1, archivo);
          fwrite(&encabezado.infoEncabezado.bitCount, 2, 1, archivo);
          fwrite(&encabezado.infoEncabezado.compresion, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.imageSize, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.xPixelsPerM, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.yPixelsPerM, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.colorsUsed, 4, 1, archivo);
          fwrite(&encabezado.infoEncabezado.colorsImportant, 4, 1, archivo);
 
          colorsUsed = encabezado.infoEncabezado.colorsUsed;

          /*Como ya comentamos en la funcion "leerEncabezado"
             para los BMPs con bit por pixeles menoero o iguales a 8
             necesitan una tabla.*/

          /*Si estamos en uno de estos guardamos la tabla tambien.*/
          switch (encabezado.infoEncabezado.bitCount)
          {
            case 1:{ 
                     int colores=(colorsUsed==0)?2:colorsUsed;
                     fwrite(encabezado.paleta, colores*4, 1, archivo);
                     return 1;
                   }
            case 4:{
                     int colores=(colorsUsed==0)?16:colorsUsed;
                     fwrite(encabezado.paleta, colores*4, 1, archivo);
                     return 1;
                   }
            case 8:{
                     int colores=(colorsUsed==0)?256:colorsUsed;
                     fwrite(encabezado.paleta, colores*4, 1, archivo);
                     return 1;
                   }
            case 16:{
                      fwrite(encabezado.paleta, 16, 1, archivo);
                      return 1;
                    }
           }
  return 1;
}


/*
 * 
 * name _BMP_imprimirEncabezado
 *   Imprime en pantalla el encabezado de un bmp
 *   imprimiendo tambien su paleta.
 * 
 * @param _BMP_Header - Encabezado a imprimer
 * @param char* - Nombre del archivo.
 * 
 * @return int - Retorna 1 si se pudo realizar la operacion 0 en caso contrario.
 * 
 */
int _BMP_imprimirEncabezado(_BMP_Header encabezado,char* nomArchivo)
{
          printf("\n------------------------------|%s|------------------------------\n", nomArchivo);
          printf("|           Type: %d\n", encabezado.encabezado.type);
          printf("|       fileSize: %.4f Kbytes (%d Bytes)\n", (float)encabezado.encabezado.fileSize/1024, encabezado.encabezado.fileSize);          
          printf("|       Reserved: %d\n", encabezado.encabezado.reserved);
          printf("|         Offset: %d\n", encabezado.encabezado.offSet); 
          printf("|           size: %d\n", encabezado.infoEncabezado.size);
          printf("|      Rsolucion: %dx%d\n", encabezado.infoEncabezado.width, \
                                            encabezado.infoEncabezado.height);
          printf("|         planes: %d\n", encabezado.infoEncabezado.planes);  
          printf("|       bitCount: %d\n", encabezado.infoEncabezado.bitCount);
          printf("|     compresion: %d\n", encabezado.infoEncabezado.compresion);
          printf("|      imageSize: %d Bytes\n", encabezado.infoEncabezado.imageSize);
          printf("|        Pixeles: %dx%d\n", encabezado.infoEncabezado.xPixelsPerM, \
                                               encabezado.infoEncabezado.yPixelsPerM);
          printf("|     colorsUsed: %d\n", encabezado.infoEncabezado.colorsUsed);
          printf("|colorsImportant: %d\n", encabezado.infoEncabezado.colorsImportant);
         
          /*Si estamos en un BMP de bit por pixeles menor o igual a 8
            mostramos la tabla correspondiente.*/
          if (encabezado.infoEncabezado.bitCount<=8)  
           {
            int i;
            paleta_t *inicio;
            printf("________________________________________________________\n");
            printf("| ID Color |   Red    |   Green   |   Blue   |   Hexa   |\n");
            printf("|__________|__________|___________|__________|__________|\n");
             inicio = encabezado.paleta;
             for(i=0;i<encabezado.infoEncabezado.colorsUsed;i++)
             {
                   printf("|%10d|%10d| %10d|%10d| 0x%X%X%X |\n", i+1, \
                          inicio->red, inicio->green, inicio->blue, inicio->red, inicio->green, inicio->blue);
                   inicio++;
             }

           }
          printf("----------------------------------------------------------------------\n\n");
          
    return 1;
}

#endif /*Fin ENCABEZADO_C*/
