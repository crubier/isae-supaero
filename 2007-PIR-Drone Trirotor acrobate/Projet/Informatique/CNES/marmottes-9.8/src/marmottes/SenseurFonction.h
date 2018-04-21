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
//>       SenseurFonction.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurFonction
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurFonction
//
//$Historique
//       $Log: SenseurFonction.h,v $
//       Revision 1.9  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.8  2003/02/27 16:13:59  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.7  2002/12/11 17:17:09  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.6  2002/12/02 17:05:40  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.5  2002/01/17 09:39:05  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.4  2001/07/17 15:32:39  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.3  2001/03/26 11:12:57  luc
//        mise � jour r�sultant de la mod�lisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.2  2000/09/13 10:57:39  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.1  2000/06/07 14:05:54  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonction.h,v 1.9 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurFonction_h
#define __marmottes_SenseurFonction_h

#include "marmottes/SenseurOptique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurFonction
//
//$Resume
//       mod�lisation d'un pseudo-senseur plaquant une fonction pr�d�finie
//       sur la sph�re unit�
//
//$Description
//       mod�lisation d'un senseur plaquant une fonction pr�d�finie
//       sur la sph�re unit�. L'utilisation principale d'un tel senseur
//       est de repr�senter des gains d'antenne.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//>     utilisation  : 
//>       SenseurFonction& operator =        () 
//          affectation
//>       virtual void respecterMesures    () 
//          pour ce pseudo-senseur, cette fonction n'agit pas
//          (les mesures d�pendent de la fonction plaqu�e, non modifiable)
//>       virtual void convertirMesures    () 
//          pour ce pseudo-senseur, cette fonction n'agit pas
//          (les mesures d�pendent de la fonction plaqu�e, non modifiable)
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le rep�re donn�
//>       virtual void modeliseConsigne     () 
//          ce pseudo-senseur ne pouvant pas �tre utilis� en consigne,
//          cette fonction retourne syst�matiquement une erreur
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'�tat donn�
//>       virtual ValeurDerivee1 foncEcart () 
//          ce pseudo-senseur ne pouvant pas �tre utilis� en consigne,
//          cette fonction retourne syst�matiquement 1.0
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allou�e en m�moire
//>       virtual int methode              () 
//          retourne un indicateur interdisant d'utiliser ce senseur
//          en consigne.
//>       virtual double fonction          () 
//          �value la fonction sous-jacente plaqu�e sur la sph�re unit�
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurFonction : public SenseurOptique
{

  public :

  // constructeurs
  SenseurFonction (const string& nom, const RotDBL& repere,
                   const VecDBL& axeCalage, double precision,
                   codeCible code, const StationCible *ptrStation,
                   const VecDBL& observe,
                   Parcelle* ptrChampDeVue,
                   Parcelle *ptrChampInhibitionSoleil,
                   Parcelle *ptrChampInhibitionLune,
                   Parcelle *ptrChampInhibitionCentral,
                   double margeEclipseSoleil, double margeEclipseLune,
                   double seuilPhaseLune,
                   const VecDBL& axe, const VecDBL& origine)
    throw (CantorErreurs);

  SenseurFonction (const SenseurFonction& s)
    : SenseurOptique (s),
      i_ (s.i_), j_ (s.j_), k_ (s.k_)
  {}

  SenseurFonction& operator = (const SenseurFonction& s);

  // destructeur
  virtual ~SenseurFonction () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  // r�orientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de r�solution de l'attitude
  virtual int    methode          () const { return aucuneMethode; }

  virtual void   modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double mesure           (const Etat& etat)
    throw (MarmottesErreurs);
  virtual ValeurDerivee1 foncEcart (const Etat& etatPrecedent,
                                    const Etat& etatResolution,
                                    const RotVD1& attitude,
                                    const VecVD1& spin
                                   );

  // fonction de mesure plaqu�e sur la sph�re
  virtual double fonction (double azimut, double depointage) const
    throw (MarmottesErreurs) = 0;

  protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurFonction () {}

  private :

  VecDBL i_;
  VecDBL j_;
  VecDBL k_;

};

#endif
