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


//
#include "otbTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(otbFuzzyVariableDSApplied);
  REGISTER_TEST(otbMassOfBeliefDSApplied);
  REGISTER_TEST(otbVectorDataToDSValidatedVectorDataFilterNew);
  REGISTER_TEST(otbVectorDataToDSValidatedVectorDataFilter);
  REGISTER_TEST(otbVectorDataToSpecificDescriptionFilterBaseNew);
  REGISTER_TEST(otbVectorDataToRoadDescriptionFilterNew);
  REGISTER_TEST(otbVectorDataToRoadDescriptionFilter);
  REGISTER_TEST(otbFuzzyDescriptorsModelManagerNew);
  REGISTER_TEST(otbFuzzyDescriptorsModelManagerTest);
  REGISTER_TEST(otbStandardDSCostFunctionNew);
}
