#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
 * Prints out the contents of the current cache.
 *
 * @param cache The array of cache values
 * @param cache_size The size of the cache to print
 */
void print_cache(char **cache, int cache_size)
{
    for(int x = 0; x < cache_size; x++)
    {
        if(*(cache+x) != NULL)
        {
            fprintf(stdout, "Cache index %d ==> \"%s\"\n", x, *(cache+x));
        }
    }
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
        // Checks to make sure a valid cache size is given
        for(int x = 0; x < strlen(*(argv+1)); x++)
        {
            if(!isdigit(*(*(argv+1)+x)))
            {
                fprintf(stderr, "Error: '%s' is not a valid cache size", *(argv+1));
                return 1;
            }
        }

        setvbuf(stdout, NULL, _IONBF, 0); // Disables buffered output for grading on Submitty

        FILE *fp;
        char c;
        char *filename = *(argv+2);
        char *str = calloc(128, sizeof(char));
        int cache_size = atoi(*(argv+1));
//        printf("Cache Size: %d\n\n", cache_size);

        // Allocates the cache memory
        char **cache = (char**) calloc(cache_size, sizeof(char*));
        char *allocated = (char*) calloc(cache_size, sizeof(char));

        int index = 0;

        fp = fopen(filename, "r");
        if(fp == NULL)
        {
            fprintf(stderr, "Error: Could not open file %s", filename);
            return 1;
        }
        else
        {
            while(!feof(fp))
            {
                c = (char) fgetc(fp);
                if(isalnum(c))
                {
                    *(str + index) = c;
                    index++;
                }
                else
                {
                    if(get_ascii_sum(str) > 0) // Makes sure this is not a blank word
                    {
                        int cache_index = (int) (get_ascii_sum(str) % cache_size);
//                        printf("String: %s \nAscii Val: %i \nCache Index: %d\n\n", str, get_ascii_sum(str), cache_index);

                        if(strlen(str) > 2) // Makes sure a word is longer than 3 characters
                        {
                            if(*(allocated+cache_index) == '1')
                            {
                                *(cache + cache_index) = realloc(*(cache + cache_index), (sizeof(strlen(str)) + 1) * sizeof(char));
                                fprintf(stdout, "Word \"%s\" ==> %d (realloc)\n", str, cache_index);
                            }
                            else
                            {
                                *(cache + cache_index) = calloc(strlen(str) + 1, sizeof(char));
                                fprintf(stdout, "Word \"%s\" ==> %d (calloc)\n", str, cache_index);
                            }

                            strcpy(*(cache + cache_index), str); // Saves the string in the cache
                            *(allocated+cache_index) = '1'; // Saves that the memory section was allocated
                        }

                        free(str); // Frees the temporary string variable
                        str = calloc(128, sizeof(char)); // Resets the string value
                        index = 0;
                    }
                }
            }

            print_cache(cache, cache_size); // Prints out the contents of the cache
        }

        for(int x = 0; x < cache_size; x++)
        {
            if(*(allocated+x) == '1')
            {
                free(*(cache+x));
            }
        }
        fclose(fp);
        free(str);
        free(cache);
        free(allocated);
        return 0;
    }
}

