build-test: Test.idr idrssl.c idrssl.h
	idris Test.idr -o test --warnreach --package contrib

test: build-test
	./test

clean:
	rm -f test *.o *.ibc
