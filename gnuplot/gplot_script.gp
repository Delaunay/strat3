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
plot "../ret_distri.txt" using (percent($1)):(percent($3)) title "EqualWeighted"
set xdata time
set timefmt "%Y %m %d"
set format x "%Y"
# ======================
# Holding Evolution     
# ======================

set terminal cairolatex eps size 16.59 cm,6.8 cm 
set key on
 set key right

set output "../../gen/graph/EqualWeighted_holding_evol.tex" 
plot "../EqualWeighted_ps.txt" using 1:4 title "XBB", '' using 1:5 title "SPY" 
# ======================
# Weight Target         
# ======================

set key on
 set key right

set output "../../gen/graph/EqualWeighted_weight_target.tex" 
plot "../EqualWeighted_tw.txt" using 1:(percent($4)) title "XBB", '' using 1:(percent($5)) title "SPY" 
# ======================
# Holding var           
# ======================

set key on
 set key right

set output "../../gen/graph/EqualWeighted_holding_var.tex" 
plot "../EqualWeighted_toNormalized.txt" using 1:4 title "XBB", '' using 1:5 title "SPY" 
# ======================
# Portfolio Values      
# ======================

set key on
 set key left 

set output "../../gen/graph/EqualWeighted_values.tex" 
plot "../EqualWeighted_pv.txt" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 


# ======================
# Periodict Ret 
# ======================

set key right
set key on
 set key bottom
set output "../../gen/graph/daily_ret.tex"
plot "../returns.txt" using 1:(percent($4)) title "EqualWeighted" 


# ======================
# Holding Period Return 
# ======================

set key on
 set key bottom
set output "../../gen/graph/holding_ret.tex" 
plot "../hpr.txt" using 1:(percent($4)) title "EqualWeighted" 
# ======================
# Drawdown              
# ======================

set key on
 set key bottom
set output "../../gen/graph/drawdown_ret.tex" 
plot "../drawdown.txt" using 1:(percent($4)) title "EqualWeighted" 
# ======================
# Volatility            
# ======================

set key on
 set key top
set output "../../gen/graph/volatility_ret.tex" 
plot "../mov_stdev.txt" using 1:(percent($4)) title "EqualWeighted" 
