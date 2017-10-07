// filter_ma_test.c

#include <stdio.h>
#include "filter.h"


#define TEST_FILTER_MA     0
#define TEST_FILTER_SPLPF  0
#define TEST_FILTER_HWDEXP 0
#define TEST_FILTER_IIR    1


int main(int argc, char * argv[])
{
	argc = argc;
	argv = argv;

    filter_sample_t samples[] =
    {
//          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//         10,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//         10,   0,  -5,   0,   1,   0,  -4,   0,   0,   0,
//          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//        100, 101, 102, 101, 100, 101, 110, 101, 100, 101,
//        102, 101, 100, 101, 120, 100, 101, 102, 101, 100,
//          0,   5,   0,   0,   0,  -15,   0,   0,   0,   3,
//          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
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
            printf("%s: %d\n", f->name, f->output);
        }
    }
#endif

#if TEST_FILTER_SPLPF
    {
        filter_splpf_t splpf1;
        filter_splpf_init(&splpf1, "splpf1", 500, 1000);
        
        int i;
        for (i = 0; i < samples_length; i++)
        {
            filter_splpf_update(&splpf1, samples[i]);
            
            filter_splpf_t * f = &splpf1;
            printf("%s: %d\n", f->name, f->output);
        }
    }
#endif

#if TEST_FILTER_HWDEXP
    {
        filter_hwdexp_t hwdexp1;
        filter_hwdexp_init(&hwdexp1, "hwdexp1", 500, 0, 10000);

        int i;
        for (i = 0; i < samples_length; i++)
        {
            filter_hwdexp_update(&hwdexp1, samples[i]);
            
            filter_hwdexp_t * f = &hwdexp1;
            printf("%s: %d\n", f->name, f->y_t);
        }
    }
#endif

#if TEST_FILTER_IIR
    {
        #define iir1_LENGTH 5
        filter_sample_t iir1_x[iir1_LENGTH];
        filter_sample_t iir1_y[iir1_LENGTH];
        filter_iir_t    iir1;
        filter_iir_init(&iir1, "iir1", iir1_x, iir1_y, filter_iir_cheby_4p04_a, filter_iir_cheby_4p04_b, 10000, iir1_LENGTH);
        
        int i;
        for (i = 0; i < samples_length; i++)
        {
            filter_iir_update(&iir1, samples[i]);
            
            filter_iir_t * f = &iir1;
            printf("%s: %d\n", f->name, f->output);
        }
    }
#endif
}

