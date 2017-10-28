// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsManager.h"
#include "CsManager_Sound.generated.h"

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

	TArray<class ACsSound*> ActiveSounds;

	UPROPERTY()
	TArray<class ACsSound*> Pool;

	uint8 PoolIndex;

	class ACsSound* Allocate();

	virtual void DeAllocate(const int32 &Index) override;

	class ACsSound* Play(struct FCsSoundElement* InSound, UObject* Owner, UObject* Parent);
	class ACsSound* Play(struct FCsSoundElement* InSound, UObject* InOwner);
	class ACsSound* Play(struct FCsSoundElement* InSound);
	class ACsSound* Play(struct FCsSoundElement* InSound, UObject* InOwner, const FVector &Location);
	
	template<typename T>
	void Play(class ACsSound* OutSound, struct FCsSoundElement* InSound, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Play(class ACsSound* OutSound, struct FCsSoundElement* InSound, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Play(class ACsSound* OutSound, struct FCsSoundElement* InSound, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
	template<typename T>
	void Play(class ACsSound* OutSound, struct FCsSoundElement* InSound, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));
};