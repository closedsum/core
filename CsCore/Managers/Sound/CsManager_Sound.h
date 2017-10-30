// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsManager.h"
#include "Types/CsTypes.h"
#include "CsManager_Sound.generated.h"

// OnAllocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerSound_OnAllocate, const int32&, PoolIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerSound_OnAllocate, const uint16&);
// OnDeAllocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerSound_OnDeAllocate, const int32&, PoolIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerSound_OnDeAllocate, const uint16&);

#define CS_SOUND_POOL_SIZE 32
#define CS_MAX_CONCURRENT_SOUNDS 16

UCLASS()
class CSCORE_API ACsManager_Sound : public ACsManager
{
	GENERATED_UCLASS_BODY()

	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const int32 &Size) override;
	virtual void PostActorCreated() override;

	virtual void OnTick(const float &DeltaSeconds) override;

	static ACsManager_Sound* Get(UWorld* InWorld);

	TSubclassOf<class ACsSound> SoundClass;

	UPROPERTY()
	TArray<class ACsSound*> ActiveSounds;

	UPROPERTY()
	TArray<class ACsSound*> Pool;

	uint8 PoolIndex;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsSound* Allocate();

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManagerSound_OnAllocate OnAllocate_ScriptEvent;

	FBindableEvent_CsManagerSound_OnAllocate OnAllocate_Event;

	virtual void DeAllocate(const int32 &Index) override;

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManagerSound_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsManagerSound_OnDeAllocate OnDeAllocate_Event;

	class ACsSound* Play(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent);
	class ACsSound* Play(FCsSoundElement* InSound, UObject* InOwner);
	class ACsSound* Play(FCsSoundElement* InSound);
	class ACsSound* Play(FCsSoundElement* InSound, UObject* InOwner, const FVector &Location);
	
	template<typename T>
	void Play(class ACsSound* OutSound, FCsSoundElement* InSound, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Play(class ACsSound* OutSound, FCsSoundElement* InSound, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Play(class ACsSound* OutSound, FCsSoundElement* InSound, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Play(class ACsSound* OutSound, FCsSoundElement* InSound, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsSound* Play_Script(FCsSoundElement &InSound, UObject* InOwner, UObject* InParent);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsSound* Play_ScriptEX(FCsSoundElement &InSound, UObject* InOwner, const FVector &Location);
};