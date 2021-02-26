/*************************************************************************
                           SearchResults  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---- Interface de la classe <SearchResults> (fichier SearchResults.h) ----------
#if !defined(SEARCH_RESULTS_H)
#define SEARCH_RESULTS_H

//--------------------------------------------------- Interfaces utilisées
#include "ListOfTrips.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes
const unsigned int SEARCH_RESULTS_DEFAULT_SIZE = 4;

//------------------------------------------------------------------------
// Rôle de la classe <SearchResults>
//  SearchResults permet de stocker et manipuler une liste de taille variable
// de ListOfTrips
//------------------------------------------------------------------------

class SearchResults
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    void Add(ListOfTrips *elem);
    // Mode d'emploi : Ajoute un élément à la fin de la liste

    ListOfTrips *Get(const unsigned int index) const;
    // Contrat : index < Size()

    ListOfTrips *GetLast() const;
    // Contrat : Size() > 0

    unsigned int Size() const;
    // Mode d'emploi : Retourne la taille actuelle de la liste

    // On désactive l'opérateur d'affectation
    SearchResults &operator=(const SearchResults &) = delete;

    //-------------------------------------------- Constructeurs - destructeur
    // On désactive le constructeur de copie
    SearchResults(const SearchResults &anSearchResults) = delete;

    SearchResults(const unsigned int startingMaxSize = SEARCH_RESULTS_DEFAULT_SIZE);
    // Mode d'emploi : maxSize indique la taille que la liste allouera pour
    //   stocker ses éléments (qui pourra varier si besoin)
    // Contrat : startingMaxSize >= 1

    virtual ~SearchResults();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées
    void doubleSize();
    // Mode d'emploi : double la taille actuellement allouée à la list

    //----------------------------------------------------- Attributs protégés
    unsigned int currentSize;
    unsigned int maxSize;

    ListOfTrips **list;
};

#endif // SEARCH_RESULTS_H
