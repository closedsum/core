// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsLibrary_Sound.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Audio
#include "AudioDeviceManager.h"
#include "AudioDevice.h"
// World
#include "Engine/World.h"

namespace NCsSound
{
	bool FLibrary::CanPlayChecked(const FString& Context, const UObject* WorldContext)
	{
		return true;
	}

	bool FLibrary::CanPlay(const UObject* WorldContext)
	{
		if (!WorldContext)
			return false;

		if (!GEngine)
			return false;

		if (!GEngine->UseSound())
			return false;

		UWorld* World = WorldContext->GetWorld();

		if (!World)
			return false;

		if (!World->bAllowAudioPlayback)
			return false;

		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		if (!AudioDevice.IsValid())
			return false;
		return true;
	}

	void FLibrary::SetMixClassOverrideChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume /*=1.0f*/, const float& Pitch /*=1.0f*/, const float& FadeInTime /*=1.0f*/, bool bApplyToChildren /*=true*/)
	{
		check(CanPlayChecked(Context, WorldContext));

		CS_IS_PTR_NULL_CHECKED(SoundMix)
		
		CS_IS_PTR_NULL_CHECKED(SoundClass)

		UWorld* World				   = WorldContext->GetWorld();
		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, Volume, Pitch, FadeInTime, bApplyToChildren);
	}

	void FLibrary::PushMixModifierChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix)
	{
		check(CanPlayChecked(Context, WorldContext));

		CS_IS_PTR_NULL_CHECKED(SoundMix)

		UWorld* World				   = WorldContext->GetWorld();
		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		AudioDevice->PushSoundMixModifier(SoundMix);
	}
		
	void FLibrary::SetAndPushMixClassOverrideChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume /*=1.0f*/, const float& Pitch /*=1.0f*/, const float& FadeInTime /*=1.0f*/, bool bApplyToChildren /*=true*/)
	{
		check(CanPlayChecked(Context, WorldContext));

		CS_IS_PTR_NULL_CHECKED(SoundMix)

		CS_IS_PTR_NULL_CHECKED(SoundClass)

		UWorld* World				   = WorldContext->GetWorld();
		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, Volume, Pitch, FadeInTime, bApplyToChildren);
		AudioDevice->PushSoundMixModifier(SoundMix);
	}
}