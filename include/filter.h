// filter.h

// Various filter type
// See http://www.dspguide.com/pdfbook.htm for a discussion of general DSP principles and


#include <stdint.h>

typedef int16_t filter_sample_t;
typedef int64_t filter_intermediate_t;


// Moving average filter
// See http://www.dspguide.com/ch15.htm

typedef struct filter_ma {
    const char * name;
    filter_sample_t * x;
    int length;
    int index_n;
    filter_intermediate_t sum;
    filter_sample_t output;
} filter_ma_t;


void filter_ma_init(filter_ma_t * filter, const char * name, filter_sample_t * x_data, int length);
void filter_ma_update(filter_ma_t * filter, filter_sample_t x_n);


// Single-pole low-pass filter
// See http://www.dspguide.com/ch19.htm

typedef struct filter_splpf {
    const char * name;
    filter_sample_t output;

    filter_sample_t alpha;
    filter_sample_t scale;

    filter_intermediate_t output_scaled;
} filter_splpf_t;

void filter_splpf_init(filter_splpf_t * filter, const char * name, filter_sample_t alpha, filter_sample_t scale);
void filter_splpf_update(filter_splpf_t * filter, filter_sample_t x_n);


// Holt-Winters dual-exponential smoothing
// See https://en.wikipedia.org/wiki/Exponential_smoothing

typedef struct filter_hwdexp_smoothing {
    const char * name;
    filter_sample_t output;

    filter_sample_t alpha;
    filter_sample_t beta;
    filter_sample_t scale;
    
    filter_intermediate_t y_t_scaled;
    filter_sample_t y_t;
    filter_intermediate_t b_t_scaled;
    filter_sample_t b_t;
} filter_hwdexp_t;

void filter_hwdexp_init(filter_hwdexp_t * filter, const char * name, filter_sample_t alpha, filter_sample_t beta, filter_sample_t scale);
void filter_hwdexp_update(filter_hwdexp_t * filter, filter_sample_t x_n);


// Generic Infinite impulse response filter
// See http://www.dspguide.com/ch19.htm

typedef struct filter_iir {
    const char * name;
    filter_sample_t output;

    filter_sample_t * x;
    filter_sample_t * y;
    const filter_sample_t * a;
    const filter_sample_t * b;
    filter_sample_t scale;
    int length;
    int index_n;
} filter_iir_t;

void filter_iir_init(filter_iir_t * flt, const char * name, filter_sample_t * x, filter_sample_t * y, const filter_sample_t * a, const filter_sample_t * b, filter_sample_t scale, int length);
void filter_iir_update(filter_iir_t * flt, filter_sample_t x_n);


// Coefficients for various different types of IIR filters
// 4-pole Chebyshev filters at various cutoff frequencies
// See http://www.dspguide.com/ch20

extern const filter_sample_t filter_iir_cheby_4p01_a[];
extern const filter_sample_t filter_iir_cheby_4p01_b[];
extern const filter_sample_t filter_iir_cheby_4p02_a[];
extern const filter_sample_t filter_iir_cheby_4p02_b[];
extern const filter_sample_t filter_iir_cheby_4p03_a[];
extern const filter_sample_t filter_iir_cheby_4p03_b[];
extern const filter_sample_t filter_iir_cheby_4p04_a[];
extern const filter_sample_t filter_iir_cheby_4p04_b[];
