#include <iostream>
#include <cstdlib>
#include "hls_stream.h"
#include "sliding_window.h"

void input_img(dtype* img) {
    for (int i = 0; i < ROWS * COLS; i++) {
        img[i] = i + 1; // Sorfolytonos feltoltes 1-tol
    }
}
void init_golden(dtype* golden) {
    for (int i = 0; i < OUT; i++) {
        golden[i] = 64; // Elvart referenciaertek
    }
}
int filter1[KERNEL_SIZE][KERNEL_SIZE] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
int filter2[KERNEL_SIZE][KERNEL_SIZE] = {
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};
int main() {
    dtype* img = new dtype[ROWS * COLS];
    dtype* result = new dtype[OUT];
    dtype* golden = new dtype[OUT];

    input_img(img);
    init_golden(golden);
    sliding_window(img, result, filter1, filter2);
    for (int i = 0; i < OUT; i++) {
        std::cout << "result[" << i << "] = " << result[i] <<std::endl;
        if (result[i] != golden[i]) {
            std::cout << "Hiba! Index: " << i << " Elvart: " << golden[i]
                    << " Kapott: " << result[i] << std::endl;
            return 1;
        }
    }
    std::cout << "Teszt sikeres." <<std::endl;
    delete[] img;
    delete[] result;
    delete[] golden;
    return 0;
}
