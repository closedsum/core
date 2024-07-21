// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Blueprint.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/Blueprint.h"

namespace NCsBlueprint
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsBlueprint::FLibrary, GetSafeClass);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsBlueprint::FLibrary, GetSafeClassDefaultObject);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsBlueprint::FLibrary, GetSafeDefaultObject);

				const FString _C = TEXT("_C");
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsBlueprint::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsBlueprint::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogWarning void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define NO_LOG void(*Log)(const FString&) = nullptr;
	#define WorldLibrary NCsWorld::FLibrary

	// Load
	#pragma region

	UBlueprint* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return CsObjectLibrary::LoadChecked<UBlueprint>(Context, Path);
	}

	UBlueprint* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogWarning)
	{
		return CsObjectLibrary::SafeLoad<UBlueprint>(Context, Path, Log);
	}

	UBlueprint* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		return CsObjectLibrary::LoadChecked<UBlueprint>(Context, Path);
	}

	UBlueprint* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogWarning)
	{
		return CsObjectLibrary::SafeLoad<UBlueprint>(Context, Path, Log);
	}

	UBlueprintGeneratedClass* FLibrary::LoadClassChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint)
	{
		CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Blueprint, UBlueprint)

		FString Path = Blueprint.ToSoftObjectPath().ToString();

		if (!Path.EndsWith(TEXT("_C"), ESearchCase::CaseSensitive))
			Path.Append(TEXT("_C"));

		FSoftObjectPath SoftPath(Path);

		UObject* O = SoftPath.TryLoad();

		CS_IS_PENDING_KILL_CHECKED(O)
		return (UBlueprintGeneratedClass*)(O);
	}

	#pragma endregion Load

	// Get
	#pragma region

	UBlueprintGeneratedClass* FLibrary::GetClassChecked(const FString& Context, const FString& Path)
	{
		CS_IS_STRING_EMPTY_CHECKED(Path)

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(NCsBlueprint::NLibrary::NCached::Str::_C))
			ClassPath.Append(NCsBlueprint::NLibrary::NCached::Str::_C);

		UObject* O					   = CsObjectLibrary::LoadChecked(Context, ClassPath);
		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		CS_IS_PENDING_KILL_CHECKED(BpGC)
		return (UBlueprintGeneratedClass*)(O);
	}

	UBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, const FString& Path, LogWarning)
	{
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(NCsBlueprint::NLibrary::NCached::Str::_C))
			ClassPath.Append(NCsBlueprint::NLibrary::NCached::Str::_C);

		UObject* O = CsObjectLibrary::SafeLoad(Context, ClassPath, Log);

		if (!O)
			return nullptr;

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		if (!BpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get BlueprintGeneratedClass from Path: %s."), *Context, *ClassPath));
			return nullptr;
		}
		return (UBlueprintGeneratedClass*)(O);
	}

	UBlueprintGeneratedClass* FLibrary::GetClassChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint)
	{
		CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Blueprint, UBlueprint)

		const FString Path = Blueprint.ToSoftObjectPath().ToString();

		return GetClassChecked(Context, Path);
	}

	UBlueprintGeneratedClass* FLibrary::GetClassChecked(const FString& Context, UBlueprint* Blueprint)
	{
		UBlueprintCore* BpC = CS_CAST_CHECKED(Blueprint, UBlueprint, UBlueprintCore);
		UClass* Class		= BpC->GeneratedClass.Get();

		return CS_CAST_CHECKED(Class, UClass, UBlueprintGeneratedClass);
	}

	UBlueprintGeneratedClass* FLibrary::GetSafeClass(const FString& Context, UBlueprint* Blueprint, LogWarning)
	{
		CS_IS_PENDING_KILL_RET_NULL(Blueprint)

		UBlueprintCore* BpC = CS_CAST(Blueprint, UBlueprint, UBlueprintCore);

		if (!BpC)
			return nullptr;

		UClass* Class = BpC->GeneratedClass.Get();

		if (!Class)
			return nullptr;
		return CS_CAST(Class, UClass, UBlueprintGeneratedClass);
	}

	UBlueprintGeneratedClass* FLibrary::GetSafeClass(UObject* Blueprint)
	{
		SET_CONTEXT(GetSafeClass);

		NO_LOG
		return GetSafeClass(Context, CS_CAST(Blueprint, UObject, UBlueprint), nullptr);
	}

	UObject* FLibrary::GetSafeClassDefaultObject(const FString& Context, UBlueprint* Blueprint, LogWarning)
	{
		if (UBlueprintGeneratedClass* BpGC = GetSafeClass(Context, Blueprint, Log))
		{
			UObject* DOb = BpGC->GetDefaultObject();

			if (!DOb)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object from Class: %s."), *Context, *(BpGC->GetName())));
				return nullptr;
			}
			return DOb;
		}
		return nullptr;
	}

	UObject* FLibrary::GetSafeClassDefaultObject(const FString& Context, UObject* Blueprint, LogWarning)
	{
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		return GetSafeClassDefaultObject(Context, CS_CAST(Blueprint, UObject, UBlueprint), Log);
	}

	UObject* FLibrary::GetSafeClassDefaultObject(UObject* Blueprint)
	{
		SET_CONTEXT(GetSafeClassDefaultObject);

		return GetSafeClassDefaultObject(Context, Blueprint, nullptr);
	}

	UObject* FLibrary::GetSafeDefaultObject(const FString& Context, const FString& Path, LogWarning)
	{
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(NCsBlueprint::NLibrary::NCached::Str::_C))
			ClassPath.Append(NCsBlueprint::NLibrary::NCached::Str::_C);

		UObject* O = CsObjectLibrary::SafeLoad(Context, ClassPath, Log);

		if (!O)
			return nullptr;

		UClass* Class = CS_CAST(O, UObject, UClass);

		if (!Class)
			return nullptr;

		UObject* DOb = Class->GetDefaultObject();

		if (!DOb)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object from Blueprint: %s."), *Context, *ClassPath));
			return nullptr;
		}
		return DOb;
	}

	UObject* FLibrary::GetSafeDefaultObject(const FString& Context, UBlueprint* Blueprint, LogWarning)
	{
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		TSoftObjectPtr<UBlueprint> Bp(Blueprint);

		FString Path = Bp.ToSoftObjectPath().ToString();

		if (!Path.EndsWith(NCsBlueprint::NLibrary::NCached::Str::_C))
			Path.Append(NCsBlueprint::NLibrary::NCached::Str::_C);
		return GetSafeDefaultObject(Context, Path, Log);
	}

	UObject* FLibrary::GetSafeDefaultObject(const FString& Context, UObject* Blueprint, LogWarning)
	{
		CS_IS_PTR_NULL_CHECKED(Blueprint)

		return GetSafeDefaultObject(Context, CS_CAST(Blueprint, UObject, UBlueprint), Log);
	}

	UObject* FLibrary::GetSafeDefaultObject(UObject* Blueprint)
	{
		SET_CONTEXT(GetSafeDefaultObject);

		return GetSafeDefaultObject(Context, Blueprint, nullptr);
	}

	#pragma endregion Get

	// Is
	#pragma region

	bool FLibrary::Is(const UObject* Object)
	{
		return Cast<UBlueprint>(Object) != nullptr;
	}

	bool FLibrary::SafeIs(const FString& Context, const UObject* Object, LogWarning)
	{
		CS_IS_PENDING_KILL(Object)

		UClass* Class = Object->GetClass();

		if (!Class)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Class from Object: %s."), *Context, *(Object->GetName())));
			return false;
		}

		UBlueprintGeneratedClass* BpGC = CS_CAST(Class, UClass, UBlueprintGeneratedClass);

		if (!BpGC)
			return false;

	#if WITH_EDITOR
		UObject* CGB = BpGC->ClassGeneratedBy;

		CS_IS_PTR_NULL(CGB)

		UBlueprint* Bp = CS_CAST(CGB, UObject, UBlueprint);
	#endif // #if WITH_EDITOR
		return true;
	}

	#pragma endregion Is
	
	// Spawn
	#pragma region
	
	AActor* FLibrary::SpawnAsActorChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UBlueprint>& Blueprint)
	{
	#if WITH_EDITOR
		UBlueprint* Bp				   = LoadChecked(Context, Blueprint);
		UBlueprintGeneratedClass* BpGC = GetClassChecked(Context, Bp);
	#else
		UBlueprintGeneratedClass* BpGC = LoadClassChecked(Context, Blueprint);
	#endif // #if WITH_EDITOR

		return WorldLibrary::SpawnChecked(Context, WorldContext, BpGC);
	}

	#pragma endregion Spawn

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogWarning
	#undef NO_LOG
	#undef WorldLibrary
}