// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Sound/CsSoundPooled.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsSoundPooledImpl.generated.h"

class UAudioComponent;
class USoundAttenuation;
struct ICsPooledObjectCache;
struct ICsPooledObjectPayload;

UCLASS()
class CSCORE_API ACsSoundPooledImpl : public AActor,
									  public ICsUpdate,
									  public ICsPooledObject,
									  public ICsSoundPooled
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Sound, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sound,Audio,Audio|Components|Audio"))
	UAudioComponent* AudioComponent;

private:

	UPROPERTY()
	USoundAttenuation* SoundAttenuation;

	// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	ICsPooledObjectCache* Cache;

	void ConstructCache();

// ICsPooledObject
#pragma region
public:

	ICsPooledObjectCache* GetCache() const;

	void Allocate(ICsPooledObjectPayload* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// ICsSoundPooled
#pragma region
public:

	FORCEINLINE UAudioComponent* GetAudioComponent() const
	{
		return AudioComponent;
	}

	FORCEINLINE USoundAttenuation* GetSoundAttenuation() const
	{
		return SoundAttenuation;
	}

#pragma endregion ICsSoundPooled

public:

	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	FECsSoundType Type;

	bool Play();
	bool Stop();
};