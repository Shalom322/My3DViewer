
#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>
#include <functional>
#include <string>

enum class Modifier
{
    NoModifier = 0,
    Shift = 1,
    Control = 2,
    Alt = 4,
    Super = 8,
};

enum class Action
{
    Release = 0,
    Press = 1,
    Repeat = 2,
};

enum class ButtonCode
{
    Button_0 = 0,
    Button_1 = 1,
    Button_2 = 2,
    Button_3 = 3,
    Button_4 = 4,
    Button_5 = 5,
    Button_6 = 6,
    Button_7 = 7,
};

enum class KeyCode
{
    UNKNOWN = -1,
    Space = 32,
    UP = 265,
    DOWN = 264,
    RIGHT = 262,
    LEFT = 263,
};

class ViewerWindow
{
    friend void keyCallback(
        GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void mouseButtonCallback(
        GLFWwindow* window, int button, int action, int mods);
    friend void cursorCallback(GLFWwindow* window, double xpos, double ypos);
    friend void scrollCallback(
        GLFWwindow* window, double xoffset, double yoffset);

public:
    using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
    using CursorPosCallback = std::function<void(double, double)>;
    using MouseCallback =
        std::function<void(ButtonCode, Action, Modifier, double, double)>;
    using ScrollCallback = std::function<void(double, double)>;

    ViewerWindow(const std::string& title, uint32_t width, uint32_t height);
    ~ViewerWindow();

    ViewerWindow(const ViewerWindow&) = delete;
    ViewerWindow& operator=(const ViewerWindow&) = delete;

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    void setKeyCallback(const KeyCallback& callback);
    void setCursorPosCallback(const CursorPosCallback& callback);
    void setMouseCallback(const MouseCallback& callback);
    void setScrollCallback(const ScrollCallback& callback);

    GLFWwindow* getGLFWHandle() const;

private:
    GLFWwindow* m_ptrHandle = nullptr;
    uint32_t m_width;
    uint32_t m_height;

    KeyCallback m_keyClBck;
    CursorPosCallback m_cursorPosClBck;
    MouseCallback m_mouseClBck;
    ScrollCallback m_scrollClBck;
};
