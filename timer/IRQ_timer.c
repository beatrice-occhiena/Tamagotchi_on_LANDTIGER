/******************************************************************************

	AUTORE  :   Beatrice Occhiena s314971
	CORSO   :   Architetture dei sistemi di elaborazione 22-23
	DOCENTE :   Sanchez Sanchez Edgar Ernesto
	
	------------------------------------------------------------
	
	FILE INFO:	Gestione interrupt dei timer 0 e 1	

*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h"
#include "../RIT/RIT.h"
#include "../MyMusic/music.h"


	//VARIABILI GLOBALI
	//------------------
	
	//IMMAGINI importate da "../GLCD/IMAGES.c"
	extern uint16_t idle1[petDIM*petDIM];
	extern uint16_t idle2[petDIM*petDIM];
	extern uint16_t dead1[petDIM*petDIM];
	extern uint16_t dead2[petDIM*petDIM];
	extern uint16_t eating1[petDIM*petDIM];
	extern uint16_t eating2[petDIM*petDIM];
	extern uint16_t heart[heartW*heartH];
	//CONTATORE DI ETA'
	volatile int ss = 0;
	volatile int mm = 0;
	volatile int hh = 0;
	//VARIABILI DI STATO
	int happiness = 4;
	int satiety = 4;
	int VOL = 0;
	//VARIABILI PER GESTIONE ANIMAZIONE
	int alive = 1;							
	volatile int idle = 0;
	volatile int eating = 0;
	volatile int running = 0;
	volatile int cuddling = 0;
	int is_meal = 0;
	int is_snack = 0;


/******************************************************************************
	FUNZIONE
	--------
		-	Priorità IRQ = 1 per mantenere il più costante possibile
			l'avanzamento del tempo
			
		- Ogni 1s aggiorna l'età del pet
		
		- Se nessun'altra animazione in corso:
			* ogni 5s diminuisce di una tacca le batterie
			* ogni 1s aggiorna il frame dell'animazione "idle"
			
				---> 	se il pet sta per morire 
							(almeno una delle batterie con una sola tacca)
							l'animazione standard di idle viene sostituita da un'immagine 
							statica in cui il pet si ferma con espressione arrabbiata
							
				---> 	se il pet muore
							(una delle batterie va a zero)
							il timer 0 viene disabilitato,
							alcune funzionalità del RIT vengono interrotte tramite flag globali,
							l'età si blocca,
							viene triggerata l'animazione di fuga abilitando il timer 1

*******************************************************************************/
void TIMER0_IRQHandler (void)
{
	//Tempo di vita
	char AGEstr[13] = "";
	
	//Update +1s di vita
	ss++;
	if(ss==60){
		ss=0;
		mm++;
		if(mm==60){
			mm=0;
			hh++;
		}
	}
	
	//Refresh del display
	//-------------------
	
	//ogni 1s aggiorno l'età
	sprintf(AGEstr,"AGE %02d:%02d:%02d",hh,mm,ss);
	GUI_Text(71, 13, (uint8_t *) AGEstr, Black, White);
	
	//se non è in conrso un'animazione
	if(!eating && !cuddling){
		
		//ogni 5s aggiorno lo stato
		if(ss%5==0){
			happiness--;
			satiety--;
			UPDATE_Notch(White,1,happiness);
			UPDATE_Notch(White,2,satiety);
		}
		
		//ogni 1s aggiorno l'animazione
		//------------------------------
		if(happiness>1 && satiety>1){
			//animazione pet felice
			if(idle==0){
				DRAW_Image(petCENTER_X,petCENTER_Y,petDIM,petDIM,petSCALE,idle2);
				idle++;
			}else{
				DRAW_Image(petCENTER_X,petCENTER_Y,petDIM,petDIM,petSCALE,idle1);
				idle--;
			}
		}
		else{
			if(happiness!=0 && satiety!=0){
				//animazione statica pet arrabbiato
				DRAW_Image(petCENTER_X,petCENTER_Y,petDIM,petDIM,petSCALE,dead1);
			}
			else{
				//stop aging
				GUI_Text(71, 13, (uint8_t *) AGEstr, White, Black);
				disable_timer(0);
				//trigger animazione pet morto
				running=1;
				alive=0;
				enable_timer(1);
			}
		}
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
	FUNZIONE
	--------
		-	Priorità IRQ = 2 per permettere l'aging durante le animazioni
			del pet che mangia

		- Il timer 1 viene abilitato unicamente per gestire le animazioni
			più lunghe, che altrimenti andrebbero ad appesantire eccessivamente
			le funzioni di gestione degli INT dei timer più reattivi

		- L'animazione da riprodurre viene selezionata tramite flag globali
			* cuddling=1 - animazione delle coccole
			* eating=1 - animazione del cibo
			* running=1/alive=0 - animazione di fuga
		
		- Per le ultime due animazioni segue un modello standard:
			* ogni 0.5s viene stampato a schermo alternatamente prima un frame 
				del pet e poi un rettangolo bianco per simularne la scomparsa
			* ad ogni passo la posizione sullo schermo viene aggiornata
				lungo l'asse orizzontale

		- Al termine di ogni animazione 
			* azzera il contatore di passi
			* disabilita il timer 1
			* aggiorna il risultato dell'animazione
				---> stato delle batterie e flag per enable funzionalità RIT (coccole e cibo)
				---> avviso, bottone di reset ed enable funzionalità RIT (fuga)
			
*******************************************************************************/
void TIMER1_IRQHandler (void)
{
	static uint16_t i, posX = 0;
	static uint16_t passi = 0;
	
	//ANIMAZIONE COCCOLE
	//-------------------
	if(cuddling==1){
		
		if(passi==0){ //tempo 0s
			//disegna a schermo il pet felice
			DRAW_Image(petCENTER_X,petCENTER_Y,petDIM,petDIM,petSCALE,eating2);
		}
		else if(passi==1){ //tempo 0.5s
			//disegna il primo cuoricino piccolo
			DRAW_Image(heartX1,heartY1,heartW,heartH,heartSCALE1,heart);
			//riproduce il suono delle coccole
			if(VOL!=0) playSOUND(cuddle_sound,cuddle_sound_len);
		}
		else if(passi==2){ //tempo 1s
			//disegna il secondo cuore più in grande
			DRAW_Image(heartX2,heartY2,heartW,heartH,heartSCALE2,heart);
		}
		
		//se animazione terminata
		//------------------------
		if(passi==4){ //tempo 2s
	
			//cancello il cuore con un rettangolo bianco
			for(i=0;i<heartH*heartSCALE2;i++){
				LCD_DrawLine(heartX2,heartY2+i,heartX2+heartW*heartSCALE2,heartY2+i,White);
			}
			
			//aumento di una tacca la batteria della felicità
			UPDATE_Notch(Black,1,happiness);
			if(happiness!=4) happiness++;
			
			//resetto le var globali e i timer
			passi=0;
			disable_timer(1);
			cuddling=0;
		}
		else{
			passi++;
		}
			

	}
	
	//ANIMAZIONE CIBO
	//----------------
	if(eating==1){
		
		//suono del cibo
		//---------------
		if(VOL!=0 && passi!=0) playSOUND(food_sound,food_sound_len);
		
		//frame visibile
		//---------------
		if(passi%2==0){
			//andata
			if(passi<=3){
				posX = petCENTER_X - ((passi/2) * ((petCENTER_X-food_X)));
				DRAW_Image(posX,petCENTER_Y,petDIM,petDIM,petSCALE,eating1);
			}
			//ritorno
			if(passi>=4){
				posX = food_X + ((passi/2-2) * ((petCENTER_X-food_X)));
				DRAW_Image(posX,petCENTER_Y,petDIM,petDIM,petSCALE,eating2);
			}
		}
		//frame bianco
		//-------------
		else{
			if(passi!=3){
				for(i=0;i<petDIM*petSCALE;i++){
					LCD_DrawLine(posX,petCENTER_Y+i,posX+petDIM*petSCALE,petCENTER_Y+i,White);
				}
			}
		}
		
		//se animazione terminata
		//------------------------
		if(passi==6){
			
			//aumento di una tacca la batteria corrispondente
			if(is_meal==1){
				UPDATE_Notch(Black,2,satiety);
				if(satiety!=4) satiety++;
			}else if(is_snack==1){
				UPDATE_Notch(Black,1,happiness);
				if(happiness!=4) happiness++;
			}
			passi=0;
			disable_timer(1);
			eating=0;
		}
		else{
			passi++;
		}
	}
	
	//ANIMAZIONE MORTE
	//-----------------
	if(alive==0){
		
		//riproduce il suono della fuga
		if(VOL!=0) playSOUND(death_sound,death_sound_len);
		
		//frame visibile
		//---------------
		if(passi%2==0){
				posX = petCENTER_X + ((passi/2) * ((240-petCENTER_X)/3+1));
				DRAW_Image(posX,petCENTER_Y,petDIM,petDIM,petSCALE,dead2);
		}
		//frame bianco
		//-------------
		else{
			for(i=0;i<petDIM*petSCALE;i++){
				LCD_DrawLine(posX,petCENTER_Y+i,posX+petDIM*petSCALE,petCENTER_Y+i,White);
			}
		}
		
		//se animazione terminata
		//------------------------
		if(passi==7){
	
			GUI_Text(65, 165, (uint8_t *) "Your pet left", Black, White);
			//reset button
			LCD_DrawLine(119,281,119,340,White);
			GUI_Text(40, 292, (uint8_t *) "Meal", White, White);
			GUI_Text(160, 292, (uint8_t *) "Snack", White, White);
			GUI_Text(100, 292, (uint8_t *) "Reset", White, Black);
			passi=0;
			disable_timer(1);
			running=0;
		}
		else{
			passi++;
		}
		
	}
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
	FUNZIONE
	--------
		-	Inizializzato con la funzione PlayNOTE, il timer 2 si occupa di
			inseire, uno per volta, i punti campionati della sinusoide in DACR,
			perché vengano convertiti dal DAC
			---> 	ogni punto della sinusoide viene diviso per la variabile
						globale VOL che, modificando l'ampiezza complessiva della funzione,
						andrà a regolare il volume del suono in unscita
		
		- È il responsabile della frequenza della nota suonata

		- I punti
			
*******************************************************************************/
extern uint16_t SinTable[45];

void TIMER2_IRQHandler (void)
{
		static int ticks=0;
		
		if(VOL!=0) LPC_DAC->DACR = (SinTable[ticks]/VOL)<<6;
		ticks++;
		if(ticks==45) ticks=0;
		LPC_TIM2->IR = 1;			/* clear interrupt flag */
	
}

/******************************************************************************
	FUNZIONE
	--------
		-	Inizializzato con la funzione PlayNOTE, il timer 3 si occupa di fermare
			il timer 2, e quindi la riproduzione della nota, quando questa raggiunge
			la sua durata in secondi
		
		- Per alleggerire il lavoro del NVIC, disabilita anche se stesso
			
*******************************************************************************/
void TIMER3_IRQHandler (void)
{
		disable_timer(2);
		disable_timer(3);
		LPC_TIM3->IR = 1;			/* clear interrupt flag */
	
}

/******************************************************************************
**                            End Of File
******************************************************************************/
