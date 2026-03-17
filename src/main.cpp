#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component_list.hpp>
#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/fs_cache.hpp>
#include <userver/server/handlers/http_handler_static.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/congestion_control/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>

#include <userver/storages/postgres/component.hpp> 

#include <userver/utils/daemon_run.hpp>

#include <hello.hpp>
#include <hello_postgres.hpp> 
#include <cortex/component.hpp>
#include <recognize_character.hpp>

int main(int argc, char* argv[]) {
    auto component_list =
        userver::components::MinimalServerComponentList()
            .Append<userver::server::handlers::Ping>()
            .Append<userver::components::TestsuiteSupport>()
            .AppendComponentList(userver::clients::http::ComponentList())
            .Append<userver::clients::dns::Component>()
            .Append<userver::server::handlers::TestsControl>()
            .Append<userver::congestion_control::Component>()
            .Append<bilol_abdilxayev::Hello>()
            .Append<userver::components::Postgres>("postgres-db-1")
            .Append<bilol_abdilxayev::HelloPostgres>()
            .Append<userver::components::FsCache>("fs-cache-main")
            .Append<userver::server::handlers::HttpHandlerStatic>()
            .Append<cortex::NeuralNetworkComponent>()
            .Append<bilol_abdilxayev::RecognizeCharacter>();
        ;

    return userver::utils::DaemonMain(argc, argv, component_list);
}