// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Singleton/CsManager_Singleton.h"
// Get Singleton
#include "Managers/FX/Actor/CsGetManagerFXActor.h"

#include "CsManager_Singleton_FX.generated.h"

class UCsManager_FX_Actor;

UCLASS()
class CSCORE_API UCsManager_Singleton_FX : public UCsManager_Singleton,
										   public ICsGetManagerFXActor
{
	GENERATED_UCLASS_BODY()

// ICsGetManagerFXActor
#pragma region
protected:

	UPROPERTY()
	UCsManager_FX_Actor* Manager_FX_Actor;

public:

	FORCEINLINE UCsManager_FX_Actor* GetManager_FX_Actor() const
	{
		return Manager_FX_Actor;
	}

	FORCEINLINE void SetManager_FX_Actor(UCsManager_FX_Actor* InManager)
	{
		Manager_FX_Actor = InManager;
	}

#pragma endregion ICsGetManagerFXActor
};