#!/usr/bin/env python

#########################################################
###    Simple macro to generate pileup wieghts file   ###
###             Andrew Brinkerhoff 18.01.17           ###
###                                                   ###
#########################################################

from ROOT import *
import sys

def main():

    eras  = ['2016']  ## Data acquisision eras
    profs = ['Spring16', 'Summer16','Winter17']  ## MC piluep profiles
    vers  = ['v0']  ## User versions

    for era in eras:
        for prof in profs:
            for ver in vers:
                prob_MC = GetProbMC(prof)
                out_file = TFile('PU_wgt_%s_%s_%s.root' % (era, prof, ver), 'recreate')
                for sys in ['', '_up', '_down']:
                    CalcWeights(era, prof, ver, prob_MC, sys, out_file)
                out_file.Close()

def CalcWeights(era, prof, ver, prob_MC, sys, out_file):    

    data_file_name = 'PU_data_%s%s_%s.root' % (era, sys, ver)
    data_file = TFile.Open(data_file_name)
    h_data = data_file.Get('pileup')

    #################################
    ### Create data distribution  ###
    #################################

    out_file.cd()
    h_data.Scale(1.0/h_data.Integral())

    ## Resize X-axis to number of bins in MC distribution
    if h_data.GetNbinsX() != len(prob_MC):
        h_tmp = TH1D('tmp', 'tmp', len(prob_MC), 0, len(prob_MC))
        h_tmp.Sumw2()
        for i in range(len(prob_MC)):
            if i < h_data.GetNbinsX():
                h_tmp.SetBinContent(i+1, h_data.GetBinContent(i+1))
                h_tmp.SetBinError(i+1, h_data.GetBinError(i+1))
            else:
                h_tmp.SetBinContent(i+1, 0)
                h_tmp.SetBinError(i+1, 1)
        h_data = h_tmp
        h_data.Scale(1.0/h_data.Integral())

    h_data.SetName('PU_data%s' % sys)
    h_data.SetTitle('True nPV in data (%s)' % era)
    h_data.GetXaxis().SetTitle('True number of interactions')
    h_data.GetYaxis().SetTitle('Probability')
    h_data.SetLineWidth(2)
    h_data.SetLineColor(kBlack)
    if sys == '_up':   h_data.SetLineColor(kRed)
    if sys == '_down': h_data.SetLineColor(kBlue)
    h_data.Write()

    ###############################
    ### Create MC distribution  ###
    ###############################

    h_MC = TH1D('PU_MC', 'True nPV in MC', len(prob_MC), 0, len(prob_MC))
    h_MC.Sumw2()
    for i in range(len(prob_MC)):
        h_MC.SetBinContent(i+1, prob_MC[i])
        h_MC.SetBinError(i+1, 0.)
    if abs(1.0 - h_MC.Integral()) > 0.000001:
        print 'MC integral = %f, not 1. Check entries and try again. Exiting.'
        sys.exit()
    h_MC.GetXaxis().SetTitle('True number of interactions')
    h_MC.GetYaxis().SetTitle('Probability')
    h_MC.SetLineWidth(2)
    h_MC.SetLineColor(kSpring)
    if sys == '': h_MC.Write()

    #############################################
    ### Create weight (data/MC) distribution  ###
    #############################################

    h_ratio = h_data.Clone()
    h_ratio.Divide(h_MC)
    h_ratio.SetName('PU_wgt%s' % sys)
    h_ratio.SetTitle('True nPV weight: data / MC')
    h_ratio.GetXaxis().SetTitle('True number of interactions')
    h_ratio.GetYaxis().SetTitle('Weight')
    h_ratio.SetLineWidth(2)
    h_ratio.SetLineColor(kBlack)
    if sys == '_up':   h_ratio.SetLineColor(kRed)
    if sys == '_down': h_ratio.SetLineColor(kBlue)

    ## Check for unusual features
    print '\n*** Checking weight histogram for era %s, MC profile %s, version %s ***' % (era, prof, ver)
    for i in range(len(prob_MC)):
        if ( h_data.GetBinContent(i+1) == 0 or h_MC.GetBinContent(i+1) == 0 or h_ratio.GetBinContent(i+1) == 0 ):
            print 'Bin %d has data = %f, MC = %f, ratio = %f' % ( i+1, h_data.GetBinContent(i+1),
                                                                  h_MC.GetBinContent(i+1),
                                                                  h_ratio.GetBinContent(i+1) )
        if ( h_MC.GetBinContent(i+1) == 0 and h_data.GetBinContent(i+1) > 0 ):
            print '  * Setting ratio to 1 +/ 1'
            h_ratio.SetBinContent(i+1, 1.0)
            h_ratio.SetBinError(i+1, 1.0)

        elif ( h_ratio.GetBinContent(i+1) > 0 or h_data.GetBinContent(i+1) > 0 ):
            if abs( (h_ratio.GetBinError(i+1) / h_ratio.GetBinContent(i+1)) -
                    (h_data.GetBinError(i+1) / h_data.GetBinContent(i+1)) ) > 0.000001:
                print 'Bin %d ratio error = %f, data = %f. Code is buggy.' % ( i+1, h_ratio.GetBinError(i+1) / h_ratio.GetBinContent(i+1),
                                                                               h_data.GetBinError(i+1) / h_data.GetBinContent(i+1) )

    h_ratio.Write()
    
    ######################################################
    ### Closure test: create weighted MC distribution  ###
    ######################################################

    h_MC_wgt = h_MC.Clone()
    h_MC_wgt.SetName('PU_MC_wgt%s' % sys)
    h_MC_wgt.SetLineColor(kOrange)
    if sys == '_up':   h_MC_wgt.SetLineColor(kMagenta)
    if sys == '_down': h_MC_wgt.SetLineColor(kViolet)
    for iBin in range(1, h_MC_wgt.GetNbinsX()+1):
        h_MC_wgt.SetBinContent( iBin, h_MC_wgt.GetBinContent(iBin) * h_ratio.GetBinContent(iBin) )
        h_MC_wgt.SetBinError  ( iBin, h_MC_wgt.GetBinError(iBin)   * h_ratio.GetBinContent(iBin) )
    h_MC_wgt.Write()

## End def CalcWeights(era, prof, ver, prob_MC):

                
def GetProbMC(prof):

    prob_MC = []

    if (prof == 'Spring16'):
        ## From https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py#L25
        ## 2016.03.10
        prob_MC = [ 0.000829312873542, 0.00124276120498, 0.00339329181587, 0.00408224735376, 0.00383036590008, 0.00659159288946,
                    0.00816022734493, 0.00943640833116, 0.0137777376066, 0.017059392038, 0.0213193035468, 0.0247343174676,
                    0.0280848773878, 0.0323308476564, 0.0370394341409, 0.0456917721191, 0.0558762890594, 0.0576956187107,
                    0.0625325287017, 0.0591603758776, 0.0656650815128, 0.0678329011676, 0.0625142146389, 0.0548068448797, 
                    0.0503893295063, 0.040209818868, 0.0374446988111, 0.0299661572042, 0.0272024759921, 0.0219328403791, 
                    0.0179586571619, 0.0142926728247, 0.00839941654725, 0.00522366397213, 0.00224457976761, 0.000779274977993, 
                    0.000197066585944, 7.16031761328e-05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]


    if (prof == 'Summer16'):
        ## From https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_X/SimGeneral/MixingModule/python/mix_2016_25ns_Moriond17MC_PoissonOOTPU_cfi.py#L25
        ## 2016.09.08
        prob_MC = [ 1.78653e-05, 2.56602e-05, 5.27857e-05, 8.88954e-05, 0.000109362, 0.000140973, 0.000240998, 0.00071209, 
                    0.00130121, 0.00245255, 0.00502589, 0.00919534, 0.0146697, 0.0204126, 0.0267586, 0.0337697, 0.0401478, 
                    0.0450159, 0.0490577, 0.0524855, 0.0548159, 0.0559937, 0.0554468, 0.0537687, 0.0512055, 0.0476713, 
                    0.0435312, 0.0393107, 0.0349812, 0.0307413, 0.0272425, 0.0237115, 0.0208329, 0.0182459, 0.0160712, 
                    0.0142498, 0.012804, 0.011571, 0.010547, 0.00959489, 0.00891718, 0.00829292, 0.0076195, 0.0069806, 
                    0.0062025, 0.00546581, 0.00484127, 0.00407168, 0.00337681, 0.00269893, 0.00212473, 0.00160208, 
                    0.00117884, 0.000859662, 0.000569085, 0.000365431, 0.000243565, 0.00015688, 9.88128e-05, 6.53783e-05, 
                    3.73924e-05, 2.61382e-05, 2.0307e-05, 1.73032e-05, 1.435e-05, 1.36486e-05, 1.35555e-05, 1.37491e-05, 
                    1.34255e-05, 1.33987e-05, 1.34061e-05, 1.34211e-05, 1.34177e-05, 1.32959e-05, 1.33287e-05 ]

    if (prof == 'Winter17'):
        ## From https://github.com/cms-sw/cmssw/blob/CMSSW_9_4_X/SimGeneral/MixingModule/python/mix_2017_25ns_WinterMC_PUScenarioV1_PoissonOOTPU_cfi.py
        ## 2018.03.08
        prob_MC = [ 3.39597497605e-05,
              6.63688402133e-06,
              1.39533611284e-05,
              3.64963078209e-05,
              6.00872171664e-05,
              9.33932578027e-05,
              0.000120591524486,
              0.000128694546198,
              0.000361697233219,
              0.000361796847553,
              0.000702474896113,
              0.00133766053707,
              0.00237817050805,
              0.00389825605651,
              0.00594546732588,
              0.00856825906255,
              0.0116627396044,
              0.0148793350787,
              0.0179897368379,
              0.0208723871946,
              0.0232564170641,
              0.0249826433945,
              0.0262245860346,
              0.0272704617569,
              0.0283301107549,
              0.0294006137386,
              0.0303026836965,
              0.0309692426278,
              0.0308818046328,
              0.0310566806228,
              0.0309692426278,
              0.0310566806228,
              0.0310566806228,
              0.0310566806228,
              0.0307696426944,
              0.0300103336052,
              0.0288355370103,
              0.0273233309106,
              0.0264343533951,
              0.0255453758796,
              0.0235877272306,
              0.0215627588047,
              0.0195825559393,
              0.0177296309658,
              0.0160560731931,
              0.0146022004183,
              0.0134080690078,
              0.0129586991411,
              0.0125093292745,
              0.0124360740539,
              0.0123547104433,
              0.0123953922486,
              0.0124360740539,
              0.0124360740539,
              0.0123547104433,
              0.0124360740539,
              0.0123387597772,
              0.0122414455005,
              0.011705203844,
              0.0108187105305,
              0.00963985508986,
              0.00827210065136,
              0.00683770076341,
              0.00545237697118,
              0.00420456901556,
              0.00367513566191,
              0.00314570230825,
              0.0022917978982,
              0.00163221454973,
              0.00114065309494,
              0.000784838366118,
              0.000533204105387,
              0.000358474034915,
              0.000238881117601,
              0.0001984254989,
              0.000157969880198,
              0.00010375646169,
              6.77366175538e-05,
              4.39850477645e-05,
              2.84298066026e-05,
              1.83041729561e-05,
              1.17473542058e-05,
              7.51982735129e-06,
              6.16160108867e-06,
              4.80337482605e-06,
              3.06235473369e-06,
              1.94863396999e-06,
              1.23726800704e-06,
              7.83538083774e-07,
              4.94602064224e-07,
              3.10989480331e-07,
              1.94628487765e-07,
              1.57888581037e-07,
              1.2114867431e-07,
              7.49518929908e-08,
              4.6060444984e-08,
              2.81008884326e-08,
              1.70121486128e-08,
              1.02159894812e-08]

    return prob_MC

## End def GetProbMC(prof):


if __name__ == '__main__':
    main()
