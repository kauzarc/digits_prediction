#define OLC_PGE_APPLICATION
#include "../header/window.hpp"

Window::Window()
{
    sAppName = "Window";
}

bool Window::OnUserCreate()
{
    return true;
}

bool Window::OnUserUpdate(float fElapsedTime)
{
    for (int x = 0; x < ScreenWidth(); x++)
        for (int y = 0; y < ScreenHeight(); y++)
            Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
    return true;
}