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
#ifndef __otbMapProjectionWrapper_h
#define __otbMapProjectionWrapper_h

#include <string>
#include <map>

#include "itkObject.h"
#include "itkObjectFactory.h"

class ossimProjection;

namespace otb
{

/**
 * \class MapProjectionWrapper
 * \brief Wrapper class to group all dependencies to ossim for map projection
 *
 * This class is NOT intented to be used outside of OTB. Use the
 * GenericMapProjection. If you feel that you need to use it directly,
 * think again!
 *
 * \sa GenericMapProjection
 * \ingroup Projection
 *
 **/

class MapProjectionWrapper: public itk::Object
{
public:
  /** Standard class typedefs. */
  typedef MapProjectionWrapper          Self;
  typedef itk::Object                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef ossimProjection*       InternalMapProjectionPointer;
  typedef const ossimProjection* InternalMapProjectionConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MapProjectionWrapper, itk::Object);

  InternalMapProjectionPointer GetMapProjection();
  InternalMapProjectionConstPointer GetMapProjection() const;

  std::string GetWkt() const;
  void SetWkt(std::string projectionRefWkt);

  void SetParameter(std::string key, std::string value);
  std::string GetParameter(std::string key) const;

  bool InstanciateProjection();

  void InverseTransform(double x, double y, double z,
                        double& lon, double& lat, double& h);
  void ForwardTransform(double lon, double lat, double h,
                        double& x, double& y, double& z);

  void PrintMap() const;

protected:
  MapProjectionWrapper();
  virtual ~MapProjectionWrapper();

private:
  MapProjectionWrapper(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  void ApplyParametersToProjection();

  InternalMapProjectionPointer m_MapProjection;
  std::string                  m_ProjectionRefWkt;

  // Hold the parameters specified directly from the user of the class
  // Consistency is done from ParameterStore -> MapProjection
  // But NOT MapProjection -> ParameterStore
  // so DO NOT use that to read the projection parameters
  typedef std::map<std::string, std::string> StoreType;
  StoreType m_ParameterStore;

  bool m_ReinstanciateProjection;
};

// Some usefull free functions related to ossim
namespace Utils
{
int GetZoneFromGeoPoint(double lon, double lat);
}


} // namespace otb

#endif
