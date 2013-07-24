DATASET= -DLARGE_DATASET
TIMER=-DPOLYBENCH_TIME
CC= gcc
INCLUDE= -I ../../../utilities
OPTI= -O3
OMP= -fopenmp -lm
ifdef DATAS
DATASET=$$DATAS
endif

#2mm-IBB.c : 2mm.c 2mm.h ../../../IBB
#	if ../../../IBB 2mm.c -o 2mm-IBB.c; then echo ''; else echo '';fi
#../../../IBB :
#	@ cd ../../../multifor-compiler3.3/source; make

2mmmulti : 2mm-IBB.c 2mm.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c 2mm-IBB.c -o 2mmmulti

2mm : ../../kernels/2mm/2mm.c 2mm.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c ../../kernels/2mm/2mm.c -o 2mm

clean:
	rm 2mmmulti 2mm 2mm.pocc 2mm.openmp # 2mm-IBB.c

cleanall :
	rm ./-D*
	make clean

2mm.pocc : 2mm.pocc.c 2mm.h
	$(CC) $(OPTI) $(OMP) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c 2mm.pocc.c -o 2mm.pocc

2mm.openmp : 2mm.openmp.c 2mm.h
	$(CC) $(INCLUDE) $(OMP) $(OPTI) $(TIMER) $(DATASET) ../../../utilities/polybench.c 2mm.openmp.c -o 2mm.openmp

compile: 2mmmulti 2mm 2mm.pocc 2mm.openmp

bench:
	@(for j in -DMINI_DATASET -DSMALL_DATASET -DSTANDARD_DATASET -DLARGE_DATASET -DEXTRALARGE_DATASET; do \
DATAS=$$j;export DATAS;make clean; make compile;\
for i in `seq 15`; do \
./2mmmulti >> $$DATAS-multi;\
./2mm >> $$DATAS-2mm;\
./2mm.pocc >> $$DATAS-pocc;\
./2mm.openmp >> $$DATAS-openmp;done;done)
