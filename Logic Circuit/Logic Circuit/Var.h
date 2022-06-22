#pragma once
struct Var
{
    Rect rect;
    wchar_t label;
    bool energized;
    Var(const wchar_t& label, const bool& energized, const Rect& rect)
        :energized(energized), rect(rect), label(label) { }

    Var(const wchar_t& label, const bool& energized)
        :energized(energized), rect(Rect()), label(label) { }

    Var(const Var& other)
    {
        this->label = other.label;
        this->energized = other.energized;
        this->rect = other.rect;
    }

    Var()
        :label(L'0'), energized(false), rect(Rect()) { }
};
