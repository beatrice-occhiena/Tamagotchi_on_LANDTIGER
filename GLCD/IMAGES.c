/******************************************************************************

	AUTORE  :   Beatrice Occhiena s314971
	CORSO   :   Architetture dei sistemi di elaborazione 22-23
	DOCENTE :   Sanchez Sanchez Edgar Ernesto

*******************************************************************************/

/******************************************************************************
	IMMAGINI
	--------
		-	Ho realizzato personalmente le qui presenti pixel art, di dimensione
            massima 32x32 pixel, su un programma di grafica dedicato.
        -   Per convertirle in linguaggio c, le ho prima replicate su un file excel
            programmato appositamente per assegnare a ogni cella contenente una
            lettera un colore, e poi, grazie alle matrici ottenute, ho copiato
            e incollato il tutto su un editor di testo che mi ha aiutato nella formattazione.

        -   Il formato risultante è un vettore di WxH elementi, in cui ciascuno di essi
            codifica un preciso colore RGB565.
        -   Ho definito per comodità tutti i colori della mia palette.

        -   Per facilitare la modifica e la corretta disposizione degli elementi sullo schermo,
            ogni vettore immagine è accompagnato da una serie di definizioni riguardanti
            dimensioni e coordinate spaziali (in GLCD.h)
        -   Queste verranno utilizzate come argomenti della funzione DRAW_image.

*******************************************************************************/

#include "GLCD.h" 

uint16_t idle1[petDIM*petDIM] =
    {
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	BB,	YY,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	BB,	YY,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	YY,	BB,	R0,	R0,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	YY,	YY,	BB,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	YY,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R2,	R2,	YY,	YY,	BB,	R1,	R1,	R2,	BB,	YY,	YY,	R2,	R2,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	YY,	YY,	YY,	BB,	YY,	YY,	YY,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	YY,	BB,	YY,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R4,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	R4,	R3,	R2,	R2,	BB,	R2,	BB,	R2,	BB,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	BB,	R3,	BB,	R3,	R3,	R3,	R4,	BB,	WW,
        WW,	WW,	BB,	R4,	R2,	R2,	R2,	R2,	WW,	WW,	WW,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	WW,	WW,	WW,	R3,	R3,	R3,	R3,	R4,	BB,	WW,
        BB,	BB,	BB,	R4,	R2,	R2,	R2,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	WW,	BB,	BB,	BB,	WW,	R4,	R3,	R3,	R4,	BB,	BB,
        YY,	YY,	BB,	R4,	R2,	R2,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	YY,
        BB,	BB,	BB,	R2,	R2,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	BB,
        YY,	YY,	BB,	R2,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	BB,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	YY,
        BB,	BB,	BB,	R3,	R3,	R3,	R4,	WW,	BB,	BB,	BB,	WW,	R0,	R0,	R0,	BB,	BB,	BB,	R0,	R0,	R0,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R4,	BB,	BB,
        YY,	YY,	YY,	BB,	R3,	R3,	R0,	R0,	WW,	WW,	WW,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	WW,	WW,	WW,	R1,	R1,	R3,	R4,	BB,	YY,	YY,
        WW,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	BB,	YY,	WW,	WW,
        WW,	WW,	WW,	WW,	YY,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	R1,	BB,	BB,	YY,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	YY,	BB,	BB,	BB,	R3,	R3,	R3,	R3,	R2,	R2,	R2,	R2,	R3,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	YY,	BB,	BB,	YY,	BB,	R2,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R4,	R2,	BB,	YY,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	BB,	BB,	YY,	YY,	BB,	BB,	YY,	BB,	R4,	R2,	R4,	R2,	R3,	R2,	R3,	R3,	R3,	R2,	R4,	R2,	R4,	BB,	YY,	BB,	BB,	YY,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	WW,	WW,	BB,	BB,	YY,	BB,	R4,	R2,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R2,	R4,	BB,	YY,	BB,	BB,	YY,	BB,	BB,	WW,	WW,
        WW,	BB,	YY,	YY,	WW,	BB,	YY,	YY,	YY,	BB,	R4,	R4,	R4,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R4,	R4,	R2,	BB,	YY,	YY,	YY,	BB,	YY,	YY,	BB,	WW,
        WW,	YY,	WW,	WW,	WW,	YY,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	YY,	WW,	WW,	YY,	WW,	WW,	YY,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R3,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	R4,	R2,	R2,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	R2,	BB,	YY,	BB,	R4,	R2,	R3,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	BB,	YY,	BB,	R4,	R4,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	BB,	YY,	YY,	YY,	BB,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW
    };

uint16_t idle2[petDIM*petDIM] =
    {
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	BB,	YY,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	BB,	YY,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	BB,	YY,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	YY,	BB,	R0,	R0,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	YY,	YY,	BB,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	YY,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R2,	R2,	YY,	YY,	BB,	R1,	R1,	R2,	BB,	YY,	YY,	R2,	R2,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	YY,	YY,	YY,	BB,	YY,	YY,	YY,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	YY,	BB,	YY,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R4,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	R4,	R3,	R2,	R2,	BB,	R2,	BB,	R2,	BB,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	BB,	R3,	BB,	R3,	R3,	R3,	R4,	BB,	WW,
        WW,	WW,	BB,	R4,	R2,	R2,	R2,	R2,	WW,	WW,	WW,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	WW,	WW,	WW,	R3,	R3,	R3,	R3,	R4,	BB,	WW,
        BB,	BB,	BB,	R4,	R2,	R2,	R2,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	WW,	BB,	BB,	BB,	WW,	R4,	R3,	R3,	R4,	BB,	BB,
        YY,	YY,	BB,	R4,	R2,	R2,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	YY,
        BB,	BB,	BB,	R2,	R2,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	BB,
        YY,	YY,	BB,	R2,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	BB,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R4,	BB,	YY,
        BB,	BB,	BB,	R3,	R3,	R3,	R4,	R4,	R3,	R3,	R3,	R3,	R3,	R0,	R0,	BB,	BB,	BB,	R0,	R0,	R3,	R3,	R3,	R3,	R3,	R4,	R4,	R3,	R3,	R4,	BB,	BB,
        YY,	YY,	YY,	BB,	R3,	R3,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R3,	R4,	BB,	YY,	YY,
        WW,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	BB,	YY,	WW,	WW,
        WW,	WW,	WW,	WW,	YY,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	R1,	BB,	BB,	YY,	WW,	WW,	WW,
        WW,	BB,	BB,	WW,	BB,	BB,	YY,	BB,	BB,	BB,	R4,	R4,	R4,	R4,	R2,	R2,	R2,	R2,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	BB,
        WW,	YY,	BB,	BB,	YY,	YY,	BB,	BB,	YY,	BB,	R4,	R2,	R2,	R2,	R3,	R2,	R3,	R3,	R3,	R2,	R2,	R2,	R4,	BB,	YY,	BB,	BB,	YY,	YY,	BB,	BB,	YY,
        WW,	WW,	YY,	YY,	BB,	WW,	BB,	BB,	YY,	R2,	R2,	R2,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	R2,	R2,	YY,	BB,	BB,	WW,	BB,	YY,	YY,	WW,
        WW,	WW,	WW,	WW,	YY,	BB,	BB,	YY,	BB,	R2,	R2,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R3,	R2,	BB,	YY,	BB,	BB,	YY,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	YY,	YY,	BB,	R3,	R3,	R4,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R4,	R3,	R3,	BB,	YY,	YY,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	R3,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	YY,	YY,	YY,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	R4,	R2,	R2,	BB,	YY,	YY,	YY,	YY,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	R2,	BB,	YY,	BB,	R4,	R2,	R3,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	BB,	YY,	BB,	R4,	R4,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	BB,	YY,	YY,	YY,	BB,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW
    };

uint16_t eating1[petDIM*petDIM] =
    {
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	BB,	YY,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	BB,	YY,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,
        WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	YY,	BB,	R0,	R0,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	YY,	YY,	BB,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	YY,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R2,	R2,	YY,	YY,	BB,	R1,	R1,	R2,	BB,	YY,	YY,	R2,	R2,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	BB,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	YY,	YY,	YY,	BB,	YY,	YY,	YY,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	YY,	BB,	YY,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R4,	BB,	BB,	BB,	WW,	WW,
        WW,	BB,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,	WW,
        WW,	BB,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,	WW,
        WW,	BB,	R4,	R3,	R2,	R2,	BB,	R2,	BB,	R2,	BB,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	BB,	R3,	BB,	R3,	R3,	R3,	R4,	BB,	WW,	WW,
        WW,	BB,	R4,	R2,	R2,	R2,	R2,	WW,	WW,	WW,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	WW,	WW,	WW,	R3,	R3,	R3,	R3,	R4,	BB,	WW,	WW,
        BB,	BB,	R4,	R2,	R2,	R2,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	WW,	BB,	BB,	BB,	WW,	R4,	R3,	R3,	R4,	BB,	BB,	WW,
        YY,	BB,	R4,	R2,	R2,	WW,	BB,	BB,	BB,	YY,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	YY,	BB,	WW,	R3,	R3,	R4,	BB,	YY,	WW,
        BB,	BB,	R2,	R2,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	BB,	WW,
        YY,	BB,	R2,	R3,	R3,	WW,	BB,	YY,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	BB,	R3,	R3,	R3,	WW,	BB,	YY,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	YY,	WW,
        BB,	BB,	R3,	R3,	R3,	R4,	WW,	BB,	BB,	BB,	WW,	R0,	BB,	R0,	BB,	BB,	BB,	R0,	BB,	R0,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        YY,	YY,	BB,	R3,	R3,	R0,	R0,	WW,	WW,	WW,	R0,	R0,	R0,	BB,	R4,	R4,	R4,	BB,	R0,	R0,	R0,	WW,	WW,	WW,	R1,	R1,	R3,	R4,	BB,	YY,	YY,	WW,
        WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R4,	RR,	RR,	RR,	R4,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	BB,	YY,	WW,	WW,	WW,
        WW,	WW,	WW,	YY,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	R1,	BB,	BB,	YY,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	YY,	BB,	BB,	BB,	R3,	R3,	R3,	R3,	R2,	R2,	R2,	R2,	R3,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	YY,	BB,	BB,	YY,	BB,	R2,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R4,	R2,	BB,	YY,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	WW,	WW,
        WW,	BB,	BB,	YY,	YY,	BB,	BB,	YY,	BB,	R4,	R2,	R4,	R2,	R3,	R2,	R3,	R3,	R3,	R2,	R4,	R2,	R4,	BB,	YY,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	WW,
        WW,	BB,	BB,	WW,	WW,	BB,	BB,	YY,	BB,	R4,	R2,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R2,	R4,	BB,	YY,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	WW,
        BB,	YY,	YY,	WW,	BB,	YY,	YY,	YY,	BB,	R4,	R4,	R4,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R4,	R4,	R2,	BB,	YY,	YY,	YY,	BB,	YY,	YY,	BB,	WW,	WW,
        YY,	WW,	WW,	WW,	YY,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	YY,	WW,	WW,	YY,	WW,	WW,	YY,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R3,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	R4,	R2,	R2,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	R2,	BB,	YY,	BB,	R4,	R2,	R3,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	BB,	YY,	BB,	R4,	R4,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	BB,	YY,	YY,	YY,	BB,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW
    };

uint16_t eating2[petDIM*petDIM] =
    {
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	BB,	YY,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	BB,	YY,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	BB,	YY,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	YY,	BB,	R0,	R0,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	YY,	YY,	BB,	R0,	R1,	R1,	R1,	R2,	BB,	YY,	YY,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R2,	R2,	YY,	YY,	BB,	R1,	R1,	R2,	BB,	YY,	YY,	R2,	R2,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	YY,	YY,	YY,	BB,	YY,	YY,	YY,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	YY,	BB,	YY,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R4,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	BB,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	BB,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	WW,
        WW,	WW,	BB,	R4,	R2,	R2,	R2,	BB,	R3,	R3,	R3,	BB,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R3,	R3,	BB,	R3,	R3,	R3,	R4,	BB,	WW,
        WW,	BB,	BB,	R4,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,
        WW,	YY,	BB,	R4,	R2,	R2,	R3,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R4,	BB,	YY,
        WW,	BB,	BB,	R2,	R2,	R3,	BB,	R4,	R4,	R4,	R4,	R4,	BB,	R3,	R3,	R3,	BB,	BB,	R3,	R3,	BB,	R4,	R4,	R4,	R4,	R4,	BB,	R3,	R3,	R4,	BB,	BB,
        WW,	YY,	BB,	R2,	R3,	R3,	R4,	R3,	R3,	R3,	R3,	R4,	R4,	R3,	R3,	BB,	R0,	R0,	BB,	R3,	R4,	R4,	R3,	R3,	R3,	R3,	R4,	R3,	R3,	R4,	BB,	YY,
        WW,	BB,	BB,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R0,	R0,	R0,	R0,	BB,	R0,	R0,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,
        WW,	YY,	YY,	BB,	R3,	R3,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	BB,	R0,	R0,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R3,	R4,	BB,	YY,	YY,
        WW,	WW,	WW,	YY,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	BB,	YY,	WW,	WW,
        WW,	WW,	WW,	WW,	YY,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	R1,	BB,	BB,	YY,	WW,	WW,	WW,
        WW,	BB,	BB,	WW,	BB,	BB,	YY,	BB,	BB,	BB,	R4,	R4,	R4,	R4,	R2,	R2,	R2,	R2,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	BB,	YY,	BB,	BB,	WW,	WW,	BB,
        WW,	YY,	BB,	BB,	YY,	YY,	BB,	BB,	YY,	BB,	R4,	R2,	R2,	R2,	R3,	R2,	R3,	R3,	R3,	R2,	R2,	R2,	R4,	BB,	YY,	BB,	BB,	YY,	YY,	BB,	BB,	YY,
        WW,	WW,	YY,	YY,	BB,	WW,	BB,	BB,	YY,	R2,	R2,	R2,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	R2,	R2,	YY,	BB,	BB,	WW,	BB,	YY,	YY,	WW,
        WW,	WW,	WW,	WW,	YY,	BB,	BB,	YY,	BB,	R2,	R2,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R3,	R2,	BB,	YY,	BB,	BB,	YY,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	YY,	YY,	BB,	R3,	R3,	R4,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R4,	R3,	R3,	BB,	YY,	YY,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	R3,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	BB,	BB,	BB,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	YY,	YY,	YY,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	R4,	R2,	R2,	BB,	YY,	YY,	YY,	YY,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	BB,	R4,	R2,	R2,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	R2,	BB,	YY,	BB,	R4,	R2,	R3,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	R4,	R3,	BB,	YY,	BB,	R4,	R4,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	YY,	BB,	BB,	YY,	YY,	YY,	BB,	BB,	YY,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW
    };

uint16_t dead1[petDIM*petDIM] =
    {
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	RR,	BB,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	BB,	RR,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	RR,	BB,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	BB,	RR,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	RR,	BB,	R0,	R0,	R0,	R1,	R1,	R1,	R2,	BB,	RR,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	RR,	RR,	BB,	R0,	R1,	R1,	R1,	R2,	BB,	RR,	RR,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R2,	R2,	RR,	RR,	BB,	R1,	R1,	R2,	BB,	RR,	RR,	R2,	R2,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	RR,	RR,	RR,	BB,	RR,	RR,	RR,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	R3,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	RR,	BB,	RR,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R4,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	BB,	R3,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	R4,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	WW,
        WW,	WW,	BB,	R4,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	R4,	BB,	WW,
        WW,	BB,	BB,	R4,	R2,	R2,	BB,	R3,	R3,	BB,	R3,	R3,	BB,	R3,	R2,	R2,	R2,	R2,	R2,	R3,	BB,	R3,	R3,	BB,	R3,	R3,	BB,	R3,	R3,	R4,	BB,	BB,
        WW,	RR,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R3,	R3,	R4,	BB,	RR,
        WW,	BB,	BB,	R2,	R2,	R3,	WW,	BB,	BB,	RR,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	RR,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	BB,
        WW,	RR,	BB,	R2,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	BB,	R3,	R3,	R3,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	BB,	RR,
        WW,	BB,	BB,	R3,	R3,	R3,	R4,	WW,	BB,	BB,	BB,	WW,	R0,	R0,	R0,	BB,	BB,	BB,	R0,	R0,	R0,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R3,	R4,	BB,	BB,
        WW,	RR,	RR,	BB,	R3,	R3,	R0,	R0,	WW,	WW,	WW,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	WW,	WW,	WW,	R1,	R1,	R3,	R4,	BB,	RR,	RR,
        WW,	WW,	WW,	RR,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	BB,	RR,	WW,	WW,
        WW,	WW,	WW,	WW,	RR,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	R1,	BB,	BB,	RR,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	RR,	BB,	BB,	BB,	R3,	R3,	R3,	R3,	R2,	R2,	R2,	R2,	R3,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	RR,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	RR,	BB,	BB,	RR,	BB,	R2,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R4,	R2,	BB,	RR,	BB,	BB,	RR,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	BB,	BB,	RR,	RR,	BB,	BB,	RR,	BB,	R4,	R2,	R4,	R2,	R3,	R2,	R3,	R3,	R3,	R2,	R4,	R2,	R4,	BB,	RR,	BB,	BB,	RR,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	WW,	WW,	BB,	BB,	RR,	BB,	R4,	R2,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R2,	R4,	BB,	RR,	BB,	BB,	RR,	BB,	BB,	WW,	WW,
        WW,	BB,	RR,	RR,	WW,	BB,	RR,	RR,	RR,	BB,	R4,	R4,	R4,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R4,	R4,	R2,	BB,	RR,	RR,	RR,	BB,	RR,	RR,	BB,	WW,
        WW,	RR,	WW,	WW,	WW,	RR,	WW,	WW,	RR,	BB,	R4,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	RR,	WW,	WW,	RR,	WW,	WW,	RR,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R3,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	R4,	R2,	R2,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R2,	R2,	BB,	RR,	BB,	R4,	R2,	R2,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R3,	R2,	BB,	RR,	BB,	R4,	R2,	R3,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R3,	BB,	RR,	BB,	R4,	R4,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	BB,	RR,	RR,	RR,	BB,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW
    };

uint16_t dead2[petDIM*petDIM] =
    {
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	RR,	BB,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	BB,	RR,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	RR,	BB,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	BB,	RR,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	RR,	BB,	R0,	R0,	R0,	R1,	R1,	R1,	R2,	BB,	RR,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	RR,	RR,	BB,	R0,	R1,	R1,	R1,	R2,	BB,	RR,	RR,	R4,	R4,	BB,	BB,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	BB,	R4,	R4,	R4,	R4,	R4,	RR,	RR,	BB,	R1,	R1,	R2,	BB,	RR,	RR,	R4,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	RR,	RR,	RR,	BB,	RR,	RR,	RR,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	RR,	BB,	RR,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	BB,	WW,
        WW,	WW,	BB,	R4,	R4,	R4,	R4,	BB,	R4,	BB,	R4,	BB,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	BB,	R4,	BB,	R4,	BB,	R4,	R4,	R4,	R4,	BB,	WW,
        WW,	WW,	BB,	R4,	R4,	R4,	R4,	R4,	WW,	WW,	WW,	R3,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R4,	R3,	WW,	WW,	WW,	R4,	R4,	R4,	R4,	R4,	BB,	WW,
        WW,	BB,	BB,	R4,	R4,	R4,	R4,	WW,	BB,	BB,	BB,	WW,	R3,	R3,	R4,	R4,	R4,	R4,	R4,	R3,	R3,	WW,	BB,	BB,	BB,	WW,	R4,	R4,	R4,	R4,	BB,	BB,
        WW,	RR,	BB,	R4,	R4,	R4,	WW,	BB,	BB,	RR,	BB,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	BB,	RR,	BB,	BB,	WW,	R4,	R4,	R4,	BB,	RR,
        WW,	BB,	BB,	R4,	R4,	R3,	WW,	BB,	RR,	RR,	RR,	BB,	WW,	R3,	R3,	R3,	R3,	R3,	R3,	R3,	WW,	BB,	RR,	RR,	RR,	BB,	WW,	R4,	R4,	R4,	BB,	BB,
        WW,	RR,	BB,	R4,	R3,	R3,	WW,	BB,	BB,	RR,	BB,	BB,	WW,	R3,	R3,	R3,	BB,	R3,	R3,	R3,	WW,	BB,	BB,	RR,	BB,	BB,	WW,	R4,	R4,	R4,	BB,	RR,
        WW,	BB,	BB,	R3,	R3,	R3,	R4,	WW,	BB,	BB,	BB,	WW,	R0,	R0,	R0,	BB,	BB,	BB,	R0,	R0,	R0,	WW,	BB,	BB,	BB,	WW,	R4,	R4,	R4,	R4,	BB,	BB,
        WW,	RR,	RR,	BB,	R3,	R3,	R0,	R0,	WW,	WW,	WW,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	WW,	WW,	WW,	R1,	R1,	R4,	R4,	BB,	RR,	RR,
        WW,	WW,	WW,	RR,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	BB,	RR,	WW,	WW,
        WW,	WW,	WW,	WW,	RR,	BB,	BB,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R1,	R1,	R1,	R1,	R1,	BB,	BB,	RR,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	RR,	BB,	BB,	BB,	R3,	R3,	R3,	R3,	R2,	R2,	R2,	R2,	R3,	R4,	R4,	R4,	R4,	BB,	BB,	BB,	RR,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	BB,	BB,	RR,	BB,	BB,	RR,	BB,	R2,	R3,	R2,	R2,	R2,	R2,	R2,	R2,	R2,	R4,	R2,	BB,	RR,	BB,	BB,	RR,	BB,	BB,	WW,	WW,	WW,
        WW,	WW,	BB,	BB,	RR,	RR,	BB,	BB,	RR,	BB,	R4,	R2,	R4,	R2,	R3,	R2,	R3,	R3,	R3,	R2,	R4,	R2,	R4,	BB,	RR,	BB,	BB,	RR,	BB,	BB,	WW,	WW,
        WW,	WW,	BB,	BB,	WW,	WW,	BB,	BB,	RR,	BB,	R4,	R2,	R4,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R4,	R2,	R4,	BB,	RR,	BB,	BB,	RR,	BB,	BB,	WW,	WW,
        WW,	BB,	RR,	RR,	WW,	BB,	RR,	RR,	RR,	BB,	R4,	R4,	R4,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R4,	R4,	R2,	BB,	RR,	RR,	RR,	BB,	RR,	RR,	BB,	WW,
        WW,	RR,	WW,	WW,	WW,	RR,	WW,	WW,	RR,	BB,	R4,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	RR,	WW,	WW,	RR,	WW,	WW,	RR,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R3,	R2,	R2,	R0,	R0,	R0,	R0,	R0,	R2,	R2,	R3,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R2,	R2,	BB,	BB,	BB,	R4,	R2,	R2,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R2,	R2,	BB,	RR,	BB,	R4,	R2,	R2,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R3,	R2,	BB,	RR,	BB,	R4,	R2,	R3,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	R4,	R3,	BB,	RR,	BB,	R4,	R4,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,
        WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	RR,	BB,	BB,	RR,	RR,	RR,	BB,	BB,	RR,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW,	WW
    };

uint16_t battery[battW*battH] =
    {
        WW, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, WW,
        WW, BB, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, BB, WW, WW,
        BB, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, BB, WW,
        BB, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, BB, BB,
        BB, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, BB, BB,
        BB, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, BB, BB,
        BB, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, BB, WW,
        WW, BB, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, WW, BB, WW, WW,
        WW, WW, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, WW, WW, WW
    };

uint16_t meal[mealW*mealH] =
    {
        WW, BB, BB, BB, BB, WW,
        BB, BB, BB, BB, BB, BB,
        R3, R3, R3, R2, R2, R3,
        R2, R2, R2, R3, R3, R2,
        BB, BB, BB, BB, BB, BB
    };

uint16_t snack[snackW*snackH] =
    {
        R3, R2, WW,
        R3, R2, R3,
        R3, R2, R3,
        R3, R2, R3,
        BB, BB, BB,
        WW, BB, WW
    };

uint16_t heart[heartW*heartH] =
    {
        WW, WW, BB, BB, WW, WW, WW, BB, BB, WW, WW,
				WW, BB, R2, R2, BB, WW, BB, R2, R3, BB, WW,
				BB, R2, R2, R2, R2, BB, R2, R3, R3, R3, BB,
				BB, R2, R2, R2, R3, R3, R3, R3, R3, R3, BB,
				BB, R2, R2, R3, R3, R3, R3, R3, R3, R3, BB,
				WW, BB, R2, R3, R3, R3, R3, R3, R3, BB, WW,
				WW, WW, BB, R2, R3, R3, R3, R3, BB, WW, WW,
				WW, WW, WW, BB, R3, R3, R3, BB, WW, WW, WW,
				WW, WW, WW, WW, BB, R3, BB, WW, WW, WW, WW,
				WW, WW, WW, WW, WW, BB, WW, WW, WW, WW, WW
    };

uint16_t volume[volW*volH] =
    {
        WW, WW, WW, WW, WW, WW, WW, WW, BB, BB,
				WW, WW, WW, WW, WW, WW, WW, BB, WW, BB,
				WW, WW, WW, WW, WW, WW, BB, BB, WW, BB,
				WW, BB, BB, BB, BB, BB, WW, BB, WW, BB,
				BB, WW, WW, WW, WW, WW, WW, BB, WW, BB,
				BB, WW, WW, WW, WW, WW, WW, BB, WW, BB,
				BB, WW, WW, WW, WW, WW, WW, BB, WW, BB,
				BB, WW, WW, WW, WW, WW, WW, BB, WW, BB,
				WW, BB, BB, BB, BB, BB, WW, BB, WW, BB,
				WW, WW, WW, WW, WW, WW, BB, BB, WW, BB,
				WW, WW, WW, WW, WW, WW, WW, BB, WW, BB,
				WW, WW, WW, WW, WW, WW, WW, WW, BB, BB
    };		

uint16_t line1[lineW*lineH]=
		{
			WW,
			WW,
			WW,
			WW,
			WW,
			BB,
			BB,
			WW,
			WW,
			WW,
			WW,
			WW
		};
		
uint16_t line2[lineW*lineH]=
		{
			WW,
			WW,
			WW,
			BB,
			BB,
			BB,
			BB,
			BB,
			BB,
			WW,
			WW,
			WW
		};

uint16_t line3[lineW*lineH]=
		{
			WW,
			BB,
			BB,
			BB,
			BB,
			BB,
			BB,
			BB,
			BB,
			BB,
			BB,
			WW
		};	

		
