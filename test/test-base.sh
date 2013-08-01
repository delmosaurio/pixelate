#
# Este archivo shell prueba todos los efectos posibles sobre las imagenes base.
#


img=test-imgs-base/200x150/test-
res=resultado-base/200x150/res
target=./pixelate
ext=bpp.bmp
#ele=	

for i in 1 	8		24
do
  $target -i $img$i$ext -n -o $res$i-n.bmp
#read var
  $target -i $img$i$ext -b 5 -o $res$i-b.bmp
#read var
  $target -i $img$i$ext -x 200 -o $res$i-x200.bmp
#read var
  $target -i $img$i$ext -x 20 -o $res$i-x20.bmp
#read var
  $target -i $ima$i$ext -d -o $res$i-d.bmp
#read var
  $target -i $img$i$ext -f -o $res$i-f.bmp
#read var
  $target -i $img$i$ext -r 90 -o $res$i-r90.bmp
#read var
  $target -i $img$i$ext -r -90 -o $res$i-r-90.bmp
#read var
  $target -i $img$i$ext -r 180 -o $res$i-r180.bmp
#read var
  $target -i $img$i$ext -lv 10 10 2123  -o $res$i-lv.bmp
#read var
  $target -i $img$i$ext -lh 10 10 215113 -o $res$i-lh.bmp
#read var
  $target -i $img$i$ext -lb 10 10  1515615 -o $res$i-lb.bmp
#read var
done

img=test-imgs-base/1000x750/test-
res=resultado-base/1000x750/res
$target=./pixelate
ext=bpp.bmp
#ele=	

for i in 1 	8		24 
do
  $target -i $img$i$ext -n -o $res$i-n.bmp
#read var
  $target -i $img$i$ext -b 5 -o $res$i-b.bmp
#read var
  $target -i $img$i$ext -x 200 -o $res$i-x200.bmp
#read var
  $target -i $img$i$ext -x 20 -o $res$i-x20.bmp
#read var
  $target -i $ima$i$ext -d -o $res$i-d.bmp
#read var
  $target -i $img$i$ext -f -o $res$i-f.bmp
#read var
  $target -i $img$i$ext -r 90 -o $res$i-r90.bmp
#read var
  $target -i $img$i$ext -r -90 -o $res$i-r-90.bmp
#read var
  $target -i $img$i$ext -r 180 -o $res$i-r180.bmp
#read var
  $target -i $img$i$ext -lv 10 10 2123  -o $res$i-lv.bmp
#read var
  $target -i $img$i$ext -lh 10 10 215113 -o $res$i-lh.bmp
#read var
  $target -i $img$i$ext -lb 10 10  1515615 -o $res$i-lb.bmp
#read var
done

echo "Listo."

