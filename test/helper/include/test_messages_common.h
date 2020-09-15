#pragma once

#include <capnp/serialize.h>

kj::Array<capnp::word> capnzero_id_message();

kj::Array<capnp::word> prepare_allocation_authority_info_message();

kj::Array<capnp::word> entrypoint_robots_message();

kj::Array<capnp::word> alica_engine_info_message();

kj::Array<capnp::word> plan_tree_info_message();

kj::Array<capnp::word> role_switch_message();

kj::Array<capnp::word> solver_result_message();

kj::Array<capnp::word> solver_var_message();

kj::Array<capnp::word> sync_ready_message();

kj::Array<capnp::word> sync_talk_message();

kj::Array<capnp::word> sync_data_message();
