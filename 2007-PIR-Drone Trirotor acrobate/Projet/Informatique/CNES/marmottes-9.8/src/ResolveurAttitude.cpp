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
//       Marmottes
//
//$Nom
//>       ResolveurAttitude.cpp
//
//$Resume
//       fichier d'implantation de la classe ResolveurAttitude
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class ResolveurAttitude     
//>         ajouteSolution()          
//>         ResolveurAttitude()       
//>         operator =()              
//>         reinitialise()            
//>         modeliseConsignes()       
//>         miseAJourConvergence()    
//>         miseAJourDichotomie()     
//>         deuxConsignes()           
//>         trouveTout()              
//>         elimineExcedentaires()    
//>         selection()               
//>         f()               
//>         static f()               
//
//$Historique
//       $Log: ResolveurAttitude.cpp,v $
//       Revision 3.28  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 3.27  2003/02/04 16:32:29  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 3.26  2002/04/17 16:09:31  marmottes
//       Corrections de throw
//
//       Revision 3.25  2002/01/17 09:26:19  marmottes
//       correction de sp�cifications throw
//
//       Revision 3.24  2001/07/17 15:46:09  luc
//       protection contre les exceptions pouvant �tre lanc�es par les m�thodes
//       de mesure des capteurs
//
//       Revision 3.23  2001/06/06 08:03:54  luc
//       remont�e des exceptions Cantor
//
//       Revision 3.22  2000/09/13 11:00:54  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 3.21  2000/06/07 13:59:11  luc
//       repassage � 50 tranches pour �viter les probl�mes de mod�le cin�matique
//
//       Revision 3.20  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 3.19  2000/02/07 16:13:06  luc
//       passage de 50 tranches � 5 tranches par d�faut
//       pour tenter d'acc�l�rer les calculs
//
//       Revision 3.18  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des m�thodes "throw"
//
//       Revision 3.17  1999/08/06 13:32:15  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 3.16  1999/07/29 12:22:55  filaire
//       Utilisation des exceptions dans les methodes ModeliseConsignes
//
//       Revision 3.16  1999/07/02 09:18:22  geraldine
//       repercution du changement de signature de prendConsigneEnCompte
//       dans les deux m�thodes modeliseConsignes
//
//       Revision 3.15  1999/04/26 11:38:08  luc
//       remplacement de abs par fabs
//
//       Revision 3.14  1998/08/04 07:00:17  luc
//       r�duction de l'intervalle de validit� de la variable libre
//       de [-1 ; +1] � [0 ; 1]
//
//       Revision 3.13  1998/06/24 20:01:05  luc
//       �limination des variables statiques RCS
//       modification du format des en-t�tes
//
//       Revision 3.12  1998/04/26 18:25:21  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.11  1998/02/19 16:21:15  luc
//       d�placement d'un constructeur inline dans le .cc
//       pour contourner un probl�me d'optimiseur avec g++ 2.8.0
//
//       Revision 3.10  1998/02/05 11:24:53  luc
//       s�lection du c�t� du recollement le plus proche du z�ro
//       dans le cas d'un ajout explicite de z�ro cach� entre +1 et -1
//
//       Revision 3.9  1998/02/04 08:11:47  luc
//       cr�ation d'une m�thode s�par�e pour ajouter une solution
//       � l'ensemble g�r� par l'instance
//       d�tection des z�ros cach�s au niveau du recollement
//       de -1 en +1
//
//       Revision 3.8  1997/11/27 06:54:46  luc
//       correction d'un commentaire
//
//       Revision 3.7  1997/09/23 09:28:38  luc
//       prise en compte des changements d'unit�s possibles de la pr�cision
//
//       Revision 3.6  1997/09/15 10:13:00  luc
//       modification du seuil de rejet des artefacts math�matiques
//
//       Revision 3.5  1997/09/14 14:30:12  luc
//       am�lioration du filtrage des solutions parasites :
//       la fonction d'�cart du troisi�me senseur porte sur le mod�le, pas
//       sur la consigne brute, elle aussi peut g�n�rer des artefacts ; il
//       faut donc �galement filtrer sur la mesure du troisi�me senseur.
//
//       Revision 3.4  1997/08/27 12:39:02  luc
//       limitation de la copie au seul mod�le actif
//       (constructeur par copie et op�rateur d'affectation)
//
//       Revision 3.3  1997/08/20 08:37:38  luc
//       ajout d'un en-t�te de fichier
//       retour d'une erreur lors de la r�initialisation des senseurs
//       retour d'une erreur lors du filtrage des solutions parasites
//       refonte du filtrage des solutions parasites
//
//       Revision 3.2  1997/04/27 19:36:27  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 3.1  1997/01/28 12:44:33  luc
//       prise en compte des changements de la classe Etat (pass�e en version 3.1)
//       
//       Revision 2.3  1996/10/07 15:41:23  luc
//       ajout d'une conversion de pointeur explicite pour �viter les avertissements
//       
//       Revision 2.2  1996/09/11 17:41:52  luc
//       ajout d'une possibilit� de n'initialiser que deux consignes
//       (pour Marmottes::deuxConsignes)
//       �limination des copies de pointeurs pour �viter les r�f�rences
//       multiples aux m�mes senseurs par des instances diff�rentes
//       (pour Marmottes::Marmottes et Marmottes::operator =)
//       
//       Revision 2.1  1996/07/31 17:18:57  luc
//       abandon des tools.h++ (Rogue Wave)
//       
//       Revision 1.2  1995/02/06 08:05:17  mercator
//       selection de la "meilleure" solution par comparaison des ecarts de spin
//       plutot que par des ecarts d'attitude extrapolee
//       
//       Revision 1.1  1995/02/02 13:03:25  mercator
//       Initial revision
//
//$Version
//       $Id: ResolveurAttitude.cpp,v 3.28 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Resolution1Iterateur.h"

#include "marmottes/ResolveurAttitude.h"

const int TailleParDefaut = 4;

void ResolveurAttitude::ajouteSolution (double t)
{ // ajoute une solution correspondant � la valeur t de la variable libre
  if (nbSol_ >= tailleTable_)
  { // extension de la table
    int      taille = tailleTable_ ? (tailleTable_ << 1) : TailleParDefaut;
    SpinAtt *table  = new SpinAtt [taille];
    for (int i = 0; i < nbSol_; i++)
      table [i] = solutions_ [i];
    if (tailleTable_)
      delete [] solutions_;
    tailleTable_ = taille;
    solutions_   = table;
  }

  // m�morisation de l'attitude respectant toutes les consignes
  RotVD1 attitude;
  VecVD1 spin;
  modeleCourant_->attitude (etatPrecedent_, etatResolution_.date (),
                            t, famille_, &attitude, &spin);
  solutions_ [nbSol_++] = SpinAtt (RotVD1DBL (attitude), VecVD1DBL (spin));

}


ResolveurAttitude::ResolveurAttitude ()
  : sA1_ (0), sA2_ (0), sB_ (0), modeleCourant_ (0),
    famille_ (0), tailleTable_ (0), nbSol_ (0), solutions_ (0), tranches_ (50)
{ senseursConsigne_ [0] = 0;
  senseursConsigne_ [1] = 0;
  senseursConsigne_ [2] = 0;
}


ResolveurAttitude::ResolveurAttitude (const ResolveurAttitude& r)
  : etatPrecedent_ (r.etatPrecedent_), etatResolution_ (r.etatResolution_),
    famille_ (r.famille_),
    tailleTable_ (r.nbSol_ ? r.nbSol_ : TailleParDefaut), nbSol_ (r.nbSol_),
    solutions_ (new SpinAtt [tailleTable_]),
    seuil_ (r.seuil_), tranches_ (r.tranches_)
{ senseursConsigne_ [0] = 0;
  senseursConsigne_ [1] = 0;
  senseursConsigne_ [2] = 0;
  sA1_                  = 0;
  sA2_                  = 0;
  sB_                   = 0;

  for (int i = 0; i < nbSol_; i++)
    solutions_ [i] = r.solutions_ [i];

  if (((const ModeleGeom *) r.modeleCourant_) == &(r.modeleGeom_))
  { // c'est le mod�le g�om�trique qui est actif
    modeleGeom_    = r.modeleGeom_;
    modeleCourant_ = &modeleGeom_;
  }
  else
  { // c'est le mod�le cin�matique qui est actif
    modeleCine_    = r.modeleCine_;
    modeleCourant_ = &modeleCine_;
  }

}


ResolveurAttitude& ResolveurAttitude::operator = (const ResolveurAttitude& r)
{ if (&r != this)     // protection contre x = x
  { senseursConsigne_ [0] = 0;
    senseursConsigne_ [1] = 0;
    senseursConsigne_ [2] = 0;
    sA1_                  = 0;
    sA2_                  = 0;
    sB_                   = 0;

    if (((const ModeleGeom *) r.modeleCourant_) == &(r.modeleGeom_))
    { // c'est le mod�le g�om�trique qui est actif
      modeleGeom_    = r.modeleGeom_;
      modeleCourant_ = &modeleGeom_;
    }
    else
    { // c'est le mod�le cin�matique qui est actif
      modeleCine_     = r.modeleCine_;
      modeleCourant_ = &modeleCine_;
    }

    etatPrecedent_  = r.etatPrecedent_;
    etatResolution_ = r.etatResolution_;
    famille_        = r.famille_;

    if (r.nbSol_ > tailleTable_)
    { // r�allocation de la table des solutions
      if (tailleTable_)
        delete [] solutions_;
      tailleTable_  = r.nbSol_;
      solutions_    = new SpinAtt [tailleTable_];
    }
    nbSol_          = r.nbSol_;
    for (int i = 0; i < nbSol_; i++)
      solutions_ [i] = r.solutions_ [i];

    seuil_          = r.seuil_;
    tranches_       = r.tranches_;

  }

  return *this;

}


void ResolveurAttitude::reinitialise (Senseur* s1, Senseur* s2, Senseur* s3)
  throw (MarmottesErreurs)
{ 
  senseursConsigne_ [0] = s1;
  senseursConsigne_ [1] = s2;
  senseursConsigne_ [2] = s3;

  // s�paration en un groupe de deux senseurs de m�me type et un troisi�me
  if (s1->methode () == s2->methode ())
  { sA1_ = s1;
    sA2_ = s2;
    sB_  = s3;
  }
  else if (s1->methode () == s3->methode ())
  { sA1_ = s1;
    sA2_ = s3;
    sB_  = s2;
  }
  else
  { sA1_ = s2;
    sA2_ = s3;
    sB_  = s1;
  }

  // mise � jour du pointeur de mod�le
  if (sA1_->methode () == Senseur::intersectionCones)
    modeleCourant_ = &modeleGeom_;
  else if (sA1_->methode () == Senseur::integrationSpin)
    modeleCourant_ = &modeleCine_;
  else
    throw MarmottesErreurs (MarmottesErreurs::consigne_interdite,
                            sA1_->nom ().c_str (),
                            sA2_->nom ().c_str ());

  modeleCourant_->miseAJourSenseurs (sA1_, sA2_);

  // mise � jour de la pr�cision de r�solution
  if (sB_->conversionMesures ())
  { // on veut la pr�cision en unit�s internes
    sB_->respecterMesures ();
    seuil_ = 0.1 * sB_->precision ();
    sB_->convertirMesures ();
  }
  else
    seuil_ = 0.1 * sB_->precision ();

}


void ResolveurAttitude::modeliseConsignes (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           double m1, double m2)
  throw  (CantorErreurs, MarmottesErreurs)
{ if ((sA1_ == 0) || (sA2_ == 0) || (sB_ == 0))
    throw  MarmottesErreurs (MarmottesErreurs::liste_non_initialisee);

  // sauvegarde de l'�tat pr�c�dent complet
  etatPrecedent_ = etatPrecedent;

  // sauvegarde de l'�tat de r�solution (l'attitude n'y est pas significative)
  etatResolution_ = etatResolution;

  // prise en compte des consignes dans le mod�le
    modeleCourant_->prendConsignesEnCompte ();
}


void ResolveurAttitude::modeliseConsignes (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           double m1, double m2, double m3)
  throw  (CantorErreurs, MarmottesErreurs)
{ if ((sA1_ == 0) || (sA2_ == 0) || (sB_ == 0))
    throw MarmottesErreurs (MarmottesErreurs::liste_non_initialisee);

  // sauvegarde de l'�tat pr�c�dent complet
  etatPrecedent_ = etatPrecedent;

  // sauvegarde de l'�tat de r�solution (l'attitude n'y est pas significative)
  etatResolution_ = etatResolution;

  // prise en compte des consignes dans le mod�le
    modeleCourant_->prendConsignesEnCompte ();
}


void ResolveurAttitude::miseAJourConvergence (double seuil)
  throw (MarmottesErreurs)
{ 
  if (seuil <= 0.0)
    throw MarmottesErreurs (MarmottesErreurs::seuil_neg,
                            seuil);

  seuil_ = seuil;

}


void ResolveurAttitude::miseAJourDichotomie (int tranches)
  throw (MarmottesErreurs)
{ 
  if (tranches <= 0)
    throw MarmottesErreurs (MarmottesErreurs::tranches_neg,
                            tranches);

  tranches_ = tranches;

}


void ResolveurAttitude::deuxConsignes (SpinAtt* ptrSpinAtt)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  // recherche d'une solution dans toutes les familles d'attitudes mod�lis�es
  RotVD1        attVD1;
  VecVD1        spinVD1;
  for (famille_ = 0; famille_ < modeleCourant_->familles (); famille_++)
    for (ValeurDerivee1 t (0.0, 1.0); t <= 1.0; t += 1.0 / double (tranches_))
    { // application du mod�le d'attitude bati sur les deux premi�res consignes
      modeleCourant_->attitude (etatPrecedent_, etatResolution_.date (),
                                t, famille_, &attVD1, &spinVD1);
      RotDBL attitude = RotVD1DBL (attVD1);
      VecDBL spin     = VecVD1DBL (spinVD1);

      // simulation de la "solution" courante
      Etat etat         (etatPrecedent_);
      etat.reinitialise (etatResolution_.date (),
                         etatResolution_.position (),
                         etatResolution_.vitesse (),
                         attitude);
      etat.reinitialise (spin);

      // test de contr�labilit� par les deux premiers senseurs de consigne
      if ((senseursConsigne_ [0]->controlable (etat))
          &&
          (senseursConsigne_ [1]->controlable (etat)))
      { 
        *ptrSpinAtt = SpinAtt (attitude, spin);
        return;
      }
    }

  // aucune attitude mod�lis�e ne convient
  throw MarmottesErreurs (MarmottesErreurs::pas_de_solution);

}


ValeurDerivee1 ResolveurAttitude::f (double t)
{
  // calcul de l'attitude mod�lis�e respectant les premi�res consignes
  RotVD1 attitude;
  VecVD1 spin;
  modeleCourant_->attitude (etatPrecedent_, etatResolution_.date (),
                            ValeurDerivee1 (t, 1.0), famille_,
                            &attitude, &spin);

  // calcul de l'�cart par rapport � la troisi�me consigne
  return sB_->foncEcart (etatPrecedent_, etatResolution_, attitude, spin);

}


ValeurDerivee1 ResolveurAttitude::f (double t, void* arg)
{
  return ((ResolveurAttitude *) arg)->f (t);
}

void ResolveurAttitude::trouveTout ()
  throw (MarmottesErreurs)
{ // vidage des solutions �ventuellement trouv�es pr�c�demment
  nbSol_ = 0;

  // recherche des solutions dans toutes les familles d'attitudes mod�lis�es
  for (famille_ = 0; famille_ < modeleCourant_->familles (); famille_++)
  { Resolution1Iterateur iter (f, (void *) this,
                               0.0, 1.0, tranches_, -1.0, seuil_);
    double t0;

    // recherche de toutes les solutions d'une famille
    while ((t0 = iter.zeroSuivant ()) < 2.0)
      ajouteSolution (t0);

    // recherche d'une solution �ventuelle au recollement t = +1 -> t = 0
    ValeurDerivee1 fMoins = f (0.0);
    ValeurDerivee1 fPlus  = f (1.0);
    if (((fMoins.f0 () < 0.0) && (fPlus.f0  () > 0.0))
        ||
        ((fMoins.f0 () > 0.0) && (fPlus.f0  () < 0.0)))
    { // la fonction s'�loigne de z�ro en quittant t = 0
      // et s'en approche par l'autre c�t� en arrivant vers t = +1
      // il y a donc un z�ro cach� au point de recollement
      // (on n'utilise pas les d�riv�es ici, car les fonctions ne sont pas
      // forc�ment d�rivables au point de recollement, il y a donc des
      // comportements num�riques erratiques dans ces zones l�)
      if (fabs (fPlus.f0 ()) <= fabs (fMoins.f0 ()))
        ajouteSolution (1.0);
      else
        ajouteSolution (0.0);
    }

  }
}


void ResolveurAttitude::elimineExcedentaires ()
  throw (CantorErreurs, MarmottesErreurs)
{ // �limination des solutions non contr�lables (cible hors champ de vue, ...)
  int src = 0, dst = 0;

  // filtrage des artefacts math�matiques
  for (src = 0; src < nbSol_; src++)
  {
    try
    {
      // simulation de la solution courante
      Etat etat         (etatPrecedent_);
      etat.reinitialise (etatResolution_.date (),
                         etatResolution_.position (), etatResolution_.vitesse (),
                         solutions_ [src].attitude ());
      etat.reinitialise (solutions_ [src].spin ());

      double ecartA1 = sA1_->mesure (etat) - sA1_->valeurConsigne ();
      double ecartA2 = sA2_->mesure (etat) - sA2_->valeurConsigne ();
      double ecartB  =  sB_->mesure (etat) -  sB_->valeurConsigne ();

      // on utilise comme seuil 100 fois la pr�cision au lieu du dixi�me
      // de la pr�cision (qui est le seuil de convergence) car les z�ros
      // cach�s que l'on rajoute parfois artificiellement au niveau des
      // points de recollement de -1 en +1 peuvent ne pas �tre calcul�s
      // avec une bonne pr�cision (leur x est bon, mais leur y peut �tre
      // pas).
      if ((fabs (ecartA1) <= 100 * sA1_->precision ())
          &&
          (fabs (ecartA2) <= 100 * sA2_->precision ())
          &&
          (fabs (ecartB)  <= 100 * sB_->precision  ()))
        solutions_ [dst++] = solutions_ [src];
    }
    catch (MarmottesErreurs me)
    { me.correction (); }
    catch (CantorErreurs ce)
    { ce.correction (); }

  }
  nbSol_ = dst;

  // � ce niveau, les artefacts math�matiques (sym�triques de
  // solutions) ont disparu. Il peut cependant rester plusieurs
  // solutions physiques. L'utilisation de senseurs cin�matiques peut
  // ainsi engendrer des solutions pr�sentant la m�me attitude mais
  // des spins diff�rents (li�s aux nombres diff�rents de tours
  // complets � partir de l'attitude pr�c�dente). De m�me certaines
  // solutions th�oriques peuvent �tre incontr�lables dans la
  // pratique, la terre peut �tre parfaitement point�e mais �tre trop
  // grosse pour que son horizon soit visible dans le champ de vue par
  // exemple. Il faut donc tester la contr�labilit�, et on ne peut pas
  // faire l'hypoth�se qu'il ne reste qu'une seule solution � ce
  // niveau.
  int incontrolable = -1;
  dst = 0;
  for (src = 0; src < nbSol_; src++)
  { // simulation de la solution courante
    Etat etat         (etatPrecedent_);
    etat.reinitialise (etatResolution_.date (),
                       etatResolution_.position (), etatResolution_.vitesse (),
                       solutions_ [src].attitude ());
    etat.reinitialise (solutions_ [src].spin ());

    // test de contr�labilit� par tous les senseurs de consigne
    if (senseursConsigne_ [0]->controlable (etat))
    { // senseur 0 contr�lable
      if (senseursConsigne_ [1]->controlable (etat))
      { // senseurs 0 et 1 contr�lables
        if (senseursConsigne_ [2]->controlable (etat))
          incontrolable = -1; // senseurs 0, 1, et 2 tous contr�lables
        else
          incontrolable =  2;
      }
      else
        incontrolable = 1;
    }
    else
      incontrolable = 0;

    if (incontrolable < 0)
      solutions_ [dst++] = solutions_ [src];

  }

  if (dst < 1)
  { if (nbSol_ == 1)
    { // il n'y avait qu'une seule solution, qui s'av�re incontr�lable
      nbSol_ = 0;
      string nomSenseur = senseursConsigne_ [incontrolable]->nom ();
      throw MarmottesErreurs (MarmottesErreurs::controlabilite,
                              nomSenseur.c_str ());
    }
    else
    { // on ne sait pas diff�rencier la solution technologique des solutions
      // simplement physiques, l'index m�moris� n'est pas forc�ment correct
      nbSol_ = 0;
      throw MarmottesErreurs (MarmottesErreurs::pas_de_solution);
    }
  }
  else
  { // il reste au moins une solution
    nbSol_ = dst;
    return;
  }
}


const SpinAtt& ResolveurAttitude::selection () const
{ // s�lection de la solution la plus coh�rente avec le mouvement pr�c�dent
  if (nbSol_ == 1)
    return solutions_ [0];

  VecDBL spin (etatResolution_.spin ());

  // recherche de la meilleure solution
  int    meilleureSpinAtt = 0;
  double meilleurEcart    = 10.0;
  for (int i = 0; i < nbSol_; i++)
  { // calcul de la modification de spin
    double ecartCourant = (solutions_ [i].spin () - spin).norme ();

    if (ecartCourant < meilleurEcart)
    { meilleurEcart    = ecartCourant;
      meilleureSpinAtt = i;
    }

  }

  return solutions_ [meilleureSpinAtt];

}
