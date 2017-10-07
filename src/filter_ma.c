// filter_ma.c

#include "filter.h"


void filter_ma_init(filter_ma_t * flt, const char * name, filter_sample_t * x_data, int length)
{
    flt->name = name;
    flt->x = x_data;
    flt->length = length;
    flt->index_n = 0;
    flt->sum = 0;
    flt->output = 0;
}

void filter_ma_update(filter_ma_t * flt, filter_sample_t x_n)
{
    flt->sum = flt->sum + x_n - flt->x[flt->index_n];
    flt->output = (filter_sample_t)(flt->sum / flt->length);

    flt->x[flt->index_n] = x_n;

    flt->index_n++;
    if (flt->index_n >= flt->length)
        flt->index_n = 0;
}

