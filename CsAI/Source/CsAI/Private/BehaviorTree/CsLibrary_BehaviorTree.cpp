// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/CsLibrary_BehaviorTree.h"

// Library
	// Common
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
// BehaviorTree
#include "BehaviorTree/BehaviorTree.h"

namespace NCsBehaviorTree
{
	using LogClassType = NCsAI::FLog;

	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

	// Load
	#pragma region

	UBehaviorTree* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<UBehaviorTree>(Context, Path, Log);
	}

	UBehaviorTree* FLibrary::SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<UBehaviorTree>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UBehaviorTree* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, TSoftObjectPtr<UBehaviorTree>& OutSoftObjectPtr, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutSoftObjectPtr			 = SoftObjectPtr.ToSoftObjectPath();
		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FSoftObjectPath& OutSoftObjectPath, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutSoftObjectPath			 = SoftObjectPtr.ToSoftObjectPath();
		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftObjectPropertyValueByPath<UBehaviorTree>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutPathAsString				 = SoftObjectPtr.ToString();
		return OutSuccess;
	}

	#pragma endregion Get
}