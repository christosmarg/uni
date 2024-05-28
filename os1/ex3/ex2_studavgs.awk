#!/usr/bin/env -S awk -f

BEGIN {
        # Quit if we don't have an input file.
        if (ARGC < 2) {
                print "usage: ex2_studavgs.awk gradefile";
                exit 1;
        }
}

{
        sum = cnt = 0;
        for (i = 4; i <= NF; i++) {
                sum += $i;
                cnt++;
        }

        # We're calling sort(1) from awk(1).
        print "Student", NR",", $1, $2",", sum / cnt | "sort -Vrk5";
}
