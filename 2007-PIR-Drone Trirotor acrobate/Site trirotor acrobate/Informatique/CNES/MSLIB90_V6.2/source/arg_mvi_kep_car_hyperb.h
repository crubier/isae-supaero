
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mvi_kep_car_hyperb
                                                              
type(tm_orb_kep), intent(in)                         :: kep     ! parametres kepleriens
real(pm_reel), intent(in)                            :: mu      ! constante de la gravitation

real(pm_reel), dimension(3), intent(out)             :: pos_car ! position en coordonnees cartesiennes
real(pm_reel), dimension(3), intent(out)             :: vit_car ! vitesse ne coordonnees cartesiennes
integer ,intent(out)                                 ::  retour
real(pm_reel), dimension(6,6), intent(out), optional :: jacob   ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mvi_kep_car_hyperb.h,v 1.1.1.1 2002/10/24 08:34:16 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

