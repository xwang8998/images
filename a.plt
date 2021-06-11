plot 'sin1.dat' pt 4
set terminal postscript eps color
set output './a.eps'
replot
set terminal png size 400,300 enhanced font "Helvetica,20"
#set terminal png truecolor 
set output './bb.png'
replot
