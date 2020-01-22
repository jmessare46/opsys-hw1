#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Gets the sum of the word based on it's ascii values
 *
 * @param word The word to get the sum of
 *
 * @return The sum of all of the ascii values of each character in the word
 */
int get_ascii_sum(char * word)
{
    char * temp;
    int sum = 0;

    for (temp = word; *temp != '\0'; temp++) {
        sum += (int) *temp;
    }

    return sum;
}

/**
 * Runs the main function.
 *
 * @param argc The number of arguments passed
 * @param argv An array of all the arguments
 *
 * @return Whether or not the program ran successfully
 */
int main(int argc, char **argv) {
    if(argc != 3)
    {
        fprintf(stderr, "Error: You must provide 2 arguments you provided %d", argc);
        return 1;
    }
    else
    {
        FILE *fp;
        char *filename = *(argv+2);
        char *str = calloc(128, sizeof(char));
        int cache_size = atoi(*(argv+1));
        char **cache = (char**) calloc(cache_size, sizeof(char*));

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
                const char s[2] = " ";
                char *token;
                char *cache_value = NULL;

                /* get the first token */
                token = strtok(str, s);
                cache_value = *(cache + (int)(get_ascii_sum(token) / cache_size));
                if(*cache_value == '0')
                {
                    *(cache + (int)(get_ascii_sum(token) / cache_size)) = calloc(strlen(token), sizeof(char));
                    strcpy(*(cache + (int)(get_ascii_sum(token) / cache_size)), token);
                }
                else
                {
                    realloc(*(cache + (int)(get_ascii_sum(token) / cache_size)), strlen(token) * sizeof(char));
                    strcpy(*(cache + (int)(get_ascii_sum(token) / cache_size)), token);
                }

                /* walk through other tokens */
                while( token != NULL ) {
                    printf( " %s\n", token );

                    token = strtok(NULL, s);
                    if(*cache_value == '0')
                    {
                        *(cache + (int)(get_ascii_sum(token) / cache_size)) = calloc(strlen(token), sizeof(char));
                        strcpy(*(cache + (int)(get_ascii_sum(token) / cache_size)), token);
                    }
                    else
                    {
                        realloc(*(cache + (int)(get_ascii_sum(token) / cache_size)), strlen(token) * sizeof(char));
                        strcpy(*(cache + (int)(get_ascii_sum(token) / cache_size)), token);
                    }
                }

                for(int x = 0; x < cache_size; x++)
                {
                    printf("%s\n", *(cache+x));
                    free(*(cache+x));
                }

                index++;
            }

            fclose(fp);
        }

        free(str);
        free(cache);
        return 0;
    }
}

