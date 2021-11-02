#ifdef __GNUC__
#pragma once
#endif

#ifndef SINSCC_SCC_H
#define SINSCC_SCC_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace scc {
    class Graph {
    public:
        explicit Graph(const std::vector<std::string> &names) {
            for (const auto &i: names) {
                nodes.insert({i, Node{i}});
            }
        }

        void connect(const std::string &x, const std::string &y) {
            nodes.at(x).edges.push_back(&nodes.at(y));
            nodes.at(y).dual_edges.push_back(&nodes.at(x));
        }

    private:
        struct Node {
            std::string name;
            std::vector<Node *> edges{};
            std::vector<Node *> dual_edges{};
            bool visited = false;

            explicit Node(std::string name) : name(std::move(name)) {}

            void dual_dfs(std::vector<Node *> &acc) {
                if (visited) return;
                visited = true;
                for (auto i: dual_edges) {
                    i->dual_dfs(acc);
                }
                acc.push_back(this);
            }

            void primal_dfs(std::vector<Node *> &acc) {
                if (visited) return;
                visited = true;
                acc.push_back(this);
                for (auto i: edges) {
                    i->primal_dfs(acc);
                }
            }
        };

        std::unordered_map<std::string, Node> nodes;

        std::vector<Node *> dual_dfs() {
            std::vector<Node *> ordered_nodes{};
            for (auto &i: nodes) {
                i.second.dual_dfs(ordered_nodes);
            }
            for (auto &i: nodes) {
                i.second.visited = false;
            }
            return ordered_nodes;
        }

    public:
        std::vector<std::vector<std::string>> scc() {
            dual_dfs();
            std::vector<std::vector<std::string>> result;
            auto reversed_topological_order = dual_dfs();
            for (auto i = reversed_topological_order.rbegin(); i != reversed_topological_order.rend(); ++i) {
                if (!(*i)->visited) {
                    result.emplace_back();
                    std::vector<Node *> subgraph{};
                    (*i)->primal_dfs(subgraph);
                    for (auto j: subgraph) {
                        result.back().push_back(j->name);
                    }
                }
            }
            for (auto &i: nodes) {
                i.second.visited = false;
            }
            return result;
        }
    };
}
#endif //SINSCC_SCC_H
