// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Singleton/CsManager_Singleton.h"
// Get Singleton
#include "Managers/FX/Actor/CsGetManagerFX.h"

#include "CsManager_Singleton_FX.generated.h"

class UCsManager_FX;

UCLASS()
class CSCORE_API UCsManager_Singleton_FX : public UCsManager_Singleton,
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