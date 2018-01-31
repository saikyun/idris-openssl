#include "idrssl.h"


void fetchHomepage(char *hostname);
void createSocketAndFetchHomePage(char *hostname);
char *createRequest(char *hostname);


int main() {
  createSocketAndFetchHomePage("ubuntuforums.org");
  return 0;
}

void createSocketAndFetchHomePage(char *hostname) {
  SSL *ssl;
  SSL_CTX *ctx;

  int sd;
  struct sockaddr_in addr;
  struct hostent *host;
  int port = 443;

  BIO *outbio = NULL;

  outbio    = BIO_new(BIO_s_file());
  outbio    = BIO_new_fp(stdout, BIO_NOCLOSE);


  
  sd = socket(AF_INET, SOCK_STREAM, 0);

  
  host = gethostbyname(hostname);
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = *(long*)(host->h_addr);

  if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == -1 ) {
	BIO_printf(outbio, "%s: Cannot connect to host [%s] on port %d.\n", hostname, inet_ntoa(addr.sin_addr), port);
  }

  
  
  sslInit();

  ctx = sslCtxNew();
  ssl = sslNew(ctx);

  sslConnect(ssl, sd);
  char* req = createRequest(hostname);
  sslWrite(ssl, req, strlen(req));
  void* test = sslRead(ssl, 1024);
  BIO_printf(outbio, "%s", idrssl_get_read_payload(test));
  idrssl_free_read_struct(test);
  test = sslRead(ssl, 1024);
  BIO_printf(outbio, "%s", idrssl_get_read_payload(test));
  idrssl_free_read_struct(test);
  sslClose(ssl, ctx);
  
  close(sd);
}

char* createRequest(char *hostname) {
  int req_len;
  
  char *req = "GET / HTTP/1.1\r\nHost: ";
  char *end = "\r\n\r\n";

  int newSize = strlen(req) + strlen(hostname) + strlen(end) + 1;
  char *newBuffer = (char *)malloc(newSize);
  strcpy(newBuffer, req);
  strcat(newBuffer, hostname);
  strcat(newBuffer, end);
  
  return newBuffer;
}
