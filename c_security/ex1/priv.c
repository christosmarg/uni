#include <stdio.h>
#include <openssl/bn.h>

int
main(int argc, char *argv[])
{
	BN_CTX *ctx;
	BIGNUM *p, *q, *e, *n, *d;

	ctx = BN_CTX_new();
	p = BN_new();
	q = BN_new();
	e = BN_new();
	n = BN_new();
	d = BN_new();
	
	BN_hex2bn(&p, "953AAB9B3F23ED593FBDC690CA10E703");
	BN_hex2bn(&q, "C34EFC7C4C2369164E953553CDF94945");
	BN_hex2bn(&e, "0D88C3");
	BN_mul(n, p, q, ctx);

	/* Calculate private key */

	OPENSSL_free(p);
	OPENSSL_free(q);
	OPENSSL_free(e);
	OPENSSL_free(n);
	OPENSSL_free(q);
	OPENSSL_free(ctx);

	return (0);
}
