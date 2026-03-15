#include <machine_learning/training/loss.hpp>
#include <machine_learning/training/trainer.hpp>

namespace network {
    void train(Network& net, const math::Matrix<float>& X, const network::math::Matrix<float>& Y, size_t epochs, float learning_rate) {
        for(size_t e = 0; e < epochs; ++e){
            math::Matrix<float> y_pred = net.forward(X);
            
            math::Matrix<float> grad = cross_entropy_grad(y_pred, Y);
            net.backward(grad, learning_rate);
        }
    }
}