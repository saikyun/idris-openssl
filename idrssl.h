#ifndef IDRSSL_H
#define IDRSSL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

typedef struct idrssl_read_result {
  int result;
  void* payload;
} idrssl_read_result;

int idrssl_get_read_res(void* res_struct);
char* idrssl_get_read_payload(void* res_struct);
void idrssl_free_read_struct(void* res_struct);

SSL_CTX *sslCtxNew();
int sslInit();
SSL* sslNew(SSL_CTX *ctx);
int sslConnect(SSL *ssl, int socket);
void sslClose(SSL *ssl, SSL_CTX *ctx);

void sslWrite(SSL *ssl, char* req, int req_len);
void *sslRead(SSL *ssl, int len);

#endif
