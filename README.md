# MIC_OpenMP
Evaluation of Xeon Phi using OpenMP

# Native Xeon Phi Execution
/opt/intel/mic/bin/micnativeloadex ./MIC_OpenMP -a "1 1 1 5"

# Offload Mode Execution
./MIC_OpenMP 1 1 1 5
