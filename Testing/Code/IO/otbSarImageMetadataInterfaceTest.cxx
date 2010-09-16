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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkExceptionObject.h"

#include <fstream>
#include <iostream>
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbSarImageMetadataInterface.h"
#include "otbSarImageMetadataInterfaceFactory.h"

int otbSarImageMetadataInterfaceTest(int argc, char* argv[])
{
  // Verify the number of parameters in the command line
  const char * inputFilename  = argv[1];
  const char * outputFilename  = argv[2];

  typedef otb::VectorImage<double,  2>         InputImageType;
  typedef otb::ImageFileReader<InputImageType> ImageReaderType;

  ImageReaderType::Pointer reader = ImageReaderType::New();
  reader->SetFileName(inputFilename);
  reader->UpdateOutputInformation();

  otb::SarImageMetadataInterface::Pointer lImageMetadata = otb::SarImageMetadataInterfaceFactory::CreateIMI(reader->GetOutput()->GetMetaDataDictionary());


  std::ofstream file;
  file.open(outputFilename);
  file << "GetRadiometricCalibrationScale                      : " << lImageMetadata->GetRadiometricCalibrationScale() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationNoise() : " << lImageMetadata->GetRadiometricCalibrationNoise()->GetNumberOfPoints() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationAntennaPatternNewGain:                 "
       << lImageMetadata->GetRadiometricCalibrationAntennaPatternNewGain()->GetNumberOfPoints() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationAntennaPatternOldGain:                 "
       << lImageMetadata->GetRadiometricCalibrationAntennaPatternOldGain()->GetNumberOfPoints() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationIncidenceAngle:                        "
       << lImageMetadata->GetRadiometricCalibrationIncidenceAngle()->GetNumberOfPoints() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationRangeSpreadLoss:                       "
       << lImageMetadata->GetRadiometricCalibrationRangeSpreadLoss()->GetNumberOfPoints() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationNoisePolynomialDegree:                 "
       << lImageMetadata->GetRadiometricCalibrationNoisePolynomialDegree() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationAntennaPatternNewGainPolynomialDegree: "
       << lImageMetadata->GetRadiometricCalibrationAntennaPatternNewGainPolynomialDegree() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationAntennaPatternOldGainPolynomialDegree: "
       << lImageMetadata->GetRadiometricCalibrationAntennaPatternOldGainPolynomialDegree() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationIncidenceAnglePolynomialDegree:        "
       << lImageMetadata->GetRadiometricCalibrationIncidenceAnglePolynomialDegree() << std::endl;
  file << "NumberOfPoints for GetRadiometricCalibrationRangeSpreadLossPolynomialDegree:       "
       << lImageMetadata->GetRadiometricCalibrationRangeSpreadLossPolynomialDegree() << std::endl;
  file.close();

  std::cout << lImageMetadata << std::endl;

  return EXIT_SUCCESS;

}
