#pragma once
#include <exception>

class BadEdge final : std::exception {};
class BadVertex final : std::exception {};