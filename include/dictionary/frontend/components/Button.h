#ifndef GUI_COMPONENT_BUTTON
#define GUI_COMPONENT_BUTTON

#include "global.h"

class Button
{
    private:
        std::string label;
    public:
        Rectangle buttonBox{0, 0, 0, 0};
        Button();
        Button(std::string label, float posX, float poxY, float width);

        bool drawButton(const Vector2 &scroll = {0, 0});

};
#endif 