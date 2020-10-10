/*************************************************************************
                           CompoundTrip  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

// - Réalisation de la classe <CompoundTrip> (fichier CompoundTrip.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <fstream>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "App.h"
#include "CompoundTrip.h"
#include "SimpleTrip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const char *CompoundTrip::GetStart() const
{
    return subtrips->Get(0)->GetStart();
} //----- Fin de GetStart

const char *CompoundTrip::GetEnd() const
{
    return subtrips->GetLast()->GetEnd();
} //----- Fin de GetEnd

ListOfTrips *CompoundTrip::GetTrips() const
{
    return subtrips;
} //----- Fin de GetTrips

void CompoundTrip::Display() const
{
    const unsigned int N = subtrips->Size();
    cout << "Trajet Composé: " << GetStart() << " -> " << GetEnd();
    cout << " (" << N << " sous-trajets)" << endl;
    for (unsigned int i = 0; i < N; i++)
    {
        Trip *trajet = subtrips->Get(i);
        cout << "     |-[" << (i + 1) << "]: ";
        trajet->Display();
    }
}

void CompoundTrip::Serialize(ofstream &output) const
{
    const unsigned int nSubTrips = subtrips->Size();
    output << "@" << endl;
    output << nSubTrips << endl;
    for (unsigned int i = 0; i < nSubTrips; i++)
    {
        const SimpleTrip *trip = (SimpleTrip *)subtrips->Get(i);
        if (i == 0)
        {
            output << trip->GetStart() << endl;
        }

        output << trip->GetEnd() << endl;

        output << trip->GetMode() << endl;
    }
}

Trip::TYPE CompoundTrip::GetType() const
{
    return TYPE::COMPOUND;
}

//-------------------------------------------- Constructeurs - destructeur
CompoundTrip::CompoundTrip(ListOfTrips *trips)
    : subtrips(trips)
{
#ifdef MAP
    cout << "Appel au constructeur de <CompoundTrip>" << endl;
#endif
} //----- Fin de CompoundTrip

CompoundTrip::~CompoundTrip()
{
#ifdef MAP
    cout << "Appel au destructeur de <CompoundTrip>" << endl;
#endif
    for (unsigned int i = 0; i < subtrips->Size(); i++)
    {
        delete subtrips->Get(i);
    }
    delete subtrips;
} //----- Fin de ~CompoundTrip

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
