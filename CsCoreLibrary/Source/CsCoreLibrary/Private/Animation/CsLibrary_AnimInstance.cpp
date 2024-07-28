// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_AnimInstance.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Blueprint
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimBlueprint.h"
// Component
#include "Components/SkeletalMeshComponent.h"

namespace NCsAnimInstance
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	// Load
	#pragma region

	UAnimBlueprint* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UAnimBlueprint>(Context, Path, Log);
	}

	UAnimBlueprint* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UAnimBlueprint>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, const FString& Path, LogLevel)
	{
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(TEXT("_C")))
			ClassPath.Append(TEXT("_C"));

		UObject* O = CsObjectLibrary::SafeLoad(Context, ClassPath, Log);

		if (!O)
			return nullptr;

		UAnimBlueprintGeneratedClass* ABpGC = Cast<UAnimBlueprintGeneratedClass>(O);

		if (!ABpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get AnimBlueprintGeneratedClass from Path: %s."), *Context, *ClassPath));
			return nullptr;
		}
		return (UAnimBlueprintGeneratedClass*)(O);
	}

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UAnimBlueprint* Blueprint, LogLevel)
	{
		CS_IS_PENDING_KILL_CHECKED(Blueprint)

		TSoftObjectPtr<UAnimBlueprint> ABp(Blueprint);

		FString Path = ABp.ToSoftObjectPath().ToString();

		return GetSafeClass(Context, Path, Log);
	}

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<UAnimBlueprintGeneratedClass>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	UAnimInstance* FLibrary::GetChecked(const FString& Context, UPrimitiveComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component);

		USkeletalMeshComponent* SMC = CS_CAST_CHECKED(Component, UPrimitiveComponent, USkeletalMeshComponent);
		UAnimInstance* AnimInstance = SMC->GetAnimInstance();

		checkf(AnimInstance, TEXT("%s: Failed to get AnimInstance from Component: %s."), *Context, *(Component->GetName()));
		return AnimInstance;
	}

	UAnimInstance* FLibrary::GetSafe(const FString& Context, UPrimitiveComponent* Component, LogLevel)
	{
		CS_IS_PENDING_KILL_RET_NULL(Component)

		USkeletalMeshComponent* SMC = CS_CAST(Component, UPrimitiveComponent, USkeletalMeshComponent);

		if (!SMC)
			return nullptr;

		UAnimInstance* AnimInstance = SMC->GetAnimInstance();

		if (!AnimInstance)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get AnimInstance from Component: %s."), *Context, *(Component->GetName())));
			return nullptr;
		}
		return AnimInstance;
	}

	#pragma endregion Get

	#undef LogLevel
}