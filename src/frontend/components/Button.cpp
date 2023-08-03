#include "components/Button.h"

Button::Button(){}

Button::Button(std::string label, float posX, float posY, float width) : buttonBox({posX, posY, width, ITEM_HEIGHT}), label(label){}

bool Button::drawButton(const Vector2 &scroll)
{
    Rectangle buttonBoxWithScroll = buttonBox;
    buttonBoxWithScroll.x = scroll.x;
    buttonBoxWithScroll.y = scroll.y;
    return GuiButton(buttonBoxWithScroll, label.c_str());
}