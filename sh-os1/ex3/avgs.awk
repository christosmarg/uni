#!/usr/bin/env -S awk -f

BEGIN {
        if (ARGC < 2) {
                print "usage: avgs.awk grades"
                exit 1
        }
}

{
        sum = cnt = 0;
        for (i = 4; i <= NF; i++) {
                sum += $i;
                cnt++;
        }
        print "Student", NR",", $1, $2",", sum / cnt
}
