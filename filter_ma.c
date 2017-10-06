// filter_ma.c

#include "filter.h"


void filter_ma_init(filter_ma_t * filter, const char * name, filter_sample_t * x_data, int length)
{
    filter->name = name;
    filter->x = x_data;
    filter->length = length;
    filter->index_n = 0;
    filter->sum = 0;
    filter->output = 0;
}

void filter_ma_update(filter_ma_t * filter, filter_sample_t x_n)
{
    filter->sum = filter->sum + x_n - filter->x[filter->index_n];
    filter->output = filter->sum / filter->length;

    filter->x[filter->index_n] = x_n;

    filter->index_n++;
    if (filter->index_n >= filter->length)
        filter->index_n = 0;
}

