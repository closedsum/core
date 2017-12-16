// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_UI.h"
#include "CsManager_Widget.generated.h"

UCLASS()
class CSCORE_API UCsManager_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

	//static ACsManager_Projectile* Get(UWorld* InWorld);

	virtual void Clear();
	virtual void Shutdown();
	virtual void BeginDestroy() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const int32 &Size);
	virtual void OnTick(const float &DeltaSeconds);

	UWorld* CurrentWorld;

	int32 PoolSize;

	UPROPERTY()
	TArray<class UCsSimpleWidget*> Pool;

	uint16 PoolIndex;

	TArray<class UCsSimpleWidget*> ActiveWidgets;

	//virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	class UCsSimpleWidget* Allocate();

	virtual void DeAllocate(const int32 &Index);

// Show
#pragma region

	virtual class UCsSimpleWidget* Show(FCsSimpleWidgetPayload* Payload, UObject* InOwner, UObject* InParent);

#pragma endregion Show
};