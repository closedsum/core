// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_AnimInstance.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Object.h"
// Blueprint
#include "Animation/AnimBlueprintGeneratedClass.h"

namespace NCsAnimInstance
{
	// Load
	#pragma region

	UAnimBlueprint* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UAnimBlueprint>(Context, Path, Log);
	}

	UAnimBlueprint* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UAnimBlueprint>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UAnimBlueprint* Blueprint, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (!Blueprint)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blueprint is NULL."), *Context));
			return nullptr;
		}

		TSoftObjectPtr<UAnimBlueprint> ABp(Blueprint);

		FString Path = ABp.ToSoftObjectPath().ToString();

		if (!Path.EndsWith(ECsLoadCached::Str::_C))
			Path.Append(ECsLoadCached::Str::_C);

		typedef NCsObject::FLibrary ObjectLibrary;

		UObject* O = ObjectLibrary::SafeLoad(Context, Path, Log);

		if (!O)
			return nullptr;

		UAnimBlueprintGeneratedClass* ABpGC = Cast<UAnimBlueprintGeneratedClass>(O);

		if (!ABpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get AnimBlueprintGeneratedClass from Blueprint: %s with Class: %s."), *Context, *(Blueprint->GetName()), *(Blueprint->GetClass()->GetName())));
		}
		return (UAnimBlueprintGeneratedClass*)(O);
	}

	#pragma endregion Get
}