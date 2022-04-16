#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <openssl/bn.h>

static char *argv0;

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

static void
usage(void)
{
	fprintf(stderr, "usage: %s [-v] input\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	BN_CTX *ctx;
	BIGNUM *p, *q, *e, *n, *d;
	BIGNUM *phi, *one, *foo, *bar;
	FILE *fp;
	int verbose = 0;
	char ch;

	argv0 = *argv;

	while ((ch = getopt(argc, argv, "v")) != -1) {
		switch (ch) {
		case 'v':
			verbose = 1;
			break;
		case '?': /* FALLTHROUGH */
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (!argc)
		usage();
	if ((fp = fopen(*argv, "r")) == NULL)
		err(1, "fopen(%s)", *argv);

	ctx = BN_CTX_new();
	p = BN_new();
	q = BN_new();
	e = BN_new();
	n = BN_new();
	d = BN_new();

	phi = BN_new();
	one = BN_new();
	foo = BN_new();
	bar = BN_new();
	
	/* We assume the file has at least 3 lines */
	BN_hex2bn(&p, read_line(fp));
	BN_hex2bn(&q, read_line(fp));
	BN_hex2bn(&e, read_line(fp));
	BN_mul(n, p, q, ctx);

	/* 
	 * Calculate private key:
	 * 1. phi(n) = (p-1) * (q-1)
	 * 2. (e * d mod phi(n) = 1), solve for d
	 */
	BN_dec2bn(&one, "1");
	BN_sub(foo, p, one);
	BN_sub(bar, q, one);
	BN_mul(phi, foo, bar, ctx);
	BN_mod_inverse(d, e, phi, ctx);

	if (verbose) {
		printbn("e: ", e);
		printbn("n: ", n);
		printbn("d: ", d);
	} else
		printbn("", d);

	fclose(fp);
	OPENSSL_free(p);
	OPENSSL_free(q);
	OPENSSL_free(e);
	OPENSSL_free(n);
	OPENSSL_free(q);
	OPENSSL_free(phi);
	OPENSSL_free(one);
	OPENSSL_free(foo);
	OPENSSL_free(bar);
	OPENSSL_free(ctx);

	return (0);
}
