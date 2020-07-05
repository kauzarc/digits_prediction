#define OLC_PGE_APPLICATION
#include "../header/window.hpp"

Window::Window()
{
    sAppName = "Window";
}

bool Window::OnUserCreate()
{
    pixel_array.assign(MODEL_HEIGHT * PIXEL_ARRAY_SCALE * MODEL_WIDTH * PIXEL_ARRAY_SCALE, false);
    return true;
}

bool Window::OnUserUpdate(float fElapsedTime)
{

    if (GetMouse(0).bHeld)
        draw_pencil(PENCIL_RADIUS);

    if (GetKey(olc::SPACE).bPressed)
    {
        Clear(olc::BACK);
        pixel_array.assign(MODEL_HEIGHT * PIXEL_ARRAY_SCALE * MODEL_WIDTH * PIXEL_ARRAY_SCALE, false);
    }

    // for (int x = 0; x < ScreenWidth(); x++)
    //     for (int y = 0; y < ScreenWidth(); y++)
    //         if (pixel_array[get_pixel_array_coord({x, y})])
    //             Draw({x, y});

    return true;
}

void Window::draw_pencil(int radius)
{
    olc::vi2d mouse_pos = {GetMouseX(), GetMouseY()};
    for (int x = mouse_pos.x - radius; x < mouse_pos.x + radius; x++)
        for (int y = mouse_pos.y - radius; y < mouse_pos.y + radius; y++)
            if ((x - mouse_pos.x) * (x - mouse_pos.x) + (y - mouse_pos.y) * (y - mouse_pos.y) < radius * radius)
            {
                Draw({x, y});
                pixel_array[get_pixel_array_coord({x, y})] = true;
            }
}

int Window::get_pixel_array_coord(const olc::vi2d &coord)
{
    return (coord.x / (SCREEN_SCALE / PIXEL_ARRAY_SCALE)) + (coord.y / (SCREEN_SCALE / PIXEL_ARRAY_SCALE)) * MODEL_WIDTH * PIXEL_ARRAY_SCALE;
}