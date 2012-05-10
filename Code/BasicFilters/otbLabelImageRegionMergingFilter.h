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
#ifndef __otbLabelImageRegionMergingFilter_h
#define __otbLabelImageRegionMergingFilter_h

#include "otbImage.h"
#include "otbVectorImage.h"
#include "itkImageToImageFilter.h"

namespace otb
{

/** \class LabelImageRegionMergingFilter
 *
 *
 * This class merges regions in the input label image according to the input
 * image of spectral values and the RangeBandwidth parameter.
 *
 *
 * \ingroup ImageSegmentation
 * \ingroup ImageEnhancement
 */
template <class TInputLabelImage, class TInputSpectralImage, class TOutputLabelImage = TInputLabelImage>
class ITK_EXPORT LabelImageRegionMergingFilter
  : public itk::ImageToImageFilter<TInputLabelImage, TOutputLabelImage>
{
public:
  /** Standard class typedef */
  typedef LabelImageRegionMergingFilter                                Self;
  typedef itk::ImageToImageFilter<TInputLabelImage, TOutputLabelImage> Superclass;
  typedef itk::SmartPointer<Self>                                      Pointer;
  typedef itk::SmartPointer<const Self>                                ConstPointer;
  typedef double                                                       RealType;

  /** Type macro */
  itkTypeMacro(LabelImageRegionMergingFilter, ImageToImageFilter);
  itkNewMacro(Self);

  /** Template parameters typedefs */

  typedef TInputLabelImage                        InputLabelImageType;
  typedef typename InputLabelImageType::PixelType InputLabelType;

  typedef TInputLabelImage                        InputImageType;
  typedef typename InputImageType::Pointer        InputImagePointerType;
  typedef typename InputImageType::PixelType      InputPixelType;
  typedef typename InputImageType::IndexType      InputIndexType;
  typedef typename InputImageType::SizeType       InputSizeType;
  typedef typename InputImageType::IndexValueType InputIndexValueType;
  typedef typename InputImageType::PointType      PointType;
  typedef typename InputImageType::RegionType     RegionType;
  typedef typename InputImageType::SizeType       SizeType;

  typedef TInputSpectralImage                     InputSpectralImageType;

  typedef TOutputLabelImage                        OutputLabelImageType;
  typedef typename OutputLabelImageType::PixelType OutputLabelType;

  typedef TOutputLabelImage                     OutputImageType;
  typedef typename OutputImageType::Pointer     OutputImagePointerType;
  typedef typename OutputImageType::PixelType   OutputPixelType;
  typedef typename OutputImageType::RegionType  OutputRegionType;


  /** Setters / Getters */
  itkSetMacro(RangeBandwidth, RealType);
  itkGetMacro(RangeBandwidth, RealType);

  /** Returns the const image of region labels */
  const OutputLabelImageType * GetLabelOutput() const;
  /** Returns the image of region labels */
  OutputLabelImageType * GetLabelOutput();

  void SetInputLabelImage( const InputLabelImageType * labelImage);
  void SetInputSpectralImage( const InputSpectralImageType * spectralImage);
  InputLabelImageType * GetInputLabelImage();
  InputSpectralImageType * GetInputSpectralImage();

protected:

   virtual void BeforeThreadedGenerateData();

    /** LabelImageRegionMergingFilter can be implemented as a multithreaded filter.
      * Therefore, this implementation provides a ThreadedGenerateData()
      * routine which is called for each processing thread. The output
      * image data is allocated automatically by the superclass prior to
      * calling ThreadedGenerateData().  ThreadedGenerateData can only
      * write to the portion of the output image specified by the
      * parameter "outputRegionForThread"
      *
      * \sa ImageToImageFilter::ThreadedGenerateData(),
      *     ImageToImageFilter::GenerateData() */
  void ThreadedGenerateData(const OutputRegionType& outputRegionForThread,
                               int threadId );

  virtual void AfterThreadedGenerateData();

  /** Constructor */
  LabelImageRegionMergingFilter();

  /** Destructor */
  virtual ~LabelImageRegionMergingFilter();

  /** PrintSelf method */
  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

private:
  LabelImageRegionMergingFilter(const Self &);     //purposely not implemented
  void operator =(const Self&);             //purposely not implemented

  /** Range bandwidth */
  RealType        m_RangeBandwidth;

  /** Number of components per pixel in the input image */
  unsigned int m_NumberOfComponentsPerPixel;
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbLabelImageRegionMergingFilter.txx"
#endif

#endif