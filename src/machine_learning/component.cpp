#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component_config.hpp>

#include <machine_learning/component.hpp>
#include <machine_learning/serialization/model_io.hpp>
#include <userver/yaml_config/schema.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

namespace network {
    constexpr std::string_view kModelPath = "model_path";
    constexpr size_t INPUT_SIZE  = 784;
    constexpr size_t OUTPUT_SIZE = 10;

    NeuralNetworkComponent::NeuralNetworkComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context
    ) : userver::components::LoggableComponentBase(config, context) {

            std::vector<float> weights; 
            std::vector<float> biases;
            serialization::ModelIO::load(config[kModelPath].As<std::string>(), weights, biases);

            network_.layers.emplace_back(INPUT_SIZE, 128, activation::Type::ReLU);
            network_.layers.emplace_back(128, 64, activation::Type::ReLU);
            network_.layers.emplace_back(64, OUTPUT_SIZE, activation::Type::Softmax);

            network_.initialize(weights,biases);

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

} // network