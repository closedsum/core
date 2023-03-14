// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_AnimMontage.h"
#include "CsCore.h"

// Library
#include "Animation/CsLibrary_AnimInstance.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Anim
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimTypes.h"

namespace NCsAnimMontage
{
	// Load
	#pragma region

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	#pragma endregion Load

	// Play
	#pragma region

	bool FLibrary::IsPlayingChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim)
	{
		typedef NCsAnimInstance::FLibrary AnimInstanceLibrary;

		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetChecked(Context, Component);

		CS_IS_PTR_NULL_CHECKED(Anim)

		if (FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(Anim))
			return MontageInstance->IsPlaying();
		return false;
	}

	void FLibrary::PlayChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, const float& PlayRate /*=1.0f*/, const float& InTimeToStartMontageAt /*=0.0f*/, const bool& bStopAllMontages /*=true*/)
	{
		checkf(!IsPlayingChecked(Context, Component, Anim), TEXT("%s: Anim: %s is ALREADY playing."), *Context, *(Anim->GetName()));

		typedef NCsAnimInstance::FLibrary AnimInstanceLibrary;

		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetChecked(Context, Component);

		AnimInstance->Montage_Play(Anim, PlayRate, EMontagePlayReturnType::MontageLength, InTimeToStartMontageAt, bStopAllMontages);
	}

	#pragma endregion Play
}