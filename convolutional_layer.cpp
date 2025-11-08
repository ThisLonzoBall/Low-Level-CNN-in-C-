#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    int depth;
    int input_shape[3];
    int input_depth;
    int output_shape[3];
    int kernels_shape[4];
    
    double *kernels;
    double *biases;
} Convolutional;

double randn() {
    double u = ((double)rand()+1.0) / ((double)RAND_MAX+ 1.0);
    double v = ((double)rand()+ 1.0) / ((double)RAND_MAX+ 1.0);
    return sqrt(-2.0 * log(u)) * cos(2.0* M_PI * v);
}

Convolutional Convolutional_create(int arr[], int k_size, int d) {
    Convolutional layer;

    layer.depth = d;
    for (int i = 0; i < 3; i++) {
        layer.input_shape[i] = arr[i];
    }
    layer.input_depth = layer.input_shape[0];
    int input_height = arr[1];
    int input_width  = arr[2];
            
    layer.output_shape[0] = layer.depth;
    layer.output_shape[1] = input_height - k_size + 1;
    layer.output_shape[2] = input_width  - k_size + 1;

    layer.kernels_shape[0] = layer.depth;
    layer.kernels_shape[1] = layer.input_depth;
    layer.kernels_shape[2] = k_size;
    layer.kernels_shape[3] = k_size;

    int kernel_total = layer.depth*layer.input_depth*k_size* k_size;
    int bias_total = layer.output_shape[0]*layer.output_shape[1]* layer.output_shape[2];
    layer.kernels = (double*) malloc(kernel_total * sizeof(double));

    for (int i = 0; i< kernel_total; i++){
        layer.kernels[i] = randn();
    }

    layer.biases = (double*) malloc(bias_total * sizeof(double));

    for (int i = 0; i < bias_total; i++){
        layer.biases[i] = randn();
    }


    return layer;
}

double correlate2d(double *input, double *kernel, int in_h, int in_w, int k_size, int i_out, int j_out){
    double sum = 0.0;
    for (int ki= 0; ki < k_size ; ki++){
        for (int kj =0; kj < k_size; kj++){
            int in_idx = (i_out + ki) * in_w + (j_out + kj);
            int k_idx = ki * k_size+ kj;
            sum += input[in_idx] * kernel[k_idx];
        }
    }
    return sum;
}



void Convolutional_free(Convolutional layer){
    free(layer.kernels);
    free(layer.biases);
}

double* forward(Convolutional *layer, double *input) {

    int in_d = layer->input_depth;
    int in_h = layer->input_shape[1];
    int in_w = layer-> input_shape[2];
    int out_d = layer-> depth;
    int out_h = layer->output_shape[1];
    int out_w = layer-> output_shape[2];
    int k_size = layer-> kernels_shape[2];

    int output_total = out_d * out_h * out_w;


}
int main() {
    int input_shape[3] = {3, 32, 32};
    Convolutional conv = Convolutional_create(input_shape, 5, 8);

    printf("Depth: %d\n", conv.depth);
    printf("Kernel shape: (%d, %d, %d, %d)\n",
           conv.kernels_shape[0],
           conv.kernels_shape[1],
           conv.kernels_shape[2],
           conv.kernels_shape[3]);
    return 0;
}





