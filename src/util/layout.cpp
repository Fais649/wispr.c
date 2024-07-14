#include "layout.h"

namespace Layout {

// NEVER TOUCH
float display_width = 960;
float display_height = 540;
epd_mode_t display_mode_fastest = epd_fast;
epd_mode_t display_mode_quality = epd_quality;

float dock_ver_margin = 0.03;
float dock_hor_margin = .02;

// NO CALLING, ONLY TOUCHING
float window_hor_margin = 0.02;
float window_ver_margin = 0.04;
float window_border = 4;
float window_content_x_padding = 0.05;
float window_content_y_padding = 0.07;
float window_border_radius = 0.05;
float window_content_x_indent = 0.04;
float window_content_title_height = 0.2;
float window_content_text_lines = 8;

// modifier < 1 = left/up; modifier > 1 = right/down
float shadow_x_modifier = .8;
float shadow_y_modifier = 1.5;
float shadow_height_modifier = 1;
float shadow_width_modifier = 1;
//

float dock_height = 0.08;
float dock_width = 0.115;
float dock_content_padding = 0.15;
float dock_border_radius = 0.5;

float dock_right_width = 0.48;
float dock_right_height = dock_height;
float dock_right_content_padding = dock_content_padding * 0.5;
float dock_right_border_radius = 0.5;

float sleep_icon_color_abs = TFT_WHITE;
float sleep_icon_content_color_abs = TFT_BLACK;

float sleep_icon_radius_abs = 20;

char sleep_icon_char = 0x78;
char sleep_icon[2] = {sleep_icon_char, '\0'};

char finger_right_icon_char = 0x4B;
char finger_icon[2] = {finger_right_icon_char, '\0'};

float sleep_icon_size = 1.75;

// NO TOUCHING, ONLY CALLING
float dock_ver_margin_abs = dock_ver_margin * display_height;
float dock_hor_margin_abs = dock_hor_margin * display_width;

float dock_height_abs = display_height * dock_height;
float dock_width_abs = display_width * dock_width;
float dock_border_radius_abs = dock_height_abs * dock_border_radius;

float dock_x_abs =
    (display_width * 0.5) -
    ((dock_width_abs + dock_right_width_abs + dock_hor_margin_abs) * 2);
float dock_y_abs = display_height - dock_height_abs - dock_ver_margin_abs;

float dock_content_x_padding_abs = dock_content_padding * dock_width_abs;
float dock_content_y_padding_abs = dock_content_padding * dock_height_abs;

float dock_right_width_abs = dock_right_width * display_width;
float dock_right_height_abs = dock_right_height * display_height;
float dock_right_x_abs = (dock_x_abs + dock_width_abs + (dock_hor_margin_abs));
float dock_right_y_abs = dock_y_abs;

float dock_right_content_x_padding_abs =
    dock_right_content_padding * dock_right_width_abs * 0.5;
float dock_right_content_y_padding_abs =
    dock_right_content_padding * dock_right_height_abs * 2;
float dock_right_border_radius_abs =
    dock_right_border_radius * dock_right_height_abs;

float window_hor_margin_abs = display_width * window_hor_margin;
float window_ver_margin_abs = display_height * window_ver_margin;

float window_x_abs = window_hor_margin_abs;
float window_y_abs = window_ver_margin_abs;

float window_width_abs = display_width - window_x_abs - window_hor_margin_abs;
float window_height_abs = display_height - window_y_abs -
                          window_ver_margin_abs - dock_height_abs -
                          (dock_ver_margin_abs * 2);

float window_content_x_padding_abs =
    window_content_x_padding * window_width_abs;
float window_content_y_padding_abs =
    window_content_y_padding * window_height_abs;
float window_content_x_abs = window_x_abs + window_content_x_padding_abs;
float window_content_y_abs = window_y_abs + window_content_y_padding_abs;
float window_content_width_abs =
    window_width_abs - 2 * window_content_x_padding_abs;
float window_content_height_abs =
    window_height_abs - 2 * window_content_y_padding_abs;
float window_content_x_indent_abs =
    window_content_width_abs * window_content_x_indent;
float window_content_title_height_abs =
    window_content_title_height * window_content_height_abs;
float window_content_text_line_height_abs =
    (window_content_height_abs - window_content_title_height_abs) /
    window_content_text_lines;

float window_border_abs = window_border;
float window_border_radius_abs = window_height_abs * window_border_radius;

const m5gfx::IFont *window_content_title_font = nullptr;
const m5gfx::IFont *window_content_text_font = nullptr;
const m5gfx::IFont *dock_symbol_font = &m5gfx::fonts::WispR24;
float window_content_title_size = 7.2;
float window_content_text_size = 4;
float dock_text_size = 4;

float sleep_icon_x_abs = dock_x_abs * 0.5;
float sleep_icon_y_abs = dock_y_abs;
float sleep_icon_wrapper_x_abs = sleep_icon_x_abs + sleep_icon_radius_abs * .5;
float sleep_icon_wrapper_y_abs = sleep_icon_y_abs + sleep_icon_radius_abs * .55;
//

} // namespace Layout