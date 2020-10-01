// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Sound/CsSoundPooled.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsSoundPooledImpl.generated.h"

class UAudioComponent;
class UDamageType;

namespace NCsPooledObject {
	namespace NCache {
		struct ICache; } }

namespace NCsPooledObject {
	namespace NPayload {
		struct IPayload; } }

namespace NCsSound {
	namespace NPayload {
		struct IPayload; } }

/**
* 
*/
UCLASS()
class CSCORE_API ACsSoundPooledImpl : public AActor,
									  public ICsUpdate,
									  public ICsPooledObject,
									  public ICsSoundPooled
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Category = Sound, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sound,Audio,Audio|Components|Audio"))
	UAudioComponent* AudioComponent;

	// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	NCsPooledObject::NCache::ICache* Cache;

	void ConstructCache();

// ICsPooledObject
#pragma region
public:

	NCsPooledObject::NCache::ICache* GetCache() const;

	void Allocate(NCsPooledObject::NPayload::IPayload* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// ICsSoundPooled
#pragma region
public:

	FORCEINLINE UAudioComponent* GetAudioComponent() const
	{
		return AudioComponent;
	}

#pragma endregion ICsSoundPooled

public:

	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	FECsSound Type;

	void Play(NCsSound::NPayload::IPayload* Payload);
	void Stop();
};