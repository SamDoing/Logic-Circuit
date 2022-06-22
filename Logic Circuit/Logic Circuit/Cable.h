#pragma once
#include "Declaration.h"

struct Cable
{
    int  x, y, xF, yF;
    bool* energized;
    WCHAR label;
    Cable(bool* energized, const WCHAR& label, const int& x, const int& y, const int& xF, const int& yF)
        :energized(energized), label(label), x(x), y(y), xF(xF), yF(yF) { }

    void Draw(Graphics& graphics)
    {
        Pen pen(Color((*energized ? 255 : 0), 0, 0), 3.F);
        DrawCable(pen, x, y, xF, yF, graphics);
    }

};

