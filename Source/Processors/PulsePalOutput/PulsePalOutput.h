/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2014 Open Ephys

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

#ifndef __PULSEPALOUTPUT_H_A8BF66D6__
#define __PULSEPALOUTPUT_H_A8BF66D6__

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../GenericProcessor/GenericProcessor.h"
#include "PulsePalOutputEditor.h"
#include "../Serial/PulsePal.h"

/**

  Allows the signal chain to send outputs to the Pulse Pal
  from Lucid Biosystems (www.lucidbiosystems.com)

  @see GenericProcessor, PulsePalOutputEditor, PulsePal

*/

class PulsePalOutput : public GenericProcessor

{
public:

    PulsePalOutput();
    ~PulsePalOutput();

    void process(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void setParameter(int parameterIndex, float newValue);

    void handleEvent(int eventType, MidiMessage& event, int sampleNum);

    AudioProcessorEditor* createEditor();

    bool isSink()
    {
        return true;
    }

private:

    Array<int> channelTtlTrigger;
    Array<int> channelTtlGate;
    Array<bool> channelState;

    int channelToChange;

    PulsePal pulsePal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PulsePalOutput);

};



#endif  // __PULSEPALOUTPUT_H_A8BF66D6__
