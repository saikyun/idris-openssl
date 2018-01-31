# idris-openssl
The beginning of an openssl-wrapper for Idris.

# Features
These are currently implemented:
- Connecting and closing SSL-connections using Network.Sockets to create the sockets
- Reading and writing data

# Dependencies
idris (https://github.com/idris-lang/Idris-dev/wiki/Installation-Instructions)
openssl (I used 1.0.2n on OSX installed through homebrew) (https://github.com/openssl/openssl)

# Test
You can try the library out by first compiling the c-files:

```
gcc -shared -o idrssl.o idrssl.c -lssl -lcrypto
```

Then running the main in Test.idr, which will make a http-request to duckduckgo.com

```
idris Test.idr --package contrib -o test && ./test
```
