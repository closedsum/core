// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_AnimMontage.h"
#include "CsCore.h"

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
	// Load
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	#undef ObjectLibrary

	#pragma endregion Load

	// Get
	#pragma region
	
	UAnimMontage* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValueByPath<UAnimMontage>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	// Play
	#pragma region

	#define AnimInstanceLibrary NCsAnimInstance::FLibrary

	bool FLibrary::IsPlayingChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim)
	{
		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetChecked(Context, Component);

		CS_IS_PTR_NULL_CHECKED(Anim)

		if (FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(Anim))
			return MontageInstance->IsPlaying();
		return false;
	}

	void FLibrary::PlayChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, const float& PlayRate /*=1.0f*/, const float& InTimeToStartMontageAt /*=0.0f*/, const bool& bStopAllMontages /*=true*/)
	{
		checkf(!IsPlayingChecked(Context, Component, Anim), TEXT("%s: Anim: %s is ALREADY playing."), *Context, *(Anim->GetName()));

		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetChecked(Context, Component);

		AnimInstance->Montage_Play(Anim, PlayRate, EMontagePlayReturnType::MontageLength, InTimeToStartMontageAt, bStopAllMontages);
	}

	#undef AnimInstanceLibrary

	#pragma endregion Play
}