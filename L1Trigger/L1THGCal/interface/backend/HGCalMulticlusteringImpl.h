#ifndef __L1Trigger_L1THGCal_HGCalMulticlusteringImpl_h__
#define __L1Trigger_L1THGCal_HGCalMulticlusteringImpl_h__

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/L1THGCal/interface/HGCalCluster.h"
#include "DataFormats/L1THGCal/interface/HGCalMulticluster.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "L1Trigger/L1THGCal/interface/HGCalTriggerGeometryBase.h"
#include "L1Trigger/L1THGCal/interface/backend/HGCalShowerShape.h"
#include "L1Trigger/L1THGCal/interface/HGCalTriggerTools.h"
#include "L1Trigger/L1THGCal/interface/backend/HGCalTriggerClusterIdentificationBase.h"


class HGCalMulticlusteringImpl{

public:

    HGCalMulticlusteringImpl( const edm::ParameterSet &conf);    

    void eventSetup(const edm::EventSetup& es) 
    {
        triggerTools_.eventSetup(es);
        shape_.eventSetup(es);
    }

    bool isPertinent( const l1t::HGCalCluster & clu, 
                      const l1t::HGCalMulticluster & mclu, 
                      double dR ) const;

    float dR( const l1t::HGCalCluster & clu,
	      const GlobalPoint & seed ) const;

    void clusterizeDR( const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtr, 
                     l1t::HGCalMulticlusterBxCollection & multiclusters,
                     const HGCalTriggerGeometryBase & triggerGeometry
                     );

    void clusterizeDBSCAN( const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtr, 
                     l1t::HGCalMulticlusterBxCollection & multiclusters,
                     const HGCalTriggerGeometryBase & triggerGeometry
                     );

    void clusterizeHistoMax( const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtr,
		     l1t::HGCalMulticlusterBxCollection & multiclusters,
		     const HGCalTriggerGeometryBase & triggerGeometry
		     );

    void clusterizeHistoThreshold( const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtr,
		     l1t::HGCalMulticlusterBxCollection & multiclusters,
		     const HGCalTriggerGeometryBase & triggerGeometry
		     );


private:

    void findNeighbor( const std::vector<std::pair<unsigned int,double>>&  rankedList,
                       unsigned int searchInd,
                       const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtr, 
                       std::vector<unsigned int>& neigbors);

    std::map<std::vector<int>,float> fillHistoClusters( const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtrs );

    std::map<std::vector<int>,float> fillSmoothPhiHistoClusters( std::map<std::vector<int>,float> histoClusters,
								 const vector<unsigned> binSums );

    std::map<std::vector<int>,float> fillSmoothRPhiHistoClusters( std::map<std::vector<int>,float> histoClusters );

    std::vector<GlobalPoint> computeMaxSeeds( std::map<std::vector<int>,float> histoClusters );

    std::vector<GlobalPoint> computeThresholdSeeds( std::map<std::vector<int>,float> histoClusters );

    std::vector<l1t::HGCalMulticluster> clusterSeedMulticluster(const std::vector<edm::Ptr<l1t::HGCalCluster>> & clustersPtrs,
								const std::vector<GlobalPoint> seeds);

    void finalizeClusters(std::vector<l1t::HGCalMulticluster>&,
            l1t::HGCalMulticlusterBxCollection&,
            const HGCalTriggerGeometryBase&);
    
    double dr_;
    double ptC3dThreshold_;
    std::string multiclusterAlgoType_;
    double distDbscan_ = 0.005;
    unsigned minNDbscan_ = 3;
    unsigned nBinsRHisto_ = 36;
    unsigned nBinsPhiHisto_ = 216;
    std::vector<unsigned> binsSumsHisto_;
    double histoThreshold_ = 20.;

    HGCalShowerShape shape_;
    HGCalTriggerTools triggerTools_;
    std::unique_ptr<HGCalTriggerClusterIdentificationBase> id_;

    static constexpr double kROverZMin_ = 0.09;
    static constexpr double kROverZMax_ = 0.52;

};

#endif
