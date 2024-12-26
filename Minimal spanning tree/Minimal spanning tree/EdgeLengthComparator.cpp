#include "EdgeLengthComparator.hpp"

bool EdgesLengthComparator::operator()(const Edge& lhs, const Edge& rhs) const noexcept
{
	return lhs.getLength() < rhs.getLength();
}
