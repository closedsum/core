// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_UI.h"
#include "Types/CsTypes_Pool.h"
#include "CsManager_Widget.generated.h"

#define CS_POOLED_WIDGET_PAYLOAD_SIZE 256

UCLASS()
class CSCORE_API UCsManager_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

	//static ACsManager_Projectile* Get(UWorld* InWorld);

	virtual void Clear();
	virtual void Shutdown();
	virtual void BeginDestroy() override;
	virtual void CreatePool(UClass* InClass, const TCsSimpleWidgetType &Type, const int32 &Size);
	virtual void AddToActivePool(UObject* InObject, const TCsSimpleWidgetType& Type);
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &DeltaSeconds);

	UWorld* CurrentWorld;

	int32 PoolSize;

	TMap<TCsSimpleWidgetType, uint16> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class UCsPooledWidget*> Pool;

	TMap<TCsSimpleWidgetType, TArray<class UCsPooledWidget*>> Pools;

	TMap<TCsSimpleWidgetType, uint16> PoolIndices;

	uint16 PoolIndex;

	TMap<TCsSimpleWidgetType, TArray<class UCsPooledWidget*>> ActiveWidgets;

	virtual int32 GetActivePoolSize(const TCsSimpleWidgetType& Type);

	virtual bool IsExhausted(const TCsSimpleWidgetType &Type);

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject);

	class UCsPooledWidget* Allocate(const TCsSimpleWidgetType &Type);

	virtual void DeAllocate(const TCsSimpleWidgetType &Type, const int32 &Index);
	virtual void DeAllocateAll();

	virtual void AddPoolToCanvas(UCanvasPanel* InCanvas, const TCsSimpleWidgetType &Type);

// Payload
#pragma region
private:

	FCsWidgetPayload Payloads[CS_POOLED_WIDGET_PAYLOAD_SIZE];

	uint8 PayloadIndex;

public:

	FCsWidgetPayload* AllocatePayload();

#pragma endregion Payload

// Show
#pragma region
public:

	virtual class UCsPooledWidget* Show(const TCsSimpleWidgetType &Type, FCsWidgetPayload* Payload, UObject* InOwner, UObject* InParent);

#pragma endregion Show
};