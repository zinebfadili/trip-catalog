/*************************************************************************
                           ListOfTrips  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---- Interface de la classe <ListOfTrips> (fichier ListOfTrips.h) ----------
#if !defined(LIST_OF_TRIPS_H)
#define LIST_OF_TRIPS_H

//--------------------------------------------------- Interfaces utilisées
#include "Trip.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes
const unsigned int LIST_OF_TRIPS_DEFAULT_SIZE = 4;

//------------------------------------------------------------------------
// Rôle de la classe <ListOfTrips>
//  ListOfTrips permet de stocker et manipuler une liste de taille variable
// de Trip
//  Via les méthodes Pop et Add, il est aussi possible de l'utiliser comme
// une pile
//------------------------------------------------------------------------

class ListOfTrips
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    void Add(Trip *elem);
    // Mode d'emploi : Ajoute un élément à la fin de la liste

    Trip *Remove(const unsigned int index);
    // Mode d'emploi : Supprime un élément à l'index donné, renvoie l'élément
    //    supprimé
    // Contrat : index < Size()

    Trip *Pop();
    // Mode d'emploi : Supprime le dernier élément de la liste, renvoie le Trip
    //    supprimé

    Trip *Get(const unsigned int index) const;
    // Contrat : index < Size()

    Trip *GetLast() const;
    // Contrat : Size() > 0

    bool Contains(const Trip *elem) const;
    // Mode d'emploi : Renvoie vrai si la liste contient un pointeur pointant
    //   sur LA MEME CASE MEMOIRE que le paramètre elem (égalité de référence)

    unsigned int Size() const;
    // Mode d'emploi : Retourne la taille actuelle de la liste

    bool IsEmpty() const;

    // On désactive l'opérateur d'affectation
    ListOfTrips &operator=(const ListOfTrips &) = delete;

    //-------------------------------------------- Constructeurs - destructeur
    // On désactive le constructeur de copie
    ListOfTrips(const ListOfTrips &anListOfTrips) = delete;

    ListOfTrips(const unsigned int startingMaxSize = LIST_OF_TRIPS_DEFAULT_SIZE);
    // Mode d'emploi : maxSize indique la taille que la liste allouera pour
    //   stocker ses éléments (qui pourra varier si besoin)
    // Contrat : startingMaxSize >= 1

    virtual ~ListOfTrips();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées
    void doubleSize();
    // Mode d'emploi : double la taille actuellement allouée à la list

    //----------------------------------------------------- Attributs protégés
    unsigned int currentSize;
    unsigned int maxSize;

    Trip **list;
};

#endif // LIST_OF_TRIPS_H
