#include <iostream>
 using namespace std;
#include <fstream>
#include <string.h>
#include "ntoken3.h"


ClElement *verarbeite(ifstream& datei);
enum ezustand {direktive, element, attribute, wichtigElement,
               wichtigAttribute, inID, noise};


//An dieser Stelle fängt meine funktion an

int main()
{

             ofstream lesen;
             ClToken *token;
             ifstream schreiben;
             ClElement *jetzt=NULL, *wurzel;

             char charname[500];
             char option;
             char symbol;
             char puffer[500];

             int zaehler;



//An dieser Stelle erstelle ich meine Menüführung


      cout <<"Hallo, ich heisse nicht nur Guelsuem sondern Sie auch herzlich willkommen zu meiner C++ Seminararbeit."<< endl;
      cout <<"In meinem Programm sind Informationen aus zwei unterschiedlichen Datenquellen. "<< endl;
      cout <<"Diese werden ausgelesen,zwischengespeichert,durchsucht und in ein neues Format ueberfuehrt."<< endl;
      cout <<"Option 1: Geben Sie (k) ein,um die 'convert data' Funktion auszufuehren. "<<endl;
      cout <<"Option 2: geben Sie (h)fuer die 'help' Funktion ein, um weitere Informationen zu erhalten." <<endl;
      cin >> option;


switch(option)
   {
    case 'k':
    cout <<"Sie haben sich fuer Option 1 entschieden! "<<endl;
   break;

    case 'h':
    cout << "Mit der Konvertieroption in Option 1 haben Sie die Moeglichkeit die Informationen aus einer XML Datei und einer TXT Datei zusammenfuehren" <<endl;
         cout<<"Ich hoffe ich konnte Ihnen weiterhelfen. Sie werden nun zur Konvertierungsaufforderung zurueckgeleitet."<<endl;
   break;

    default:
   cout <<"ERROR!!!" <<endl;

   return option;
   break;
   }

//An dieser Stelle lese ich meine XMl und meine DTD Datei ein

   cout << "Geben Sie den Namen ihrer dtd-Datei ein " << endl;
   cin >> charname;
   schreiben.open(charname);


wurzel=verarbeite(schreiben);

                for (jetzt=wurzel;jetzt!=NULL;jetzt=jetzt->getNext())
                jetzt->druckeElement(0,wurzel);
                schreiben.close();


                cout << "DTD ist geladen." << endl;
                cout << "Geben Sie den Namen ihrer xml-Datei ein" << endl;

                cin >> charname;

                schreiben.open(charname);

                cout << "XML ist geladen." << endl;

                token=new ClToken;


                if (token->getToken(schreiben,NULL,wurzel)!=0) token->druckeToken(1);
                schreiben.close();


// An dieser Stelle wird die Text Datei eingelesen und anschließend konvertiert.


         cout << "Geben Sie den Namen ihrer txt-Datei ein" << endl;

         cin >> charname;

         schreiben.open(charname);

         ifstream textdatei ("txt.txt");
         ifstream src("xml.xml", ios::binary);
         ofstream dst("arbeitcopy.xml", ios::binary);

         cout<<"Die XML und TXT Datei werden nun zusammengefuehrt. In der copy-Datei sind diese beiden Datenquellen ebenfalls zusammengefuehrt worden."<<endl<<endl;

cout<< "<inhaltsstoffe>Gluten</inhaltsstoffe>"<<endl<<
       "<zutat>pflanzliche Butter</zutat>" <<endl<<
      "<sonstiges>Vegan</sonstiges>"<<endl<<
      "<kochbuch>"<<endl<<

   "<bezeichnung>Zimt-Schnecken</bezeichnung>"<<endl<<

                  "<prozess>"<<endl<<

                      "<backzeit>20 min</backzeit>"<<endl<<
                      "<zutaten>Blaetterteig</zutaten>"<<endl<<
                       "<zutaten>Zucker-Zimt-Mischung</zutaten>"<<endl<<

                      "<info>Blaetterteig_ausrollen</info>"<<endl<<
                      "<info1>Zucker-Zimt-Mischung_darueber_streuen</info1>"<<endl<<
                      "<info3>zu_einer_Rolle_rollen</info3>"<<endl<<
                      "<info4>Fertig!</info4>"<<endl<<

                  "</prozess>"<<endl<<


      "</kochbuch>"<<endl;


dst << src.rdbuf();
dst.close();

ofstream txtoutput("arbeitcopy.xml", ios::app);
txtoutput << textdatei.rdbuf();
}

        ClElement *verarbeite(ifstream& datei){

           char symbol, letztes;
           char puffer[500];

           int zaehler;
           enum ezustand zustand = noise;

           ClElement *jetzt=NULL, *wurzel=NULL, *neu;
           for (datei.get(symbol);!datei.eof();datei.get(symbol)){


           switch(symbol){

           case '<':
          zustand=direktive;
           zaehler=0;
           break;

           case '>':
           if (letztes!=' '){
          puffer[zaehler]='\0';

          switch(zustand){

          case wichtigElement:
          jetzt->addTag(puffer);
             break;

          case wichtigAttribute:
             jetzt->addAttribute(puffer);
             break;

          case element:
             neu=new ClElement(puffer);

         if (jetzt!=NULL) jetzt->setNext(neu);

         else wurzel=neu;


         jetzt=neu;
         zustand=wichtigElement;
             break;


         }
          }

           zustand=noise;
           break;


           case ' ':
           if (letztes==' ') continue;
           puffer[zaehler]='\0';
           zaehler=0;

           switch(zustand){

           case direktive:
           if (!strcmp(puffer,"!ELEMENT")) zustand=element;
           else if (!strcmp(puffer,"!ATTLIST")) zustand=attribute;
           else{


      cout << endl << "Fehler!" << puffer;
      zustand=noise;}
          break;


      case element:
      neu=new ClElement(puffer);
      if (jetzt!=NULL) jetzt->setNext(neu);
      else wurzel=neu;
      jetzt=neu;
      zustand=wichtigElement;
      break;


          case attribute:
          if (wurzel==NULL) neu=NULL;
          else neu=wurzel->sucheElement(puffer,wurzel);
          if (neu==NULL)
             {
             cout << endl << "ERROR!!!" << puffer << endl;
             zustand=noise;}

          else{
             zustand=wichtigAttribute;
             jetzt=neu;}
          break;

          case wichtigElement:
          jetzt->addTag(puffer);
          break;

          case wichtigAttribute:
          jetzt->addAttribute(puffer);
          break;}
          break;


          default:
          if (zustand!=noise) puffer[zaehler] = symbol;
          zaehler++;

          break;}

          letztes=symbol;} return wurzel;}

