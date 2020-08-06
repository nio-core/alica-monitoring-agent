#pragma once

// capnzero::ID
constexpr const int ID_TYPE = 1;
const std::string ID_VALUE = "id";

// Alica Engine Info
const std::string MASTER_PLAN = "MASTER_PLAN";
const std::string PLAN = "PLAN";
const std::string STATE = "STATE";
const std::string ROLE = "ROLE";
const std::string TASK = "TASK";
constexpr const int AGENT_COUNT = 3;

// Allocation Authority Info
constexpr const int PARENT_STATE = 1;
constexpr const int PLAN_TYPE = 1;
constexpr const int PLAN_ID = 1;
constexpr const int ENTRY_POINT_COUNT = 3;
constexpr const int ENTRY_POINT = 1;
constexpr const int ROBOT_COUNT = 2;

// Plan Tree Info
constexpr const int STATE_ID_COUNT = 3;
constexpr const int SUCCEEDED_EPS_COUNT = 3;

// Role Switch
constexpr const int ROLE_ID = 1;

// Solver Var
constexpr const int SOLVER_VAR_ID = 1;
constexpr const int SOLVER_VAR_VALUE_SIZE = 4;

// Solver Result
constexpr const int SOLVER_VAR_COUNT = 3;