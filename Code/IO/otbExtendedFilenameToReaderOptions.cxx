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
#include "otbExtendedFilenameToReaderOptions.h"

namespace otb
{

ExtendedFilenameToReaderOptions
::ExtendedFilenameToReaderOptions() : itk::Object()
{
  m_FilenameHelper = FNameHelperType::New();

  m_Options.simpleFileName.first  = false;
  m_Options.simpleFileName.second = "";

  m_Options.extGEOMFileName.first  = false;
  m_Options.extGEOMFileName.second = "";

  m_Options.subDatasetIndex.first  = false;
  m_Options.subDatasetIndex.second = 0;

  m_Options.resolutionFactor.first  = false;
  m_Options.resolutionFactor.second = 0;

  m_Options.skipCarto.first  = false;
  m_Options.skipCarto.second = false;

  m_Options.nbSetOptions = 0;
  std::cout << "Done" << std::endl;
}

void
ExtendedFilenameToReaderOptions
::SetExtendedFileName(const char *extFname)
{
  this->m_FilenameHelper->SetExtendedFileName(extFname);
  MapType map = this->m_FilenameHelper->GetOptionMap();
  unsigned int nbOpts = map.size();

  m_Options.simpleFileName.first  = true;
  m_Options.simpleFileName.second = this->m_FilenameHelper->GetSimpleFileName();

  if (!map["geom"].empty())
    {
    m_Options.extGEOMFileName.first  = true;
    m_Options.extGEOMFileName.second = map["geom"];
    m_Options.nbSetOptions ++;
    }
  if (!map["sdataidx"].empty())
    {
    m_Options.subDatasetIndex.first  = true;
    m_Options.subDatasetIndex.second = atoi(map["sdataidx"].c_str());
    m_Options.nbSetOptions ++;
    }
  if (!map["resol"].empty())
    {
    m_Options.resolutionFactor.first  = true;
    m_Options.resolutionFactor.second = atoi(map["resol"].c_str());
    m_Options.nbSetOptions ++;
    }

  if (!map["skipcarto"].empty())
    {
    m_Options.skipCarto.first = true;
    m_Options.nbSetOptions ++;

    if (   map["skipcarto"] == "On"
        || map["skipcarto"] == "on"
        || map["skipcarto"] == "True"
        || map["skipcarto"] == "true"
        || map["skipcarto"] == "True"
        || map["skipcarto"] == "1"   )
      {
      m_Options.skipCarto.second = true;
      }
    }

  if (m_Options.nbSetOptions < nbOpts)
    {
    itkWarningMacro("Some unknown reader options have been detected")
    }
}

bool
ExtendedFilenameToReaderOptions
::SimpleFileNameIsSet () const
{
  return m_Options.simpleFileName.first;
}
const char*
ExtendedFilenameToReaderOptions
::GetSimpleFileName () const
{
  return m_Options.simpleFileName.second.c_str();
}

bool
ExtendedFilenameToReaderOptions
::ExtGEOMFileNameIsSet () const
{
  return m_Options.extGEOMFileName.first;
}
const char*
ExtendedFilenameToReaderOptions
::GetExtGEOMFileName () const
{
  return m_Options.extGEOMFileName.second.c_str();
}

bool
ExtendedFilenameToReaderOptions
::SubDatasetIndexIsSet () const
{
  return m_Options.subDatasetIndex.first;
}
unsigned int
ExtendedFilenameToReaderOptions
::GetSubDatasetIndex () const
{
  return m_Options.subDatasetIndex.second;
}

bool
ExtendedFilenameToReaderOptions
::ResolutionFactorIsSet () const
{
  return m_Options.resolutionFactor.first;
}
unsigned int
ExtendedFilenameToReaderOptions
::GetResolutionFactor () const
{
  return m_Options.resolutionFactor.second;
}

bool
ExtendedFilenameToReaderOptions
::SkipCartoIsSet () const
{
  return m_Options.skipCarto.first;
}
bool
ExtendedFilenameToReaderOptions
::GetSkipCarto () const
{
  return m_Options.skipCarto.second;
}

} // end namespace otb
