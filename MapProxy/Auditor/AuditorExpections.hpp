#pragma once
#include <exception>

class NullPtrDelegate : std::exception{};

class NullPtrReadAccessDelegate final : NullPtrDelegate{};

class NullPtrWriteAccessDelegate final : NullPtrDelegate {};

class NullPtrEraseAccessDelegate final : NullPtrDelegate {};

class NullPtrReplacementDelegate final : NullPtrDelegate {};
