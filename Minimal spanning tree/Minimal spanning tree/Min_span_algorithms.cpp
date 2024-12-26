#include <set>

#include "Min_span_algorithms.hpp"

Kruskals_algorithm::Edge::Edge(const Vertex& vertex1, const Vertex& vertex2)
: vertex_1_(vertex1), vertex_2_(vertex2)
{
	const double dx = vertex1.x() - vertex2.x();
	const double dy = vertex1.y() - vertex2.y();
	length_ = sqrt(pow(dx, 2) + pow(dy, 2));
}

double Kruskals_algorithm::Edge::get_length() const
{
	return length_;
}

const Vertex& Kruskals_algorithm::Edge::get_vertex_first() const
{
	return vertex_1_;
}

const Vertex& Kruskals_algorithm::Edge::get_vertex_second() const
{
	return vertex_2_;
}


bool Kruskals_algorithm::Edge_Comparator::operator()(const Edge& lhs, const Edge& rhs) const
{
	return lhs.get_length() < rhs.get_length();
}


Minimal_Spanning_Tree Kruskals_algorithm::create_span(const Complete_graph& complete_graph) const
{
	Minimal_Spanning_Tree span;
	if(complete_graph.get_vertex_set().empty())
	{
		return span;
	}
	if (complete_graph.get_vertex_set().size() == 1)
	{
		span.insert_vertex(*complete_graph.get_vertex_set().begin());
		return span;
	}
	std::multiset<Edge, Edge_Comparator> all_path_set;
	for (auto iterator_1{ complete_graph.get_vertex_set().begin() };
		iterator_1 != complete_graph.get_vertex_set().end(); ++iterator_1)
	{
		for (auto iterator_2 = std::next(iterator_1);
			iterator_2 != complete_graph.get_vertex_set().end(); ++iterator_2)
		{
			all_path_set.insert({ *iterator_2 ,*iterator_1 });
		}
	}

	for (auto iterator = all_path_set.begin();
		span.get_path_map().size() < complete_graph.get_vertex_set().size() - 1
		&& iterator != all_path_set.end();
		++iterator)
	{
		span.insert_path(iterator->get_vertex_first(), iterator->get_vertex_second());
	}
	return span;
}