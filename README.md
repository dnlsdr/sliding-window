# sliding-window
Sliding window image filter using Vitis HLS on FPGA

This project demonstrates the concepts I have learned through the implementation of a sliding window-based image filter developed using Vitis HLS on an FPGA platform. Image processing tasks are particularly well-suited to showcasing the advantages of FPGAs: for clearly defined, highly parallelizable operations, only the necessary logic is implemented. This results in energy-efficient, high-performance processing.

The core idea of sliding window processing is to move a fixed-size window — typically 3×3 — across the image, pixel by pixel. At each position, the neighborhood of the central pixel is selected and subjected to a mathematical operation.

This method is especially efficient on FPGAs due to the use of buffered storage and register chains to move the window. Thanks to pipelined data processing, a new result can be produced on every clock cycle. This enables real-time image processing with low latency and high throughput.
