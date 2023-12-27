PinkTrombone : UGen {
	*ar { arg noiseSource=0.0, freq=400.0, tenseness=0.2, tongueIndex=30, tongueDiameter=3.5, constrictionX=0.5, constrictionY=0.5, fricativeIntens=1.0;
		if (noiseSource.rate != \audio) {
			noiseSource = K2A.ar(noiseSource);
		};
		if (freq.rate != \audio) {
			freq = K2A.ar(freq);
		};
		if (tenseness.rate != \audio) {
			tenseness = K2A.ar(tenseness);
		};
		if (tongueIndex.rate != \audio) {
			tongueIndex = K2A.ar(tongueIndex);
		};
		if (tongueDiameter.rate != \audio) {
			tongueDiameter = K2A.ar(tongueDiameter);
		};
		if (constrictionX.rate != \audio) {
			constrictionX = K2A.ar(constrictionX);
		};
	        if (constrictionY.rate != \audio) {
			constrictionY = K2A.ar(constrictionY);
		};
		if (fricativeIntens.rate != \audio) {
			fricativeIntens = K2A.ar(fricativeIntens);
		};
	
		^this.multiNew('audio', noiseSource, freq, tenseness, tongueIndex, tongueDiameter, constrictionX, constrictionY, fricativeIntens);
	}
	checkInputs {
		^this.checkValidInputs;
	}
}
