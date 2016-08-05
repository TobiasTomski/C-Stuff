#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <netcdf.h>

#define function(a)( sizeof(a)/sizeof(a[0]))

void read_stations(char** []);
char ** str_split(char*, const char);

int main()
{
    char **stations[450];
    read_stations(stations);
    int i;
    for(i = 0; i < 450; i++)
    {
        //printf("%s\n", *(stations+0));
        char **station = stations[i];
        int idx;
        for(idx = 0; *(station + idx); idx++)
        {
            printf("%s\n", *(station + idx));
        }

    }
}

void read_stations(char** stations[])
{
    char **station;
    int stat_num = 0;
    /* char ***stations; */
    FILE *fp;
    fp = fopen("/home/t.tomski/C-Stuff/test.txt", "r");
    if(fp!=NULL)
    {
        char line[1000];
        while(fgets(line, sizeof(line), fp) != NULL)
        {
            station = str_split(line, ',');
            if(station)
            {
                stations[stat_num++] = station;
                //printf("%d\n", stations[stat_num - 1]);
            }
        }
    }
    fclose(fp);
}

char** str_split(char* a_str, const char a_delim)
{
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    while(*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    count += last_comma < (a_str + strlen(a_str) - 1);
    count++;

    result = malloc(sizeof(char*) * count);

    if(result)
    {
        size_t idx = 0;
        char* token = strtok(a_str, delim);

        while(token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}