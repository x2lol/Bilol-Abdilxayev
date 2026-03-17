#pragma once

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <cortex/component.hpp>
#include <models/recognition_response.hpp>

namespace bilol_abdilxayev {
    
class RecognizeCharacter final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-recognize-character";

    RecognizeCharacter(
        const userver::components::ComponentConfig& config, 
        const userver::components::ComponentContext& context
    );

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest&,
        userver::server::request::RequestContext&) const override;

private:
    cortex::Network& network_;
    std::vector<Prediction> build_predictions(const cortex::math::Matrix<float>& output) const;
};
}  // namespace bilol_abdilxayev