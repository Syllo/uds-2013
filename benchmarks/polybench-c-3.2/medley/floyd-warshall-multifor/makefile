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
	rm floyd-warshallmulti floyd-warshall

test : floyd-warshall floyd-warshallmulti
	(./floyd-warshall 2> ll; ./floyd-warshallmulti 2> lll; if ! diff ll lll; then echo "Les données diffèrent"; else echo "Les données sont les mêmes";fi;rm lll ll;make clean;)
