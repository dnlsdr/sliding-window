#ifndef HLS_SLIDING_WINDOW_H
#define HLS_SLIDING_WINDOW_H

#include <hls_stream.h>

#define ROWS 5
#define COLS 8
#define OUT ((ROWS - 2) * (COLS - 2))
#define KERNEL_SIZE 3

typedef int dtype;

void sliding_window(dtype* img, dtype* result,
                    int filter1[KERNEL_SIZE][KERNEL_SIZE],
                    int filter2[KERNEL_SIZE][KERNEL_SIZE]);

#endif // HLS_SLIDING_WINDOW_H
