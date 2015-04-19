### Basic Makefile for OpenMP

# Offload mode execution
# CC = icc -Wall -openmp -fPIC -wd2568
# Native Phi Execution
CC = icc -mmic -g -Wall -openmp -fPIC  -L /opt/intel/lib/mic -Wno-unknown-pragmas -liomp5
CFLAGS = -g
LDFLAGS =

MIC_OpenMP: MIC_OpenMP.o
        $(CC) $(LDFLAGS) -o MIC_OpenMP MIC_OpenMP.o

MIC_OpenMP.o: MIC_OpenMP.c
        $(CC) $(CFLAGS) -c src/MIC_OpenMP.c src/MatrixMul.c

all:   
        $(CC) $(CFLAGS) -c src/MIC_OpenMP.c src/MatrixMul.c
        $(CC) $(LDFLAGS) -o MIC_OpenMP MIC_OpenMP.o MatrixMul.o

clean: 
        rm -f MIC_OpenMP MIC_OpenMP.o MatrixMul.o
	
