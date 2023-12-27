// PinkTrombone.cpp
// Bruno Gola (me@bgo.la)

#include "SC_PlugIn.hpp"
#include "PinkTrombone.hpp"
#include "PinkTrombone/Glottis.hpp"
#include "PinkTrombone/Tract.hpp"
#include "PinkTrombone/util.h"
#include <stdio.h>
#include <stdlib.h>


static InterfaceTable* ft;

namespace PinkTrombone {

PinkTrombone::PinkTrombone() {
    mCalcFunc = make_calc_function<PinkTrombone, &PinkTrombone::next>();
    Unit* unit = (Unit*) this;

    m_buffer_size = 128;
    
    pitch = 440.0;
    fm = 0;
    tongueX = 0.0;
    tongueY = 0.0;
    constrictionX = 0.0;
    constrictionY = 0.0;
    fricativeIntensity = 0.0;
    vibAmount = 0.0;
    fricativeLevel = 0.5;
    muteAudio = false;
    constrictionActive = true;
    
    newFricFC = 0.5;
    newAspFC = 0.5;
    newQ = 0.5;
    tenseness = 0.5;
    
    int n = 44;
    sample_t sampleRate = SAMPLERATE;
    sample_t samplesPerBlock = m_buffer_size;
    
    initializeTractProps(&tractProps, n);
    
    glottis = new Glottis(sampleRate);
    bool isnull = false;
    if (glottis == NULL) { isnull = true; };
    
    tract = new Tract(sampleRate, samplesPerBlock, &tractProps);
    
    next(1);
}

PinkTrombone::~PinkTrombone() {
}

void PinkTrombone::next(int nSamples) {
    float* output = out(0);
    // TODO: try using two noise sources, one of Aspirate and one for fricative
    const float *noiseSource = in(0);
    const float *freq = in(1);
    const float *tenseness = in(2);
    const float *tongueIndex = in(3);
    const float *tongueDiameter = in(4);
    const float *constrictionX = in(5);
    const float *constrictionY = in(6);
    const float *fricativeIntens = in(7);


    Unit* unit = (Unit*) this;
    bool isnull = false;
    if (glottis == NULL) { isnull = true; };
   
    for (int i=0; i < nSamples; ++i) {
    	glottis->setIntensity(fricativeLevel);
    	glottis->setTargetFrequency(freq[i]);
    	glottis->setTargetTenseness(tenseness[i]);
	tract->setRestDiameter(tongueIndex[i], tongueDiameter[i]);
	
	//tractProps.noseStart = (int)(params[NOSE_PARAM].getValue());
	//tractProps.bladeStart = (int)(1.f + params[BLADE_PARAM].getValue() * 10.f);
	//tractProps.tipStart = (int)(params[TIP_PARAM].getValue()*params[BLADE_PARAM].getValue());
	double lambda1 = 1 / nSamples;
	double lambda2 = (1+0.5)/nSamples;
	//sample_t lambda1 = (nSamples+j)/(sample_t)N;
	//sample_t lambda2 = (samplesSinceLastUpdate+j+(sample_t)0.5)/(sample_t)N;

	double glot = glottis->runStep(lambda1, noiseSource[i]);
	double vocalOutput = 0.0;
	double random = rand();
	tract->runStep(glot, noiseSource[i], lambda1, glottis->getNoiseModulator());
	float vocalOut1 = tract->lipOutput + tract->noseOutput;
	tract->runStep(glot, noiseSource[i], lambda2, glottis->getNoiseModulator());
	float vocalOut2 = tract->lipOutput + tract->noseOutput;
	vocalOutput = (vocalOut1 + vocalOut2) * 0.125;
	//vocalOutput = glot;

	double constrictionMin = -2.0;
	double constrictionMax = 2.0;
	double constrictionIndex = constrictionX[i] * (double)tract->getTractIndexCount();
	double constrictionDiameter = constrictionY[i] * (constrictionMax - constrictionMin) + constrictionMin;
	//fricativeIntensity += 0.1; // TODO ex recto
	//fricativeIntensity = minf(1.0, this->fricativeIntensity);
	tract->setConstriction(constrictionIndex, constrictionDiameter, fricativeIntens[i]);
	glottis->finishBlock();
	tract->finishBlock();
	output[i] = vocalOutput;

	//output[i] = vocalOutput;

        //outl[i] = fri;
        //outr[i] = asp;
	//output[i] = fri;
    };
}


} // namespace PinkTrombone 



PluginLoad(PinkTromboneUGens) {
    ft = inTable;
    registerUnit<PinkTrombone::PinkTrombone>(ft, "PinkTrombone", false);
}
