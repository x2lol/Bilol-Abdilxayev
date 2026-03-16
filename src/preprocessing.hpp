#pragma once

#include <cstddef>
#include <vector>
#include <utility>

#include <machine_learning/math/matrix.hpp>

namespace bilol_abdilxayev {

struct BoundingBox {
    size_t min_x, max_x;
    size_t min_y, max_y;
};

network::math::Matrix<float> pixels_to_matrix(
    const std::vector<double>& pixels,
    size_t width,
    size_t height);

BoundingBox compute_bbox(const network::math::Matrix<float>& img);

std::pair<float,float> bbox_center(const BoundingBox& box);

network::math::Matrix<float> center_image(const network::math::Matrix<float>& img);

network::math::Matrix<float> flatten(const network::math::Matrix<float>& img);

    network::math::Matrix<float> resize_to_28(const network::math::Matrix<float>& img);

} // namespace bilol_abdilxayev