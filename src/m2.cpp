// #include <M5Unified.h>
// #include "CardKb.h" // Assuming this is your custom keyboard library

// CardKb keyboard;
// bool isPointInRect(const m5::touch_point_t &p, int x, int y, int w, int h);
// void handleInputAndNavigation();
// void handleTouchInput();
// void renderChecklist();
// void clearInput();
// void renderInput();
// void renderChecklistItem(int index, bool isSelected);

// const int maxItems = 100;
// String checklist[maxItems];
// bool completed[maxItems];
// int itemCount = 0;
// int currentPosition = -1; // -1 indicates the input area

// String currentInput = "";

// // Screen and layout dimensions
// int cursorStartX = 10;
// int cursorStartY = 10;
// int cursorStepY = 30;
// int inputOffsetY = 450;
// int itemStartOffsetY = 60;
// int itemHeight = 50;
// int itemWidth = 900;
// int textSize = 3;

// // Colors
// int textColorDefault = 0;
// int textColorCompleted = 15;

// void setup()
// {
//   M5.begin();
//   display.clear(TFT_BLACK);
//   display.setRotation(1);

//   for (int i = 0; i < maxItems; ++i)
//   {
//     completed[i] = false;
//   }

//   renderChecklist();
//   renderInput();
// }

// void loop()
// {
//   M5.update();
//   handleInputAndNavigation();
//   handleTouchInput();
// }

// void handleInputAndNavigation()
// {
//   keyboard.scan();

//   if (keyboard.isKeyPressed())
//   {
//     char key = keyboard.getChar();
//     if (key == 13)
//     {
//       if (itemCount < maxItems)
//       {
//         checklist[itemCount] = currentInput;
//         completed[itemCount] = false;
//         renderChecklistItem(itemCount, false);
//         itemCount++;
//         currentInput = "";
//       }
//       clearInput();
//       renderInput();
//     }
//     else if (key == 182) // Move up
//     {
//       if (currentPosition > -1)
//       {
//         int previousPosition = currentPosition;
//         currentPosition--;
//         renderChecklistItem(previousPosition, false);
//         if (currentPosition == -1)
//         {
//           renderInput();
//         }
//         else
//         {
//           renderChecklistItem(currentPosition, true);
//         }
//       }
//     }
//     else if (key == 181) // Move down
//     {
//       if (currentPosition < itemCount - 1)
//       {
//         int previousPosition = currentPosition;
//         currentPosition++;
//         if (previousPosition == -1)
//         {
//           renderInput();
//         }
//         else
//         {
//           renderChecklistItem(previousPosition, false);
//         }
//         renderChecklistItem(currentPosition, true);
//       }
//     }
//     else
//     {
//       currentInput += key;
//       renderInput();
//     }
//   }
// }

// void handleTouchInput()
// {
//   if (M5.Touch.getDetail().wasClicked())
//   {
//     auto point = M5.Touch.getTouchPointRaw(0);
//     for (int i = 0; i < itemCount; ++i)
//     {
//       if (isPointInRect(point, cursorStartX, itemStartOffsetY + i * cursorStepY, itemWidth, itemHeight))
//       {
//         completed[i] = !completed[i];
//         renderChecklistItem(i, currentPosition == i);
//         break;
//       }
//     }
//   }
// }

// void renderChecklist()
// {
//   display.fillRect(cursorStartX, cursorStartY, itemWidth, itemStartOffsetY - cursorStartY, TFT_BLACK); // Clear the checklist header area
//   display.setTextSize(textSize);
//   display.setTextColor(textColorDefault);
//   display.setCursor(cursorStartX, cursorStartY);
//   display.print("Checklist:");

//   for (int i = 0; i < itemCount; ++i)
//   {
//     renderChecklistItem(i, currentPosition == i);
//   }
// }

// void   renderChecklistItem(int index, bool isSelected)
// {
//   if (isSelected)
//   {

//     display.setEpdMode(epd_fastest);
//   }
//   else
//   {
//     display.setEpdMode(epd_fastest);
//   }
//   int itemY = itemStartOffsetY + index * cursorStepY;
//   display.fillRect(cursorStartX, itemY, itemWidth, cursorStepY, TFT_BLACK); // Clear the item area

//   if (completed[index])
//   {
//     display.setTextColor(textColorCompleted); // Inverted color
//   }
//   else
//   {
//     display.setTextColor(textColorDefault);
//   }

//   display.setCursor(cursorStartX, itemY);

//   if (isSelected)
//   {
//     display.print(completed[index] ? "[_]" : "[_]");
//   }
//   else
//   {
//     display.print(completed[index] ? "[X]" : "[ ]");
//   }

//   display.print(" " + checklist[index]);
// }

// void clearInput()
// {
//   display.setEpdMode(epd_fastest);
//   display.fillRect(cursorStartX, cursorStartY + inputOffsetY, itemWidth, cursorStepY, TFT_BLACK);
// }

// void renderInput()
// {
//   display.setEpdMode(epd_fastest);
//   display.setTextSize(textSize);
//   display.setTextColor(textColorDefault);
//   display.setCursor(cursorStartX, cursorStartY + inputOffsetY);
//   display.print("Input: " + currentInput);
// }

// bool isPointInRect(const m5::touch_point_t &p, int x, int y, int w, int h)
// {
//   return p.x > x && p.x < x + w && p.y > y && p.y < y + h;
// }