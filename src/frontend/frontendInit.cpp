#include "frontendInit.h"
#include "global.h"

void setStyles()
{
    // Text Colors
    GuiSetStyle(DEFAULT, TEXT_SIZE, DISPLAY_FONT_SIZE);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, TEXT_COLOR);

    // Borders for buttons
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, OUTLINE_COLOR);

    // Buttons
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, TEXT_COLOR);

    // Textbox
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, TEXT_COLOR);

    // Dropdown Box
    GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL, TEXT_COLOR);
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING, 0);

    // List views
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, 15);

    // Font
    GuiSetFont(ResourcesPath::displayRegularFont);
}