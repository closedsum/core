// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsLibrary_AnimInstance.h"
#include "CsCore.h"

// Types
#include "Types/CsCached.h"
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
	#define ObjectLibrary NCsObject::FLibrary

	// Load
	#pragma region

	UAnimBlueprint* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UAnimBlueprint>(Context, Path, Log);
	}

	UAnimBlueprint* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UAnimBlueprint>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(NCsCached::Str::_C))
			ClassPath.Append(NCsCached::Str::_C);

		UObject* O = ObjectLibrary::SafeLoad(Context, ClassPath, Log);

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

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UAnimBlueprint* Blueprint, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		TSoftObjectPtr<UAnimBlueprint> ABp(Blueprint);

		FString Path = ABp.ToSoftObjectPath().ToString();

		return GetSafeClass(Context, Path, Log);
	}

	UAnimBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValueByPath<UAnimBlueprintGeneratedClass>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
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

	#undef ObjectLibrary
}