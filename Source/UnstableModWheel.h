/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

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
**/
/*
  ==============================================================================

    UnstableModWheel.h
    Created: 2 Mar 2021 7:48:49pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once
#include "NoteEffectBase.h"
#include "IDrawableModule.h"
#include "Slider.h"
#include "ModulationChain.h"
#include "Transport.h"
#include "UnstablePitch.h"

class UnstableModWheel : public NoteEffectBase, public IDrawableModule, public IFloatSliderListener, public IAudioPoller
{
public:
   UnstableModWheel();
   virtual ~UnstableModWheel();
   static IDrawableModule* Create() { return new UnstableModWheel(); }
   static bool AcceptsAudio() { return false; }
   static bool AcceptsNotes() { return true; }
   static bool AcceptsPulses() { return false; }

   void CreateUIControls() override;
   void Init() override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }

   //INoteReceiver
   void PlayNote(NoteMessage note) override;

   //IAudioPoller
   void OnTransportAdvanced(float amount) override;

   void FloatSliderUpdated(FloatSlider* slider, float oldVal, double time) override;
   void CheckboxUpdated(Checkbox* checkbox, double time) override;

   void LoadLayout(const ofxJSONElement& moduleInfo) override;
   void SetUpFromSaveData() override;

   bool IsEnabled() const override { return mEnabled; }

private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override
   {
      width = mWidth;
      height = mHeight;
   }

   void FillModulationBuffer(double time, int voiceIdx);

   UnstablePerlinModulation mPerlin{ .2, .1, 0 };
   FloatSlider* mAmountSlider{ nullptr };
   FloatSlider* mWarbleSlider{ nullptr };
   FloatSlider* mNoiseSlider{ nullptr };
   float mWidth{ 200 };
   float mHeight{ 20 };
   std::array<bool, kNumVoices> mIsVoiceUsed{ false };
   std::array<int, 128> mPitchToVoice{};
   int mVoiceRoundRobin{ 0 };

   Modulations mModulation{ false };
};
