set terminal cairolatex eps size 16.59 cm,6.8 cm
set datafile separator ','
set style data lines
percent(x) = x * 100.0
set grid
# set format y "%.2f"
set xtics 
# ======================
# Distribution          
# ======================

set key top
# set format x "%.2f"
set output "../gen/graph/distri_ret.tex"
plot "../gen/data/distri_ret.dat" using (percent($1)):(percent($2)) title "Equity", '' using (percent($1)):(percent($3)) title "EW", '' using (percent($1)):(percent($4)) title "Debt", '' using (percent($1)):(percent($5)) title "VarianceMin", '' using (percent($1)):(percent($6)) title "MaxDiv" 
# ======================
# Loss                  
# ======================

set terminal cairolatex eps size 8.5 cm,6.8 cm 
set key left
set output "../gen/graph/loss_distri_ret.tex"
plot "../gen/data/loss_distri_ret.dat" using (percent($1)):(percent($2)) title "Equity", '' using (percent($3)):(percent($4)) title "EW", '' using (percent($5)):(percent($6)) title "Debt", '' using (percent($7)):(percent($8)) title "VarianceMin", '' using (percent($9)):(percent($10)) title "MaxDiv" 
# ======================
# Gain                  
# ======================

set key right
set output "../gen/graph/gain_distri_ret.tex"
plot "../gen/data/gain_distri_ret.dat" using (percent($1)):(percent($2)) title "Equity", '' using (percent($3)):(percent($4)) title "EW", '' using (percent($5)):(percent($6)) title "Debt", '' using (percent($7)):(percent($8)) title "VarianceMin", '' using (percent($9)):(percent($10)) title "MaxDiv" 
set xdata time
set timefmt "%Y,%m,%d"
set format x "%Y"
# ======================
# Holding Evolution     
# ======================

set terminal cairolatex eps size 16.59 cm,6.8 cm 
set key right

set output "../gen/graph/Equity_holding_evol.tex" 
plot "../gen/data/Equity_holding_evol.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/EW_holding_evol.tex" 
plot "../gen/data/EW_holding_evol.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/Debt_holding_evol.tex" 
plot "../gen/data/Debt_holding_evol.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/VarianceMin_holding_evol.tex" 
plot "../gen/data/VarianceMin_holding_evol.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/MaxDiv_holding_evol.tex" 
plot "../gen/data/MaxDiv_holding_evol.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 
# ======================
# Weight Target         
# ======================

set key right

set output "../gen/graph/Equity_weight_target.tex" 
plot "../gen/data/Equity_weight_target.dat" using 1:(percent($4)) title "SPY", '' using 1:(percent($5)) title "XBB" 

set output "../gen/graph/EW_weight_target.tex" 
plot "../gen/data/EW_weight_target.dat" using 1:(percent($4)) title "SPY", '' using 1:(percent($5)) title "XBB" 

set output "../gen/graph/Debt_weight_target.tex" 
plot "../gen/data/Debt_weight_target.dat" using 1:(percent($4)) title "SPY", '' using 1:(percent($5)) title "XBB" 

set output "../gen/graph/VarianceMin_weight_target.tex" 
plot "../gen/data/VarianceMin_weight_target.dat" using 1:(percent($4)) title "SPY", '' using 1:(percent($5)) title "XBB" 

set output "../gen/graph/MaxDiv_weight_target.tex" 
plot "../gen/data/MaxDiv_weight_target.dat" using 1:(percent($4)) title "SPY", '' using 1:(percent($5)) title "XBB" 
# ======================
# Holding var           
# ======================

set key right

set output "../gen/graph/Equity_holding_var.tex" 
plot "../gen/data/Equity_holding_var.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/EW_holding_var.tex" 
plot "../gen/data/EW_holding_var.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/Debt_holding_var.tex" 
plot "../gen/data/Debt_holding_var.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/VarianceMin_holding_var.tex" 
plot "../gen/data/VarianceMin_holding_var.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 

set output "../gen/graph/MaxDiv_holding_var.tex" 
plot "../gen/data/MaxDiv_holding_var.dat" using 1:4 title "SPY", '' using 1:5 title "XBB" 
# ======================
# Portfolio Values      
# ======================

set key left 

set output "../gen/graph/Equity_values.tex" 
plot "../gen/data/Equity_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/EW_values.tex" 
plot "../gen/data/EW_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/Debt_values.tex" 
plot "../gen/data/Debt_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/VarianceMin_values.tex" 
plot "../gen/data/VarianceMin_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/MaxDiv_values.tex" 
plot "../gen/data/MaxDiv_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 


# ======================
# Periodict Ret 
# ======================

set key right
set key bottom
set output "../gen/graph/daily_ret.tex"
plot "../gen/data/daily_ret.dat" using 1:(percent($4)) title "Equity", '' using 1:(percent($5)) title "EW", '' using 1:(percent($6)) title "Debt", '' using 1:(percent($7)) title "VarianceMin", '' using 1:(percent($8)) title "MaxDiv" 


# ======================
# Holding Period Return 
# ======================

set output "../gen/graph/holding_ret.tex" 
plot "../gen/data/hpr_ret.dat" using 1:(percent($4)) title "Equity", '' using 1:(percent($5)) title "EW", '' using 1:(percent($6)) title "Debt", '' using 1:(percent($7)) title "VarianceMin", '' using 1:(percent($8)) title "MaxDiv" 
# ======================
# Drawdown              
# ======================

set key bottom
set output "../gen/graph/drawdown_ret.tex" 
plot "../gen/data/drawdown_ret.dat" using 1:(percent($4)) title "Equity", '' using 1:(percent($5)) title "EW", '' using 1:(percent($6)) title "Debt", '' using 1:(percent($7)) title "VarianceMin", '' using 1:(percent($8)) title "MaxDiv" 
# ======================
# Volatility            
# ======================

set key top
set output "../gen/graph/volatility_ret.tex" 
plot "../gen/data/volatility_ret.dat" using 1:(percent($4)) title "Equity", '' using 1:(percent($5)) title "EW", '' using 1:(percent($6)) title "Debt", '' using 1:(percent($7)) title "VarianceMin", '' using 1:(percent($8)) title "MaxDiv" 
