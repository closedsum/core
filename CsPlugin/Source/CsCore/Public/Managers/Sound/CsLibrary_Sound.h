// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Sound/CsTypes_Library_Sound.h"
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsLog.h"
#pragma once

class USoundBase;
class UObject;
struct FCsRoutine;
class USoundMix;
class USoundClass;

namespace NCsSound
{
	/**
	* Library of function related to Sound
	*/
	struct CSCORE_API FLibrary final
	{
	private:
		FLibrary();

		FLibrary(const FLibrary&) = delete;
		FLibrary(FLibrary&&) = delete;
	public:
		~FLibrary();

		FORCEINLINE static FLibrary& Get()
		{
			static FLibrary Instance;
			return Instance;
		}

	// Load
	#pragma region
	public:

		/**
		* Load a SoundBase at the given Path.
		* 
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the SoundBase to load.
		* @param Log
		* return			SoundBase.
		*/
		static USoundBase* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a SoundBase at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the SoundBase to load.
		* @param Log
		* return			SoundBase.
		*/
		static USoundBase* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	// Spawn
	#pragma region
	private:

	#define ParamsManagerType NCsSound::NSpawn::NParams::FManager
	#define ParamsResourceType NCsSound::NSpawn::NParams::FResource
	#define ParamsType NCsSound::NSpawn::NParams::FParams

		ParamsManagerType Manager_SpawnParams;

	public:

		FORCEINLINE ParamsResourceType* AllocateSpawnParams() { return Manager_SpawnParams.Allocate(); }

		FORCEINLINE void DeallocateSpawnParams(ParamsResourceType* Resource) { Manager_SpawnParams.Deallocate(Resource); }

	public:


		/**
		* Spawn an Sound with the given params.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param ParamsType
		* return
		*/
		static FCsRoutineHandle SpawnChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params);

		/**
		* Safely spawn an Sound with the given params.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param ParamsType
		* @param Log
		* return				Handle to the coroutine if the souind is spawned via a coroutine.
		*/
		static FCsRoutineHandle SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

		static char Spawn_Internal(FCsRoutine* R);

		static void Spawn_Internal_OnEnd(FCsRoutine* R);

	#undef ParamsManagerType
	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Spawn

	public:

		/**
		* Check whether it is possible to play any audio with checks
		* (i.e. World is valid, AudioDevice is valid, ... etc)
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Whether it is possible to play any audio.
		*/
		static bool CanPlayChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Check whether it is possible to play any audio.
		* (i.e. World is valid, AudioDevice is valid, ... etc)
		* 
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Whether it is possible to play any audio.
		*/
		static bool CanPlay(const UObject* WorldContext);

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
		static void SetMixClassOverrideChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume = 1.0f, const float& Pitch = 1.0f, const float& FadeInTime = 1.0f, bool bApplyToChildren = true);

		/** 
		* Push a sound mix modifier onto the audio system
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param SoundMix
		*/
		static void PushMixModifierChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix);

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
		static void SetAndPushMixClassOverrideChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume = 1.0f, const float& Pitch = 1.0f, const float& FadeInTime = 1.0f, bool bApplyToChildren = true);
	};
}