DATASET= -DSMALL_DATASET
TIMER=-DPOLYBENCH_TIME -D__PRINT
CC= gcc
INCLUDE= -I ../../utilities
OPTI= -O3 -std=c99
OMP= -fopenmp -lm
ifdef DATAS
DATASET=$$DATAS
endif

floyd-warshall-IBB.c : floyd-warshall.c floyd-warshall.h ../../IBB
	if ../../IBB floyd-warshall.c -o floyd-warshall-IBB.c; then echo ''; else echo '';fi
../../IBB :
	@ cd ../../multifor-compiler3.3/source; make

floyd-warshallmulti : floyd-warshall-IBB.c floyd-warshall.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../utilities/polybench.c floyd-warshall-IBB.c -o floyd-warshallmulti

floyd-warshall : ../floyd-warshall/floyd-warshall.c floyd-warshall.h
	$(CC) $(OPTI) $(INCLUDE) $(TIMER) $(DATASET) ../../utilities/polybench.c ../floyd-warshall/floyd-warshall.c -o floyd-warshall

clean:
	rm floyd-warshallmulti floyd-warshall floyd-warshall.pocc floyd-warshall.openmp # floyd-warshall-IBB.c

cleanall :
	rm ./-D*
	make clean

test : floyd-warshall floyd-warshallmulti
	(./floyd-warshall 2> ll; ./floyd-warshallmulti 2> lll; if ! diff ll lll; then echo "Les données diffèrent"; else echo "Les données sont les mêmes";fi;rm lll ll;make clean;)

floyd-warshall.pocc : floyd-warshall.pocc.c floyd-warshall.h
	$(CC) $(OPTI) $(OMP) $(INCLUDE) $(TIMER) $(DATASET) ../../utilities/polybench.c floyd-warshall.pocc.c -o floyd-warshall.pocc

floyd-warshall.openmp : floyd-warshall.openmp.c floyd-warshall.h
	$(CC) $(INCLUDE) $(OMP) $(OPTI) $(TIMER) $(DATASET) ../../utilities/polybench.c floyd-warshall.openmp.c -o floyd-warshall.openmp

compile: floyd-warshallmulti floyd-warshall floyd-warshall.pocc floyd-warshall.openmp

bench:
	@(for j in -DMINI_DATASET -DSMALL_DATASET -DSTANDARD_DATASET -DLARGE_DATASET -DEXTRALARGE_DATASET; do \
DATAS=$$j;export DATAS;make clean; make compile;\
for i in `seq 15`; do \
./floyd-warshallmulti >> $$DATAS-multi;\
./floyd-warshall >> $$DATAS-floyd-warshall;\
./floyd-warshall.pocc >> $$DATAS-pocc;\
./floyd-warshall.openmp >> $$DATAS-openmp;done;done)
