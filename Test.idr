module Main
import Idrssl
import Network.Socket

createRequest : String -> String
createRequest hostname = "GET / HTTP/1.1\r\nHost: " ++ hostname ++ "\r\n\r\n"

main : IO ()
main = do Right sock <- socket AF_INET Stream 0 | Left err => do putStrLn (show err); pure ()
          hostname <- pure "duckduckgo.com"
          res <- connect sock (Hostname hostname) 443
          if res == -1
          then putStrLn ("couldn't connect to " ++ hostname)
          else do sslInit
                  ctx <- sslCtxNew
                  ssl <- sslNew ctx
                  sslConnect ssl sock
                  req <- pure (createRequest hostname)
                  sslWrite ssl req
                  Right res <- sslRead ssl 1024 | Left err => do putStrLn (show err); sslClose ssl ctx; close sock
                  putStrLn (fst res)
                  sslClose ssl ctx
                  close sock

-- Local Variables:
-- idris-load-packages: ("contrib")
-- End:
