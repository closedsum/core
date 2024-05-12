// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Save/Script/CsScriptLibrary_Manager_Save.h"
#include "CsPlatformServices.h"

// Types
#include "CsMacro_Misc.h"
// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Managers/Save/CsLibrary_Manager_Save.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "Managers/Save/CsManager_Save.h"

#include "Managers/PlayerProfile/CsPlayerProfile.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Save)

// Cached
#pragma region

namespace NCsScriptLibraryManagerSave
{
	namespace NCached
	{
		namespace Str
		{
			// FileName
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, SetCurrentSave);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, SetCurrentSaveChecked);
			// Enumerate
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Enumerate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, EnumerateChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnEnumerate);
			// Read
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Read);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, ReadChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnRead);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, ReadAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, ReadAllChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnReadAll);
			// Write
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Write);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, WriteChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnWrite);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, WriteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, WriteAllChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnWriteAll);
			// Delete
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Delete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnDelete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteAllChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnDeleteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteAllContent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteAllContentChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Save::UCsScriptLibrary_Manager_Save(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerSave::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerSave::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsPlatformServices::FLog::Error
#define SaveManagerLibrary NCsSave::NManager::FLibrary

// FileName
#pragma region

bool UCsScriptLibrary_Manager_Save::SetCurrentSave(const FString& Context, UObject* WorldContextObject, const ECsSave& Save)
{
	CONDITIONAL_SET_CTXT(SetCurrentSave);

	return SaveManagerLibrary::SetSafeCurrentSave(Ctxt, WorldContextObject, Save);
}

void UCsScriptLibrary_Manager_Save::SetCurrentSaveChecked(const FString& Context, UObject* WorldContextObject, const ECsSave& Save, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetCurrentSaveChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::SetCurrentSaveChecked(Ctxt, WorldContextObject, Save), SaveManagerLibrary::SetSafeCurrentSave(Ctxt, WorldContextObject, Save, OutSuccess, LogError))
}

#pragma endregion FileName

// Enumerate
#pragma region

bool UCsScriptLibrary_Manager_Save::Enumerate(const FString& Context, UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Enumerate);

	return SaveManagerLibrary::SafeEnumerate(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Manager_Save::EnumerateChecked(const FString& Context, UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(EnumerateChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::EnumerateChecked(Ctxt, WorldContextObject), SaveManagerLibrary::SafeEnumerate(Ctxt, WorldContextObject, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnEnumerate(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnEnumerate Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnEnumerate);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnEnumerate_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

#pragma endregion Enumerate

// Read
#pragma region

bool UCsScriptLibrary_Manager_Save::Read(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	CONDITIONAL_SET_CTXT(Read);

	return SaveManagerLibrary::SafeRead(Ctxt, WorldContextObject, Profile, Save);
}

void UCsScriptLibrary_Manager_Save::ReadChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(ReadChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::ReadChecked(Ctxt, WorldContextObject, Profile, Save), SaveManagerLibrary::SafeRead(Ctxt, WorldContextObject, Profile, Save, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnRead(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnRead Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnRead);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnRead_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

bool UCsScriptLibrary_Manager_Save::ReadAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
	CONDITIONAL_SET_CTXT(ReadAll);

	return SaveManagerLibrary::SafeReadAll(Ctxt, WorldContextObject, Profile);
}

void UCsScriptLibrary_Manager_Save::ReadAllChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(ReadAll);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::ReadAllChecked(Ctxt, WorldContextObject, Profile), SaveManagerLibrary::SafeReadAll(Ctxt, WorldContextObject, Profile, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnReadAll(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnReadAll Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnReadAll);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnReadAll_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

#pragma endregion Read

// Write
#pragma region

bool UCsScriptLibrary_Manager_Save::Write(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	CONDITIONAL_SET_CTXT(Write);

	return SaveManagerLibrary::SafeWrite(Ctxt, WorldContextObject, Profile, Save);
}

void UCsScriptLibrary_Manager_Save::WriteChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(WriteChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::WriteChecked(Ctxt, WorldContextObject, Profile, Save), SaveManagerLibrary::SafeWrite(Ctxt, WorldContextObject, Profile, Save, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnWrite(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnWrite Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnWrite);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnWrite_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

bool UCsScriptLibrary_Manager_Save::WriteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
	CONDITIONAL_SET_CTXT(WriteAll);

	return SaveManagerLibrary::SafeWriteAll(Ctxt, WorldContextObject, Profile);
}

void UCsScriptLibrary_Manager_Save::WriteAllChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(WriteAll);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::WriteAllChecked(Ctxt, WorldContextObject, Profile), SaveManagerLibrary::SafeWriteAll(Ctxt, WorldContextObject, Profile, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnWriteAll(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnWriteAll Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnWriteAll);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnWriteAll_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

#pragma endregion Write

// Delete
#pragma region

bool UCsScriptLibrary_Manager_Save::Delete(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	CONDITIONAL_SET_CTXT(Delete);

	return SaveManagerLibrary::SafeDelete(Ctxt, WorldContextObject, Profile, Save);
}

void UCsScriptLibrary_Manager_Save::DeleteChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(DeleteChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::DeleteChecked(Ctxt, WorldContextObject, Profile, Save), SaveManagerLibrary::SafeDelete(Ctxt, WorldContextObject, Profile, Save, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnDelete(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnDelete Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnDelete);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnDelete_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

bool UCsScriptLibrary_Manager_Save::DeleteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
	CONDITIONAL_SET_CTXT(DeleteAll);

	return SaveManagerLibrary::SafeDeleteAll(Ctxt, WorldContextObject, Profile);
}

void UCsScriptLibrary_Manager_Save::DeleteAllChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(DeleteAllChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::DeleteAllChecked(Ctxt, WorldContextObject, Profile), SaveManagerLibrary::SafeDeleteAll(Ctxt, WorldContextObject, Profile, OutSuccess, LogError))
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnDeleteAll(const FString& Context, UObject* WorldContextObject, FCsManagerSave_ScriptPassable_OnDeleteAll Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnDeleteAll);

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnDeleteAll_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

bool UCsScriptLibrary_Manager_Save::DeleteAllContent(const FString& Context, UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(DeleteAllContent);

	return SaveManagerLibrary::SafeDeleteAllContent(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Manager_Save::DeleteAllContentChecked(const FString& Context, UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(DeleteAllContent);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(SaveManagerLibrary::DeleteAllContentChecked(Ctxt, WorldContextObject), SaveManagerLibrary::SafeDeleteAllContent(Ctxt, WorldContextObject, OutSuccess, LogError))
}

#pragma endregion Delete

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef SaveManagerLibrary