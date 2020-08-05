#pragma once

#include <capnp/serialize.h>
#include <string>

namespace processing {
    std::string role_switch_capnproto_to_json(::capnp::FlatArrayMessageReader &reader);

    std::string solver_result_capnproto_to_json(::capnp::FlatArrayMessageReader &reader);

    std::string sync_ready_capnproto_to_json(::capnp::FlatArrayMessageReader &reader);

    std::string sync_talk_capnproto_to_json(::capnp::FlatArrayMessageReader &reader);
}