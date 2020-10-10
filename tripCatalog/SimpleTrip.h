/*************************************************************************
                           SimpleTrip  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---- Interface de la classe <SimpleTrip> (fichier SimpleTrip.h) ----------
#if !defined(SIMPLE_TRIP_H)
#define SIMPLE_TRIP_H

//--------------------------------------------------- Interfaces utilisées
#include "Trip.h"
#include <cstring>
#include <fstream>
#include <iostream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------
// Rôle de la classe <SimpleTrip>
//  SimpleTrip représente un voyage entre deux villes
//------------------------------------------------------------------------

class SimpleTrip : public Trip
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    const char *GetStart() const;
    // Mode d'emploi :
    // Accesseur de la propriété startCity.
    // Renvoie un pointeur vers une chaîne de caractères.
    // Contrats :
    //

    const char *GetEnd() const;
    // Mode d'emploi :
    // Accesseur de la propriété endCity.
    // Renvoie un pointeur vers une chaîne de caractères.
    // Contrats :
    //

    const char *GetMode() const;
    // Mode d'emploi :
    // Accesseur de la propriété mode.
    // Renvoie un pointeur vers une chaîne de caractères.
    // Contrats :
    //

    void Display() const;
    // Mode d'emploi :
    // Affiche sur la sortie standard une représentation du trajet simple,
    // selon le format suivant :
    //      ville départ -> ville arrivée (mode de transport)

    void Serialize(ofstream &output) const;
    // Mode d'emploi :
    //

    Trip::TYPE GetType() const;
    // Mode d'emploi :
    // Renvoie le type de trajet, qui est Trip::TYPE::SIMPLE

    // On désactive l'opérateur d'affectation
    SimpleTrip &operator=(const SimpleTrip &) = delete;

    //-------------------------------------------- Constructeurs - destructeur
    // On désactive le constructeur de copie
    SimpleTrip(const SimpleTrip &aSimpleTrip) = delete;

    SimpleTrip(const char *inStart, const char *inEnd, const char *inMode);
    // Mode d'emploi :
    // Crée une instance de la classe
    // Trip s'occupera de delete start et end
    //
    // Les chaînes passées en paramètre seront copiées.
    // Pourquoi copier les chaines de caractères passées en paramètre ?
    // La raison est que l'espace mémoire consommé par les chaînes
    //     données en paramètre est égal à la taille du buffer UI_BUFFER_SIZE.
    // On peut rapidement arriver à de fortes consommations
    //     de mémoire de manière inutile.
    //
    // Nous avons donc fait le choix de systématiquement copier les chaines
    //     données en paramètre dans un espace mémoire de taille adapté.
    //
    // Cependant, ce choix a un coût :
    //     - le constructeur est plus lent ;
    //     - le constructeur est plus complexe (ce qui augmente le risque de bug) ;
    //     - l'espace mémoire risque d'être fragmenté plus facilement.
    //
    // Nous considérons cependant que ce choix est une bonne manière
    //     de satisfaire un certain nombre de contraintes rigoureuses que
    //     nous nous sommes fixées (notamment le fait que les paramètres
    //     en entrée doivent être tous `const`).
    //
    // Enfin, ce choix est en adéquation avec le Guide de Style imposé,
    //     notamment la règle C-3 : « Le constructeur doit allouer lui-même
    //     toutes les zones dynamiques de l'objet. »

    virtual ~SimpleTrip();
    // Mode d'emploi :
    // Libération de l'espace mémoire pointé par startCity, endCity et mode

    //------------------------------------------------------------------ PRIVE

protected:
    //------------------------------------------------- Constructeurs protégés

    //----------------------------------------------------- Attributs protégés
    const char *startCity;
    const char *endCity;
    const char *mode;
};

//-------------------------------- Autres définitions dépendantes de <SimpleTrip>

#endif // SIMPLE_TRIP_H
