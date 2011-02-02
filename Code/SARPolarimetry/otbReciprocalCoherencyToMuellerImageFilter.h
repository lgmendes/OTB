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

#ifndef __ReciprocalCoherencyToMuellerImageFilter_h
#define __ReciprocalCoherencyToMuellerImageFilter_h

#include "otbUnaryFunctorImageFilter.h"

namespace otb
 {

namespace Functor {

/** \class otbCoherencyToMuellerFunctor
 * \brief Evaluate the Mueller matrix from the reciprocal coherency matrix image
 *
 */
template< class TInput, class TOutput>
class ReciprocalCoherencyToMuellerFunctor
{
public:
  typedef double                                   RealType;
  typedef typename std::complex <RealType>         ComplexType;
  typedef typename TOutput::ValueType              OutputValueType;

  inline TOutput operator()( const TInput & Coherency ) const
    {
    TOutput result;
    result.SetSize(NumberOfComponentsPerPixel);

    RealType T1 = static_cast<RealType>(Coherency[0].real());
    RealType T2 = static_cast<RealType>(Coherency[3].real());
    RealType T3 = static_cast<RealType>(Coherency[5].real());
    RealType T4 = static_cast<RealType>(Coherency[1].real());
    RealType T5 = static_cast<RealType>(Coherency[1].imag());
    RealType T6 = static_cast<RealType>(Coherency[2].real());
    RealType T7 = static_cast<RealType>(Coherency[2].imag());
    RealType T8 = static_cast<RealType>(Coherency[4].real());
    RealType T9 = static_cast<RealType>(Coherency[4].imag());

    result[0] = static_cast<RealType>( (T1+T2+T3)/2. );  // A0+B0
    result[1] = static_cast<RealType>( (T1+T2-T3)/2. );  // A0+B
    result[2] = static_cast<RealType>( (T1-T2+T3)/2. );  // A0-B
    result[3] = static_cast<RealType>( (-T1+T2+T3)/2.);  // -A0+B0
    result[4] = static_cast<RealType>( T4 );             // C
    result[5] = static_cast<RealType>( T6 );             // H
    result[6] = static_cast<RealType>( T9 );             // F
    result[7] = static_cast<RealType>( T8 );             // E
    result[8] = static_cast<RealType>( T7 );             // G
    result[9] = static_cast<RealType>(-T5 );             // D

    return result;
    }

   unsigned int GetOutputSize()
   {
     return NumberOfComponentsPerPixel;
   }

   /** Constructor */
   ReciprocalCoherencyToMuellerFunctor() {}

   /** Destructor */
   ~ReciprocalCoherencyToMuellerFunctor() {}

private:
   itkStaticConstMacro(NumberOfComponentsPerPixel, unsigned int, 10);
};
}


/** \class otbReciprocalCoherencyToMuellerImageFilter
 * \brief Compute the Mueller matrix image (9 real channels)
 * from the Reciprocal coherency image (6 complex channels)
 */
template <class TInputImage, class TOutputImage, class TFunction = Functor::ReciprocalCoherencyToMuellerFunctor<
    ITK_TYPENAME TInputImage::PixelType, ITK_TYPENAME TOutputImage::PixelType> >
class ITK_EXPORT ReciprocalCoherencyToMuellerImageFilter :
   public otb::UnaryFunctorImageFilter<TInputImage, TOutputImage, TFunction>
{
public:
   /** Standard class typedefs. */
   typedef ReciprocalCoherencyToMuellerImageFilter  Self;
   typedef otb::UnaryFunctorImageFilter<TInputImage, TOutputImage, TFunction> Superclass;
   typedef itk::SmartPointer<Self>        Pointer;
   typedef itk::SmartPointer<const Self>  ConstPointer;

   /** Method for creation through the object factory. */
   itkNewMacro(Self);

   /** Runtime information support. */
   itkTypeMacro(ReciprocalCoherencyToMuellerImageFilter, UnaryFunctorImageFilter);


protected:
   ReciprocalCoherencyToMuellerImageFilter() {}
  virtual ~ReciprocalCoherencyToMuellerImageFilter() {}

private:
  ReciprocalCoherencyToMuellerImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&);            //purposely not implemented

};
  
} // end namespace otb

#endif