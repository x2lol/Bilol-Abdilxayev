#include <vector>

#include <models/recognition_request.hpp>

namespace bilol_abdilxayev {

    RecognitionRequest Parse(
        const userver::formats::json::Value& json,
        userver::formats::parse::To<RecognitionRequest>)
    {
        RecognitionRequest req;

        req.width = json["width"].As<int>();
        req.height = json["height"].As<int>();
        req.pixels = json["pixels"].As<std::vector<double>>();

        return req;
    }
} // nemaspace bilol_abdilxayev