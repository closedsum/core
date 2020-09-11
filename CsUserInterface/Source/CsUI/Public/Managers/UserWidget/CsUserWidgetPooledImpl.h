// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"

#include "CsUserWidgetPooledImpl.generated.h"

struct ICsPooledObjectCache;
struct ICsPayload_PooledObject;
class UUserWidget;

UCLASS()
class CSUI_API UCsUserWidgetPooledImpl : public UObject,
										 public ICsOnConstructObject,
										 public ICsUpdate,
										 public ICsPooledObject,
										 public ICsUserWidgetPooled
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region
public:

	void OnConstructObject(const FCsManagerPooledObjectConstructParams& Params);

#pragma endregion ICsOnConstructObject

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

	ICsPooledObjectCache* Cache;

	void ConstructCache();

// ICsUserWidgetPooled
#pragma region
public:

	FORCEINLINE UUserWidget* GetUserWidget() const 
	{
		return UserWidget;
	}

#pragma endregion ICsUserWidgetPooled

protected:

	UPROPERTY()
	UUserWidget* UserWidget;
};