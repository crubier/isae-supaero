///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Club
//
//$Nom
//>       OptionsAppli.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionsAppli
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       static int CopieTable()    
//>       static void MessageOption()
//>       class OptionsAppli         
//>         ajouterNonReconnu()      
//>         OptionsAppli()           
//>         operator =()             
//>         ~OptionsAppli()          
//>         ajouterOption()          
//>         usage()                  
//>         initialiser()            
//>         verifier()               
//>         argvReste()              
//>         garantirComplet()        
//>         occurrencesPassees()     
//>         lireValeur()             
//
//$Historique
//       $Log: OptionsAppli.cpp,v $
//       Revision 3.23  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 3.22  2003/02/03 14:00:19  club
//       DM-ID 17 Mise � jour des extensions des fichiers & correction du passage par r�f�rence des objets ClubErreurs
//
//       Revision 3.21  2002/12/10 09:10:35  club
//       DM-ID 12 Modification de l'initialisation des pointeurs/variables.
//
//       Revision 3.20  2001/06/22 05:40:44  club
//       remplacement de l'inclusion de cwctype par l'inclusion de cctype
//
//       Revision 3.19  2001/03/22 11:17:52  club
//       suppression d'une fuite m�moire
//
//       Revision 3.18  2001/02/16 12:44:50  club
//       correction de red�clarations de valeurs par d�faut
//       dans la d�finition de fonctions en ligne
//       ajout de transtypages explicites pour aider le compilateur SUN
//
//       Revision 3.17  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.16  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 3.15  2000/09/07 08:04:23  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include ctype.h
//
//       Revision 3.14  2000/08/30 14:22:20  club
//       Utilisation de hash_map de la STL au lieu de Adressage dans l'impl�mentation
//       de la classe.
//
//       Revision 3.13  2000/07/03 08:57:21  club
//       Ajout du copyright CNES
//
//       Revision 3.12.2.1  2000/03/30 14:46:51  club
//       ajout du copyright CNES
//
//       Revision 3.12  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.11  1999/03/18 10:05:01  club
//       normalisation des d�clarations de cha�nes litt�rales par l'utilisation
//       de const char* au lieu de char*
//
//       Revision 3.10  1998/11/17 11:49:42  club
//       �limination de l'inclusion de ctype.h
//       ajout de (void) explicite pour indiquer que l'on ignore certains retours
//
//       Revision 3.9  1998/08/05 07:02:45  club
//       utilisation de HAVE_INSTANTIATIONS (mis en place par configure)
//
//       Revision 3.8  1998/06/21 15:56:02  luc
//       modification du format de l'en-t�te
//       �limination de la cha�ne statique RCS
//
//       Revision 3.7  1998/04/26 13:02:43  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.6  1997/09/07 09:56:07  luc
//       correction typographique mineure
//
//       Revision 3.5  1997/08/21 16:44:07  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.4  1997/04/11 10:41:57  luc
//       correction du code de retour de OptionsAppli::initialiser
//       
//       Revision 3.3  1997/04/03 12:49:00  luc
//       inversion des codes de retour, 0 signifie d�sormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:13  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 15:20:05  luc
//       *** empty log message ***
//       
//       Revision 2.2  1996/07/26 18:49:33  luc
//       correction d'une erreur sur un caract�re de fin de cha�ne
//       se manifestant lors de l'ajout d'une cha�ne vide � une cha�ne vide
//       
//       Revision 2.1  1996/07/15 17:19:57  luc
//       �limination de la d�pendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour enti�re et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant g�n�rer des erreurs
//       
//       Revision 1.4  1995/01/03 07:58:42  mercator
//       remplacement des variables globales de traduction
//       par des fonctions globales
//       
//       Revision 1.3  1994/11/09 15:02:23  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/30 12:54:27  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:58  luc
//       Initial revision
//
//$Version
//       $Id: OptionsAppli.cpp,v 3.23 2003/07/17 12:38:06 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cctype>
#endif

#include "club/ClubErreurs.h"
#include "club/Traducteur.h"
#include "club/OptionsAppli.h"

static void CopieTable (map<string, OptionBase *>       *dst,
                        const map<string, OptionBase *>& src)
  throw(ClubErreurs)
{ // copie de la table d'adressage

  // nettoyage de la table pr�c�dente
  for (map<string, OptionBase *>::iterator i = dst->begin ();
       i != dst->end ();
       i++)
  { 
    OptionBase *valeur = (*i).second;
    delete valeur;
  }
  dst->clear ();

  for (map<string, OptionBase *>::const_iterator i = src.begin ();
       i != src.end ();
       i++)
  { 
    const string&     clef   = (*i).first;
    const OptionBase *valeur = (*i).second;

    switch (valeur->type ())
    { // allocation d'un �l�ment de la bonne classe d�riv�e

      case OptionBase::tableau_d_entiers :
        { 
          const OptionTableauEntiers *v = (OptionTableauEntiers *) valeur;
          (*dst) [clef] = new OptionTableauEntiers (*v);
        }
        break;

      case OptionBase::tableau_de_reels :
        { 
          const OptionTableauReels *v = (OptionTableauReels *) valeur;
          (*dst) [clef] = new OptionTableauReels (*v);
        }
        break;

      case OptionBase::tableau_de_chaines :
        { 
          const OptionTableauChaines *v = (OptionTableauChaines *) valeur;
          (*dst) [clef] = new OptionTableauChaines (*v);
        }
        break;

      case OptionBase::sans_valeur :
        { 
          const OptionSansValeur *v = (OptionSansValeur *) valeur;
          (*dst) [clef] = new OptionSansValeur (*v);
        }
        break;

      default :
        throw ClubErreurs(ClubErreurs::trace,
                          __LINE__, __FILE__);
    }
  }
}

static void MessageOption (const OptionBase& option, string *ptrMessage)
{ //constitution de la cha�ne de description d'une option

  // prise en compte du code de l'option
  *ptrMessage = " ";
  if (option.occurrencesMin () < 1)
    *ptrMessage += "[";
  if (! option.code ().empty ())
  {
    *ptrMessage += "-";
    *ptrMessage += option.code ();
  }

  // prise en compte des arguments de l'option
  const char *chaineArguments = NULL;
  switch (option.type ())
  { 
    case OptionBase::tableau_d_entiers :
      chaineArguments = " n";
      break;

    case OptionBase::tableau_de_reels :
      chaineArguments = " f.ff";
      break;

    case OptionBase::tableau_de_chaines :
      chaineArguments = " xxxx";
      break;

    case OptionBase::sans_valeur :
      // en fait, dans ce cas, chaineArguments n'est pas utilis�
      // ce cas n'a �t� mis dans ce switch que pour des raisons de clart�
      chaineArguments = " (void)";
      break;

    default :
      chaineArguments = " ???";
      break;
  }

  for (int i = 0; i < option.valeursAttendues (); i++)
    *ptrMessage += chaineArguments;

  if (option.occurrencesMin () < 1)
    *ptrMessage += "]";
}


OptionsAppli::OptionsAppli (const OptionsAppli& opts)
  : tableOptions_ (), nom_ (opts.nom_),
    nombreNonReconnus_ (opts.nombreNonReconnus_),
    initialise_ (opts.initialise_)
{ // copie-constructeur

  // copie de la table d'adressage
  try
  {
    CopieTable (&tableOptions_, opts.tableOptions_);
  }
  catch (ClubErreurs ce)
  {return;}

  // gestion des arguments non reconnus
  if (opts.nombreNonReconnus_ == 0)
    argumentsNonReconnus_ = 0;
  else
  { // copie des arguments non reconnus de la ligne de commande
    argumentsNonReconnus_ = new string [opts.nombreNonReconnus_];
    for (int j = 0; j < opts.nombreNonReconnus_; j++)
      argumentsNonReconnus_ [j] = opts.argumentsNonReconnus_ [j];
  }
}

OptionsAppli& OptionsAppli::operator = (const OptionsAppli& opts)
{ // affectation

  if (this != &opts) // protection contre x = x
  { 
    try
    {
      CopieTable (&tableOptions_, opts.tableOptions_);
    }
    catch(ClubErreurs ce)
    {
      return *this;
    }
    nom_ = opts.nom_;

    // mise � jour de la table des arguments non reconnus
    delete [] argumentsNonReconnus_;

    nombreNonReconnus_ = opts.nombreNonReconnus_;
    if (opts.nombreNonReconnus_ == 0)
      argumentsNonReconnus_ = 0;
    else
    { 
      argumentsNonReconnus_ = new string [opts.nombreNonReconnus_];
      for (int i = 0; i < opts.nombreNonReconnus_; i++)
        argumentsNonReconnus_ [i] = opts.argumentsNonReconnus_ [i];
    }
    initialise_   = opts.initialise_;
  }
  return *this;
}

OptionsAppli::~OptionsAppli ()
{ // nettoyage de l'instance

  // lib�ration des options individuelles
  for (map<string, OptionBase *>::iterator i = tableOptions_.begin ();
       i != tableOptions_.end ();
       i++)
  { 
    OptionBase *valeur = (*i).second;
    delete valeur;
  }
  tableOptions_.clear ();

  // lib�ration des arguments non reconnus
  delete [] argumentsNonReconnus_;
}

void OptionsAppli::ajouterOption (const OptionEntier& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());

  // v�rification du nom et insertion
  OptionEntier* opt = new OptionEntier (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}

void OptionsAppli::ajouterOption (const OptionTableauEntiers& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());

  // v�rification du nom et insertion
  OptionTableauEntiers* opt = new OptionTableauEntiers (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}

void OptionsAppli::ajouterOption (const OptionReel& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());

  // v�rification du nom et insertion
  OptionReel* opt = new OptionReel (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}

void OptionsAppli::ajouterOption (const OptionTableauReels& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());

  // v�rification du nom et insertion
  OptionTableauReels* opt = new OptionTableauReels (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}

void OptionsAppli::ajouterOption (const OptionChaine& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());
  
  // v�rification du nom et insertion
  OptionChaine* opt = new OptionChaine (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}

void OptionsAppli::ajouterOption (const OptionTableauChaines& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());
  
  // v�rification du nom et insertion
  OptionTableauChaines* opt = new OptionTableauChaines (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}

void OptionsAppli::ajouterOption (const OptionSansValeur& option)
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());
  
  // v�rification du nom et insertion
  OptionSansValeur* opt = new OptionSansValeur (option);

  // insertion de la nouvelle paire si l'option n'est pas d�j� d�finie
  pair<string, OptionBase *> arg = make_pair (option.code (),
                                              (OptionBase *) opt);
  if (! tableOptions_.insert (arg).second)
    throw ClubErreurs (ClubErreurs::option_deja_definie,
                       option.code ().c_str ());
}


void OptionsAppli::initialiser (int  argc, const char *const argv [])
  throw (ClubErreurs)
{ 
  if (initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_deja_initialise,
                       nom_.c_str ());
  initialise_ = 1;

  // initialisation des variables de parcours de la ligne de commande
  int iCourant  = 0;
  int iProchain = 1;

  // initialisation des arguments non reconnus avec le nom de l'application
  ajouterNonReconnu (argv [0]);

  // boucle sur les champs
  while (argc > iProchain)
  { 
    iCourant = iProchain;
    iProchain++;
    
    if ((argv [iCourant][0] == '-') && (argv [iCourant][1] == '\0'))
    { // cas particulier de l'option sans nom
      // on signale que le champ suivant est bien une donn�e
      // (m�me s'il commence par un '-' suivi d'une lettre)

      if (iProchain >= argc)
        throw ClubErreurs (ClubErreurs::plus_d_argument, "");

      // s'il n'existe pas de clef dont la valeur est ""
      if (tableOptions_.find ("") == tableOptions_.end ())
      { // on n'attendait pas d'option sans code: argument non reconnu
        ajouterNonReconnu (argv [iProchain]);
      }
      else
      { // on dispose d'une option o� stocker une donn�e sans code
        // les 2 lignes suivantes peuvent lever une exception
        tableOptions_ [""]->ajouterOccurrence ();
        tableOptions_ [""]->ajouterValeur (argv [iProchain]);
      }

      iProchain++;
    }
    else if ((argv [iCourant][0] != '-') || !isalpha (argv [iCourant][1]))
    { // c'est un champ de donn�es: on le consid�re comme une option sans code

      // s'il n'existe pas de clef dont la valeur est ""
      if (tableOptions_.find ("") == tableOptions_.end ())
      { // on n'attendait pas d'option sans code: argument non reconnu
        ajouterNonReconnu (argv [iCourant]);
      }
      else
      { // on dispose d'une option o� stocker une donn�e sans code
        // les 2 lignes suivantes peuvent lever une exception
        tableOptions_ [""]->ajouterOccurrence ();
        tableOptions_ [""]->ajouterValeur (argv [iCourant]);
      }
    }
    else
    { // c'est une option: son code commence apr�s le '-'
      const char* mobile   = argv [iCourant];

      // boucle sur les codes juxtapos�s derri�re le '-'
      while (*++mobile)
      { 
        string code (mobile);
        int continuer = 1;
        while (continuer)
        { 
          // s'il existe une clef �gale � code
          if (tableOptions_.find (code) != tableOptions_.end ())
          { 
            // on a trouv� une option dont le code correspond
            // peut lever une exception
            tableOptions_ [code]->ajouterOccurrence ();
            
            for (int i = 0; i < tableOptions_ [code]->valeursAttendues (); i++)
            { 
              if (iProchain >= argc)
                throw ClubErreurs (ClubErreurs::plus_d_argument,
                                   mobile);
              
              tableOptions_ [code]->ajouterValeur (argv [iProchain]);
              iProchain++;
            }

            // pr�paration de l'analyse de l'option suivante
            // (on se positionne sur le dernier caract�re de l'option courante)
            mobile += code.size () - 1;

            // arr�t de la recherche
            continuer = 0;

          }
          else
          { // aucune option ne correspond au code complet
            if (code.size () > 1)
            { // il s'agit peut-�tre d'une juxtaposition de codes
              // on enl�ve un caract�re � la fin
              code.erase (code.end ()-1);
            }
            else
            { // aucun caract�re de l'option n'est reconnu: on l'�carte

              // reconstitution du nom de l'option
              string avecTiret ("-");
              avecTiret += mobile;
              ajouterNonReconnu (avecTiret.c_str ());

              // arr�t de la recherche
              mobile   += strlen (mobile) - 1;
              continuer = 0;

            }
          }
        }
      }
    }
  }
}


const char *OptionsAppli::usage (unsigned int largeur) const
{ // constitution d'un message d'usage

  static string *ptrChaine = 0;
  if (ptrChaine == 0)
    ptrChaine = new string;

  *ptrChaine  = TraduitVersExterne ("usage : ");
  *ptrChaine += nom_;

  // constitution d'une cha�ne pour pr�parer les indentations
  int colonne = ptrChaine->size ();
  string finLigne ("\n");
  finLigne += string (colonne, ' ');

  string msgOpt;
  map<string, OptionBase *>::const_iterator jSansCode;
  map<string, OptionBase *>::const_iterator j;

  if ((jSansCode = tableOptions_.find ("")) != tableOptions_.end ())
  { // pour des raisons de clart�, on affiche les options sans code
    // avant toutes les autres
    MessageOption (*(*jSansCode).second, &msgOpt);

    // ajout de la description au message courant
    *ptrChaine += msgOpt;
    colonne    += msgOpt.size ();
  }

  for (j = tableOptions_.begin (); j != tableOptions_.end (); j++)
  { // boucle sur les options

    OptionBase* option = (*j).second;
    if (j != jSansCode)
    { // seules les options avec code sont trait�es dans la boucle
      // (les autres ont �t� trait�es avant)
      MessageOption (*option, &msgOpt);

      // la description de l'option tient-elle dans la ligne courante ?
      if (colonne + msgOpt.size () > largeur)
      { // elle ne tient pas, il faut passer � la ligne
        *ptrChaine += finLigne;
        colonne     = finLigne.size () - 1;
      }

      // ajout de la description au message courant
      *ptrChaine += msgOpt;
      colonne    += msgOpt.size ();
    }
  }
  // retour normal � la fonction appelante
  return ptrChaine->c_str ();
}

int OptionsAppli::verifier (string *ptrMessage) const
{
  if (!initialise_)
  { 
    ClubErreurs ue (ClubErreurs::options_appli_non_initialise,
                    nom_.c_str ());
    *ptrMessage = ue.why ();
    ue.correction ();
    return ClubErreurs::options_appli_non_initialise;
  }

  map<string, OptionBase *>::const_iterator i;

  for (i = tableOptions_.begin (); i != tableOptions_.end (); i++)
  { // v�rification de chacune des options
    int r = (*i).second->verifier (ptrMessage);
    if (r)
      return r;
  }
  // retour normal � la fonction appelante
  return 0;
}

void OptionsAppli::argvReste (char** argv)
  throw (ClubErreurs)
{ 
  if (!initialise_)
    throw ClubErreurs(ClubErreurs::options_appli_non_initialise,
                      nom_.c_str ());

  for (int i = 0; i < nombreNonReconnus_; i++)
  { // allocation d'une cha�ne brute pour stocker les arguments
    // la responsabilit� de la d�sallocation incombe � l'appelant
    argv [i] = new char [1 + argumentsNonReconnus_ [i].size ()];
    (void) strcpy (argv [i], argumentsNonReconnus_ [i].c_str ());
  }
}

void OptionsAppli::garantirComplet () const
  throw (ClubErreurs)
{ // v�rification des arguments reconnus
  string message;
  if (verifier (&message))
  { // il y a un probleme � l'analyse

    // ajout de la description des options en fin de message
    message += "\n";
    message += usage ();
    throw ClubErreurs (ClubErreurs::message_simple,
                       message.c_str ());
  }

  // v�rification des arguments non reconnus
  if (nombreNonReconnus_ > 1)
  { // en-t�te du message d'erreur
    ClubErreurs e (ClubErreurs::arguments_non_reconnus, nom_.c_str ());
    message += e.why ();
    e.correction ();

    // affichage des arguments non reconnus (excepte le argv [0])
    for (int i = 1; i < nombreNonReconnus_; i++)
    {
      message += " ";
      message += argumentsNonReconnus_ [i];
    }

    // ajout de la description des options en fin de message
    message += "\n";
    message += usage ();
    throw ClubErreurs (ClubErreurs::message_simple,
                       message.c_str ());
  }
}

int OptionsAppli::occurrencesPassees (const char *code) const
  throw (ClubErreurs)
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());

  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    return (*index).second->occurrencesPassees ();
}

void OptionsAppli::lireValeur (const char  *code,
                               int         *dest, int occurrence) const
  throw (ClubErreurs) 
{
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());

  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (dest, occurrence);
}

void OptionsAppli::lireValeur (const char  *code,
                               double      *dest, int occurrence) const
  throw (ClubErreurs)
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());
  
  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (dest, occurrence);
}

void OptionsAppli::lireValeur (const char  *code,
                               char        *dest, int occurrence) const
  throw (ClubErreurs) 
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());
  
  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (dest, occurrence);
}

void OptionsAppli::lireValeur (const char   *code,
                               string *dest, int occurrence) const
  throw (ClubErreurs) 
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());

  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (dest, occurrence);
}

void OptionsAppli::lireValeur (const char  *code, int nombre,
                               int          dest [], int occurrence) const
  throw (ClubErreurs) 
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());

  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (nombre, dest, occurrence);
}

void OptionsAppli::lireValeur (const char  *code, int nombre,
                               double       dest [], int occurrence) const
  throw (ClubErreurs) 
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());

  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (nombre, dest, occurrence);
}

void OptionsAppli::lireValeur (const char  *code, int nombre,
                               char*        dest [], int occurrence) const
  throw (ClubErreurs) 
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());
  
  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (nombre, dest, occurrence);
}

void OptionsAppli::lireValeur (const char  *code, int nombre,
                               string dest [], int occurrence) const
  throw (ClubErreurs)
{ 
  if (!initialise_)
    throw ClubErreurs (ClubErreurs::options_appli_non_initialise,
                       nom_.c_str ());
  
  map<string, OptionBase *>::const_iterator index = tableOptions_.find (code);

  if (index == tableOptions_.end ())
    throw ClubErreurs (ClubErreurs::code_option_non_reconnu, code);
  else
    (*index).second->lireValeur (nombre, dest, occurrence);
}

void OptionsAppli::ajouterNonReconnu (const char* chaine)
{ // allocation d'une nouvelle table
  string *allouee = new string [nombreNonReconnus_ + 1];

  // copie des anciennes valeurs
  for (int i = 0; i < nombreNonReconnus_; i++)
    allouee [i] = argumentsNonReconnus_ [i];

  // remplacement de l'ancienne table par la nouvelle
  delete [] argumentsNonReconnus_;
  argumentsNonReconnus_ = allouee;

  // prise en compte du nouvel argument
  argumentsNonReconnus_ [nombreNonReconnus_] = chaine;
  nombreNonReconnus_++;
}
