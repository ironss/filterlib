// filter_splpf.c

// Single-pole low-pass filter
// See http://www.dspguide.com/ch19.htm


#include "filter.h"


void filter_splpf_init(filter_splpf_t * flt, const char * name, filter_sample_t alpha, filter_sample_t scale)
{
    flt->name = name;
    flt->alpha = alpha;
    flt->scale = scale;
    flt->output_scaled = 0;
    flt->output = 0;
}

void filter_splpf_update(filter_splpf_t * flt, filter_sample_t x)
{
    flt->output_scaled = flt->output_scaled + flt->alpha * (x - flt->output);
    flt->output = (filter_sample_t)(flt->output_scaled / flt->scale);
}
