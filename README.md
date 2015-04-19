# MIC_OpenMP
Evaluation of Xeon Phi using OpenMP

# Native Xeon Phi Execution
export SINK_LD_LIBRARY_PATH=/software/intel/composer_xe_2015.1.133/compiler/lib/mic
/opt/intel/mic/bin/micnativeloadex ./MIC_OpenMP -a "1 1 1 5"

# Offload Mode Execution
./MIC_OpenMP 1 1 1 5
