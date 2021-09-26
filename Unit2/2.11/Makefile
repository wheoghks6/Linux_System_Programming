all : frontdesk

frontdesk: frontdesk.o findfree.o getoccupier.o addguest.o freeroom.o
	gcc -o frontdesk frontdesk.o findfree.o getoccupier.o addguest.o freeroom.o

frontdesk.o : hotel.h frontdesk.c
	gcc -c -o frontdesk.o frontdesk.c
	
findfree.o : hotel.h findfree.c
	gcc -c -o findfree.o findfree.c

getoccupier.o : hotel.h getoccupier.c
	gcc -c -o getoccupier.o getoccupier.c

addguest.o : hotel.h addguest.c
	gcc -c -o addguest.o addguest.c

freeroom.o : hotel.h freeroom.c
	gcc -c -o freeroom.o freeroom.c

clean:
	rm *.o frontdesk residents
