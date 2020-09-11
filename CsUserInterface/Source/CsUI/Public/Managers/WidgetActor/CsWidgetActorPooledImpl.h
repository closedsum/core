// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "CsWidgetActorPooledImpl.generated.h"

struct ICsPooledObjectCache;
struct ICsPayload_PooledObject;
class UCsWidgetComponent;
struct ICsPayload_UserWidget;
struct FCsUserWidgetPooled;

UCLASS()
class CSUI_API ACsWidgetActorPooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPooledObject,
										  public ICsWidgetActor
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

// AActor Interface
#pragma region
public:

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region
public:

	FORCEINLINE ICsPooledObjectCache* GetCache() const
	{
		return Cache;
	}
	
	void Allocate(ICsPayload_PooledObject* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	void Deallocate_Internal();

	ICsPooledObjectCache* Cache;

	void ConstructCache();

// ICsWidgetActor
#pragma region
public:

	FORCEINLINE UCsWidgetComponent* GetWidgetComponent() const
	{
		return WidgetComponent;
	}

#pragma endregion ICsWidgetActor

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCsWidgetComponent* WidgetComponent;

	FCsUserWidgetPooled* UserWidgetPooled;
};