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

// this file defines the otbMultiScaleTest for the test driver
// and all it expects is that you have a function called RegisterTests


#include "otbTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(otbMorphologicalPyramidSegmentationFilterNew);
  REGISTER_TEST(otbMorphologicalPyramidSegmentationFilter);
  REGISTER_TEST(otbGeodesicMorphologyDecompositionImageFilterNew);
  REGISTER_TEST(otbGeodesicMorphologyDecompositionImageFilter);
  REGISTER_TEST(otbGeodesicMorphologyLevelingFilterNew);
  REGISTER_TEST(otbGeodesicMorphologyLevelingFilter);
  REGISTER_TEST(otbConvexOrConcaveClassificationFilterNew);
  REGISTER_TEST(otbConvexOrConcaveClassificationFilter);
  REGISTER_TEST(otbMorphologicalOpeningProfileFilterNew);
  REGISTER_TEST(otbMorphologicalOpeningProfileFilter);
  REGISTER_TEST(otbMorphologicalClosingProfileFilterNew);
  REGISTER_TEST(otbMorphologicalClosingProfileFilter);
}
