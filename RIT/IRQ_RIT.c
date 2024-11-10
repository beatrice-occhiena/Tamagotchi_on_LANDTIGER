/******************************************************************************

	AUTORE  :   Beatrice Occhiena s314971
	CORSO   :   Architetture dei sistemi di elaborazione 22-23
	DOCENTE :   Sanchez Sanchez Edgar Ernesto
	
	------------------------------------------------------------
	
	FILE INFO:	Gestione interrupt del RIT

*******************************************************************************/

#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"
#include "../adc/adc.h"
#include "../MyMusic/music.h"


//VARIABILI GLOBALI ESTERNE
//--------------------------
extern int ss, mm, hh;
extern int happiness, satiety;
extern int VOL;
extern int eating;
extern int cuddling;
extern int running;
extern int alive;
extern int is_meal;
extern int is_snack;
extern uint16_t meal[mealW*mealH];
extern uint16_t snack[snackW*snackH];

/******************************************************************************
	FUNZIONE
	--------
		-	Priorità IRQ = 0 per garantire la massima reattività
		
		- Gestione polling del potenziometro
			* attiva anche durante le animazioni per permettere la
				regolazione del volume
		
		- Gestione polling del touch screen
			* quando non è in corso alcuna animazione,
				controlla se è stato premuto un punto sul touchpad
				---> 	se il punto appartiene all'area di visualizzazione
							del pet su schermo, triggera l'animazione delle coccole
				
		- Gestione polling del joystick:
			* quando non è in corso alcuna animazione,
				ogni 50ms legge quali pin sono connessi e aggiorna in "position"
				la posizione attuale del joystick
				
			Se il pet è ancora vivo (alive=1):
			* con left-right gestisce la selezione dei bottoni
				del menù del cibo (meal-snack)
			* con select (oppure down se si usa l'emulatore)
				dà l'ok triggerando l'animazione di eating
				---> 	stampa il cibo a schermo e
							abilita il timer 1
			* con touch triggera l'animazione delle coccole
		
			Se il pet è morto (alive=0):
			* con select (oppure down se si usa l'emulatore)
				ripristina tutte le variabili di stato e riavvia il gioco

*******************************************************************************/
void RIT_IRQHandler (void)
{					
	static int J_select=0;
	static int J_left = 0;
	static int J_right = 0;
	static int position=0;	//0=null,1=left,2=right
	
	//potenziometro spostato
	//----------------------
	ADC_start_conversion();	
	
	//se il pet è ancora vivo e nessuna animazione è in corso
	if(alive && !cuddling && !eating && !running){
		
		//touch screen premuto
		//--------------------
		if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
			
			//se il punto premuto appartiene all'area di visualizzazione del pet
			if(display.x>=petCENTER_X && display.x<=petCENTER_X+petDIM*petSCALE){
				if(display.y>=petCENTER_Y && display.y<=petCENTER_Y+petDIM*petSCALE){
					
					//triggero l'animazione delle coccole
					//-----------------------------------
					
					//aggiorno lo stato del pet
					//(durante l'animazione l'età cresce ma le batterie non diminuiscono)
					cuddling = 1;
					
					//abilito il TIMER1
					//per avviare l'animazione in movimento
					enable_timer(1);
				}
			}
		}
		
		//joystick a sinistra
		//--------------------
		if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
			
			J_left++;
			position=1;
			switch(J_left){
			case 1:
					//per la prima volta
					//evidenzia il bottone selezionato
					GUI_Text(40, 292, (uint8_t *) "Meal", White, Black);
					GUI_Text(160, 292, (uint8_t *) "Snack", Black, White);
					break;
			default:
					//ancora a sinistra
					//do nothing
					break;
			}
		}else{
			//se cambio posizione
			J_left=0;
		}
		
		//joystick a destra
		//--------------------
		if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
			
			J_right++;
			position=2;;
			switch(J_right){
			case 1:
					//per la prima volta
					//evidenzia il bottone selezionato
					GUI_Text(40, 292, (uint8_t *) "Meal", Black, White);
					GUI_Text(160, 292, (uint8_t *) "Snack", White, Black);
					break;
			default:
					//ancora a destra
					//do nothing
					break;
			}
		}else{
			//se cambio posizione
			J_right=0;
		}
	
	}
	
	//se nessuna animazione in corso
	if(!cuddling && !eating && !running){
		
		//joystick schiacciato
		// - funzione select o down -
		// poiché l'emulatore non supporta la select
		//-------------------------------------------
		if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 || (LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
			
			J_select++;
			
			switch(J_select){
			case 1:
					//per la prima volta
					//-------------------
					
					//SELEZIONE MENU - pet vivo
					//--------------------------
					if(alive==1){
						//ripristino l'aspetto standard dei bottoni
						GUI_Text(40, 292, (uint8_t *) "Meal", Black, White);
						GUI_Text(160, 292, (uint8_t *) "Snack", Black, White);
				
						//triggero l'animazione del cibo
						//se ho precedentemente selezionato almeno uno dei due bottoni
						//-------------------------------------------------------------
						if(position!=0){
							
							//emetto il suono del click
							if(VOL!=0) playNOTE(click);
							
							//aggiorno lo stato del pet
							//(durante l'animazione l'età cresce ma le batterie non diminuiscono)
							eating = 1;
							
							//stampo il cibo a schermo
							//e setto il flag per il tipo di cibo
							if(position==1){
								DRAW_Image(food_X,food_Y,mealW,mealH,foodSCALE,meal);
								is_meal = 1;
								is_snack = 0;
							}else{
								DRAW_Image(food_X,food_Y,snackW,snackH,foodSCALE,snack);
								is_snack = 1;
								is_meal = 0;
							}
							
							//abilito il TIMER1
							//per avviare l'animazione in movimento
							enable_timer(1);
							
							//ripristino la posizione neutrale
							position = 0;
						}
					}
					
					//RESET - pet morto
					//------------------
					else{
						ss=0;
						mm=0;
						hh=0;
						happiness=4;
						satiety=4;
						alive=1;
						NEW_GAME();
						reset_timer(0);
						enable_timer(0);
					}
					break;
			default:
					//ancora schiacciato
					//do nothing
					break;
			}
		}else{
			//se smetto di premere
			J_select=0;
		}
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
