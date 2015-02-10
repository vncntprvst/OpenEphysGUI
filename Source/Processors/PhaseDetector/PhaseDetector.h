/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __PHASEDETECTOR_H_F411F29D__
#define __PHASEDETECTOR_H_F411F29D__


#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../GenericProcessor/GenericProcessor.h"

#define NUM_INTERVALS 5

/**

  Uses peaks to estimate the phase of a continuous signal.

  @see GenericProcessor, PhaseDetectorEditor

*/

class PhaseDetector : public GenericProcessor

{
public:

    PhaseDetector();
    ~PhaseDetector();

    void process(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void setParameter(int parameterIndex, float newValue);

    AudioProcessorEditor* createEditor();

    bool hasEditor() const
    {
        return false;
    }

    bool enable();

    void updateSettings();

    void addModule();
    void setActiveModule(int);

private:

    enum ModuleType
    {
        NONE, PEAK, FALLING_ZERO, TROUGH, RISING_ZERO
    };

    enum PhaseType
    {
        NO_PHASE, RISING_POS, FALLING_POS, FALLING_NEG, RISING_NEG
    };

    struct DetectorModule
    {

        int inputChan;
        int gateChan;
        int outputChan;
        bool isActive;
        float lastSample;
        int samplesSinceTrigger;
        bool wasTriggered;
        ModuleType type;
        PhaseType phase;
    };

    Array<DetectorModule> modules;

    int activeModule;

    void handleEvent(int eventType, MidiMessage& event, int sampleNum);

    bool risingPos, risingNeg, fallingPos, fallingNeg;

    void estimateFrequency();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaseDetector);

};

#endif  // __PHASEDETECTOR_H_F411F29D__
