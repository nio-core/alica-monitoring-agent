#pragma once

#include <capnp/serialize.h>
#include <string>

namespace processing {
    std::string try_read_alica_engine_info(::capnp::FlatArrayMessageReader& reader);

    std::string try_read_allocation_authority_information(::capnp::FlatArrayMessageReader &reader);

    std::string try_read_plan_tree_information(::capnp::FlatArrayMessageReader &reader);

    std::string try_read_role_switch(::capnp::FlatArrayMessageReader &reader);

    void try_read_solver_result(::capnp::FlatArrayMessageReader &reader);

    void try_read_sync_ready(::capnp::FlatArrayMessageReader &reader);

    void try_read_sync_talk(::capnp::FlatArrayMessageReader &reader);
}