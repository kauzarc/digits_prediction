#pragma once

#include "olcPixelGameEngine.h"

class Window : public olc::PixelGameEngine
{
public:
    Window();

public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;
};