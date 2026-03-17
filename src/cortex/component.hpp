#pragma once

#include <userver/components/loggable_component_base.hpp>

#include <cortex/nn/network.hpp>

namespace cortex {
    class NeuralNetworkComponent final
        : public userver::components::LoggableComponentBase {

    public:
        static constexpr std::string_view kName = "neural-network";

        NeuralNetworkComponent(
            const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context
        );

        Network& GetNetwork();
        
        static userver::yaml_config::Schema GetStaticConfigSchema();
    
    private:
        Network network_;
    };

} // namespace cortex