// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Types/CsTypes_Sound.h"
#include "Managers/CsPooledActor.h"
#include "CsSound.generated.h"

USTRUCT(BlueprintType)
struct FCsSoundCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class ACsSound> Sound;
	TWeakObjectPtr<USoundCue> Cue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsSoundType::Type> Type_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TEnumAsByte<ECsSoundPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float Duration;

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

	void Set(const uint16 &InIndex, ACsSound* InSound)
	{
		Index = InIndex;
		Sound = InSound;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		ActiveIndex		   = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;

		IsAllocated = true;

		Owner			 = InOwner;
		Cue				 = InElement->Get();
		Parent			 = InParent;
		Type_Script		 = InElement->Type;
		Type			 = (uint8)Type_Script;
		Priority		 = InElement->Priority;
		Duration		 = InElement->Duration;
		IsLooping		 = InElement->IsLooping;
		VolumeMultiplier = InElement->VolumeMultiplier;
		PitchMultiplier  = InElement->PitchMultiplier;
		Bone			 = InElement->Bone;
		Time			 = InTime;
		RealTime		 = InRealTime;
		Frame			 = InFrame;

		if (InObject && OnDeAllocate)
		{
			DelegateInvoker = (UObject*)InObject;
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.AddUObject(InObject, OnDeAllocate);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.AddUObject(InObject, OnDeAllocate);
		}
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, InOwner, nullptr, InObject, OnDeAllocate);

		Location = InLocation;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &inFrame, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, inFrame, nullptr, InLocation, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, const FVector &InLocation)
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;

		IsAllocated = true;

		Owner			 = InOwner;
		Cue				 = InElement->Get();
		Parent			 = InParent;
		Type_Script		 = InElement->Type;
		Type			 = (uint8)Type_Script;
		Priority		 = InElement->Priority;
		Duration		 = InElement->Duration;
		IsLooping		 = InElement->IsLooping;
		VolumeMultiplier = InElement->VolumeMultiplier;
		PitchMultiplier	 = InElement->PitchMultiplier;
		Bone			 = InElement->Bone;
		Time			 = InTime;
		RealTime		 = InRealTime;
		Frame			 = InFrame;
		Location		 = InLocation;
	}

	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, InOwner, InParent, FVector::ZeroVector);
	}

	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, const FVector &InLocation)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, InOwner, InLocation);
	}

	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame, const FVector &InLocation)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, nullptr, InLocation);
	}

	void Init(const uint16& InActiveIndex, FCsSoundElement* InElement, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, InElement, InTime, InRealTime, InFrame, nullptr, nullptr, FVector::ZeroVector);
	}

	virtual void Reset() override
	{
		Super::Reset();

		Cue.Reset();
		Cue   = nullptr;
		Type_Script		 = ECsSoundType::s3D;
		Type			 = (uint8)Type_Script;
		Priority		 = ECsSoundPriority::VeryLow;
		Duration		 = 0.0f;
		IsLooping		 = false;
		VolumeMultiplier = 1.0f;
		PitchMultiplier  = 1.0f;
		Bone			 = NAME_None;
	}

	ACsSound* GetSound() { return Sound.IsValid() ? Sound.Get() : nullptr; }
	USoundCue* GetCue() { return Cue.IsValid() ? Cue.Get() : nullptr; }
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
	FCsSoundCache Cache;

	void Init(const int32 &Index);

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, const FVector &InLocation);
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &InLocation);
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &InLocation);
	void Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame);

	virtual void DeAllocate() override;

	//bool Play(USoundCue* Cue, UObject* Parent, const float &StartTime=0.0f, const FVector &Location = FVector::ZeroVector);
	bool Play();
	bool Stop();
};