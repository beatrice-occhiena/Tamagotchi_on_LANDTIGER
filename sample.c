/******************************************************************************

	AUTORE  :   Beatrice Occhiena s314971
	CORSO   :   Architetture dei sistemi di elaborazione 22-23
	DOCENTE :   Sanchez Sanchez Edgar Ernesto
	
	------------------------------------------------------------
	
	PROGETTO:		Extra point #1 - Make a Tamagotchi!

*******************************************************************************/

#include "LPC17xx.h"
#include "GLCD/GLCD.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "TouchPanel/TouchPanel.h"
#include "adc/adc.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{	
	SystemInit();  												
  LCD_Initialization();
	joystick_init();
	TP_Init();
	TouchPanel_Calibrate();
	ADC_init();
	//DAC->Speaker init() ----------
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
	//schermata di avvio gioco
	//-------------------------
	NEW_GAME();
	
	//RIT:
	//count = 50ms
	// - polling joystick, touchscreen e potenziometro
	// - priorità 0 per elevata reattività
	//------------------------------------------------
	init_RIT(0x004C4B40);								
	enable_RIT();
	NVIC_SetPriority(RIT_IRQn,0);
	
	//timer 0: 	
	//count = 1s*25MHz = 0x017D7840
	//type = Interrupt & Reset
	// - aging (1s)
	// - update batterie (5s)
	// - refresh animazione idle (1s)
	// - priorità 1 per garantire costanza
	//-------------------------------------
	init_timer(0,0x017D7840); 						    	
	enable_timer(0);
	NVIC_SetPriority(TIMER0_IRQn,1);
	
	//timer 1: 	
	//count = 0.5s*25MHz = 0x00BEBC20
	//type = Interrupt & Reset
	// - animazioni in movimento (0.5s)
	// - priorità minima per permettere l'aging
	// - abilitato solo su richiesta
	//------------------------------------------
	init_timer(1,0x00BEBC20); 						    	
	NVIC_SetPriority(TIMER1_IRQn,2);
	
	//timer 2:
	//count = 25MHz/(freq_nota*45)
	//type = Interrupt & Reset
	// - gestione della freq di ogni nota
	// - priorità max per garantire un suono pulito
	// - abilitato solo su richiesta
	//----------------------------------------------
	NVIC_SetPriority(TIMER2_IRQn,0);
	
	//timer 3:
	//count = 25MHz*durat_nota(s)
	//type = Interrupt & Reset
	// - gestione della durata di ogni nota
	// - priorità max per garantire un suono pulito
	// - abilitato solo su richiesta
	//----------------------------------------------
	NVIC_SetPriority(TIMER3_IRQn,0);
	
	// power down
	//------------
	LPC_SC->PCON |= 0x1;										
	LPC_SC->PCON &= ~(0x2);						
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
