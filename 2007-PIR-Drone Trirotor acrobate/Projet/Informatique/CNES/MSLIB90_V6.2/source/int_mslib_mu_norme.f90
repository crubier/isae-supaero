module int_mslib_mu_norme

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_norme( vect, norme, code_retour, vect_norme )

       use type_mslib
       use precision_mslib

       include 'arg_mu_norme.h'

     end subroutine mu_norme
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_norme.f90,v 1.2 2003/05/06 15:50:42 mslibatv Exp $ '

end module int_mslib_mu_norme
