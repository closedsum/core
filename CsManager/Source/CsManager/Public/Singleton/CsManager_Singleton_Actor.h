// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Singleton/CsGetManagerSingleton.h"

#include "CsManager_Singleton_Actor.generated.h"

class UCsManager_Singleton;

UCLASS()
class CSMANAGER_API ACsManager_Singleton_Actor : public AActor,
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
public:

	virtual void PostActorCreated() override;

#pragma endregion AActor Interface

private:

	UFUNCTION()
	void OnDestroy(AActor* Actor);

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

	virtual void SetupSingletons() {}

	virtual void ShutdownSingletons() {}

#pragma endregion Manager Singleton
};