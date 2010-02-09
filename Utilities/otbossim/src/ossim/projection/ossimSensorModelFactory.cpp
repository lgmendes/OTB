//*****************************************************************************
// FILE: ossimSensorModelFactory.cc
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// AUTHOR:  Oscar Kramer
//
// DESCRIPTION:
//   Contains implementation of class ossimSensorModelFactory
//
//*****************************************************************************
//  $Id: ossimSensorModelFactory.cpp 15766 2009-10-20 12:37:09Z gpotts $
#include <fstream>
#include <algorithm>
#include <ossim/projection/ossimSensorModelFactory.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimDirectory.h>
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimNotifyContext.h>

//***
// Define Trace flags for use within this file:
//***
#include <ossim/base/ossimTrace.h>
static ossimTrace traceExec  = ossimTrace("ossimSensorModelFactory:exec");
static ossimTrace traceDebug = ossimTrace("ossimSensorModelFactory:debug");

//***
// Note to programmer: To add a new model, search this file for "ADD_MODEL"
// to locate places requiring editing. Functional example below...
//
// ADD_MODEL: Include all sensor model headers here:
//***
#include <ossim/projection/ossimCoarseGridModel.h>
#include <ossim/projection/ossimRpcModel.h>
#include <ossim/projection/ossimRpcProjection.h>
#include <ossim/projection/ossimIkonosRpcModel.h>
#include <ossim/projection/ossimNitfRpcModel.h>
#include <ossim/projection/ossimQuickbirdRpcModel.h>
#include <ossim/projection/ossimLandSatModel.h>
#include <ossim/projection/ossimSpot5Model.h>
#include <ossim/projection/ossimSarModel.h>
#include <ossim/support_data/ossimSpotDimapSupportData.h>
#include <ossim/projection/ossimNitfMapModel.h>
#include <ossim/projection/ossimFcsiModel.h>
#include <ossim/projection/ossimApplanixUtmModel.h>
#include <ossim/projection/ossimApplanixEcefModel.h>
#include <ossim/support_data/ossimFfL7.h>
#include <ossim/support_data/ossimFfL5.h>
//#include <ossim/projection/ossimRadarSatModel.h>
//#include <ossim/projection/ossimEnvisatAsarModel.h>
// #include <ossim/projection/ossimTerraSarModel.h>
//#include <ossim/projection/ossimCosmoSkymedModel.h>
// #include <ossim/projection/ossimRadarSat2Model.h>
// #include <ossim/projection/ossimErsSarModel.h>
#include <ossim/projection/ossimTileMapModel.h>

//***
// ADD_MODEL: List names of all sensor models produced by this factory:
//***
//const char* MY_NEW_MODEL = "myNewModel";
// const char* OCG_MODEL        = "ossimCoarseGridModel";
// const char* RPC_MODEL        = "ossimRpcModel";
// const char* IKONOS_RPC_MODEL = "ossimIkonosRpcModel";
// const char* NITF_RPC_MODEL   = "ossimNitfRpcModel";
// const char* LANDSAT_MODEL    = "ossimLandSatModel";
// const char* NITF_MAP_MODEL   = "ossimNitfMapModel";
// const char* FCSI_MODEL       = "ossimFcsiModel";
// const char* EMERGE_FCSI_MODEL= "ossimEmergeFcsiModel";

ossimSensorModelFactory* ossimSensorModelFactory::theInstance = 0;

//*****************************************************************************
//  STATIC METHOD: ossimSensorModelFactory::instance()
//  
//*****************************************************************************
ossimSensorModelFactory*  ossimSensorModelFactory::instance()
{
   if(!theInstance)
   {
      theInstance = new ossimSensorModelFactory;
   }

   return (ossimSensorModelFactory*) theInstance;
}

//*****************************************************************************
//  METHOD: ossimSensorModelFactory::create(kwl, prefix)
//*****************************************************************************
ossimProjection* ossimSensorModelFactory::createProjection(const ossimKeywordlist &keywordList,
                                                           const char *prefix) const
{
   ossimRefPtr<ossimProjection> result;

   //
   // Permit specification of geometry file name in lieu of type:
   //
   const char*  value = keywordList.find(prefix, ossimKeywordNames::GEOM_FILE_KW);
   if (value)
   {
      result = createProjection(ossimFilename(value), 0);
   }
   //
   // Search for occurence of "type" keyword:
   //
   else
   {
      value = keywordList.find(prefix, ossimKeywordNames::TYPE_KW);
      if(value)
      {
         result = createProjection(ossimString(value));
         if(result.valid())
         {
            if(!result->loadState(keywordList, prefix))
            {
               result = 0;
            }
        }
      }
   }
   
   return result.release();
}

//*****************************************************************************
//  METHOD: 
//  
//*****************************************************************************
ossimProjection*
ossimSensorModelFactory::createProjection(const ossimString &name) const
{
   //***
   // Name should represent the model type:
   //***
   if(name == STATIC_TYPE_NAME(ossimCoarseGridModel))
   {
      return new ossimCoarseGridModel;
   }

   if (name ==  STATIC_TYPE_NAME(ossimRpcModel))
   {
      return new ossimRpcModel;
   }

   if(name == STATIC_TYPE_NAME(ossimLandSatModel))
   {
      return new ossimLandSatModel;
   }

   if(name == STATIC_TYPE_NAME(ossimNitfMapModel))
   {
      return new ossimNitfMapModel;
   }

   if(name == STATIC_TYPE_NAME(ossimQuickbirdRpcModel))
   {
      return new ossimQuickbirdRpcModel;
   }
   
   if(name == STATIC_TYPE_NAME(ossimIkonosRpcModel))
   {
     return new ossimIkonosRpcModel;
   }

   if(name == STATIC_TYPE_NAME(ossimNitfRpcModel))
   {
      return new ossimNitfRpcModel;
   }
   if(name == STATIC_TYPE_NAME(ossimRpcProjection))
   {
      return new ossimRpcProjection;
   }
   if(name == STATIC_TYPE_NAME(ossimFcsiModel))
   {
      return new ossimFcsiModel;
   }
   if(name == STATIC_TYPE_NAME(ossimApplanixUtmModel))
   {
      return new ossimApplanixUtmModel;
   }
   if(name == STATIC_TYPE_NAME(ossimApplanixEcefModel))
   {
      return new ossimApplanixEcefModel;
   }

   if(name == STATIC_TYPE_NAME(ossimSpot5Model))
   {
      return new ossimSpot5Model;
   }

   if(name==STATIC_TYPE_NAME(ossimTileMapModel))
    {
      return new ossimTileMapModel;
    }
   if(name == STATIC_TYPE_NAME(ossimSarModel))
   {
      return new ossimSarModel;
   }
//   if (name == STATIC_TYPE_NAME(ossimRadarSatModel))
//   {
//	   return new ossimRadarSatModel;
//   }
//   if (name == STATIC_TYPE_NAME(ossimEnvisatAsarModel))
//   {
//	   return new ossimEnvisatAsarModel;
//   }
// 	if (name == STATIC_TYPE_NAME(ossimTerraSarModel))
//    {
// 	   return new ossimTerraSarModel;
//    }
// 	if (name == STATIC_TYPE_NAME(ossimCosmoSkymedModel))
//    {
// 	   return new ossimCosmoSkymedModel;
//   }
// 	if (name == STATIC_TYPE_NAME(ossimRadarSat2Model))
//    {
// 	   return new ossimRadarSat2Model;
//    }
//    if (name == STATIC_TYPE_NAME(ossimErsSarModel))
//    {
// 	   return new ossimErsSarModel;
//    }
   //***
   // ADD_MODEL: (Please leave this comment for the next programmer)
   //***
//   if(name == MY_NEW_MODEL)
//      return new myNewModel;

   return NULL;
}

//*****************************************************************************
//  METHOD
//*****************************************************************************
ossimObject*
ossimSensorModelFactory::createObject(const ossimString& typeName)const
{
   return createProjection(typeName);
}

//*****************************************************************************
//  METHOD
//*****************************************************************************
ossimObject*
ossimSensorModelFactory::createObject(const ossimKeywordlist& kwl,
                                      const char* prefix)const
{
   return createProjection(kwl, prefix);
}
   
//*****************************************************************************
//  METHOD
//*****************************************************************************
void
ossimSensorModelFactory::getTypeNameList(std::vector<ossimString>& typeList)
   const
{
   typeList.push_back(STATIC_TYPE_NAME(ossimApplanixEcefModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimApplanixUtmModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimCoarseGridModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimRpcModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimIkonosRpcModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimQuickbirdRpcModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimNitfRpcModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimLandSatModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimNitfMapModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimFcsiModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimSpot5Model));
   typeList.push_back(STATIC_TYPE_NAME(ossimSarModel));
//   typeList.push_back(STATIC_TYPE_NAME(ossimRadarSatModel));
//    typeList.push_back(STATIC_TYPE_NAME(ossimRadarSat2Model));
//    typeList.push_back(STATIC_TYPE_NAME(ossimTerraSarModel));
   //   typeList.push_back(STATIC_TYPE_NAME(ossimCosmoSkymedModel));
//   typeList.push_back(STATIC_TYPE_NAME(ossimEnvisatAsarModel));
//    typeList.push_back(STATIC_TYPE_NAME(ossimErsSarModel));
   typeList.push_back(STATIC_TYPE_NAME(ossimTileMapModel));
   //***
   // ADD_MODEL: Please leave this comment for the next programmer. Add above.
   //***
   //typeList.push_back(ossimString(MY_NEW_MODEL));
   
}

ossimProjection* ossimSensorModelFactory::createProjection(const ossimFilename& filename,
                                                           ossim_uint32  entryIdx) const
{
   ossimKeywordlist kwl;
   ossimRefPtr<ossimProjection> model = 0;

   ossimFilename geomFile = filename;
   geomFile = geomFile.setExtension("geom");
   
   if(geomFile.exists()&&
      kwl.addFile(filename.c_str()))
   {
      ossimFilename coarseGrid;
      
      const char* type = kwl.find(ossimKeywordNames::TYPE_KW);
      if(type)
      {
         if(ossimString(type) == ossimString(STATIC_TYPE_NAME(ossimCoarseGridModel)))
         {
            findCoarseGrid(coarseGrid,
                           filename);
            
            if(coarseGrid.exists() &&(coarseGrid != ""))
            {
               kwl.add("grid_file_name",
                       coarseGrid.c_str(),
                       true);
               model = new ossimCoarseGridModel(kwl);
               if(!model->getErrorStatus())
               {
                  return model.release();
               }
            }
         }
      }
      kwl.clear();
   }

   // See if there is an external geomtry.
   ossimRefPtr<ossimProjection> proj = createProjectionFromGeometryFile(filename,
                                                            entryIdx);
   if (proj.valid())
   {
      return proj.release();
   }

   if(model.valid())
   {
      model = 0;
   }
   // first check for override
   //
   if(geomFile.exists()&&kwl.addFile(geomFile.c_str()))
   {
      model =  createProjection(kwl);
   }
   if(model.valid())
   {
      return model.release();
   }

   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << "DEBUG ossimSensorModelFactory::createProjection: Testing ossimCoarsGridModel" << std::endl;
   }
   
   ifstream input(geomFile.c_str());
   char ecgTest[4];
   input.read((char*)ecgTest, 3);
   ecgTest[3] = '\0';
   input.close();
   if(ossimString(ecgTest) == "eCG")
   {
      ossimKeywordlist kwlTemp;
      kwlTemp.add("type",
                  "ossimCoarseGridModel",
                  true);
      kwlTemp.add("geom_file",
                  geomFile.c_str(),
                  true);
      return createProjection(kwlTemp);
   }
   
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << "DEBUG ossimSensorModelFactory::createProjection: testing ossimRpcModel" << std::endl;
   }

   //---
   // Test for quick bird rpc.  Could be either a tiff or nitf so not wrapped
   // around "isNitf()" anymore.
   //---
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "DEBUG ossimSensorModelFactory::createProjection: "
         << "testing ossimQuickbirdRpcModel"
         << std::endl;
   }
   
   ossimQuickbirdRpcModel* qbModel = new ossimQuickbirdRpcModel;
   model = qbModel;
   if(qbModel->parseFile(filename))
   {
      if(traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "DEBUG ossimSensorModelFactory::createProjection: "
            << "returning ossimQuickbirdRpcModel" << std::endl;
      }
      return model.release();
   }
   else
   {
      model = 0;
   }
   //---
   // Test for ikonos rpc.  Could be tiff or nitf which is handled in
   // parseFile method.
   //---
   ossimIkonosRpcModel* ikModel = new ossimIkonosRpcModel;
   model = ikModel;
   if(ikModel->parseFile(filename))
   {
      if(traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "DEBUG ossimSensorModelFactory::createProjection: "
            << "returning ossimQuickbirdRpcModel" << std::endl;
      }
      return model.release();
   }
   else
   {
      model = 0;
   }

   if(isNitf(filename))
   {
     if(traceDebug())
     {
        ossimNotify(ossimNotifyLevel_DEBUG)
           << "DEBUG ossimSensorModelFactory::createProjection: "
           << " testing ossimNitfRpcModel" << std::endl;
     }

     ossimNitfRpcModel* rpcModel = new ossimNitfRpcModel();
      model = rpcModel;
     if ( rpcModel->parseFile(filename, entryIdx) ) // filename = NITF_file
     {
        return model.release();
     }
     model = 0;
     
     if(traceDebug())
     {
        ossimNotify(ossimNotifyLevel_DEBUG)
           << "DEBUG ossimSensorModelFactory::createProjection: "
           << "testing ossimIkinosRpcModel" << std::endl;
     }
     
     model = new ossimNitfMapModel(filename); // filename = NITF_file
     if(!model->getErrorStatus())
     {
        return model.release();
     }
   }
   else if(isLandsat(filename))
   {
      model = new ossimLandSatModel(filename);
      if(!model->getErrorStatus())
         return model.release();
   }
   model = 0;
   
   ossimFilename spot5Test = geomFile;
   if(!spot5Test.exists())
   {
      spot5Test = geomFile.path();
      spot5Test = spot5Test.dirCat(ossimFilename("METADATA.DIM"));
      if (spot5Test.exists() == false)
      {
         spot5Test = geomFile.path();
         spot5Test = spot5Test.dirCat(ossimFilename("metadata.dim"));
      }
   }
   if(spot5Test.exists())
   {
      ossimRefPtr<ossimSpotDimapSupportData> meta = new ossimSpotDimapSupportData;
      if(meta->loadXmlFile(spot5Test))
      {
         model = new ossimSpot5Model(meta.get());
         if(!model->getErrorStatus())
         {
            return model.release();
         }
         model = 0;
      }
   }
   
   model = new ossimCoarseGridModel(geomFile);
   if(model.valid())
   {
      if(!model->getErrorStatus())
         return model.release();
      model = 0;
   }
   return model.release();
}

bool ossimSensorModelFactory::isTileMap(const ossimFilename& filename)const
{
  ossimFilename temp(filename);
  temp.downcase();
  
  ossimString os = temp.beforePos(4);
  
  std::cout << os << std::endl;
  
  if(temp.ext()=="otb")
  {
    return true;
  }
  else
  {
    return true;
  }
  return false;
}
   
bool ossimSensorModelFactory::isNitf(const ossimFilename& filename)const
{
   std::ifstream in(filename.c_str(), ios::in|ios::binary);
   
   if(in)
   {
      char nitfFile[4];
      in.read((char*)nitfFile, 4);

      return (ossimString(nitfFile,
                          nitfFile+4) == "NITF");
   }

   return false;
}

bool ossimSensorModelFactory::isLandsat(const ossimFilename& filename)const
{
   ossimFilename temp(filename);
   temp.downcase();
   ossimRefPtr<ossimFfL7> ff_headerp;
   if (temp.contains("header.dat"))
   {
       ff_headerp = new ossimFfL5(filename);
   } 
   else 
   {
       ff_headerp = new ossimFfL7(filename);
   }
   bool r = !(ff_headerp->getErrorStatus());
   ff_headerp = 0;
   return r;
}

void ossimSensorModelFactory::findCoarseGrid(ossimFilename& result,
                                             const ossimFilename& geomFile)const
{
   result = geomFile;
   result.setFile(result.fileNoExtension()+"_ocg");
   result.setExtension("dat");
   
   if(!result.exists())
   {
      result = geomFile;
      result.setExtension("dat");
   }
   
   // let's find a .dat file in the current directory
   //
   if(!result.exists())
   {
      result = "";
      ossimDirectory directoryList(geomFile.path());
      ossimFilename file;
      if(directoryList.getFirst(file,
                                ossimDirectory::OSSIM_DIR_FILES))
      {
         ossimString testString = "OSSIM_DBL_GRID";
         char tempBuf[14];
         do
         {
            if(file.ext().downcase() == "dat")
            {
               ifstream in(file);
               if(in)
               {
                  in.read((char*)tempBuf, 14);
                  in.close();
                  if(ossimString(tempBuf, tempBuf+14) == testString)
                  {
                     result = file;
                  }
               }
               
            }
         }while((directoryList.getNext(file))&&(result == ""));
      }
      // try to find it
   }
}

