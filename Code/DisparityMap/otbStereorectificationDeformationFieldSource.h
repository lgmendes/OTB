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
#ifndef __otbStereorectificationDeformationFieldSource_h
#define __otbStereorectificationDeformationFieldSource_h

#include "itkImageSource.h"
#include "otbGenericRSTransform.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkVector.h"

namespace otb
{
/** \class StereorectificationDeformationFieldSource
 *  \brief Compute the deformation fields for stereo-rectification
 *
 *  The geometry of acqusition related to stereo pairs is such that
 *  the displacement related to the elevation between the two images
 *  of the pair always occurs along lines that are called epipolar
 *  lines.
 *
 *  In the case of conic acqusition, these lines are perfectly
 *  parallel by definition, while in push-broom geometry, these lines
 *  might not be exactly parallel due to perturbations during
 *  acquisition, especially when considering a large field of view.
 *
 *  The purpose of stereo-rectification is to warp both images of the
 *  pairs so that the displacement related to the elevation only
 *  occurs in the horizontal direction (i.e. epipolar lines are
 *  horizontal). This operation is useful for mainly two reasons: it
 *  allows to search for disparities in one direction only, and it
 *  allows to derives anaglyph for 3D viewing with 3D glasses.
 *
 *  This filter allows you to compute the deformation fields up to the
 *  sensor model precision needed to warp a pair of stereo images into
 *  epipolar geometry. Warping can be done using the
 *  otb::StreamingWarpImageFilter.
 *
 *  Since lines might not be perfectly regular, the algorithm
 *  performed by this filter uses the otb::GenericRSTransform
 *  capabilities to compute the local epipolar lines, and iteratively
 *  build a resampling grid by propagating along these locally
 *  estimated lines.
 *
 *  Epipolar images will have a null origin and a size as given by the
 *  GetRectifiedImageSize() method. The deformation fields and size
 *  are derived to produce epipolar images covering the whole extent
 *  of the left image.
 *
 *  The SetAverageElevation() method allows you to set the elevation
 *  hypothesis on which the epipolar geometry is built. It means that
 *  any pair of pixels in the stereo pair whose elevation is exactly
 *  equal to the average elevation will have a null disparity (no
 *  displacement). The SetElevationOffset() method allows to tune the
 *  elevation offset which is only used for local epipolar lines
 *  estimation. The default value of 50 meters should do.
 *
 *  Additionnaly, the SetScale() method allows to derive deformation
 *  fields and images size at a coarser (scale > 1) or finer (scale <
 *  1) resolution. The SetGridStep() allows to tune the step of the
 *  resampling grid. Please keep in mind that the whole grid is loaded
 *  into memory, and that the epipolar lines direction may only vary
 *  smoothly. When working with large images, a coarse grid-step will
 *  generally be accurate enough and will preserve the memory ressources.
 *
 *  \sa StreamingWarpImageFilter
 *  \sa StereoSensorModelToElevationMapFilter
 */
template <class TInputImage, class TOutputImage >
class ITK_EXPORT StereorectificationDeformationFieldSource
  : public itk::ImageSource<TOutputImage>
{
public:
  /** Standard class typedefs */
  typedef StereorectificationDeformationFieldSource Self;
  typedef itk::ImageSource<TOutputImage>            Superclass;
  typedef itk::SmartPointer<Self>                   Pointer;
  typedef itk::SmartPointer<const Self>             ConstPointer;

  // Inputs and outputs relative typedefs
  typedef TInputImage                               InputImageType;
  typedef typename InputImageType::Pointer          InputImagePointerType;
  typedef TOutputImage                              OutputImageType;
  typedef typename OutputImageType::Pointer         OutputImagePointerType;

  // Image related typedefs
  typedef typename OutputImageType::SizeType        SizeType;
  typedef typename OutputImageType::PointType       PointType;
  typedef typename OutputImageType::SpacingType     SpacingType;
  typedef typename OutputImageType::RegionType      RegionType;

  // 3D RS transform
  // TODO: Allow to tune precision (i.e. double or float)
  typedef otb::GenericRSTransform<double,3,3>       RSTransformType;
  typedef typename RSTransformType::Pointer         RSTransformPointerType;

  // 3D points
  typedef typename RSTransformType::InputPointType  TDPointType;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( StereorectificationDeformationFieldSource, ImageSource );

  /** Get/Set the average elevation */
  itkSetMacro(AverageElevation,double);
  itkGetConstReferenceMacro(AverageElevation,double);
  
  /** Get/Set the elevation offset */
  itkSetMacro(ElevationOffset,double);
  itkGetConstReferenceMacro(ElevationOffset,double);

  /** Get/Set the scale */
  itkSetMacro(Scale,double);
  itkGetConstReferenceMacro(Scale,double);

  /** Get/Set the grid scale */
  itkSetMacro(GridStep,double);
  itkGetMacro(GridStep,double);

  /** Get/Set left image for stereo-rectification */
  itkSetObjectMacro(LeftImage,InputImageType);
  itkGetObjectMacro(LeftImage,InputImageType);

  /** Get/Set right image for stereo-rectification */
  itkSetObjectMacro(RightImage,InputImageType);
  itkGetObjectMacro(RightImage,InputImageType);

  /** Get the size of the rectified image */
  itkGetConstReferenceMacro(RectifiedImageSize,SizeType);

  /** Get the estimated mean baseline ratio */
  itkGetConstReferenceMacro(MeanBaselineRatio,double);

  /** Return the left deformation field (const version)  */
  const OutputImageType * GetLeftDeformationFieldOutput() const;

  /** Return the left deformation field */
  OutputImageType * GetLeftDeformationFieldOutput();

  /** Return the left deformation field (const version)  */
  const OutputImageType * GetRightDeformationFieldOutput() const;

  /** Return the left deformation field */
  OutputImageType * GetRightDeformationFieldOutput();

protected:
  /** Constructor */
  StereorectificationDeformationFieldSource( void );
  
  /** Destructor */
  ~StereorectificationDeformationFieldSource( void ) {};

  /** Generate output images information */
  virtual void GenerateOutputInformation();

  /** Enlarge output requested region (no streaming) */
  virtual void EnlargeOutputRequestedRegion(itk::DataObject * itkNotUsed(output));

  /** Compute the deformation field */
  virtual void GenerateData();

  /** PrintSelf method */
  virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const;

private:
  StereorectificationDeformationFieldSource( const Self& ); // purposely
                                                            // not
                                                            // implemented
  void operator=( const Self& ); //purposely not implemented

  /** Disparity will be null for this elevation */
  double m_AverageElevation;

  /** This elevation offset is used to compute the epipolar direction */
  double m_ElevationOffset;

  /** A scale greater than 1 will lead to zoomed stereo-rectified
   *  pairs */
  double m_Scale;

  /** Controls the step of the resampling grid (in pixels). A finer
   * step will lead to more memory consumption.
   */
  double m_GridStep;

  /** Left image */
  InputImagePointerType m_LeftImage;

  /** Right image */
  InputImagePointerType m_RightImage;

  /** Left to right transform */
  RSTransformPointerType m_LeftToRightTransform;

  /** Right to left transform */
  RSTransformPointerType m_RightToLeftTransform;

  /** Size of the rectified images */
  SizeType m_RectifiedImageSize;

  /** Output origin in left image (internal use) */
  TDPointType m_OutputOriginInLeftImage;

  /** This variable contains the estimated mean baseline ratio over
   *  the image */
  double m_MeanBaselineRatio;
};

} // End namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbStereorectificationDeformationFieldSource.txx"
#endif

#endif