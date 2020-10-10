/*************************************************************************
                           Parser  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

// - Réalisation de la classe <Parser> (fichier Parser.cpp) --
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "CompoundTrip.h"
#include "ListOfTrips.h"
#include "Parser.h"
#include "SimpleTrip.h"

//----------------------------------------------------------------- PUBLIC
ListOfTrips *Parser::Parse(ifstream &input)
{
    ListOfTrips *parseResults = new ListOfTrips();

    unsigned int lineIndex = 0;
    string line;

    bool isInvalidInput = false;

    while (std::getline(input, line))
    {
        lineIndex += 1;

        if (line == ">")
        {
            string startCity;
            string endCity;
            string mode;

            std::getline(input, startCity);
            lineIndex += 1;
            if (startCity == "")
            {
                cerr << "Erreur: ligne " << lineIndex << endl;
                cerr << "  [chaîne de caractères non vide] attendu" << endl;
                cerr << "  mais [retour à la ligne] ou [fin de fichier] trouvé." << endl;
                isInvalidInput = true;
                break;
            }
            std::getline(input, endCity);
            lineIndex += 1;
            if (endCity == "")
            {
                cerr << "Erreur: ligne " << lineIndex << endl;
                cerr << "  [chaîne de caractères non vide] attendu." << endl;
                cerr << "  mais [retour à la ligne] ou [fin de fichier] trouvé." << endl;
                isInvalidInput = true;
                break;
            }
            std::getline(input, mode);
            lineIndex += 1;
            if (mode == "")
            {
                cerr << "Erreur: ligne " << lineIndex << endl;
                cerr << "  [chaîne de caractères non vide] attendu." << endl;
                cerr << "  mais [retour à la ligne] ou [fin de fichier] trouvé." << endl;
                isInvalidInput = true;
                break;
            }

            Trip *trip = new SimpleTrip(startCity.c_str(), endCity.c_str(), mode.c_str());
            parseResults->Add(trip);
        }
        else if (line == "@")
        {
            unsigned int nSubTrips;
            input >> nSubTrips;
            std::getline(input, line); // on ignore les caractères restants sur la ligne

            if (line != "")
            {
                cerr << "Erreur: ligne " << lineIndex << endl;
                cerr << "  [nombre seul] attendu" << endl;
                cerr << "  mais “" << line << "” trouvé après le nombre lu (" << nSubTrips << ")." << endl;

                isInvalidInput = true;
                break;
            }

            ListOfTrips *subtrips = new ListOfTrips(nSubTrips);

            string city1;
            string city2;
            string mode;

            std::getline(input, city1);
            lineIndex += 1;

            if (city1 == "")
            {
                cerr << "Erreur: ligne " << lineIndex << endl;
                cerr << "  [chaîne de caractères non vide] attendu" << endl;
                cerr << "  mais [retour à la ligne] ou [fin de fichier] trouvé." << endl;
                isInvalidInput = true;
                break;
            }

            // On lit <nSubTrips> éléments, soit 2 * nSubTrips lignes au total.
            for (unsigned int i = 0; i < nSubTrips; i++)
            {
                std::getline(input, city2);
                lineIndex += 1;

                if (city2 == "")
                {
                    cerr << "Erreur: ligne " << lineIndex << endl;
                    cerr << "  [chaîne de caractères non vide] attendu." << endl;
                    cerr << "  mais [retour à la ligne] ou [fin de fichier] trouvé." << endl;
                    isInvalidInput = true;
                    break;
                }

                std::getline(input, mode);
                lineIndex += 1;

                if (mode == "")
                {
                    cerr << "Erreur: ligne " << lineIndex << endl;
                    cerr << "  [chaîne de caractères non vide] attendu." << endl;
                    cerr << "  mais [retour à la ligne] ou [fin de fichier] trouvé." << endl;
                    isInvalidInput = true;
                    break;
                }

                SimpleTrip *theSubtrip = new SimpleTrip(city1.c_str(), city2.c_str(), mode.c_str());
                subtrips->Add(theSubtrip);

                city1 = city2;
            }

            Trip *trip = new CompoundTrip(subtrips);
            parseResults->Add(trip);
        }
        else
        {
            cerr << "Erreur: ligne " << lineIndex << "." << endl;
            cerr << "  ‘@’ ou ‘>’ attendu" << endl;
            cerr << "  mais “" << line << "” trouvé." << endl;

            isInvalidInput = true;
            break;
        }
    }

    input.close();

    if (isInvalidInput)
    {
        const unsigned int n = parseResults->Size();
        for (unsigned int i = 0; i < n; i++)
        {
            delete parseResults->Get(i);
        }
        delete parseResults;

        return nullptr;
    }

    return parseResults;
}

void Parser::FiltreParType(ListOfTrips *trips, bool shouldFreeMemory, Trip::TYPE typeTrajet)
{
    unsigned int nRemoved = 0;
    const unsigned int n = trips->Size();

    for (unsigned int i = 0; i < n; i++)
    {
        const unsigned int j = i - nRemoved;
        if (trips->Get(j)->GetType() != typeTrajet)
        {
            const Trip *t = trips->Remove(j);
            if (shouldFreeMemory)
            {
                delete t;
            }
            nRemoved++;
        }
    }
}

void Parser::FiltreParIndex(ListOfTrips *trips, bool shouldFreeMemory, unsigned int debut, unsigned int fin)
{
    unsigned int nRemoved = 0;
    const unsigned int n = trips->Size();

    for (unsigned int i = 0; i < debut; i++)
    {
        const Trip *t = trips->Remove(i - nRemoved);
        if (shouldFreeMemory)
        {
            delete t;
        }
        nRemoved++;
    }

    for (unsigned int i = fin + 1; i < n; i++)
    {
        const Trip *t = trips->Remove(i - nRemoved);
        if (shouldFreeMemory)
        {
            delete t;
        }
        nRemoved++;
    }
}

void Parser::FiltreParNom(ListOfTrips *trips, bool shouldFreeMemory, const char *startCitySearch, const char *endCitySearch)
{
    unsigned int nRemoved = 0;
    const unsigned int n = trips->Size();

    for (unsigned int i = 0; i < n; i++)
    {
        const Trip *trip = trips->Get(i - nRemoved);

        const bool startCityValid = (strlen(startCitySearch) == 0) || (strcmp(trip->GetStart(), startCitySearch) == 0);
        const bool endCityValid = (strlen(endCitySearch) == 0) || (strcmp(trip->GetEnd(), endCitySearch) == 0);

        if (!startCityValid || !endCityValid)
        {
            const Trip *t = trips->Remove(i - nRemoved);
            if (shouldFreeMemory)
            {
                delete t;
            }
            nRemoved++;
        }
    }
}

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
