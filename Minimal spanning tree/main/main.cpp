#include <fstream>
#include <iostream>

#include "CompleteGraphFactory.hpp"
#include "KruskalsAlgorithm.hpp"
#include "Parser.hpp"
#include "GraphsEdgesPrinter.hpp"

int main()
{
    const CompleteGraphFactory factory{ Parser{ ", " } };
    KruskalsAlgorithm algorithm;
    std::fstream inputFile;

    inputFile.open("inputTestOneEdge.txt", std::ios::in);
    auto completeGraph = factory.createGraph(inputFile);
    Graph span = algorithm.createSpanningTree(completeGraph);

    std::cout << "Graph with one edge minimal spanning tree:" << std::endl;
    GraphEdgesPrinter::printToStream(span, std::cout);

    inputFile.close();
    inputFile.open("inputTestTwoEdges.txt", std::ios::in);
    completeGraph = factory.createGraph(inputFile);
    span = algorithm.createSpanningTree(completeGraph);

    std::cout << "Graph with two edges minimal spanning tree:" << std::endl;
    GraphEdgesPrinter::printToStream(span, std::cout);

    inputFile.close();
    inputFile.open("inputTestManyEdges.txt", std::ios::in);
    completeGraph = factory.createGraph(inputFile);
    span = algorithm.createSpanningTree(completeGraph);

    std::cout << "Graph with five edges minimal spanning tree:" << std::endl;
    GraphEdgesPrinter::printToStream(span, std::cout);
}
