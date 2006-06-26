#ifndef SiStripZeroSuppressionAlgorithm_h
#define SiStripZeroSuppressionAlgorithm_h

/** \class SiStripZeroSuppressionAlgorithm
 *
 * SiStripZeroSuppressionAlgorithm invokes specific strip Zero Suppression algorithms
 *
 * \author Domenico Giordano
 *
 *
 ************************************************************/

#include <string>

//edm
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
//Data Formats
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/SiStripDigi/interface/SiStripDigi.h"
#include "DataFormats/SiStripDigi/interface/SiStripRawDigi.h"
//ES Data
#include "CondFormats/SiStripObjects/interface/SiStripPedestals.h" 
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h"

#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripZeroSuppressor.h"
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripCommonModeNoiseSubtractor.h"
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripPedestalsSubtractor.h"

//SiStripPedestalsService
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripPedestalsService.h"
//SiStripNoiseService
#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripNoiseService.h"

#include <iostream> 
#include <memory>
#include <string>
#include <vector>
#include "CLHEP/Random/RandFlat.h"

class SiStripZeroSuppressionAlgorithm 
{
 public:
  
  SiStripZeroSuppressionAlgorithm(const edm::ParameterSet& conf);
  ~SiStripZeroSuppressionAlgorithm();

  /// Runs the algorithm
  void run(std::string RawDigiType, const edm::DetSetVector<SiStripRawDigi>& input,
	   edm::DetSetVector<SiStripDigi>& output);

  void configure( SiStripPedestalsService* , SiStripNoiseService* );

 private:
  edm::ParameterSet conf_;

  SiStripZeroSuppressor* SiStripZeroSuppressor_;
  std::string ZeroSuppressionMode_;
  bool validZeroSuppression_;  

  SiStripCommonModeNoiseSubtractor* SiStripCommonModeNoiseSubtractor_;
  std::string CMNSubtractionMode_;
  bool validCMNSubtraction_;  

  SiStripPedestalsSubtractor* SiStripPedestalsSubtractor_;
};
#endif
