/*************************************************************************
                           Trip  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---- Réalisation de la classe <Trip> (fichier Trip.cpp) ------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "App.h"
#include "Trip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
Trip::Trip()
{
#ifdef MAP
    cout << "Appel au constructeur de <Trip>" << endl;
#endif
} //----- Fin de Trip

Trip::~Trip()
{
#ifdef MAP
    cout << "Appel au destructeur de <Trip>" << endl;
#endif
} //----- Fin de ~Trip

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
