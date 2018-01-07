// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsManager.h"
#include "Types/CsTypes_Sound.h"
#include "CsManager_Sound.generated.h"

#define CS_SOUND_POOL_SIZE 32
#define CS_MAX_CONCURRENT_SOUNDS 16

UCLASS()
class CSCORE_API ACsManager_Sound : public ACsManager
{
	GENERATED_UCLASS_BODY()

private:

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();

public:

	static void Init(UObject* InOwner);
	static ACsManager_Sound* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const int32 &Size) override;
	virtual void PostActorCreated() override;
	virtual void OnTick(const float &DeltaSeconds) override;

	TSubclassOf<class ACsSound> SoundClass;

	UPROPERTY()
	TArray<class ACsSound*> ActiveSounds;

	UPROPERTY()
	TArray<class ACsSound*> Pool;

	uint8 PoolIndex;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsSound* Allocate();

	virtual void DeAllocate(const int32 &Index) override;

// Play
#pragma region
public:

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

#pragma endregion Play

// Stop
#pragma region
public:

	void Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent);

#pragma endregion Stop

};