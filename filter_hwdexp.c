// filter_hwdexp.c

#include "filter.h"


void filter_hwdexp_init(filter_hwdexp_t * flt, const char * name, filter_sample_t alpha, filter_sample_t beta, filter_sample_t scale)
{
    flt->name = name;
    flt->alpha = alpha;
    flt->beta = beta;
    flt->scale = scale;
    flt->y_t_scaled = 0;
    flt->y_t = 0;
    flt->b_t_scaled = 0;
    flt->b_t = 0;
    
}

void filter_hwdexp_update(filter_hwdexp_t * flt, filter_sample_t x)
{
    filter_intermediate_t y_t_scaled = flt->alpha * x + (flt->scale - flt->alpha) * (flt->y_t + flt->b_t);
    filter_sample_t y_t = y_t_scaled / flt->scale;
    
    filter_intermediate_t b_t_scaled = flt->beta * (y_t - flt->y_t) + (flt->scale - flt->beta) * flt->b_t;
    filter_sample_t b_t = flt->b_t_scaled / flt->scale;
    
    flt->y_t_scaled = y_t_scaled;
    flt->y_t = y_t;
    flt->b_t_scaled = flt->b_t;
    flt->b_t = flt->b_t;
}

