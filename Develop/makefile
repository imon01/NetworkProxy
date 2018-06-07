OBJ = table.o util.o

exec: $(OBJ)
	cc -o table_exec $(OBJ)

table.o: table.c  table.h 

util.o: util.c util.h 

.PHONY: clean
clean:
	rm -table_exec $(OBJ)
