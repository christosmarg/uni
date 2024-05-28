#!/usr/bin/env -S awk -f

BEGIN {
        # Quit if we don't have an input file.
        if (ARGC < 2) {
                print "usage: ex3_courseavgs.awk gradefile";
                exit 1;
        }
}

{
        # Loop from the 4th field onwards and
        # add its value to the sum array.
        for (i = 4; i <= NF; i++)
                sum[i] += $i;
}

END {
        # `NR` is the number of rows in the file, so
        # we divide by that since each column is a
        # course.
        cnt = 1;
        for (i = 4; i <= NF; i++)
                print "Course", cnt++":", sum[i] / NR;
}
