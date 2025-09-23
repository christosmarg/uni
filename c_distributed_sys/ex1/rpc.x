struct arg_arr {
	int	n;
	int	arr<>;
};

struct arg_prod {
	float	a;
	struct arg_arr arr;
};

struct minmax {
	int	arr<2>;
};

struct float_arr {
	float	arr<>;
};

program calc_avg_PROG {
	version calc_avg_VERS {
		float calc_avg(arg_arr) = 1;
	} = 1;
} = 0x20000000;

program calc_minmax_PROG {
	version calc_minmax_VERS {
		struct minmax calc_minmax(arg_arr) = 1;
	} = 1;
} = 0x20000001;

program calc_prod_PROG {
	version calc_prod_VERS {
		struct float_arr calc_prod(arg_prod) = 1;
	} = 1;
} = 0x20000002;
