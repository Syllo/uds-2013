image_gen_view : lu.c lu.h ../../../utilities/polybench.h
	gcc -O3 -I utilities -I../../../utilities/ ../../../utilities/polybench.c lu.c -o lu_dom -std=gnu99 -Ddom_a -Ddom_b -DMINI_DATASET
	./lu_dom > hello
	#../../../utilities/supdoub
	neato -Tsvg hello -o pic.svg
	rm hello lu_dom
	eog pic.svg&

clean :
	rm pic.svg
