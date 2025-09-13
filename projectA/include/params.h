//
// Created by denisyang on 25-9-13.
//

#ifndef PLUGIN_PARAMS_H
#define PLUGIN_PARAMS_H
#include <string>
#include <unordered_map>
#include <any>
#include <iostream>
enum class NodeType {
    INPUT,
    OUTPUT,
    PROCESS
};

// 重载<<操作符
inline std::ostream& operator<<(std::ostream& os, const NodeType& type) {
        switch (type) {
                case NodeType::INPUT: os << "INPUT"; break;
                case NodeType::OUTPUT: os << "OUTPUT"; break;
                case NodeType::PROCESS: os << "PROCESS"; break;
                default: os << "UNKNOWN";
        }
        return os;
}

struct NodeConfig {
    std::string id;
    std::string name;
    NodeType type;
    std::string typeVersion;
    std::string description;
    std::string label;
    std::unordered_map<std::string, std::any> inputs;
    std::unordered_map<std::string, std::any> outputs;
    std::string responseMode;
    std::string responseContent;
    std::unordered_map<std::string, std::string> branches;

public:
    void print() {
        std::cout << "id: " << id << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "type: " << type << std::endl;
        std::cout << "typeVersion: " << typeVersion << std::endl;
        std::cout << "description: " << description << std::endl;
        std::cout << "label: " << label << std::endl;
        std::cout << "inputs: " << inputs.size() << std::endl;
        std::cout << "outputs: " << outputs.size() << std::endl;
        std::cout << "responseMode: " << responseMode << std::endl;
        std::cout << "responseContent: " << responseContent << std::endl;
        std::cout << "branches: " << branches.size() << std::endl;
    }
};

#endif //PLUGIN_PARAMS_H
