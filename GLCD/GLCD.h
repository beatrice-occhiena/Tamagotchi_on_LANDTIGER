/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			GLCD.h
** Descriptions:		Has been tested SSD1289、ILI9320、R61505U、SSD1298、ST7781、SPFD5408B、ILI9325、ILI9328、
**						HX8346A、HX8347A
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-3-10
** Version:				1.3
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Beatrice Occhiena
** Modified date:		05/01/2023
** Version:					1.0
** Descriptions:		palette e define dalla riga 101
********************************************************************************************************/

#ifndef __GLCD_H 
#define __GLCD_H

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include <stdio.h>

/* Private define ------------------------------------------------------------*/

/* LCD Interface */
#define PIN_EN		(1 << 19)
#define PIN_LE		(1 << 20)
#define PIN_DIR		(1 << 21)
#define PIN_CS      (1 << 22)
#define PIN_RS		(1 << 23)
#define PIN_WR		(1 << 24)
#define PIN_RD		(1 << 25)   

#define LCD_EN(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_EN) : (LPC_GPIO0->FIOCLR = PIN_EN));
#define LCD_LE(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_LE) : (LPC_GPIO0->FIOCLR = PIN_LE));
#define LCD_DIR(x)  ((x) ? (LPC_GPIO0->FIOSET = PIN_DIR) : (LPC_GPIO0->FIOCLR = PIN_DIR));
#define LCD_CS(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_CS) : (LPC_GPIO0->FIOCLR = PIN_CS));
#define LCD_RS(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_RS) : (LPC_GPIO0->FIOCLR = PIN_RS));
#define LCD_WR(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_WR) : (LPC_GPIO0->FIOCLR = PIN_WR));
#define LCD_RD(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_RD) : (LPC_GPIO0->FIOCLR = PIN_RD));

/* Private define ------------------------------------------------------------*/
#define DISP_ORIENTATION  0  /* angle 0 90 */ 

#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

#define  MAX_X  320
#define  MAX_Y  240   

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#define  MAX_X  240
#define  MAX_Y  320   

#endif

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

/******************************************************************************
* Function Name  : RGB565CONVERT
* Description    : 24位转换16位
* Input          : - red: R
*                  - green: G 
*				   - blue: B
* Output         : None
* Return         : RGB 颜色值
* Attention		 : None
*******************************************************************************/
#define RGB565CONVERT(red, green, blue)\
(uint16_t)( (( red   >> 3 ) << 11 ) | \
(( green >> 2 ) << 5  ) | \
( blue  >> 3 ))

/* Private function prototypes -----------------------------------------------*/
void LCD_Initialization(void);
void LCD_Clear(uint16_t Color);
uint16_t LCD_GetPoint(uint16_t Xpos,uint16_t Ypos);
void LCD_SetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t point);
void LCD_DrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color );
void PutChar( uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint16_t charColor, uint16_t bkColor );
void GUI_Text(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color, uint16_t bkColor);



/* I miei dati */

// La mia palette
//---------------------
#define R0					0xF71C
#define R1          0xF69C
#define R2          0xF60C
#define R3          0xF50C
#define R4          0xF40C
#define RR				 	0xF800
#define WW				 	0xFFFF
#define BB					0x0000
#define YY					0xFFE0

// Le mie info immagine
//---------------------
#define petDIM          32
#define petSCALE        3
#define petCENTER_X     70
#define petCENTER_Y     140
//-------------------------
#define battW       18
#define battH       9
#define battSCALE   2
#define batt1_X     48
#define batt2_X     152
#define batt_Y      68
//-------------------------
#define notchW      3*battSCALE
#define notchH      5*battSCALE
#define notch1_X    batt1_X+2*battSCALE
#define notch2_X    batt2_X+2*battSCALE
#define notch_Y     batt_Y+2*battSCALE
#define MAXnotch		4
//-------------------------
#define mealW       6
#define mealH       5
#define snackW      3
#define snackH      6
#define foodSCALE   4
#define food_X      20
#define food_Y      200
//-------------------------
#define heartW			11
#define heartH			10
#define heartSCALE1	2
#define heartSCALE2 4
#define heartX1			109
#define heartY1			116
#define heartX2			98
#define heartY2			98
//-------------------------
#define volW				10
#define volH				12
#define volSCALE		2
#define	volX				6
#define volY				8
//-------------------------
#define lineW				1
#define lineH 			12
#define lineSCALE		volSCALE
#define lineX				28
#define lineY				volY


// Le mie funzioni
//---------------------
void NEW_GAME(void);
void DRAW_Image(uint16_t Xpos,uint16_t Ypos,uint16_t W,uint16_t H,uint16_t scale,uint16_t *IMG);
void UPDATE_Notch(uint16_t color,uint16_t num_batt,uint16_t cnt);
void UPDATE_Volume(uint16_t volume);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
