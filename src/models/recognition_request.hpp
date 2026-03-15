#pragma once

#include <vector>

#include <userver/formats/json/value.hpp>

namespace bilol_abdilxayev {
    struct RecognitionRequest {
        int width;
        int height;
        std::vector<float> pixels;

    };

    RecognitionRequest Parse(
        const userver::formats::json::Value& json,
        userver::formats::parse::To<RecognitionRequest>)
    {
        RecognitionRequest req;

        req.width = json["width"].As<int>();
        req.height = json["height"].As<int>();
        req.pixels = json["pixels"].As<std::vector<float>>();

        return req;
    }
} // nemaspace bilol_abdilxayev