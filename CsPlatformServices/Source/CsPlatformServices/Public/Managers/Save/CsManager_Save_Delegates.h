// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Managers/Save/CsTypes_Save.h"

#include "CsManager_Save_Delegates.generated.h"

USTRUCT()
struct CSPLATFORMSERVICES_API FCsManager_Save_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Save_Delegates_STUB()
	{
	}
};

// Script Passable
#pragma region

	// Enumerate
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsManagerSave_ScriptPassable_OnEnumerate, bool, WasSuccessful);
	// Read
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsManagerSave_ScriptPassable_OnRead, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsManagerSave_ScriptPassable_OnReadAll);
	// Write
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsManagerSave_ScriptPassable_OnWrite, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsManagerSave_ScriptPassable_OnWriteAll);
	// Delete
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsManagerSave_ScriptPassable_OnDelete, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsManagerSave_ScriptPassable_OnDeleteAll);

#pragma endregion Script Passable

/**
* OnStart
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerSave_OnStart);
/**
* OnEnumerate
*
* @param WasSuccessful
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerSave_OnEnumerate, bool, WasSuccessful);
/**
* OnRead
*
* @param WasSuccessful
* @param Profile
* @param Save
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerSave_OnRead, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
/**
* OnReadAll
*
* @param Profile
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerSave_OnReadAll, const ECsPlayerProfile&, Profile);
/**
* OnWrite
*
* @param WasSuccessful
* @param Profile
* @param Save
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerSave_OnWrite, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
/**
* OnWriteAll
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerSave_OnWriteAll);
/**
* OnDelete
*
* @param WasSuccessful
* @param Profile
* @param Save
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerSave_OnDelete, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
/**
* OnDeleteAll
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerSave_OnDeleteAll);

namespace NCsSave
{
	namespace NManager
	{
		/** Delegate type when save files have been enumerated / file names recorded.
		*
		* @param WasSuccessful
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnumerate, bool /*WasSuccessful*/);
	}
}