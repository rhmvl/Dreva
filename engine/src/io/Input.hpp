#pragma once

#include <unordered_map>

namespace kine
{

/**
 * @enum InputAction
 * @brief Semantic meaning of actions used by the gameplay layer.
 */
enum class InputAction
{
    RELOAD
};

/**
 * @class Input
 * @brief Wrapper around Raylib input functions with action binding support.
 *
 * This class allows querying raw input states (keyboard and mouse) and also
 * supports mapping high-level game actions to specific key codes.
 */
class Input
{
   public:
    Input();

    /// @name Raw Input Checks
    /// @{

    /** @brief Returns true while a key is held down. */
    bool keyDown(int key) const;

    /** @brief Returns true only on the frame the key is pressed. */
    bool keyPressed(int key) const;

    /** @brief Returns true only on the frame the key is released. */
    bool keyReleased(int key) const;

    /** @brief Returns true while a mouse button is held. */
    bool mouseDown(int button) const;

    /** @brief Returns true only on the frame the mouse button is pressed. */
    bool mousePressed(int button) const;

    /** @brief Returns true only on the frame the mouse button is released. */
    bool mouseReleased(int button) const;

    /// @}

    /** @brief Gets current mouse X coordinate in screen space. */
    float mouseX() const;

    /** @brief Gets current mouse Y coordinate in screen space. */
    float mouseY() const;

    /**
     * @brief Binds an InputAction to a specific keycode.
     */
    void bindAction(InputAction action, int keyCode);

    /**
     * @brief Tests whether an action's bound key is currently held down.
     */
    bool isActionDown(InputAction action) const;

   private:
    std::unordered_map<InputAction, int> keyBindings;  ///< Maps gameplay actions to keycodes
};

}  // namespace kine
