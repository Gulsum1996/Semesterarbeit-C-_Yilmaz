#include <iostream>
using namespace std;
#include <fstream>
#include <string.h>
#include "natt3.h"



          int ClattToken::getAttList(
          char *schreiben,



ClElement *element){

      enum attzustand { eins, zwei, erwarteAttributNamen, Wertdrei,Wertvier} ;
      enum attzustand zustand;
      char puffer[500];
      int zaehler;


      for (zaehler=0,zustand=zwei,anzahlAtt=0;*schreiben!='\0';
      schreiben = schreiben + 1){

      switch(*schreiben){

      case ' ':
      if (zustand == zwei){
         zustand = erwarteAttributNamen;
         *schreiben='\0';
         zaehler=0;}


      else if (zustand == Wertvier){
         puffer[zaehler] = *schreiben;
         zaehler++;}


      break;
      case '=':
      if (zustand == erwarteAttributNamen){
         zustand = Wertdrei;
         puffer[zaehler] = '\0';


         if (element->attributeIstErlaubt(puffer)<0)
            cout << endl << "Das Attribut " << puffer << " ist nicht moeglich" << endl;
         attName[anzahlAtt] = new char[zaehler+1];
         strcpy(attName[anzahlAtt],puffer);
         zaehler=0;}

         else if (zustand == Wertvier){
         puffer[zaehler] = *schreiben;
         zaehler++;}

         else cout << "Fehler! '='" << endl;
         break;
         case '"':

         if (zustand == Wertdrei){
         zustand = Wertvier;
         zaehler = 0;}


         else if (zustand == Wertvier){
         zustand = erwarteAttributNamen;
         puffer[zaehler] = '\0';
         attValue[anzahlAtt] = new char[zaehler+1];
         strcpy(attValue[anzahlAtt],puffer);
         zaehler=0;
         anzahlAtt++;}

         else cout << "Fehler! '\"'" << endl;
         break;

         default:

             if (zustand >= erwarteAttributNamen){
         puffer[zaehler] = *schreiben;
         zaehler++;}break;
      }
   } return 1;
}
