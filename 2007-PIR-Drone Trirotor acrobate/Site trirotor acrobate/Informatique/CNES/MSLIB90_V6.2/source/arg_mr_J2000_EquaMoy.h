
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_J2000_EquaMoy


integer,                            intent(in)            :: model       ! indicateur des modeles de precession et de nutation
type(tm_jour_sec),                  intent(in)            :: jul1950     ! date julienne 1950 t (non normalisee) en jour et secondes
real(pm_reel),                      intent(in)            :: delta_tai   ! ecart entre l'echelle de temps TAI et l'echelle de temps utilisee pour la date t
real(pm_reel),        dimension(3), intent(in)            :: pos_J2000   ! vecteur position dans le repere equatorial moyen J2000
real(pm_reel),        dimension(3), intent(out)           :: pos_EquaMoy ! vecteur position dans le repere equatorial moyen a la date t
type(tm_code_retour),               intent(out)           :: code_retour
logical,                            intent(in),  optional :: inertiel    ! indicateur a vrai si calcul inertiel (sans vitesses d'entrainement)
real(pm_reel),        dimension(3), intent(in),  optional :: vit_J2000   ! vecteur vitesse dans le repere equatorial moyen J2000
real(pm_reel),        dimension(3), intent(out), optional :: vit_EquaMoy ! vecteur vitesse dans le repere equatorial moyen a la date t 
real(pm_reel),      dimension(6,6), intent(out), optional :: jacob       ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_J2000_EquaMoy.h,v 1.3 2004/10/14 09:02:12 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

