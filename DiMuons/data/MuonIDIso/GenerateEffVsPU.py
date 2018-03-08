#!/usr/bin/env python

#####################################################################
###    Generate normalized pileup-dependent ID/Iso efficiencies   ###
###             Andrew Brinkerhoff 18.01.17                       ###
###                                                               ###
#####################################################################

from ROOT import *
import sys

def main():

    PU_years = ['2016']      ## Data acquisision eras
    PU_profs = ['Summer16']  ## MC piluep profiles
    PU_vers  = ['v0']        ## User versions
    mu_eras  = ['BCDEF', 'GH']
    mu_cuts  = [ ['ID',  'MC_NUM_MediumID_DEN_genTracks_PAR'], 
                 ['Iso', 'LooseISO_MediumID'] ]

    for year in PU_years:
        for prof in PU_profs:
            for ver in PU_vers:
                for era in mu_eras:
                    for cut in mu_cuts:

                        print '\n\nLooking at %s %s %s %s %s' % (year, prof, ver, era, cut[0])
                        
                        PU_file_name = '../Pileup/PU_data_%s_%s.root' % (year, ver)
                        mu_file_name = 'EfficienciesAndSF_%s_Mu%s.root' % (era, cut[0])
                        
                        PU_file = TFile.Open(PU_file_name)
                        mu_file = TFile.Open(mu_file_name, 'UPDATE')

                        h_PU = PU_file.Get('pileup')
                        h_PU.Scale( 1.0 / h_PU.Integral() )
                            
                        h_mu_data = mu_file.Get('%s_vtx/efficienciesDATA/histo_tag_nVertices_DATA' % cut[1])
                        h_mu_MC   = mu_file.Get('%s_vtx/efficienciesMC/histo_tag_nVertices_MC' % cut[1])
                        h_mu_SF   = mu_file.Get('%s_vtx/tag_nVertices_ratio' % cut[1])

                        mu_data_sum = 0
                        mu_MC_sum   = 0
                        mu_SF_sum   = 0
                        for iMu in range(1, h_mu_SF.GetNbinsX()+1):
                            PU_sum = 0
                            for iPU in range(1, h_PU.GetNbinsX()+1):
                                if ( h_PU.GetBinLowEdge(iPU) > h_mu_SF.GetBinLowEdge(iMu) and
                                     h_PU.GetBinLowEdge(iPU) < h_mu_SF.GetBinLowEdge(iMu) + h_mu_SF.GetBinWidth(iMu) ):
                                    PU_sum += h_PU.GetBinContent(iPU)

                            if (PU_sum > 0):
                                mu_data_sum += h_mu_data.GetBinContent(iMu) * PU_sum
                                mu_MC_sum   += h_mu_MC.GetBinContent(iMu)   * PU_sum
                                mu_SF_sum   += h_mu_SF.GetBinContent(iMu)   * PU_sum

                        print 'Muon data sum = %.3f, MC = %.3f, SF = %.3f' % ( mu_data_sum, mu_MC_sum, mu_SF_sum )

                        gROOT.cd()
                        h_mu_data_norm = manual_clone(h_mu_data, 'histo_tag_nVertices_DATA_norm')
                        h_mu_MC_norm   = manual_clone(h_mu_MC,   'histo_tag_nVertices_MC_norm')
                        h_mu_SF_norm   = manual_clone(h_mu_SF,   'tag_nVertices_ratio_norm')

                        h_mu_data_norm.Scale(1.0 / mu_data_sum)
                        h_mu_MC_norm  .Scale(1.0 / mu_MC_sum)
                        h_mu_SF_norm  .Scale(1.0 / mu_SF_sum)

                        del h_mu_data
                        del h_mu_MC  
                        del h_mu_SF  

                        mu_file.cd()

                        ## For some reason, writes duplicates of h_mu_data, h_mu_MC, and h_mu_SF every time ...
                        ## and writes the "_norm" histograms in both the top directory and the proper directory
                        ## Bizzare, confusing, and annoying ... should fix sometime - AWB 13.03.17
                        h_mu_data_norm.SetDirectory(mu_file.GetDirectory('%s_vtx/efficienciesDATA' % cut[1]))
                        h_mu_MC_norm  .SetDirectory(mu_file.GetDirectory('%s_vtx/efficienciesMC' % cut[1]))
                        h_mu_SF_norm  .SetDirectory(mu_file.GetDirectory('%s_vtx' % cut[1]))
                        h_mu_data_norm.Write('', TObject.kWriteDelete)
                        h_mu_MC_norm  .Write('', TObject.kWriteDelete)
                        h_mu_SF_norm  .Write('', TObject.kWriteDelete)

                        mu_file.Write()
                        mu_file.Close()
                        PU_file.Close()


def manual_clone(old_hist, new_name):
    nBins = old_hist.GetNbinsX()
    x_low = old_hist.GetBinLowEdge(1)
    x_hi  = old_hist.GetBinLowEdge(old_hist.GetNbinsX()) + old_hist.GetBinWidth(old_hist.GetNbinsX())
    new_hist = TH1F(new_name, new_name, nBins, x_low, x_hi)

    for iBin in range(1, nBins+1):
        new_hist.SetBinContent(iBin, old_hist.GetBinContent(iBin))
        new_hist.SetBinError(iBin, old_hist.GetBinError(iBin))

    return new_hist
                

if __name__ == '__main__':
    main()
