// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Save/Script/CsScriptLibrary_Manager_Save.h"
#include "CsPlatformServices.h"

// Library
#include "Managers/Save/CsLibrary_Manager_Save.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "Managers/Save/CsManager_Save.h"

#include "Managers/PlayerProfile/CsPlayerProfile.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerSave
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, SetCurrentSave);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Enumerate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnEnumerate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Read);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnRead);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, ReadAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnReadAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Write);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnWrite);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, WriteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnWriteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, Delete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnDelete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, BindToEvent_OnDeleteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Save, DeleteAllContent);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Save::UCsScriptLibrary_Manager_Save(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// FileName
#pragma region

void UCsScriptLibrary_Manager_Save::SetCurrentSave(const FString& Context, UObject* WorldContextObject, const ECsSave& Save)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetCurrentSave : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SetSafeCurrentSave(Ctxt, WorldContextObject, Save);
}

#pragma endregion FileName

// Enumerate
#pragma region

void UCsScriptLibrary_Manager_Save::Enumerate(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Enumerate : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeEnumerate(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnEnumerate(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnEnumerate Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnEnumerate : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnEnumerate_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

#pragma endregion Enumerate

// Read
#pragma region

void UCsScriptLibrary_Manager_Save::Read(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Read : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeRead(Ctxt, WorldContextObject, Profile, Save);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnRead(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnRead Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnRead : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnRead_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

void UCsScriptLibrary_Manager_Save::ReadAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ReadAll : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeReadAll(Ctxt, WorldContextObject, Profile);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnReadAll(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnReadAll Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnReadAll : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnReadAll_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

#pragma endregion Read

// Write
#pragma region

void UCsScriptLibrary_Manager_Save::Write(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Write : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeWrite(Ctxt, WorldContextObject, Profile, Save);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnWrite(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnWrite Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnWrite : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnWrite_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

void UCsScriptLibrary_Manager_Save::WriteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::WriteAll : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeWriteAll(Ctxt, WorldContextObject, Profile);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnWriteAll(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnWriteAll Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnWriteAll : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnWriteAll_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

#pragma endregion Write

// Delete
#pragma region

void UCsScriptLibrary_Manager_Save::Delete(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Delete : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeDelete(Ctxt, WorldContextObject, Profile, Save);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnDelete(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnDelete Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnDelete : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnDelete_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

void UCsScriptLibrary_Manager_Save::DeleteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::DeleteAll : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::DeleteAllChecked(Ctxt, WorldContextObject, Profile);
}

void UCsScriptLibrary_Manager_Save::BindToEvent_OnDeleteAll(const FString& Context, UObject* WorldContextObject, FCsScriptLibraryManagerSave_OnDeleteAll Delegate)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnDeleteAll : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	if (UCsManager_Save* Manager = SaveManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnDeleteAll_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

void UCsScriptLibrary_Manager_Save::DeleteAllContent(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerSave::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::DeleteAllContent : Context;

	typedef NCsSave::NManager::FLibrary SaveManagerLibrary;

	SaveManagerLibrary::SafeDeleteAllContent(Ctxt, WorldContextObject);
}

#pragma endregion Delete