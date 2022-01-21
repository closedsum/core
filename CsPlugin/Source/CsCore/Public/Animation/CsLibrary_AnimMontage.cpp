// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_AnimMontage.h"
#include "CsCore.h"

// Library
#include "Object/CsLibrary_Object.h"
// Blueprint
#include "Animation/AnimMontage.h"

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
}