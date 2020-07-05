#define OLC_PGE_APPLICATION
#include "../header/window.hpp"

Window::Window()
{
    sAppName = "Window";
}

bool Window::OnUserCreate()
{
    pixel_array.assign(MODEL_HEIGHT * PIXEL_ARRAY_SCALE * MODEL_WIDTH * PIXEL_ARRAY_SCALE, false);
    X.assign(MODEL_WIDTH * MODEL_HEIGHT + 1, 0.);
    X[0] = 1.;

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

    fill_X();

    // for (int x = 0; x < ScreenWidth(); x++)
    //     for (int y = 0; y < ScreenWidth(); y++)
    //     {
    //         float c = X[x / SCREEN_SCALE + y / SCREEN_SCALE * MODEL_WIDTH + 1];
    //         Draw({x, y},
    //              olc::PixelF(c, c, c));
    //     }

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

void Window::fill_X()
{
    for (int x = 0; x < MODEL_WIDTH; x++)
        for (int y = 0; y < MODEL_HEIGHT; y++)
        {
            int count = 0;
            for (int i = 0; i < PIXEL_ARRAY_SCALE; i++)
                for (int j = 0; j < PIXEL_ARRAY_SCALE; j++)
                    if (pixel_array[(x * PIXEL_ARRAY_SCALE + i) + (y * PIXEL_ARRAY_SCALE + j) * MODEL_WIDTH * PIXEL_ARRAY_SCALE])
                        count++;

            X[x + y * MODEL_WIDTH + 1] = (double)count / (double)(PIXEL_ARRAY_SCALE * PIXEL_ARRAY_SCALE);
        }
}