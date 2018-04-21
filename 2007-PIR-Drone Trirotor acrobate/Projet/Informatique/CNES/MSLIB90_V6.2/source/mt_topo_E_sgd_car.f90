subroutine mt_topo_E_sgd_car (pos_sgd, pos_car, code_retour, vit_sgd, vit_car, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Dans un repere TOPOcentrique Est (convention axe Ox vers l'Est) , 
! ===   passage des coordonnees Site/Gisement/Distance aux coordonnees CARtesiennes
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par la routine mt_topo_E_car_sgd
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 260 ed01 rev00): creation a partir de la routine MVRCAR de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mt_topo_E_sgd_car.h'

! Autres declarations
! -------------------
real(pm_reel), dimension(3)  :: poscar     !     variable intermediaire contenant la position cartesienne
real(pm_reel), dimension(3)  :: vitcar     !     variable intermediaire contenant la vitesse cartesienne
real(pm_reel)  ::  rcscg,rcssg,rsssg,rsscg !     variables intermediaires pour le calcul du jacobien
real(pm_reel)  ::  rcos1,rsin1,rcos2,rsin2 !     variables intermediaires

intrinsic present, cos, sin

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mt_topo_E_sgd_car.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_topo_E_sgd_car.f90,v 1.7 2003/10/14 12:53:03 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! ---------------------
! calcul intermediaires 
! ---------------------

rcos1 = cos(pos_sgd%s)
rsin1 = sin(pos_sgd%s)
rcos2 = cos(pos_sgd%g)
rsin2 = sin(pos_sgd%g)

rcscg = rcos1 * rcos2
rsssg = rsin1 * rsin2
rsscg = rsin1 * rcos2
rcssg = rcos1 * rsin2

! ------------------------------------------------------------
! calcul des composantes positions en coordonnees cartesiennes 
! ------------------------------------------------------------

poscar(1) = pos_sgd%d * rcssg  !     axe des x 
poscar(2) = pos_sgd%d * rcscg  !     axe des y 
poscar(3) = pos_sgd%d * rsin1  !     axe des z 


!----------------------
! calcul optionnels 
!----------------------

if ((present(vit_car) .and. .not.present(vit_sgd)) .or.(present(jacob).and. .not.present(vit_sgd))) then  ! mauvais parametrage
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ( present(vit_sgd).and. (.not.present(vit_car).and..not.present(jacob)))  code_retour%valeur = pm_warn_para_option 
                                                                           ! parametrage optionnel incoherent

if (present(vit_car).or.present(jacob)) then  !  calcul vecteur vitesse en coordonnees cartesiennes

   vitcar(1) = vit_sgd%d * rcssg - poscar(3) * rsin2 * vit_sgd%s+ poscar(2) * vit_sgd%g      !     axe des x 
   vitcar(2) = vit_sgd%d * rcscg - poscar(3) * rcos2 * vit_sgd%s- poscar(1) * vit_sgd%g      !     axe des y 
   vitcar(3) = (vit_sgd%d * rsin1) + pos_sgd%d * rcos1 * vit_sgd%s                           !     axe des z 

end if

if (present(jacob)) then            ! calcul du jacobien 

   jacob(:,:) = 0._pm_reel

   !     derivee partielle de x :
   !     ------------------------
   jacob(1,1) = - pos_sgd%d * rsssg
   jacob(1,2) = poscar(2)
   jacob(1,3) = rcssg

   !     derivee partielle de y :
   !     ------------------------
   jacob(2,1) = - pos_sgd%d * rsscg
   jacob(2,2) = - poscar(1)
   jacob(2,3) = rcscg

   !     derivee partielle de z :
   !     ------------------------
   jacob(3,1) = pos_sgd%d * rcos1
   jacob(3,3) = rsin1

   !     derivee partielle de vx :
   !     ------------------------
   jacob(4,1) = - vitcar(3) * rsin2 - poscar(3) * rcos2 *vit_sgd%g
   jacob(4,2) = vitcar(2) 
   jacob(4,3) = rcscg * vit_sgd%g - rsssg * vit_sgd%s
   jacob(4,4) = - pos_sgd%d * rsssg
   jacob(4,5) = poscar(2)
   jacob(4,6) = rcssg

   !     derivee partielle de vy :
   !     ------------------------
   jacob(5,1) = - vitcar(3) * rcos2 + poscar(3) * rsin2 * vit_sgd%g
   jacob(5,2) = - vitcar(1) 
   jacob(5,3) = -((rsscg * vit_sgd%s) + (rcssg * vit_sgd%g))
   jacob(5,4) = - pos_sgd%d * rsscg 
   jacob(5,5) =  - poscar(1)
   jacob(5,6) = rcscg 

   !     derivee partielle de vz :
   !     ------------------------
   jacob(6,1) = vit_sgd%d * rcos1 - poscar(3) * vit_sgd%s
   jacob(6,3) = rcos1 * vit_sgd%s
   jacob(6,4) = pos_sgd%d * rcos1
   jacob(6,6) = rsin1

end if

! Affectation des sorties
pos_car(:) = poscar(:)
if (present(vit_car)) vit_car(:) = vitcar(:)

6000 continue

code_retour%routine = pm_num_mt_topo_E_sgd_car
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_topo_E_sgd_car
