CFLAGS = -Wall -Iincludes

all : final

final : main.o dynamic_memory.o
	@@echo "linking all objects"
	gcc $(CFLAGS) main.o dynamic_memory.o
	
main.o: main.c
	@@echo "compiling the main file"
	gcc $(CFLAGS) -c main.c 

dynamic_memory.o: dynamic_memory.c
	@@echo "compiling the dynamic_memory source"
	gcc $(CFLAGS) -c dynamic_memory.c

clean: 
	@@echo "remove all files except headers and sources"
	del *.o *.exe
