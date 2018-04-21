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
//>       ChaineSimple.cpp
//
//$Resume
//       fichier d'implantation de la classe ChaineSimple
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       inline short int & EntierCourt()          
//>       inline short int & NombreTotalCellules()  
//>       inline short int & NombreCellulesLibres() 
//>       inline short int & PremiereCelluleLibre() 
//>       inline short int & CellulesBlocCourant()  
//>       inline short int & CellulesBlocPrecedent()
//>       inline char *MemoireUtilisateur()         
//>       static int CreeTampon()                   
//>       static int CelluleReservable()            
//>       static void ReserveChaine()               
//>       static void RestitueChaine()              
//>       class ChaineSimple                        
//>         alloueChaine()                          
//>         etendChaine()                           
//>         ChaineSimple()                          
//>         ~ChaineSimple()                         
//>         reinitialise()                          
//>         formate()                               
//>         vFormate()                              
//>         modifieCaractere()                      
//>         elimineBlancsFinaux()                   
//>         elimineBlancsInitiaux()                 
//>         operator +=()                           
//>         operator()()                            
//
//$Historique
//       $Log: ChaineSimple.cpp,v $
//       Revision 1.20  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.19  2003/02/03 09:05:10  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 1.18  2002/12/10 08:51:42  club
//       DM-ID 12 Modification portant sur l'initialisation des pointeurset des variables.
//
//       Revision 1.17  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.16  2000/08/30 14:20:44  club
//       Ajout du '\0' � la fin de la ChaineSimple construite � partir d'un string STL.
//
//       Revision 1.15  2000/08/25 07:43:13  club
//       Ajout du constructeur de ChaineSimple � partir d'un string.
//
//       Revision 1.14  2000/07/03 08:57:18  club
//       Ajout du copyright CNES
//
//       Revision 1.13.2.2  2000/03/30 14:46:46  club
//       ajout du copyright CNES
//
//       Revision 1.13.2.1  2000/03/30 11:23:14  club
//       �limination d'une portion de code optionnelle posant
//       des probl�mes de droits de distribution
//
//       Revision 1.13  1999/03/15 13:15:41  club
//       modification lors de la r�initialisation d'une cha�ne simple, si la cha�ne
//       n'existe pas elle est allou�e automatiquement
//
//       Revision 1.12  1998/07/27 10:13:40  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 1.11  1998/06/24 08:43:39  luc
//       correction d'un �crasement m�moire lors des lib�rations de cha�nes
//
//       Revision 1.10  1998/06/21 15:53:34  luc
//       modification du format de l'en-t�te
//       �limination de la cha�ne statique RCS
//
//       Revision 1.9  1998/04/26 13:02:19  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/01/22 08:20:14  luc
//       initialisation d'une variable pour supprimer un avertissement
//
//       Revision 1.7  1997/10/14 16:44:42  luc
//       acc�l�ration de la recherche des cellules libres contigu�s
//       passage par un typedef pour faciliter le travail du compilateur SUN
//
//       Revision 1.6  1997/08/21 16:48:10  luc
//       ajout d'un en-t�te de fichier
//       prise en compte des '\0' pouvant �tre contenus dans une cha�ne
//       dont on donne explicitement une longueur plus grande
//       constructeur ChaineSimple::ChaineSimple (const char *chaine, int longueur)
//
//       Revision 1.5  1997/04/28 14:18:18  luc
//       correction d'une longueur de copie
//       
//       Revision 1.4  1997/04/27 17:15:04  luc
//       allocation du tampon d'�criture de ChaineSimple::vFormate
//       uniquement au premier appel
//       
//       Revision 1.3  1997/03/25 14:45:44  luc
//       ajout d'une m�thode vFormate prenant un argument de type va_list
//       changement des r�gles de nommage
//       
//       Revision 1.2  1997/03/19 15:13:44  luc
//       ajout d'un niveau interm�diaire pour la gestion m�moire
//       entre les cha�nes de caract�res et les op�rateurs new/delete
//       
//       Revision 1.1  1997/03/16 18:09:59  luc
//       Initial revision
//
//$Version
//       $Id: ChaineSimple.cpp,v 1.20 2003/07/17 12:38:06 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/ChaineSimple.h"

// gestion de la m�moire par allocation de plusieurs tampons
// et distribution de cellules de taille fixe dans ces tampons
static int    TailleTable       = 0;
static char **TableTampons      = 0;

// avec 250 cellules de 16 octets plus une cellule pour la gestion,
// les tampons minimaux occuperont 4000 octets, m�me en comptant large
// les op�rateurs new et les �ventuels malloc sous-jacents peuvent ajouter
// leur m�moire de gestion tout en restant dans une page de 4096 octets.
const  int    TailleCellule     = 16;
const  int    NombreCellulesMin = 250;

// les tampons sont des zones contigu�s de cellules toutes de m�me
// taille, la premi�re cellule est r�serv�e � la gestion du tampon
// elle contient le nombre total de cellules (sans compter la
// premi�re) et le nombre de cellules libres ; lorsque de la m�moire
// est attribu�e � l'utilisateur, le nombre de cellules concern�es et
// le nombre de cellules du bloc pr�c�dent sont stock�s dans deux
// entiers courts au d�but de la premi�re cellule, on attribue donc
// toujours une taille de la forme k * tc - 2 * s, o� tc est la taille
// d'une cellule et s la taille d'un entier court
inline short int & EntierCourt (int i, int decalage)
{ return *((short int *) (TableTampons [i] + decalage)); }


// informations globales du tampon d'index i
inline short int & NombreTotalCellules (int i)
{ return EntierCourt (i, 0); }

inline short int & NombreCellulesLibres (int i)
{ return EntierCourt (i, sizeof(short int)); }

inline short int & PremiereCelluleLibre (int i)
{ return EntierCourt (i, 2 * sizeof(short int)); }


// information pour le bloc commen�ant � la cellule c du tampon i
// (attention, les nombres de cellules sont positifs si les blocs
//  contiennent des donn�es, et n�gatifs si les blocs sont libres)
inline short int & CellulesBlocCourant (int i, int c)
{ return EntierCourt (i, (c + 1) * TailleCellule); }

inline short int & CellulesBlocPrecedent (int i, int c)
{ return EntierCourt (i, (c + 1) * TailleCellule + sizeof(short int)); }

inline char *MemoireUtilisateur (int i, int c)
{ return TableTampons [i] + (c + 1) * TailleCellule + 2 * sizeof(short int); }


static int CreeTampon (int nombreCellules)
{ // cr�ation d'un tampon contenant au moins un nombre de cellules donn�
  if (nombreCellules < NombreCellulesMin)
    nombreCellules = NombreCellulesMin;

  int i, index = -1;

  // recherche d'une entr�e disponible dans la table
  for (i = 0; (i < TailleTable) && (index < 0); i++)
    if (TableTampons [i] == 0)
      index = i;

  if (index < 0)
  { // la table est pleine (ou inexistante), il faut l'�tendre
    typedef char *CharPTR;
    int    nouvelleTaille = TailleTable ? (TailleTable << 1) : 8;
    char **nouvelleTable  = new CharPTR [nouvelleTaille];

    for (i = 0; i < TailleTable; i++)
      nouvelleTable [i] = TableTampons [i];
    for (i = TailleTable; i < nouvelleTaille; i++)
      nouvelleTable [i] = 0;

    // m�morisation de la premi�re entr�e libre
    index = TailleTable;

    // mise en place de la nouvelle table
    if (TailleTable)
      delete [] TableTampons;
    TailleTable  = nouvelleTaille;
    TableTampons = nouvelleTable;

  }

  // allocation du tampon
  TableTampons [index] = new char [(1 + nombreCellules) * TailleCellule];

  // initialisation du tampon
  NombreTotalCellules   (index)    = nombreCellules;
  NombreCellulesLibres  (index)    = nombreCellules;
  PremiereCelluleLibre  (index)    = 0;
  CellulesBlocCourant   (index, 0) = -nombreCellules;
  CellulesBlocPrecedent (index, 0) = 0;

  return index;

}

static int CelluleReservable (int index, int nombreCellules)
{ // recherche d'une zone de cellules libres contigu�s
  int cellule        = PremiereCelluleLibre (index);
  int cellulesLibres = NombreCellulesLibres (index);

  while (nombreCellules <= cellulesLibres)
  { // test de la cellule courante
    int reservees = CellulesBlocCourant (index, cellule);

    if (reservees > 0)
    { // il y a des cellules r�serv�es ici, on les �vite
      cellule += reservees;
    }
    else
    { // il y a des cellules libres
      if (nombreCellules > -reservees)
      { // le trou est trop petit
        cellule        += -reservees;
        cellulesLibres +=  reservees;
      }
      else
        return cellule;
    }

  }

  // il n'y a pas de zone utilisable
  return -1;

}

static void ReserveChaine (int tailleRequise,
                           int *ptrTailleReservee, char **ptrChaine)
{ // r�servation d'espace dans les tampons pour stocker une cha�ne
  if (tailleRequise < 0)
    tailleRequise = 0;

  int nombreCellules = (tailleRequise + 2 * sizeof(short int)
                      + TailleCellule - 1) / TailleCellule;

  // recherche de cellules libres contigu�s dans les tampons
  int cellule = -1, index = -1;
  for (int i = 0; (i < TailleTable) && (index < 0); i++)
  { // parcours de la table

    if (TableTampons [i] != 0)
    { // peut-on r�server une zone dans ce tampon ?
      cellule = CelluleReservable (i, nombreCellules);
      if (cellule >= 0)
        index = i; // le couple (i, cellule) convient, on arr�te la recherche
    }

  }

  if (index < 0)
  { // aucun tampon ne disposait des cellules n�cessaires : on en cr�e un
    index   = CreeTampon (nombreCellules);
    cellule = PremiereCelluleLibre (index);
  }

  // r�servation des cellules
  int reste = (-CellulesBlocCourant (index, cellule)) - nombreCellules;
  if (reste > 0)
  { // on ne prend qu'une partie d'un bloc libre
    if (cellule + nombreCellules + reste < NombreTotalCellules (index))
      CellulesBlocPrecedent (index, cellule + nombreCellules + reste) = -reste;
    CellulesBlocCourant   (index, cellule + nombreCellules) = -reste;
  }

  if (cellule + nombreCellules < NombreTotalCellules (index))
    CellulesBlocPrecedent (index, cellule + nombreCellules) = nombreCellules;
  CellulesBlocCourant (index, cellule) = nombreCellules;

  // mise � jour du tampon
  NombreCellulesLibres (index) -= nombreCellules;
  if (cellule == PremiereCelluleLibre (index))
    PremiereCelluleLibre (index) = CelluleReservable (index, 1);

  // affectation des variables de l'appelant
  *ptrTailleReservee = nombreCellules * TailleCellule - 2 * sizeof(short int);
  *ptrChaine         = MemoireUtilisateur (index, cellule);

}

static void RestitueChaine (char *chaine)
{ // restitution de m�moire
  // cette fonction ne marche QUE si la cha�ne provient d'un ReserveChaine

  // recherche du tampon contenant la cha�ne
  int index = 0;
  while ((TableTampons [index] == 0)
         ||
         (MemoireUtilisateur (index, 0) > chaine)
         ||
         (MemoireUtilisateur (index,
                              NombreTotalCellules (index) - 1) < chaine))
    index++;

  // r�cup�ration des �l�ments de gestion du tampon
  int nombreTotal    = NombreTotalCellules (index);
  int cellule        = (chaine - TableTampons [index]) / TailleCellule - 1;
  int nombreRestitue = CellulesBlocCourant (index, cellule);

  if (NombreCellulesLibres (index) + nombreRestitue == nombreTotal)
  { // on doit lib�rer la totalit� du tampon : on le rend au syst�me
    delete [] TableTampons [index];
    TableTampons [index] = 0;
  }
  else
  { // il reste des cha�nes allou�es dans le tampon : on le met � jour
    int tailleBloc = nombreRestitue;

    if (cellule + nombreRestitue < nombreTotal)
    { // analyse du bloc suivant le bloc restitu�
      int cellulesSuivant = CellulesBlocCourant (index,
                                                 cellule + nombreRestitue);

      // si le bloc suivant est un trou, on l'incorpore au bloc courant
      if (cellulesSuivant < 0)
        tailleBloc += -cellulesSuivant;

    }

    // analyse du bloc pr�c�dant le bloc restitu�
    int cellulesPrecedant = CellulesBlocPrecedent (index, cellule);

    // si le bloc pr�c�dant est un trou, on l'incorpore au bloc courant
    if (cellulesPrecedant < 0)
    { tailleBloc += -cellulesPrecedant;
      cellule    +=  cellulesPrecedant;
    }

    // transformation du bloc allou� en bloc libre
    CellulesBlocCourant (index, cellule) = -tailleBloc;
    if (cellule + tailleBloc < nombreTotal)
      CellulesBlocPrecedent (index, cellule + tailleBloc) = -tailleBloc;

    // mise � jour des compteurs globaux du tampon
    NombreCellulesLibres (index) += nombreRestitue;
    short int premiere = PremiereCelluleLibre (index);
    if ((premiere < 0) || (premiere > cellule))
      PremiereCelluleLibre (index) = cellule;

  }

}

void ChaineSimple::alloueChaine (int taille)
{ // allocation d'une cha�ne d'au moins taille caract�res
  ReserveChaine (taille, &taille_, &chaine_);

  // mise en place d'un chien de garde pour la m�thode modifieCaractere 
  chaine_ [taille_ - 1] = '\0';

  // initialisation de la cha�ne
  chaine_ [0]           = '\0';
  longueur_             = 0;

}

void ChaineSimple::etendChaine (int taille)
{ // extension du tableau de m�morisation d'une cha�ne

  // pr�paration d'un nouveau tableau
  int   nouvelleTaille = 0;
  char *nouvelleChaine = NULL;
  ReserveChaine (taille, &nouvelleTaille, &nouvelleChaine);

  // mise en place d'un chien de garde pour la m�thode modifieCaractere 
  nouvelleChaine [nouvelleTaille - 1] = '\0';

  // copie de l'ancienne cha�ne
  (void) memcpy ((void *) nouvelleChaine, (void *) chaine_, 1 + longueur_);

  // �limination du tableau pr�c�dent
  RestitueChaine (chaine_);

  // remplacement
  taille_ = nouvelleTaille;
  chaine_ = nouvelleChaine;

}

ChaineSimple::ChaineSimple (const char *chaine)
{ // cr�ation � partir d'une cha�ne constante
  if (chaine)
  { // il y a bien une cha�ne
    int longueur = strlen (chaine);
    alloueChaine (1 + longueur);
    longueur_    = longueur;
    (void) memcpy ((void *) chaine_, (void *) chaine, 1 + longueur_);
  }
  else
    alloueChaine (-1);

}

ChaineSimple::ChaineSimple (const char *chaine, int longueur)
{ // cr�ation � partir d'un tron�on (�ventuellement vide) de cha�ne constante
  alloueChaine (1 + longueur);

  if (chaine)
  { // il y a bien une cha�ne
    if (longueur)
      (void) memcpy ((void *) chaine_, (void *) chaine, longueur);

    // recherche d'un �ventuel '\0' avant la fin de la cha�ne
    longueur_ = 0;
    while ((longueur_ < longueur) && (chaine_ [longueur_] != '\0'))
      longueur_++;

  }
  else
    longueur_ = 0;

  chaine_ [longueur_] = '\0';

}

ChaineSimple::ChaineSimple (char caractere, int repetitions)
{ // cr�ation par duplication d'un caract�re
  alloueChaine (1 + repetitions);

  longueur_ = repetitions;

  char *ptr = chaine_;
  while (repetitions-- > 0)
    *ptr++ = caractere;

  chaine_ [longueur_] = '\0';

}

ChaineSimple::ChaineSimple (const ChaineSimple& c)
{ alloueChaine (1 + c.longueur_);
  longueur_ = c.longueur_;
  (void) strcpy (chaine_, c.chaine_);
}

ChaineSimple::ChaineSimple (const string& c)
{ alloueChaine (1 + c.size ());
  longueur_ = c.size ();
  for (int i=0 ; i<longueur_ ; i++)
    chaine_[i] = c[i];
  chaine_ [longueur_] = '\0';
}

ChaineSimple::~ChaineSimple ()
{ // nettoyage de l'instance
  RestitueChaine (chaine_);
}

void ChaineSimple::reinitialise (const ChaineSimple& c)
{ // r�affectation � partir d'une autre instance

  if (this != &c)     // protection contre x.reinitialise (x)
  { // on doit copier tous les caract�res stock�s au cas o�
    // l'utilisateur ait ins�r� un '\0' en plein milieu de sa cha�ne
    // avec modifieCaractere (i, '\0') et qu'il d�sire malgr� tout
    // pouvoir reconstruire la cha�ne compl�te initiale

    // v�rification de la place n�cessaire
    if (taille_ < c.taille_)
    {
      if( !chaine_ )
        alloueChaine( c.taille_ );
      else
        etendChaine (c.taille_);
    }

    // copie
    (void) memcpy ((void *) chaine_, (void *) c.chaine_, c.taille_);
    longueur_ = c.longueur_;

  }

}

void ChaineSimple::reinitialise (const char *chaine)
{ // r�affectation � partir d'une cha�ne brute
  if (chaine)
  { // taille n�cessaire en comptant le '\0' final
    int tailleNecessaire = 1 + strlen (chaine);
  
    // v�rification de la place n�cessaire

    if ((taille_ < tailleNecessaire) || (!chaine_)){
      if( !chaine_ )
        alloueChaine( tailleNecessaire );
      else
        etendChaine (tailleNecessaire);
    }    

    // copie
    (void) memcpy ((void *) chaine_, (void *) chaine, tailleNecessaire);
    longueur_ = tailleNecessaire - 1;

  }
  else
  { // il n'y a pas de cha�ne brute
    chaine_ [0] = '\0';
    longueur_   = 0;
  }
}

void ChaineSimple::reinitialise (const char *chaine, int longueur)
{ // r�affectation � partir d'un tron�on (�ventuellement vide) de cha�ne

  // v�rification de la place n�cessaire
  int tailleNecessaire = longueur + 1;
  if (taille_ < tailleNecessaire)
    if( !chaine_ )
      alloueChaine( tailleNecessaire );
    else
      etendChaine (tailleNecessaire);

  if (chaine)
  { // il y a bien une cha�ne
    if (longueur)
      (void) memcpy ((void *) chaine_, (void *) chaine, longueur);
  }
  else
    longueur = 0;

  chaine_ [longueur] = '\0';
  longueur_ = strlen (chaine_); // indispensable s'il y a des '\0' inclus

}

void ChaineSimple::reinitialise (char caractere, int repetitions)
{ // r�affectation par duplication d'un caract�re

  // v�rification de la place n�cessaire
  int tailleNecessaire = repetitions + 1;
  if (taille_ < tailleNecessaire)
    if( !chaine_ )
      alloueChaine( tailleNecessaire );
    else
      etendChaine (tailleNecessaire);

  longueur_ = repetitions;

  char *ptr = chaine_;
  while (repetitions-- > 0)
    *ptr++ = caractere;

  chaine_ [longueur_] = '\0';

}

void ChaineSimple::formate (const char *f ...)
{ // �crit dans l'instance � l'aide d'un format C
  va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, f);

  vFormate (f, ap);

  // fin de r�cup�ration des arguments d'appel
  va_end(ap);

}

void ChaineSimple::vFormate (const char *f, va_list ap)
{ // �crit dans l'instance � l'aide d'un format C

  // �criture dans un tampon de taille suppos�e suffisante
  static char *tampon = 0;
  if (tampon == 0)
    tampon = new char [4096];
  (void) vsprintf (tampon, f, ap);

  // recopie du tampon dans l'instance
  *this = tampon;

}

void ChaineSimple::modifieCaractere (int i, char c)
{ // modification du caract�re d'index i

  // on autorise la modification dans toute la cha�ne stock�e,
  // y compris au del� de la fin courante de la cha�ne
  if ((i < 0) || (i >= taille_ - 1))
    return;

  // modification
  chaine_ [i] = c;

  // mise � jour de la longueur
  if (c == '\0')
    longueur_ = i;
  else if (i == longueur_)
    longueur_ += strlen (chaine_ + i);

}

void ChaineSimple::elimineBlancsFinaux ()
{ // �limine les blancs finaux

  // blancs finaux
  for (char *mobile = chaine_ + longueur_ - 1; isspace(*mobile); mobile--)
  { // �limination du dernier caract�re
    *mobile = '\0';
    longueur_--;
  }

}

void ChaineSimple::elimineBlancsInitiaux ()
{ // �limine les blancs initiaux

  // blancs initiaux
  if (isspace(chaine_ [0]))
  { // comptage des blancs � �liminer
    char *src = chaine_ + 1;
    while (isspace(*src))
      src++;

    // d�calage de la fin de cha�ne
    char *dst = chaine_;
    while (*src)
      *dst++ = *src++;
    *dst = '\0';

    // correction de la longueur
    longueur_ = dst - chaine_;

  }

}

ChaineSimple& ChaineSimple::operator += (const ChaineSimple& c)
{ // ajout d'une instance � la fin d'une autre

  // v�rification de la place n�cessaire
  int tailleNecessaire = longueur_ + c.longueur_ + 1;
  if (taille_ < tailleNecessaire)
    etendChaine (tailleNecessaire);

  // copie
  (void) memcpy ((void *) (chaine_ + longueur_), (void *) c.chaine_,
                 1 + c.longueur_);
  longueur_ += c.longueur_;

  return *this;

}

ChaineSimple& ChaineSimple::operator += (const char *chaine)
{ // ajout d'une cha�ne � la fin de l'instance

  if (chaine)
  { // il y a une cha�ne brute
    int l = strlen (chaine);

    // v�rification de la place n�cessaire
    int tailleNecessaire = longueur_ + l + 1;
    if (taille_ < tailleNecessaire)
      etendChaine (tailleNecessaire);

    // copie
    (void) memcpy ((void *) (chaine_ + longueur_), (void *) chaine, 1 + l);
    longueur_ += l;

  }

  return *this;

}

ChaineSimple& ChaineSimple::operator += (char c)
{ // ajout d'un caract�re � la fin de l'instance

    // v�rification de la place n�cessaire
    int tailleNecessaire = longueur_ + 2;
    if (taille_ < tailleNecessaire)
      etendChaine (tailleNecessaire);

    // copie
    chaine_ [longueur_++] = c;
    chaine_ [longueur_]   = '\0';

  return *this;

}

ChaineSimple ChaineSimple::operator () (const char *debut,
                                        const char *fin) const
{ // extraction d'une sous-cha�ne

  // limitation des pointeurs
  if (debut < chaine_)
    debut = chaine_;
  if (fin > chaine_ + longueur_ - 1)
    fin = chaine_ + longueur_ - 1;

  // cr�ation d'une nouvelle instance
  int longueur = fin + 1 - debut;
  ChaineSimple sousChaine (1 + longueur);

  // copie de la sous-cha�ne
  (void) memcpy ((void *) sousChaine.chaine_, (void *) debut, longueur);
  sousChaine.chaine_ [longueur] = '\0';
  sousChaine.longueur_ = longueur;

  return sousChaine;

}

ChaineSimple ChaineSimple::operator () (int debut, int fin) const
{ // extraction d'une sous-cha�ne

  // limitation des pointeurs
  if (debut < 0)
    debut = 0;
  if (fin > longueur_ - 1)
    fin = longueur_ - 1;

  // cr�ation d'une nouvelle instance
  int longueur = fin + 1 - debut;
  ChaineSimple sousChaine (1 + longueur);

  // copie de la sous-cha�ne
  (void) memcpy ((void *) sousChaine.chaine_, (void *) (chaine_ + debut),
                 longueur);
  sousChaine.chaine_ [longueur] = '\0';
  sousChaine.longueur_ = longueur;

  return sousChaine;

}

int ChaineSimple::operator == (const char *chaine) const
{ return strcmp (chaine_, chaine) == 0; }

int ChaineSimple::operator == (const ChaineSimple& chaine) const
{ return strcmp (chaine_, chaine.chaine_) == 0; }

int ChaineSimple::operator != (const char *chaine) const
{ return strcmp (chaine_, chaine); }

int ChaineSimple::operator != (const ChaineSimple& chaine) const
{ return strcmp (chaine_, chaine.chaine_); }
