#include "Complete_Graph.hpp"

void Complete_Graph::insert(const Vertex& vertex)
{
	vertex_set_.insert(vertex);
}

const Vertex_Set& Complete_Graph::get_vertex_set() const
{
	return vertex_set_;
}

[[nodiscard]] std::size_t Complete_Graph::vertex_set_size() const
{
	return vertex_set_.size();
}