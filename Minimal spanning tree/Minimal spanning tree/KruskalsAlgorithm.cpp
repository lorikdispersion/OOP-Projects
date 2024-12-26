#include "KruskalsAlgorithm.hpp"
#include "EdgeLengthComparator.hpp"
#include "DisjointSetUnion.hpp"

#include <map>
#include <ranges>
#include <set>


Graph KruskalsAlgorithm::createSpanningTree(const Graph& graph) const  noexcept
{
	Graph::Builder spanningTreeData;

	if (graph.countVertices() == 0)
	{
		return spanningTreeData.createGraph();
	}
	if (graph.countVertices() == 1)
	{
		spanningTreeData.insertVertex(graph.getVertices().begin()->second);
		return spanningTreeData.createGraph();
	}

	std::multiset<Edge, EdgesLengthComparator> sortedEdges;
	for (const auto& it : graph.getEdges())
	{
		sortedEdges.insert(it);
	}

	DisjointSetUnion dsu;
	for (const auto& it : graph.getVertices() | std::views::values) {
		dsu.insertNewVertexToDeligate(it, it);
	}

	for (auto iterator = sortedEdges.begin();
		spanningTreeData.countEdges() < graph.countVertices() - 1; ++iterator)
	{
		const Vertex& startVertex = iterator->getStartVertex();
		const Vertex& endVertex = iterator->getEndVertex();
		Vertex startVertexDeligate = dsu.getParent(startVertex);
		Vertex endVertexDeligate = dsu.getParent(endVertex);
		if (startVertexDeligate != endVertexDeligate)
		{
			for (auto [vertex, deligate] : dsu.getVerticesToDeligates())
			{
				if (deligate == endVertexDeligate)
				{
					dsu.changeDeligate(vertex, startVertexDeligate);
				}
			}
			spanningTreeData.insertEdge(startVertex, endVertex);
		}
	}
	return spanningTreeData.createGraph();
}
