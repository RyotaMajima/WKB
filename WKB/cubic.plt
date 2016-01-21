unset multiplot; reset

#set ter tikz standalone size 10,6
#set output "./cubic.tex"

set ls 1 lc rgb "red"

set xran [-5:5]; set yran [-2:2]
set xlab "$x$"
set zeroaxis

b = 1.0 / 4.0
V(x) = (1.0 / 2) * x**2 - (b / 3) * x**3 - 1 / (6*b**2)

w = 1.0
pl V(x) ti "$V(x)$" ls 1, (1.0 / 2.0)* w**2 * x**2 - 1.0 / (6*b**2)

set output
set ter pop
