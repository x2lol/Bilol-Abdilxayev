#include <hello.hpp>

#include <recognize_character.hpp>

namespace bilol_abdilxayev {
    RecognizeCharacter::RecognizeCharacter(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : HttpHandlerBase(config, context),
          network_(context.FindComponent<network::NeuralNetworkComponent>().GetNetwork())
    {}
    
    std::string RecognizeCharacter::HandleRequestThrow(
        const userver::server::http::HttpRequest& request, 
        userver::server::request::RequestContext&) const {
            request.
    }

} // namespace bilol_abdilxayev