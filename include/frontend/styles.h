#ifndef FRONTEND_PALETTE_H
#define FRONTEND_PALETTE_H

/**
*   Bảng màu đươc lấy từ Material Design Theme Builder, sử dụng 4 màu cơ bản ở đây: 
*   https://colorhunt.co/palette/ff9b9bffd6a5fffec4cbffa9
* 
*   Material Theme Builder:
*   https://m3.material.io/theme-builder#/custom
*
*   Hình của bảng màu có thể xem tại folder visualisations/palette-sample.jpeg
*   Hình của các nút dựa trên bảng màu này có thể xem tại visualisations/Components.png
*/

// Có một số hàm tạo hình của Raylib sử dụng Color, nên cần phải chuyển đổi từ hex sang RGB
// Chính xác ra có thể sử dụng GetColor() để lấy màu từ hex, nhưng mà phê quá lỡ làm cmnr 
// 
// Note là nếu cần đổi màu, mã Hex cần phải đủ 8 kí tự, tức là có cả mã alpha.
// Có thể để alpha là `FF` cho xong.

// Màu chính
#define PRIMARY_COLOR (0x9C4144ff)
#define PRIMARY_COLOR_RGB (Color){0x9c, 0x41, 0x44, 0xff}

// Màu của nút, các ô chứa, ...
#define PRIMARY_COLOR_CONTAINER (0xF1C27BFF)
#define PRIMARY_COLOR_CONTAINER_RGB (Color){241, 194, 123, 255}

// Same thing nhưng khi di chuột lên
#define PRIMARY_COLOR_CONTAINER_HOVER (0xFAEAD4FF)
#define PRIMARY_COLOR_CONTAINER_HOVER_RGB (Color){250, 234, 212, 255}

// Màu phụ
#define SECONDARY_COLOR (0xB5C99AFF)
#define SECONDARY_COLOR_RGB (Color){181, 201, 154, 255}

#define BOX_COLOR_RGB (Color){196, 193, 164, 255}

// Màu của nút, các ô chứa, ... nhưng sử dụng tông màu phụ
#define SECONDARY_COLOR_CONTAINER (0x#73490dff)
#define SECONDARY_COLOR_CONTAINER_RGB (Color){0xff, 0xdd, 0xb6, 0xff}

// Same thing nhưng khi di chuột lên
#define OUTLINE_COLOR (0xB5C99Aff)
#define OUTLINE_COLOR_RGB (Color){0x85, 0x73, 0x72, 0xff}

#define RESULT_COLOR_CONTAINER_HOVER (0xBDD2B6FF)

// Màu nền
#define BG_COLOR (0xFFECAFF)
#define BG_COLOR_RGB (Color){255, 254, 202, 255}

// Màu của chữ
#define TEXT_COLOR (0x000000ff)
#define TEXT_COLOR_RGB (Color){0x08, 0x21, 0x00, 0xff}

#define DEF_COLOR (0xF1F0E8FF)

// Window resolution
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Cỡ font chữ

// Font size của từ
#define WORD_FONT_SIZE 30

// Font nội dụng bình thường
#define TEXT_FONT_SIZE 25

// 2 cái này chắc dư thừa nhma ai biết có xài hay ko :)))
#define ITEM_HEIGHT 30

#define MAX_INPUT_CHAR 256


#endif