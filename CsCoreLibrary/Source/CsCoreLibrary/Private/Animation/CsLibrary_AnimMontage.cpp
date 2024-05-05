// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_AnimMontage.h"

// Library
#include "Animation/CsLibrary_AnimInstance.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Anim
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimTypes.h"

namespace NCsAnimMontage
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define ObjectLibrary NCsObject::FLibrary
	#define PropertyLibrary NCsProperty::FLibrary
	#define AnimInstanceLibrary NCsAnimInstance::FLibrary

	// Load
	#pragma region

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		return ObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		return ObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UAnimMontage* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel)
	{
		return PropertyLibrary::GetObjectPropertyValueByPath<UAnimMontage>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	// Play
	#pragma region

	bool FLibrary::IsPlayingChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim)
	{
		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetChecked(Context, Component);

		CS_IS_PENDING_KILL_CHECKED(Anim)

		if (FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(Anim))
			return MontageInstance->IsPlaying();
		return false;
	}

	bool FLibrary::SafeIsPlaying(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, bool& OutSuccess, LogLevel)
	{
		OutSuccess					= false;
		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetSafe(Context, Component, OutSuccess, Log);

		if (!AnimInstance)
			return false;

		CS_IS_PENDING_KILL(Anim)

		OutSuccess = true;

		if (FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(Anim))
			return MontageInstance->IsPlaying();
		return false;
	}

	#define ParamsType NCsAnimMontage::NPlay::FParams

	float FLibrary::PlayChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, const float& PlayRate /*=1.0f*/, const float& TimeToStartMontageAt /*=0.0f*/)
	{
		return AnimInstanceLibrary::GetChecked(Context, Component)->Montage_Play(Anim, PlayRate, EMontagePlayReturnType::Duration, TimeToStartMontageAt);
	}

	float FLibrary::PlayChecked(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params)
	{
		CS_IS_VALID_CHECKED(Params);

		if (!Params.ShouldPlayOverExisting())
		{
			checkf(!IsPlayingChecked(Context, Component, Params.GetAnim()), TEXT("%s: Anim: %s is ALREADY playing."), *Context, *(Params.GetAnim()->GetName()));
		}

		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetChecked(Context, Component);

		return AnimInstance->Montage_Play(Params.GetAnim(), Params.GetPlayRate(), EMontagePlayReturnType::Duration, Params.GetTimeToStartAt(), Params.GetbStopAll());
	}

	float FLibrary::SafePlay(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		CS_IS_VALID_RET_VALUE(Params, -1.0f)

		if (!Params.ShouldPlayOverExisting())
		{
			if (!SafeIsPlaying(Context, Component, Params.GetAnim(), OutSuccess, Log))
				return -1.0f;
		}

		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetSafe(Context, Component, OutSuccess, Log);

		if (!AnimInstance)
			return -1.0f;
		return AnimInstance->Montage_Play(Params.GetAnim(), Params.GetPlayRate(), EMontagePlayReturnType::Duration, Params.GetTimeToStartAt(), Params.GetbStopAll());
	}

	#undef ParamsType

	#pragma endregion Play

	#undef LogLevel
	#undef ObjectLibrary
	#undef PropertyLibrary
	#undef AnimInstanceLibrary
}