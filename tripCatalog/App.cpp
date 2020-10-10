/*************************************************************************
                           App  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <App> (fichier App.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "App.h"
#include "CompoundTrip.h"
#include "ListOfTrips.h"
#include "Parser.h"
#include "SimpleTrip.h"
#include "Trip.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int App::Run()
{
    cout << "Bienvenue dans l'application de gestion de trajets !" << endl;
    App::MenuStatus res = menuPrincipal();
    return (res == MenuStatus::ERROR) ? 1 : 0;
} //----- Fin de App::Run

const char *App::Ask(const char *question)
{
    cout << question;

    char *answer = new char[UI_BUFFER_SIZE]{0};

    cin.getline(answer, UI_BUFFER_SIZE);

    if (answer[0] == '\0' || cin.eof() || cin.fail())
    {
        cin.clear();             // on efface les bits d'erreur du flux std::cin
        cin.ignore(10000, '\n'); // skip new line

        delete[] answer;
        return nullptr;
    }

    return answer;
} //----- Fin de App::Ask

int App::Choose(const unsigned int nChoices, const char *choices[])
{
    unsigned int answer = 0;

    for (unsigned int i = 1; i < nChoices; i++)
    {
        cout << "| " << i << ". " << choices[i] << endl;
    }

    // Quitter ou retourner au menu précédent
    cout << "| " << 0 << ". " << choices[0] << endl;

    cout << "--> ";

    cin >> answer;

    if (cin.eof())
    {
        return 0; // quit
    }

    if (cin.fail())
    {
        cin.clear();             // on efface les bits d'erreur du flux std::cin
        cin.ignore(10000, '\n'); // skip new line

        return -1; // ask again
    }

    cin.clear(); // on efface les bits d'erreur du flux std::cin

    cin.ignore(10000, '\n'); // skip new line

    if (answer >= nChoices)
    {
        return -1;
    }

    return answer; // [0 ; nChoices]
} //----- Fin de App::Choose

void App::Error(const char *message)
{
    cerr << "Erreur: " << message << endl;
} //----- Fin de App::Error

void App::MenuTitle(const char *title)
{
    cout << endl
         << "--- " << title << " ---" << endl;
} //----- Fin de App::Error

//-------------------------------------------- Constructeurs - destructeur
App::App()
    : catalog(new Catalog())
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <App>" << endl;
#endif
} //----- Fin de App

App::~App()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <App>" << endl;
#endif
    delete catalog;
} //----- Fin de ~App

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

App::MenuStatus App::menuPrincipal()
{
    const int nChoices = 6;
    const char *choices[] = {
        "Quitter l'application",
        "Consulter le catalogue",
        "Ajouter un trajet",
        "Rechercher un trajet",
        "Charger un fichier",
        "Sauvegarder dans un fichier"};

    while (true)
    {
        App::MenuTitle("MENU PRINCIPAL");
        const int ans = App::Choose(nChoices, choices);

        MenuStatus status = MenuStatus::DONE;
        switch (ans)
        {
        case 0:
            return MenuStatus::DONE; // exit normally
            // break;
        case 1:
            status = App::menuConsulter();
            break;
        case 2:
            status = App::menuAjouter();
            break;
        case 3:
            status = App::menuRechercher();
            break;
        case 4:
            status = App::menuCharger();
            break;
        case 5:
            status = App::menuSauvegarder();
            break;
        default:
            App::Error("Cette option n'existe pas.");
            continue;
        }

        if (status == MenuStatus::ERROR)
        {
            return status;
        }
        else
        {
            continue;
        }
    }
}

App::MenuStatus App::menuConsulter() const
{
    App::MenuTitle("CONSULTATION DU CATALOGUE");
    catalog->Display();
    return MenuStatus::DONE;
}

App::MenuStatus App::menuAjouter()
{
    App::MenuTitle("AJOUTER UN TRAJET");
    cout << "Veuillez choisir un type de trajet." << endl;

    const int nChoices = 3;
    const char *choices[] = {"Retourner au menu principal", "Trajet simple", "Trajet composé"};

    while (true)
    {
        const int ans = App::Choose(nChoices, choices);

        switch (ans)
        {
        case 0:
            return MenuStatus::DONE;
        case 1:
            return App::menuAjouterTrajetSimple();
        case 2:
            return App::menuAjouterTrajetCompose();
        default:
            App::Error("Cette option n'existe pas.");
            break;
        }

        return MenuStatus::DONE;
    }
}

App::MenuStatus App::menuAjouterTrajetSimple()
{
    App::MenuTitle("AJOUTER UN TRAJET SIMPLE");
    cout << "Veuillez entrer les informations du trajet." << endl;

    const char MSG_DEP[] = "* Ville de départ:   ";
    const char MSG_ARR[] = "* Ville d'arrivée:   ";
    const char MSG_MOD[] = "* Mode de transport: ";

    const char *startName = App::Ask(MSG_DEP);
    if (startName == nullptr)
        return MenuStatus::DONE;

    const char *endName = App::Ask(MSG_ARR);
    if (endName == nullptr)
        return MenuStatus::DONE;

    if (!strcmp(startName, endName)) // startName equals endName
    {
        delete[] startName;
        delete[] endName;

        App::Error("La ville d'arrivée doit être différente de la ville de départ. "
                   "Le trajet simple n'a pas été enregistré.");
        return MenuStatus::DONE;
    }

    const char *mode = App::Ask(MSG_MOD);
    if (mode == nullptr)
        return MenuStatus::DONE;

    Trip *trip = new SimpleTrip(startName, endName, mode);
    catalog->Add(trip);

    delete[] startName;
    delete[] endName;
    delete[] mode;

    return MenuStatus::DONE;
}

App::MenuStatus App::menuAjouterTrajetCompose()
{
    App::MenuTitle("AJOUTER UN TRAJET COMPOSÉ");
    cout << "Appuyez sur [entrée] à tout moment pour quitter." << endl
         << "Tous les sous-trajets valides seront enregistrés.";

    const char MSG_DEP[] = "  | Ville de départ:   ";
    const char MSG_ARR[] = "  | Ville d'arrivée:   ";
    const char MSG_MOD[] = "  | Mode de transport: ";

    ListOfTrips *trips = new ListOfTrips(4);

    unsigned int k = 0;
    while (true)
    {
        cout << endl
             << "Trajet #" << (k + 1) << endl;

        char *nonConstStartName = nullptr;

        if (k == 0)
        {
            // S'il s'agit du premier trajet, alors on demande le nom de la ville de départ.
            const char *answer = App::Ask(MSG_DEP);

            if (answer == nullptr)
            {
                break;
            }

            const long unsigned int len = strlen(answer);
            nonConstStartName = new char[len + 1]{0};
            nonConstStartName = strncpy(nonConstStartName, answer, len);

            delete[] answer;
        }
        else
        {
            // S'il ne s'agit pas du premier trajet,
            // alors on connait déjà le nom de sa ville de départ
            // puisqu'il s'agit du nom de la dernière ville d'arrivée.
            const char *lastEndCityName = trips->GetLast()->GetEnd();

            const long unsigned int len = strlen(lastEndCityName);
            nonConstStartName = new char[len + 1]{0};
            nonConstStartName = strncpy(nonConstStartName, lastEndCityName, len);

            cout << MSG_DEP << nonConstStartName << " [valeur remplie automatiquement]" << endl;
        }

        const char *startName = nonConstStartName;
        if (startName == nullptr)
        {
            break;
        }

        const char *endName = App::Ask(MSG_ARR);
        if (endName == nullptr)
        {
            delete[] startName;
            break;
        }
        if (!strcmp(startName, endName)) // startName equals endName
        {
            delete[] startName;
            delete[] endName;
            const unsigned int nSubTrips = trips->Size();
            for (unsigned int i = 0; i < nSubTrips; i++)
            {
                delete trips->Get(i);
            }
            delete trips;

            App::Error("La ville d'arrivée doit être différente de la ville de départ. "
                       "Le trajet composé n'a pas été enregistré.");
            return MenuStatus::DONE;
        }

        const char *mode = App::Ask(MSG_MOD);
        if (mode == nullptr)
        {
            delete[] startName;
            delete[] endName;
            break;
        }

        Trip *trip = new SimpleTrip(startName, endName, mode);
        trips->Add(trip);

        delete[] startName;
        delete[] endName;
        delete[] mode;

        k++;
    }

    const unsigned int nSubTrips = trips->Size();
    if (nSubTrips == 0) // trips est vide
    {
        for (unsigned int i = 0; i < nSubTrips; i++)
        {
            delete trips->Get(i);
        }
        delete trips;
        App::Error("Pas assez de sous-trajets dans le trajet composé en cours de création. "
                   "Le trajet composé n'a pas été enregistré.");
        return MenuStatus::DONE;
    }
    else
    {
        CompoundTrip *compoundTrip = new CompoundTrip(trips);
        catalog->Add(compoundTrip);

        cout << "Vous avez ajouté un nouveau trajet." << endl;
        compoundTrip->Display();

        return MenuStatus::DONE;
    }
}

App::MenuStatus App::menuRechercher() const
{
    App::MenuTitle("RECHERCHER UN TRAJET");
    cout << "Veuillez renseigner les paramètres de recherche." << endl;

    const char MSG_DEP[] = "  | Ville de départ: ";
    const char MSG_ARR[] = "  | Ville d'arrivée: ";

    const char *startName = App::Ask(MSG_DEP);
    if (startName == nullptr)
    {
        return MenuStatus::DONE;
    }

    const char *endName = App::Ask(MSG_ARR);
    if (endName == nullptr)
    {
        delete[] startName;
        return MenuStatus::DONE;
    }

    const int nChoices = 3;
    const char *choices[] = {"Retourner au menu principal", "Recherche simple", "Recherche avancée"};

    SearchResults *results = nullptr;
    while (results == nullptr)
    {
        cout << endl
             << "Veuillez choisir un type de recherche." << endl;
        const int ans = App::Choose(nChoices, choices);

        switch (ans)
        {
        case 0:
            delete startName;
            delete endName;
            return MenuStatus::DONE;
        case 1:
            results = catalog->Search(startName, endName);
            break;
        case 2:
            results = catalog->SearchV2(startName, endName);
            break;
        default:
            App::Error("Cette option n'existe pas.");
            // return MenuStatus::DONE;
            break;
        }
    }

    const unsigned int nResults = results->Size();

    if (nResults == 0)
    {
        cout << "Pas de trajet trouvé"
             << " entre " << startName << " et " << endName << "." << endl
             << endl;
    }
    else
    {
        cout << "Il y a " << nResults << " résultat" << (nResults > 1 ? "s" : "") << " de recherche"
             << " entre " << startName << " et " << endName << "." << endl
             << endl;

        for (unsigned int i = 0; i < nResults; i++)
        {
            ListOfTrips *subResult = results->Get(i);
            cout << "[Résultat N°" << (i + 1) << "]: ";

            const unsigned int nSubResult = subResult->Size();
            if (nSubResult == 1)
            {
                subResult->Get(0)->Display();
            }
            else
            {
                cout << endl;
                for (unsigned int j = 0; j < nSubResult; j++)
                {
                    cout << " |-[" << (j + 1) << "/" << nSubResult << "]: ";
                    subResult->Get(j)->Display();
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    delete[] startName;
    delete[] endName;
    for (unsigned int i = 0; i < results->Size(); i++)
    {
        // ATTENTION: on ne delete pas les trajets
        // contenus dans les sous-résultats car ils
        // ne sont que des références (pointeurs)
        // vers des objets qui sont présents dans le catalogue.

        // ListOfTrips *x = results->Get(i);
        // for (unsigned int j = 0; j < x->Size(); j++)
        // {
        //     delete x->Get(j);
        // }
        delete results->Get(i);
    }
    delete results;

    return MenuStatus::DONE;
}

App::MenuStatus App::menuSauvegarder() const
{
    App::MenuTitle("SAUVEGARDER LE CATALOGUE");

    const unsigned int nTrips = catalog->Size();

    if (nTrips == 0)
    {
        cout << "Sauvegarde annulée, le catalogue ne contient aucun trajet." << endl;
        return MenuStatus::DONE;
    }

    // On demande le nom du fichier de sortie
    string filename;
    cout << "Chemin du fichier de sauvegarde : ";
    std::getline(cin, filename);

    // On ouvre le fichier
    ofstream output(filename);

    // On affiche une erreur s'il est impossible d'ouvrir le fichier
    if (output.fail()) // diapo N°43
    {
        App::Error("Impossible d'ouvrir le fichier de sauvegarde.");
        return MenuStatus::DONE;
    }

    ListOfTrips *filteredList = new ListOfTrips(nTrips);

    for (unsigned int i = 0; i < nTrips; i++)
    {
        filteredList->Add(catalog->Get(i));
    }

    // shouldFreeMemory = false
    // On ne doit pas libérer la mémoire car la liste est dupliquée (en surface)
    const MenuStatus status = menuFiltrer(filteredList, false);
    if (status == MenuStatus::ERROR)
    {
        cout << "Sauvegarde annulée." << endl;

        // Attention : on ne libére pas la mémoire des trajets pointés
        delete filteredList;

        return MenuStatus::DONE;
    }

    const unsigned int nToSave = filteredList->Size();

    for (unsigned int i = 0; i < nToSave; i++)
    {
        Trip *trajet = filteredList->Get(i);
        trajet->Serialize(output);
    }

    cout << nToSave << " trajets sauvegardés vers le fichier " << filename << endl;

    delete filteredList; // N'est qu'un type conteneur,
                         // donc ne contient que des pointeurs,
                         // et donc ne delete pas ses enfants.

    output.close();

    return MenuStatus::DONE;
}

App::MenuStatus App::menuCharger()
{
    App::MenuTitle("CHARGER DES TRAJETS DEPUIS UN FICHIER");

    // On demande le nom du fichier d'entrée
    string filename;
    cout << "Chemin du fichier à charger : ";
    std::getline(cin, filename);

    // On ouvre le fichier
    ifstream input(filename);

    // On affiche une erreur s'il est impossible d'ouvrir le fichier
    if (input.fail()) // diapo N°43
    {
        App::Error("Impossible d'ouvrir le fichier à charger.");
        return MenuStatus::DONE;
    }

    ListOfTrips *parseResults = Parser::Parse(input);

    if (parseResults == nullptr)
    {
        cout << "Chargement annulé, le fichier ne respecte pas le bon format de données." << endl;
        return MenuStatus::DONE;
    }

    if (parseResults->Size() == 0)
    {
        cout << "Chargement annulé, le fichier ne contient aucun trajet." << endl;
        delete parseResults;
        return MenuStatus::DONE;
    }

    // shouldFreeMemory = true
    // On libère la mémoire allouée "en trop" dans Parser::Parse
    const MenuStatus status = menuFiltrer(parseResults, true);
    if (status == MenuStatus::ERROR)
    {
        cout << "Chargement annulé." << endl;

        // On n'oublie pas de libérer la mémoire.
        for (unsigned int i = 0; i < parseResults->Size(); i++)
        {
            delete parseResults->Get(i);
        }
        delete parseResults;

        return MenuStatus::DONE;
    }

    const unsigned int nResults = parseResults->Size();
    for (unsigned int i = 0; i < nResults; i++)
    {
        Trip *trip = parseResults->Get(i);
        catalog->Add(trip);
    }

    cout << nResults << " trajets chargés depuis le fichier " << filename << endl;

    delete parseResults; // N'est qu'un type conteneur,
                         // donc ne contient que des pointeurs,
                         // et donc ne delete pas ses enfants.

    input.close();

    return MenuStatus::DONE;
}

App::MenuStatus App::menuFiltrer(ListOfTrips *liste, bool shouldFreeMemory) const // attention, cette méthode modifie la liste en entrée
{
    const int nChoices = 5;
    const char *choices[] = {
        "Annuler et retourner au menu principal",
        "Aucun filtrage",
        "Filtrage par type",
        "Filtrage par nom de ville",
        "Filtrage par position"};

    cout << endl
         << "Veuillez choisir un type de filtre."
         << endl;
    const int ans = App::Choose(nChoices, choices);

    switch (ans)
    {
    case 0:
        return MenuStatus::ERROR;
        break;
    case 1:
        // On ne fait rien
        break;
    case 2:
    {
        cout << endl
             << "Veuillez choisir un type de de trajet."
             << endl;
        const char *types[] = {"Annuler", "Simple", "Composé"};
        const int ans = App::Choose(3, types);

        if (ans == 0 || ans == -1)
        {
            // On redemande un filtre. On pourrait aussi utiliser
            // une boucle while, mais ça complexifie le code
            // alors que ce n'est pas demandé.
            return App::menuFiltrer(liste, shouldFreeMemory);
        }

        const Trip::TYPE type = ans == 1 ? Trip::TYPE::SIMPLE : Trip::TYPE::COMPOUND;
        Parser::FiltreParType(liste, shouldFreeMemory, type);
        break;
    }
    case 3:
    {
        cout << endl
             << "Veuillez définir les noms des villes :" << endl
             << "[Laissez vide pour ne pas filtrer]" << endl;

        string startCityName;
        string endCityName;

        cout << ("* Ville de départ: ");
        std::getline(cin, startCityName);
        if (!cin)
        {
            break;
        }

        cout << ("* Ville d'arrivée: ");
        std::getline(cin, endCityName);
        if (!cin)
        {
            break;
        }

        Parser::FiltreParNom(liste, shouldFreeMemory, startCityName.c_str(), endCityName.c_str());
        break;
    }
    case 4:
    {
        unsigned int debut;
        unsigned int fin;

        cout << endl
             << "Veuillez définir la plage de sélection"
             << " (indices entre 1 et " << liste->Size() << " inclus) : "
             << endl;

        // les indices sont donnés à partir de 1
        cout << "* Début: ";
        cin >> debut;
        cout << "* Fin:   ";
        cin >> fin;

        if (cin.fail())
        {
            cerr << endl;
            App::Error("Vous devez entrer un nombre.");
            cin.clear();              // on efface les bits d'erreur du flux std::cin
            cin.ignore(10000, '\n');  // skip new line
            return MenuStatus::ERROR; // quit
        }

        if (debut < 1 || fin > liste->Size() || (debut > fin))
        {
            cerr << "Erreur: l'intervalle ["
                 << debut << ", " << fin << "] n'est pas correct." << endl;
            return MenuStatus::ERROR;
        }

        // on transforme les indices pour qu'ils commencent à 0
        Parser::FiltreParIndex(liste, shouldFreeMemory, debut - 1, fin - 1);
        break;
    }
    default:
        App::Error("Cette option n'existe pas.");

        // On redemande un filtre. On pourrait aussi utiliser
        // une boucle while, mais ça complexifie le code
        // alors que ce n'est pas demandé.
        return App::menuFiltrer(liste, shouldFreeMemory);
        // break;
    }

    return MenuStatus::DONE;
}
