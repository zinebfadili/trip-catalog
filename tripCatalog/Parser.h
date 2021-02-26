/*************************************************************************
                           Parser  -  description
                             -------------------
    début                : 2019-11-19
    copyright            : (C) 2019 FADILI Zineb & FORLER Corentin
    e-mail               : zineb.fadili@insa-lyon.fr
                           corentin.forler@insa-lyon.fr
*************************************************************************/

//---- Interface de la classe <Parser> (fichier Parser.h) ----------
#if !defined(PARSER_H)
#define PARSER_H

//--------------------------------------------------- Interfaces utilisées
#include "ListOfTrips.h"
#include <fstream>
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------
// Rôle de la classe <Parser>
// La classe Parser permet de lire une liste de Trip à partir d'un fichier
// Elle est notamment utilisée pour gérer le filtrage (spécifications pour l'enregistrement
// ou chargement de fichiers)
//
// Cette classe contient tout le code nécessaire pour acquérir des trajets issus
// d'un fichier spécifié par l'utilisateur.
// La méthode Parse() est appelée lorsque l'utilisateur souhaite télécharger
// des trajets depuis un fichier.
// Les méthodes de filtrage (FiltreParType(), FiltreParIndex(),
// FiltreParNom()) sont optionnellement appelées si l'utilisateur indique
// vouloir appliquer des spécifications aux trajets qu'il sauvegarde ou
// télécharge.
//------------------------------------------------------------------------

class Parser
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    static ListOfTrips *Parse(ifstream &input);
    // Mode d'emploi :
    // Cette méthode, appelée dans la métthode menuCharger() de la classe
    // App qui lui envoie une référence à un stream correspondant au fichier
    // spécifié par l'utilisateur.
    // Cette méthode se charge de traduire le contenu du fichier texte en trajets
    // et de créer un tableau de pointeurs vers ces trajets qu'elle renvoie.
    // Contrats :
    //  - Le stream qu'elle reçoit en paramètre doit être dans un état fonctionnel
    // cette méthode ne vérifie pas son état.
    //  - La méthode renvoie une liste de pointeurs vers les trajets contenu dans
    // le fichier texte.
    //  - Si le fichier texte ne respecte pas la convention d'écriture établie
    // qui est expliquée en détail dans le compte-rendu, elle retourne un pointeur
    // nul et affiche sur le terminal l'erreur trouvée dans le fichier.

    static void FiltreParType(ListOfTrips *trips, bool shouldFreeMemory, Trip::TYPE typeTrajet);
    // Mode d'emploi :
    // Cette méthode, appelée dans la méthode menuFiltrer(ListOfTrips*, bool)
    // de la classe App qui lui envoie un pointeur vers un ListOfTrips
    // un booléen qui indique si les trajets doivent être supprimés en cas de
    // non correspondance du type (opération effectuée uniquement lors du chargement)
    // et le type de trajet à garder.
    // Cette méthode se charge de ne conserver dans le tableau de pointeurs vers
    // des trajets qu'elle reçoit en paramètre uniquement les trajets dont le type
    // est celui spécfié par l'utilisateur.
    // Contrats :
    //  - La méthode ne supprime en mémoire les trajets pointés par la liste reçue
    // en paramètre que lorsqu'elle est utilisée en chargement (le booléen
    // shouldFreeMemory a pour valeur true). Lors de la sauvegarde, les membres du
    // tableau reçu pointent vers les trajets du catalogue, la méthode ne les supprime donc
    // pas de la mémoire (le booléen shouldFreeMemory a pour valeur false).
    //  - La méthode ne renvoie rien, elle modifie l'un des paramètre qu'elle reçoit.

    static void FiltreParIndex(ListOfTrips *trips, bool shouldFreeMemory, unsigned int debut, unsigned int fin);
    // Mode d'emploi :
    // Cette méthode, appelée dans la méthode menuFiltrer(ListOfTrips*, bool)
    // de la classe App qui lui envoie un pointeur vers un ListOfTrips,
    // un booléen qui indique si les trajets doivent être supprimés en cas de
    // non correspondance des indices (opération effectuée uniquement lors du chargement)
    // et deux entiers naturels : debut et fin indiquant les bornes de l'intervalle
    // des indices des trajets à conserver.
    // Cette méthode se charge de ne conserver dans le tableau de pointeurs vers
    // des trajets qu'elle reçoit en paramètre uniquement les trajets dont l'indice
    // est inclu dans l'intervalle ayant pour borne debut et fin (incluses).
    // Contrats :
    //  - La méthode ne supprime en mémoire les trajets pointés par la liste reçue
    // en paramètre que lorsqu'elle est utilisée en chargement (le booléen
    // shouldFreeMemory a pour valeur true). Lors de la sauvegarde, les membres du
    // tableau reçu pointent vers les trajets du catalogue, la méthode ne les supprime donc
    // pas de la mémoire (le booléen shouldFreeMemory a pour valeur false).
    //  - Les indices donnés en paramètre à cette méthode doivent être valides,
    // c'est à dire compris entre 0 et l'indice du dernier élément du paramètre
    // trips, elle fait aucune vérification.
    //  - La méthode ne renvoie rien, elle modifie l'un des paramètre qu'elle reçoit.

    static void FiltreParNom(ListOfTrips *trips, bool shouldFreeMemory, const char *startCitySearch, const char *endCitySearch);
    // Mode d'emploi :
    // Cette méthode, appelée dans la méthode menuFiltrer(ListOfTrips*, bool)
    // de la classe App qui lui envoie un pointeur vers un ListOfTrips
    // un booléen qui indique si les trajets doivent être supprimés en cas de
    // non respect des critères (opération effectuée uniquement lors du chargement)
    // et deux pointeurs vers des caractères constants: l'un donnant
    // la ville de départ et l'autre la ville d'arrivée. Les chaînes en paramètre
    // peuvent être vides, signifiant que l'utilisateur ne donne pas de condition
    // sur la ville d'arrivé ou de départ. Donner deux chaînes vides équivaut donc
    // à ne pas filtrer du tout.
    // Cette méthode se charge de ne conserver dans le tableau de pointeurs vers
    // des trajets qu'elle reçoit en paramètre uniquement les trajets ayant pour
    // ville de départ et/ou d'arrivée celles reçues en paramètre.
    // Contrats :
    //  - La méthode ne supprime en mémoire les trajets pointés par la liste reçue
    // en paramètre que lorsqu'elle est utilisée en chargement (le booléen
    // shouldFreeMemory a pour valeur true). Lors de la sauvegarde, les membres du
    // tableau reçu pointent vers les trajets du catalogue, la méthode ne les supprime donc
    // pas de la mémoire (le booléen shouldFreeMemory a pour valeur false).
    //  - La méthode ne renvoie rien, elle modifie l'un des paramètre qu'elle reçoit.

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};

#endif // PARSER_H
