#ifndef BASISFUNCTIONS_H
#define BASISFUNCTIONS_H

/** This is a complete template header for generating 1D hp basis functions
 *
 *  © 2012-2013, Copy Rights Reserved.
 *  Roman Poya  roman.poya@cimne.com
*/


#include <boost/algorithm/string/predicate.hpp>     //For string comparison

#include"NumInt.h"
#include"hpBasis1D.h"

namespace FEAPB {


template<typename str1,typename B,typename str2>
class BasisFunctions {
private:
    B _C;
    str1 _base;
    str2 _numint;
    B _intsch;
    B _choosebases;
    B _chooselag;
public:
    BasisFunctions(){_choosebases=2; _chooselag=1; _intsch=1;
        _base="Lagrange"; _C=0; _numint="GaussQuadrature";}
    BasisFunctions(str1& base){_base=base; _C=0; _numint="GaussQuadrature"; _intsch=1;
    if (boost::iequals(_base,"Lagrange") || boost::iequals(_base,"Lagrangian"))
    {
        _choosebases=2;
        _chooselag=2;
    }
    else if (boost::iequals(_base,"LagrangeES") || boost::iequals(_base,"LagrangianES") || boost::iequals(_base,"Lagrange ES"))
    {
        _choosebases=2;
        _chooselag=1;
    }
    else if (boost::iequals(_base,"Legendre"))
    {
        _choosebases=1;
        _chooselag=0;
    }
                                }

    BasisFunctions(str1& base, int C) {_base=base; _C=C; _numint="GaussQuadrature"; _intsch=1;
        if (boost::iequals(_base,"Lagrange") || boost::iequals(_base,"Lagrangian"))
        {
            _choosebases=2;
            _chooselag=2;
        }
        else if (boost::iequals(_base,"LagrangeES") || boost::iequals(_base,"LagrangianES") || boost::iequals(_base,"Lagrange ES"))
        {
            _choosebases=2;
            _chooselag=1;
        }
        else if (boost::iequals(_base,"Legendre"))
        {
            _choosebases=1;
            _chooselag=0;
        }
                                        }
    BasisFunctions(str1& base, int C, str2& numint) {_base=base; _C=C; _numint=numint;
        if (boost::iequals(_base,"Lagrange") || boost::iequals(_base,"Lagrangian"))
        {
            _choosebases=2;
            _chooselag=2;
        }
        else if (boost::iequals(_base,"LagrangeES") || boost::iequals(_base,"LagrangianES") || boost::iequals(_base,"Lagrange ES"))
        {
            _choosebases=2;
            _chooselag=1;
        }
        else if (boost::iequals(_base,"Legendre"))
        {
            _choosebases=1;
            _chooselag=0;
        }

    if (boost::iequals(_numint,"GaussLobatto"))
    {
        _intsch=2;
    }
    else
    {
        _intsch=1;
    }

                                                        }

    template<typename DerivedA, typename DerivedB, typename DerivedC>
    void BasesPointsWeights(Eigen::MatrixBase<DerivedA>& zwbases, Eigen::MatrixBase<DerivedB>& zwgbases,
                                                         Eigen::MatrixBase<DerivedC>& zw);
};

template<typename str1,typename B,typename str2>
template<typename DerivedA, typename DerivedB, typename DerivedC>
inline void BasisFunctions<str1,B,str2>::BasesPointsWeights(Eigen::MatrixBase<DerivedA>& zwbases,
                                                            Eigen::MatrixBase<DerivedB>& zwgbases,
                                                            Eigen::MatrixBase<DerivedC>& zw){

//    _zwbases=zwbases; _zwgbases=zwgbases; _zw=zw;

    if (_intsch==2)
    {
       const int c=_C+3;
       zw=NumInt::GuassLobattoQaudrature(c);
    }
    else
    {
       double a=-1; double b=1; const int c=_C+2;
       zw=NumInt::GuassQaudrature(c,a,b);
    }

    for (int i=0; i<zw.rows(); i++)
    {
        Eigen::Matrix<double,-1,-1> temp;
        Eigen::MatrixBase<DerivedA>& hpbases=temp; // keep it like this because hpBasis1D is not templated
        if (_choosebases==2)
        {
            hpBasis1D hp(_C,zw(i,0),_chooselag,true);
            hpbases= hp.Lagrange();
        }
        else
        {
            hpBasis1D hp(_C,zw(i,0));
            hpbases= hp.Legendre();

        }

        zwbases.col(i)=hpbases.col(0);
        zwgbases.col(i)=hpbases.col(1);

    }

}

} // end of namespace

#endif // BASISFUNCTIONS_H
