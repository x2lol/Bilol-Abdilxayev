#pragma once

#include <vector>

#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/common_containers.hpp>

namespace bilol_abdilxayev {
    struct RecognitionRequest {
        int width;
        int height;
        std::vector<double> pixels;
    };

    RecognitionRequest Parse(
        const userver::formats::json::Value& json,
        userver::formats::parse::To<RecognitionRequest>);

} // nemaspace bilol_abdilxayev