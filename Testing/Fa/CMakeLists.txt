
add_executable(0000307-ExtractROICompareRegion  0000307-ExtractROICompareRegionsImplementations.cxx)
target_link_libraries(0000307-ExtractROICompareRegion OTBIO OTBCommon)

add_executable(0000479-WriteInt8Image 0000479-WriteInt8Image.cxx)
target_link_libraries(0000479-WriteInt8Image OTBIO OTBCommon)

add_executable(AlignementsQB  AlignementsQB.cxx)
target_link_libraries(AlignementsQB OTBFeatureExtraction OTBIO OTBCommon)

add_executable(MapActivation  MapActivation.cxx)
target_link_libraries(MapActivation OTBFeatureExtraction OTBIO OTBCommon)

add_executable(StreamingStat  StreamingStat.cxx)
target_link_libraries(StreamingStat OTBFeatureExtraction OTBIO OTBCommon)

add_executable(0000041-mean_shift  0000041-mean_shift.cxx)
target_link_libraries(0000041-mean_shift OTBIO OTBCommon OTBBasicFilters)

add_executable(00134-feature_extraction  00134-feature_extraction.cxx)
target_link_libraries(00134-feature_extraction OTBIO OTBCommon OTBBasicFilters OTBFeatureExtraction)

add_executable(0000094-PolygonsVectorization 0000094-PolygonsVectorization.cxx)
target_link_libraries(0000094-PolygonsVectorization OTBIO OTBCommon)

if(ITK_USE_FFTWD OR ITK_USE_FFTWF)
add_executable(0000169-fftcomplextocomplex  0000169-fftcomplextocomplex.cxx)
target_link_libraries(0000169-fftcomplextocomplex OTBIO OTBCommon)
endif(ITK_USE_FFTWD OR ITK_USE_FFTWF)

add_executable(000295-MeanShiftVectorImageFilterWithStreamingShrink 000295-MeanShiftVectorImageFilterWithStreamingShrink.cxx)
target_link_libraries(000295-MeanShiftVectorImageFilterWithStreamingShrink OTBIO OTBCommon)

add_executable(SensorModelBorder SensorModelBorder.cxx)
target_link_libraries(SensorModelBorder OTBIO OTBCommon OTBBasicFilters OTBProjections)

add_executable(WriteUnsignedLong WriteUnsignedLong.cxx)
target_link_libraries(WriteUnsignedLong OTBIO OTBCommon)

add_executable(0000209-SVMValidationLinearlySeparableProbEstimation 0000209-SVMValidationLinearlySeparableProbEstimation.cxx)
target_link_libraries(0000209-SVMValidationLinearlySeparableProbEstimation OTBIO OTBLearning)

add_executable(0000428-CastImageFilterStreaming  0000428-CastImageFilterStreaming.cxx)
target_link_libraries(0000428-CastImageFilterStreaming OTBIO OTBCommon OTBBasicFilters)

add_executable(0000433-LineSegmentDetector_8b_16b_compare 0000433-LineSegmentDetector_8b_16b_compare.cxx)
target_link_libraries(0000433-LineSegmentDetector_8b_16b_compare OTBIO OTBFeatureExtraction)

add_executable(otbVectorDataToLabelImageFilterWithoutReader  otbVectorDataToLabelImageFilterWithoutReader.cxx)
target_link_libraries(otbVectorDataToLabelImageFilterWithoutReader OTBBasicFilters OTBIO OTBCommon)

if(BUILD_APPLICATIONS)
  add_executable(0000436-WrapperInputImage_GetImage 0000436-WrapperInputImage_GetImage.cxx)
  target_link_libraries(0000436-WrapperInputImage_GetImage OTBApplicationEngine)
endif()

add_executable(0000437-WriteImageCentOS 0000437-WriteImageCentOS.cxx)
target_link_libraries(0000437-WriteImageCentOS OTBIO OTBCommon)

add_executable(0000495-StreamingImageFileWriterProgressReporting
               0000495-StreamingImageFileWriterProgressReporting.cxx)
target_link_libraries(0000495-StreamingImageFileWriterProgressReporting OTBIO OTBCommon)

set(TEMP ${OTBTesting_BINARY_DIR}/Temporary)

# Always add the Resolved Fa to be compiled and tested
add_subdirectory(Resolved)

# Add the failing bugs
if(BUILD_BUG_TRACKER_TESTS)
  add_subdirectory(Failing)
endif()
