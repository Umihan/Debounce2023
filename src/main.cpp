
/********************************************************************************
 * Beispiel:
 * Entprellen eines Tasters :
 * Bei jeder Änderung des Taster-Inputs wird für eine vordefinierte Entprellzeit
 * gewartet. Erst wenn das Eingangssignal diese Zeitspanne lang gleich bleibt,
 * wird der neue Zustand als stabil erkannt und in buttonStatus gespeichert.
 * - Non blocking
 * - Tasterzustand wird mit EntprellZeit Verspätung erkannt.
 * Date: 09.03.2023
 ********************************************************************************/
#include <Arduino.h>

int buttonPin = 4;

// Variablen zum speichern der Zustände

int buttonStatus;         // zum Zwischenspeichern des aktuellen Taster-Status
int letztesGelesen = LOW; // zum Zwischenspeichern des letzten Taster-Status

// long ist ein Datentyp für große Zahlen; unsigned bedeutet, dass nur positive Zahlenwerte angenommen werden können.
unsigned long letzteAenderung = 0; // der letzte Zeitpunkt, an dem eine Änderung stattfand
unsigned long entprellZeit = 50;   // Zeit, die der Taster-Zustand gleich bleiben soll, um einen stabilen Zustand zu erkennen

void setup()
{
  pinMode(buttonPin, INPUT); // Taster
}

void loop()
{
  // aktuellen Taster-Messwert lesen
  int gelesen = digitalRead(buttonPin);

  //...Wenn der Taster-Status sich geändert hat (durch drücken oder auch prellen)
  if (gelesen != letztesGelesen)
  {
    // setze den Timer zurück, Zeitmessung startet neu
    letzteAenderung = millis();
  }

  if ((millis() - letzteAenderung) > entprellZeit)
  {
    // Der aktuell-gelesene Wert kann nun als zuverlässig angesehen werden, da dieser länger als 50ms vorliegt.

    if (gelesen != buttonStatus)    // falls sich der Status verändert hat...
    { 
      //*** Hier kann die Flanke erkannt werden (steigend oder fallend) ***
      buttonStatus = gelesen;       //...setze diesen als buttonStatus
    }
  }

  
  letztesGelesen = gelesen;         // merke für den nächsten Loop, was der aktuelle Taster-Wert ist.
}