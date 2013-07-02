2mm-IBB.c : 2mm.c 2mm.h ../../../IBB
	if ../../../IBB 2mm.c -o 2mm-IBB.c; then echo ''; else echo '';fi
../../../IBB :
	@ cd ../../../multifor-compiler3.3/source; make
2mmmultifor : 2mm-IBB.c 2mm.h
	gcc -O3 -I ../../../utilities -I. ../../../utilities/polybench.c 2mm-IBB.c -DPOLYBENCH_TIME -o 2mmmulti -DSMALL_DATASET
2mm : ../../kernels/2mm/2mm.c 2mm.h
	gcc -O3 -I ../../../utilities -I. ../../../utilities/polybench.c ../../kernels/2mm/2mm.c -DPOLYBENCH_TIME -o 2mm -DSMALL_DATASET
clean:
	rm 2mmmulti 2mm 2mm-IBB.c
test: 2mmmultifor 2mm
	@./2mm 2> __2mm
	@./2mmmulti 2> __2mmulti
	@if diff __2mm __2mmulti > __diff;then echo ' '; fi
	@if ! test -s __diff; then echo Les valeurs en sortie sont les mêmes; else echo Les valeurs en sortie divergent; fi
	@rm __2mm __2mmulti __diff
