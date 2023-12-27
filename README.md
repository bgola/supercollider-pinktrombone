# supercollider-pinktrombone

SuperCollider port of https://dood.al/pinktrombone/

Based on many ports around, inlcuding:

- https://github.com/VegaDeftwing/PinkTromboneVCV
- https://github.com/giuliomoro/pink-trombone
- https://github.com/zakaton/Pink-Trombone
- https://github.com/jamesstaub/pink-trombone-osc
- https://github.com/cutelabnyc/pink-trombone-plugin

This is a work in progress, I still would like to expose the internal parameters in a nicer way.

Also, some modulations / parameter values might end up in glitchy behaviour.

## Example

```supercollider
// Modulate everything
s.boot;

Ndef(\pinkt, {
    PinkTrombone.ar(
        BPF.ar(WhiteNoise.ar(LFNoise1.kr(0.4).range(0,1)), 3000),
        LFNoise0.kr(4).exprange(20,2000),
        LFNoise1.kr(3.3).range(0,1),
        LFNoise0.kr(1.6).range(5,50), 
        LFNoise1.kr(1.3).range(1.6,8), 
        LFNoise1.kr(3).range(0,1), 
        LFNoise1.kr(1.2).range(0.6,1), 
        LFNoise1.kr(1).range(0.6,1));
}).play;
```

### Requirements

- CMake >= 3.12
- SuperCollider source code

### Building

Clone the project:

    git clone https://github.com/bgola/supercollider-pinktrombone
    cd supercollider-pinktrombone
    mkdir build
    cd build

Then, use CMake to configure and build it:

    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    cmake --build . --config Release --target install

You may want to manually specify the install location in the first step to point it at your
SuperCollider extensions directory: add the option `-DCMAKE_INSTALL_PREFIX=/path/to/extensions`.

It's expected that the SuperCollider repo is cloned at `../supercollider` relative to this repo. If
it's not: add the option `-DSC_PATH=/path/to/sc/source`.

## License

As noted by https://github.com/VegaDeftwing/PinkTromboneVCV the original Pink Trombone C++ Code is MIT License'd & Copyright (c) 2021 cutelabnyc, available at https://github.com/cutelabnyc/pink-trombone-cpp

The original Pink Trombone (Javascript) is Copyright 2017 Neil Thapen and also MIT licensed. It is available at https://dood.al/pinktrombone/.

However, following PinkTromboneVCV this project is also GPLv3.
