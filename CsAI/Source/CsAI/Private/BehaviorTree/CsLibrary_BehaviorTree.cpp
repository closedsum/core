// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/CsLibrary_BehaviorTree.h"
#include "CsAI.h"

// Library
	// Common
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
// BehaviorTree
#include "BehaviorTree/BehaviorTree.h"

namespace NCsBehaviorTree
{
	// Load
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	UBehaviorTree* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UBehaviorTree>(Context, Path, Log);
	}

	UBehaviorTree* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UBehaviorTree>(Context, Path, Log);
	}

	#undef ObjectLibrary

	#pragma endregion Load

	// Get
	#pragma region
	
	#define PropertyLibrary NCsProperty::FLibrary

	UBehaviorTree* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		return PropertyLibrary::GetObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, TSoftObjectPtr<UBehaviorTree>& OutSoftObjectPtr, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		FSoftObjectPtr SoftObjectPtr = PropertyLibrary::GetSoftObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutSoftObjectPtr			 = SoftObjectPtr.ToSoftObjectPath();
		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FSoftObjectPath& OutSoftObjectPath, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		FSoftObjectPtr SoftObjectPtr = PropertyLibrary::GetSoftObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutSoftObjectPath			 = SoftObjectPtr.ToSoftObjectPath();
		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		FSoftObjectPtr SoftObjectPtr = PropertyLibrary::GetSoftObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutPathAsString				 = SoftObjectPtr.ToString();
		return OutSuccess;
	}

	#undef PropertyLibrary

	#pragma endregion Get
}