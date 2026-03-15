#pragma once
#include <vector>
#include <machine_learning/nn/dense_layer.hpp>

namespace network {
    struct Network {
        std::vector<DenseLayer> layers;

        network::math::Matrix<float> forward(const network::math::Matrix<float>& x);
        void backward(const network::math::Matrix<float>& grad_output, float learning_rate);
        void serialize(std::vector<float>& weights, std::vector<float>& biases) const;
        void initialize(const std::vector<float>& weights, const std::vector<float>& biases); 
    };
} // nemaspace network