#include "RenderBatcher.hpp"
#include "../resources/ResourceManager.hpp"

#include <algorithm>

namespace kine
{

RenderBatcher::RenderBatcher(ResourceManager* resources) : resourceManager(resources)
{
    sorted.reserve(2048);
    batches.reserve(128);
}

void RenderBatcher::buildBatches(const std::vector<RenderCommand>& commands)
{
    sorted.clear();
    batches.clear();

    // Point sorted to existing commands
    for (const auto& cmd : commands) sorted.push_back(&cmd);

    // Deterministic stable sort by layer
    std::stable_sort(sorted.begin(), sorted.end(),
                     [](const RenderCommand* a, const RenderCommand* b) { return a->layer < b->layer; });

    // Group by texture name
    // Hash map ensures one batch per texture
    std::unordered_map<void*, size_t> batchLookup;
    batchLookup.reserve(64);

    for (const RenderCommand* cmd : sorted)
    {
        void* texturePtr = nullptr;

        if (cmd->type == RenderType::Sprite)
        {
            // Resolve texture name to Texture2D*
            // ResourceManager returns Texture2D&,
            auto& texture = resourceManager->getTexture(cmd->textureName);
            texturePtr = static_cast<void*>(&texture);
        }

        // Create new batch if necessary
        if (!batchLookup.contains(texturePtr))
        {
            const size_t newIndex = batches.size();
            batchLookup[texturePtr] = newIndex;

            RenderBatch newBatch;
            newBatch.texturePtr = texturePtr;
            batches.push_back(newBatch);
        }

        size_t batchIndex = batchLookup[texturePtr];
        batches[batchIndex].commands.push_back(cmd);
    }
}

const std::vector<RenderBatch>& RenderBatcher::getBatches() const { return batches; }

}  // namespace kine
