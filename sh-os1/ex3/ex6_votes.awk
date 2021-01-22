#!/usr/bin/env -S awk -f

BEGIN {
        # Quit if we don't have an input file.
        if (ARGC != 2) {
                print "usage: ex6_votes.awk votefile";
                exit 1;
        }

        max = 0;
}

{
        cnt = 0;
        # We're testing only against 'y's,
        # no need to check for 'n's.
        for (i = 2; i <= NF; i++)
                if ($i == "y")
                        cnt++;
        if (cnt > max) {
                max = cnt;
                winner = $1;
        }
}

END {
        print "Winner:", winner;
        print "Votes:", max;
}
