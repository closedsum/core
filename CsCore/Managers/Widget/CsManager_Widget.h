// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_UI.h"
#include "Types/CsTypes_Pool.h"
#include "CsManager_Widget.generated.h"

UCLASS()
class CSCORE_API UCsManager_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

	//static ACsManager_Projectile* Get(UWorld* InWorld);

	virtual void Clear();
	virtual void Shutdown();
	virtual void BeginDestroy() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const TCsSimpleWidgetType &Type, const int32 &Size);
	virtual void AddToActivePool(UObject* InObject, const TCsSimpleWidgetType& Type);
	virtual void OnTick(const float &DeltaSeconds);

	UWorld* CurrentWorld;

	int32 PoolSize;

	TMap<TCsSimpleWidgetType, uint16> PoolSizes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<class UCsSimpleWidget*> Pool;

	TMap<TCsSimpleWidgetType, TArray<class UCsSimpleWidget*>> Pools;

	TMap<TCsSimpleWidgetType, uint16> PoolIndices;

	uint16 PoolIndex;

	TMap<TCsSimpleWidgetType, TArray<class UCsSimpleWidget*>> ActiveWidgets;

	virtual int32 GetActivePoolSize(const TCsSimpleWidgetType& Type);

	virtual bool IsExhausted(const TCsSimpleWidgetType &Type);

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject);

	class UCsSimpleWidget* Allocate(const TCsSimpleWidgetType &Type);

	virtual void DeAllocate(const TCsSimpleWidgetType &Type, const int32 &Index);
	virtual void DeAllocateAll();

// Show
#pragma region

	virtual class UCsSimpleWidget* Show(const TCsSimpleWidgetType &Type, FCsSimpleWidgetPayload* Payload, UObject* InOwner, UObject* InParent);

#pragma endregion Show
};