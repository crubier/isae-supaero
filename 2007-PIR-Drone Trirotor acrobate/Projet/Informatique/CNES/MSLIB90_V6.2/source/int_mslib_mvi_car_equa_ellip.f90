module int_mslib_mvi_car_equa_ellip

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_car_equa_ellip( pos_car, vit_car,rrxv,norme_vect_pos,norme_vect_vit,norme_moment_cinetique,&
                                    un_sur_a,excentricite ,rscal,mu,equa,retour,jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mvi_car_equa_ellip.h'

     end subroutine mvi_car_equa_ellip
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_car_equa_ellip.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mvi_car_equa_ellip
