#pragma once

#include <vector>

#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <cortex/math/matrix.hpp>

namespace bilol_abdilxayev {
    struct Prediction {
        std::string label;
        float probability;
    };

    struct RecognitionResponse {
        std::vector<Prediction> predictions;
    };

    userver::formats::json::Value Serialize(const RecognitionResponse& data, userver::formats::serialize::To<userver::formats::json::Value>);


    userver::formats::json::Value Serialize(const Prediction& data, userver::formats::serialize::To<userver::formats::json::Value>); 

} // nemaspace bilol_abdilxayev