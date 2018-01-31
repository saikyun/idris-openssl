#include "lule.h"

BIO *outbio2 = NULL;


SSL_CTX *sslCtxNew() {
  SSL_METHOD *method;
  SSL_CTX *ctx;

  method = SSLv23_client_method();
  ctx = SSL_CTX_new(method);
  SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
  return ctx;
}

int sslInit() {
  //    char hostname[] = "ubuntuforums.org";
  char certs[] = "/etc/ssl/certs/ca-certificates.crt";
  
  // added this to test
  // char           dest_url[] = "https://ubuntuforums.org/showthread.php?t=2217101";
  
  outbio2    = BIO_new(BIO_s_file());
  outbio2    = BIO_new_fp(stdout, BIO_NOCLOSE);

  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();

  
  if(SSL_library_init() < 0){
	BIO_printf(outbio2, "Could not initialize the OpenSSL library !\n");
	return -1;
  }
  
  return 0;
}

SSL* sslNew(SSL_CTX *ctx) {
  return SSL_new(ctx);
}

int sslConnect(SSL *ssl, int socket) {
  BIO              *certbio = NULL;
  X509                *cert = NULL;
  X509_NAME       *certname = NULL;

  SSL_set_fd(ssl, socket);
    
  SSL_connect(ssl);

  // try something here
  /* Get the remote certificate into the X509 structure */
  printf("SSL_get_peer_certificate(ssl) \n");
  cert = SSL_get_peer_certificate(ssl);
  if (cert == NULL) {
	printf("Error: Could not get a certificate from: %i.\n", socket);
	return -1;
  } else
	printf("Retrieved the server's certificate from: %i.\n", socket);

  printf("\n");
    
  /* extract various certificate information */
  certname = X509_NAME_new();
  certname = X509_get_subject_name(cert);

  /*  display the cert subject here */
  BIO_printf(outbio2, "Displaying the certificate subject data:\n");
  X509_NAME_print_ex(outbio2, certname, 0, 0);
  BIO_printf(outbio2, "\n\n");

  return 0;
}

void sslWrite(SSL *ssl, char* req, int req_len) {
  SSL_write(ssl, req, req_len);
}

int idrssl_get_read_res(void* res_struct) {
    return (((idrssl_read_result*) res_struct)->result);
}

char* idrssl_get_read_payload(void* res_struct) {
    return (((idrssl_read_result*) res_struct)->payload);
}

void idrssl_free_read_struct(void* res_struct) {
    idrssl_read_result* i_res_struct =
	  (idrssl_read_result*) res_struct;
	
    if (i_res_struct->payload != NULL) {
	  free(i_res_struct->payload);
    }
	
    free(res_struct);
}

void *sslRead(SSL *ssl, int len) {
  idrssl_read_result* res_struct =
	(idrssl_read_result*) malloc(sizeof(idrssl_read_result));
  
  char* buf = malloc(len + 1);
  memset(buf, 0, len + 1);
  int read_res = SSL_read(ssl, buf, len);
  res_struct->result = read_res;

  if (read_res > 0) { // Data was received
	buf[read_res + 1] = 0x00; // Null-term, so Idris can interpret it
  }
  res_struct->payload = buf;
  
  return (void*) res_struct;
  
  /* int bytes; */
  /* char buf[128]; */

  /* memset(buf, '\0', sizeof(buf)); */
  /* bytes = SSL_read(ssl, buf, sizeof(buf)); */
  /* while(bytes > 0){ */
  /* 	write(STDOUT_FILENO, buf, bytes); */
  /* 	memset(buf, '\0', sizeof(buf)); */
  /* 	bytes = SSL_read(ssl, buf, sizeof(buf)); */
  /* } */
}

void sslClose(SSL *ssl, SSL_CTX *ctx) {
  SSL_free(ssl);
  SSL_CTX_free(ctx);
}
