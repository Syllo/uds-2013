image_gen_view : 3mm.c 3mm.h ../../../utilities/polybench.h
	gcc -O3 -I utilities -I../../../utilities/ ../../../utilities/polybench.c 3mm.c -o 3mm_dom -std=gnu99 -Ddom_a -Ddom_b -Ddom_c -DMINI_DATASET
	./3mm_dom > hello
	../../../utilities/supdoub
	neato -Tsvg hello -o pic.svg
	rm hello 3mm_dom
	eog pic.svg&

clean :
	rm pic.svg
