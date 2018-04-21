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
//>       Traducteur.cpp
//
//$Resume
//       fichier d'implantation de la classe Traducteur
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       int domtrad_()                            
//>       void tradext_()                           
//>       void tradint_()                           
//>       void tradform_()                          
//>       void tradecrch_()                         
//>       void tradecrfd_()                         
//>       static void InitTraducteurs()             
//>       static int AjouteDomaineDepuisRepertoire()
//>       int AjouterDomaine()                      
//>       const char* TraduitVersExterne()          
//>       const char* TraduitVersInterne()          
//>       const char* TraduitFormatCVersExterne()   
//>       const char* VariableLangue()              
//>       const char* VariableCheminsTraduction()   
//>       static const char* SpecificateurFormatC() 
//>       static const string& ErreurFormatC()
//>       void InitDomaineClub()                    
//>       class Traducteur                          
//>         Traducteur()                            
//>         operator =()                            
//>         ajouterDomaine()                        
//>         domaineMembre()                         
//>         operator()()                            
//>         traductionFormatC()                     
//>         traductionFormatF()                     
//
//$Historique
//       $Log: Traducteur.cpp,v $
//       Revision 3.26  2003/02/03 14:02:12  club
//       DM-ID 17 Mise � jour des extensions des fichiers & correction du passage par r�f�rence des objets ClubErreurs
//
//       Revision 3.25  2001/03/14 11:12:54  club
//       correction du retour erron� d'un pointeur sur un attribut d'une
//       variable automatique
//
//       Revision 3.24  2001/02/16 12:42:58  club
//       remplacement de la classe hash_map par la classe standard map
//
//       Revision 3.23  2000/10/25 09:31:42  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.22  2000/10/24 14:21:02  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.21  2000/10/24 08:33:31  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 3.20  2000/09/07 08:07:25  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.19  2000/08/30 14:22:21  club
//       Utilisation de hash_map de la STL au lieu de Adressage dans l'impl�mentation
//       de la classe.
//
//       Revision 3.18  2000/08/25 07:39:02  club
//       Suppression du traitement interne du format C et utilisation � la place
//       des services de la classe FormatC.
//
//       Revision 3.17  2000/07/03 08:57:22  club
//       Ajout du copyright CNES
//
//       Revision 3.16.2.1  2000/03/30 14:46:53  club
//       ajout du copyright CNES
//
//       Revision 3.16  1999/07/07 07:55:17  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.15  1998/11/17 11:48:27  club
//       �limination de l'inclusion de ctype.h
//       ajout de (void) explicite pour indiquer que l'on ignore certains retours
//
//       Revision 3.14  1998/08/11 07:46:07  club
//       correction de l'en-t�te
//
//       Revision 3.13  1998/08/11 07:45:06  club
//       ajout des fonctions VariableLangue et VariableCheminsTraduction
//
//       Revision 3.12  1998/08/05 07:02:23  club
//       utilisation de HAVE_INSTANTIATIONS (mis en place par configure)
//
//       Revision 3.11  1998/07/27 10:13:54  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 3.10  1998/06/21 15:56:41  luc
//       modification du format de l'en-t�te
//       �limination de la cha�ne statique RCS
//
//       Revision 3.9  1998/04/26 13:02:56  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.8  1997/08/29 05:31:52  luc
//       ajout des interfaces fortran tradecrch_ et tradecrfd_
//       am�lioration des messages d'erreurs de traduction de formats fortran
//       prise en compte du changement de signature de FormatFortran::applique
//       changement de signature de traductionFormatF
//
//       Revision 3.7  1997/08/27 20:57:01  luc
//       refonte compl�te de la traduction des formats fortran
//
//       Revision 3.6  1997/08/24 13:39:24  luc
//       ajout d'une v�rification du nombre de champs
//       dans les dictionnaires
//
//       Revision 3.5  1997/08/21 16:44:09  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.4  1997/04/28 13:44:14  luc
//       correction d'un oubli d'allocation de ChaineSimple
//       
//       Revision 3.3  1997/04/03 12:49:33  luc
//       inversion des codes de retour, 0 signifie d�sormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:03:59  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 15:21:16  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 2.3  1996/08/05 16:34:58  luc
//       introduction de la reconnaissance des '/' dans les formats fortran
//       
//       Revision 2.2  1996/07/18 14:48:52  luc
//       correction du traitement des blancs dans les cha�nes fortran
//       correction de la gestion des noms de domaines
//       renforcement des v�rifications dans les formats fortran
//       
//       Revision 2.1  1996/07/15 17:31:09  luc
//       �limination de la d�pendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       
//       Revision 1.8  1996/01/15 13:33:35  luc
//       correction d'une confusion de variables
//       (confusion sur les longueurs des mots interne/externe)
//       
//       Revision 1.7  1995/07/12 14:56:24  mercator
//       suppression d'un argument dans une methode privee
//       simplification d'une construction de chaine pour le compilateur SUN
//       
//       Revision 1.6  1995/01/09 07:31:23  mercator
//       changement de l'ordre de recherche dans les repertoires
//       desormais on teste: ".", puis $HOME, puis $MRC_USER_CONFIG, puis $MRC_CONFIG
//       
//       Revision 1.5  1995/01/05 13:03:01  mercator
//       remplacement des variables globales de traduction par des fonctions globales
//       ajout de fonctions de traduction des formats fortran
//       ajout de fonctions d'interface avec le fortran
//       
//       Revision 1.4  1994/11/09 15:03:05  mercator
//       elimination des directives #pragma
//       
//       Revision 1.3  1994/09/28 16:28:37  mercator
//       prise en compte du changement de nom:
//       FichierTexte --> TamponTexte
//       
//       Revision 1.2  1994/08/30 08:42:59  mercator
//       remplacement de l'appel a "lance" par un appel a "erreur"
//       
//       Revision 1.1  1994/07/27 12:06:04  luc
//       Initial revision
//
//$Version
//       $Id: Traducteur.cpp,v 3.26 2003/02/03 14:02:12 club Exp $
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
# include <cstdlib>
#endif

#ifdef HAVE_CSTDARG
# include <cstdarg>
#endif

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#include "club/Traducteur.h"

// d�finition des variables statiques utiles au syst�me g�n�ral
// (seront construites d�s qu'on en aura besoin)
static Traducteur* ptrExterne = 0;
static Traducteur* ptrInterne = 0;


// d�claration des fonctions statiques
static void        InitTraducteurs               ();
static int         AjouteDomaineDepuisRepertoire (const char  *repertoire,
                                                  const char  *domaine);
static const string& ErreurFormatC               (const char *format);

int domtrad_ (const char* domaine, long int lDecl)
{ // ajout d'un domaine de traduction
  InitTraducteurs ();

  // �limination des blancs finaux
  string chaine (domaine, lDecl);
  int pos = chaine.find_last_not_of ("\n\t\v\b\r ");
  chaine.erase (pos+1);
  return AjouterDomaine (chaine.c_str ());

}

void tradext_  (const char* interne,  char*    externe, int& lUtile,
                long int lDeclInt, long int lDeclExt)
{ // traduction d'un mot-clef interne dans la langue utilisateur
  InitTraducteurs ();

  // conservation d'une cha�ne de caract�res de travail statique
  // pour �viter les r�allocations multiples
  static string *ptrChaine = 0;
  if (ptrChaine == 0)
    ptrChaine = new string;
  ptrChaine->replace (ptrChaine->begin (), ptrChaine->end (), 
                      interne, lDeclInt);

  // �limination des blancs finaux
  int pos = ptrChaine->find_last_not_of ("\n\t\v\b\r ");
  ptrChaine->erase (pos+1);

  // traduction
  const string& traduit = (*ptrExterne) (ptrChaine->c_str ());

  // copie des r�sultats dans les variables fortran
  if (traduit.size () > (long unsigned int) lDeclExt)
  { // la traduction ne tient pas dans le tableau, on abandonne la traduction
    lUtile = ptrChaine->size ();
    (void) strncpy (externe, ptrChaine->c_str (), lUtile);
  }
  else
  { 
    lUtile = traduit.size ();
    (void) strncpy (externe, traduit.c_str (), lUtile);
  }

  if (lDeclExt > lUtile)
  { // on compl�te la cha�ne fortran par des blancs
    char *ptr   = externe + lUtile;
    int   reste = lDeclExt - lUtile;
    while (reste-- > 0)
      *ptr++ = ' ';
  }
}

void tradint_  (const char* externe,  char*    interne, int& lUtile,
                long int    lDeclExt, long int lDeclInt)
{ // traduction d'un mot-clef utilisateur dans la langue interne
  InitTraducteurs ();

  // conservation d'une cha�ne de caract�res de travail statique
  // pour �viter les r�allocations multiples
  static string *ptrChaine = 0;
  if (ptrChaine == 0)
    ptrChaine = new string;
  ptrChaine->replace (ptrChaine->begin (), ptrChaine->end (), 
                      interne, lDeclInt);

  // �limination des blancs finaux
  int pos = ptrChaine->find_last_not_of ("\n\t\v\b\r ");
  ptrChaine->erase (pos+1);

  // traduction
  const string& traduit = (*ptrInterne) (ptrChaine->c_str ());

  // copie des r�sultats dans les variables fortran
  if (traduit.size () > (long unsigned int) lDeclInt)
  { // la traduction ne tient pas dans le tableau, on abandonne la traduction
    lUtile = ptrChaine->size ();
    (void) strncpy (interne, ptrChaine->c_str (), lUtile);
  }
  else
  {
    lUtile = traduit.size ();
    (void) strncpy (interne, traduit.c_str (), lUtile);
  }

  if (lDeclInt > lUtile)
  { // on compl�te la cha�ne fortran par des blancs
    char *ptr   = interne + lUtile;
    int   reste = lDeclInt - lUtile;
    while (reste-- > 0)
      *ptr++ = ' ';
  }
}

void tradform_  (const char* interne, char* externe, int& lUtile,
                 long int lDeclInt, long int lDeclExt)
{ // traduction d'un format fortran
  InitTraducteurs ();

  // conservation d'une cha�ne de caract�res de travail statique
  // pour �viter les r�allocations multiples
  static string *ptrChaine = 0;
  if (ptrChaine == 0)
    ptrChaine = new string;
  ptrChaine->replace (ptrChaine->begin (), ptrChaine->end (), 
                      interne, lDeclInt);

  // �limination des blancs finaux
  int pos = ptrChaine->find_last_not_of ("\n\t\v\b\r ");
  ptrChaine->erase (pos+1);

  // traduction
  FormatFortran traduit;
  (void) ptrExterne->traductionFormatF (ptrChaine->c_str (), &traduit);

  // copie des r�sultats dans les variables fortran
  if (traduit.chaine ().size () > (long unsigned int) lDeclExt)
  { // la traduction ne tient pas dans le tableau, on abandonne la traduction
    lUtile = ptrChaine->size ();
    (void) strncpy (externe, ptrChaine->c_str (), lUtile);
  }
  else
  {
    lUtile = traduit.chaine ().size ();
    (void) strncpy (externe, traduit.chaine ().c_str (), lUtile);
  }

  if (lDeclExt > lUtile)
  { // on compl�te la cha�ne fortran par des blancs
    char *ptr   = externe + lUtile;
    int   reste = lDeclExt - lUtile;
    while (reste-- > 0)
      *ptr++ = ' ';
  }
}

void tradecrch_  (char* chaine, int& lUtile, const char* format ...)
{ // �criture dans une cha�ne � partir d'un format fortran
  InitTraducteurs ();

  // traduction
  FormatFortran traduit;
  if (ptrExterne->traductionFormatF (format, &traduit) > 0)
  { // on ne peut pas utiliser le format retourn� pour analyser les
    // arguments variables, on ne peut m�me pas retrouver les longueurs
    // des cha�nes ...

    // on suppose tout de m�me que l'on peut �crire un caract�re ...
    *chaine = '?';
    lUtile  = 1;
    return;
  }

  int nbLong = 2;
  long int tabLg [2];
  string sortie;

  // �criture
  va_list ap;
  va_start(ap, format);
  ap = traduit.applique (ap, nbLong, tabLg, &sortie);
  va_end(ap);

  // copie des r�sultats dans les variables fortran
  lUtile = (sortie.size () < (long unsigned int) tabLg [0]) ? sortie.size () : tabLg [0];
  (void) strncpy (chaine, sortie.c_str (), lUtile);
  if (tabLg [0] > lUtile)
  { // on compl�te la cha�ne fortran par des blancs
    char *ptr   = chaine + lUtile;
    int   reste = tabLg [0] - lUtile;
    while (reste-- > 0)
      *ptr++ = ' ';
  }
}

void tradecrfd_  (int& fd, const char* format ...)
{ // �criture dans un descripteur de fichier � partir d'un format fortran
  InitTraducteurs ();

  // traduction (on sait qu'en cas de probl�me traductionFormatF
  // retourne un format qui ne consomme pas d'argument variable, comme
  // ici nous n'en avons pas besoin non plus on peut se permettre
  // d'ignorer un retour sur erreur et utiliser le format tel quel)
  FormatFortran traduit;
  (void) ptrExterne->traductionFormatF (format, &traduit);

  int nbLong = 1;
  long int tabLg [1];
  string sortie;

  // �criture
  va_list ap;
  va_start(ap, format);
  ap = traduit.applique (ap, nbLong, tabLg, &sortie);
  va_end(ap);

  // �criture
  sortie += '\n';
  (void) write (fd, sortie.c_str (), sortie.size ());
}

static void InitTraducteurs ()
{ // allocation des objets statiques
  if (ptrExterne == 0)
    ptrExterne = new Traducteur;
  if (ptrInterne == 0)
    ptrInterne = new Traducteur;
}

static int AjouteDomaineDepuisRepertoire (const char *repertoire,
                                          const char *domaine)
{ // recherche du domaine dans un r�pertoire donn�

  // constitution du nom complet du fichier de domaine
  string nomFichier (repertoire);
  if (nomFichier[nomFichier.size ()-1] != '/')
    nomFichier += "/";
  nomFichier += ptrExterne->langueUtilisateur ();
  nomFichier += "/";
  nomFichier += domaine;
  
  if (access (nomFichier.c_str (), R_OK) == 0)
  { // la ressource existe
    try
    {
      TamponTexte fichier (nomFichier.c_str ());
      
      if (! ptrExterne->domaineMembre (domaine))
        ptrExterne->ajouterDomaine (domaine, fichier, 1);
      if (! ptrInterne->domaineMembre (domaine))
        ptrInterne->ajouterDomaine (domaine, fichier, 0);
      
      // le r�pertoire test� �tait le bon
      return 0;
      
    }
    catch(ClubErreurs ce)
    {
      // on n'a pas pu creer le TamponTexte
      ce.correction();
    }
  }
  // le r�pertoire test� ne convenait pas
  return 1;
}

int AjouterDomaine (const char* domaine)
{ // initialisation �ventuelle des instances statiques g�n�rales
  InitTraducteurs ();

  char* temp_str = getenv (CL_VAR_TRADPATH);
  if (temp_str == 0)
    return 1;

  string chemin (temp_str);
  const char *debut = chemin.c_str ();
  while (debut)
  { // analyse du prochain r�pertoire sp�cifi� dans le chemin

    // s�paration du nom du r�pertoire
    const char *fin = strchr (debut, ':');
    if (fin != 0)
      chemin [fin - chemin.c_str ()] = '\0';

    // test du r�pertoire (un nom vide repr�sente le r�pertoire courant, comme PATH)
    if (! AjouteDomaineDepuisRepertoire ((*debut) ? debut : ".", domaine))
      return 0;

    // passage au r�pertoire suivant
    debut = (fin == 0) ? 0 : (fin + 1);
  }

  // on n'a pas trouv� le domaine
  return 1;

}

const char* TraduitVersExterne (const char* interne)
{
  InitTraducteurs ();
  return (*ptrExterne) (interne).c_str ();
}

const char* TraduitVersInterne (const char* externe)
{ 
  InitTraducteurs ();
  return (*ptrInterne) (externe).c_str ();
}

const char* TraduitFormatCVersExterne (const char* format)
{ 
  InitTraducteurs ();
  return ptrExterne->traductionFormatC (format).c_str ();
}

const char* VariableLangue ()
{ return CL_VAR_LANG; }

const char* VariableCheminsTraduction ()
{ return CL_VAR_TRADPATH; }


static const string& ErreurFormatC (const char *format)
{ // production d'un format signalant une erreur de traduction

  // variables permettant de constituer un message en cas d'erreur
  static string *ptrChaine = 0;
  if (ptrChaine == 0)
    ptrChaine = new string;

  *ptrChaine  = "FORMAT TRADUIT INCOMPATIBLE, PAS DE TRADUCTION : ";
  *ptrChaine += format;
  return *ptrChaine;
}

void InitDomaineClub ()
{ // initialisation des domaines de traduction pour la biblioth�que club
  static int dejaInitialise = 0;

  if (!dejaInitialise)
  { 
    dejaInitialise = 1;

    // le m�canisme de traduction n'est qu'un "plus" qui peut travailler
    // sans le fichier de ressource (les messages sont alors ceux du code),
    // on ignore donc ici l'erreur d'acc�s au domaine de traduction
    (void) AjouterDomaine ("club");
  }

}

Traducteur::Traducteur ()
  : tableCorrespondance_ (), nbDomaines_ (0), domaines_ (0),
    langueUtilisateur_ ("??")
{ //constructeur par d�faut
  const char* langue = getenv (CL_VAR_LANG);
  if (langue != 0)
    langueUtilisateur_ = langue;
}

Traducteur::Traducteur (const Traducteur& t)
  : tableCorrespondance_ (t.tableCorrespondance_), nbDomaines_ (t.nbDomaines_),
    domaines_ (0), langueUtilisateur_ (t.langueUtilisateur_)
{ // constructeur par copie

  if (nbDomaines_)
  { // il y a une table que l'on doit copier
    domaines_ = new string [nbDomaines_];
    for (int i = 0; i < nbDomaines_; i++)
      domaines_ [i] = t.domaines_ [i];
  }

}

Traducteur& Traducteur::operator = (const Traducteur& t)
{ 
  if (this != &t)     // protection contre x = x
  { // nettoyage pr�alable de l'instance
    if (nbDomaines_)
      delete [] domaines_;

    // copie
    map<string, string>::const_iterator i;
    for (i=t.tableCorrespondance_.begin (); i!=t.tableCorrespondance_.end (); i++)
      tableCorrespondance_[(*i).first] = (*i).second;

    nbDomaines_          = t.nbDomaines_;

    if (nbDomaines_)
    { // il y a une table que l'on doit copier
      domaines_ = new string [nbDomaines_];
      for (int j = 0; j < nbDomaines_; j++)
        domaines_ [j] = t.domaines_ [j];
    }
    else
      domaines_ = 0;
    langueUtilisateur_ = t.langueUtilisateur_;
  }
  return *this;
}

void Traducteur::ajouterDomaine (const char   *domaine,
                                 TamponTexte&  fichier,
                                 int           cleSurChampsImpairs)
{ // recherche du domaine dans la table d�j� g�r�e
  for (int i = 0; i < nbDomaines_; i++)
    if (domaines_ [i] == domaine)
      return;

  // pr�paration de la lecture
  try
  {
    fichier.elimineCommentaires ();
    fichier.elimineBlancs       ();
  }
  catch(ClubErreurs ce)
  { // la traduction n'�tant qu'un plus, on ignore les erreurs
    ce.correction ();
    return;
  }

  if (fichier.nombreChamps () % 2)
  { // le fichier comporte un nombre impair de champs : il est inutilisable
    return;
  }

  // ajout d'une entr�e � la table des domaines
  string *nouvelleTableDomaines = new string [nbDomaines_ + 1];
  for (int j = 0; j < nbDomaines_; j++)
    nouvelleTableDomaines [j] = domaines_ [j];
  nouvelleTableDomaines [nbDomaines_++] = domaine;

  delete [] domaines_;
  domaines_ = nouvelleTableDomaines;

  // analyse du fichier
  for (int k = 1; k <= fichier.nombreChamps (); k += 2)
  { // analyse d'un couple de cha�nes dans les langues interne et externe

    // lecture des cha�nes par la m�thode TamponTexte::champ qui retourne un
    // pointeur sur une cha�ne priv�e
    try
    {
      string s_impair (fichier.champ (k));
      string s_pair   (fichier.champ (k + 1));

      if (cleSurChampsImpairs)
        tableCorrespondance_.insert (make_pair (s_impair, s_pair));
      else
        tableCorrespondance_.insert (make_pair (s_pair, s_impair));
    }
    catch(ClubErreurs ce)
    { // la traduction n'�tant qu'un plus, on ignore les erreurs
      ce.correction();
    }
  }
}

int Traducteur::domaineMembre (const char *domaine) const
{ // recherche du domaine dans la table d�j� g�r�e
  for (int i = 0; i < nbDomaines_; i++)
    if (domaines_ [i] == domaine)
      return 1;
  return 0;
}

const string& Traducteur::operator () (const char *clef) const
{ // recherche de la clef dans la table

  map<string, string>::const_iterator index;
  index = tableCorrespondance_.find (clef);
  if (index != tableCorrespondance_.end ())
  {
    // on retourne une r�f�rence constante. Il faut donc utiliser un objet
    // statique pour fournir la valeur de retour.
    static string *ptrChaine = 0;
    if (ptrChaine == 0)
      ptrChaine = new string;
    
    *ptrChaine = (*index).second;  
    return *ptrChaine;
  }
  else
  { // si la clef n'existe pas, on retourne une copie de la cha�ne d'entr�e
    static string *ptrCopie = 0;
    if (ptrCopie == 0)
      ptrCopie = new string;

    *ptrCopie = clef;
    return *ptrCopie;
  }
}

const string& Traducteur::traductionFormatC (const char *format) const
{
  // traduction directe
  FormatC  origine (format);

  // on retourne une r�f�rence constante. Il faut donc utiliser un objet
  // statique pour fournir la valeur de retour.
  static FormatC *ptrTraduit = 0;
  if (ptrTraduit == 0)
    ptrTraduit = new FormatC;
  ptrTraduit->analyse (operator () (format));

  // v�rification de la compatibilit� des formats
  if (! origine.compatible (*ptrTraduit))
    return ErreurFormatC (format);

  // retour du format traduit sous forme compatible
  return ptrTraduit->chaine ();
}

int Traducteur::traductionFormatF (const char *format,
                                   FormatFortran *ptrTrad) const
{ // traduction d'un format fortran

  // analyse des sp�cificateurs pr�sents dans le format origine
  try
  {
    FormatFortran origine (format);
    try
    {
      // analyse des sp�cificateurs pr�sents dans le format traduit
      FormatFortran traduit (operator () (format));
      if (! origine.compatible (traduit))
      { // le format traduit n'attend pas les bons arguments
        string formatQuote ("('FORMAT TRADUIT INCOMPATIBLE,"
                            " PAS DE TRADUCTION : ',");
        formatQuote += origine.chaine ();
        formatQuote += ")";
        try
        {
          ptrTrad->analyse (formatQuote);
        }
        catch(ClubErreurs ce)
        {
          ce.correction ();
        }
        return -1;   // indique que l'on peut utiliser ce format
      }
      // la traduction a fonctionn� correctement
      *ptrTrad = traduit;
      return 0;
    }

    catch(ClubErreurs ce)
    { // le format traduit est inutilisable, on reprend l'origine
      ce.correction ();
      string formatQuote ("('FORMAT TRADUIT SYNTAXIQUEMENT INCORRECT,"
                          " PAS DE TRADUCTION : ',");
      formatQuote += origine.chaine ();
      formatQuote += ")";
      
      try
      {
        ptrTrad->analyse (formatQuote);
      }
      catch(ClubErreurs ce)
      {
        ce.correction ();
      }
      return -1;   // indique que l'on peut utiliser ce format
    }
  }

  catch(ClubErreurs ce)
  { // le format est inutilisable
    
    // transformation du format en cha�ne affichable sans risque
    string formatQuote ("('FORMAT FORTRAN INUTILISABLE"
                        " (SYNTAXIQUEMENT INCORRECT) : ");
    char c;
    while ((c = *format++) != '\0')
      if (c == '\'')
        formatQuote += "''";
      else
        formatQuote += c;
    formatQuote += "')";
    
    try
    {
      ptrTrad->analyse (formatQuote);
    }
    catch(ClubErreurs c)
    {
      // Il n'y a plus rien a faire
      c.correction ();
    }
      ce.correction ();
    return 1;   // indique que l'on est vraiment perdu

  }
}
