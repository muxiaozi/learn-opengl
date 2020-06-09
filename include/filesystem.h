#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <root_directory.h>
#include <string>
#include <functional>

class FileSystem
{
private:
    using Builder = std::function<std::string(const std::string& path)>;

public:
	static std::string getPath(const std::string& path)
	{
        static Builder builder = getPathBuilder();
        return builder(path);
	}

private:
    static std::string const& getRoot()
    {
        static char const* envRoot = getenv("LOGL_ROOT_PATH");
        static char const* givenRoot = (envRoot != nullptr ? envRoot : logl_root);
        static std::string root = (givenRoot != nullptr ? givenRoot : "");
        return root;
    }

    static Builder getPathBuilder()
    {
        if (getRoot().empty())
        {
            return &FileSystem::getPathRelativeRoot;
        }
        else
        {
            return &FileSystem::getPathRelativeBinary;
        }
    }

    static std::string getPathRelativeRoot(const std::string& path)
    {
        return getRoot() + std::string("/") + path;
    }

    static std::string getPathRelativeBinary(const std::string& path)
    {
        return "../../../" + path;
    }
};

#endif // FILE_SYSTEM_H