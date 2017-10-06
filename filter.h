// filter.h

#include <stdint.h>

typedef int16_t filter_sample_t;

typedef struct filter_ma {
    const char * name;
    filter_sample_t * x;
    int length;
    int index_n;
    int64_t sum;
    filter_sample_t output;
} filter_ma_t;


void filter_ma_init(filter_ma_t * filter, const char * name, filter_sample_t * x_data, int length);
void filter_ma_update(filter_ma_t * filter, filter_sample_t x_n);


typedef struct filter_splpf {
    const char * name;
    filter_sample_t alpha_num;
    filter_sample_t alpha_denom;
    int64_t sum;
    filter_sample_t output;
} filter_splpf_t;

void filter_splpf_init(filter_splpf_t * filter, const char * name, filter_sample_t num, filter_sample_t denom);
void filter_splpf_update(filter_splpf_t * filter, filter_sample_t x);

