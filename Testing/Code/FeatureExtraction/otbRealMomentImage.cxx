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

#include <iostream>
#include <iomanip>
#include <fstream>
#include "itkExceptionObject.h"
#include "itkImage.h"

#include "otbImageFileReader.h"
#include "otbRealMomentImageFunction.h"

int otbRealMomentImage(int argc, char * argv[])
{
  const char * inputFilename  = argv[1];
  unsigned int p((unsigned int) ::atoi(argv[2]));
  unsigned int q((unsigned int) ::atoi(argv[3]));
  const char * outputFilename  = argv[4];

  typedef unsigned char InputPixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image<InputPixelType,  Dimension> InputImageType;
  typedef otb::ImageFileReader<InputImageType>   ReaderType;

  typedef otb::RealMomentImageFunction<InputImageType>    FunctionType;
  typedef FunctionType::RealType                          RealType;

  ReaderType::Pointer    reader         = ReaderType::New();
  FunctionType::Pointer  function       = FunctionType::New();

  reader->SetFileName(inputFilename);

  reader->Update();
  function->SetInputImage(reader->GetOutput());

  function->SetQmax(q);
  function->SetPmax(p);

  InputImageType::IndexType index;
  index[0] = 100;
  index[1] = 100;

  RealType Result;

  std::ofstream outputStream(outputFilename);
  outputStream << std::setprecision(10) << "Central Image moments: [10]" << std::endl;
  
  function->SetNeighborhoodRadius(3);
  Result = function->EvaluateAtIndex(index);
  for (unsigned int k=0; k<=p; k++)
    {
    for (unsigned int l=0; l<=q; l++)
      {
      outputStream << "RealMoment c(" << k << l << ") : " << Result.at(k).at(l) << std::endl;
      }
    }
  outputStream.close();

  return EXIT_SUCCESS;
}
