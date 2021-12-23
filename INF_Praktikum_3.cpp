/* ===============================================================
*
* Filmdatenbank
*
* Programmautor: 
*
* v1.0 / Datum: 21.12.2021
*
* ================================================================
*/

// Einbindung der Header-Dateien
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


// ================================================================
// Global verfuegbare Datentypen
// ================================================================

typedef struct {
	char filmtitel[30];
	unsigned int erscheinungsjahr;
	char regisseur[50];
	char genre[50];
	float einspielergebnis;
} film_t;


// ================================================================
// Globale Parameter und Variablen fuer Filmdatenbank
// ================================================================

#define MAX_STORAGE 100

film_t filmDaten[MAX_STORAGE];

unsigned int anzahlFilme = 0;

film_t movieDatensatz;

// ================================================================
// Hilfsfunktionen
// ================================================================

/*
Funktion zur sicheren Stringeingabe ueber die Konsole durch den Benutzer

Eingabeparameter:
- zeichenkette: Pointer zum char-Array, in dem die Eingabe abgelegt werden soll
- maxLaenge   : Laenge dieses char-Arrays (Anzahl an verfuegbaren Elementen)
Rueckgabe:
- Laenge der eingelesenen Zeichenkette (falls -1, ist ein Fehler aufgetreten)
*/
int
sichereStringEingabe(char* zeichenkette, unsigned maxLaenge)
{
	// Check, ob ein valider Pointer auf das char-Array uebergeben wurde
	if (!zeichenkette)
	{
		return -1;
	}

	// Leere Eingabepuffer von evtl. Altlasten
	fflush(stdin);

	// zeichenkette von stdin einlesen (Benutzereingabe)
	char* s = fgets(zeichenkette, maxLaenge, stdin);
	// Falls s ein Nullpointer ist, kam es zu einem Fehler
	// waehrend der Ausfuehrung von fgets()
	// --> also -1 zurueckgeben
	if (!s)
	{
		return -1;
	}

	// Beseitige das Newline-Zeichen von der Benutzereingabe,
	// welches fgets(..) in der eingelesenen Zeichenkette belaesst
	unsigned l = strlen(zeichenkette);
	if (l > 0)
	{
		if (zeichenkette[l - 1] == '\n')
		{
			zeichenkette[l - 1] = '\0';
			l--;
		}
	}

	// Rueckgabe: Laenge der eingelesenen Zeichenkette
	return l;
}


// ================================================================
// Unterfunktionen fuer Filmdatenbank
// ================================================================

film_t
benutzerEingabe(void)
{
	system("CLS");

	printf("\nIhre Wahl: n\n\n");

	//Buffer für die Zahlen
	char erscheinungsJahrBuffer[10], einspielergebnisBuffer[10];

	printf("Bitte geben Sie Ihre Filmdaten ein.\n");

	printf("\nFilmtitel eingeben	: ");
	sichereStringEingabe(movieDatensatz.filmtitel, sizeof(movieDatensatz.filmtitel));

	printf("Erscheinungsjahr	: ");
	sichereStringEingabe(erscheinungsJahrBuffer, sizeof(erscheinungsJahrBuffer));
	movieDatensatz.erscheinungsjahr = atoi(erscheinungsJahrBuffer);

	printf("Regisseur eingeben	: ");
	sichereStringEingabe(movieDatensatz.regisseur, sizeof(movieDatensatz.regisseur));

	printf("Genre eingeben		: ");
	sichereStringEingabe(movieDatensatz.genre, sizeof(movieDatensatz.genre));

	printf("Einspielergebnis	: ");
	sichereStringEingabe(einspielergebnisBuffer, sizeof(einspielergebnisBuffer));
	movieDatensatz.einspielergebnis = atof(einspielergebnisBuffer);

	system("CLS");

	printf("\nAlle Eingeben waren erfolgreich.\n");
	
	return movieDatensatz;
}

void
konsolenAusgabe(film_t filmDatensatz, unsigned index)
{
	system("CLS");

	printf("\nIhre Wahl: a\n\n");

	printf("FILMDATENSATZ\t\t NR. %u\n\n", index);

	printf("Filmtitel		: %s\n", filmDatensatz.filmtitel);
	printf("Erscheinungsjahr	: %u\n", filmDatensatz.erscheinungsjahr);
	printf("Regisseur		: %s\n", filmDatensatz.regisseur);
	printf("Genre			: %s\n", filmDatensatz.genre);
	printf("Einspielergebnis	: %.2f\n", filmDatensatz.einspielergebnis);

	return;
}


int
dateiEinlesen(const char *dateiname)
{
	FILE* fp = fopen(dateiname, "rb");
	if(!fp)
	{
		printf("ERROR: Datei konnte nicht geoeffnet werden!\n");
		return -1;
	}

	printf("%s wurde erfolgreich geoeffnet.\n\n", dateiname);

	/*
	int res = fread(filmDaten, sizeof(film_t), MAX_STORAGE, fp);
	if (res > MAX_STORAGE)
	{
		printf("ERROR: Lesevorgang war nicht erfolgreich oder unvollstaendig!\n");
		return -1;
	}*/

	/*
	fread(&movieDatensatz.filmtitel, sizeof(movieDatensatz.filmtitel), 1, fp);
	fread(&movieDatensatz.erscheinungsjahr, sizeof(movieDatensatz.erscheinungsjahr), 1, fp);
	fread(&movieDatensatz.regisseur, sizeof(movieDatensatz.regisseur), 1, fp);
	fread(&movieDatensatz.genre, sizeof(movieDatensatz.genre), 1, fp);
	fread(&movieDatensatz.einspielergebnis, sizeof(movieDatensatz.einspielergebnis), 1, fp);
	*/

	/*
	int n=0;
	n = fscanf(fp, "%[^,], %u, %[^,], %[^,], %f", movieDatensatz.filmtitel, &movieDatensatz.erscheinungsjahr, movieDatensatz.regisseur, movieDatensatz.genre, &movieDatensatz.einspielergebnis);
	if (n < 5)
	{
		printf("ERROR: Lesevorgang war nicht erfolgreich oder unvollstaendig!\n");
		return -1;
	}*/

	fclose(fp);

	printf("Filme eingelesen.\n");

	return 0;
}


/*
int
dateiSpeichern(const char *dateiname)
{
}
*/

// ================================================================
// MAIN
// ================================================================

int main(void)
{
	// Default fuer Namen der Filmdatei
	char dateiname[50] = "movies.dat";

	// Hilfsvariablen--------------------------------------------------------------------------------------------------
	int i = 0;

	// Hilfsvariable fuer do-while-Schleife
	int stopLoop = 0;

	// Hauptschleife
	do {
		// Ausgabe des Bildschirm-Menus
		printf("\nAUSWAHL-MENU:\n");
		printf("(n)   Neuen Film eingeben\n");
		printf("(a)   Alle Filme anzeigen lassen\n");
		printf("(o)   Filmdatenbank aus Datei einlesen\n");
		printf("(s)   Filmdatenbank in Datei speichern\n");
		printf("(d)   Dateinamen fuer Lesen/Speichern festlegen (Aktuell: %s)\n",
			dateiname);
		printf("(q)   Programm verlassen\n");
		//printf("\nIhre Wahl: ");

		// Abfrage der Benutzerwahl
		char ch = _getch();
		printf("%c\n\n", ch);

		// Aktionen in Abhaengigkeit von der Benutzerwahl
		switch (ch)
			//----------------------------------------------------------------------------------------------------------------------
		{
		case 'q': // Programm verlassen
			stopLoop = 1;
			break;
		case 'n': // Neuen Film eingeben
			movieDatensatz = benutzerEingabe();
			break;
		case 'a': // Alle Filme anzeigen lassen
			konsolenAusgabe(movieDatensatz, i);
			break;
		case 'o': // Filmdatenbank aus Datei einlesen
			dateiEinlesen(dateiname);
			break;
		case 's': // Filmdatenbank in Datei speichern
			break;
		case 'd': // Dateinamen fuer Lesen/Speichern festlegen
			break;
		default:  // keine gueltige Eingabe
			printf("==> Ungueltige Eingabe!\n");
		}

	} while (!stopLoop);

	return 0;
}
