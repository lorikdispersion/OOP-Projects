#pragma once
#include <stdexcept>

class ReadAccessDenied final : std::exception{};

class WriteAccessDenied final : std::exception {};

class EraseAccessDenied final : std::exception {};

class AuditorNullPtr final : std::exception {};