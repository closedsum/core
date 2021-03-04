// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
class USoundMix;
class USoundClass;

namespace NCsSound
{
	/**
	* Library of function related to Sound
	*/
	struct CSCORE_API FLibrary
	{
	public:

		/**
		* Check whether it is possible to play any audio with checks
		* (i.e. World is valid, AudioDevice is valid, ... etc)
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Whether it is possible to play any audio.
		*/
		static bool CanPlayChecked(const FString& Context, UObject* WorldContext);

		/**
		* Check whether it is possible to play any audio.
		* (i.e. World is valid, AudioDevice is valid, ... etc)
		* 
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Whether it is possible to play any audio.
		*/
		static bool CanPlay(UObject* WorldContext);

		/** 
		* Overrides the sound class adjuster in the given sound mix. 
		* If the sound class does not exist in the input sound mix, 
		* the sound class adjustment will be added to the sound mix.
		*
		* @param Context			The calling context.
		* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
		* @param SoundMix			The sound mix to modify.
		* @param SoundClass			The sound class to override (or add) in the sound mix.
		* @param Volume				The volume scale to set the sound class adjuster to.
		* @param Pitch				The pitch scale to set the sound class adjuster to.
		* @param FadeInTime			The interpolation time to use to go from the current 
		*							sound class adjuster values to the new values.
		* @param bApplyToChildren	Whether or not to apply this override to the sound class' 
									children or to just the specified sound class.
		*/
		static void SetMixClassOverrideChecked(const FString& Context, UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume = 1.0f, const float& Pitch = 1.0f, const float& FadeInTime = 1.0f, bool bApplyToChildren = true);

		/** 
		* Push a sound mix modifier onto the audio system
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param SoundMix
		*/
		static void PushMixModifierChecked(const FString& Context, UObject* WorldContext, USoundMix* SoundMix);

		/**
		* Overrides the sound class adjuster in the given sound mix.
		* If the sound class does not exist in the input sound mix,
		* the sound class adjustment will be added to the sound mix.
		* Push a sound mix modifier onto the audio system
		*
		* @param Context			The calling context.
		* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
		* @param SoundMix			The sound mix to modify.
		* @param SoundClass			The sound class to override (or add) in the sound mix.
		* @param Volume				The volume scale to set the sound class adjuster to.
		* @param Pitch				The pitch scale to set the sound class adjuster to.
		* @param FadeInTime			The interpolation time to use to go from the current
		*							sound class adjuster values to the new values.
		* @param bApplyToChildren	Whether or not to apply this override to the sound class'
									children or to just the specified sound class.
		*/
		static void SetAndPushMixClassOverrideChecked(const FString& Context, UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume = 1.0f, const float& Pitch = 1.0f, const float& FadeInTime = 1.0f, bool bApplyToChildren = true);
	};
}