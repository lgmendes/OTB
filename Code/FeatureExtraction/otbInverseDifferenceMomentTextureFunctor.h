/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbInverseDifferenceMomentTextureFunctor_h
#define __otbInverseDifferenceMomentTextureFunctor_h

#include "otbTextureFunctorBase.h"

namespace otb
{
namespace Functor
{
/** \class InverseDifferenceMomentTextureFunctor
 *  \brief This functor calculates the inverse difference moment of an image
 *
 *  Computes joint histogram (neighborhood and offset neighborhood).
 *  The formula is:
 *  \f$ \sum_{i}\sum_{j}\frac{1}{1+(i-j)^2}p(i,j) \f$
 *  TIterInput is an ietrator, TOutput is a PixelType.
 *
 *  \sa TextureFunctorBase
 *  \ingroup Functor
 *  \ingroup Statistics
 */

template <class TScalarInputPixelType, class TScalarOutputPixelType>
class ITK_EXPORT InverseDifferenceMomentTextureFunctor :
public TextureFunctorBase<TScalarInputPixelType, TScalarOutputPixelType>
{
public:
  InverseDifferenceMomentTextureFunctor(){};
  virtual ~InverseDifferenceMomentTextureFunctor(){};

  typedef TextureFunctorBase<TScalarInputPixelType, TScalarOutputPixelType> Superclass;
  typedef typename Superclass::NeighborhoodType                             NeighborhoodType;
 
 virtual double ComputeOverSingleChannel(const NeighborhoodType &neigh, const NeighborhoodType &neighOff)
  {
    this->ComputeJointHistogram(neigh, neighOff);
    double area = static_cast<double>(neigh.GetSize()[0]*neigh.GetSize()[1]);
    double areaInv = 1/area;
    double out = 0.;
      for (unsigned r = 0; r<this->GetHisto().size(); r++)
	{
	  for (unsigned s = 0; s<this->GetHisto()[r].size(); s++)
	    {
	      double p = static_cast<double>(this->GetHisto()[r][s]) * areaInv;
	      double dist = vcl_pow( ( (static_cast<double>(r)+0.5)*this->GetOffsetBinLength())-((static_cast<double>(s)+0.5)*this->GetNeighBinLength()), 2);

	      out += ((1/(1+dist)) * p);
	    }
	}
      return out;
  }

};




  } // namespace Functor
} // namespace otb

#endif

