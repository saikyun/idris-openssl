all: idrssl.o

build-test: Test.idr idrssl.o
	idris Test.idr -o test --warnreach --package contrib

idrssl.o: idrssl.c idrssl.h
	gcc -O2 -shared -o idrssl.o idrssl.c -lssl -lcrypto

test: build-test
	./test

clean:
	rm -f test *.o *.ibc
