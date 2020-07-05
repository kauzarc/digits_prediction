#pragma once

#include "olcPixelGameEngine.h"

const int MODEL_HEIGHT = 28, MODEL_WIDTH = 28, PIXEL_ARRAY_SCALE = 4, SCREEN_SCALE = 20, PENCIL_RADIUS = 20;

class Window : public olc::PixelGameEngine
{
private:
    std::vector<bool> pixel_array;

public:
    Window();

public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

private:
    void draw_pencil(int radius);
    int get_pixel_array_coord(const olc::vi2d &coord);
};