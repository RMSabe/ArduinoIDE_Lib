/*
  ST7920 Driver Test.

  Author: Rafael Sabe
  Email: rafaelmsabe@gmail.com
*/

#include <globldef.h>
#include <math.h>

#include <st7920.hpp>

#define LCD_DB0 14U
#define LCD_DB1 15U
#define LCD_DB2 16U
#define LCD_DB3 17U
#define LCD_DB4 34U
#define LCD_DB5 35U
#define LCD_DB6 36U
#define LCD_DB7 37U
#define LCD_RS 38U
#define LCD1_E 26U

__attribute__((aligned(PTR_SIZE_BITS))) ST7920 st7920(LCD_DB0, LCD_DB1, LCD_DB2, LCD_DB3, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7, LCD_RS, LCD1_E);

extern void draw_proc1(void) __PROGMEM_CODE__;
extern void draw_proc2(void) __PROGMEM_CODE__;
extern void draw_proc3(void) __PROGMEM_CODE__;
extern void draw_proc4(void) __PROGMEM_CODE__;

__PROGMEM_CODE__ void setup(void)
{
  st7920.begin();
  st7920.clearDisplay();
  st7920.enableGraphicDisplay(true);
  return;
}

__PROGMEM_CODE__ void loop(void)
{
_l_loop_runtimeloop:

  st7920.bufferSetAll(false);
  draw_proc1();
  st7920.enableGraphicDisplay(true);
  delay(5000);
  st7920.bufferSetAll(false);
  draw_proc2();
  delay(5000);
  st7920.enableGraphicDisplay(false);
  draw_proc3();
  delay(5000);
  st7920.clearText();
  draw_proc4();
  delay(5000);
  st7920.clearText();

  goto _l_loop_runtimeloop;
  return;
}

__PROGMEM_CODE__ void draw_proc1(void)
{
  uintptr_t cx = 0u;
  uintptr_t cy = 0u;
  
  float x = 0.0f;
  float y = 0.0f;

  for(x = 0.0f; x <= 6.28f; x += 0.01f)
  {
    y = sinf(x);

    cx = (uintptr_t) roundf(20.0f*x);
    cy = (uintptr_t) (roundf(32.0f - 28.0f*y));

    st7920.bufferSetPixel(cx, cy, true);
  }

  st7920.bufferPaintAll();
  return;
}

__PROGMEM_CODE__ void draw_proc2(void)
{
  uintptr_t cx = 0u;
  uintptr_t cy = 0u;
  
  float x = 0.0f;

  for(x = 0.0f; x <= 6.28f; x += 0.01f)
  {
    cx = (uintptr_t) (roundf(64.0f - 28.0f*cosf(x)));
    cy = (uintptr_t) (roundf(32.0f - 28.0f*sinf(x)));

    st7920.bufferSetPixel(cx, cy, true);
  }

  for(x = 3.4f; x <= 6.02f; x += 0.01f)
  {
    cx = (uintptr_t) (roundf(64.0f - 18.0f*cosf(x)));
    cy = (uintptr_t) (roundf(34.0f - 14.0f*sinf(x)));

    st7920.bufferSetPixel(cx, cy, true);
  }

  st7920.bufferSetPixel(53, 22, true);
  st7920.bufferSetPixel(53, 23, true);
  st7920.bufferSetPixel(54, 22, true);
  st7920.bufferSetPixel(54, 23, true);

  st7920.bufferSetPixel(73, 22, true);
  st7920.bufferSetPixel(73, 23, true);
  st7920.bufferSetPixel(74, 22, true);
  st7920.bufferSetPixel(74, 23, true);

  st7920.bufferPaintAll();
  return;
}

__PROGMEM_CODE__ void draw_proc3(void)
{
  st7920.setTextCursorPosition(0u, 0u);
  st7920.printText("This is line 00");
  st7920.setTextCursorPosition(0u, 1u);
  st7920.printText("This is line 01");
  st7920.setTextCursorPosition(0u, 2u);
  st7920.printText("This is line 02");
  st7920.setTextCursorPosition(0u, 3u);
  st7920.printText("This is line 03");
  
  return;
}

__PROGMEM_CODE__ void draw_proc4(void)
{
  const uint16_t wtext[] = {0xa5e9, 0xa5d5, 0xa5a1, 0xa5a8, 0xa5eb, 0xa4b5, 0xa4f3, 0x0};

  st7920.setWTextCursorPosition(0u, 0u);
  st7920.printWText(wtext);
  
  return;
}
