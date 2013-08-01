CC = gcc
CFLAGS = -Wall -ansi
LIBS = -lm
TARGET = pixelate
SRC = main.c \
      bitmaps.c\
      bmp_encabezado.c\
      bmp_mapabit.c\
      arg_main.c\
      e_blur.c\
      e_lineas.c\
      e_negativo.c\
      e_redimensionar.c\
      e_rotar.c\
      img.c

OBJ = $(SRC:%.c=%.o)
MANUAL = README help.txt
LICENCIA = GPL.txt GPL-spanish.txt
DESTINO = pixelate-0.5

all : $(TARGET)

$(TARGET) : $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

-include .depend
 .depend: $(SRC) *.h
		$(CC) -MM $(SRC) > .depend

.PHONY: info dist clean
info: $(MANUAL) $(LICENCIA)
dist: $(SRC) *.h $(LICENCIA) $(MANUAL) makefile
		tar -zcf $(DESTINO).tar.gz $^
clean:
		rm -f $(TARGET) $(OBJ) .depend


