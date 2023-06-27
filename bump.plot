set xlabel 'Time'
set ylabel 'Depth'
plot 'log' using 1:2 with lines title 'min (adaptive)','log' using 1:3 with lines title 'max (adaptive)'