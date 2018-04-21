subroutine mr_J2000_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_J2000, pos_TerVrai, code_retour, &
                              vit_J2000, vit_TerVrai, jacob )

! (C) Copyright CNES - MSLIB - 2002

!************************************************************************
!
! But:  passage du repere equatorial moyen J2000 au repere terrestre vrai a la date t
! ===
!
! Note d'utilisation:   [DR1] "Les systemes de reference utilises en astronomie"
! ===================        de M. Chapront-Touze, G. Francou et B. Morando
!                            Bureau Des Longitudes (BDL) novembre 1994
!                            ISSN 1243-4272
!                            ISBN 2-910015-05-X
!                            nomenclature MSLIB M-NT-0-160-CN
!                      Nota: Les epoques B1900, J1900 et J2000 sont explicitees en
!                            page 23 table 1.1
!
!                      Les vitesses declarees en sorties optionnelles ne peuvent etre calculees 
!                      que si les vitesses declarees en entree optionnelles sont specifiees.
!
! Historique:
! ==========
!   + Version 4.0 (SP 457 ed01 rev00): creation a partir de rien
!   + Version 4.1 (DE globale 484 ed01 rev00): calcul de la jacobienne 
!
!************************************************************************


! Modules
! =======
use int_mslib_mr_J2000_EquaMoy
use int_mslib_mr_EquaMoy_EquaVrai
use int_mslib_mr_EquaVrai_TerVrai

use code_modeles_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_J2000_TerVrai.h'

! Autres declarations
! ===================

real(pm_reel),        dimension(3) :: pos_EquaVrai, vit_EquaVrai ! vecteurs position/vitesse intermediaires
real(pm_reel),        dimension(3) :: pos_EquaMoy, vit_EquaMoy   ! vecteurs position/vitesse intermediaires
real(pm_reel),      dimension(6,6) :: jacob_1, jacob_2, jacob_3, jacob_int  ! jacobiennes intermediaires

type(tm_code_retour)               :: code_retour_local

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_J2000_TerVrai.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id = &
         ' $Id: mr_J2000_TerVrai.f90,v 1.13 2003/10/14 12:48:24 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

! autres initialisations

! Debut de corps du programme
! ===========================

! test sur la coherence des entrees/sorties optionnelles si precisees

if ((present(vit_TerVrai)) .and. (.not. present(vit_J2000))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_J2000)) .and. (.not. present(vit_TerVrai))) then
   code_retour%valeur = pm_warn_para_option
end if

! test sur le modele choisi 

if (model /= pm_lieske_wahr) then

   code_retour%valeur = pm_err_ind_model
   go to 6000

end if

if (present(jacob)) then               ! avec la jacobienne

   if (present(vit_TerVrai)) then      ! avec les vitesses

      !  calcul du passage du repere J2000 au repere celeste moyen a la date t

      call mr_J2000_EquaMoy ( model, jul1950, delta_tai, pos_J2000, pos_EquaMoy, code_retour_local,             &
           vit_J2000=vit_J2000, vit_EquaMoy=vit_EquaMoy, jacob=jacob_1 )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste moyen au repere celeste vrai a la date t

      call mr_EquaMoy_EquaVrai ( model, jul1950, delta_tai, pos_EquaMoy, pos_EquaVrai, code_retour_local,           &
           vit_EquaMoy=vit_EquaMoy, vit_EquaVrai=vit_EquaVrai, jacob=jacob_2 )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste vrai au repere Terrestre Vrai a la date t

      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local,  &
           vit_EquaVrai=vit_EquaVrai, vit_TerVrai=vit_TerVrai, jacob=jacob_3 )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if


   else                                ! sans les vitesses

      !  calcul du passage du repere J2000 au repere celeste moyen a la date t

      call mr_J2000_EquaMoy ( model, jul1950, delta_tai, pos_J2000, pos_EquaMoy, code_retour_local, jacob=jacob_1 )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste moyen au repere celeste vrai a la date t

      call mr_EquaMoy_EquaVrai ( model, jul1950, delta_tai, pos_EquaMoy, pos_EquaVrai, code_retour_local, jacob=jacob_2 )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste vrai au repere Terrestre Vrai a la date t

      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local, jacob=jacob_3 )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

   end if

   jacob_int = matmul(jacob_2,jacob_1)
   jacob =  matmul(jacob_3,jacob_int)

else                                   ! sans la jacobienne

   if (present(vit_TerVrai)) then      ! avec les vitesses

      !  calcul du passage du repere J2000 au repere celeste moyen a la date t

      call mr_J2000_EquaMoy ( model, jul1950, delta_tai, pos_J2000, pos_EquaMoy, code_retour_local,             &
           vit_J2000=vit_J2000, vit_EquaMoy=vit_EquaMoy )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste moyen au repere celeste vrai a la date t

      call mr_EquaMoy_EquaVrai ( model, jul1950, delta_tai, pos_EquaMoy, pos_EquaVrai, code_retour_local,           &
           vit_EquaMoy=vit_EquaMoy, vit_EquaVrai=vit_EquaVrai )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste vrai au repere Terrestre Vrai a la date t

      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local,  &
           vit_EquaVrai=vit_EquaVrai, vit_TerVrai=vit_TerVrai )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if


   else                                ! sans les vitesses

      !  calcul du passage du repere J2000 au repere celeste moyen a la date t

      call mr_J2000_EquaMoy ( model, jul1950, delta_tai, pos_J2000, pos_EquaMoy, code_retour_local )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste moyen au repere celeste vrai a la date t

      call mr_EquaMoy_EquaVrai ( model, jul1950, delta_tai, pos_EquaMoy, pos_EquaVrai, code_retour_local )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

      !  calcul du passage du repere celeste vrai au repere Terrestre Vrai a la date t

      call mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour_local )

      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur           ! affectation du code retour
         if (code_retour%valeur < pm_OK) go to 6000  ! sortie si erreur
      end if

   end if

end if

! Fin de corps du programme
! =========================




6000 continue

code_retour%routine = pm_num_mr_J2000_TerVrai
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_J2000_TerVrai
