// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_AnimInstance.h"
#include "CsCore.h"

// Types
#include "Types/CsCached.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Blueprint
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimBlueprint.h"
// Component
#include "Components/SkeletalMeshComponent.h"

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
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		TSoftObjectPtr<UAnimBlueprint> ABp(Blueprint);

		FString Path = ABp.ToSoftObjectPath().ToString();

		if (!Path.EndsWith(NCsCached::Str::_C))
			Path.Append(NCsCached::Str::_C);

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

	UAnimInstance* FLibrary::GetChecked(const FString& Context, UPrimitiveComponent* Component)
	{
		CS_IS_PTR_NULL_CHECKED(Component);

		USkeletalMeshComponent* SMC = CS_CAST_CHECKED(Component, UPrimitiveComponent, USkeletalMeshComponent);
		UAnimInstance* AnimInstance = SMC->GetAnimInstance();

		checkf(AnimInstance, TEXT("%s: Failed to get AnimInstance from Component: %s."), *Context, *(Component->GetName()));

		return AnimInstance;
	}

	#pragma endregion Get
}