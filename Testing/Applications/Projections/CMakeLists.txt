
if(OTB_DATA_USE_LARGEINPUT)

OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_UTM
                     APP  OrthoRectification
                     OPTIONS -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                 			 -io.out ${TEMP}/apTvPrOrthorectifTest_UTM.tif
                 			 -elev.dem ${INPUTDATA}/DEM/srtm_directory/
                 		     -outputs.ulx  374100.8
                 			 -outputs.uly  4829184.8
                 			 -outputs.sizex 500
                 			 -outputs.sizey 500
                 			 -outputs.spacingx  0.5
                 			 -outputs.spacingy  -0.5
                 			 -map utm
                 			 -opt.gridspacing 4 # Spacing of the displacement field equal to 4 meters
                       -interpolator linear
                     VALID   --compare-image ${EPSILON_4}
                              ${BASELINE}/owTvOrthorectifTest_UTM.tif
                 			  ${TEMP}/apTvPrOrthorectifTest_UTM.tif)


OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_UTM_OutXML1
                     APP  OrthoRectification
                     OPTIONS -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                 			 -io.out ${TEMP}/apTvPrOrthorectifTest_UTM_OutXML1.tif
                 			 -elev.dem ${INPUTDATA}/DEM/srtm_directory/
                 		     -outputs.ulx  374100.8
                 			 -outputs.uly  4829184.8
                 			 -outputs.sizex 500
                 			 -outputs.sizey 500
                 			 -outputs.spacingx  0.5
                 			 -outputs.spacingy  -0.5
                 			 -map utm
                 			 -opt.gridspacing 4 # Spacing of the deformation field equal to 4 meters
                       -outxml  ${TEMP}/apTvPrOrthorectifTest_UTM_OutXML1.xml
                       -interpolator linear
                     VALID   --compare-image ${EPSILON_4}
                              ${BASELINE}/owTvOrthorectifTest_UTM.tif
                 			  ${TEMP}/apTvPrOrthorectifTest_UTM_OutXML1.tif)


OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_UTM_InXML1
                     APP  OrthoRectification
                     OPTIONS
                       -inxml  ${INPUTDATA}/apTvPrOrthorectifTest_UTM_OutXML1.xml
                 			 -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                 			 -io.out ${TEMP}/apTvPrOrthorectifTest_UTM_InXML1.tif
                 			 -elev.dem ${INPUTDATA}/DEM/srtm_directory/
                        VALID   --compare-image ${EPSILON_4}
                              ${BASELINE}/owTvOrthorectifTest_UTM.tif
                 			  ${TEMP}/apTvPrOrthorectifTest_UTM_InXML1.tif)


OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_DEMTIF_UTM
                     APP  OrthoRectification
                     OPTIONS -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                       -io.out ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM.tif
                       -elev.dem ${INPUTDATA}/DEM/tif_directory/
                       -outputs.ulx  374100.8
                       -outputs.uly  4829184.8
                       -outputs.sizex 500
                       -outputs.sizey 500
                       -outputs.spacingx  0.5
                       -outputs.spacingy  -0.5
                       -map utm
                       -opt.gridspacing 4 # Spacing of the deformation field equal to 4 meters
                       -interpolator linear
                     VALID   --compare-image ${EPSILON_4}
                              ${BASELINE}/owTvOrthorectifTest_UTM.tif
                        ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM.tif)


OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_DEMTIF_UTM_OutXML1
                     APP  OrthoRectification
                     OPTIONS -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                       -io.out ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM_OutXML1.tif
                       -elev.dem ${INPUTDATA}/DEM/tif_directory/
                       -outputs.ulx  374100.8
                       -outputs.uly  4829184.8
                       -outputs.sizex 500
                       -outputs.sizey 500
                       -outputs.spacingx  0.5
                       -outputs.spacingy  -0.5
                       -map utm
                       -opt.gridspacing 4 # Spacing of the deformation field equal to 4 meters
                       -outxml  ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM_OutXML1.xml
                       -interpolator linear
                     VALID   --compare-image ${EPSILON_4}
                              ${BASELINE}/owTvOrthorectifTest_UTM.tif
                        ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM_OutXML1.tif)


OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_DEMTIF_UTM_InXML1
                     APP  OrthoRectification
                     OPTIONS
                       -inxml  ${INPUTDATA}/apTvPrOrthorectifTest_DEMTIF_UTM_OutXML1.xml
                       -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                       -io.out ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM_InXML1.tif
                       -elev.dem ${INPUTDATA}/DEM/tif_directory/
                        VALID   --compare-image ${EPSILON_4}
                              ${BASELINE}/owTvOrthorectifTest_UTM.tif
                        ${TEMP}/apTvPrOrthorectifTest_DEMTIF_UTM_InXML1.tif)


OTB_TEST_APPLICATION(NAME  apTvPrOrthorectification_WGS84
                     APP  OrthoRectification
                     OPTIONS -io.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                       -io.out ${TEMP}/apTvPrOrthorectifTest_WGS84.tif
                       -elev.dem ${INPUTDATA}/DEM/srtm_directory/
                       -outputs.ulx  1.35404
                       -outputs.uly  43.65414
                       -outputs.sizex 500
                       -outputs.sizey 500
                       -outputs.spacingx  0.00000621314
                       -outputs.spacingy  -0.00000621314
                       -map wgs
                       -opt.gridspacing 0.00001242628 # Spacing of the deformation field equal to |2*outputs.spacingx| degrees
                       -interpolator linear
                     VALID   --compare-image ${EPSILON_4}
                        ${BASELINE}/owTvOrthorectifTest_WGS84.tif
                        ${TEMP}/apTvPrOrthorectifTest_WGS84.tif
                     )


endif()

OTB_TEST_APPLICATION(NAME apTvPrRigidTransformResample
                     APP  RigidTransformResample
                     OPTIONS -in ${INPUTDATA}/poupees.tif
                 			       -out ${TEMP}/apTvPrRigidTransformResampleTest.tif
                             -transform.type translation
                             -transform.type.translation.tx -5
                             -transform.type.translation.ty 5
                             -interpolator nn
                     VALID   --compare-image ${NOTOL}
                              ${BASELINE}/owTvRigidTransformResampleTest.tif
                			  ${TEMP}/apTvPrRigidTransformResampleTest.tif)


OTB_TEST_APPLICATION(NAME  apTvPrConvertCartoToGeoPoint
                     APP  ConvertCartoToGeoPoint
                     OPTIONS -carto.x 374100.828
                             -carto.y 4829184.806
                 	           -mapproj utm
                 	           -mapproj.utm.northhem true
                 	           -mapproj.utm.zone 31
                     TESTENVOPTIONS ${TEMP}/apTvPrConvertCartoToGeoPoint.txt
                     VALID   --compare-ascii ${EPSILON_7}
                             ${BASELINE_FILES}/apTvPrConvertCartoToGeoPoint.txt
                	     ${TEMP}/apTvPrConvertCartoToGeoPoint.txt)

OTB_TEST_APPLICATION(NAME apTvPrImageEnvelopeTest
                     APP ImageEnvelope
                     OPTIONS -in ${EXAMPLEDATA}/sensor_stereo_left.tif
                             -out ${TEMP}/apTvPrImageEnvelopeTest.shp
                     VALID   --compare-ogr ${NOTOL}
                        ${BASELINE_FILES}/apTvPrImageEnvelopeTest.shp
                        ${TEMP}/apTvPrImageEnvelopeTest.shp)

OTB_TEST_APPLICATION(NAME apTvPrObtainUTMZoneFromGeoPoint
                     APP ObtainUTMZoneFromGeoPoint
                     OPTIONS -lat 10.0
                             -lon 124.0
                     TESTENVOPTIONS ${TEMP}/apTvPrObtainUTMZoneFromGeoPoint.txt
                     VALID  --compare-ascii ${EPSILON_7}
                        ${BASELINE_FILES}/apTvPrObtainUTMZoneFromGeoPoint.txt
                        ${TEMP}/apTvPrObtainUTMZoneFromGeoPoint.txt)

OTB_TEST_APPLICATION(NAME apTvPrConvertSensorToGeoPoint
                     APP ConvertSensorToGeoPoint
                     OPTIONS -in  ${INPUTDATA}/QB_TOULOUSE_MUL_Extract_500_500.tif
                             -input.idx 500
                             -input.idy 500
                     TESTENVOPTIONS ${TEMP}/apTvPrConvertSensorToGeoPoint.txt
                     VALID  --compare-ascii ${EPSILON_7}
                        ${BASELINE_FILES}/apTvPrConvertSensorToGeoPoint.txt
                        ${TEMP}/apTvPrConvertSensorToGeoPoint.txt)

OTB_TEST_APPLICATION(NAME apTvPrBundleToPerfectSensor
                     APP BundleToPerfectSensor
                     OPTIONS -inp  ${INPUTDATA}/QB_Toulouse_Ortho_PAN.tif
                             -inxs ${INPUTDATA}/QB_Toulouse_Ortho_XS_ROI_170x230.tif
                             -elev.dem ${INPUTDATA}/DEM/srtm_directory
                             -out ${TEMP}/apTvPrBundleToPerfectSensor.tif int16
                     VALID  --compare-image ${EPSILON_7}
                        ${BASELINE}/apTvPrBundleToPerfectSensor.tif
                        ${TEMP}/apTvPrBundleToPerfectSensor.tif)

OTB_TEST_APPLICATION(NAME apTvPrSuperimpose
                     APP Superimpose
                     OPTIONS -inr  ${INPUTDATA}/QB_Toulouse_Ortho_PAN.tif
                             -inm ${INPUTDATA}/QB_Toulouse_Ortho_XS_ROI_170x230.tif
                             -elev.dem ${INPUTDATA}/DEM/srtm_directory
                             -out ${TEMP}/apTvPrSuperimpose.tif int16
                     VALID  --compare-image ${EPSILON_7}
                        ${BASELINE}/apTvPrSuperimpose.tif
                        ${TEMP}/apTvPrSuperimpose.tif)


OTB_TEST_APPLICATION(NAME  apTvPrVectorDataReprojectionFromMapToImage
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${INPUTDATA}/ToulousePoints-examples.shp
                 			       -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromMapToImage.shp
                             -out.proj image
                             -out.proj.image.in  ${INPUTDATA}/QB_Toulouse_Ortho_XS.tif
                     VALID   --compare-ogr ${NOTOL}
                              ${BASELINE_FILES}/prTvVectorDataProjectionFilterFromMapToImage.shp
                 			  ${TEMP}/apTvPrVectorDataReprojectionFromMapToImage.shp)

# With QGIS the two vectordata are equal
# TODO : add validation
OTB_TEST_APPLICATION(NAME  apTuPrVectorDataReprojectionFromImageToMap
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${INPUTDATA}/ToulousePointsUTM31N.shp
                     		     -in.kwl ${INPUTDATA}/QB_Toulouse_Ortho_XS.tif
                 			       -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromImageToMap.shp
                             -out.proj user
                             -out.proj.user.map utm
                             -out.proj.user.map.utm.northhem true
                 	           -out.proj.user.map.utm.zone 31)

OTB_TEST_APPLICATION(NAME  apTvPrVectorDataReprojectionFromMapToGeo
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${INPUTDATA}/ToulousePoints-examples.shp
                 			       -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromMapToGeo.kml
                             -out.proj user
                             -out.proj.user.map  wgs
                     VALID   --compare-ogr ${NOTOL}
                              ${BASELINE_FILES}/prTvVectorDataProjectionFilterFromMapToGeo.kml
                 			  ${TEMP}/apTvPrVectorDataReprojectionFromMapToGeo.kml)

OTB_TEST_APPLICATION(NAME  apTvPrVectorDataReprojectionFromMapToMap
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${INPUTDATA}/ToulousePoints-examples.shp
                 			       -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromMapToMap.sqlite
                             -out.proj user
                             -out.proj.user.map  lambert93
                     VALID   --compare-ogr ${NOTOL}
                              ${BASELINE_FILES}/prTvVectorDataProjectionFilterFromMapToMap.sqlite
                 			  ${TEMP}/apTvPrVectorDataReprojectionFromMapToMap.sqlite)

OTB_TEST_APPLICATION(NAME  apTvPrVectorDataReprojectionFromMapToMap2
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${BASELINE_FILES}/prTvVectorDataProjectionFilterFromMapToMap.sqlite
                 			       -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromMapToMap2.sqlite
                             -out.proj user
                             -out.proj.user.map  utm
                             -out.proj.user.map.utm.northhem true
                 	           -out.proj.user.map.utm.zone 31
                     VALID   --compare-ogr ${NOTOL}
                              ${BASELINE_FILES}/apTvPrVectorDataReprojectionFromMapToMap2.sqlite
                 			  ${TEMP}/apTvPrVectorDataReprojectionFromMapToMap2.sqlite)

if(OTB_DATA_USE_LARGEINPUT)
OTB_TEST_APPLICATION(NAME  apTvPrVectorDataReprojectionFromMapToSensor
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${INPUTDATA}/ToulousePoints-examples.shp
                 			 -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromMapToSensor.shp
                             -out.proj image
                             -out.proj.image.in ${OTB_DATA_LARGEINPUT_ROOT}/QUICKBIRD/TOULOUSE/000000128955_01_P001_PAN/02APR01105228-P1BS-000000128955_01_P001.TIF
                     VALID   --compare-ogr ${NOTOL}
                              ${BASELINE_FILES}/prTvVectorDataProjectionFilterFromMapToSensor.shp
                 			  ${TEMP}/apTvPrVectorDataReprojectionFromMapToSensor.shp)
endif()


# With QGIS the two vectordata are equal
# TODO : add validation
OTB_TEST_APPLICATION(NAME  apTuPrVectorDataReprojectionFromGeoToMap
                     APP  VectorDataReprojection
                     OPTIONS -in.vd  ${INPUTDATA}/ToulousePointsWGS.sqlite
                 			 -out.vd ${TEMP}/apTvPrVectorDataReprojectionFromGeoToMap.shp
                             -out.proj image
                             -out.proj.image.in ${INPUTDATA}/QB_Toulouse_Ortho_PAN.tif)

OTB_TEST_APPLICATION(NAME  apTvPrRefineSensorModel
                     APP  RefineSensorModel
                     OPTIONS -ingeom    ${INPUTDATA}/QB_TOULOUSE_MUL_Extract_500_500.geom
                             -inpoints  ${INPUTDATA}/QB_TOULOUSE_MUL_Extract_500_500_in_tie_points.txt
                 	     -outgeom   ${TEMP}/apTvPrRefineSensorModelGeomOutput.geom
                             -outstat   ${TEMP}/apTvPrRefineSensorModelStatsOutput.txt
                             -outvector ${TEMP}/apTvPrRefineSensorModelVectorOutput.shp
                             -map utm -map.utm.zone 31 -map.utm.northhem 1
                             -elev.dem ${INPUTDATA}/DEM/srtm_directory
                             -elev.geoid ${INPUTDATA}/DEM/egm96.grd
                     VALID   --compare-ascii 0.1
                             ${BASELINE_FILES}/apTvPrRefineSensorModelGeomOutput.geom
                             ${TEMP}/apTvPrRefineSensorModelGeomOutput.geom)

OTB_TEST_APPLICATION(NAME  apTvPrGenerateRPCSensorModel
                     APP  GenerateRPCSensorModel
                     OPTIONS -inpoints  ${INPUTDATA}/QB_TOULOUSE_MUL_Extract_500_500_in_tie_points.txt
                 	     -outgeom   ${TEMP}/apTvPrGenerateRPCSensorModelGeomOutput.geom
                             -outstat   ${TEMP}/apTvPrGenerateRPCSensorModelStatsOutput.txt
                             -outvector ${TEMP}/apTvPrGenerateRPCSensorModelVectorOutput.shp
                             -map utm -map.utm.zone 31 -map.utm.northhem 1
                             -elev.dem ${INPUTDATA}/DEM/srtm_directory
                             -elev.geoid ${INPUTDATA}/DEM/egm96.grd
                     VALID   --compare-ascii ${EPSILON_3}
                             ${BASELINE_FILES}/apTvPrGenerateRPCSensorModelGeomOutput.geom
                             ${TEMP}/apTvPrGenerateRPCSensorModelGeomOutput.geom)

