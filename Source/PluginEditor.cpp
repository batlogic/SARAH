#include "PluginProcessor.h"
#include "PluginEditor.h"

SARAHAudioProcessorEditor::SARAHAudioProcessorEditor (SARAHAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processor (p)
    , gOsc1("gOsc1", TRANS("Oscillator 1"))
    , gPeg1("gPeg1", TRANS("Pitch EG"))
    , gOsc2("gOsc2", TRANS("Oscillator 2"))
    , gPeg2("gPeg2", TRANS("Pitch EG"))
    , gFlt1("gFlt1", TRANS("Harmonic Shaping 1"))
    , gFeg1("gFeg1", TRANS("Harmonic EG"))
    , gFlt2("gFlt2", TRANS("Harmonic Shaping 2"))
    , gFeg2("gFeg2", TRANS("Harmonic EG"))
    , gPlfo("gPlfo", TRANS("Pitch LFO"))
    , gHlfo("gHlfo", TRANS("Harmonic LFO"))
    , gAeg("gAeg", TRANS("Amplitude EG"))
    , gMaster("gMaster", TRANS("Master"))
    , lblOsc1Pitch("lblOsc1Pitch", TRANS("Pitch"))
    , lblOsc1Detune("lblOsc1Detune", TRANS("Detune"))
    , lblOsc1PitchEgAttack("lblOsc1PitchEgAttack", TRANS("A.sec"))
    , lblOsc1PitchEgSustain("lblOsc1PitchEgSustain", TRANS("S.semi"))
    , lblOsc1PitchEgRelease("lblOsc1PitchEgRelease", TRANS("R.sec"))
    , lblOsc2Pitch("lblOsc2Pitch", TRANS("Pitch"))
    , lblOsc2Detune("lblOsc2Detune", TRANS("Detune"))
    , lblOsc2PitchEgAttack("lblOsc2PitchEgAttack", TRANS("A.sec"))
    , lblOsc2PitchEgSustain("lblOsc2PitchEgSustain", TRANS("S.semi"))
    , lblOsc2PitchEgRelease("lblOsc2PitchEgRelease", TRANS("R.sec"))
    , lblFlt1Cutoff("lblFlt1Cutoff", TRANS("Cutoff%"))
    , lblFlt1Slope("lblFlt1Slope", TRANS("dB/oct"))
    , lblFlt1EnvAmt("lblFlt1EnvAmt", TRANS("Env.amt"))
    , lblFlt1EgAttack("lblFlt1EgAttack", TRANS("A.sec"))
    , lblFlt1EgDecay("lblFlt1EgDecay", TRANS("D.sec"))
    , lblFlt1EgSustain("lblFlt1EgSustain", TRANS("S.%"))
    , lblFlt1EgRelease("lblFlt1EgRelease", TRANS("R.sec"))
    , lblFlt2Cutoff("lblFlt2Cutoff", TRANS("Cutoff%"))
    , lblFlt2Slope("lblFlt2Slope", TRANS("dB/oct"))
    , lblFlt2EnvAmt("lblFlt2EnvAmt", TRANS("Env.amt"))
    , lblFlt2EgAttack("lblFlt2EgAttack", TRANS("A.sec"))
    , lblFlt2EgDecay("lblFlt2EgDecay", TRANS("D.sec"))
    , lblFlt2EgSustain("lblFlt2EgSustain", TRANS("S.%"))
    , lblFlt2EgRelease("lblFlt2EgRelease", TRANS("R.sec"))
    , lblPitchLfoFreq("lblPitchLfoFreq", TRANS("Freq.Hz"))
    , lblPitchLfoAmount("lblPitchLfoAmount", TRANS("Cents"))
    , lblFilterLfoFreq("lblFilterLfoFreq", TRANS("Freq.Hz"))
    , lblFilterLfoAmount("lblFilterLfoAmount", TRANS("Amt.%"))
    , lblMasterVol("lblMasterVol", TRANS("Volume"))
    , lblOscBal("lblOscBal", TRANS("Osc.Bal"))
    , lblPitchBendUp("lblPitchBendUp", TRANS("PB.Up"))
    , lblPitchBendDown("lblPitchBendDown", TRANS("PB.Dn"))
    , lblAmpEgAttack("lblAmpEgAttack", TRANS("A.sec"))
    , lblAmpEgDecay("lblAmpEgDecay", TRANS("D.sec"))
    , lblAmpEgSustain("lblAmpEgSustain", TRANS("S.%"))
    , lblAmpEgRelease ("lblAmpEgRelease", TRANS("R.sec"))
{
    setSize (870, 450);
    p.addChangeListener(this);

    addAndMakeVisible(gOsc1);
    addAndMakeVisible(gPeg1);
    addAndMakeVisible(gOsc2);
    addAndMakeVisible(gPeg2);
    addAndMakeVisible(gFlt1);
    addAndMakeVisible(gFeg1);
    addAndMakeVisible(gFlt2);
    addAndMakeVisible(gFeg2);
    addAndMakeVisible(gPlfo);
    addAndMakeVisible(gHlfo);
    addAndMakeVisible(gAeg);
    addAndMakeVisible(gMaster);

    auto initCombo = [this](WaveformComboBox& combo)
    {
        addAndMakeVisible(combo);
        combo.setEditableText(false);
        combo.setJustificationType(Justification::centredLeft);
        combo.setTextWhenNothingSelected("");
        combo.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
        combo.addItem(TRANS("Sine"), 1);
        combo.addItem(TRANS("Triangle"), 2);
        combo.addItem(TRANS("Square"), 3);
        combo.addItem(TRANS("Sawtooth"), 4);
        combo.addListener(this);
    };

    initCombo(cbOsc1);
    initCombo(cbOsc2);
    initCombo(cbPlfo);
    initCombo(cbHlfo);

    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setJustificationType(Justification::horizontallyCentred);
        label.setEditable(false, false, false);
    };

    initLabel(lblOsc1Pitch);
    initLabel(lblOsc1Detune);
    initLabel(lblOsc1PitchEgAttack);
    initLabel(lblOsc1PitchEgSustain);
    initLabel(lblOsc1PitchEgRelease);
    initLabel(lblOsc2Pitch);
    initLabel(lblOsc2Detune);
    initLabel(lblOsc2PitchEgAttack);
    initLabel(lblOsc2PitchEgSustain);
    initLabel(lblOsc2PitchEgRelease);
    initLabel(lblFlt1Cutoff);
    initLabel(lblFlt1Slope);
    initLabel(lblFlt1EnvAmt);
    initLabel(lblFlt1EgAttack);
    initLabel(lblFlt1EgDecay);
    initLabel(lblFlt1EgSustain);
    initLabel(lblFlt1EgRelease);
    initLabel(lblFlt2Cutoff);
    initLabel(lblFlt2Slope);
    initLabel(lblFlt2EnvAmt);
    initLabel(lblFlt2EgAttack);
    initLabel(lblFlt2EgDecay);
    initLabel(lblFlt2EgSustain);
    initLabel(lblFlt2EgRelease);
    initLabel(lblPitchLfoFreq);
    initLabel(lblPitchLfoAmount);
    initLabel(lblFilterLfoFreq);
    initLabel(lblFilterLfoAmount);
    initLabel(lblMasterVol);
    initLabel(lblOscBal);
    initLabel(lblPitchBendUp);
    initLabel(lblPitchBendDown);
    initLabel(lblAmpEgAttack);
    initLabel(lblAmpEgDecay);
    initLabel(lblAmpEgSustain);
    initLabel(lblAmpEgRelease);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::Rotary);
        slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        slider.addListener(this);
    };

    initSlider(slOsc1Pitch); slOsc1Pitch.setRange(-24, 24, 1);
    initSlider(slOsc2Pitch); slOsc2Pitch.setRange(-24, 24, 1);
    initSlider(slOsc1Detune); slOsc1Detune.setRange(-50, 50, 0);
    initSlider(slOsc2Detune); slOsc2Detune.setRange(-50, 50, 0);
    initSlider(slOsc1PitchEgAttack); slOsc1PitchEgAttack.setRange(0, 10, 0);
    initSlider(slOsc1PitchEgSustain); slOsc1PitchEgSustain.setRange(-12, 12, 0);
    initSlider(slOsc1PitchEgRelease); slOsc1PitchEgRelease.setRange(0, 10, 0);
    initSlider(slOsc2PitchEgAttack); slOsc2PitchEgAttack.setRange(0, 10, 0);
    initSlider(slOsc2PitchEgSustain); slOsc2PitchEgSustain.setRange(-12, 12, 0);
    initSlider(slOsc2PitchEgRelease); slOsc2PitchEgRelease.setRange(0, 10, 0);
    initSlider(slFlt1Cutoff); slFlt1Cutoff.setRange(0, 100, 0); slFlt1Cutoff.setScale(100);
    initSlider(slFlt1Slope); slFlt1Slope.setRange(6, 48, 6);
    initSlider(slFlt1EnvAmt); slFlt1EnvAmt.setRange(0, 100, 0); slFlt1EnvAmt.setScale(100);
    initSlider(slFlt1EgAttack); slFlt1EgAttack.setRange(0, 10, 0);
    initSlider(slFlt1EgDecay); slFlt1EgDecay.setRange(0, 10, 0);
    initSlider(slFlt1EgSustain); slFlt1EgSustain.setRange(0, 100, 0); slFlt1EgSustain.setScale(100);
    initSlider(slFlt1EgRelease); slFlt1EgRelease.setRange(0, 10, 0);
    initSlider(slFlt2Cutoff); slFlt2Cutoff.setRange(0, 100, 0); slFlt2Cutoff.setScale(100);
    initSlider(slFlt2Slope); slFlt2Slope.setRange(6, 48, 6);
    initSlider(slFlt2EnvAmt); slFlt2EnvAmt.setRange(0, 100, 0); slFlt2EnvAmt.setScale(100);
    initSlider(slFlt2EgAttack); slFlt2EgAttack.setRange(0, 10, 0);
    initSlider(slFlt2EgDecay); slFlt2EgDecay.setRange(0, 10, 0);
    initSlider(slFlt2EgSustain); slFlt2EgSustain.setRange(0, 100, 0); slFlt2EgSustain.setScale(100);
    initSlider(slFlt2EgRelease); slFlt2EgRelease.setRange(0, 10, 0);
    initSlider(slPitchLfoFreq); slPitchLfoFreq.setRange(0.1, 10, 0);
    initSlider(slPitchLfoAmount); slPitchLfoAmount.setRange(0, 100, 0);
    initSlider(slFilterLfoFreq); slPitchLfoFreq.setRange(0.1, 10, 0);
    initSlider(slFilterLfoAmount); slFilterLfoAmount.setRange(0, 100, 0); slFilterLfoAmount.setScale(100);
    initSlider(slMasterVol); slMasterVol.setRange(0, 100, 0); slMasterVol.setScale(100);
    initSlider(slOscBal); slOscBal.setRange(0, 1, 0);
    initSlider(slPitchBendUp); slPitchBendUp.setRange(0, 12, 1);
    initSlider(slPitchBendDown); slPitchBendDown.setRange(0, 12, 1);
    initSlider(slAmpEgAttack); slAmpEgAttack.setRange(0, 10, 0);
    initSlider(slAmpEgDecay); slAmpEgDecay.setRange(0, 10, 0);
    initSlider(slAmpEgSustain); slAmpEgSustain.setRange(0, 100, 0); slAmpEgSustain.setScale(100);
    initSlider(slAmpEgRelease); slAmpEgRelease.setRange(0, 10, 0);

    changeListenerCallback(0);  // set all control pointers
}

SARAHAudioProcessorEditor::~SARAHAudioProcessorEditor()
{
    processor.removeChangeListener(this);
}

void SARAHAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colour(0xff323e44));
}

void SARAHAudioProcessorEditor::resized()
{
    const int leftOffset = 14;
    const int groupWidth = 270;
    const int cboxWidth = 100;
    const int egLeftOffset = 20;
    const int egWidth = 230;
    const int groupHorizontalGap = 15;
    const int slLeftOffset = 38;
    const int slLeftAdvance = 52;
    const int lblWidth = 90;

    const int topOffset1 = 12;
    const int largeGroupHeight = 180;
    const int smallGroupHeight = 80;
    const int middleGap = 60;
    const int topOffset2 = topOffset1 + largeGroupHeight + middleGap;
    const int egTopOffset = 80;
    const int egHeight = 84;
    const int groupVerticalGap = 20;
    const int cbTopOffset = 30;
    const int cbHeight = 24;
    const int slTopOffset = 12;
    const int slSize = 56;
    const int lblTopOffset = 62;
    const int lblHeight = 10;

    int left, top, slLeftCtr;

    // First column: OSC1
    left = leftOffset;
    top = topOffset1;
    gOsc1.setBounds(left, top, groupWidth, largeGroupHeight);
    cbOsc1.setBounds(left + egLeftOffset, top + cbTopOffset, cboxWidth, cbHeight);
    slLeftCtr = left + egLeftOffset + cboxWidth + slLeftOffset;
    slOsc1Pitch.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblOsc1Pitch.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slOsc1Detune.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblOsc1Detune.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    gPeg1.setBounds(left + egLeftOffset, top + egTopOffset, egWidth, egHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slOsc1PitchEgAttack.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblOsc1PitchEgAttack.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += 2 * slLeftAdvance;
    slOsc1PitchEgSustain.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblOsc1PitchEgSustain.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slOsc1PitchEgRelease.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblOsc1PitchEgRelease.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);

    // First column: OSC2
    top = topOffset2;
    gOsc2.setBounds(left, top, groupWidth, largeGroupHeight);
    cbOsc2.setBounds(left + egLeftOffset, top + cbTopOffset, cboxWidth, cbHeight);
    slLeftCtr = left + egLeftOffset + cboxWidth + slLeftOffset;
    slOsc2Pitch.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblOsc2Pitch.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slOsc2Detune.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblOsc2Detune.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    gPeg2.setBounds(left + egLeftOffset, top + egTopOffset, egWidth, egHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slOsc2PitchEgAttack.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblOsc2PitchEgAttack.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += 2 * slLeftAdvance;
    slOsc2PitchEgSustain.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblOsc2PitchEgSustain.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slOsc2PitchEgRelease.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblOsc2PitchEgRelease.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);

    // Second column: HS1
    left += groupWidth + groupHorizontalGap;
    top = topOffset1;
    gFlt1.setBounds(left, top, groupWidth, largeGroupHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slFlt1Cutoff.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFlt1Cutoff.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += 1.5 * slLeftAdvance;
    slFlt1Slope.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFlt1Slope.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += 1.5 * slLeftAdvance;
    slFlt1EnvAmt.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFlt1EnvAmt.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    gFeg1.setBounds(left + egLeftOffset, top + egTopOffset, egWidth, egHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slFlt1EgAttack.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt1EgAttack.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFlt1EgDecay.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt1EgDecay.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFlt1EgSustain.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt1EgSustain.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFlt1EgRelease.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt1EgRelease.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);

    // Second column: HS2
    top = topOffset2;
    gFlt2.setBounds(left, top, groupWidth, largeGroupHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slFlt2Cutoff.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFlt2Cutoff.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += 1.5 * slLeftAdvance;
    slFlt2Slope.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFlt2Slope.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += 1.5 * slLeftAdvance;
    slFlt2EnvAmt.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFlt2EnvAmt.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    gFeg2.setBounds(left + egLeftOffset, top + egTopOffset, egWidth, egHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slFlt2EgAttack.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt2EgAttack.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFlt2EgDecay.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt2EgDecay.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFlt2EgSustain.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt2EgSustain.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFlt2EgRelease.setBounds(slLeftCtr - slSize / 2, top + egTopOffset + slTopOffset, slSize, slSize);
    lblFlt2EgRelease.setBounds(slLeftCtr - lblWidth / 2, top + egTopOffset + lblTopOffset, lblWidth, lblHeight);

    // Third column: Pitch LFO
    left += groupWidth + groupHorizontalGap;
    top = topOffset1;
    gPlfo.setBounds(left, top, groupWidth, smallGroupHeight);
    cbPlfo.setBounds(left + egLeftOffset, top + cbTopOffset, cboxWidth, cbHeight);
    slLeftCtr = left + egLeftOffset + cboxWidth + slLeftOffset;
    slPitchLfoFreq.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblPitchLfoFreq.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slPitchLfoAmount.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblPitchLfoAmount.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);

    // Third column: Harmonic LFO
    top += smallGroupHeight + groupVerticalGap;
    gHlfo.setBounds(left, top, groupWidth, smallGroupHeight);
    cbHlfo.setBounds(left + egLeftOffset, top + cbTopOffset, cboxWidth, cbHeight);
    slLeftCtr = left + egLeftOffset + cboxWidth + slLeftOffset;
    slFilterLfoFreq.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFilterLfoFreq.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slFilterLfoAmount.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblFilterLfoAmount.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);

    // Third column: Amp EG
    top = topOffset2;
    gAeg.setBounds(left, top, groupWidth, smallGroupHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slAmpEgAttack.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblAmpEgAttack.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slAmpEgDecay.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblAmpEgDecay.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slAmpEgSustain.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblAmpEgSustain.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slAmpEgRelease.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblAmpEgRelease.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);

    // Third column: Master
    top += smallGroupHeight + groupVerticalGap;
    gMaster.setBounds(left, top, groupWidth, smallGroupHeight);
    slLeftCtr = left + egLeftOffset + slLeftOffset;
    slMasterVol.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblMasterVol.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slOscBal.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblOscBal.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slPitchBendUp.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblPitchBendUp.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
    slLeftCtr += slLeftAdvance;
    slPitchBendDown.setBounds(slLeftCtr - slSize / 2, top + slTopOffset, slSize, slSize);
    lblPitchBendDown.setBounds(slLeftCtr - lblWidth / 2, top + lblTopOffset, lblWidth, lblHeight);
}

void SARAHAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster*)
{
    SynthParameters* pParams = processor.getSound()->pParams;

    cbOsc1.setPointer(&pParams->osc1.waveform);
    cbOsc2.setPointer(&pParams->osc2.waveform);
    cbPlfo.setPointer(&pParams->pitchLFO.waveform);
    cbHlfo.setPointer(&pParams->filterLFO.waveform);

    slOsc1Pitch.setPointer(&pParams->osc1.pitchOffsetSemitones);
    slOsc1Detune.setPointer(&pParams->osc1.detuneOffsetCents);
    slOsc1PitchEgAttack.setPointer(&pParams->pitch1EG.attackTimeSeconds);
    slOsc1PitchEgSustain.setPointer(&pParams->pitch1EG.sustainLevel);
    slOsc1PitchEgRelease.setPointer(&pParams->pitch1EG.releaseTimeSeconds);

    slOsc2Pitch.setPointer(&pParams->osc2.pitchOffsetSemitones);
    slOsc2Detune.setPointer(&pParams->osc2.detuneOffsetCents);
    slOsc2PitchEgAttack.setPointer(&pParams->pitch2EG.attackTimeSeconds);
    slOsc2PitchEgSustain.setPointer(&pParams->pitch2EG.sustainLevel);
    slOsc2PitchEgRelease.setPointer(&pParams->pitch2EG.releaseTimeSeconds);

    slFlt1Cutoff.setPointer(&pParams->filter1.cutoff);
    slFlt1Slope.setPointer(&pParams->filter1.dBperOctave);
    slFlt1EnvAmt.setPointer(&pParams->filter1.envAmount);
    slFlt1EgAttack.setPointer(&pParams->filter1EG.attackTimeSeconds);
    slFlt1EgDecay.setPointer(&pParams->filter1EG.decayTimeSeconds);
    slFlt1EgSustain.setPointer(&pParams->filter1EG.sustainLevel);
    slFlt1EgRelease.setPointer(&pParams->filter1EG.releaseTimeSeconds);

    slFlt2Cutoff.setPointer(&pParams->filter2.cutoff);
    slFlt2Slope.setPointer(&pParams->filter2.dBperOctave);
    slFlt2EnvAmt.setPointer(&pParams->filter2.envAmount);
    slFlt2EgAttack.setPointer(&pParams->filter2EG.attackTimeSeconds);
    slFlt2EgDecay.setPointer(&pParams->filter2EG.decayTimeSeconds);
    slFlt2EgSustain.setPointer(&pParams->filter2EG.sustainLevel);
    slFlt2EgRelease.setPointer(&pParams->filter2EG.releaseTimeSeconds);

    slPitchLfoFreq.setPointer(&pParams->pitchLFO.freqHz);
    slPitchLfoAmount.setPointer(&pParams->pitchLFO.amount);
    slFilterLfoFreq.setPointer(&pParams->filterLFO.freqHz);
    slFilterLfoAmount.setPointer(&pParams->filterLFO.amount);
    slMasterVol.setPointer(&pParams->main.masterLevel);
    slOscBal.setPointer(&pParams->main.oscBlend);
    slPitchBendUp.setPointer(&pParams->main.pitchBendUpSemitones);
    slPitchBendDown.setPointer(&pParams->main.pitchBendDownSemitones);
    slAmpEgAttack.setPointer(&pParams->ampEG.attackTimeSeconds);
    slAmpEgDecay.setPointer(&pParams->ampEG.decayTimeSeconds);
    slAmpEgSustain.setPointer(&pParams->ampEG.sustainLevel);
    slAmpEgRelease.setPointer(&pParams->ampEG.releaseTimeSeconds);
}

void SARAHAudioProcessorEditor::comboBoxChanged(ComboBox*)
{
    processor.getSound()->parameterChanged();
}

void SARAHAudioProcessorEditor::sliderValueChanged(Slider*)
{
    processor.getSound()->parameterChanged();
}
