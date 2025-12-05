#include "Input.hpp"

#include <raylib.h>

namespace kine
{

Input::Input() {}

bool Input::keyDown(int key) const { return IsKeyDown(key); }
bool Input::keyPressed(int key) const { return IsKeyPressed(key); }
bool Input::keyReleased(int key) const { return IsKeyReleased(key); }

bool Input::mouseDown(int button) const { return IsMouseButtonDown(button); }
bool Input::mousePressed(int button) const { return IsMouseButtonPressed(button); }
bool Input::mouseReleased(int button) const { return IsMouseButtonReleased(button); }

float Input::mouseX() const { return GetMouseX(); }
float Input::mouseY() const { return GetMouseY(); }

void Input::bindAction(InputAction action, int keyCode) { keyBindings[action] = keyCode; }

bool Input::isActionDown(InputAction action) const
{
    auto it = keyBindings.find(action);
    if (it != keyBindings.end())
    {
        return keyDown(it->second);
    }
    return false;
}

}  // namespace kine
