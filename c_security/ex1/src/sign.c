#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
	BIGNUM *e, *n, *d, *c, *str, *sign;
	FILE *fp;
	int len = 0;
	char buf[2048];

	if (argc < 2) {
		fprintf(stderr, "usage: %s input\n", *argv);
		return (-1);
	}
	if ((fp = fopen(argv[1], "r")) == NULL)
		err(1, "fopen(%s)", argv[1]);

	/* Read string from stdin */
	while (read(STDIN_FILENO, &buf[len++], 1) > 0)
		;
	buf[--len] = '\0';

	ctx = BN_CTX_new();
	e = BN_new();
	n = BN_new();
	d = BN_new();
	c = BN_new();
	str = BN_new();
	sign = BN_new();

	BN_hex2bn(&e, read_line(fp));
	BN_hex2bn(&n, read_line(fp));
	BN_hex2bn(&d, read_line(fp));

	BN_hex2bn(&str, buf);
	BN_mod_exp(sign, str, d, n, ctx);
	printbn("", sign);
	
	fclose(fp);
	OPENSSL_free(e);
	OPENSSL_free(n);
	OPENSSL_free(d);
	OPENSSL_free(c);
	OPENSSL_free(str);
	OPENSSL_free(sign);
	OPENSSL_free(ctx);

	return (0);
}
