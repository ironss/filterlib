// filter_splpf.c

// Single-pole low-pass filter
// See http://www.dspguide.com/ch19.htm


#include "filter.h"


void filter_sphpf_init(filter_sphpf_t * flt, const char * name, filter_sample_t alpha, filter_sample_t scale)
{
    flt->name = name;
    flt->A0 = (filter_sample_t)((scale + alpha) / 2);
    flt->A1 = (filter_sample_t)(-flt->A0);
    flt->B1 = alpha;
    flt->scale = scale;
    flt->x_n1 = 0;
    flt->output_scaled = 0;
    flt->output = 0;
}

void filter_sphpf_update(filter_sphpf_t * flt, filter_sample_t x_n)
{
    flt->output_scaled = flt->A0 * x_n  +  flt->A1 * flt->x_n1  +  flt->B1 * flt->output;
    flt->output = (filter_sample_t)(flt->output_scaled / flt->scale);
    flt->x_n1 = x_n;
}
