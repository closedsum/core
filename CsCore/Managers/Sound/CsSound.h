// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Sound.h"
#include "Managers/CsPooledActor.h"
#include "CsSound.generated.h"

USTRUCT(BlueprintType)
struct FCsSoundCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class ACsSound> Sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<USoundCue> Cue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FECsSoundType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsSoundPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool bSpatialize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool IsLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FName Bone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;

	FCsSoundCache()
	{
		Reset();
	}

	~FCsSoundCache(){}

	void Set(const int32 &InIndex, ACsSound* InSound)
	{
		Index = InIndex;
		Sound = InSound;
	}

	void Init(FCsSoundPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		IsAllocated = true;

		Owner			 = Payload->GetOwner();
		Cue				 = Payload->GetCue();
		Parent			 = Payload->GetParent();
		Priority		 = Payload->Priority;
		IsLooping		 = Payload->IsLooping;

		SetLifeTime(IsLooping ? 0.0f : Payload->Duration);

		VolumeMultiplier = Payload->VolumeMultiplier;
		PitchMultiplier	 = Payload->PitchMultiplier;
		Bone			 = Payload->Bone;
		Time			 = InTime;
		RealTime		 = InRealTime;
		SetFrame(InFrame);
		Location		 = Payload->Location;
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Cue.Reset();
		Cue   = nullptr;
		Priority		 = ECsSoundPriority::VeryLow;
		bSpatialize		 = false;
		IsLooping		 = false;
		VolumeMultiplier = 1.0f;
		PitchMultiplier  = 1.0f;
		Bone			 = NAME_None;
	}

	FORCEINLINE ACsSound* GetSound() { return Sound.IsValid() ? Sound.Get() : nullptr; }
	template<typename T>
	T* GetSound() { return Cast<T>(GetSound()); }
	FORCEINLINE USoundCue* GetCue() { return Cue.IsValid() ? Cue.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsSound : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Sound, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sound,Audio,Audio|Components|Audio"))
	UAudioComponent* AudioComponent;

private:
	USoundAttenuation* DefaultAttenuation;
public:

	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	FECsSoundType Type;

	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	FCsSoundCache Cache;

	void Init(const int32 &Index, const FECsSoundType &InType);
	void Init(const int32 &Index);

	void Allocate(FCsSoundPayload* Payload);

	virtual void DeAllocate() override;

	bool Play();
	bool Stop();
};