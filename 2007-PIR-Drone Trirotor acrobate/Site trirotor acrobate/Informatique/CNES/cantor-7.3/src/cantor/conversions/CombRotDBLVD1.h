#ifndef __cantor_CombRotDBLVD1_h
#define __cantor_CombRotDBLVD1_h

static char rcsid_CombRotDBLVD1_h [] = "$Id: CombRotDBLVD1.h,v 1.2 1997/03/26 06:38:15 luc Exp $";

// ce paquetage r�alise les combinaisons d'op�randes
// entre les types rotations suivants:
//            double
//            class ValeurDerivee1
//

// il ne doit �tre utilis� que par le fichier "cantor/DeclDBLVD1.h",
// dont il n'est s�par� que pour des raisons de clart�

// combinaisons
inline int    operator == (const RotVD1& r, const RotDBL& q)
{ return RotVD1DBL (r) == q; }


inline int    operator == (const RotDBL& r, const RotVD1& q)
{ return r == RotVD1DBL (q); }

#endif
