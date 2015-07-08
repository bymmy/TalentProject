reset
clear
set noarrow	
unset multiplot


set encoding iso_8859_15
set term postscript color "time" 24 enhanced
set term post eps
set out 'Diago.eps'

#####################################################################################################

set grid
set xlabel "g"
set ylabel "EigenValues"
set samples 1000
set xrange [-1:1]
set yrange [*:*]


plot  "./diago_out.dat" using 1:2 with lines lt 1 lw 1 lc 1  title "FCI : Exact",\
      "./diago_out.dat" using 1:3 with lines lt 1 lw 1 lc 3  title "CI : Approx",\
      


###########################################################################################################
   

     	      	
    			   
