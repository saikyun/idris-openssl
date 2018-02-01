# idris-openssl
The beginning of an openssl-wrapper for Idris.

# Features
These are currently implemented:
* Connecting and closing SSL-connections using Network.Sockets to create the sockets
* Reading and writing data

# Dependencies
* idris (https://github.com/idris-lang/Idris-dev/wiki/Installation-Instructions)
* openssl (I used 1.0.2n on OSX installed through homebrew) (https://github.com/openssl/openssl)

# Installation
Clone the library and run the idris install command.
```
git clone git@github.com:Saikyun/idris-openssl.git
cd idris-openssl
idris --install idrssl.ipkg
```

# Usage
Import the lib:
```
import Idrssl
```

Create a Socket using Network.Socket (https://www.idris-lang.org/docs/0.12/contrib_doc/docs/Network.Socket.html)
Run the following functions
where sock is the socket you created.
```
connect sock (Hostname "www.google.com") 443
ctx <- sslCtxNex
ssl <- sslNew ctx
sslConnect ssl sock
sslWrite ssl "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n"
Right msg <- sslRead 1024 | Left err => do sslClose ssl ctx; close sock
sslClose ssl ctx
close sock
```

It's probably easiest to take a look in Test.idr for a working example.

# Test
You can test the library by first compiling the c-files & running the test (Test.idr) which fetches a part of duckduckgo.com:
```
make test
```

# Stuff that's missing
* Docs
* Error handling on most functions
* A higher level lib in the spirit of Sockets: http://docs.idris-lang.org/en/latest/st/examples.html

# Thanks
Thanks to fugu2 and tux3do for providing a compilable ssl client example: https://ubuntuforums.org/showthread.php?t=2217101
