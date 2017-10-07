// filter_ma_test.c

#include <check.h>

#include <stdio.h>
#include <stdlib.h>
#include "filter.h"


#define TEST_FILTER_MA     0
#define TEST_FILTER_SPLPF  0
#define TEST_FILTER_HWDEXP 0
#define TEST_FILTER_IIR    1


#define UNUSED(x) ((void)(x))


//int main(int argc, char * argv[])
//{
//	UNUSED(argc);
//	UNUSED(argv);

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

    START_TEST(test_iir)
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
    END_TEST

//}


Suite * iir_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("test-iir");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_iir);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = iir_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
