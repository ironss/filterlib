// filter_iir.c

// Generic Infinite impulse response filter
// See http://www.dspguide.com/ch19.htm


#include "filter.h"


void filter_iir_init(filter_iir_t * flt, const char * name, filter_sample_t * x, filter_sample_t * y, const filter_sample_t * a, const filter_sample_t *b, filter_sample_t scale, int length)
{
    flt->name = name;
    flt->x = x;
    flt->y = y;
    flt->a = a;
    flt->b = b;
    flt->scale = scale;
    flt->length = length;
    flt->index_n = 0;
    flt->output = 0;
}

void filter_iir_update(filter_iir_t * flt, filter_sample_t x_n)
{
    // Insert the new sample into the x data array
    flt->index_n++;
    if (flt->index_n >= flt->length)
        flt->index_n = 0;
    flt->x[flt->index_n] = x_n;
    flt->y[flt->index_n] = 0;
    
    // Calculate the new
    filter_intermediate_t y_scaled = 0;
    int i = 0;
    int j = flt->index_n;
    while (i < flt->length)
    {
        y_scaled += flt->a[i] * flt->x[j] + flt->b[i] * flt->y[j];
        i++;
        j--;
        if (j < 0)
            j = flt->length - 1;
    }
    flt->y[flt->index_n] = (filter_sample_t)(y_scaled / flt->scale);
    flt->output = flt->y[flt->index_n];
}


const filter_sample_t filter_iir_cheby_4p01_a[] = 
{
    28, 111, 167, 111, 28,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p01_b[] = 
{
    0, 27640, -31228, 16645, -3502,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p02_a[] = 
{
    322, 1290, 1935, 1290, 322,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p02_b[] = 
{
    0, 12659, -12039, 5406, -1186,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p03_a[] = 
{
    1336, 5342, 8013, 5342, 1336,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p03_b[] = 
{
    0, -3904, -6784, -141, -539,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p04_a[] = 
{
    3897, 15588, 23382, 15588, 3897,  // scaled by 10000
};

const filter_sample_t filter_iir_cheby_4p04_b[] = 
{
    0, -21612, -20340, -8789, -1611,  // scaled by 10000
};
