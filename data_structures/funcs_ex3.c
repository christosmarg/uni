#include <stdio.h>
#include <string.h>

/* 
 * Read 2 strings. If they are the same replace all a's with
 * b's, otherwise concatenate them using a third string.
 */

int
main(int argc, char *argv[])
{
        char str1[64], str2[64], str3[64] = {0};
        int i = 0;

        printf("str1: ");
        fgets(str1, 64, stdin);
        printf("str2: ");
        fgets(str2, 64, stdin);

        if (!strcmp(str1, str2)) {
                for (; i < strlen(str1); i++)
                        if (str1[i] == 'a')
                                str1[i] = 'b';
        } else {
                strcpy(str3, str1);
                strcat(str3, str2);
        }

        printf("str1: %sstr2: %sstr3: %s\n", str1, str2, str3);

        return 0;
}
