OBJECTS = Friend-List.o main.o

run: $(OBJECTS)
	gcc -o Friend-List $(OBJECTS)

Friend-List.o: Friend-List.c
	gcc -c Friend-List.c

main.o: main.c
	gcc -c main.c

clean:
	rm $(OBJECTS) 
