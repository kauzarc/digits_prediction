#pragma once

#include "olcPixelGameEngine.h"
#include "perceptron_multi.hpp"

const int MODEL_HEIGHT = 28, MODEL_WIDTH = 28, PIXEL_ARRAY_SCALE = 4, SCREEN_SCALE = 20, PENCIL_RADIUS = 35;

class Window : public olc::PixelGameEngine
{
private:
    std::vector<bool> pixel_array;
    vect::vectd X;

    PerceptronMulti perceptron;
    std::vector<double> prediction;

public:
    Window();

public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

private:
    void draw_pencil(int radius);
    int get_pixel_array_coord(const olc::vi2d &coord);
    void fill_X();
};