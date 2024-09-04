// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Singleton/CsManager_Singleton.h"
// Get Singleton
#include "Managers/FX/Actor/CsGetManagerFX.h"

#include "CsManager_Singleton_FX.generated.h"

class UCsManager_FX;

UCLASS()
class CSFX_API UCsManager_Singleton_FX : public UCsManager_Singleton,
										   public ICsGetManagerFX
{
	GENERATED_UCLASS_BODY()

// ICsGetManagerFX
#pragma region
protected:

	UPROPERTY()
	UCsManager_FX* Manager_FX;

public:

	FORCEINLINE UCsManager_FX* GetManager_FX() const
	{
		return Manager_FX;
	}

	FORCEINLINE void SetManager_FX(UCsManager_FX* InManager)
	{
		Manager_FX = InManager;
	}

#pragma endregion ICsGetManagerFX
};