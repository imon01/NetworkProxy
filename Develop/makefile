OBJ = main.o driver.o network.o bsd_sock.o table.o util.o

exec: $(OBJ)
	cc -o main_exec $(OBJ)

main.o: main.c

driver.o: driver.c driver.h

table.o: table.c  table.h 

network.o:	network.c network.h

util.o: util.c util.h 

bsd_sock.o: bsd_sock.c bsd_sock.h

.PHONY: clean
clean:
	rm -table_exec $(OBJ)
