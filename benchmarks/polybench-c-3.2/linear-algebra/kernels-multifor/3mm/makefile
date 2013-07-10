3mm-IBB.c: 3mm.c 3mm.h ../../../IBB
	if ../../../IBB 3mm.c -o 3mm-IBB.c; then echo ''; fi
../../../IBB :
	@ (cd ../../../multifor-compiler3.3/source; make)
3mmmulti : 3mm-IBB.c 3mm.h
	gcc -std=c99 -Wall -g -I ../../../utilities -I. ../../../utilities/polybench.c 3mm-IBB.c -DPOLYBENCH_TIME -o 3mmmulti -DSMALL_DATASET -D __PRINT
3mm : ../../kernels/3mm/3mm.c 3mm.h
	gcc -std=c99 -Wall -g -I ../../../utilities -I. ../../../utilities/polybench.c ../../kernels/3mm/3mm.c -DPOLYBENCH_TIME -o 3mm -DSMALL_DATASET -D __PRINT
clean:
	rm 3mmmulti 3mm 3mm-IBB.c
test: 3mmmulti 3mm
	@./3mm 2> __3mm
	@./3mmmulti 2> __3mmulti
	@if diff __3mm __3mmulti > __diff; then echo '';fi
	@if ! test -s __diff; then echo Les valeurs en sortie sont les mêmes; else echo Les valeurs en sortie divergent; fi
	@rm __3mm __3mmulti #__diff
