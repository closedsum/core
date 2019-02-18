// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Managers/CsManager.h"
#include "Managers/Widget/CsPooledWidget.h"
#include "CsManager_Widget.generated.h"

#define CS_POOLED_WIDGET_PAYLOAD_SIZE 256

class FCsManager_Widget : public TCsManager_PooledObjects_TMap<ECsSimpleWidgetType, UCsPooledWidget, FCsWidgetPayload, CS_POOLED_WIDGET_PAYLOAD_SIZE>
{
private:
	typedef TCsManager_PooledObjects_TMap<ECsSimpleWidgetType, UCsPooledWidget, FCsWidgetPayload, CS_POOLED_WIDGET_PAYLOAD_SIZE> Super;

public:
	~FCsManager_Widget();

	virtual void DeconstructObject(UCsPooledWidget* o) override;
	virtual FString GetObjectName(UCsPooledWidget* o) override;
	virtual const FString& EnumTypeToString(const ECsSimpleWidgetType &e) override;
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

	TMap<ECsSimpleWidgetType, UClass*> ClassMap;

	virtual UCsPooledWidget* ConstructObject(const ECsSimpleWidgetType &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void CreatePool(const ECsSimpleWidgetType& Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void AddToPool(const ECsSimpleWidgetType& Type, UCsPooledWidget* Object);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void AddToActivePool(const ECsSimpleWidgetType& Type, UCsPooledWidget* Object);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void GetAllActiveObjects(TArray<UCsPooledWidget*> &OutObjects);

	const TArray<class UCsPooledWidget*>* GetObjects(const ECsSimpleWidgetType& Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	int32 GetActivePoolSize(const ECsSimpleWidgetType& Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	bool IsExhausted(const ECsSimpleWidgetType& Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	bool DeAllocate(const ECsSimpleWidgetType& Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	void DeAllocateAll();

	FCsWidgetPayload* AllocatePayload();

	UFUNCTION(BlueprintCallable, Category = "Manager Widget")
	UCsPooledWidget* Display(const ECsSimpleWidgetType& Type, FCsWidgetPayload &Payload);
	UCsPooledWidget* Display(const ECsSimpleWidgetType& Type, FCsWidgetPayload* Payload);

	template<typename T>
	T* Display(const ECsSimpleWidgetType& Type, FCsWidgetPayload* Payload)
	{
		return Cast<T>(Display(Type, Payload));
	}
};