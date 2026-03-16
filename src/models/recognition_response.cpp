#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/common_containers.hpp>

#include <models/recognition_response.hpp>

namespace bilol_abdilxayev {

userver::formats::json::Value Serialize(const RecognitionResponse& data, userver::formats::serialize::To<userver::formats::json::Value>) {
    userver::formats::json::ValueBuilder builder;

    for (const Prediction& prediction : data.predictions) {
        builder.PushBack(userver::formats::json::ValueBuilder{prediction});
    }

    return builder.ExtractValue();
}

userver::formats::json::Value Serialize(const Prediction& data, userver::formats::serialize::To<userver::formats::json::Value>) {
    userver::formats::json::ValueBuilder builder;
    builder["label"] = data.label;
    builder["probability"] = data.probability;
 
    return builder.ExtractValue();
}

} // nemaspace bilol_abdilxayev