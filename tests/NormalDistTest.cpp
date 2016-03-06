#include <tiny_cnn/tiny_cnn.h>

using namespace tiny_cnn;
using namespace tiny_cnn::activation;

int main() {
    network<mse, gradient_descent> nn;

    nn << fully_connected_layer<sigmoid>(12, 4)
       << fully_connected_layer<identity>(4, 4);

    for (int i = 0; i < nn.depth(); i++) {
        std::cout << "#layer:" << i << "\n";
        std::cout << "layer type:" << nn[i]->layer_type() << "\n";
        std::cout << "input:" << nn[i]->in_size() << " (" << nn[i]->in_shape() << ")\n";
        std::cout << "output:" << nn[i]->out_size() << " (" << nn[i]->out_shape() << ")\n";
        std::cout << "weight:" << nn[i]->weight().size() << " (" << nn[i]->weight()[0] << ")\n\n";
    }
}