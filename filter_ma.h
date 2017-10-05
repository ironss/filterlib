// filter_ma.h

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

