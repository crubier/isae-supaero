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
//>       Senseur.h
//$Resume
//       fichier d'en-t�te de la classe Senseur
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Senseur    
//>       enum typeMethode 
//>       enum codeAstre 
//$Historique
//       $Log: Senseur.h,v $
//       Revision 3.20  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 3.19  2002/12/11 17:11:00  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 3.18  2002/02/27 14:09:09  marmottes
//       suppression de la description de la r�vision ins�r�e manuellement
//       et mise � jour du copyright CNES
//
//       Revision 3.17  2002/02/22 09:48:55  marmottes
//       D�claration de la m�thode Senseur::initialiseDerive (DM 0002)
//
//       Revision 3.16  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 3.15  2001/04/05 09:58:04  luc
//       �limination de l'initialisation � 1 inutile
//
//       Revision 3.14  2001/04/04 12:09:19  luc
//       ajout de la m�thode criteresControlabilite
//
//       Revision 3.13  2000/10/02 12:32:12  luc
//       remplacement d'attributs entiers en bool�ens
//
//       Revision 3.12  2000/09/13 09:48:26  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 3.11  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 3.10  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 3.9  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 3.8  1999/08/06 13:32:18  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 3.7  1998/07/15 12:22:59  luc
//       ajout des m�thodes virtuelles :
//       modifieCible, initialiseGyro, modifieReference, prendEtatEnCompte
//
//       Revision 3.6  1998/06/25 06:12:16  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 3.5  1998/04/26 18:25:25  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.4  1997/09/23 09:25:32  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 3.3  1997/08/20 09:50:06  luc
//       ajout d'un en-t�te de fichier
//       ajout d'un attribut valeurConsigne_
//       utilisation de ChaineSimple
//       d�placement de constructeurs dans le .h (simplifi�s gr�ce � ChaineSimple)
//       implantation d'une version g�n�rique de la m�thode modeliseConsigne
//
//       Revision 3.2  1997/04/27 19:33:40  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//
//       Revision 3.1  1997/01/28 12:46:31  luc
//       ajout d'un #include "marmottes/marmottes_erreurs.h"
//       (car "marmottes/etat.h" ne le fait plus)
//
//       Revision 2.2  1996/09/11 17:44:19  luc
//       ajout du nom du senseur dans l'instance
//
//       Revision 2.1  1996/07/31 17:21:48  luc
//       ajout d'une possibilit� de modifier le rep�re senseur � l'ex�cution
//
//       Revision 1.3  1995/01/30 09:43:27  mercator
//       ajout de l'initialisation de pointeurs d'erreur en sortie
//       ajout d'initialisations des cibles de senseurs geometriques
//
//       Revision 1.2  1995/01/27 16:59:47  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//
//       Revision 1.1  1994/12/23 11:00:13  luc
//       Initial revision
//
//$Version
//       $Id: Senseur.h,v 3.20 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Senseur_h
#define __marmottes_Senseur_h

#include <string>

#include "cantor/DeclDBLVD1.h"

#include "marmottes/Etat.h"
#include "marmottes/MarmottesErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Senseur
//$Resume
//       classe abstraite masquant le type sous-jacent de senseur utilis�.
//
//$Description
//       Cette classe abstraite est l'interface d'acc�s � tous les
//       types de senseurs, elle permet de rendre les routines de
//       calculs appelantes ind�pendantes des d�tails de mod�lisation
//       des senseurs.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       enum typeMethode  : 
//          m�thode de mod�lisation analytique
//>       Senseur& operator =              () 
//          affectation
//>       virtual Senseur *copie           () 
//          retourne une copie du senseur allou�e en m�moire
//>       virtual void respecterMesures    () 
//          force le senseur � respecter les unit�s de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur � convertir les unit�s de mesures dans
//          ses sortie
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le rep�re donn�
//>       int calage                       () 
//          tourne le senseur � partir du rep�re de base autour de
//          l'axe de calage.
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'�tat donn�
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contr�ler
//          l'attitude de l'�tat donn�
//>       virtual int criteresControlabilite () 
//          calcule les crit�res de contr�labilit� de l'attitude
//          dans l'�tat donn�
//>       virtual int methode              () 
//          retourne un identificateur qui permet de regrouper les
//          senseurs de m�me principe g�n�ral (g�om�trique ou
//          cin�matique).
//>       virtual int modeliseConsigne     () 
//          permet de stocker un mod�le de la consigne que doit
//          respecter un senseur contr�lant l'attitude du satellite
//          dans l'�tat courant ATTENTION: dans cet �tat, l'attitude
//          ne doit pas �tre utilis�e, elle ne sera initialis�e
//          correctement qu'� la fin de la r�solution ayant utilis� ce
//          mod�le!
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'�cart du senseur par rapport � sa
//          consigne � la date donn�e et dans l'attitude donn�e en
//          tenant compte de l'�tat pr�c�dent.
//>       const string& nom                () 
//          retourne le nom du senseur
//>       const RotDBL& repereBase         () 
//          retourne la rotation qui projette un vecteur exprim� en
//          rep�re satellite dans le rep�re senseur de base.
//>       const RotDBL& repere             () 
//          retourne la rotation qui projette un vecteur exprim� en
//          rep�re satellite dans le rep�re senseur courant.
//>       const VecDBL& axeCalage          () 
//          retourne l'axe de calage pr�d�fini pour le senseur
//>       double precision                 () 
//          retourne la pr�cision du senseur (toujours dans la m�me
//          unit� que mesure ()).
//>       bool conversionConsignes         () 
//          indique si le senseur doit convertir les consignes en
//          entr�e dans son unit� interne
//>       bool conversionMesures           () 
//          indique si le senseur doit convertir les mesures en sortie
//          dans les unit�s externes
//>       double valeurConsigne            () 
//          retourne la valeur de consigne courante (toujours dans la
//          m�me unit� que mesure ()).
//>       void respecterConsignes          () 
//          force le senseur � respecter les unit�s de consignes
//          fournies en entr�e
//>       void convertirConsignes          () 
//          force le senseur � convertir les unit�s de mesures dans
//          ses sorties
//>       VecDBL satSens                   () 
//          projette un vecteur donn� en rep�re satellite dans le
//          rep�re senseur.
//>       VecDBL sensSat                   () 
//          projette un vecteur donn� en rep�re senseur dans le rep�re
//          satellite.
//>       virtual int modifieCible         () 
//          m�morise une cible utilisateur pour un senseur optique
//>       virtual int initialiseGyro       () 
//          initialise l'angle d'un gyro int�grateur
//>       virtual int modifieReference     () 
//          initialise l'attitude de r�f�rence d'un senseur de Cardan
//>       virtual void prendEtatEnCompte   () 
//>       void reinitialisePrecision       () protegee - 
//>       virtual void initialiseDerive    ()
//          initialisation de la d�rive d'un senseur
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class Senseur
{
public :

  enum typeMethode { intersectionCones, integrationSpin, aucuneMethode };

  enum codeAstre { nonSignificatif, soleil, lune, corpsCentral, aucunAstre };

  // constructeurs
  Senseur (const string &nom, const RotDBL& repere,
           const VecDBL& axeCalage, double precision)
  : nom_ (nom), repereBase_ (repere), repere_ (repere),
    axeCalage_ (axeCalage), precision_ (precision),
    convertirConsignes_ (false), convertirMesures_ (false),
    valeurConsigne_ (0)
  {}

  Senseur (const Senseur& s)
  : nom_ (s.nom_), repereBase_ (s.repereBase_), repere_ (s.repere_),
    axeCalage_ (s.axeCalage_), precision_ (s.precision_),
    convertirConsignes_ (s.convertirConsignes_),
    convertirMesures_ (s.convertirMesures_),
    valeurConsigne_ (s.valeurConsigne_)
  {}

  Senseur& operator = (const Senseur& s);

  // destructeur
  virtual ~Senseur () {}

  virtual Senseur *copie () const = 0;

  // acc�s aux �l�ments internes
  const string&       nom            () const { return nom_;            }
  const RotDBL&       repereBase     () const { return repereBase_;     }
  const RotDBL&       repere         () const { return repere_;         }
  const VecDBL&       axeCalage      () const { return axeCalage_;      }
  double              precision      () const { return precision_;      }
  bool           conversionConsignes () const { return convertirConsignes_; }
  bool           conversionMesures   () const { return convertirMesures_;   }
  double              valeurConsigne () const { return valeurConsigne_; }

  // conversions d'unit�s en entr�e et en sortie
  void respecterConsignes () { convertirConsignes_ = false; }
  void convertirConsignes () { convertirConsignes_ = true;  }
  virtual void respecterMesures () = 0;
  virtual void convertirMesures () = 0;

  // r�orientation du senseur
  virtual void  nouveauRepere   (const RotDBL& nouveau);
          void  calage          (double c)
            throw (MarmottesErreurs);

  // changements de rep�res
  VecDBL satSens (const VecDBL& sat)  const { return repere_ (sat);     }
  VecDBL sensSat (const VecDBL& sens) const { return (-repere_) (sens); }

  // mesure fournie par le senseur
  virtual double mesure                 (const Etat& etat)
    throw (MarmottesErreurs) = 0;

  // contr�labilit� d'une attitude
  virtual int    controlable            (const Etat& etat)
    throw (MarmottesErreurs, CantorErreurs) = 0;

  virtual void   criteresControlabilite (const Etat& etat,
                                         codeAstre *ptrInhibant,
                                         codeAstre *ptrEclipsant,
                                         double    *ptrEcartFrontiere,
                                         bool      *ptrAmplitudeSignificative)
    throw (MarmottesErreurs, CantorErreurs);

  // mod�lisations des consignes d'attitude
  virtual int            methode          () const = 0;
  virtual void           modeliseConsigne (const Etat& etat,
                                           double valeur)  
    throw (CantorErreurs, MarmottesErreurs) = 0;

  // fonction de r�solution de l'attitude
  virtual ValeurDerivee1 foncEcart        (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           const RotVD1& attitude,
                                           const VecVD1& spin
                                          ) = 0;

  // fonction de modification de la cible
  virtual void modifieCible (const VecDBL& cible)
    throw  (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::senseur_sans_cible,
                             nom ().c_str ());
  }

  // initialisation d'un gyro int�grateur
  virtual void initialiseGyro (double date, double angle)
    throw (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::pas_gyro_integrateur,
                             nom ().c_str ());
  }

  // mise en place du rep�re de r�f�rence pour un senseur de Cardan
  virtual void modifieReference (const RotDBL& reference)
    throw (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::senseur_sans_reference,
                             nom ().c_str ());
  }

  // prise en compte des �tats apr�s r�solution d'attitude (ce n'est
  // utile que pour les senseurs cin�matiques, et plus pr�cis�ment que
  // pour ceux qui int�grent les �volutions et doivent �tre tenus au
  // courant de l'�tat r�el du satellite � chaque pas)
  virtual void prendEtatEnCompte (const Etat& etat)
  {}

  // initialisation de la d�rive d'un senseur cin�matique
  virtual void initialiseDerive (double derive)
    throw (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::pas_senseur_cinematique,
                             nom ().c_str ());
  }

protected :

  // m�thode utilis�e pour changer les unit�s de la pr�cision
  void reinitialisePrecision (double precision) { precision_ = precision; }

  // constructeur par defaut : ne JAMAIS utiliser
  Senseur () {}

private :

  string nom_;
  RotDBL repereBase_;
  RotDBL repere_;
  VecDBL axeCalage_;  // <-- ATTENTION : coordonn�es dans le REP�RE DE BASE
  double precision_;
  bool   convertirConsignes_;
  bool   convertirMesures_;

  double valeurConsigne_;

};

#endif
