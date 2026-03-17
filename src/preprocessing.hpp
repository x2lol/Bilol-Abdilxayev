#pragma once

#include <cstddef>
#include <vector>

#include <cortex/math/matrix.hpp>

namespace bilol_abdilxayev {

cortex::math::Matrix<float> preprocess(const std::vector<double>& pixels, size_t width, size_t height);

cortex::math::Matrix<float> pixels_to_matrix(const std::vector<double>& pixels, size_t width, size_t height);

cortex::math::Matrix<float> center_image(const cortex::math::Matrix<float>& img);

cortex::math::Matrix<float> flatten(const cortex::math::Matrix<float>& img);

cortex::math::Matrix<float> center_of_mass(const cortex::math::Matrix<float>& img);

cortex::math::Matrix<float> downsample_280_to_28(const cortex::math::Matrix<float>& img);

} // namespace bilol_abdilxayev