subroutine mt_topo_sgd_E_N (pos_E, pos_N, code_retour, vit_E, vit_N, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Passage d'un repere TOPOcentrique Est (convention axe Ox vers l'Est) au repere topocentrique Nord associe
! ===   (convention axe Ox vers le Nord) en coordonnees Site/Gisement/Distance.
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par la routine mt_topo_sgd_N_E
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 258 ed01 rev00): creation a partir de la routine MVTOPO (MVRTSG) de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mt_topo_sgd_E_N.h'

! Autres declarations
! -------------------
real(pm_reel)      ::    deux_pi

intrinsic present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mt_topo_sgd_E_N.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_topo_sgd_E_N.f90,v 1.7 2003/10/14 12:53:33 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! initialisation valeur de 2*pi
deux_pi = pm_deux_pi

!-----------------------------------------------
! calcul vecteur position en repere topocentrique 
!-----------------------------------------------

pos_N%s = pos_E%s
pos_N%g = deux_pi - pos_E%g
pos_N%d = pos_E%d

!----------------------
! calcul optionnels 
!----------------------
if (present(jacob)) then           ! calcul du jacobien

   jacob(:,:) = 0._pm_reel

   jacob(1,1) = 1._pm_reel
   jacob(2,2) = -1._pm_reel
   jacob(3,3) = 1._pm_reel
   jacob(4,4) = 1._pm_reel
   jacob(5,5) = -1._pm_reel
   jacob(6,6) = 1._pm_reel

end if

if (present(vit_N).and..not.present(vit_E)) then ! erreur de parametrage
      code_retour%valeur = pm_err_para_option
      go to 6000
else if (present(vit_E).and.present(vit_N)) then   !  calcul vecteur vitesse en repere topocentrique
vit_N%s = vit_E%s
vit_N%g = - vit_E%g
vit_N%d = vit_E%d
end if

if (.not.present(vit_N).and. present(vit_E))  code_retour%valeur = pm_warn_para_option ! parametrage optionnel incoherent


6000 continue

code_retour%routine = pm_num_mt_topo_sgd_E_N
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_topo_sgd_E_N
