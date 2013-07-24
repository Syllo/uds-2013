NOMBRE=5
floyd-warshalldomain : floyd-warshall.c floyd-warshall.h
	for i in `seq $(NOMBRE)`;do gcc -O3 -I utilities -I../../utilities/ ../../utilities/polybench.c floyd-warshall.c -o floyddom$$i -std=gnu99 -DMINI_DATASET -D_K$$i; ./floyddom$$i > hello$$i;neato -Tsvg hello$$i -o pic$$i.svg;rm hello$$i floyddom$$i;eog pic$$i.svg& sleep 2; done

clean :
	for i in `seq $(NOMBRE)`;do rm pic$$i.svg; done
