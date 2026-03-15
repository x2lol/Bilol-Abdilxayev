#pragma once

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <machine_learning/component.hpp>

namespace bilol_abdilxayev {
    
class RecognizeCharacter final : public userver::server::handlers::HttpHandlerBase {
public:
    RecognizeCharacter(
        const userver::components::ComponentConfig& config, 
        const userver::components::ComponentContext& context
    );

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest&,
        userver::server::request::RequestContext&) const override;

private:
    const network::Network& network_;
};
}  // namespace bilol_abdilxayev