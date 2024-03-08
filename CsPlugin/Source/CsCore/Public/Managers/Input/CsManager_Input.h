// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/Profile/CsTypes_InputProfile.h"
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsManager_Input.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsManager_Input : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct FCsGameEventDefinition;

class CSCORE_API ICsManager_Input
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual APlayerController* GetOwnerAsController() const = 0;

	virtual int32 GetControllerId() const = 0;

	virtual void Init() = 0;

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) = 0;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) = 0;

	virtual void SetCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map) = 0;
	virtual void SetCurrentInputActionMap(const FECsInputActionMap& Map) = 0;
	virtual void SetCurrentInputActionMap(const FString& Context, const int32& Map) = 0;
	virtual void SetCurrentInputActionMap(const int32& Map) = 0;
	virtual void ClearCurrentInputActionMap(const FString& Context, const FECsInputActionMap& Map) = 0;
	virtual void ClearCurrentInputActionMap(const FECsInputActionMap& Map) = 0;
	virtual void ClearCurrentInputActionMap(const FString& Context, const int32& Map) = 0;
	virtual void ClearCurrentInputActionMap(const int32& Map) = 0;
	virtual void ResetCurrentInputActionMap() = 0;

	virtual const FCsGameEventDefinition* GetGameEventDefinition(const FECsGameEvent& GameEvent) const = 0;

	virtual const FCsInputProfile& GetDefaultInputProfile() const = 0;
};