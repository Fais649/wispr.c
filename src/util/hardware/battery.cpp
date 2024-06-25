#include "battery.h"

const float Battery::SCALE = 0.5;

Battery::Battery() : is_adc_started(false), adc_chars(nullptr) {
    mutex = xSemaphoreCreateMutex();
}

void Battery::begin() {
    xSemaphoreTake(mutex, portMAX_DELAY);
    if (!is_adc_started) {
        initADC();
        is_adc_started = true;
    }
    xSemaphoreGive(mutex);
}

void Battery::initADC() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(BAT_ADC_CHANNEL, ADC_ATTEN_DB_11);
    adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, BASE_VOLTAGE, adc_chars);
}

uint32_t Battery::getBatteryRaw() {
    uint32_t adc_raw_value = 0;
    xSemaphoreTake(mutex, portMAX_DELAY);
    for (uint16_t i = 0; i < ADC_FILTER_SAMPLE; i++) {
        adc_raw_value += adc1_get_raw(BAT_ADC_CHANNEL);
    }
    xSemaphoreGive(mutex);
    return adc_raw_value / ADC_FILTER_SAMPLE;
}

uint32_t Battery::getBatteryVoltage() {
    uint32_t adc_raw_value = getBatteryRaw();
    return (uint32_t)(esp_adc_cal_raw_to_voltage(adc_raw_value, adc_chars) / SCALE);
}

float Battery::getBatteryPercentage() {
    uint32_t voltage = getBatteryVoltage();
    // Assuming 3.0V (3000mV) is 0% and 4.2V (4200mV) is 100%
    if (voltage < 3000) {
        return 0.0;
    } else if (voltage > 4200) {
        return 100.0;
    } else {
        return (float)(voltage - 3000) / (4200 - 3000) * 100.0;
    }
}