unset multiplot; reset

#set ter pdfcairo
#set output "T.pdf"

set logscale y
set format y "%.1e"
set grid
set xlab "E"; set ylab "T"
pl "./output/T.txt" ti "" w l lc rgb "black"

set output
set ter pop
