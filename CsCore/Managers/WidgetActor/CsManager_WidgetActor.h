// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_UI.h"
#include "CsManager_WidgetActor.generated.h"

typedef FString(*TCsWidgetActorTypeToString)(const ECsWidgetActorType::Type&);

UCLASS()
class CSCORE_API ACsManager_WidgetActor : public ACsManager
{
	GENERATED_UCLASS_BODY()

	virtual void Shutdown() override;

	TCsWidgetActorTypeToString WidgetActorClassToString;

	void Init(TCsWidgetActorTypeToString InWidgetActorClassToString);

	virtual void Destroyed() override;
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	virtual void OnTick(const float &DeltaSeconds) override;

	static ACsManager_WidgetActor* Get(UWorld* InWorld);

	TMap<TCsWidgetActorType, TArray<class ACsWidgetActor*>> ActiveWidgetActors;

	virtual int32 GetActivePoolSize(const uint8 &Type) override;

	TMap<TCsWidgetActorType, uint8> PoolSizes;

	UPROPERTY()
	TArray<class ACsWidgetActor*> Pool;

	TMap<TCsWidgetActorType, TArray<class ACsWidgetActor*>> Pools;

	TMap<TCsWidgetActorType, uint8> PoolIndices;

	class ACsWidgetActor* Allocate(const TCsWidgetActorType &ClassType);

	virtual void DeAllocate(const uint8 &Type, const int32 &Index) override;

	class ACsWidgetActor* Display(const TCsWidgetActorType &ClassType, class UCsUserWidget* InWidget, UObject* InOwner, UObject* Parent);
	class ACsWidgetActor* Display(const TCsWidgetActorType &ClassType, class UCsUserWidget* InWidget, UObject* InOwner);
	class ACsWidgetActor* Display(const TCsWidgetActorType &ClassType, class UCsUserWidget* InWidget);

	template<typename T>
	void Display(const TCsWidgetActorType &ClassType, class ACsWidgetActor* OutWidgetActor, class UCsUserWidget* InWidget, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Display(const TCsWidgetActorType &ClassType, class ACsWidgetActor* OutWidgetActor, class UCsUserWidget* InWidget, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Display(const TCsWidgetActorType &ClassType, class ACsWidgetActor* OutWidgetActor, class UCsUserWidget* InWidget, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
};