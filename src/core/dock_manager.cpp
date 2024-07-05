#include "dock_manager.h"

void DockManager::addApp(Application *app)
{
    apps.push_back(app);
    appNames.push_back(app->getAppName()); // Using typeid to get a unique name for each app
}

void DockManager::removeApp(Application *app)
{
    auto it = std::find(apps.begin(), apps.end(), app);
    if (it != apps.end())
    {
        int index = std::distance(apps.begin(), it);
        apps.erase(it);
        appNames.erase(appNames.begin() + index); // Optional: Remove the corresponding app name
    }
}

void DockManager::render()
{
    int dockHeight = M5EPD_DOCK_HEIGHT; // Example icon size
    int x = 60;
    int y = display.height() - dockHeight * 1.1;
    int dockWidth = display.width() * 0.3;
    int round = dockHeight / 2;

    Serial.println("ENTER RENDER");
    display.setWindow(display.width() * 0.25, display.height() - dockHeight, display.width() * 0.50, dockHeight);
    if (!isDirty)
    {
        return;
    }
    Serial.println("WINDOW SET");

    // if (!windowManager->hasActiveWindow())
    // {
    //     Serial.println("NO ACTIVE WINDOW");
    //     display.setEpdMode(epd_fastest);
    //     display.setWindow(0, 0, display.width(), display.height() - dockHeight);
    //     display.fillRect(0, 0, display.width(), display.height() - dockHeight, TFT_BLACK);
    //     display.display();
    //     display.display();
    //     display.display();
    // }

    int iconX = x + 70 * apps.size() - 35;
    display.fillRoundRect(-x, y, display.width() * 0.275, dockHeight, round, TFT_WHITE);
    for (size_t i = 0; i < apps.size(); ++i)
    {
        int circleRadius = dockHeight / 3;
        iconX = x + 70 * i + 35;
        int iconY = y + dockHeight / 2;

        if (i == selectedAppIndex)
        {
            display.fillCircle(iconX, iconY, 20, TFT_BLACK);
            display.fillCircle(iconX, iconY, circleRadius * .75, TFT_WHITE);
            display.setEpdMode(epd_fastest);
        }
        else
        {
            display.fillCircle(iconX, iconY, 20, TFT_BLACK);
        }

        display.setTextColor(TFT_WHITE, TFT_BLACK);
        display.setCursor(iconX, iconY + dockHeight + 2);
    }

    updateDateBattery();

    if (isFirstRender)
    {
        display.setEpdMode(epd_fastest);
        isFirstRender = false;
    }

    display.display();
    display.display();
    display.display();
    isDirty = false;
}

void DockManager::updateDateBattery()
{
    int x = 60;
    int y = display.height() - dockHeight * 1.1;
    int dockWidth = display.width() * 0.3;
    int round = dockHeight / 2;

    m5::rtc_date_t date;
    M5.Rtc.getDate(&date);
    String year = String(date.year);
    String month = String(date.month);
    String day = String(date.date);

    display.setTextSize(3);
    display.setTextColor(TFT_BLACK, TFT_WHITE);
    int mv = getBatteryVoltage();
    Serial.println("VOLTAGE");
    Serial.println(mv);
    String battery = String(averageBatteryLevel(mv));

    String batterySymbol = String("%");
    if (M5.Power.isCharging())
    {
        batterySymbol = "|";
    }

    display.fillRoundRect(display.width() * 0.65, y + dockHeight * 0.1, display.width() * 0.5, dockHeight * 0.95, dockHeight * .5, TFT_WHITE);
    display.drawString(battery + batterySymbol + " ; " + year + "-" + month + "-" + day, display.width() * 0.68, (y + dockHeight * 0.35));
}

void DockManager::batteryBegin()
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(BAT_ADC_CHANNEL, ADC_ATTEN_DB_12);
    _adc_chars = (esp_adc_cal_characteristics_t *)calloc(
        1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12,
                             BASE_VOLATAGE, _adc_chars);

    uint32_t raw_value = adc1_get_raw(ADC1_CHANNEL_7);
    uint32_t measured_voltage = esp_adc_cal_raw_to_voltage(raw_value, _adc_chars);
    float actual_voltage = 4.37 * 1000; // Convert 4.37V to mV (assuming the battery is fully charged and the full charge voltage is 4.37V)
    float scale = actual_voltage / measured_voltage;
    Serial.println("SCALE");
    Serial.println(scale);
}

uint32_t DockManager::getBatteryVoltage()
{
    uint32_t adc_raw_value = 0;
    for (uint16_t i = 0; i < ADC_FILTER_SAMPLE; i++)
    {
        adc_raw_value += adc1_get_raw(BAT_ADC_CHANNEL);
    }

    adc_raw_value = adc_raw_value / ADC_FILTER_SAMPLE;

    uint32_t voltage =
        (uint32_t)(esp_adc_cal_raw_to_voltage(adc_raw_value, _adc_chars) /
                   SCALE);

    filteredVoltage = ALPHA * voltage + (1 - ALPHA) * filteredVoltage;
    return voltage;
}

int DockManager::averageBatteryLevel(int mv)
{
    const int minVoltage = BASE_VOLATAGE; // Minimum voltage in mV
    const int maxVoltage = 4200;          // Maximum voltage in mV

    // Ensure voltage is within range
    if (mv < minVoltage)
        mv = minVoltage;
    if (mv > maxVoltage - 20)
        mv = maxVoltage;

    // Calculate charge level percentage
    int level = (mv - minVoltage) * 100 / (maxVoltage - minVoltage);
    return level;
}

void DockManager::handleTouchEvent(int x, int y)
{
    if (x < dockHeight)
    {
        int index = (y / (60)) - 1;
        if (index >= 0 && index < apps.size() && y >= 40)
        {
            if (index == selectedAppIndex)
            {
                Serial.println("REMOVE WINDOW");
                windowManager->removeWindow(apps[index]);
                windowManager->setDirty();
                windowManager->render();
                delay(50);
                selectedAppIndex = -1;
            }
            else
            {
                selectedAppIndex = index;
                windowManager->addWindow(apps[index]);
                windowManager->switchToWindow(apps[index]); // Switch to the selected app
            }
            setDirty();
            render();
        }
    }
}

void DockManager::setDirty()
{
    isDirty = true;
}