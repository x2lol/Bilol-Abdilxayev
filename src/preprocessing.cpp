#include <preprocessing.hpp>

#include <algorithm>

namespace bilol_abdilxayev {

network::math::Matrix<float> pixels_to_matrix(
    const std::vector<double>& pixels,
    size_t width,
    size_t height)
{
    network::math::Matrix<float> img(height, width);

    for (size_t i = 0; i < pixels.size(); ++i) {
        img[i] = static_cast<float>(pixels[i]);
    }

    return img;
}

BoundingBox compute_bbox(const network::math::Matrix<float>& img)
{
    size_t w = img.cols();
    size_t h = img.rows();

    size_t min_x = w, max_x = 0;
    size_t min_y = h, max_y = 0;

    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            if (img(y,x) > 0.01f) {
                min_x = std::min(min_x, x);
                max_x = std::max(max_x, x);
                min_y = std::min(min_y, y);
                max_y = std::max(max_y, y);
            }
        }
    }

    return {min_x, max_x, min_y, max_y};
}

std::pair<float,float> bbox_center(const BoundingBox& box)
{
    float cx = (box.min_x + box.max_x) / 2.0f;
    float cy = (box.min_y + box.max_y) / 2.0f;

    return {cx, cy};
}

network::math::Matrix<float> center_image(const network::math::Matrix<float>& img)
{
    size_t w = img.cols();
    size_t h = img.rows();

    BoundingBox box = compute_bbox(img);
    auto [cx, cy] = bbox_center(box);

    float target_x = w / 2.0f;
    float target_y = h / 2.0f;

    int dx = static_cast<int>(target_x - cx);
    int dy = static_cast<int>(target_y - cy);

    network::math::Matrix<float> result(h, w);

    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {

            int src_x = static_cast<int>(x) - dx;
            int src_y = static_cast<int>(y) - dy;

            if (src_x >= 0 && src_x < (int)w &&
                src_y >= 0 && src_y < (int)h)
            {
                result(y,x) = img(src_y,src_x);
            }
            else
            {
                result(y,x) = 0.0f;
            }
        }
    }

    return result;
}

network::math::Matrix<float> flatten(const network::math::Matrix<float>& img)
{
    network::math::Matrix<float> vec(img.size(), 1);

    for (size_t i = 0; i < img.size(); ++i)
        vec[i] = img[i];

    return vec;
}

network::math::Matrix<float> resize_to_28(const network::math::Matrix<float>& img){
    size_t src_h = img.rows();
    size_t src_w = img.cols();

    const size_t dst = 28;

    network::math::Matrix<float> out(dst, dst);

    float scale_x = static_cast<float>(src_w) / dst;
    float scale_y = static_cast<float>(src_h) / dst;

    for (size_t y = 0; y < dst; ++y) {
        for (size_t x = 0; x < dst; ++x) {

            size_t src_x = static_cast<size_t>(x * scale_x);
            size_t src_y = static_cast<size_t>(y * scale_y);

            out(y,x) = img(src_y,src_x);
        }
    }

    return out;
}

} // namespace bilol_abdilxayev