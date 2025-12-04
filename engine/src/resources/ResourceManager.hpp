#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace dreva::engine
{

class ResourceManager
{
   public:
    ResourceManager();

    void init();
    Texture2D& getTexture(const std::string& name);
    const Texture2D& getTexture(const std::string& name) const;
    void shutdown();

   private:
    void buildIndex();
    Texture2D& loadIndexedTexture(const std::string& name);

    std::vector<std::string> searchDirs;
    std::vector<std::string> extensions;

    // name to full path
    std::unordered_map<std::string, std::string> fileIndex;
    // name to loaded texture
    std::unordered_map<std::string, Texture2D> textures;

    Texture2D* errorTexture = nullptr;
};

}  // namespace dreva::engine
