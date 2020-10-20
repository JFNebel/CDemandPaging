pagingdemand: pagingdemand.o
	gcc -o pagingdemand pagingdemand.o

pagingdemand.o: pagingdemand.c ./include/pagingdemand.h
	gcc -c pagingdemand.c


.PHONY: clean
clean:
	rm pagingdemand *.o
