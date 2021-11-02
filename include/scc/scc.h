#ifdef __GNUC__
#pragma once
#endif

#ifndef SINSCC_SCC_H
#define SINSCC_SCC_H

#include <vector>
#include <unordered_map>
#include <algorithm>

namespace scc {
    template<class Index, class N>
    struct VectorType {
        using Container = std::vector<N>;

        template<class Source>
        static N const &get(Source const &src) {
            return src;
        }

        template<class Iter>
        static Container construct(Iter begin, Iter end) {
            Container nodes{};
            for (auto i = begin; i != end; i = std::next(i)) {
                nodes.push_back(N{*i});
            }
            return nodes;
        }
    };

    template<class Index, class N>
    struct AssocMapType {
        using Container = std::unordered_map<Index, N>;

        template<class Source>
        static N const &get(Source const &src) {
            return src.second;
        }

        template<class Iter>
        static Container construct(Iter begin, Iter end) {
            Container nodes{};
            for (auto i = begin; i != end; i = std::next(i)) {
                nodes.insert({*i, N{*i}});
            }
            return nodes;
        }
    };
};

template<class Index, template<class, class> typename TypeTrait>
class Graph {
public:
    template<class Iter>
    explicit Graph(Iter begin, Iter end) : nodes(TypeImpl::construct(std::move(begin), std::move(end))) {

    }

    void connect(const Index &x, const Index &y) {
        nodes[x].edges.push_back(&nodes[y]);
        nodes[y].dual_edges.push_back(&nodes[x]);
    }

private:
    struct Node {
        Index name;
        std::vector<const Node *> edges{};
        std::vector<const Node *> dual_edges{};
        mutable bool visited = false;

        Node() {}

        explicit Node(Index name) : name(std::move(name)) {}

        void dual_dfs(std::vector<const Node *> &acc) const {
            if (visited) return;
            visited = true;
            for (auto i: dual_edges) {
                i->dual_dfs(acc);
            }
            acc.push_back(this);
        }

        void primal_dfs(std::vector<const Node *> &acc) const {
            if (visited) return;
            visited = true;
            acc.push_back(this);
            for (auto i: edges) {
                i->primal_dfs(acc);
            }
        }
    };

    using TypeImpl = TypeTrait<Index, Node>;
    typename TypeImpl::Container nodes;

    std::vector<const Node *> dual_dfs() {
        std::vector<const Node *> ordered_nodes{};
        for (auto &i: nodes) {
            TypeImpl::get(i).dual_dfs(ordered_nodes);
        }
        for (auto &i: nodes) {
            TypeImpl::get(i).visited = false;
        }
        return ordered_nodes;
    }

public:
    std::vector<std::vector<Index>> scc() {
        dual_dfs();
        std::vector<std::vector<Index>> result;
        auto reversed_topological_order = dual_dfs();
        for (auto i = reversed_topological_order.rbegin(); i != reversed_topological_order.rend(); ++i) {
            if (!(*i)->visited) {
                result.emplace_back();
                std::vector<const Node *> subgraph{};
                (*i)->primal_dfs(subgraph);
                for (auto j: subgraph) {
                    result.back().push_back(j->name);
                }
            }
        }
        for (auto &i: nodes) {
            TypeImpl::get(i).visited = false;
        }
        return result;
    }
};

#endif //SINSCC_SCC_H
