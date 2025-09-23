#!/usr/bin/env -S awk -f

BEGIN {
        # Quit if we don't have an input file.
        if (ARGC < 2) {
                print "usage: ex4_rev.awk file";
                exit 1;
        }
}

{
        # Add all lines to an array.
        ln[NR] = $0;
}

END {
        # Print them in reverse.
        for (i = NR; i >= 1; i--)
                print ln[i];
}
