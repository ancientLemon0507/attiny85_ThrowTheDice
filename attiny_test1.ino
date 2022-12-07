/*摇骰子*/
#include"attiny_test1.h"

struct Dice{
    uint8_t dot;
    uint8_t posX;
    uint8_t posY;
}dice1,dice2;

void init_dice(){
  dice1.dot = dice2.dot = 1;
  dice1.posY = dice2.posY = 1;
  dice1.posX = 10;
  dice2.posX = 69;
}
//绘制骰子背景
void draw_back(){
  for(uint8_t i = dice1.posY; i < dice1.posY+Dice_size/8; ++i){
    SSD1306.ssd1306_setpos(dice1.posX, i);
    SSD1306.ssd1306_send_data_start();
    for(uint8_t j = 0; j < Dice_size; ++j){
      SSD1306.ssd1306_send_byte(0xFF);  
    }
    SSD1306.ssd1306_send_data_stop();
    SSD1306.ssd1306_setpos(dice2.posX, i);
    SSD1306.ssd1306_send_data_start();
    for(uint8_t j = 0; j < Dice_size; ++j){                     
      SSD1306.ssd1306_send_byte(0xFF);  
    }
    SSD1306.ssd1306_send_data_stop();
  }
}
//绘制一个点数方格
void draw_dot(uint8_t x, uint8_t y){
  SSD1306.ssd1306_setpos(x, y);
  SSD1306.ssd1306_send_data_start();
  for(uint8_t i = 0; i < 16; ++i){
    SSD1306.ssd1306_send_byte(Dot_img[0][i]);  
  }
  SSD1306.ssd1306_send_data_stop();
  SSD1306.ssd1306_setpos(x, y+1);
  SSD1306.ssd1306_send_data_start();
  for(uint8_t i = 0; i < 16; ++i){
    SSD1306.ssd1306_send_byte(Dot_img[1][i]);  
  }      
  SSD1306.ssd1306_send_data_stop();
}
//绘制骰子(提供骰子,点数,以及是否还原)
void draw_dice(struct Dice dice){
    for(uint8_t i = 0; i < dice.dot+1; ++i)
        draw_dot(dice.posX+Dot_pos[dice.dot][i][0], dice.posY+Dot_pos[dice.dot][i][1]);
}

void setup() {
  SSD1306.ssd1306_init();
  SSD1306.ssd1306_fillscreen(0); 
  randomSeed(analogRead(0));
  pinMode(F_button,INPUT);
  init_dice();
  draw_back();
}
void loop() {
  static bool flag = false;
  if(!digitalRead(F_button)){
    flag = true;
    //随机骰子
    draw_back();
    dice1.dot = random(0, Dot_count);
    dice2.dot = random(0, Dot_count);
    //SSD1306.ssd1306_setpos(dice1.posX, 0);
    //SSD1306.ssd1306_char_font6x8(49+dice1.dot);
    //SSD1306.ssd1306_setpos(dice2.posX, 0);
    //SSD1306.ssd1306_char_font6x8(49+dice2.dot);
    draw_dice(dice1);
    draw_dice(dice2);
    draw_back();
  } 
  if(flag){
    flag = false;
    draw_dice(dice1);
    draw_dice(dice2);
    uint8_t sum = dice1.dot+dice2.dot+2;
    SSD1306.ssd1306_setpos(dice2.posX-13, 0);
    SSD1306.ssd1306_char_font6x8(48+sum/10);
    SSD1306.ssd1306_setpos(dice2.posX-5, 0);
    SSD1306.ssd1306_char_font6x8(48+sum%10);
  }
}
