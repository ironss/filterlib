// filter_ma_test.c

#include <stdio.h>
#include "filter.h"


#define TEST_FILTER_MA     1
#define TEST_FILTER_SPLPF  1


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

#if TEST_FILTER_MA
    {
        #define ma1_LENGTH 5
        filter_sample_t ma1_x[ma1_LENGTH];
        filter_ma_t     ma1;
        filter_ma_init(&ma1, "ma1", ma1_x, ma1_LENGTH);
        
        int i;
        for (i = 0; i < samples_length; i++)
        {
            filter_ma_update(&ma1, samples[i]);
            
            filter_ma_t * f = &ma1;
            printf("%s: %ld %d\n", f->name, f->sum, f->output);
        }
    }
#endif

#if TEST_FILTER_SPLPF
    {
        filter_splpf_t splpf1;
        filter_splpf_init(&splpf1, "splpf1", 600, 1000);
        
        int i;
        for (i = 0; i < samples_length; i++)
        {
            filter_splpf_update(&splpf1, samples[i]);
            
            filter_splpf_t * f = &splpf1;
            printf("%s: %ld %d\n", f->name, f->sum, f->output);
        }
    }
#endif
}

