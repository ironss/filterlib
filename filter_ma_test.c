// filter_ma_test.c

#include <stdio.h>
#include "filter_ma.h"


#define f1_LENGTH 5
filter_sample_t f1x[f1_LENGTH];
filter_ma_t     f1;


int main(int argc, char * argv[])
{
    filter_sample_t samples[] =
    {
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
         10,   0,   0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
         10,   0,  -5,   0,   1,   0,  -4,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        100, 101, 102, 101, 100, 101, 110, 101, 100, 101,
        102, 101, 100, 101, 120, 100, 101, 102, 101, 100,
          0,   5,   0,   0,   0,  -15,   0,   0,   0,   3,
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    };
    int samples_length = sizeof(samples) / sizeof(samples[0]);

    filter_ma_init(&f1, "f1", f1x, f1_LENGTH);
    
    int i;
    for (i = 0; i < samples_length; i++)
    {
        filter_ma_update(&f1, samples[i]);
        printf("%s: %ld %d\n", f1.name, f1.sum, f1.output);
    }
}

