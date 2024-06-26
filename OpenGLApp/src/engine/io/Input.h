#pragma once
#include <unordered_map>
#include "Callbacks.h"

class Input {
public:
    static bool GetKey(int key);
    static bool GetMouseButton(int button);
    static double GetMouseX();
    static double GetMouseY();
    static void RegisterCallbacks(GLFWwindow* window);

    friend class Callbacks;

private:
    Input() {}

    static std::unordered_map<int, bool> keys;
    static std::unordered_map<int, bool> mouseButtons;
    static double mouseX;
    static double mouseY;
};
