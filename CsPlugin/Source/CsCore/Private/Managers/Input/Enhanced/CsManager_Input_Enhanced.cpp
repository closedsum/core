// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Enhanced/CsManager_Input_Enhanced.h"

// Cached
#pragma region

namespace NCsManagerInputEnhanced
{
	namespace NCached
	{
		namespace Str
		{
		}
	}
}

#pragma endregion Cached

UCsManager_Input_Enhanced::UCsManager_Input_Enhanced() :
	// Owner
	OwnerAsController(nullptr),
	ControllerId(INDEX_NONE),
	// Manager_Input_Event
	OnPostProcessInput_Event(),
	OnGameEventInfo_Event(),
	OnGameEventInfos_Event(),
	OnAnyKey_Pressed_Event(),
	OnAnyKey_Pressed_ScriptEvent(),
	OnAnyKey_Released_Event(),
	OnAnyKey_Released_ScriptEvent()
{
}

// UObject Interface
#pragma region

void UCsManager_Input_Enhanced::BeginDestroy()
{
	Super::BeginDestroy();

	/*typedef NCsObject::FLibrary ObjectLibrary;

	for (UCsInputListener* Listener : Listeners)
	{
		ObjectLibrary::SafeMarkAsGarbage(Listener);
	}
	Listeners.Reset();*/
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_Input_Enhanced::OnRegister()
{
	Super::OnRegister();

	OwnerAsController = Cast<APlayerController>(GetOwner());
	
	//Init();
}

#pragma endregion UActorComponent Interface

// ICsManager_Input
#pragma region

void UCsManager_Input_Enhanced::Init() 
{
}

void UCsManager_Input_Enhanced::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
}

void UCsManager_Input_Enhanced::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
}

void UCsManager_Input_Enhanced::SetCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map) 
{
	/*check(EMCsInputActionMap::Get().IsValidEnumChecked(Context, Map));

	CS_SET_BITFLAG(CurrentInputActionMap, Map.Mask); */
}

void UCsManager_Input_Enhanced::SetCurrentInputActionMap(const FECsInputActionMap& Map) 
{ 
	//SetCurrentInputActionMap(NCsManagerInput::NCached::Str::SetCurrentInputActionMap, Map); 
}
	
void UCsManager_Input_Enhanced::SetCurrentInputActionMap(const FString& Context, const int32& Map) 
{ 
	/*checkf(Map >= 0, TEXT("%s: Map: %s is NOT Valid."), *Context, Map);

	CS_SET_BITFLAG(CurrentInputActionMap, Map); */
}

void UCsManager_Input_Enhanced::SetCurrentInputActionMap(const int32& Map) 
{ 
	//SetCurrentInputActionMap(NCsManagerInput::NCached::Str::SetCurrentInputActionMap, Map); 
}

void UCsManager_Input_Enhanced::ClearCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map)
{
	//checkf(EMCsInputActionMap::Get().IsValidEnum(Map), TEXT("%s: Map: %s is NOT Valid."), *Context, Map.ToChar());

	//CS_CLEAR_BITFLAG(CurrentInputActionMap, Map.Mask);
}

void UCsManager_Input_Enhanced::ClearCurrentInputActionMap(const FECsInputActionMap& Map) 
{ 
	//ClearCurrentInputActionMap(NCsManagerInput::NCached::Str::ClearCurrentInputActionMap, Map); 
}

void UCsManager_Input_Enhanced::ClearCurrentInputActionMap(const FString& Context, const int32& Map) 
{
	/*checkf(Map >= 0, TEXT("%s: Map: %s is NOT Valid."), *Context, Map);

	CS_CLEAR_BITFLAG(CurrentInputActionMap, Map);*/ 
}

void UCsManager_Input_Enhanced::ClearCurrentInputActionMap(const int32& Map) 
{ 
	//ClearCurrentInputActionMap(NCsManagerInput::NCached::Str::ClearCurrentInputActionMap, Map); 
}

void UCsManager_Input_Enhanced::ResetCurrentInputActionMap()
{ 
	CurrentInputActionMap = 0; 
}

#pragma endregion ICsManager_Input