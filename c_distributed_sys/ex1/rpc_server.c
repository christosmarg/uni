#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "rpc.h"

static void *emalloc(size_t);

static void *
emalloc(size_t nb)
{
	void *p;

	if ((p = malloc(nb)) == NULL)
		err(1, "malloc");
	return (p);
}

float *
calc_avg_1_svc(arg_arr *argp, struct svc_req *rqstp)
{
	static float  result;
	int i, sum;

	for (i = 0, sum = 0; i < argp->n; i++)
		sum += argp->arr.arr_val[i];
	result = sum / (float)argp->n;

	return (&result);
}

struct minmax *
calc_minmax_1_svc(arg_arr *argp, struct svc_req *rqstp)
{
	static struct minmax  result;
	int i, *min, *max;

	result.arr.arr_len = 2;
	result.arr.arr_val = emalloc(2 * sizeof(int));
	min = &result.arr.arr_val[0];
	max = &result.arr.arr_val[1];
	*min = *argp->arr.arr_val;
	*max = *argp->arr.arr_val;
	for (i = 0; i < argp->n; i++) {
		if (argp->arr.arr_val[i] < *min)
			*min = argp->arr.arr_val[i];
		if (argp->arr.arr_val[i] > *max)
			*max = argp->arr.arr_val[i];
	}

	return (&result);
}

struct float_arr *
calc_prod_1_svc(arg_prod *argp, struct svc_req *rqstp)
{
	static struct float_arr  result;
	int i;

	result.arr.arr_len = argp->arr.n;
	result.arr.arr_val = emalloc(argp->arr.n * sizeof(float));
	for (i = 0; i < argp->arr.n; i++)
		result.arr.arr_val[i] = argp->a * argp->arr.arr.arr_val[i];

	return (&result);
}
