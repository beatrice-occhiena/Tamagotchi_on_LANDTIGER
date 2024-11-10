/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:       IRQ_adc.c
** Modified by:			Beatrice Occhiena
** Modified date:		18/01/2023
** Version:					1.0
** Descriptions:		lettura A/D del potenziometro per la regolazione del volume
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../GLCD/GLCD.h"

extern int VOL;
uint16_t AD_trad;   
uint16_t AD_current = 0;
uint16_t AD_last = 0;

void ADC_IRQHandler(void) {
	
	static int cnt = 0;
	
	//Legge lo specifico valore corrente di tensione appena tradotto
	//dal registro ADGDR del convertitore
  AD_trad = ((LPC_ADC->ADGDR>>4) & 0xFFF);
	
	/********************************************************************
		Livelli di volume previsti: {mute,1,2,3}
	
			- l'intervallo di tensioni convertite viene diviso in 4 parti:
				0x000-0x1ff, 0x200-0x7ff, 0x800-0xdff, 0xe00-0xfff
	
			- gli intervalli sono diversi in grandezza ma dimesionati per
				adattarli alla scarsa linearità del potenziometro agli estremi
			
	********************************************************************/
	if(AD_trad<=0x1ff){ //intervallo n^0
		AD_trad = 0;
	}
	else if(AD_trad<=0x7ff){ //intervallo n^1
		AD_trad=1;
	}
	else if(AD_trad<=0xdff){ //intervallo n^2
		AD_trad=2;
	}
	else if(AD_trad<=0xfff){ //intervallo n^3
		AD_trad=3;
	}
	
	/************************************************************
		Gestione dello sfarfallamento:
		- pur tenendo fisso il potenziometro, ogni tot secondi
			questo emette un vaolre molto fuori range, generando
			un falso segnale di cambio intervallo
			--->  prima di confermare il nuovo valore di AD_curr
						controllo il contatore
	************************************************************/
	if(AD_trad != AD_last){
		//se provengo da un intervallo diverso
		if(cnt <= 9){
			//se sono qui da meno di 10 rintocchi
			//è possibile si tratti di sfarfallamento
			//---> non cambio intervallo
			//---> ma aumento il contatore
			AD_current = AD_last;
			cnt++;
		}else{
			//il risultato è sato confermato dopo 150ms
			//---> cambio intervallo
			//---> resetto il contatore
			AD_current = AD_trad;
			cnt=0;
		}
	}
	
	//Se il potenziometro è stato spostato al livello successivo
  if(AD_current != AD_last){
		
		//Aggiorno il disegno a schermo
		UPDATE_Volume(AD_current);
		
		//Aggiorno la variabile globale che controlla il volume
		if(AD_current == 0) VOL=0;
		else if(AD_current == 1) VOL=7;
		else if(AD_current == 2) VOL=3;
		else VOL=1;
		AD_last = AD_current;
  }	
}
