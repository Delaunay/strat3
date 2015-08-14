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

set key on
 set key top
# set format x "%.2f"
set output "../gen/graph/distri_ret.tex"
plot "../gen/data/distri_ret.dat" using (percent($1)):(percent($2)) title "EW", '' using (percent($1)):(percent($3)) title "MC1", '' using (percent($1)):(percent($4)) title "MCGBM", '' using (percent($1)):(percent($5)) title "MC4", '' using (percent($1)):(percent($6)) title "MC20"
# ======================
# Loss                  
# ======================

set terminal cairolatex eps size 8.5 cm,6.8 cm 
set key on
 set key left
set output "../gen/graph/loss_distri_ret.tex"
plot "../gen/data/loss_distri_ret.dat" using (percent($1)):(percent($2)) title "EW", '' using (percent($3)):(percent($4)) title "MC1", '' using (percent($5)):(percent($6)) title "MCGBM", '' using (percent($7)):(percent($8)) title "MC4", '' using (percent($9)):(percent($10)) title "MC20"
# ======================
# Gain                  
# ======================

set key on
 set key right
set output "../gen/graph/gain_distri_ret.tex"
plot "../gen/data/gain_distri_ret.dat" using (percent($1)):(percent($2))title "EW", '' using (percent($3)):(percent($4))title "MC1", '' using (percent($5)):(percent($6))title "MCGBM", '' using (percent($7)):(percent($8))title "MC4", '' using (percent($9)):(percent($10))title "MC20"
set xdata time
set timefmt "%Y,%m,%d"
set format x "%Y"
# ======================
# Holding Evolution     
# ======================

set terminal cairolatex eps size 16.59 cm,6.8 cm 
set key on
 set key right
set key off
 unset key

set output "../gen/graph/EW_holding_evol.tex" 
plot "../gen/data/EW_holding_evol.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MC1_holding_evol.tex" 
plot "../gen/data/MC1_holding_evol.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MCGBM_holding_evol.tex" 
plot "../gen/data/MCGBM_holding_evol.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MC4_holding_evol.tex" 
plot "../gen/data/MC4_holding_evol.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MC20_holding_evol.tex" 
plot "../gen/data/MC20_holding_evol.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 
# ======================
# Weight Target         
# ======================

set key on
 set key right
set key off
 unset key

set output "../gen/graph/EW_weight_target.tex" 
plot "../gen/data/EW_weight_target.dat" using 1:(percent($4)) title "AAR-UN.TO", '' using 1:(percent($5)) title "ABX.TO", '' using 1:(percent($6)) title "ACQ.TO", '' using 1:(percent($7)) title "AEM.TO", '' using 1:(percent($8)) title "AGF-B.TO", '' using 1:(percent($9)) title "AQN.TO", '' using 1:(percent($10)) title "AR.TO", '' using 1:(percent($11)) title "ARX.TO", '' using 1:(percent($12)) title "ASR.TO", '' using 1:(percent($13)) title "ATD-B.TO", '' using 1:(percent($14)) title "ATH.TO", '' using 1:(percent($15)) title "AUQ.TO", '' using 1:(percent($16)) title "BAM-A.TO", '' using 1:(percent($17)) title "BB.TO", '' using 1:(percent($18)) title "BBD-B.TO", '' using 1:(percent($19)) title "BCE.TO", '' using 1:(percent($20)) title "BDI.TO", '' using 1:(percent($21)) title "BMO.TO", '' using 1:(percent($22)) title "BNS.TO", '' using 1:(percent($23)) title "BTE.TO", '' using 1:(percent($24)) title "BTO.TO", '' using 1:(percent($25)) title "CCO.TO", '' using 1:(percent($26)) title "CFW.TO", '' using 1:(percent($27)) title "CG.TO", '' using 1:(percent($28)) title "CGG.TO", '' using 1:(percent($29)) title "CM.TO", '' using 1:(percent($30)) title "CNL.TO", '' using 1:(percent($31)) title "CNQ.TO", '' using 1:(percent($32)) title "CNR.TO", '' using 1:(percent($33)) title "COS.TO", '' using 1:(percent($34)) title "CPG.TO", '' using 1:(percent($35)) title "CS.TO", '' using 1:(percent($36)) title "CVE.TO", '' using 1:(percent($37)) title "DC-A.TO", '' using 1:(percent($38)) title "DGC.TO", '' using 1:(percent($39)) title "DHX-B.TO", '' using 1:(percent($40)) title "DPM.TO", '' using 1:(percent($41)) title "ECA.TO", '' using 1:(percent($42)) title "EDV.TO", '' using 1:(percent($43)) title "ELD.TO" 

set output "../gen/graph/MC1_weight_target.tex" 
plot "../gen/data/MC1_weight_target.dat" using 1:(percent($4)) title "AAR-UN.TO", '' using 1:(percent($5)) title "ABX.TO", '' using 1:(percent($6)) title "ACQ.TO", '' using 1:(percent($7)) title "AEM.TO", '' using 1:(percent($8)) title "AGF-B.TO", '' using 1:(percent($9)) title "AQN.TO", '' using 1:(percent($10)) title "AR.TO", '' using 1:(percent($11)) title "ARX.TO", '' using 1:(percent($12)) title "ASR.TO", '' using 1:(percent($13)) title "ATD-B.TO", '' using 1:(percent($14)) title "ATH.TO", '' using 1:(percent($15)) title "AUQ.TO", '' using 1:(percent($16)) title "BAM-A.TO", '' using 1:(percent($17)) title "BB.TO", '' using 1:(percent($18)) title "BBD-B.TO", '' using 1:(percent($19)) title "BCE.TO", '' using 1:(percent($20)) title "BDI.TO", '' using 1:(percent($21)) title "BMO.TO", '' using 1:(percent($22)) title "BNS.TO", '' using 1:(percent($23)) title "BTE.TO", '' using 1:(percent($24)) title "BTO.TO", '' using 1:(percent($25)) title "CCO.TO", '' using 1:(percent($26)) title "CFW.TO", '' using 1:(percent($27)) title "CG.TO", '' using 1:(percent($28)) title "CGG.TO", '' using 1:(percent($29)) title "CM.TO", '' using 1:(percent($30)) title "CNL.TO", '' using 1:(percent($31)) title "CNQ.TO", '' using 1:(percent($32)) title "CNR.TO", '' using 1:(percent($33)) title "COS.TO", '' using 1:(percent($34)) title "CPG.TO", '' using 1:(percent($35)) title "CS.TO", '' using 1:(percent($36)) title "CVE.TO", '' using 1:(percent($37)) title "DC-A.TO", '' using 1:(percent($38)) title "DGC.TO", '' using 1:(percent($39)) title "DHX-B.TO", '' using 1:(percent($40)) title "DPM.TO", '' using 1:(percent($41)) title "ECA.TO", '' using 1:(percent($42)) title "EDV.TO", '' using 1:(percent($43)) title "ELD.TO" 

set output "../gen/graph/MCGBM_weight_target.tex" 
plot "../gen/data/MCGBM_weight_target.dat" using 1:(percent($4)) title "AAR-UN.TO", '' using 1:(percent($5)) title "ABX.TO", '' using 1:(percent($6)) title "ACQ.TO", '' using 1:(percent($7)) title "AEM.TO", '' using 1:(percent($8)) title "AGF-B.TO", '' using 1:(percent($9)) title "AQN.TO", '' using 1:(percent($10)) title "AR.TO", '' using 1:(percent($11)) title "ARX.TO", '' using 1:(percent($12)) title "ASR.TO", '' using 1:(percent($13)) title "ATD-B.TO", '' using 1:(percent($14)) title "ATH.TO", '' using 1:(percent($15)) title "AUQ.TO", '' using 1:(percent($16)) title "BAM-A.TO", '' using 1:(percent($17)) title "BB.TO", '' using 1:(percent($18)) title "BBD-B.TO", '' using 1:(percent($19)) title "BCE.TO", '' using 1:(percent($20)) title "BDI.TO", '' using 1:(percent($21)) title "BMO.TO", '' using 1:(percent($22)) title "BNS.TO", '' using 1:(percent($23)) title "BTE.TO", '' using 1:(percent($24)) title "BTO.TO", '' using 1:(percent($25)) title "CCO.TO", '' using 1:(percent($26)) title "CFW.TO", '' using 1:(percent($27)) title "CG.TO", '' using 1:(percent($28)) title "CGG.TO", '' using 1:(percent($29)) title "CM.TO", '' using 1:(percent($30)) title "CNL.TO", '' using 1:(percent($31)) title "CNQ.TO", '' using 1:(percent($32)) title "CNR.TO", '' using 1:(percent($33)) title "COS.TO", '' using 1:(percent($34)) title "CPG.TO", '' using 1:(percent($35)) title "CS.TO", '' using 1:(percent($36)) title "CVE.TO", '' using 1:(percent($37)) title "DC-A.TO", '' using 1:(percent($38)) title "DGC.TO", '' using 1:(percent($39)) title "DHX-B.TO", '' using 1:(percent($40)) title "DPM.TO", '' using 1:(percent($41)) title "ECA.TO", '' using 1:(percent($42)) title "EDV.TO", '' using 1:(percent($43)) title "ELD.TO" 

set output "../gen/graph/MC4_weight_target.tex" 
plot "../gen/data/MC4_weight_target.dat" using 1:(percent($4)) title "AAR-UN.TO", '' using 1:(percent($5)) title "ABX.TO", '' using 1:(percent($6)) title "ACQ.TO", '' using 1:(percent($7)) title "AEM.TO", '' using 1:(percent($8)) title "AGF-B.TO", '' using 1:(percent($9)) title "AQN.TO", '' using 1:(percent($10)) title "AR.TO", '' using 1:(percent($11)) title "ARX.TO", '' using 1:(percent($12)) title "ASR.TO", '' using 1:(percent($13)) title "ATD-B.TO", '' using 1:(percent($14)) title "ATH.TO", '' using 1:(percent($15)) title "AUQ.TO", '' using 1:(percent($16)) title "BAM-A.TO", '' using 1:(percent($17)) title "BB.TO", '' using 1:(percent($18)) title "BBD-B.TO", '' using 1:(percent($19)) title "BCE.TO", '' using 1:(percent($20)) title "BDI.TO", '' using 1:(percent($21)) title "BMO.TO", '' using 1:(percent($22)) title "BNS.TO", '' using 1:(percent($23)) title "BTE.TO", '' using 1:(percent($24)) title "BTO.TO", '' using 1:(percent($25)) title "CCO.TO", '' using 1:(percent($26)) title "CFW.TO", '' using 1:(percent($27)) title "CG.TO", '' using 1:(percent($28)) title "CGG.TO", '' using 1:(percent($29)) title "CM.TO", '' using 1:(percent($30)) title "CNL.TO", '' using 1:(percent($31)) title "CNQ.TO", '' using 1:(percent($32)) title "CNR.TO", '' using 1:(percent($33)) title "COS.TO", '' using 1:(percent($34)) title "CPG.TO", '' using 1:(percent($35)) title "CS.TO", '' using 1:(percent($36)) title "CVE.TO", '' using 1:(percent($37)) title "DC-A.TO", '' using 1:(percent($38)) title "DGC.TO", '' using 1:(percent($39)) title "DHX-B.TO", '' using 1:(percent($40)) title "DPM.TO", '' using 1:(percent($41)) title "ECA.TO", '' using 1:(percent($42)) title "EDV.TO", '' using 1:(percent($43)) title "ELD.TO" 

set output "../gen/graph/MC20_weight_target.tex" 
plot "../gen/data/MC20_weight_target.dat" using 1:(percent($4)) title "AAR-UN.TO", '' using 1:(percent($5)) title "ABX.TO", '' using 1:(percent($6)) title "ACQ.TO", '' using 1:(percent($7)) title "AEM.TO", '' using 1:(percent($8)) title "AGF-B.TO", '' using 1:(percent($9)) title "AQN.TO", '' using 1:(percent($10)) title "AR.TO", '' using 1:(percent($11)) title "ARX.TO", '' using 1:(percent($12)) title "ASR.TO", '' using 1:(percent($13)) title "ATD-B.TO", '' using 1:(percent($14)) title "ATH.TO", '' using 1:(percent($15)) title "AUQ.TO", '' using 1:(percent($16)) title "BAM-A.TO", '' using 1:(percent($17)) title "BB.TO", '' using 1:(percent($18)) title "BBD-B.TO", '' using 1:(percent($19)) title "BCE.TO", '' using 1:(percent($20)) title "BDI.TO", '' using 1:(percent($21)) title "BMO.TO", '' using 1:(percent($22)) title "BNS.TO", '' using 1:(percent($23)) title "BTE.TO", '' using 1:(percent($24)) title "BTO.TO", '' using 1:(percent($25)) title "CCO.TO", '' using 1:(percent($26)) title "CFW.TO", '' using 1:(percent($27)) title "CG.TO", '' using 1:(percent($28)) title "CGG.TO", '' using 1:(percent($29)) title "CM.TO", '' using 1:(percent($30)) title "CNL.TO", '' using 1:(percent($31)) title "CNQ.TO", '' using 1:(percent($32)) title "CNR.TO", '' using 1:(percent($33)) title "COS.TO", '' using 1:(percent($34)) title "CPG.TO", '' using 1:(percent($35)) title "CS.TO", '' using 1:(percent($36)) title "CVE.TO", '' using 1:(percent($37)) title "DC-A.TO", '' using 1:(percent($38)) title "DGC.TO", '' using 1:(percent($39)) title "DHX-B.TO", '' using 1:(percent($40)) title "DPM.TO", '' using 1:(percent($41)) title "ECA.TO", '' using 1:(percent($42)) title "EDV.TO", '' using 1:(percent($43)) title "ELD.TO" 
# ======================
# Holding var           
# ======================

set key on
 set key right
set key off
 unset key

set output "../gen/graph/EW_holding_var.tex" 
plot "../gen/data/EW_holding_var.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MC1_holding_var.tex" 
plot "../gen/data/MC1_holding_var.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MCGBM_holding_var.tex" 
plot "../gen/data/MCGBM_holding_var.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MC4_holding_var.tex" 
plot "../gen/data/MC4_holding_var.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 

set output "../gen/graph/MC20_holding_var.tex" 
plot "../gen/data/MC20_holding_var.dat" using 1:4 title "AAR-UN.TO", '' using 1:5 title "ABX.TO", '' using 1:6 title "ACQ.TO", '' using 1:7 title "AEM.TO", '' using 1:8 title "AGF-B.TO", '' using 1:9 title "AQN.TO", '' using 1:10 title "AR.TO", '' using 1:11 title "ARX.TO", '' using 1:12 title "ASR.TO", '' using 1:13 title "ATD-B.TO", '' using 1:14 title "ATH.TO", '' using 1:15 title "AUQ.TO", '' using 1:16 title "BAM-A.TO", '' using 1:17 title "BB.TO", '' using 1:18 title "BBD-B.TO", '' using 1:19 title "BCE.TO", '' using 1:20 title "BDI.TO", '' using 1:21 title "BMO.TO", '' using 1:22 title "BNS.TO", '' using 1:23 title "BTE.TO", '' using 1:24 title "BTO.TO", '' using 1:25 title "CCO.TO", '' using 1:26 title "CFW.TO", '' using 1:27 title "CG.TO", '' using 1:28 title "CGG.TO", '' using 1:29 title "CM.TO", '' using 1:30 title "CNL.TO", '' using 1:31 title "CNQ.TO", '' using 1:32 title "CNR.TO", '' using 1:33 title "COS.TO", '' using 1:34 title "CPG.TO", '' using 1:35 title "CS.TO", '' using 1:36 title "CVE.TO", '' using 1:37 title "DC-A.TO", '' using 1:38 title "DGC.TO", '' using 1:39 title "DHX-B.TO", '' using 1:40 title "DPM.TO", '' using 1:41 title "ECA.TO", '' using 1:42 title "EDV.TO", '' using 1:43 title "ELD.TO" 
# ======================
# Portfolio Values      
# ======================

set key on
 set key left 

set output "../gen/graph/EW_values.tex" 
plot "../gen/data/EW_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/MC1_values.tex" 
plot "../gen/data/MC1_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/MCGBM_values.tex" 
plot "../gen/data/MCGBM_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/MC4_values.tex" 
plot "../gen/data/MC4_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 

set output "../gen/graph/MC20_values.tex" 
plot "../gen/data/MC20_values.dat" using 1:4 title "Liabilities", '' using 1:5 title "Equity", '' using 1:6 title "Asset" 


# ======================
# Periodict Ret 
# ======================

set key right
set key on
 set key bottom
set output "../gen/graph/daily_ret.tex"
plot "../gen/data/daily_ret.dat" using 1:(percent($4)) title "EW", '' using 1:(percent($5)) title "MC1", '' using 1:(percent($6)) title "MCGBM", '' using 1:(percent($7)) title "MC4", '' using 1:(percent($8)) title "MC20" 


# ======================
# Holding Period Return 
# ======================

set key on
 set key bottom
set output "../gen/graph/holding_ret.tex" 
plot "../gen/data/hpr_ret.dat" using 1:(percent($4)) title "EW", '' using 1:(percent($5)) title "MC1", '' using 1:(percent($6)) title "MCGBM", '' using 1:(percent($7)) title "MC4", '' using 1:(percent($8)) title "MC20" 
# ======================
# Drawdown              
# ======================

set key on
 set key bottom
set output "../gen/graph/drawdown_ret.tex" 
plot "../gen/data/drawdown_ret.dat" using 1:(percent($4)) title "EW", '' using 1:(percent($5)) title "MC1", '' using 1:(percent($6)) title "MCGBM", '' using 1:(percent($7)) title "MC4", '' using 1:(percent($8)) title "MC20" 
# ======================
# Volatility            
# ======================

set key on
 set key top
set output "../gen/graph/volatility_ret.tex" 
plot "../gen/data/volatility_ret.dat" using 1:(percent($4)) title "EW", '' using 1:(percent($5)) title "MC1", '' using 1:(percent($6)) title "MCGBM", '' using 1:(percent($7)) title "MC4", '' using 1:(percent($8)) title "MC20" 
