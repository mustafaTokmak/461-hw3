
#include <stdio.h>

int main()
{
    char *str;

    /* Initial memory allocation */
    str = (char *) malloc(15);
    strcpy(str, "tutorialspoint");
    char** a = str;
    printf("Address = %d\n",a); 
    printf("String = %s\n",a);
    
    printf("String = %s,  Address = %d\n", str, str);





    return 0;
}