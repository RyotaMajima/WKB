unset multiplot; reset

set logscale y
set format y "%.1e"
set xlab "E"; set ylab "T"
pl "./output/T.txt" ti "" w l

