DATASET= -DSTANDARD_DATASET
TIMER=-DPOLYBENCH_TIME
CC= gcc
INCLUDE= -I ../../../utilities
OPTI= -O3 -std=c99
OMP= -fopenmp -lm
ifdef DATAS
DATASET=$$DATAS
endif

3mm-IBB.c : 3mm.c 3mm.h ../../../IBB
	if ../../../IBB 3mm.c -o 3mm-IBB.c; then echo ''; else echo '';fi

3mm2-IBB.c : 3mm2.c 3mm.h ../../../IBB
	if ../../../IBB 3mm2.c -o 3mm2-IBB.c; then echo ''; else echo '';fi

../../../IBB :
	@ cd ../../../multifor-compiler3.3/source; make

3mmmulti : 3mm-IBB.c 3mm.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c 3mm-IBB.c -o 3mmmulti

3mmmulti2 : 3mm2-IBB.c 3mm.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c 3mm2-IBB.c -o 3mmmulti2

3mm : ../../kernels/3mm/3mm.c 3mm.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c ../../kernels/3mm/3mm.c -o 3mm

clean:
	rm 3mmmulti 3mm 3mm.pocc 3mm.openmp 3mmmulti2 #3mm-IBB.c

cleanall :
	rm ./-D*
	make clean

3mm.pocc : 3mm.pocc.c 3mm.h
	$(CC) $(OPTI) $(OMP) $(INCLUDE) $(TIMER) $(DATASET) ../../../utilities/polybench.c 3mm.pocc.c -o 3mm.pocc

3mm.openmp : 3mm.openmp.c 3mm.h
	$(CC) $(INCLUDE) $(OMP) $(OPTI) $(TIMER) $(DATASET) ../../../utilities/polybench.c 3mm.openmp.c -o 3mm.openmp

compile: 3mmmulti 3mm 3mm.pocc 3mm.openmp 3mmmulti2

bench:
	@(for j in -DMINI_DATASET -DSMALL_DATASET -DSTANDARD_DATASET -DLARGE_DATASET ; do \
DATAS=$$j;export DATAS;make clean;make compile;\
for i in `seq 15`; do \
./3mmmulti >> $$DATAS-multi;\
./3mmmulti2 >> $$DATAS-multi2;\
./3mm >> $$DATAS-3mm;\
./3mm.pocc >> $$DATAS-pocc;\
./3mm.openmp >> $$DATAS-openmp;done;done)
