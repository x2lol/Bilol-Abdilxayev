#include <recognize_character.hpp>
#include <models/recognition_request.hpp>
#include <preprocessing.hpp>

namespace bilol_abdilxayev {
    static const std::vector<std::string> LABELS = {
        "0","1","2","3","4","5","6","7","8","9",
    };
    
    RecognizeCharacter::RecognizeCharacter(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : HttpHandlerBase(config, context),
          network_(context.FindComponent<cortex::NeuralNetworkComponent>().GetNetwork())
    {}
    
    std::string RecognizeCharacter::HandleRequestThrow(
        const userver::server::http::HttpRequest& request, 
        userver::server::request::RequestContext&) const {
            
            userver::formats::json::Value request_json = userver::formats::json::FromString(request.RequestBody());
 
            RecognitionRequest req = request_json.As<RecognitionRequest>();
            
            cortex::math::Matrix<float> input = preprocess(req.pixels, req.width, req.height);

            cortex::math::Matrix<float> output = network_.forward(input);

            return  userver::formats::json::ToString(userver::formats::json::ValueBuilder{RecognitionResponse{build_predictions(output)}}.ExtractValue());
    }


    std::vector<Prediction> RecognizeCharacter::build_predictions(const cortex::math::Matrix<float>& output) const {
        std::vector<Prediction> preds;

        preds.reserve(output.size());

        for (size_t i = 0; i < output.size(); ++i) {
            preds.push_back({
                LABELS[i],
                output[i]
            });
        }

        auto comp = [] (const Prediction& a, const Prediction& b) -> bool {
            return a.probability > b.probability;
        };

        std::sort(preds.begin(), preds.end(), comp);
        
        return preds;
    }
    
} // namespace bilol_abdilxayev