/*************************************************************************
                                                     SimpleTrip  -  description
                                                         -------------------
        début                : 2019-11-19
        copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
        e-mail               : zineb.fadili@insa-lyon.fr
                                                     corentin.forler@insa-lyon.fr
*************************************************************************/

// - Réalisation de la classe <SimpleTrip> (fichier SimpleTrip.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <cstring>
#include <fstream>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "App.h"
#include "SimpleTrip.h"
#include "Trip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const char *SimpleTrip::GetStart() const
{
    return startCity;
} //----- Fin de GetStart

const char *SimpleTrip::GetEnd() const
{
    return endCity;
} //----- Fin de GetEnd

const char *SimpleTrip::GetMode() const
{
    return mode;
} //----- Fin de GetMode

void SimpleTrip::Display() const
{
    cout << "Trajet Simple: " << startCity << " -> " << endCity << " (" << mode << ")" << endl;
}

void SimpleTrip::Serialize(ofstream &output) const
{
    output << ">" << endl;
    output << startCity << endl;
    output << endCity << endl;
    output << mode << endl;
}

Trip::TYPE SimpleTrip::GetType() const
{
    return TYPE::SIMPLE;
}

//-------------------------------------------- Constructeurs - destructeur
SimpleTrip::SimpleTrip(const char *inStart, const char *inEnd, const char *inMode)
    : startCity(nullptr), endCity(nullptr), mode(nullptr)
{
#ifdef MAP
    cout << "Appel au constructeur de <SimpleTrip>" << endl;
#endif
    if (inStart != nullptr)
    {
        char *tmpStartCity = new char[strlen(inStart) + 1];
        strcpy(tmpStartCity, inStart);
        startCity = tmpStartCity;
    }

    if (inEnd != nullptr)
    {
        char *tmpEndCity = new char[strlen(inEnd) + 1];
        strcpy(tmpEndCity, inEnd);
        endCity = tmpEndCity;
    }

    if (inMode != nullptr)
    {
        char *tmpMode = new char[strlen(inMode) + 1];
        strcpy(tmpMode, inMode);
        mode = tmpMode;
    }
} //----- Fin de SimpleTrip

SimpleTrip::~SimpleTrip()
{
#ifdef MAP
    cout << "Appel au destructeur de <SimpleTrip>" << endl;
#endif
    delete[] startCity;
    delete[] endCity;
    delete[] mode;
} //----- Fin de ~SimpleTrip

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
