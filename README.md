# idris-openssl
The beginning of an openssl-wrapper for Idris.

# Features
These are currently implemented:
* Connecting and closing SSL-connections using Network.Sockets to create the sockets
* Reading and writing data

# Dependencies
* idris (https://github.com/idris-lang/Idris-dev/wiki/Installation-Instructions)
* openssl (I used 1.0.2n on OSX installed through homebrew) (https://github.com/openssl/openssl)

# Test
You can test the library by first compiling the c-files & running the test (Test.idr) which fetches a part of duckduckgo.com:
```
make test
```

# Thanks
Thanks to fugu2 and tux3do for providing a compilable ssl client example: https://ubuntuforums.org/showthread.php?t=2217101
