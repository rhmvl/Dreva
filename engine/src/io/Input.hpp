#pragma once

#include <unordered_map>

namespace dreva::engine
{
// Define semantic actions for the game
enum class InputAction
{
};

class Input
{
   public:
    Input();

    // Raw Input Checks
    bool keyDown(int key) const;
    bool keyPressed(int key) const;
    bool keyReleased(int key) const;

    bool mouseDown(int button) const;
    bool mousePressed(int button) const;
    bool mouseReleased(int button) const;

    float mouseX() const;
    float mouseY() const;

    // Action Mapping
    bool isActionDown(InputAction action) const;
    void bindAction(InputAction action, int keyCode);

   private:
    std::unordered_map<InputAction, int> keyBindings;
};

}  // namespace dreva::engine
