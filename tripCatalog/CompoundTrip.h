/*************************************************************************
                           CoumpoundTrip  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---- Interface de la classe <CompoundTrip> (fichier CompoundTrip.h) ----
#if !defined(COMPOUND_TRIP_H)
#define COMPOUND_TRIP_H

//--------------------------------------------------- Interfaces utilisées
#include "ListOfTrips.h"
#include "Trip.h"
#include <fstream>
#include <iostream>

//------------------------------------------------------------------------
// Rôle de la classe <CompoundTrip>
//
//
//------------------------------------------------------------------------

class CompoundTrip : public Trip
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    const char *GetStart() const;
    // Mode d'emploi :
    // Renvoie un pointeur vers une chaîne de caractères associée
    // à la ville de départ du premier trajet.
    // Contrats :
    //

    const char *GetEnd() const;
    // Mode d'emploi :
    // Renvoie un pointeur vers une chaîne de caractères associée
    // à la ville d'arrivée du dernier trajet.
    // Contrats :
    //

    ListOfTrips *GetTrips() const;
    // Mode d'emploi :
    //  Renvoie la liste des sous-trajets de ce trajet composé

    void Display() const;
    // Mode d'emploi :
    // Affiche sur la sortie standard une représentation du trajet composé
    // ainsi que des trajets contenus dans ce trajet composé.

    void Serialize(ofstream &output) const;
    // Mode d'emploi :
    //

    Trip::TYPE GetType() const;
    // Mode d'emploi :
    // Renvoie le type de trajet, qui est Trip::TYPE::COMPOUND

    // On désactive l'opérateur d'affectation
    CompoundTrip &operator=(const CompoundTrip &) = delete;

    //-------------------------------------------- Constructeurs - destructeur
    // On désactive le constructeur de copie
    CompoundTrip(const CompoundTrip &aCompoundTrip) = delete;

    CompoundTrip(ListOfTrips *trips);
    // Mode d'emploi :
    //  Construit un trajet composé de l'ensemble des trajets (dans l'ordre) de
    //  trips.
    // CompoundTrip s'occuppera de delete la liste et ses sous-trajets.
    // Contrat :
    //  trips doit contenir au moins un trip

    virtual ~CompoundTrip();
    // Mode d'emploi :
    //  Libère la liste

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Attributs protégés
    ListOfTrips *subtrips;
};

//-------------------------------- Autres définitions dépendantes de <CompoundTrip>

#endif // CompoundTrip_H
