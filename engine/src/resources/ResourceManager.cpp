#include "ResourceManager.hpp"
#include <Log.hpp>
#include <filesystem>

namespace fs = std::filesystem;

namespace kine
{

ResourceManager::ResourceManager()
{
    searchDirs = {
        "assets/",
    };

    extensions = {".png", ".jpg"};
}

void ResourceManager::init()
{
    buildIndex();

    // Load fallback texture
    errorTexture = &loadIndexedTexture("error");

    Log::info("[ResourceManager] Indexed ", fileIndex.size(), " texture files");
}

void ResourceManager::buildIndex()
{
    fileIndex.clear();

    for (const auto& dir : searchDirs)
    {
        if (!fs::exists(dir))
        {
            Log::warn("[ResourceManager] Directory not found: ", dir);
            continue;
        }

        for (auto& entry : fs::recursive_directory_iterator(dir))
        {
            if (!entry.is_regular_file()) continue;

            const auto ext = entry.path().extension().string();
            const auto filename = entry.path().stem().string();

            // Only index supported extensions
            if (std::find(extensions.begin(), extensions.end(), ext) == extensions.end()) continue;

            const std::string fullPath = entry.path().string();

            // Store unique key
            fileIndex[filename] = fullPath;
        }
    }
}

Texture2D& ResourceManager::loadIndexedTexture(const std::string& name)
{
    // Already loaded?
    if (textures.contains(name)) return textures[name];

    // Exists in index?
    auto it = fileIndex.find(name);
    if (it == fileIndex.end())
    {
        Log::error("[ResourceManager] No file indexed for ", name);
        return *errorTexture;
    }

    const std::string& path = it->second;

    Log::info("[ResourceManager] Loading texture: ", path);

    Texture2D tex = LoadTexture(path.c_str());
    if (tex.id == 0)
    {
        Log::error("[ResourceManager] Failed to load '", path, "'");
        return *errorTexture;
    }

    textures[name] = tex;
    return textures[name];
}

Texture2D& ResourceManager::getTexture(const std::string& name) { return loadIndexedTexture(name); }

const Texture2D& ResourceManager::getTexture(const std::string& name) const
{
    auto it = textures.find(name);
    if (it != textures.end()) return it->second;

    return *errorTexture;
}

void ResourceManager::shutdown()
{
    Log::info("[ResourceManager] Unloading {} textures", textures.size());

    for (auto& [name, tex] : textures) UnloadTexture(tex);

    textures.clear();
    errorTexture = nullptr;
    fileIndex.clear();
}

}  // namespace kine
