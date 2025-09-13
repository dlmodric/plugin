#include "class_factory.h"

ClassFactory& ClassFactory::getInstance() {
    static ClassFactory instance;
    return instance;
}

void ClassFactory::registerClass(const std::string& className, CreateFunc creator) {
    registry[className] = creator;
}

std::unique_ptr<IPlugin> ClassFactory::createObject(const std::string& className) {
    auto it = registry.find(className);
    if (it != registry.end()) {
        return std::unique_ptr<IPlugin>(it->second());
    }
    return nullptr;
}

bool ClassFactory::isRegistered(const std::string& className) const {
    return registry.find(className) != registry.end();
}

size_t ClassFactory::getRegisteredCount() const {
    return registry.size();
}

std::vector<std::string> ClassFactory::getRegisteredClasses() const {
    std::vector<std::string> classes;
    for (const auto& pair : registry) {
        classes.push_back(pair.first);
    }
    return classes;
}