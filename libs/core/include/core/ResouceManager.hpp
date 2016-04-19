#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <core/DEFS.hpp>
#include <string>

template class LIB_EXPORT_CONV std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

class LIB_EXPORT_CONV ResourceManager {
public:

    ResourceManager(const std::string& appLocation);
    ~ResourceManager();

    void setShadersDir(const std::string& dirPath);

    std::string getShaderPath(const std::string& shaderName) const;

private:

    std::string resourceRoot;
    std::string shadersRoot;
};

#endif /* __RESOURCE_MANAGER_HPP__ */