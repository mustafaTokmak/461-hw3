
#include <stdio.h>

int main()
{
    int i,j;

    char *p = malloc(6 * sizeof(char));
    p[0] = "a";
    p[1] = "b";
    p[2] = "c";
    p[3] = "d";
    p[4] = "e";
    p[5] = "f";


    printf("%c %d\n", p, &i);
    return 0;
}