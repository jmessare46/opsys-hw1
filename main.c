#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 3)
    {
        printf("Error: You must provide 2 arguments you provided %d", argc);
        return 0;
    }
    else
    {
        for(int x = 0; x < argc; x++)
        {
            printf("\n%s", argv[x]);
        }
        printf("Hello, World!\n");
        return 0;
    }
}
