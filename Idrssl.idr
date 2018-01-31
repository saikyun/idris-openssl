module Idrssl
import Network.Socket

%include C "idrssl.h"
%link C "idrssl.o"

%access export
      
data ReadStructPtr = RSPtr Ptr

sslCtxNew : IO Ptr
sslCtxNew = foreign FFI_C "sslCtxNew" (IO Ptr)

sslNew : Ptr -> IO Ptr
sslNew ctx = foreign FFI_C "sslNew" (Ptr -> IO Ptr) ctx

sslInit : IO ()
sslInit = foreign FFI_C "sslInit" (IO ())

sslConnect : Ptr -> Socket -> IO Int
sslConnect ssl (MkSocket socket_res _ _ _) =
  foreign FFI_C "sslConnect" (Ptr -> Int -> IO Int) ssl socket_res
  
sslClose : Ptr -> Ptr -> IO ()
sslClose ssl ctx = foreign FFI_C "sslClose" (Ptr -> Ptr -> IO ()) ssl ctx

sslWrite : Ptr -> String -> IO ()
sslWrite ssl req =
  foreign FFI_C "sslWrite" (Ptr -> String -> Int -> IO ())
                           ssl req (cast (length req))

freeReadStruct : ReadStructPtr -> IO ()
freeReadStruct (RSPtr p) = foreign FFI_C "idrssl_free_read_struct" (Ptr -> IO ()) p
             
sslRead : Ptr -> (len : ByteLength) -> IO (Either SocketError (String, ResultCode))
sslRead ssl len =
  do
    read_struct_ptr <- foreign FFI_C "sslRead" (Ptr -> Int -> IO Ptr) ssl len
    read_res        <- foreign FFI_C "idrssl_get_read_res" (Ptr -> IO Int) read_struct_ptr

    if read_res == -1
      then do errno <- getErrno
              freeReadStruct (RSPtr read_struct_ptr)
              pure $ Left errno
      else if read_res == 0
        then do freeReadStruct (RSPtr read_struct_ptr)
                pure $ Left 0
        else do payload <- foreign FFI_C "idrssl_get_read_payload"
                                         (Ptr -> IO String)
                                         read_struct_ptr
                freeReadStruct (RSPtr read_struct_ptr)
                pure $ Right (payload, read_res)

-- Local Variables:
-- idris-load-packages: ("contrib")
-- End:
