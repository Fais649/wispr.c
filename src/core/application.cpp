#include "application.h"

void Application::drawWindow(String window_content_title) {
  display.fillRoundRect(
      (Layout::window_x_abs - Layout::window_border_abs) *
          Layout::shadow_x_modifier,
      (Layout::window_y_abs - Layout::window_border_abs) *
          Layout::shadow_y_modifier,
      (Layout::window_width_abs + 2 * Layout::window_border_abs) *
          Layout::shadow_width_modifier,
      (Layout::window_height_abs + 2 * Layout::window_border_abs) *
          Layout::shadow_height_modifier,
      Layout::window_border_radius_abs, TFT_DARKGREY);

  display.fillRoundRect(
      Layout::window_x_abs - Layout::window_border_abs,
      Layout::window_y_abs - Layout::window_border_abs,
      Layout::window_width_abs + 2 * Layout::window_border_abs,
      Layout::window_height_abs + 2 * Layout::window_border_abs,
      Layout::window_border_radius_abs, TFT_WHITE);

  display.fillRoundRect(Layout::window_x_abs, Layout::window_y_abs,
                        Layout::window_width_abs, Layout::window_height_abs,
                        Layout::window_border_radius_abs * 0.6, TFT_BLACK);

  display.setTextColor(TFT_WHITE);
  display.setFont(Layout::window_content_title_font);
  display.setTextSize(Layout::window_content_title_size);
  
  display.setCursor(Layout::window_x_abs + Layout::window_content_x_padding_abs,
                    Layout::window_y_abs +
                        Layout::window_content_y_padding_abs);
  display.print(window_content_title.c_str());

  display.setFont(Layout::window_content_text_font);
  display.setTextSize(Layout::window_content_text_size);
}