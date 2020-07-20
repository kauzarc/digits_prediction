#define OLC_PGE_APPLICATION
#include "../header/window.hpp"

#include <iomanip>

Window::Window()
{
    sAppName = "Window";
}

bool Window::OnUserCreate()
{
    pixel_array.assign(MODEL_HEIGHT * PIXEL_ARRAY_SCALE * MODEL_WIDTH * PIXEL_ARRAY_SCALE, false);
    X.assign(MODEL_WIDTH * MODEL_HEIGHT + 1, 0.);
    X[0] = 1.;
    perceptron.load("perceptron.bin");

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

    const int scale = 2;

    FillRect({0, 0},
             {scale * 7 * 8, scale * 10 * 8},
             olc::BLACK);

    prediction = perceptron.predict(X);
    int max_index = std::max_element(prediction.begin(), prediction.end()) - prediction.begin();

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(3);
    for (unsigned int i = 0; i < prediction.size(); i++)
    {
        stream << i << ":" << prediction[i] << "\n";
    }

    DrawString({0, 0},
               stream.str(),
               olc::WHITE,
               scale);

    DrawRect({0, scale * max_index * 8},
             {scale * 7 * 8, scale * 8},
             olc::WHITE);

    // for (int x = 0; x < ScreenWidth(); x++)
    //     for (int y = 0; y < ScreenWidth(); y++)
    //     {
    //         float c = X[x / SCREEN_SCALE * MODEL_HEIGHT + y / SCREEN_SCALE + 1];
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

            X[x * MODEL_HEIGHT + y + 1] = (double)count / (double)(PIXEL_ARRAY_SCALE * PIXEL_ARRAY_SCALE);
        }
}