#include "header/window.hpp"

int main()
{
    Window app;
    if (app.Construct(SCREEN_SCALE * MODEL_WIDTH, SCREEN_SCALE * MODEL_HEIGHT, 1, 1))
        app.Start();
    return 0;
}
