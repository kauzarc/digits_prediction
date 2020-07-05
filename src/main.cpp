#include "header/window.hpp"

int main()
{
    Window app;
    if (app.Construct(560, 560, 1, 1))
        app.Start();
    return 0;
}
