//*******************************************************************
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
// 
// Description:
// 
// Class definition for ossimQuickbirdMetaData.
// 
// This class parses a Space Imaging Quickbird meta data file.
//
//********************************************************************
// $Id: ossimQuickbirdMetaData.cpp 14431 2009-04-30 21:58:33Z dburken $

#include <cstdio>
#include <iostream>
#include <ossim/support_data/ossimQuickbirdMetaData.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimTrace.h>


RTTI_DEF1(ossimQuickbirdMetaData, "ossimQuickbirdMetaData", ossimObject);

// Define Trace flags for use within this file:
static ossimTrace traceExec  ("ossimQuickbirdMetaData:exec");
static ossimTrace traceDebug ("ossimQuickbirdMetaData:debug");

ossimQuickbirdMetaData::ossimQuickbirdMetaData()
  :
  theGenerationDate("Unknown"),
  theBandId("Unknown"),
  theSatID("Unknown"),
  theTLCDate("Unknown"),
  theSunAzimuth(0.0),
  theSunElevation(0.0)
{
  theAbsCalFactors.clear();
}

ossimQuickbirdMetaData::~ossimQuickbirdMetaData()
{
}

bool ossimQuickbirdMetaData::open(const ossimFilename& imageFile)
{
  static const char MODULE[] = "ossimQuickbirdMetaData::open";

  clearFields();

  //retrieve information from the metadata file
  //if the Quickbird tif is 02APR01105228-M1BS-000000128955_01_P001.TIF
  //the metadata file will be 02APR01105228-M1BS-000000128955_01_P001.IMD

  ossimFilename metadatafile = imageFile;
  metadatafile.setExtension(ossimString("IMD"));

  if( parseMetaData(metadatafile) == false )
    {
      if(traceDebug())
	{
	  ossimNotify(ossimNotifyLevel_WARN)
	    << MODULE << " errors parsing metadata" << std::endl;
	}
      return false;
    }

  return true;
}

void ossimQuickbirdMetaData::clearFields()
{
  theGenerationDate = "Unknown";
  theBandId = "Unknown";
  theSatID = "Unknown";
  theTLCDate = "Unknown",
  theSunAzimuth = 0.0;
  theSunElevation = 0.0;
  theAbsCalFactors.clear();
}

std::ostream& ossimQuickbirdMetaData::print(std::ostream& out) const
{

  out << "\n----------------- Info on Quickbird Image -------------------"
      << "\n  "
      << "\n  Generation date:   " << theGenerationDate
      << "\n  Band Id:   " << theBandId
      << "\n  Sat Id:   " << theSatID
      << "\n  TLC date:   " << theTLCDate
      << "\n  Sun Azimuth:    " << theSunAzimuth
      << "\n  Sun Elevation:   " << theSunElevation
      << "\n  abs Calibration Factors:   " 
      << std::endl;
      for(unsigned int i=0; i<theAbsCalFactors.size(); i++)
      {
      	out<<theAbsCalFactors[i] << "   ";
      }
      out<< "\n"
      << "\n---------------------------------------------------------"
      << "\n  " << std::endl;
  return out;
}

bool ossimQuickbirdMetaData::saveState(ossimKeywordlist& kwl,
				       const char* prefix)const
{


  kwl.add(prefix,
          ossimKeywordNames::TYPE_KW,
          "ossimQuickbirdMetaData",
          true);

  kwl.add(prefix,
          "generation_date",
          theGenerationDate,
          true);

  kwl.add(prefix,
          "band_id",
          theBandId,
          true);

  kwl.add(prefix,
          "sat_id",
          theSatID,
          true);

  kwl.add(prefix,
          "tlc_date",
          theTLCDate,
          true);

  kwl.add(prefix,
          ossimKeywordNames::AZIMUTH_ANGLE_KW,
          theSunAzimuth,
          true);

  kwl.add(prefix,
          ossimKeywordNames::ELEVATION_ANGLE_KW,
          theSunElevation,
          true);
//******************************************************
//  kwl.add(prefix,
//          "absCalFactors",
//          theAbsCalFactors,
//          true);
//******************************************************

  return true;
}

bool ossimQuickbirdMetaData::loadState(const ossimKeywordlist& kwl,
				       const char* prefix)
{
  clearFields();

  const char* lookup = 0;
  ossimString s;
  
  lookup = kwl.find(prefix, ossimKeywordNames::TYPE_KW);
  if (lookup)
    {
      s = lookup;
      if(s != "ossimQuickbirdMetaData")
	{
	  return false;
	}
    }

  lookup = kwl.find(prefix, "generation_date");
  if (lookup)
    {
      theGenerationDate = lookup;
    }

  lookup = kwl.find(prefix, "band_id");
  if (lookup)
    {
      theBandId = lookup;
    }

  lookup = kwl.find(prefix, "sat_id");
  if (lookup)
    {
      theSatID = lookup;
    }

  lookup = kwl.find(prefix, "tlc_date");
  if (lookup)
    {
      theTLCDate= lookup;
    }

  lookup = kwl.find(prefix, ossimKeywordNames::AZIMUTH_ANGLE_KW);
  if (lookup)
    {
      s = lookup;
      theSunAzimuth = s.toFloat64();
    }

  lookup = kwl.find(prefix, ossimKeywordNames::ELEVATION_ANGLE_KW);
  if (lookup)
    {
      s = lookup;
      theSunElevation = s.toFloat64();
    }

  return true;
}

//*****************************************************************************
// PROTECTED METHOD: ossimQuickbirdMetaData::parseMetaData()
//
//  Parses the Quickbird IMD file.
//
//*****************************************************************************
bool ossimQuickbirdMetaData::parseMetaData(const ossimFilename& data_file)
{
  if (traceExec()) ossimNotify(ossimNotifyLevel_DEBUG) << "DEBUG ossimQuickbirdMetaData::parseMetaData(data_file): entering..." << std::endl;
   
  if( !data_file.exists() )
    {
     if (traceExec()) ossimNotify(ossimNotifyLevel_WARN) << "ossimQuickbirdMetaData::parseMetaData(data_file) WARN:" << "\nmetadate data file <" << data_file << ">. " << "doesn't exist..." << std::endl;
     return false;
    }
  

  FILE* fptr = fopen (data_file, "r");
  if (!fptr)
    {
      if (traceDebug())
	{
	  ossimNotify(ossimNotifyLevel_DEBUG)
	    << "ossimQuickbirdRpcModel::parseMetaData(data_file) DEBUG:"
	    << "\nCould not open Meta data file:  " << data_file
	    << "\nreturning with error..." << std::endl;
	}
      return false;
    }

  char* strptr;
  char dummy[80], name[80];
  double value;

  //---
  // Read the file into a buffer:
  //---
  ossim_int32 fileSize = static_cast<ossim_int32>(data_file.fileSize());
  char* filebuf = new char[fileSize];
  fread(filebuf, 1, fileSize, fptr);
  strptr = filebuf;
  fclose(fptr);
  ossimString temp;

  //---
  // Generation time:
  //---
  
  if(getEndOfLine( strptr, ossimString("\ngenerationTime ="), "%17c %s", temp))
    theGenerationDate = ossimString(temp).before(";");
  else
    {
      if(traceDebug())
	{
	  ossimNotify(ossimNotifyLevel_FATAL)
	    << "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
	    << "\n\tAborting construction. Error encountered parsing "
	    << "presumed meta-data file." << std::endl;

	  delete [] filebuf;
	  return false;
	}
    }

  //---
  // BandId:
  //---
  if(getEndOfLine( strptr, ossimString("\nbandId ="), "%9c %s", temp))
    theBandId = ossimString(temp).after("\"").before("\";");
  else
    {
      if(traceDebug())
	{
	  ossimNotify(ossimNotifyLevel_FATAL)
	    << "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
	    << "\n\tAborting construction. Error encountered parsing "
	    << "presumed meta-data file." << std::endl;

	  delete [] filebuf;
	  return false;
	}
    }

  //---
  // absCalFactors:
  //---
  //--- Multispectral
  std::cout<<theBandId<<std::endl;
  if(theBandId=="Multi")
    {
      std::vector<ossimString> bandList(4, "B");
      bandList[1] = "G";
      bandList[2] = "R";
      bandList[3] = "N";
      for(unsigned int j=0; j<bandList.size(); j++)
      {
      	ossimString begin_group = "\nBEGIN_GROUP = BAND_" + bandList[j];
  	  	if(getEndOfLine( strptr, ossimString(begin_group), "%20c %s", temp))
      		{
      		    ossimString bandCur = ossimString(temp).before("\n");
      			std::cout<<bandCur<<bandList[j]<<"--"<<std::endl;

      			bool fine=false;
      	  		if(bandList[j] == bandCur)
	  			{
	  				std::cout<<bandCur<<"--"<<bandList[j]<<"--"<<std::endl;
	  		    	if(getEndOfLine( strptr, ossimString("\n\tabsCalFactor = "), "%17c %s", temp))
      				{
      					//std::cout<<strptr<<std::endl;
      					//std::cout<<"==================================="<<std::endl;
      					std::cout<<ossimString(temp).before(";").toFloat64()<<std::endl;
      					fine = true;
      				}
	  			}
	  		    if(fine==false && traceDebug())
	    		{	  				
	    			std::cout<<"exceptionnnnnn"<<std::endl;
		  			ossimNotify(ossimNotifyLevel_FATAL)
	    	 				<< "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
	    	 				<< "\n\tAborting construction. Error encountered parsing "
	    	 				<< "presumed meta-data file." << std::endl;
		  		  	delete [] filebuf;
  		  			return false;
     			}
 	      }
  	  	else
      	{
        	if(traceDebug())
	    	{
		  		ossimNotify(ossimNotifyLevel_FATAL)
	    	  		<< "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
	    	  		<< "\n\tAborting construction. Error encountered parsing "
	    	  		<< "presumed meta-data file." << std::endl;

	  		  	delete [] filebuf;
	  		  	return false;
	     	}
     	}
     }
     }
  //--- Panchromatic
  else
    {
    }
  //---
  // SatID:
  //---
  if(getEndOfLine( strptr, ossimString("\n\tsatId ="), "%9c %s", temp))
    theSatID = ossimString(temp).after("\"").before("\";");
  else
    {
      if(traceDebug())
	{
	  ossimNotify(ossimNotifyLevel_FATAL)
	    << "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
	    << "\n\tAborting construction. Error encountered parsing "
	    << "presumed meta-data file." << std::endl;

	  delete [] filebuf;
	  return false;
	}
    }


  //---
  // TLCTime:
  //---
  if(getEndOfLine( strptr, ossimString("\n\tTLCTime ="), "%11c %s", temp))
    theTLCDate = ossimString(temp).before("\";");
  else
    {
      if(traceDebug())
	{
	  ossimNotify(ossimNotifyLevel_FATAL)
	    << "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
	    << "\n\tAborting construction. Error encountered parsing "
	    << "presumed meta-data file." << std::endl;

	  delete [] filebuf;
	  return false;
	}
    }
//std::cout<<strptr<<std::endl;

  //***
  // Sun Azimuth:
  //***
  if(getEndOfLine( strptr, ossimString("\n\tsunAz ="), "%9c %s", temp))
    theSunAzimuth = ossimString(temp).before(";").toFloat64();
  else
    {
      if(getEndOfLine( strptr, ossimString("\n\tmeanSunAz ="), "%13c %s", temp))
	theSunAzimuth = ossimString(temp).before(";").toFloat64();
      else
	{
	  if(traceDebug())
	    {
	      ossimNotify(ossimNotifyLevel_FATAL)
		<< "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
		<< "\n\tAborting construction. Error encountered parsing "
		<< "presumed meta-data file." << std::endl;

	      delete [] filebuf;
	      return false;
	    }
	}
    }

  //***
  // Sun Elevation:
  //***
  if(getEndOfLine( filebuf, ossimString("\n\tsunEl ="), "%9c %s", temp))
    theSunElevation = ossimString(temp).before(";").toFloat64();
  else
    {
      if(getEndOfLine( filebuf, ossimString("\n\tmeanSunEl ="), "%13c %s", temp))
	theSunElevation = ossimString(temp).before(";").toFloat64();
      else
	{
	  if(traceDebug())
	    {
	      ossimNotify(ossimNotifyLevel_FATAL)
		<< "FATAL ossimQuickbirdRpcModel::parseMetaData(data_file): "
		<< "\n\tAborting construction. Error encountered parsing "
		<< "presumed meta-data file." << std::endl;

	      delete [] filebuf;
	      return false;
	    }
	}
    }

  delete [] filebuf;
  filebuf = 0;

  if (traceExec())
    {
      ossimNotify(ossimNotifyLevel_DEBUG)
        << "DEBUG ossimQuickbirdRpcModel::parseMetaData(data_file): returning..."
        << std::endl;
    }

  return true;
}

//*****************************************************************************
// PROTECTED METHOD: ossimQuickbirdMetaData::parseGEOData()
//
//  Parses the Quickbird GEO file.
//
//*****************************************************************************
bool ossimQuickbirdMetaData::parseGEOData(const ossimFilename& data_file)
{
  return true;
}

//*****************************************************************************
// PROTECTED METHOD: ossimQuickbirdMetaData::parseRpcData()
//
//  Parses the Quickbird EPH file.
//
//*****************************************************************************
bool ossimQuickbirdMetaData::parseEPHData(const ossimFilename& data_file)
{
  return true;
}

//*****************************************************************************
// PROTECTED METHOD: ossimQuickbirdMetaData::parseRpcData()
//
//  Parses the Quickbird ATT file.
//
//*****************************************************************************
bool ossimQuickbirdMetaData::parseATTData(const ossimFilename& data_file)
{
  return true;
}

//*****************************************************************************
// PROTECTED METHOD: ossimQuickbirdMetaData::getEndOfLine
//
// //  Parse a char * to find another char *. Change the pointer only if the second char * is found.
//
//*****************************************************************************
bool ossimQuickbirdMetaData::getEndOfLine( char * fileBuf, ossimString lineBeginning, char * format, ossimString & name)
  {
     //char * res = strstr(fileBuf, lineBeginning.c_str());
     //if (!res)
     //{
     //  return false;
     // }
    //// if the lineBeginning is found, update the start pointer adress
    //fileBuf = res;
        
    //char dummy[80], nameChar[80];
    //sscanf(res, format, dummy, nameChar);    
    //name = ossimString(nameChar);
    
    char * res = strstr(fileBuf, lineBeginning.c_str());
    if(!res)
    {
    	return false;
    }
    fileBuf = strstr(fileBuf, lineBeginning.c_str());
    char dummy[80], nameChar[80];
    sscanf(fileBuf, format, dummy, nameChar);  
    name = ossimString(nameChar);
    
    return true;
  }
