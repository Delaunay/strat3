set terminal cairolatex eps size 16.59 cm,6.8 cm
set datafile separator ' '
set style data lines
percent(x) = x * 100.0
set grid
# set format y "%.2f"
set xtics 
# ======================
# Distribution          
# ======================

set key on
set key top
# set format x "%.2f"
set output "../../gen/graph/distri_ret.tex"
plot "../ret_distri.txt" using (percent($1)):(percent($2)) title "EqualWeighted"
# ======================
# Holding Evolution     
# ======================

set terminal cairolatex eps size 16.59 cm,6.8 cm 
set key on
 set key right

set output "../../gen/graph/EqualWeighted_holding_evol.tex" 
plot "../EqualWeighted_ps.txt" using 1:2 title "Sec0", '' using 1:3 title "Sec1", '' using 1:4 title "Sec2", '' using 1:5 title "Sec3", '' using 1:6 title "Sec4" 
# ======================
# Weight Target         
# ======================

set key on
 set key right

set output "../../gen/graph/EqualWeighted_weight_target.tex" 
plot "../EqualWeighted_tw.txt" using 1:(percent($2)) title "Sec0", '' using 1:(percent($3)) title "Sec1", '' using 1:(percent($4)) title "Sec2", '' using 1:(percent($5)) title "Sec3", '' using 1:(percent($6)) title "Sec4" 
# ======================
# Holding var           
# ======================

set key on
 set key right

set output "../../gen/graph/EqualWeighted_holding_var.tex" 
plot "../EqualWeighted_to.txt" using 1:2 title "Sec0", '' using 1:3 title "Sec1", '' using 1:4 title "Sec2", '' using 1:5 title "Sec3", '' using 1:6 title "Sec4" 
# ======================
# Portfolio Values      
# ======================

set key on
 set key left 

set output "../../gen/graph/EqualWeighted_values.tex" 
plot "../EqualWeighted_pv.txt" using 1:2 title "Liabilities", '' using 1:3 title "Equity", '' using 1:4 title "Asset" 


# ======================
# Periodict Ret 
# ======================

set key right
set key on
 set key bottom
set output "../../gen/graph/daily_ret.tex"
plot "../returns.txt" using (percent($0)) title "EqualWeighted" 


# ======================
# Holding Period Return 
# ======================

set key on
 set key bottom
set output "../../gen/graph/holding_ret.tex" 
plot "../hpr.txt" using (percent($0)) title "EqualWeighted" 
# ======================
# Drawdown              
# ======================

set key on
 set key bottom
set output "../../gen/graph/drawdown_ret.tex" 
plot "../drawdown.txt" using (percent($0)) title "EqualWeighted" 
# ======================
# Volatility            
# ======================

set key on
 set key top
set output "../../gen/graph/volatility_ret.tex" 
plot "../mov_stdev.txt" using (percent($0)) title "EqualWeighted" 
