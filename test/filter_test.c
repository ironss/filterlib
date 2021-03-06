// filter_ma_test.c

#include <check.h>

#include <stdio.h>
#include <stdlib.h>
#include "filter.h"


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
	filter_splpf_init(&splpf1, "splpf1", 700, 1000);

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


START_TEST(test_sphpf)
{
    filter_sphpf_t sphpf1;
    filter_sphpf_init(&sphpf1, "sphpf1", 800, 1000);

    int i;
    for (i = 0; i < samples1_length; i++)
        filter_sphpf_update(&sphpf1, samples1[i]);
    ck_assert_int_eq(sphpf1.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_sphpf_update(&sphpf1, samples2[i]);
        printf("%s: %d\n", sphpf1.name, sphpf1.output);
    }

    ck_assert_int_eq(sphpf1.output, 0);

    for (i = 0; i < samples3_length; i++)
    {
        filter_sphpf_update(&sphpf1, samples3[i]);
        printf("%s: %d\n", sphpf1.name, sphpf1.output);
    }
    ck_assert_int_eq(sphpf1.output, 0);
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


START_TEST(test_iir2)
{
    #define iir2_LENGTH 5
    filter_sample_t iir2_x[iir2_LENGTH] = {};
    filter_sample_t iir2_y[iir2_LENGTH] = {};
    filter_iir_t    iir2;
    filter_iir_init(&iir2, "iir2", iir2_x, iir2_y, &filter_iir_cheby_4p04);

    int i;
    for (i = 0; i < samples1_length; i++)
        filter_iir_update(&iir2, samples1[i]);
    ck_assert_int_eq(iir2.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_iir_update(&iir2, samples2[i]);
        printf("%s: %d\n", iir2.name, iir2.output);
    }
    ck_assert_int_eq(iir2.output, 100);

    for (i = 0; i < samples3_length; i++)
    {
        filter_iir_update(&iir2, samples3[i]);
        printf("%s: %d\n", iir2.name, iir2.output);
    }
    ck_assert_int_eq(iir2.output, -1);
}
END_TEST


START_TEST(test_splpf_iir)
{
    filter_splpf_t splpf3;
    filter_splpf_init(&splpf3, "splpf3", 750, 1000);

    #define iir3_LENGTH 2
    filter_sample_t iir3_x[iir2_LENGTH] = {};
    filter_sample_t iir3_y[iir2_LENGTH] = {};
    const filter_iir_config_t filter_iir_splpf_0_75 =
    {
        2,
        1000,
        (filter_sample_t [2]){ 250, 0, },
        (filter_sample_t [2]){ 0, 750, },
    };

    filter_iir_t    iir3;
    filter_iir_init(&iir3, "iir3", iir3_x, iir3_y, &filter_iir_splpf_0_75);

    int i;
    for (i = 0; i < samples1_length; i++)
    {
        filter_splpf_update(&splpf3, samples1[i]);
        filter_iir_update(&iir3, samples1[i]);
    }
    ck_assert_int_eq(splpf3.output, 0);
    ck_assert_int_eq(iir3.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_splpf_update(&splpf3, samples2[i]);
        filter_iir_update(&iir3, samples2[i]);
        printf("%s: %d   %s: %d\n", splpf3.name, splpf3.output, iir3.name, iir3.output);
    }
    ck_assert_int_eq(splpf3.output, 100);
    ck_assert_int_eq(iir3.output, 97);  // This is an expected failure

    for (i = 0; i < samples3_length; i++)
    {
        filter_splpf_update(&splpf3, samples3[i]);
        filter_iir_update(&iir3, samples3[i]);
        printf("%s: %d   %s: %d\n", splpf3.name, splpf3.output, iir3.name, iir3.output);
    }
    ck_assert_int_eq(splpf3.output, 0);
    ck_assert_int_eq(iir3.output, 0);
}
END_TEST


START_TEST(test_sphpf_iir)
{
    filter_sphpf_t sphpf4;
    filter_sphpf_init(&sphpf4, "sphpf4", 750, 1000);

    #define iir4_LENGTH 2
    filter_sample_t iir4_x[iir2_LENGTH] = {};
    filter_sample_t iir4_y[iir2_LENGTH] = {};
    const filter_iir_config_t filter_iir_sphpf_0_75 =
    {
        2,
        1000,
        (filter_sample_t [2]){ 825, -825, },
        (filter_sample_t [2]){ 0, 750, },
    };

    filter_iir_t    iir4;
    filter_iir_init(&iir4, "iir4", iir4_x, iir4_y, &filter_iir_sphpf_0_75);

    int i;
    for (i = 0; i < samples1_length; i++)
    {
        filter_sphpf_update(&sphpf4, samples1[i]);
        filter_iir_update(&iir4, samples1[i]);
    }
    ck_assert_int_eq(sphpf4.output, 0);
    ck_assert_int_eq(iir4.output, 0);

    for (i = 0; i < samples2_length; i++)
    {
        filter_sphpf_update(&sphpf4, samples2[i]);
        filter_iir_update(&iir4, samples2[i]);
        printf("%s: %d   %s: %d\n", sphpf4.name, sphpf4.output, iir4.name, iir4.output);
    }
    ck_assert_int_eq(sphpf4.output, 0);
    ck_assert_int_eq(iir4.output, 0);

    for (i = 0; i < samples3_length; i++)
    {
        filter_sphpf_update(&sphpf4, samples3[i]);
        filter_iir_update(&iir4, samples3[i]);
        printf("%s: %d   %s: %d\n", sphpf4.name, sphpf4.output, iir4.name, iir4.output);
    }
    ck_assert_int_eq(sphpf4.output, 0);
    ck_assert_int_eq(iir4.output, 0);
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
    tcase_add_test(tc_core, test_sphpf);
    tcase_add_test(tc_core, test_hwdexp);
    tcase_add_test(tc_core, test_iir2);
    tcase_add_test(tc_core, test_splpf_iir);
    tcase_add_test(tc_core, test_sphpf_iir);
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
