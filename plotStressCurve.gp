set terminal pngcairo size 500,300 enhanced font 'Verdana,10'

set output "stress_curve.png"

set xlabel "t/t_B"
set ylabel "S_{xz} d^3/k_B T"

set yrange [0:30]
set xrange [0:0.1]

unset key

plot "output/stress_relaxation/shear_stress_relaxation_data.txt" u 1:2 with lines lw 2
