// PinkTrombone.hpp
// Bruno Gola (me@bgo.la)

#pragma once

#include "SC_PlugIn.hpp"
#include "PinkTrombone/Glottis.hpp"
#include "PinkTrombone/Tract.hpp"
#include "PinkTrombone/util.h"

namespace PinkTrombone {

class PinkTrombone : public SCUnit {
public:
    PinkTrombone();

    // Destructor
    ~PinkTrombone();

private:
    // Calc function
    void next(int nSamples);
    Glottis *glottis;
    Tract *tract;
    t_tractProps tractProps;
    uint32_t m_buffer_size = 128;

    float pitch = 440.0;
    float fm = 0;
    float tongueX = 0.0;
    float tongueY = 0.0;
    float constrictionX = 0.0;
    float constrictionY = 0.0;
    float fricativeIntensity = 0.0;
    float vibAmount = 0.0;
    float fricativeLevel = 0.5;
    bool  muteAudio = false;
    bool constrictionActive = true;
    
    float newFricFC = 0.5;
    float newAspFC = 0.5;
    float newQ = 0.5;
    float tenseness = 0.5; 
};

} // namespace PinkTrombone
