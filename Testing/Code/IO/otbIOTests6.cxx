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

// this file defines the otbCommonTest for the test driver
// and all it expects is that you have a function called RegisterTests


#include "otbTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(otbGDALImageIOTestCanWrite);
  REGISTER_TEST(otbONERAImageIOTestCanRead);
  REGISTER_TEST(otbImageFileReaderONERATest);
  REGISTER_TEST(otbImageFileReaderONERAComplex);
  REGISTER_TEST(otbImageFileWriterONERAComplex);
  REGISTER_TEST(otbImageFileWriterStreamingONERAComplex);
  REGISTER_TEST(otbMSTARImageIOTestCanRead);
  REGISTER_TEST(otbImageFileReaderMSTAR);
  REGISTER_TEST(otbGDALImageIOTestWriteMetadata);
}
