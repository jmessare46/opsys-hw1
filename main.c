#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

// The main function
int main(int argc, char *argv[]) {
    if(argc != 3)
    {
        fprintf(stderr, "Error: You must provide 2 arguments you provided %d", argc);
        return 1;
    }
    else
    {
        FILE *fp;
        char *filename = argv[2];
        char *str = calloc(128, sizeof(char));
        char **cache = (char**) calloc((unsigned int) argv[1], sizeof(char*));

        fp = fopen(filename, "r");
        if(fp == NULL)
        {
            fprintf(stderr, "Could not open file %s", filename);
            return 1;
        }
        else
        {
            int index = 0;
            while (fgets(str, 128, fp) != NULL)
            {
                cache[index] = (char*) calloc(128, sizeof(char*));
                cache[index] = str;
                printf("%s", cache[index]);
                index++;
            }

            fclose(fp);
        }

        free(str);
        free(cache);
        return 0;
    }
}
