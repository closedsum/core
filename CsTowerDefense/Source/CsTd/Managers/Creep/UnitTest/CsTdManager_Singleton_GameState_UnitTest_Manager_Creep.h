// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Creep/CsTdGetManagerCreep.h"
#include "CsTdManager_Singleton_GameState_UnitTest_Manager_Creep.generated.h"

class UCsTdManager_Creep;

UCLASS()
class CSTD_API UCsTdManager_Singleton_GameState_UnitTest_Manager_Creep : public UCsManager_Singleton,
																		 public ICsTdGetManagerCreep
{
	GENERATED_UCLASS_BODY()

// ICsTdGetManagerCreep
#pragma region
protected:

	UPROPERTY()
	UCsTdManager_Creep* Manager_Creep;

public:

	FORCEINLINE UCsTdManager_Creep* GetManager_Creep() const
	{
		return Manager_Creep;
	}

	FORCEINLINE void SetManager_Creep(UCsTdManager_Creep* InManager)
	{
		Manager_Creep = InManager;
	}

#pragma endregion ICsTdGetManagerCreep
};