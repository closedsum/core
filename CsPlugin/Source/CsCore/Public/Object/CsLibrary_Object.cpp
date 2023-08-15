// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Object/CsLibrary_Object.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
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
			}
		}
	}

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

	bool FLibrary::IsDefaultObject(const UObject* Object)
	{
		return Object ? Object->GetName().StartsWith(TEXT("Default__")) : false;
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

	UObject* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	UObject* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Path is Valid
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		FSoftObjectPath SoftPath(Path);

		return SafeLoad(Context, SoftPath, Log);
	}

	#pragma endregion Load

	bool FLibrary::SafeMarkAsGarbage(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
}