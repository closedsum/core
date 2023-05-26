// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Blueprint.h"
#include "CsCore.h"

// Types
#include "Types/CsCached.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/Blueprint.h"

namespace NCsBlueprint
{
	// Load
	#pragma region

	UBlueprint* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UBlueprint>(Context, Path, Log);
	}

	UBlueprint* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UBlueprint>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region

	UBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UBlueprint* Blueprint, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		TSoftObjectPtr<UBlueprint> Bp(Blueprint);

		FString Path = Bp.ToSoftObjectPath().ToString();

		if (!Path.EndsWith(NCsCached::Str::_C))
			Path.Append(NCsCached::Str::_C);

		typedef NCsObject::FLibrary ObjectLibrary;

		UObject* O = ObjectLibrary::SafeLoad(Context, Path, Log);

		if (!O)
			return nullptr;

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		if (!BpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get BlueprintGeneratedClass from Blueprint: %s with Class: %s."), *Context, *(Blueprint->GetName()), *(Blueprint->GetClass()->GetName())));
		}
		return (UBlueprintGeneratedClass*)(O);
	}

	UObject* FLibrary::GetSafeDefaultObject(const FString& Context, UBlueprint* Blueprint, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		TSoftObjectPtr<UBlueprint> Bp(Blueprint);

		FString Path = Bp.ToSoftObjectPath().ToString();

		if (!Path.EndsWith(NCsCached::Str::_C))
			Path.Append(NCsCached::Str::_C);

		typedef NCsObject::FLibrary ObjectLibrary;

		UObject* O = ObjectLibrary::SafeLoad(Context, Path, Log);

		if (!O)
			return nullptr;

		UClass* Class = CS_CAST(O, UObject, UClass);

		if (!Class)
			return nullptr;

		UObject* DOb = Class->GetDefaultObject();

		if (!DOb)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object from Blueprint: %s with Class: %s."), *Context, *(Blueprint->GetName()), *(Blueprint->GetClass()->GetName())));
		}
		return DOb;
	}

	#pragma endregion Get
}