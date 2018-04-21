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
//       Cantor
//
//$Nom
//>       MoindreCarreLineaire.cpp
//
//$Resume
//       fichier d'implantation de la classe MoindreCarreLineaire
//
//$Description
//       Module de d�finition de la classe et des fonctions associ�es
//
//$Contenu
//>       void factLDLt()            
//>       void resoudLDLt()         
//>       class MoindreCarreLineaire
//>         alloueTableaux()        
//>         libereTableaux()        
//>         MoindreCarreLineaire()  
//>         operator =()            
//>         ajouteResidu()          
//>         oteResidu()             
//>         oteTousResidus()        
//>         ajuste()                
//>         coefficients()          
//>         erreurQuadratique()     
//>         operator()()            
//
//$Historique
//       $Log: MoindreCarreLineaire.cpp,v $
//       Revision 1.10  2003/02/04 09:28:52  cantor
//       DM-ID 17 Mise � jour du nom du fichier dans le bandeau suite � la modification des extensions.
//
//       Revision 1.9  2002/12/10 16:21:03  cantor
//       DM-ID 12 Correction d'un d�faut d'initialisation de pointeurs
//
//       Revision 1.8  2001/06/05 15:44:04  cantor
//       utilisation du m�canisme des exceptions pour la gestion des erreurs
//
//       Revision 1.7  2000/08/09 14:36:42  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:10:20  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.5  1998/04/26 15:23:59  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1997/07/06 10:38:59  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.3  1997/04/03 19:32:10  luc
//       inversion des codes de retour, 0 signifie d�sormais : pas d'erreur
//       
//       Revision 1.2  1997/03/26 06:54:33  luc
//       changement des conventions de nommage
//       
//       Revision 1.1  1997/03/24 08:32:22  luc
//       Initial revision
//
//$Version
//       $Id: MoindreCarreLineaire.cpp,v 1.10 2003/02/04 09:28:52 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/MoindreCarreLineaire.h"


void factLDLt (double *m, int n, double seuil)
  throw (CantorErreurs)
{ // factorisation en place d'une matrice sym�trique dont seul
  // le triangle sup�rieur est rang� par lignes dans un tableau

  while (--n)
  { // boucle sur les lignes de la matrice triangulaire

    // test du pivot
    if ((*m < seuil) && (*m > -seuil))
      throw CantorErreurs(CantorErreurs::matrice_singuliere);
    double inverse = 1.0 / *m++;

    // �limination de la contribution de la ligne dans la matrice initiale
    double *ptrM = m + n; // pointeur sur les �l�ments � transformer
    for (int i = n; i; i--)
    {
      double  coeff  = inverse * *m;
      double *mobile = m;

      for (int j = i; j; j--)
        *ptrM++ -= coeff * *mobile++; // boucle effectu�e n(n^2 - 1) / 6 fois

      *m++ = coeff;

    }
  }

  if ((*m < seuil) && (*m > -seuil))
    throw CantorErreurs (CantorErreurs::matrice_singuliere);

}

void resoudLDLt (const double *m, int n, double x [])
{ // r�solution d'un syst�me lin�aire factoris� sous forme L.D.Lt
  // la diagonale de D ne comportant aucun 0

  // r�solution descendante de LD.Y = B
  const double *ptrL = m; // pointeur sur les lignes de L
  for (int l = n - 1; l; l--)
  {
    double *ptrB = x + (n - 1 - l);
    double    yi = *ptrB;

    *ptrB++ /= *ptrL++;

    for (int i = l; i; i--)
      *ptrB++ -= yi * *ptrL++;

  }
  x [n-1] /= *ptrL;

  // r�solution montante de Lt.X = Y
  ptrL = m + ((n * (n + 1)) / 2 - 1);
  double *ptrY = x + (n - 1);
  for (int k = n - 1; k; k--)
  { // passage � la fin de la ligne pr�c�dente
    ptrL--;
    ptrY--;
    double *ptrX = x + (n - 1);
    for (int i = n - k; i; i--)
      *ptrY -= *ptrL-- * *ptrX--;
  }

}

void MoindreCarreLineaire::alloueTableaux (int dimension)
{ // mise � jour des tableaux d'une instance consid�r�e comme vide au d�part

  if (dimension <= 0)
  { // argument incoh�rent : on se contente de tout mettre � z�ro
    dimension_    = 0;
    vecSommeRkFk_ = 0;
    matSommeFkFk_ = 0;
    ai_           = 0;
  }
  else
  { // allocation des tableau de travail pour la dimension donn�e
    // 2 vecteurs de taille dimension_,
    // 1 matrice sym�trique dimension_ X dimension_ dont on ne stocke
    // que le triangle sup�rieur
    // => soit une allocation totale de : dimension_ * (dimension_ + 5) / 2
    dimension_    = dimension;
    vecSommeRkFk_ = new double [(dimension_ * (dimension_ + 5)) / 2];
    matSommeFkFk_ = vecSommeRkFk_  + dimension_;
    ai_           = matSommeFkFk_ + (dimension_ * (dimension_ + 1)) / 2;
  }

  // initialisation des tableaux
  oteTousResidus ();

}

void MoindreCarreLineaire::libereTableaux ()
{ if (vecSommeRkFk_)
    delete [] vecSommeRkFk_;

  dimension_    = 0;
  vecSommeRkFk_ = 0;
  matSommeFkFk_ = 0;
  ai_           = 0;

}

MoindreCarreLineaire::MoindreCarreLineaire (const MoindreCarreLineaire& m)
{ // constructeur par copie
  alloueTableaux (m.dimension_);

  nbResidus_ = m.nbResidus_;
  sommeRk2_  = m.sommeRk2_;
  for (int i = 0; i < m.dimension_; i++)
    vecSommeRkFk_ [i] = m.vecSommeRkFk_ [i];
  for (int j = 0; j < m.dimension_ * (m.dimension_ + 1) / 2; j++)
    matSommeFkFk_ [j] = m.matSommeFkFk_ [j];

  if (m.estAjuste_)
  { estAjuste_ = m.estAjuste_;

    for (int k = 0; k < m.dimension_; k++)
      ai_ [k] = m.ai_ [k];

    errQuad_ = m.errQuad_;

  }

}

MoindreCarreLineaire& MoindreCarreLineaire::operator =
                                            (const MoindreCarreLineaire& m)
{ // affectation
  if (this != &m)     // protection contre x = x
  { if (dimension_ < m.dimension_)
    { // il est possible que les tableaux soient trop petits
      libereTableaux ();
      alloueTableaux (m.dimension_);
    }
    else
      dimension_ = m.dimension_;

    nbResidus_ = m.nbResidus_;
    sommeRk2_  = m.sommeRk2_;
    for (int i = 0; i < m.dimension_; i++)
      vecSommeRkFk_ [i] = m.vecSommeRkFk_ [i];
    for (int j = 0; j < m.dimension_ * (m.dimension_ + 1) / 2; j++)
      matSommeFkFk_ [j] = m.matSommeFkFk_ [j];

    estAjuste_ = m.estAjuste_;

    if (m.estAjuste_)
    { // le mod�le a �t� ajust�, on doit �galement copier les r�sultats

      for (int k = 0; k < m.dimension_; k++)
        ai_ [k] = m.ai_ [k];

      errQuad_ = m.errQuad_;

    }

  }

  return *this;

}

void MoindreCarreLineaire::ajouteResidu (double rk, double fki [], double wk)
{ // ajout d'un r�sidu dans l'�chantillon de r�f�rence de l'ajustement

  // incr�mentation des tableaux de sommes partielles
  sommeRk2_  += wk * rk * rk;

  double *mobileM = matSommeFkFk_;
  double *mobileV = vecSommeRkFk_;
  for (int i = 0; i < dimension_; i++)
  { double  wkFki = wk * *fki;
    double *ptrXkj = NULL;
    int     j;
    for (j = i, ptrXkj = fki++; j < dimension_; j++, ptrXkj++)
      *mobileM++ += wkFki * *ptrXkj;
    *mobileV++ += rk * wkFki;
  }

  nbResidus_++;
  estAjuste_ = false;

}

void MoindreCarreLineaire::oteResidu (double rk, double fki [], double wk)
{ // �limination d'un r�sidu de l'�chantillon de r�f�rence de l'ajustement

  // d�cr�mentation des tableaux de sommes partielles
  sommeRk2_ -= wk * rk * rk;

  double *mobileM = matSommeFkFk_;
  double *mobileV = vecSommeRkFk_;
  for (int i = 0; i < dimension_; i++)
  { double  wkFki = wk * *fki;
    double *ptrXkj = NULL;
    int     j;
    for (j = i, ptrXkj = fki++; j < dimension_; j++, ptrXkj++)
      *mobileM++ -= wkFki * *ptrXkj;
    *mobileV++ -= rk * wkFki;
  }

  nbResidus_--;
  estAjuste_ = false;

}

void MoindreCarreLineaire::oteTousResidus ()
{ // remise � z�ro de l'�chantillon de r�f�rence
  nbResidus_ = 0;
  sommeRk2_  = 0.0;
  estAjuste_ = false;
  errQuad_   = 0.0;

  // mise � z�ro de TOUS les vecteurs et de la matrice
  if (vecSommeRkFk_)
    for (int i = 0; i < dimension_ * (dimension_ + 5) / 2; i++)
      vecSommeRkFk_ [i] = 0.0;

}

void MoindreCarreLineaire::ajuste (double seuil)
  throw (CantorErreurs)
{ // ajustement au sens des moindres carr�s de l'�chantillon des r�sidus
  // de r�f�rence par rapport � une combinaison lin�aire de coefficients
  if (estAjuste_)
    return;

  if (dimension_ <= 0)
    throw CantorErreurs (CantorErreurs::ajuste_dimension_nulle);
  int tailleRequise = dimension_ * (dimension_ + 1) / 2;

  // gestion d'une matrice de travail
  static int     maxMatrice = 0;
  static double *m          = 0;
  if (maxMatrice < tailleRequise)
  { // la matrice de travail allou�e n'est pas assez grande
    if (m)
      delete [] m;
    maxMatrice = tailleRequise;
    m          = new double [maxMatrice];
  }

  // r�solution du syst�me lin�aire des moindres carr�s
  for (int i = 0; i < tailleRequise; i++)
    m [i] = matSommeFkFk_ [i];

  // factorisation L.D.Lt de la matrice des moindres carr�s
  try
  {
    factLDLt (m, dimension_, seuil);
  }
  catch (CantorErreurs erreur)
  {
    if (erreur.correspond (CantorErreurs::matrice_singuliere, "cantor"))
    {
      erreur.correction ();
      throw CantorErreurs (CantorErreurs::non_ajustable);
    }
    throw;
  }

  // calcul des coefficients de l'ajustement minimisant l'erreur quadratique
  for (int j = 0; j < dimension_; j++)
    ai_ [j] = vecSommeRkFk_ [j];
  resoudLDLt (m, dimension_, ai_);

  estAjuste_ = true;

  // estimation de l'erreur quadratique d'ajustement
  errQuad_ = sommeRk2_;
  for (int k = 0; k < dimension_; k++)
    errQuad_ -= ai_ [k] * vecSommeRkFk_ [k];

}

void MoindreCarreLineaire::coefficients (double ai []) const
  throw (CantorErreurs)
{
  if (!estAjuste_)
    throw CantorErreurs (CantorErreurs::non_ajustee);

  for (int i = 0; i < dimension_; i++)
    ai [i] = ai_ [i];
}

double MoindreCarreLineaire::erreurQuadratique () const
  throw (CantorErreurs)
{
  if (!estAjuste_)
    throw CantorErreurs (CantorErreurs::non_ajustee);
  return errQuad_;
}

void MoindreCarreLineaire::operator () (double *ptrFk, double fki []) const
  throw (CantorErreurs)
{
  if (!estAjuste_)
    throw CantorErreurs (CantorErreurs::non_ajustee);

  // combinaison lin�aire
  *ptrFk = ai_ [0] * fki [0];
  for (int i = 1; i < dimension_; i++)
    *ptrFk += ai_ [i] * fki [i];

}
