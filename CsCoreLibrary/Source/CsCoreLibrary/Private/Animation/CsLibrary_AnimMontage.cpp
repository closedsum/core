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
	#define AnimInstanceLibrary NCsAnimInstance::FLibrary

	// Load
	#pragma region

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	UAnimMontage* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UAnimMontage>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UAnimMontage* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<UAnimMontage>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	// Length
	#pragma region
	
	float FLibrary::GetPositionByPercentChecked(const FString& Context, UAnimMontage* Anim, const float& Percent)
	{
		CS_IS_PENDING_KILL_CHECKED(Anim)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Percent, 0.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Percent, 1.0f)

		const float Length = Anim->CalculateSequenceLength();
		return Percent * Length;
	}

	#pragma endregion Length

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

		if (Params.GetbBlendIn())
			return AnimInstance->Montage_PlayWithBlendIn(Params.GetAnim(), Params.GetBlendIn(), Params.GetPlayRate(), EMontagePlayReturnType::Duration, Params.GetTimeToStartAt(), Params.GetbStopAll());
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

	float FLibrary::SafePlay(const FString& Context, UPrimitiveComponent* Component, const FCsAnimMontage_PlayByPathParams& Params, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		CS_IS_VALID_RET_VALUE(Params, -1.0f)

		UAnimMontage* Anim = SafeLoad(Context, Params.Path, Log);

		if (!Anim)
			return -1.0f;

		if (!Params.bPlayOverExisting)
		{
			if (!SafeIsPlaying(Context, Component, Anim, OutSuccess, Log))
				return -1.0f;
		}

		UAnimInstance* AnimInstance = AnimInstanceLibrary::GetSafe(Context, Component, OutSuccess, Log);

		if (!AnimInstance)
			return -1.0f;
		return AnimInstance->Montage_Play(Anim, Params.PlayRate, EMontagePlayReturnType::Duration, Params.TimeToStartAt, Params.bStopAll);
	}

	float FLibrary::ConditionalPlayChecked(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params)
	{
		if (IsPlayingChecked(Context, Component, Params.GetAnim()))
			return Params.GetAnim()->CalculateSequenceLength();
		return PlayChecked(Context, Component, Params.GetAnim());
	}

	#undef ParamsType

	#pragma endregion Play

	// Pause
	#pragma region
	
	void FLibrary::PauseChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim)
	{
		check(IsPlayingChecked(Context, Component, Anim));
		AnimInstanceLibrary::GetChecked(Context, Component)->Montage_Pause(Anim);
	}

	#pragma endregion Pause

	// SetPosition
	#pragma region

	#define ParamsType NCsAnimMontage::NSetPosition::FParams

	float FLibrary::SetPositionChecked(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params)
	{
		CS_IS_VALID_CHECKED(Params);

		if (Params.GetbPlay())
			PlayChecked(Context, Component, ParamsType::MakePlayParams(Params));
		if (Params.GetbPause())
			PauseChecked(Context, Component, Params.GetAnim());

		// Time
		if (Params.GetPositionType() == NCsAnimMontage::ESetPosition::Time)
		{
			AnimInstanceLibrary::GetChecked(Context, Component)->Montage_SetPosition(Params.GetAnim(), Params.GetNewPosition());
			return Params.GetNewPosition();
		}
		// Percent
		if (Params.GetPositionType() == NCsAnimMontage::ESetPosition::Percent)
		{
			const float NewPosition = GetPositionByPercentChecked(Context, Params.GetAnim(), Params.GetNewPositionAsPercent());

			AnimInstanceLibrary::GetChecked(Context, Component)->Montage_SetPosition(Params.GetAnim(), NewPosition);
			return NewPosition;
		}
		checkf(0, TEXT("%s: PositionType: %s is NOT Supported."), *Context, NCsAnimMontage::EMSetPosition::Get().ToChar(Params.GetPositionType()));
		return 0.0f;
	}

	float FLibrary::ConditionalSetPositionChecked(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params)
	{
		CS_IS_VALID_CHECKED(Params);

		if (Params.GetbPlay())
			ConditionalPlayChecked(Context, Component, ParamsType::MakePlayParams(Params));
		if (Params.GetbPause())
			PauseChecked(Context, Component, Params.GetAnim());

		// Time
		if (Params.GetPositionType() == NCsAnimMontage::ESetPosition::Time)
		{
			AnimInstanceLibrary::GetChecked(Context, Component)->Montage_SetPosition(Params.GetAnim(), Params.GetNewPosition());
			return Params.GetNewPosition();
		}
		// Percent
		if (Params.GetPositionType() == NCsAnimMontage::ESetPosition::Percent)
		{
			const float NewPosition = GetPositionByPercentChecked(Context, Params.GetAnim(), Params.GetNewPositionAsPercent());

			AnimInstanceLibrary::GetChecked(Context, Component)->Montage_SetPosition(Params.GetAnim(), NewPosition);
			return NewPosition;
		}
		checkf(0, TEXT("%s: PositionType: %s is NOT Supported."), *Context, NCsAnimMontage::EMSetPosition::Get().ToChar(Params.GetPositionType()));
		return 0.0f;
	}

	#undef ParamsType

	#pragma endregion SetPosition

	#undef LogLevel
	#undef AnimInstanceLibrary
}