#ifndef _ATTINY_TEST1_H
#define _ATTINY_TEST1_H

#include <avr/pgmspace.h>
#include <ssd1306xled.h>

extern const uint8_t Dot_count = 6;
extern const uint8_t Dice_size = 49;
//功能按钮引脚
extern const uint8_t F_button = 1;
//方向按钮引脚(ADC检测A0,A3)
/*
  analogRead(A0)>=750 && analogRead(A3)<950时
  向下
  analogRead(A0) > 500 && analogRead(A0) < 750时
  向上
   analogRead(A3)>=750 && analogRead(A3)<950时
  向右
  analogRead(A3) > 500 && analogRead(A3) < 750时
  向左
*/

//骰子点数对应的位置(x,y)
extern const uint8_t Dot_pos[6][6][2] {
  {{16,2}},
  {{8,2},{24,2}},
  {{0,0},{16,2},{32,4}},
  {{8,1},{24,1},{8,3},{24,3}},
  {{0,0},{32,0},{16,2},{0,4},{32,4}},
  {{0,0},{32,0},{0,2},{32,2},{0,4},{32,4}}
};
//骰子图形(8x8)
extern const uint8_t Dot_img[2][16]{
  //点的上半部分
  {0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF},
  //点的下半部分
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,0xF8,0xF8,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF}
};

void delay_us(uint16_t us){
  while(us--)
    for(uint16_t i = 0; i < 1000; ++i);
}



#endif
