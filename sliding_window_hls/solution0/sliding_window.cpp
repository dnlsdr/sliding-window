#include <hls_stream.h>
#include <math.h>
#include "sliding_window.h"


// Kernel szamolas
int kernel_comp(dtype kernel[3][3], const int filter1[3][3], const int filter2[3][3]) {
    int gx = 0, gy = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gx += kernel[i][j] * filter1[i][j];
            gy += kernel[i][j] * filter2[i][j];
        }
    }
    return (int)sqrt((float)(gx * gx + gy * gy));
}

void load(dtype* img, hls::stream<dtype>& in_stream) {
    for (int i = 0; i < ROWS * COLS; i++) {
    #pragma HLS PIPELINE II=1
        in_stream.write(img[i]);
    }
}

void compute(hls::stream<dtype>& in_stream, hls::stream<dtype>& out_stream, int filter1[3][3], int filter2[3][3]) {
    dtype shift_reg[2 * COLS + 3];
#pragma HLS ARRAY_PARTITION variable=shift_reg complete dim=1

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
        #pragma HLS PIPELINE II=1
            // Shift
            for (int k = 0; k < 2 * COLS + 2; k++) {
                shift_reg[k] = shift_reg[k + 1];
            }
            shift_reg[2 * COLS + 2] = in_stream.read();

            if (i >= 2 && j >= 2) {
                dtype kernel[3][3];

                #pragma HLS ARRAY_PARTITION variable=kernel complete dim=0
                kernel[0][0] = shift_reg[0];
                kernel[0][1] = shift_reg[1];
                kernel[0][2] = shift_reg[2];
                kernel[1][0] = shift_reg[COLS];
                kernel[1][1] = shift_reg[COLS + 1];
                kernel[1][2] = shift_reg[COLS + 2];
                kernel[2][0] = shift_reg[2 * COLS];
                kernel[2][1] = shift_reg[2 * COLS + 1];
                kernel[2][2] = shift_reg[2 * COLS + 2];
                #pragma HLS DEPENDENCE variable=kernel inter false
                out_stream.write(kernel_comp(kernel, filter1, filter2));
            }
        }
    }
}

void store(hls::stream<dtype>& out_stream, dtype* result) {
    for (int i = 0; i < OUT; i++) {
    #pragma HLS PIPELINE II=1
        result[i] = out_stream.read();
    }
}

void sliding_window(dtype* img, dtype* result, int filter1[3][3], int filter2[3][3]) {

//#pragma HLS DATAFLOW

hls::stream<dtype> in_stream("input_stream");

hls::stream<dtype> out_stream("output_stream");
    load(img, in_stream);
    compute(in_stream, out_stream, filter1, filter2);
    store(out_stream, result);
}
