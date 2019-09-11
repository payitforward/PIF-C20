/*
 * LCD.c
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */

#include <App/LCD/st7735/imgs.h>
#include <App/LCD/st7735/st7735.h>
#include "LCD.h"
#include "Timer/timer.h"

#define MAX_LCD_APP  15

static uint8_t gFunc_cnt = 0;
static func_t gFunc[MAX_LCD_APP];

void lcd_app_int_0(){
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
    ST7735_WriteString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    ST7735_WriteString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
}

void lcd_app_init_1(){
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
}

void lcd_app_init_2(){
    ST7735_FillScreen(ST7735_BLUE);
    ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
}

void lcd_app_init_3(){
    ST7735_FillScreen(ST7735_RED);
    ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
}

void lcd_app_init_4(){
    ST7735_FillScreen(ST7735_GREEN);
    ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
}

void lcd_app_init_5(){
    ST7735_FillScreen(ST7735_CYAN);
    ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
}

void lcd_app_init_6(){
    ST7735_FillScreen(ST7735_MAGENTA);
    ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
}

void lcd_app_init_7(){
    ST7735_FillScreen(ST7735_YELLOW);
    ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
}

void lcd_app_init_8(){
    ST7735_FillScreen(ST7735_WHITE);
    ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
}

void lcd_app_init_9(){
	ST7735_DrawImage(0, 0, ST7735_WIDTH, ST7735_HEIGHT, (uint16_t*)test_img_128x128);
}

static void LCD_app_change(uint8_t *cnt){
	if(gFunc_cnt < MAX_LCD_APP && gFunc[gFunc_cnt+1] != 0){
		gFunc_cnt++;
	}
	else{
		gFunc_cnt = 0;
	}
	if(gFunc[gFunc_cnt] != 0) gFunc[gFunc_cnt]();
}

void LCD_app(){
	ST7735_Init();

	gFunc[0] = lcd_app_int_0;
	gFunc[1] = lcd_app_init_1;
	gFunc[2] = lcd_app_init_2;
	gFunc[3] = lcd_app_init_3;
	gFunc[4] = lcd_app_init_4;
	gFunc[5] = lcd_app_init_5;
	gFunc[6] = lcd_app_init_6;
	gFunc[7] = lcd_app_init_7;
	gFunc[8] = lcd_app_init_8;
	gFunc[9] = lcd_app_init_9;

	timer_register_callback(LCD_app_change, 500, 0, TIMER_MODE_REPEAT);
}
