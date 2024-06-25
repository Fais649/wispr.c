// #include "buttons.h"

// Buttons(m5::Button_Class &btnL, m5::Button_Class &btnP, m5::Button_Class &btnR) : BtnL(btnL) : BtnP(btnP) : BtnR(btnR)
// {
//     mutex = xSemaphoreCreateMutex();
// }

// void Buttons::update()
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);

//     BtnL.read();
//     BtnR.read();
//     BtnP.read();

//     xSemaphoreGive(mutex);
// }
