#include <preprocessing.hpp>
#include <userver/logging/log.hpp>

namespace bilol_abdilxayev {

cortex::math::Matrix<float> preprocess(const std::vector<double>& pixels, size_t width, size_t height) {
    cortex::math::Matrix<float> img = pixels_to_matrix(pixels, width, height);

    img = center_of_mass(img);

    img = downsample_280_to_28(img);

    return flatten(img.transpose()); // transpose is EMNIST specific
}

cortex::math::Matrix<float> pixels_to_matrix(const std::vector<double>& pixels, size_t width, size_t height) {
    cortex::math::Matrix<float> img(height, width);

    for (size_t i = 0; i < pixels.size(); ++i) {
        img[i] = static_cast<float>(pixels[i]);
    }

    return img;
}


cortex::math::Matrix<float> flatten(const cortex::math::Matrix<float>& img) {
    cortex::math::Matrix<float> vec(img.size(), 1);

    for (size_t i = 0; i < img.size(); ++i) {
        vec[i] = img[i];
    }

    return vec;
}


cortex::math::Matrix<float> center_of_mass(const cortex::math::Matrix<float>& img) {
    size_t h = img.rows();
    size_t w = img.cols();

    float sum = 0;
    float cx = 0;
    float cy = 0;

    for(size_t y = 0; y < h; y++) {
        for(size_t x = 0; x < w; x++) {
            float v = img(y,x);

            sum += v;
            cx += x * v;
            cy += y * v;
        }
    }

    if(sum == 0) return img;

    cx /= sum;
    cy /= sum;

    int shift_x = static_cast<int>(w / 2 - cx);
    int shift_y = static_cast<int>(h / 2 - cy);

    cortex::math::Matrix<float> out(h,w);

    for(size_t y = 0; y < h; y++) {
        for(size_t x = 0; x < w; x++) {
            int src_x = x - shift_x;
            int src_y = y - shift_y;

            if(src_x >= 0 && src_x < (int)w && src_y >= 0 && src_y < (int)h) {
                out(y,x) = img(src_y,src_x);
            } else {
                out(y,x) = 0;
            }
        }
    }

    return out;
}

cortex::math::Matrix<float> downsample_280_to_28(const cortex::math::Matrix<float>& img) {
    const int block = 10;

    cortex::math::Matrix<float> out(28,28);

    for(int y=0;y<28;y++) {
        for(int x=0;x<28;x++) {
            float sum = 0;

            for(int dy = 0; dy < block; dy++) {
                for(int dx = 0; dx < block; dx++) {
                    sum += img(y * block + dy, x * block + dx);
                }
            }

            out(y,x) = sum / 100.0f;
        }
    }

    return out;
}

} // namespace bilol_abdilxayev