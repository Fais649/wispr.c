#ifndef LAYOUT_H
#define LAYOUT_H

#include <M5Unified.h>

namespace Layout {
extern const m5gfx::IFont *window_content_title_font;
extern const m5gfx::IFont *window_content_text_font;
extern const m5gfx::IFont *dock_symbol_font;

extern float window_content_title_size;
extern float window_content_text_size;
extern float dock_text_size;

// NEVER TOUCH
extern float display_width;
extern float display_height;

extern epd_mode_t display_mode_fastest;
extern epd_mode_t display_mode_slowest;

// NO CALLING, ONLY TOUCHING
extern float dock_ver_margin;
extern float dock_hor_margin;

extern float window_hor_margin;
extern float window_ver_margin;
extern float window_content_x_padding;
extern float window_content_y_padding;
extern float window_border_radius;
extern float window_content_x_indent;
extern float window_content_title_height;
extern float window_content_text_lines;

extern float dock_width;
extern float dock_height;
extern float dock_border_radius;
extern float dock_content_padding;

extern float dock_right_width;
extern float dock_right_height;
extern float dock_right_content_padding;
extern float dock_right_border_radius;

extern float shadow_x_modifier;
extern float shadow_y_modifier;
extern float shadow_width_modifier;
extern float shadow_height_modifier;
//

extern float sleep_icon_color_abs;
extern float sleep_icon_content_color_abs;

extern char sleep_icon[2];
extern char finger_icon[2];
extern float sleep_icon_size;
extern float sleep_icon_radius_abs;
extern float sleep_icon_x_abs;
extern float sleep_icon_y_abs;
extern float sleep_icon_wrapper_x_abs;
extern float sleep_icon_wrapper_y_abs;

// NO TOUCHING, ONLY CALLING
extern float dock_ver_margin_abs;
extern float dock_hor_margin_abs;

extern float dock_x_abs;
extern float dock_y_abs;
extern float dock_height_abs;
extern float dock_width_abs;

extern float dock_content_x_padding_abs;
extern float dock_content_y_padding_abs;
extern float dock_border_radius_abs;

extern float dock_right_x_abs;
extern float dock_right_y_abs;

extern float dock_right_width_abs;
extern float dock_right_height_abs;

extern float dock_right_content_x_padding_abs;
extern float dock_right_content_y_padding_abs;
extern float dock_right_border_radius_abs;

extern float window_hor_margin_abs;
extern float window_ver_margin_abs;

extern float window_x_abs;
extern float window_y_abs;

extern float window_width_abs;
extern float window_height_abs;

extern float window_content_x_padding_abs;
extern float window_content_y_padding_abs;
extern float window_content_x_abs;
extern float window_content_y_abs;
extern float window_content_width_abs;
extern float window_content_height_abs;
extern float window_content_x_indent_abs;
extern float window_content_title_height_abs;
extern float window_content_text_line_height_abs;
extern float window_content_text_y_abs;

extern float window_border_abs;
extern float window_border_radius_abs;

extern float window_input_height_abs;
//

} // namespace Layout

#endif // LAYOUT_H
