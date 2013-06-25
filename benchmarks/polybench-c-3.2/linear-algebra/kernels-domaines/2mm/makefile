image_gen_view : 2mm.c 2mm.h
	gcc -O3 -I utilities -I../../../utilities/ ../../../utilities/polybench.c 2mm.c -o 2mm_dom -std=gnu99 -Ddom_a -Ddom_b -DMINI_DATASET
	./2mm_dom > hello
	../../../utilities/supdoub
	neato -Tsvg hello -o pic.svg
	rm hello 2mm_dom
	eog pic.svg&

domaine_show : 2mmdomain.c 2mm.h
	gcc -O3 -I utilities -I../../../utilities/ ../../../utilities/polybench.c 2mmdomain.c -o 2mmdomain_dom -std=gnu99 -Ddom_a -Ddom_b -DSMALL_DATASET
	./2mmdomain_dom > hello
	neato -Tsvg hello -o pic.svg
	rm hello 2mmdomain_dom
	eog pic.svg&

clean :
	rm pic.svg
