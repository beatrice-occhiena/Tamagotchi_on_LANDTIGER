/******************************************************************************

	AUTORE  :   		Paolo BERNARDI
	MODIFICATO_DA: 	Beatrice Occhiena s314971
	CORSO   :   		Architetture dei sistemi di elaborazione 22-23
	DOCENTE :   		Sanchez Sanchez Edgar Ernesto

*******************************************************************************/
#ifndef MUSIC_H
#define MUSIC_H

//DEFINIZIONI
//-----------
#define SPEEDUP 			1.6
#define TIMERSCALER 	1
#define SECOND 				0x17D7840*TIMERSCALER

typedef enum durat_ts
{
	time_semibiscroma = (unsigned int)(SECOND * SPEEDUP / 64.0f + 0.5), // 1/128
	time_biscroma = (unsigned int)(SECOND * SPEEDUP / 32.0f + 0.5), // 1/64
	time_semicroma = (unsigned int)(SECOND * SPEEDUP / 16.0f + 0.5), // 1/32
	time_croma = (unsigned int)(SECOND * SPEEDUP / 8.0f + 0.5), // 1/16
	time_semiminima = (unsigned int)(SECOND * SPEEDUP / 4.0f + 0.5), // 1/4
	time_minima = (unsigned int)(SECOND * SPEEDUP / 2.0f + 0.5), // 1/2
	time_semibreve = (unsigned int)(SECOND * SPEEDUP + 0.5), // 1
} durat_t;

typedef enum frequencies
{
	//timer_count = 25MHz/(freq_nota*45)
	//note personalizzate
	nota1 = 8270,
	nota2 = 8300,
	nota3 = 9780,
	nota4 = 5800,
	nota5 = 6000,
	nota6 = 6520,
	nota7 = 7000,
	nota8 = 10000,
	nota9 = 10270,
	nota0 = 12000,
	//note canoniche tradotte
	a2b = 5351,	
	b2 = 4500,	
	c3b = 4370,	
	c3 = 4240,	
	d3 = 3779,	
	e3 = 3367,	
	f3 = 3175,	
	g3 = 2834,	
	a3b = 2670,
	//no sound
	pause = 0
} freq_t;

//Una nota è caratterizzata da:
//- frequenza
//- durata
//-----------------------------
typedef struct note_t{
	freq_t freq;
	durat_t durat;
} note_t;

//ESPORTAZIONI DA "music.c"
//-------------------------
#define food_sound_len		3
#define cuddle_sound_len	4
#define death_sound_len 	3
extern note_t click;
extern note_t food_sound[food_sound_len];
extern note_t cuddle_sound[cuddle_sound_len];
extern note_t death_sound[death_sound_len];

//FUNIONI
//-------
void playNOTE(note_t note);
void playSOUND(note_t *sound,int len);
int isNOTEPlaying(void);

#endif
/* EOF */
