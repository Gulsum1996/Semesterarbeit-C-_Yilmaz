#include <iostream>
using namespace std;
#include <string.h>
#include "nelement3.h"



ClElement::ClElement(
char *symbolkette) {


    zahl=0;
    zahlAttribute=0;


    strcpy(name,symbolkette);
    status=frei;
    naechstes=NULL;}


        void ClElement::addTag(
        char *symbolkette){

        strcpy(tags[zahl],symbolkette);
        zahl++;}

        void ClElement::addAttribute(
        char                        *symbolkette){


        strcpy(attributes[zahlAttribute],symbolkette);
        zahlAttribute++;}

        void ClElement::druckeElement(
        int ebene,



                ClElement *wurzel){
int j,i;

ClElement *wichtig;

            status=inBearbeitung;

            for (j=0;j<ebene;j++) cout << "|   ";
            cout << "Hier ist das Element" << name << "diese Attribute gibt es: " << endl;

            for (i=0;i<zahlAttribute;i++)
    {
            for (j=0;j<ebene;j++) cout << "|   ";
            cout << "  -" << attributes[i] << endl;}

            for (j=0;j<ebene;j++) cout << "|   ";

            cout << "enthält die Tags: " << endl;

            for (i=0;i<zahl;i++)
    {
    for (j=0;j<ebene;j++) cout << "|   ";
    cout << "   " << tags[i] << endl;
    wichtig=sucheElement(tags[i],wurzel);
    if (wichtig != NULL) wichtig->druckeElement(ebene+1,wurzel);
    }
           status=frei;}

ClElement *ClElement::sucheElement(
char *suche,
ClElement *element)
{
ClElement *resultat;

           if (element==NULL) return NULL;

           if (!strcmp(suche,element->name))

           if (element->status==frei) return element;

           else return NULL;

           return sucheElement(suche,element->naechstes);}



           int ClElement::elementIstErlaubt(
           char                            *name){
for (int i=0;i<zahl;i++)
    if (!strcmp(name,tags[i])) return i;

return -1;
}

int ClElement::attributeIstErlaubt(
char                            *name)
{
for (int i=0;i<zahlAttribute;i++)
    if (!strcmp(name,attributes[i])) return i;

return -1;
}

