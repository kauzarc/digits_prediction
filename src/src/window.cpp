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
    const int radius = 100;

    if (GetMouse(0).bHeld)
    {
        olc::vi2d mouse_pos = {GetMouseX(), GetMouseY()};
        for (int x = mouse_pos.x - radius; x < mouse_pos.x + radius; x++)
            for (int y = mouse_pos.y - radius; y < mouse_pos.y + radius; y++)
                if ((x - mouse_pos.x) * (x - mouse_pos.x) + (y - mouse_pos.y) * (y - mouse_pos.y) < radius)
                    Draw({x, y});
    }

    return true;
}