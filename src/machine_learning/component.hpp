#pragma once

#include <userver/components/loggable_component_base.hpp>

#include <machine_learning/nn/network.hpp>

namespace network {
    class NeuralNetworkComponent final
        : public userver::components::LoggableComponentBase {

    public:
        static constexpr std::string_view kName = "neural-network";

        NeuralNetworkComponent(
            const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context
        );

        Network& GetNetwork();

    private:
        Network network_;
    };

} // namespace network