// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "CsTdGameState_UnitTest_Manager_Creep.generated.h"

class UCsManager_Singleton;

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick", "LOD", "Cooking"))
class CSTD_API ACsTdGameState_UnitTest_Manager_Creep : public AGameState,
													   public ICsGetManagerSingleton
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
protected:

	virtual void BeginPlay() override;

#pragma endregion AActor Interface

// ICsGetManagerSingleton
#pragma region
public:

	FORCEINLINE UCsManager_Singleton* GetManager_Singleton() const
	{
		return Manager_Singleton;
	}

#pragma endregion ICsGetManagerSingleton

// Manager Singleton
#pragma region
protected:

	UPROPERTY()
	UCsManager_Singleton* Manager_Singleton;

	virtual void ConstructManagerSingleton();

	void OnBeginPlay_SetupSingletons();
	void OnBeginDestroy_ShutdownSingletons();

#pragma endregion Manager Singleton
};