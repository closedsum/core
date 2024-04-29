// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/CsLibrary_Object.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsObject
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsObject::FLibrary, SafeMarkAsGarbage);

				const FString Default__ = TEXT("Default__");
			}
		}
	}

	#define LogWarning void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	FString FLibrary::PrintObjectAndClass(const UObject* Object)
	{
		if (!Object)
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("Object: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	FString FLibrary::PrintNameAndClass(const UObject* Object)
	{
		if (!Object)
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("%s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	bool FLibrary::IsValidObject(const UObject* Object) { return IsValid(Object); }

	bool FLibrary::IsPendingKill(const UObject* Object) { return !IsValid(Object); }

	#if WITH_EDITOR

	bool FLibrary::IsValidChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)
		return true;
	}

	#endif // #if WITH_EDITOR
	
	bool FLibrary::SafeIsValid(const FString& Context, const UObject* Object, LogWarning)
	{
		CS_IS_PENDING_KILL(Object)
		return true;
	}

	FString FLibrary::GetFlagsAsString(const UObject* Object)
	{
		FString Str = TEXT("(");
		int32 Count = 0;

		// RF_Public
		if (Object->HasAnyFlags(EObjectFlags::RF_Public))
			Str += TEXT("RF_Public,");
		// RF_Standalone
		if (Object->HasAnyFlags(EObjectFlags::RF_Standalone))
			Str += TEXT("RF_Standalone,");
		// RF_Transactional
		if (Object->HasAnyFlags(EObjectFlags::RF_Transactional))
			Str += TEXT("RF_Transactional,");
		// RF_ClassDefaultObject
		if (Object->HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
			Str += TEXT("RF_ClassDefaultObject,");
		// RF_ArchetypeObject
		if (Object->HasAnyFlags(EObjectFlags::RF_ArchetypeObject))
			Str += TEXT("RF_ArchetypeObject,");
		// RF_Transient
		if (Object->HasAnyFlags(EObjectFlags::RF_Transient))
			Str += TEXT("RF_Transient,");
		// RF_TagGarbageTemp
		if (Object->HasAnyFlags(EObjectFlags::RF_TagGarbageTemp))
			Str += TEXT("RF_TagGarbageTemp,");
		// RF_NeedInitialization
		if (Object->HasAnyFlags(EObjectFlags::RF_NeedInitialization))
			Str += TEXT("RF_NeedInitialization,");
		// RF_NeedLoad
		if (Object->HasAnyFlags(EObjectFlags::RF_NeedLoad))
			Str += TEXT("RF_NeedLoad,");
		// RF_KeepForCooker
		if (Object->HasAnyFlags(EObjectFlags::RF_KeepForCooker))
			Str += TEXT("RF_KeepForCooker,");
		// RF_NeedPostLoad
		if (Object->HasAnyFlags(EObjectFlags::RF_NeedPostLoad))
			Str += TEXT("RF_NeedPostLoad,");
		// RF_NeedPostLoadSubobjects
		if (Object->HasAnyFlags(EObjectFlags::RF_NeedPostLoadSubobjects))
			Str += TEXT("RF_NeedPostLoadSubobjects,");
		// RF_NewerVersionExists
		if (Object->HasAnyFlags(EObjectFlags::RF_NewerVersionExists))
			Str += TEXT("RF_NewerVersionExists,");
		// RF_BeginDestroyed
		if (Object->HasAnyFlags(EObjectFlags::RF_BeginDestroyed))
			Str += TEXT("RF_BeginDestroyed,");
		// RF_FinishDestroyed
		if (Object->HasAnyFlags(EObjectFlags::RF_FinishDestroyed))
			Str += TEXT("RF_FinishDestroyed,");
		// RF_BeingRegenerated
		if (Object->HasAnyFlags(EObjectFlags::RF_BeingRegenerated))
			Str += TEXT("RF_BeingRegenerated,");
		// RF_DefaultSubObject
		if (Object->HasAnyFlags(EObjectFlags::RF_DefaultSubObject))
			Str += TEXT("RF_DefaultSubObject,");
		// RF_WasLoaded
		if (Object->HasAnyFlags(EObjectFlags::RF_WasLoaded))
			Str += TEXT("RF_WasLoaded,");
		// RF_TextExportTransient
		if (Object->HasAnyFlags(EObjectFlags::RF_TextExportTransient))
			Str += TEXT("RF_TextExportTransient,");
		// RF_InheritableComponentTemplate
		if (Object->HasAnyFlags(EObjectFlags::RF_InheritableComponentTemplate))
			Str += TEXT("RF_InheritableComponentTemplate,");
		// RF_DuplicateTransient
		if (Object->HasAnyFlags(EObjectFlags::RF_DuplicateTransient))
			Str += TEXT("RF_DuplicateTransient,");
		// RF_StrongRefOnFrame
		if (Object->HasAnyFlags(EObjectFlags::RF_StrongRefOnFrame))
			Str += TEXT("RF_StrongRefOnFrame,");
		// RF_NonPIEDuplicateTransient
		if (Object->HasAnyFlags(EObjectFlags::RF_NonPIEDuplicateTransient))
			Str += TEXT("RF_NonPIEDuplicateTransient,");
		// RF_Dynamic1
		//if (Object->HasAnyFlags(EObjectFlags::RF_Dynamic))
		//	Str += TEXT("RF_Dynamic,");
		// RF_WillBeLoaded
		if (Object->HasAnyFlags(EObjectFlags::RF_WillBeLoaded))
			Str += TEXT("RF_WillBeLoaded,");

		Str.RemoveFromEnd(TEXT(","));
		Str = Str.Replace(TEXT(","), TEXT(" | "));
		Str += TEXT(")");

		return Str;
	}

	UObject* FLibrary::ConstructChecked(const FString& Context, UObject* Outer, UClass* Class)
	{
		CS_IS_PENDING_KILL_CHECKED(Outer)
		CS_IS_PENDING_KILL_CHECKED(Class)

		UObject* O  = NewObject<UObject>(Outer, Class);

		checkf(O, TEXT("%s: Failed to Create New Object with Outer: %s and Class: %s."), *Context, *(Outer->GetName()), *(Class->GetName()));
		return O;
	}

	UObject* FLibrary::SafeConstruct(const FString& Context, UObject* Outer, UClass* Class, LogWarning)
	{
		CS_IS_PENDING_KILL_RET_NULL(Outer)
		CS_IS_PENDING_KILL_RET_NULL(Class)

		UObject* O  = NewObject<UObject>(Outer, Class);

		if (!O)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to Create New Object with Outer: %s and Class: %s."), *Context, *(Outer->GetName()), *(Class->GetName())));
			return nullptr;
		}
		return O;
	}

	UObject* FLibrary::GetDefaultObjectChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		UClass* Class = Object->GetClass();

		checkf(Class, TEXT("%s: Failed to get Class from Object: %s."), *Context, *(Class->GetName()));

		UObject* DOb = Class->GetDefaultObject<UObject>();

		checkf(DOb, TEXT("%s: Failed to get Default Object from Object: %s with Class: %s."), *Context, *(Object->GetName()), *(Class->GetName()));
		return DOb;
	}

	UObject* FLibrary::GetSafeDefaultObject(const FString& Context, const UObject* Object, LogWarning)
	{
		CS_IS_PENDING_KILL_RET_NULL(Object)

		UClass* Class = Object->GetClass();

		if (!Class)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Class from Object: %s."), *Context, *(Class->GetName())));
			return nullptr;
		}

		UObject* DOb = Class->GetDefaultObject<UObject>();

		if (!DOb)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object from Object: %s with Class: %s."), *Context, *(Object->GetName()), *(Class->GetName())));
			return nullptr;
		}
		return DOb;
	}

	bool FLibrary::IsDefaultObject(const UObject* Object)
	{
		return Object ? Object->GetName().StartsWith(NCsObject::NLibrary::NCached::Str::Default__) : false;
	}

	int32 FLibrary::GetUniqueIDChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)
		return Object->GetUniqueID();
	}

	int32 FLibrary::GetSafeUniqueID(const FString& Context, const UObject* Object, LogWarning)
	{
		CS_IS_PENDING_KILL_RET_VALUE(Object, INDEX_NONE)
		return Object->GetUniqueID();
	}

	// Load
	#pragma region

	UObject* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		// Check Path is Valid
		CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Path)

		UObject* Object = Path.TryLoad();

		checkf(Object, TEXT("%s: Failed to load Object at Path: %s."), *Context, *(Path.ToString()));
		return Object;
	}

	UObject* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogWarning)
	{
		// Check Path is Valid
		CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(Path)

		UObject* Object = Path.TryLoad();

		if (!Object)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Object at Path: %s."), *Context, *(Path.ToString())));
			return nullptr;
		}
		return Object;
	}

	UObject* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		// Check Path is Valid
		CS_IS_STRING_EMPTY_CHECKED(Path)

		FSoftObjectPath SoftPath(Path);

		return LoadChecked(Context, SoftPath);
	}

	UObject* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogWarning)
	{
		// Check Path is Valid
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FSoftObjectPath SoftPath(Path);

		return SafeLoad(Context, SoftPath, Log);
	}

	#pragma endregion Load

	bool FLibrary::SafeMarkAsGarbage(const FString& Context, UObject* Object, LogWarning)
	{
		CS_IS_PTR_NULL(Object)

		if (IsValid(Object))
		{
			Object->MarkAsGarbage();
			return true;
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s has ALREADY been Marked as Garbage."), *Context, *(PrintObjectAndClass(Object))));
		return false;
	}

	bool FLibrary::SafeMarkAsGarbage(UObject* Object)
	{
		using namespace NCsObject::NLibrary::NCached;
		
		const FString& Context = Str::SafeMarkAsGarbage;

		return SafeMarkAsGarbage(Context, Object, nullptr);
	}

	#undef LogWarning
}