
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mv_cir_equa_kep

type(tm_orb_cir_equa), intent(in)     ::  cir_equa     ! parametres adaptes aux orbites circulaires equatoriales
type(tm_orb_kep), intent(out)         ::  kep          ! parametres kepleriens
type(tm_code_retour), intent(out)     ::  code_retour
real(pm_reel), dimension(6,6), intent(out), optional :: jacob  ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mv_cir_equa_kep.h,v 1.3 2004/04/26 09:14:50 mslibdev Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

