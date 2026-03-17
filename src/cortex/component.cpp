#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component_config.hpp>

#include <cortex/component.hpp>
#include <cortex/serialization/model_io.hpp>
#include <userver/yaml_config/schema.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

namespace cortex {
    constexpr std::string_view kModelPath = "model_path";

    NeuralNetworkComponent::NeuralNetworkComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context
    ) : userver::components::LoggableComponentBase(config, context) {

            std::vector<float> weights; 
            std::vector<float> biases;
            network_ = serialization::ModelIO::load(config[kModelPath].As<std::string>());

    }

    userver::yaml_config::Schema NeuralNetworkComponent::GetStaticConfigSchema() {
        return userver::yaml_config::MergeSchemas<
            userver::components::LoggableComponentBase
        >(R"(
    type: object
    description: Neural network inference component
    additionalProperties: false
    properties:
        model_path:
            type: string
            description: Path to serialized neural network model
    )");
    }
    Network& NeuralNetworkComponent::GetNetwork() {
        return network_;
    };

} // cortex