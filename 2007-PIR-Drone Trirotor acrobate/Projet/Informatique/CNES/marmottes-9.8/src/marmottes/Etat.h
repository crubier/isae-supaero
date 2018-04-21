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
//>       Etat.h
//$Resume
//       fichier d'en-t�te de la classe Etat
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Etat
//$Historique
//       $Log: Etat.h,v $
//       Revision 4.17  2003/02/27 16:18:11  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 4.16  2002/12/02 17:02:29  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 4.15  2002/09/13 08:49:51  marmottes
//       extension du copyright � 2002 suite � la DM 0007
//
//       Revision 4.14  2002/09/09 13:21:26  marmottes
//       ajout de la m�thode enregistreCorps, modification des attributs et
//       utilisation de la classe BodyEphem (DM 0007)
//
//       Revision 4.13  2001/07/17 15:23:41  luc
//       ajout d'une m�thode vitesseRotation
//
//       Revision 4.12  2001/06/06 07:58:35  luc
//       remont�e des exceptions Cantor
//
//       Revision 4.11  2001/04/04 12:16:40  luc
//       ajout des distances lune et soleil
//       report du corps du constructeur par copie dans Etat.cc
//
//       Revision 4.10  2001/03/26 11:10:19  luc
//       ajout des caract�ristiques du corps central
//
//       Revision 4.9  2000/09/13 08:45:21  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 4.8  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 4.7  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 4.6  1999/08/06 13:32:17  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 4.5  1998/06/25 05:58:06  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 4.4  1998/05/14 12:03:34  luc
//       d�placement d'un constructeur dans le .cc
//
//       Revision 4.3  1998/04/26 18:24:54  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 4.2  1998/04/26 18:20:54  luc
//       ajout d'une gestion d'unit�s de position et de vitesse variables
//
//       Revision 4.1  1997/11/27 07:06:37  luc
//       ajout du temps sid�ral
//
//       Revision 3.5  1997/09/15 09:30:44  luc
//       d�placement de certains constructeurs dans le .cc
//
//       Revision 3.4  1997/09/03 09:28:15  luc
//       renommage de Etat::soleil () en Etat::satSoleil ()
//       renommage de Etat::lune   () en Etat::satLune   ()
//       ajout de Etat::terreSoleil ()
//
//       Revision 3.3  1997/08/20 09:31:35  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.2  1997/04/27 19:32:10  luc
//       ajout des directions lune et soleil
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 3.1  1997/01/28 12:36:53  luc
//       ajout de la vitesse du satellite
//       initialisation de spin d�s le d�but
//       (il n'y a donc plus besoin de compter les r�initialisations)
//       
//       Revision 2.1  1996/07/31 16:46:03  luc
//       abandon des tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en marmottes_erreurs.h
//       
//       Revision 1.5  1996/02/19 15:57:43  luc
//       ajout d'un constructeur utilisant le spin
//       
//       Revision 1.4  1995/07/12 12:16:54  mercator
//       ajout d'une methode de desinitialisation de l'etat
//       
//       Revision 1.3  1995/02/06 08:07:52  mercator
//       prise en compte du spin precedent pour estimer le spin courant
//       incorporation de l'extrapolation de spin dans la classe Etat
//       
//       Revision 1.2  1995/01/27 16:59:34  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:02  luc
//       Initial revision
//
//$Version
//       $Id: Etat.h,v 4.17 2003/02/27 16:18:11 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Etat_h
#define __marmottes_Etat_h

#include "cantor/DeclDBLVD1.h"
#include "cantor/CantorErreurs.h"
#include "marmottes/MarmottesErreurs.h"
#include "marmottes/BodyEphemC.h"
#include "marmottes/BodyEphemF.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Etat
//
//$Resume
//       classe g�rant l'�tat d'un simulateur d'attitude et son �volution
//
//$Description
//       Cette classe concr�te m�morise les �tats pr�c�dent et courant
//       d'un satellite. Elle stocke en particulier date, position,
//       vitesse, attitude et spin. Pour des raison d'optimisation les
//       positions de la lune et du soleil pour la date courante sont
//       �galement g�r�s par cette classe.
//
//$Usage
//>     construction : 
//          sans argument, � partir des date/position/vitesse/attitude et
//          �ventuellement spin, par copie
//>     utilisation  : 
//>       Etat& operator =          () 
//          affectation
//>       void desinitialise        () 
//          d�sinitialise l'etat
//>       void reinitialise         () 
//          r�initialise l'�tat (soit sans le spin, soit uniquement le spin)
//>       int unitesPositionVitesse () 
//          modifie l'interpr�tation des unit�s de position/vitesse
//          re�ue de l'appelant
//>       int normesLitigieuses     () 
//          indique que les normes sont temporairement sujettes �
//          caution et que les parallaxes peuvent �tre erron�es
//>       VecDBL spinExtrapole      () 
//          retourne une extrapolation du spin permettant d'atteindre
//          la cible en date et attitude, en restant coh�rent avec le
//          spin de l'�tat courant. Le spin conserv� dans l'�tat n'est
//          pas modifi�
//>       VecVD1 spinExtrapole      () 
//          retourne une extrapolation du spin permettant d'atteindre
//          la cible en date et attitude, en restant coh�rent avec le
//          spin de l'�tat courant. Le spin conserv� dans l'�tat n'est
//          pas modifi�
//>       RotDBL attitudeExtrapolee () 
//          attitudeExtrapolee (date) retourne une extrapolation de
//          l'attitude � la date donn�e. L'attitude conserv�e dans
//          l'�tat n'est pas modifi�e
//>       double date               () 
//          retourne la date m�moris�e
//>       double tempsSideral       () 
//          retourne le temps sid�ral � la date courante
//>       const VecDBL& position    () 
//          retourne la position m�moris�e
//>       const VecDBL& vitesse     () 
//          retourne la vitesse m�moris�e
//>       const RotDBL& attitude    () 
//          retourne l'attitude m�moris�e
//>       const RotVD1& attitudeVD1 () 
//          retourne l'attitude m�moris�e
//>       const VecDBL& spin        () 
//          retourne le spin m�moris�
//>       double aplatissement      () 
//          retourne l'aplatissement du corps central
//>       double rayonEquatorial    () 
//          retourne le rayon �quatorial du corps central
//>       double rayonCorpsCentral  () 
//          retourne le rayon angulaire du corps central
//>       double vitesseRotation    () 
//          retourne le vitesse angulaire de rotation du corps central
//>       const VecDBL& satLune     () 
//          retourne la direction satellite lune � la date courante
//>       double rayonLune          () 
//          retourne le rayon lune angulaire
//>       const VecDBL& satSoleil   () 
//          retourne la direction satellite soleil � la date courante
//>       const VecDBL& terreSoleil () 
//          retourne la direction terre soleil � la date courante
//>       double rayonSoleil        () 
//          retourne le rayon soleil angulaire
//>       double coeffPosition      () 
//          retourne le coefficient de conversion des positions
//>       double coeffVitesse       () 
//          retourne le coefficient de conversion des vitesses
//>       void enregistreCorps      () 
//          donne acc�s aux fonctions utilisateurs de calculs d'�ph�m�rides 
//          par rapport au corps central (�crites en C ou en fortran)
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class Etat
{ 

  public :

  // constructeurs
  Etat ()
    throw (CantorErreurs);

  Etat (double date, const VecDBL& position, const VecDBL& vitesse,
        const RotDBL& attitude, const VecDBL& spin,
        double coeffPosition, double coeffVitesse)
    throw (CantorErreurs);

  Etat (double date, const VecDBL& position, const VecDBL& vitesse,
        const RotDBL& attitude,
        double coeffPosition, double coeffVitesse)
    throw (CantorErreurs);

  Etat (const Etat& e);

  Etat& operator = (const Etat& e);

  // destructeur
  ~Etat();

  // fonctions de mise � jour
  void desinitialise ();
  void reinitialise  (double date,
                      const VecDBL& position, const VecDBL& vitesse,
                      const RotDBL& attitude)
    throw (CantorErreurs);
  void reinitialise  (const VecDBL& spin) { spin_ = spin; }

  void unitesPositionVitesse (const string& unitePos, const string& uniteVit)
    throw (MarmottesErreurs);

  // fonctions d'acc�s aux �l�ments internes
  double        date         () const { return date_;         }
  double        tempsSideral () const { return tempsSideral_; }
  const VecDBL& position     () const
  { static VecDBL p; p = position_ / coeffPosition_; return p; }
  const VecDBL& vitesse      () const
  { static VecDBL v; v = vitesse_  / coeffVitesse_;  return v; }
  const RotDBL& attitude     () const { return attitude_;     }
  const RotVD1& attitudeVD1  () const { return attitudeVD1_;  }
  const VecDBL& spin         () const { return spin_;         }

  double aplatissement       () const { return (ptrBodyEphem_ -> getOblateness()); }

  double rayonEquatorial     () const { return (ptrBodyEphem_ -> getEquatorialRadius() / coeffPosition_) ; }

  double rayonCorpsCentral   () const { return rayonCorpsCentral_; }

  double vitesseRotation     () const { return (ptrBodyEphem_ -> getRotationVelocity()); }

  const VecDBL& satLune      () const { return satLune_;      }
  double        distLune     () const { return distLune_ / coeffPosition_; }
  double        rayonLune    () const { return rayonLune_;    }
  const VecDBL& satSoleil    () const { return satSoleil_;    }
  double        distSoleil   () const { return distSoleil_ / coeffPosition_; }
  const VecDBL& terreSoleil  () const { return terreSoleil_;  }
  double        rayonSoleil  () const { return rayonSoleil_;  }

  double         coeffPosition     () const { return coeffPosition_; }
  double         coeffVitesse      () const { return coeffVitesse_;  }
  void           normesLitigieuses () const
    throw (MarmottesErreurs);

  VecDBL spinExtrapole      (double date, const RotDBL& attitude) const;
  VecVD1 spinExtrapole      (double date, const RotVD1& attitude) const;
  RotDBL attitudeExtrapolee (double date) const;

  void enregistreCorps (double equatorialRadius, 
                        double oblateness, double rotationVelocity,
                        double moonRadius, double sunRadius,
                        BodyEphemC::TypeFuncTsid *tsidFunc, 
                        BodyEphemC::TypeFuncPos *sunFunc, BodyEphemC::TypeFuncPos *moonFunc, 
                        BodyEphemC::TypeFuncPos *earthFunc);

  void enregistreCorps (double equatorialRadius, 
                        double oblateness, double rotationVelocity, 
                        double moonRadius, double sunRadius,
                        BodyEphemF::TypeFuncTsid *tsidFunc, 
                        BodyEphemF::TypeFuncPos *sunFunc, BodyEphemF::TypeFuncPos *moonFunc, 
                        BodyEphemF::TypeFuncPos *earthFunc);

  private :

  double            date_;
  double            tempsSideral_;
  VecDBL            position_;
  VecDBL            vitesse_;
  RotDBL            attitude_;
  RotVD1            attitudeVD1_;
  VecDBL            spin_;
  double            rayonCorpsCentral_;
  VecDBL            satLune_;
  double            distLune_;
  double            rayonLune_;
  VecDBL            satSoleil_;
  double            distSoleil_;
  VecDBL            terreSoleil_;
  double            rayonSoleil_;

  BodyEphem        *ptrBodyEphem_;

  double            coeffPosition_;
  double            coeffVitesse_;
  int               normesLitigieuses_;

  void miseAJourTempsSideral (double decalage = 0.0);
  void miseAJourAstres       () throw (CantorErreurs);

};

#endif
