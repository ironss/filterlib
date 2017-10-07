// filter_ma_test.c

#include <check.h>

#include <stdio.h>
#include <stdlib.h>
#include "filter.h"


const filter_sample_t samples[] =
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
};

const filter_sample_t samples1[] =
{
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
};
int samples1_length = sizeof(samples1) / sizeof(samples1[0]);

const filter_sample_t samples2[] =
{
    100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
};
int samples2_length = sizeof(samples2) / sizeof(samples2[0]);

const filter_sample_t samples3[] =
{
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
};
int samples3_length = sizeof(samples3) / sizeof(samples3[0]);


START_TEST(test_ma)
{
	#define ma1_LENGTH 5
	filter_sample_t ma1_x[ma1_LENGTH] = {};
	filter_ma_t     ma1;
	filter_ma_init(&ma1, "ma1", ma1_x, ma1_LENGTH);

	int i;
	for (i = 0; i < samples1_length; i++)
		filter_ma_update(&ma1, samples1[i]);
	ck_assert_int_eq(ma1.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_ma_update(&ma1, samples2[i]);
        printf("%s: %d\n", ma1.name, ma1.output);
    }
    ck_assert_int_eq(ma1.output, 100);

    for (i = 0; i < samples3_length; i++)
    {
        filter_ma_update(&ma1, samples3[i]);
        printf("%s: %d\n", ma1.name, ma1.output);
    }
    ck_assert_int_eq(ma1.output, 0);
}
END_TEST


START_TEST(test_splpf)
{
	filter_splpf_t splpf1;
	filter_splpf_init(&splpf1, "splpf1", 500, 1000);

	int i;
	for (i = 0; i < samples1_length; i++)
		filter_splpf_update(&splpf1, samples1[i]);
	ck_assert_int_eq(splpf1.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_splpf_update(&splpf1, samples2[i]);
        printf("%s: %d\n", splpf1.name, splpf1.output);
    }

    ck_assert_int_eq(splpf1.output, 100);

    for (i = 0; i < samples3_length; i++)
    {
        filter_splpf_update(&splpf1, samples3[i]);
        printf("%s: %d\n", splpf1.name, splpf1.output);
    }
    ck_assert_int_eq(splpf1.output, 0);
}
END_TEST


START_TEST(test_hwdexp)
{
	filter_hwdexp_t hwdexp1;
	filter_hwdexp_init(&hwdexp1, "hwdexp1", 600, 100, 1000);

	int i;
	for (i = 0; i < samples1_length; i++)
		filter_hwdexp_update(&hwdexp1, samples1[i]);
	ck_assert_int_eq(hwdexp1.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_hwdexp_update(&hwdexp1, samples2[i]);
        printf("%s: %d\n", hwdexp1.name, hwdexp1.output);
    }
    ck_assert_int_eq(hwdexp1.output, 100);

    for (i = 0; i < samples3_length; i++)
    {
        filter_hwdexp_update(&hwdexp1, samples3[i]);
    printf("%s: %d\n", hwdexp1.name, hwdexp1.output);
    }
    ck_assert_int_eq(hwdexp1.output, 0);
}
END_TEST


START_TEST(test_iir)
{
	#define iir1_LENGTH 5
	filter_sample_t iir1_x[iir1_LENGTH] = {};
	filter_sample_t iir1_y[iir1_LENGTH] = {};
	filter_iir_t    iir1;
	filter_iir_init(&iir1, "iir1", iir1_x, iir1_y, filter_iir_cheby_4p04_a, filter_iir_cheby_4p04_b, 10000, iir1_LENGTH);

	int i;
	for (i = 0; i < samples1_length; i++)
		filter_iir_update(&iir1, samples1[i]);
	ck_assert_int_eq(iir1.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_iir_update(&iir1, samples2[i]);
        printf("%s: %d\n", iir1.name, iir1.output);
    }
    ck_assert_int_eq(iir1.output, 100);

    for (i = 0; i < samples3_length; i++)
    {
        filter_iir_update(&iir1, samples3[i]);
        printf("%s: %d\n", iir1.name, iir1.output);
    }
    ck_assert_int_eq(iir1.output, -1);
}
END_TEST


Suite * filter_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("test-filters");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_ma);
    tcase_add_test(tc_core, test_splpf);
    tcase_add_test(tc_core, test_hwdexp);
    tcase_add_test(tc_core, test_iir);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = filter_suite();
    sr = srunner_create(s);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
