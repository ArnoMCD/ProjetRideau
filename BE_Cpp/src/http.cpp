

<<<<<<< HEAD

#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>
=======
//#include <Ethernet.h>
//#include <mraa/i2c.h>
//#include <unistd.h>
//#include <iostream>
//#include <string>
//#include <mraa/aio.h>
//#include <mraa/gpio.h>
>>>>>>> branch 'master' of https://github.com/ArnoMCD/ProjetRideau

//#include "../headers/Ecran.h"
//#include "../headers/Capteur.h"


//using namespace std;

//int main(void)
//{

//boolean incoming = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
//byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
//IPAddress ip(169,254,73,223); //<<< ENTER YOUR IP ADDRESS HERE!!!

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
//EthernetServer server(80);

//void setup()
//=======
////i#include <Ethernet.h>
//#include <mraa/i2c.h>
//#include <unistd.h>
//#include <iostream>
//#include <string>
//#include <mraa/aio.h>
//#include <mraa/gpio.h>
//
//#include "../headers/Ecran.h"
//#include "../headers/Capteur.h"
//
//
//using namespace std;
//
<<<<<<< HEAD
//int main4(void)
=======
//int main4(void)
//>>>>>>> branch 'master' of https://github.com/ArnoMCD/ProjetRideau
>>>>>>> branch 'master' of https://github.com/ArnoMCD/ProjetRideau
//{
//
//boolean incoming = 0;
//
//// Enter a MAC address and IP address for your controller below.
//// The IP address will be dependent on your local network:
//byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
//IPAddress ip(169,254,73,223); //<<< ENTER YOUR IP ADDRESS HERE!!!
//
//// Initialize the Ethernet server library
//// with the IP address and port you want to use
//// (port 80 is default for HTTP):
//EthernetServer server(80);
//
////void setup()
////{
// // pinMode(2, OUTPUT);
//
//  // start the Ethernet connection and the server:
//  Ethernet.begin(mac, ip);
//  server.begin();
//  Serial.begin(9600);
////}
//
////void loop()
////{
//  //on regarde si y'a au moins un client
//  EthernetClient client = server.available();
//  if (client) {
//
//    //une requete http se finit par une ligne blanche
//    boolean currentLineIsBlank = true;
//
//    while (client.connected()) {
//      if (client.available()) {
//        char c = client.read();
//        /*si on arrive à la fin d'une ligne (nouvelle ligne de caractères reçu) et que la ligne est blanche,
//        la requete http est finie, donc on peut envoyer une réponse */
//
//        //il lit la chaine de caractère de l'url du '$' jusqu'à la première ligne blanche
//        if(incoming && c == ' '){
//          incoming = 0;
//        }
//        if(c == '$'){
//          incoming = 1;
//        }
//
//        //on regarde la valeur de la chaine de caractère ($1 ou $2)
//        if(incoming == 1){
//          Serial.println(c);
//
//          if(c == '1'){
//            Serial.println("ON");
//            mraa_init();
//
//            	Capteur *monCapteurLum = new Capteur();
//            	Ecran *monEcran = new Ecran();
//
//            	monCapteurLum->setPin(1);
//            	monCapteurLum->init();
//
//            	monEcran -> setPin(0);
//            	monEcran -> init();
//            	int compteur_seconde(0);
//
//            	while (compteur_seconde < 10)
//            	{
//            		monEcran -> afficher(monCapteurLum->readADCValue());
//            		sleep(1);
//            		++compteur_seconde;
//            	}
//
//            	monEcran->arreter();
//
//            	free(monEcran);
//            	free(monCapteurLum);
//          }
//          //if(c == '2'){
//           // Serial.println("OFF");
//           // digitalWrite(2, LOW);
//          }
//
//        }
//
//        if (c == '\n') {
//          //on commence une nouvelle ligne
//          currentLineIsBlank = true;
//        }
//        else if (c != '\r') {
//          //on a un caractère sur la ligne en cours
//          currentLineIsBlank = false;
//        }
//      }
//    }
//    //on laisse le navigateur web le temps de recevoir les données
//    delay(1);
//    //on éteint la connection
//    client.stop();
//  }
//
