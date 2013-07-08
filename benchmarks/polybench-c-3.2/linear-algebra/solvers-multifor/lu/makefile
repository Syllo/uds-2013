lu-IBB.c : lu.c ../../../IBB
	if ../../../IBB lu.c -o lu-IBB.c; then echo ''; else echo '';fi
../../../IBB :
	@ (cd ../../../multifor-compiler3.3/source; make)
lumulti : lu-IBB.c lu.h
	gcc -O3 -D __PRINT -I ../../../utilities -I. ../../../utilities/polybench.c lu-IBB.c -DPOLYBENCH_TIME -DMINI_DATASET -o lumulti
lu : ../../solvers/lu/lu.c lu.h
	gcc -O3 -D __PRINT -I ../../../utilities -I. ../../../utilities/polybench.c ../../solvers/lu/lu.c -DPOLYBENCH_TIME -o lu -DMINI_DATASET
clean:
	rm lumulti lu lu-IBB.c
test:  lumulti lu
	@./lu 2> __lu
	@./lumulti 2> __luulti
	@if diff __lu __luulti > __diff;then echo ' '; fi
	@if ! test -s __diff; then echo Les valeurs en sortie sont les mêmes; else echo Les valeurs en sortie divergent; fi
	@rm __lu __luulti __diff
