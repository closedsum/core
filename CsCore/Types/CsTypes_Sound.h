// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Sound/SoundCue.h"

#include "CsTypes_Sound.generated.h"
#pragma once

// Sound
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSoundType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsSoundType() {}
	FECsSoundType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsSoundType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsSoundType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsSoundType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsSoundType : public TCsEnumStructMap<FECsSoundType, uint8>
{
protected:
	EMCsSoundType() {}
	EMCsSoundType(const EMCsSoundType &) = delete;
	EMCsSoundType(EMCsSoundType &&) = delete;
public:
	~EMCsSoundType() {}
private:
	static EMCsSoundType* Instance;

public:
	static EMCsSoundType& Get();
};

UENUM(BlueprintType)
namespace ECsSoundPriority
{
	enum Type
	{
		VeryLow				 UMETA(DisplayName = "Very Low"),
		Low					 UMETA(DisplayName = "Low"),
		Medium				 UMETA(DisplayName = "Medium"),
		High				 UMETA(DisplayName = "High"),
		VeryHigh			 UMETA(DisplayName = "Very High"),
		ECsSoundPriority_MAX UMETA(Hidden),
	};
}

typedef ECsSoundPriority::Type TCsSoundPriority;

struct CSCORE_API EMCsSoundPriority : public TCsEnumMap<ECsSoundPriority::Type>
{
protected:
	EMCsSoundPriority() {}
	EMCsSoundPriority(const EMCsSoundPriority &) = delete;
	EMCsSoundPriority(EMCsSoundPriority &&) = delete;
public:
	~EMCsSoundPriority() {}
private:
	static EMCsSoundPriority* Instance;

public:
	static EMCsSoundPriority& Get();
};

namespace ECsSoundPriority
{
	namespace Ref
	{
		extern CSCORE_API const Type VeryLow;
		extern CSCORE_API const Type Low;
		extern CSCORE_API const Type Medium;
		extern CSCORE_API const Type High;
		extern CSCORE_API const Type VeryHigh;
		extern CSCORE_API const Type ECsSoundPriority_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return EMCsSoundPriority::Get().ToString(EType);
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return EMCsSoundPriority::Get().ToType(String);
	}
}

USTRUCT(BlueprintType)
struct FCsSoundElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TAssetPtr<class USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	FECsSoundType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TEnumAsByte<ECsSoundPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	bool bSpatialize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (ClampMin = "0.05", UIMin = "0.05"))
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	bool IsLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	FName Bone;

private:
	UPROPERTY(Transient)
	class USoundCue* Sound_Internal;

public:
	FCsSoundElement()
	{
		CS_SET_BLUEPRINT_BITFLAG(Sound_LoadFlags, ECsLoadFlags::Game);

		Type = EMCsSoundType::Get().GetMAX();
		Priority = ECsSoundPriority::Medium;
		Duration = 0.05f;
		VolumeMultiplier = 1.0f;
		PitchMultiplier = 1.0f;
		Bone = NAME_None;
	}

	FORCEINLINE FCsSoundElement& operator=(const FCsSoundElement& B)
	{
		Sound = B.Sound;
		Sound_LoadFlags = B.Sound_LoadFlags;
		Type = B.Type;
		Priority = B.Priority;
		Duration = B.Duration;
		IsLooping = B.IsLooping;
		VolumeMultiplier = B.VolumeMultiplier;
		PitchMultiplier = B.PitchMultiplier;
		Bone = B.Bone;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsSoundElement& B) const
	{
		return Sound == B.Sound &&
				Sound_LoadFlags == B.Sound_LoadFlags &&
				Type == B.Type &&
				Priority == B.Priority &&
				Duration == B.Duration &&
				IsLooping == B.IsLooping &&
				VolumeMultiplier == B.VolumeMultiplier &&
				PitchMultiplier == B.PitchMultiplier &&
				Bone == B.Bone;
	}

	FORCEINLINE bool operator!=(const FCsSoundElement& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(USoundCue* InSound)
	{
		Sound = TAssetPtr<USoundCue>(InSound);
		Sound_Internal = InSound;
	}

	FORCEINLINE USoundCue* Get() const
	{
		return Sound_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsFpvSoundElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Sound")
	FCsSoundElement Sound1P;

	UPROPERTY(EditAnywhere, Category = "Sound")
	FCsSoundElement Sound3P;

public:

	FORCEINLINE FCsFpvSoundElement& operator=(const FCsFpvSoundElement& B)
	{
		Sound1P = B.Sound1P;
		Sound3P = B.Sound3P;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsFpvSoundElement& B) const
	{
		return Sound1P == B.Sound1P && Sound3P == B.Sound3P;
	}

	FORCEINLINE bool operator!=(const FCsFpvSoundElement& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FCsSoundElement* Get(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return &Sound1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return &Sound3P;
		return nullptr;
	}

	FORCEINLINE USoundCue* GetCue(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Sound1P.Get();
		if (ViewType == ECsViewType::ThirdPerson)
			return Sound3P.Get();
		return nullptr;
	}
};

USTRUCT(BlueprintType)
struct FCsSoundPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<UObject> Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<UObject> Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<class USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TEnumAsByte<ECsSoundPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	bool bSpatialize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload", meta = (ClampMin = "0.05", UIMin = "0.05"))
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	bool IsLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName Bone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FVector Location;

	FCsSoundPayload(){}
	~FCsSoundPayload(){}

	FORCEINLINE void Set(FCsSoundElement* Element)
	{
		Sound = Element->Get();
		Priority = Element->Priority;
		bSpatialize = Element->bSpatialize;
		Duration = Element->Duration;
		IsLooping = Element->IsLooping;
		VolumeMultiplier = Element->VolumeMultiplier;
		PitchMultiplier = Element->PitchMultiplier;
		Bone = Element->Bone;
	}

	FORCEINLINE void Reset()
	{
		Instigator.Reset();
		Instigator = nullptr;
		Owner.Reset();
		Owner = nullptr;
		Parent.Reset();
		Parent = nullptr;
		Sound = nullptr;
		Priority = ECsSoundPriority::Medium;
		bSpatialize = true;
		Duration = 0.05f;
		IsLooping = false;
		VolumeMultiplier = 1.0f;
		PitchMultiplier = 1.0f;
		Bone = NAME_None;
		Location = FVector::ZeroVector;
	}

	FORCEINLINE UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }

	FORCEINLINE UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetOwner() { return Cast<T>(GetOwner()); }

	FORCEINLINE UObject* GetParent() { return Parent.IsValid() ? Parent.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetParent() { return Cast<T>(GetParent()); }

	FORCEINLINE USoundCue* GetCue() { return Sound.IsValid() ? Sound.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetCue() { return Cast<T>(GetCue()); }
};

#pragma endregion Sound