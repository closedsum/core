// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Managers/CsManager.h"
#include "Managers/Widget/CsPooledWidget.h"
#include "CsManager_Widget.generated.h"

#define CS_POOLED_WIDGET_PAYLOAD_SIZE 256

class FCsManager_Widget : public TCsManager_PooledObjects_TMap<TCsSimpleWidgetType, UCsPooledWidget, FCsWidgetPayload, CS_POOLED_WIDGET_PAYLOAD_SIZE>
{
public:
	~FCsManager_Widget();

	virtual void DeconstructObject(UCsPooledWidget* o) override;
	virtual FString GetObjectName(UCsPooledWidget* o) override;
	virtual const FString& EnumTypeToString(const TCsSimpleWidgetType &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void Log(const FString& log) override;
};

UCLASS()
class CSCORE_API UICsManager_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

protected:

	FCsManager_Widget * Internal;

public:

	//static ACsManager_Projectile* Get(UWorld* InWorld);

	TWeakObjectPtr<UWorld> CurrentWorld;

	UWorld* GetCurrentWorld();

	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void Clear();

	void Shutdown();

	TMap<TCsSimpleWidgetType, UClass*> ClassMap;

	virtual UCsPooledWidget* ConstructObject(const TCsSimpleWidgetType &Type);

	void CreatePool(const TCsSimpleWidgetType &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void CreatePool(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, const int32 &Size);
	void AddToPool(const TCsSimpleWidgetType &Type, UCsPooledWidget* Object);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void AddToPool(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, UCsPooledWidget* Object);
	void AddToActivePool(const TCsSimpleWidgetType &Type, UCsPooledWidget* Object);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void AddToActivePool(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, UCsPooledWidget* Object);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void GetAllActiveObjects(TArray<UCsPooledWidget*> &OutObjects);

	const TArray<class UCsPooledWidget*>* GetObjects(const TCsSimpleWidgetType& Type);

	int32 GetActivePoolSize(const TCsSimpleWidgetType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	int32 GetActivePoolSize(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type);
	bool IsExhausted(const TCsSimpleWidgetType &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	bool IsExhausted(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type);
	bool DeAllocate(const TCsSimpleWidgetType &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	bool DeAllocate(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void DeAllocateAll();

	FCsWidgetPayload* AllocatePayload();

	UCsPooledWidget* Display(const TCsSimpleWidgetType &Type, FCsWidgetPayload &Payload);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	UCsPooledWidget* Display(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, FCsWidgetPayload &Payload);
	UCsPooledWidget* Display(const TCsSimpleWidgetType &Type, FCsWidgetPayload* Payload);

	template<typename T>
	T* Display(const TCsSimpleWidgetType &Type, FCsWidgetPayload* Payload)
	{
		return Cast<T>(Display(Type, Payload));
	}
};