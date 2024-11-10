/******************************************************************************

	AUTORE  :   		Paolo BERNARDI
	MODIFICATO_DA: 	Beatrice Occhiena s314971
	CORSO   :   		Architetture dei sistemi di elaborazione 22-23
	DOCENTE :   		Sanchez Sanchez Edgar Ernesto

*******************************************************************************/
#include "music.h"
#include "../timer/timer.h"
#include "LPC17xx.h"

/******************************************************************************
	FUNZIONE
	--------
		-	Riprogramma il timer2 che gestisce DAC e speaker perché
			venga riprodotta una nuova nota
		- Riprogramma il timer3 che ne gestisce la durata
			
*******************************************************************************/
void playNOTE(note_t note)
{
	//se la nota non corrisponde a una pausa
	if(note.freq != pause)
	{
		//update timer2
		reset_timer(2);
		init_timer(2, note.freq);
		enable_timer(2);
	}
	
	//update timer3
	reset_timer(3);
	init_timer(3, note.durat);
	enable_timer(3);
}

/******************************************************************************
	FUNZIONE
	--------
		-	Riproduce un suono, ossia una sequenza di note, con il giusto timing
			
*******************************************************************************/
void playSOUND(note_t *sound,int len){
	
	int note_i = 0;
	
	while(note_i<len){
		//se la nota precedente è finita
		if(!isNOTEPlaying()){
			playNOTE(sound[note_i]);
			note_i++;
		}
	}
}

/******************************************************************************
	FUNZIONE
	--------
		-	Controlla rapidamente se la scheda è già impegnata a far suonare una nota, 
			leggendo il bit di enable di TIM2e3 nel TimerControlRegister 
			
*******************************************************************************/
int isNOTEPlaying(void)
{
	int is=0;
	if(LPC_TIM2->TCR!=0) is=1;
	return is;
}

//I MIEI SUONI
//------------
uint16_t SinTable[45] =                                       
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

note_t click = {nota3,time_biscroma};

note_t food_sound[food_sound_len] = 
		{
			{nota1, time_semicroma},
			{nota3, time_semicroma},
			{nota2, time_croma},
		};

note_t cuddle_sound[cuddle_sound_len] = 
		{
			{nota7, time_croma},
			{nota6, time_semicroma},
			{nota5, time_semicroma},
			{nota4, time_semicroma},
		};

note_t death_sound[death_sound_len] =
		{
			{nota9, time_semicroma},
			{nota8, time_semicroma},
			{nota0, time_croma},
		};

