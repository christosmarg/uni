#include <stdio.h>

int main(int argc, char **argv)
{
    int intArr[3], maxInt, index;

    printf("Integer 1: ");
    scanf("%d", &intArr[0]);

    printf("Integer 2: ");
    scanf("%d", &intArr[1]);

    printf("Integer 3: ");
    scanf("%d", &intArr[2]);

    maxInt = (intArr[0] > intArr[1]) ? ((intArr[0] > intArr[2]) ? intArr[0] : intArr[2]) : ((intArr[1] > intArr[2]) ? intArr[1] : intArr[2]);

    index = (maxInt == intArr[0]) ? 1 : ((maxInt == intArr[1]) ? 2 : (maxInt == intArr[1]) ? 3 : 4);

    printf("The biggest number is %d in position %d.\n", maxInt, index);

    return 0;
}