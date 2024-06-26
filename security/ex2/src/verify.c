#include <err.h>
#include <stdio.h>
#include <string.h>

#include <openssl/bn.h>

static const char *
read_line(FILE *fp)
{
	char buf[2048];

	if (fgets(buf, sizeof(buf), fp) == NULL)
		err(1, "fgets");
	return (strdup(buf));
}

static void
printbn(char *str, BIGNUM *bn)
{
	char *s;

	s = BN_bn2hex(bn);
	printf("%s%s\n", str, s);
	OPENSSL_free(s);
}

int
main(int argc, char *argv[])
{
	BN_CTX *ctx;
	BIGNUM *e, *n, *sign, *str;
	FILE *fp;

	if (argc < 2) {
		fprintf(stderr, "usage: %s input\n", *argv);
		return (-1);
	}
	if ((fp = fopen(argv[1], "r")) == NULL)
		err(1, "fopen(%s)", argv[1]);

	ctx = BN_CTX_new();
	e = BN_new();
	n = BN_new();
	sign = BN_new();
	str = BN_new();

	BN_hex2bn(&e, read_line(fp));
	BN_hex2bn(&n, read_line(fp));
	BN_hex2bn(&sign, read_line(fp));

	BN_mod_exp(str, sign, e, n, ctx);
	printbn("e: ", e);
	printbn("n: ", n);
	printbn("sign: ", sign);
	printbn("str: ", str);

	fclose(fp);
	OPENSSL_free(e);
	OPENSSL_free(n);
	OPENSSL_free(sign);
	OPENSSL_free(str);
	OPENSSL_free(ctx);

	return (0);
}
