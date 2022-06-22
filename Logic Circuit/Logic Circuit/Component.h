#pragma once

struct Component
{
    const Size size = szComponent;
    int x, y;
    int xF = x + szComponent.Width, yF = y + szComponent.Height;
    bool energized;

    GateType type;
    std::vector<bool*> inputs;

    Component(const int& x, const int& y, const GateType& type, std::vector<bool*>& inputs)
        :energized(false), x(x), y(y), type(type)
    {
        for (size_t i = 0; i < inputs.size(); i++)
        {
            bool* boP = new bool;
            boP = inputs[i];
            this->inputs.push_back(boP);
        }
        CalculateOut();
    }

    Component()
        :energized(false), x(0), y(0), type(NOT)
    {}


    Component operator=(const Component& other)
    {
        x = other.x;
        y = other.y;
        xF = other.xF;
        yF = other.yF;
        energized = other.energized;
        type = other.type;
        inputs = other.inputs;

        return other;
    }

    void Draw(Graphics& graphics)
    {
        DrawComponent(energized, type, x, y, graphics);
        CalculateOut();
    }

    bool* GetEnergized() {
        return &energized;
    }

private:
    void CalculateOut()
    {
        bool result;
        switch (type)
        {
        case AND:
            result = true;
            for (size_t i = 0; i < inputs.size(); i++)
                result = result & *inputs[i];
            energized = result;
            break;

        case OR:
            result = false;
            for (size_t i = 0; i < this->inputs.size(); i++)
                result = result | *inputs[i];
            energized = result;
            break;

        case NOT:
            energized = !*inputs[0];
            break;

        default:
            break;
        }
    }
};
