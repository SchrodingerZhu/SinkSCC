# SinkSCC

A C++ implementation of the graph algorithm of finding all strongly connected components with DFS.

## Details
Each SCC of a graph can be treated as a large node. In the graph of SCC nodes, 
we can do a topological sort of nodes and find out the sink (the SCC with only in-degrees). 
Since it is a sink, a DFS on the sink SCC would reach all and only the nodes within the component.

Now the problem becomes how to identify the an abitrary node in a sink SCC. The algorithm construct 
the dual graph to solve the problem: we can do a DFS on the dual graph and then the node with the highest 
post order will be one node of the sink.

Why? Suppose we have X, Y being two SCCs, where there is an edge from X to Y in the original graph. 
So in the dual graph, there is an edge from Y to X. Consider the following two cases:

1. We do a DFS and reach a node in Y. Then, we will follow the edge to visit all the nodes in X, hence
   there must be a node in Y that has higher post order than all the nodes in X.
2. We do a DFS and reach X without touch anything in Y. However, since the global counter for post order
   will always increase, so later on, when we start a new DFS that visit Y, nodes in Y will naturally have 
   higher post order.

Therefore, both cases guarantee that the node with the highest post order must be in a sink SCC.
