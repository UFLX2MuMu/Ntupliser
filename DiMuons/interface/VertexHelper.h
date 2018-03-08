
#ifndef VERTEX_HELPER
#define VERTEX_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/VertexInfo.h"

void FillVertexInfos( VertexInfos& _vertexInfos, int& _nVertices,
                      const reco::VertexCollection verticesSelected,
                      const bool _onlyPV );

reco::VertexCollection SelectVertices( const edm::Handle<reco::VertexCollection>& vertices, const double _vertex_ndof_min,
				       const double _vertex_rho_max, const double _vertex_z_max, bool& _goodPV );

#endif  // #ifndef VERTEX_HELPER
