#pragma once
#include <exception>

class DisjointSetUnionException : std::exception{};

class VertexNotInSet : DisjointSetUnionException{};
class VertexAlreadyInSet : DisjointSetUnionException{};