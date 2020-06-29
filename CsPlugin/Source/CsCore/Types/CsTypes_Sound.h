// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Types/CsTypes_Load.h"

#include "Sound/SoundCue.h"

#include "CsTypes_Sound.generated.h"
#pragma once

// SoundType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSoundType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSoundType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSoundType)

struct CSCORE_API EMCsSoundType : public TCsEnumStructMap<FECsSoundType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSoundType, FECsSoundType, uint8)
};

#pragma endregion SoundType

// SoundPriority
#pragma region

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

struct CSCORE_API EMCsSoundPriority : public TCsEnumMap<ECsSoundPriority::Type>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSoundPriority, ECsSoundPriority::Type)
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
}

#pragma endregion SoundPriority

// FCsSoundCue
#pragma region

class USoundCue;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSoundCue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	USoundCue* Sound_Internal;

	FCsSoundCue() :
		Sound(),
		Sound_LoadFlags(0),
		Sound_Internal(nullptr)
	{
	}

	FORCEINLINE USoundCue* Get() const { return Sound_Internal; }
};

#pragma endregion FCsSoundCue

// FCsSoundElement
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSoundElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TSoftObjectPtr<class USoundCue> Sound;

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
	FCsSoundElement() :
		Sound_LoadFlags(0),
		bSpatialize(false),
		IsLooping(false),
		Sound_Internal(nullptr)
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
		Sound = TSoftObjectPtr<USoundCue>(InSound);
		Sound_Internal = InSound;
	}

	FORCEINLINE USoundCue* Get() const
	{
		return Sound_Internal;
	}
};

#pragma endregion FCsSoundElement

// FCsFpvSoundElement
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvSoundElement
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

	FORCEINLINE FCsSoundElement* Get(const ECsViewType& ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return &Sound1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return &Sound3P;
		return nullptr;
	}

	FORCEINLINE USoundCue* GetCue(const ECsViewType& ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Sound1P.Get();
		if (ViewType == ECsViewType::ThirdPerson)
			return Sound3P.Get();
		return nullptr;
	}
};

#pragma endregion FCsFpvSoundElement

// FCsSoundPayload
#pragma region

struct CSCORE_API FCsSoundPayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	FCsTime Time;

	TWeakObjectPtr<class USoundCue> Sound;

	TEnumAsByte<ECsSoundPriority::Type> Priority;

	bool bSpatialize;

	float Duration;

	bool IsLooping;

	float VolumeMultiplier;

	float PitchMultiplier;

	FName Bone;

	FVector Location;

	FCsSoundPayload()
	{
		Reset();
	}
	~FCsSoundPayload(){}

// ICsPooledObjectPayload
#pragma region
public:

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	UObject* GetInstigator() const
	{
		return Instigator;
	}

	UObject* GetOwner() const
	{
		return Owner;
	}

	UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE const FCsTime& GetTime() const 
	{
		return Time;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;

		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;

		Time.Reset();

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

#pragma endregion ICsPooledObjectPayload

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

	FORCEINLINE USoundCue* GetCue() { return Sound.IsValid() ? Sound.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetCue() { return Cast<T>(GetCue()); }
};

#pragma endregion FCsSoundPayload

// NoiseEvent
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsNoiseEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsNoiseEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsNoiseEvent)

struct CSCORE_API EMCsNoiseEvent final : public TCsEnumStructMap<FECsNoiseEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsNoiseEvent, FECsNoiseEvent, uint8)
};

namespace NCsNoiseEvent
{
	typedef FECsNoiseEvent Type;
}

#pragma endregion NoiseEvent