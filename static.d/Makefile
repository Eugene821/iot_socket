CC = gcc

OBJECT = input.o output.o hi.o
TARGET = hi

$(TARGET):$(OBJECT)
#hi:input.o output.o hi.o
	$(CC) -o $@ $(OBJECT)
#	gcc -o hi 
%.o:%.c
#input.o:input.c
#output.o:output.c
#hi.o:hi.c
	$(CC) -c -o $@ $<
#	gcc -c -o input.o input.c

clean:
	rm -rf *.o $(TARGET)
