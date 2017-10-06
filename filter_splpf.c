// filter_splpf.c

#include "filter.h"


void filter_splpf_init(filter_splpf_t * filter, const char * name, filter_sample_t num, filter_sample_t denom)
{
    filter->name = name;
    filter->alpha_num = num;
    filter->alpha_denom = denom;
    filter->sum = 0;
    filter->output = 0;
}

void filter_splpf_update(filter_splpf_t * filter, filter_sample_t x)
{
    filter->sum = filter->sum + filter->alpha_num * (x - filter->output);
    filter->output = filter->sum / filter->alpha_denom;
}

