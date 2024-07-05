#ifndef HARDWARE_H
#define HARDWARE_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "globals.h"
#include "power.h"
#include <Arduino.h>
// #include "ports.h"
#include "display.h"
// #include "touch_panel.h"
// #include "sd_card.h"
// #include "battery.h"
#include "rclock.h"
// #include "buttons.h"
#include <CardKb.h>
#include <esp_sleep.h>

// extern Power power;
extern Display display;
// extern Ports ports;
// extern Battery battery;
extern RClock rclock;
// extern TouchPanel touchPanel;
// extern SDCard sdCard;
// extern Buttons buttons;
extern CardKb keyboard;

#endif