SANIT=-fsanitize=address,undefined
ALLSRC=src/createadmin.c src/destruiradmin.c src/memasign.c src/nuevadir.c src/reasignar.c src/desfragmentar.c src/liberar.c src/mostrarestado.c
ALLOBJ=obj/createadmin.o obj/destruiradmin.o obj/memasign.o obj/nuevadir.o obj/reasignar.o obj/desfragmentar.o obj/liberar.o obj/mostrarestado.o
FLAGS=gcc -Wall -I include/ -c

ALL: lib/libmadmin.a lib/libmadmind.so

lib/libmadmin.a: $(ALLOBJ)
	ar rcs $@ $^

lib/libmadmind.so: $(ALLSRC)
	gcc -fPIC -I include/ -shared $^ -o $@


obj/createadmin.o: src/createadmin.c
	$(FLAGS) $^ -o $@

obj/destruiradmin.o: src/destruiradmin.c
	$(FLAGS) $^ -o $@

obj/memasign.o: src/memasign.c
	$(FLAGS) $^ -o $@

obj/nuevadir.o: src/nuevadir.c
	$(FLAGS) $^ -o $@

obj/reasignar.o: src/reasignar.c
	$(FLAGS) $^ -o $@

obj/desfragmentar.o: src/desfragmentar.c
	$(FLAGS) $^ -o $@

obj/liberar.o: src/liberar.c
	$(FLAGS) $^ -o $@

obj/mostrarestado.o: src/mostrarestado.c
	$(FLAGS) $^ -o $@

obj/createadmin.o: src/createadmin.c
	$(FLAGS) $^ -o $@
