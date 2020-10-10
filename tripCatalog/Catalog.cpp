/*************************************************************************
                           Catalog  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Catalog> (fichier Catalog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "App.h"
#include "Catalog.h"
#include "ListOfTrips.h"
#include "SearchResults.h"
#include "Trip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalog::Display() const
{
    const unsigned int nTrajets = Size();

    if (nTrajets == 0)
    {
        cout << "Pas de trajets dans le catalogue." << endl
             << endl;
    }
    else
    {
        cout << "Il y a " << nTrajets << " trajet" << (nTrajets > 1 ? "s" : "") << " dans le catalogue." << endl
             << endl;

        for (unsigned int i = 0; i < nTrajets; i++)
        {
            Trip *trajet = Get(i);
            cout << "[" << (i + 1) << "]: ";
            trajet->Display();
        }
        cout << endl;
    }
}

bool StringEquals(const char *a, const char *b)
{
    return !strcmp(a, b);
}

SearchResults *Catalog::Search(const char *searchedStart, const char *searchedEnd) const
// Algorithme :
// Vérification simple, pour chaque trajet, d'égalité entre ses villes
// de départs et d'arrivée et les villes de départs et d'arrivées demandées
{
    SearchResults *results = new SearchResults();

    for (unsigned int i = 0; i < Size(); i++)
    {
        const char *currStart = Get(i)->GetStart();
        const char *currEnd = Get(i)->GetEnd();
        if (StringEquals(currStart, searchedStart) && StringEquals(currEnd, searchedEnd))
        {
            ListOfTrips *toAdd = new ListOfTrips(1);
            toAdd->Add(Get(i));
            results->Add(toAdd);
        }
    }

    return results;
}

// Fonction "privée" à SearchV2, clonant une liste de trips pour pouvoir la
// retourner en paramètre
static ListOfTrips *cloneList(ListOfTrips &trips)
{
    ListOfTrips *cloned = new ListOfTrips();
    for (unsigned int i = 0; i < trips.Size(); i++)
    {
        cloned->Add(trips.Get(i));
    }

    return cloned;
}

static bool isBeginning(SearchResults *results, ListOfTrips *currentJourney, Trip *toAdd)
{
    ListOfTrips *trips = cloneList(*currentJourney);
    trips->Add(toAdd);

    for (unsigned int i = 0; i < results->Size(); i++)
    {
        ListOfTrips *currResult = results->Get(i);
        for (unsigned int j = 0; j <= trips->Size(); j++)
        {
            if (j == trips->Size())
            {
                delete trips;
                return true;
            }
            if (currResult->Size() <= j || currResult->Get(j) != trips->Get(j))
                break;
        }
    }

    delete trips;
    return false;
}

SearchResults *Catalog::SearchV2(const char *searchedStart, const char *searchedEnd) const
// Algorithme :
//
// ENTREE :
//   - Ville debutVoulu, finVoulue
//   - Liste<Trajet> catalogue
// SORTIE :
//   - Liste<Liste<Trajet> resultats    # Une liste de liste car chaque résultat
//                                      # possible est lui même une liste de Trip
// VARIABLES :
//   - Pile<Trajet> aTraiter            # Les trajets vus mais pas encore traites
//   - Liste<Trajet> voyageActuel       # La suite de trajet actuellement envisagée
//   - Trajet trajetActuel              # Une variable permettant de naviguer dans la pile
//
// ALGORITHME :
// # Initialisation de la pile avec les trajets partant directement du départ
// Pour trajet dans catalogue:
//   Si debut(trajet) = debutVoulu:
//     Ajouter trajet à aTraiter
//
// Tant que aTraiter non vide:
//   Pop la tête de aTraiter dans trajetActuel
//   Mettre à jour voyageActuel en fonction de trajetActuel
//   Si fin(trajetActuel) = finVoulue:
//     Ajouter (un clone de) voyageActuel à resultats
//   Pour trajetSuivant dans catalogue:
//     Si fin(trajetActuel) = debut(trajetSuivant):
//       Ajouter trajetSuivant à aTraiter
{
    SearchResults *results = new SearchResults();
    ListOfTrips tripStack;
    ListOfTrips currentJourney;

    // Init. de la recherche avec tous les trajets partant de la ville de départ
    for (unsigned int i = 0; i < Size(); i++)
    {
        if (StringEquals(Get(i)->GetStart(), searchedStart))
        {
            tripStack.Add(Get(i));
        }
    }

    while (!tripStack.IsEmpty())
    {
        Trip *currentTrip = tripStack.Pop();
        // Mise à jour du trajet actuellement testé
        if (!currentJourney.IsEmpty())
        {
            const char *startCurrTrip = currentTrip->GetStart();
            const char *endCurrJourney = currentJourney.GetLast()->GetEnd();
            while (!StringEquals(endCurrJourney, startCurrTrip) ||
                   isBeginning(results, &currentJourney, currentTrip))
            {
                currentJourney.GetLast()->Display();
                currentJourney.Pop();
                if (currentJourney.IsEmpty())
                    break;
                endCurrJourney = currentJourney.GetLast()->GetEnd();
            }
        }
        currentJourney.Add(currentTrip);

        if (StringEquals(currentTrip->GetEnd(), searchedEnd))
        {
            results->Add(cloneList(currentJourney));
        }

        for (unsigned int i = 0; i < Size(); i++)
        {
            Trip *next = Get(i);
            if (!currentJourney.Contains(next) && StringEquals(next->GetStart(), currentTrip->GetEnd()))
            {
                tripStack.Add(next);
            }
        }
    }

    return results;
} //----- Fin de SearchV2

//-------------------------------------------- Constructeurs - destructeur
Catalog::Catalog()
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalog>" << endl;
#endif
} //----- Fin de Catalog

Catalog::~Catalog()
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalog>" << endl;
#endif
    for (unsigned int i = 0; i < Size(); i++)
    {
        Trip *trip = Get(i);
        delete trip;
    }
} //----- Fin de ~Catalog
