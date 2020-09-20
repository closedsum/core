// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/CsTypes_View.h"
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsTypes_Sound.generated.h"
#pragma once

// Sound
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSound)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSound)

struct CSCORE_API EMCsSound : public TCsEnumStructMap<FECsSound, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSound, FECsSound, uint8)
};

namespace NCsSound
{
	typedef FECsSound Type;

	namespace Ref
	{
	}

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Sound

// SoundPriority
#pragma region

UENUM(BlueprintType)
enum class ECsSoundPriority : uint8
{
	VeryLow				 UMETA(DisplayName = "Very Low"),
	Low					 UMETA(DisplayName = "Low"),
	Medium				 UMETA(DisplayName = "Medium"),
	High				 UMETA(DisplayName = "High"),
	VeryHigh			 UMETA(DisplayName = "Very High"),
	ECsSoundPriority_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsSoundPriority : public TCsEnumMap<ECsSoundPriority>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSoundPriority, ECsSoundPriority)
};

namespace NCsSoundPriority
{
	typedef ECsSoundPriority Type;

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

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
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

// SoundDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate a Sound.
*/
UENUM(BlueprintType)
enum class ECsSoundDeallocateMethod : uint8
{
	/** If a Sound is attached to a parent object,
		  LifeTime == 0.of means the Sound object will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the Sound object.
		If a Sound is NOT attached to a parent object,
		  LifeTime == 0.0f means the Sound object will stay active forever.
		  LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
		   the Sound object has been allocated. */
	LifeTime					 UMETA(DisplayName = "LifeTime"),
	/** */
	Complete					 UMETA(DisplayName = "Complete"),
	ECsSoundDeallocateMethod_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsSoundDeallocateMethod final : public TCsEnumMap<ECsSoundDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSoundDeallocateMethod, ECsSoundDeallocateMethod)
};

namespace NCsSoundDeallocateMethod
{
	typedef ECsSoundDeallocateMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type LifeTime;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsSoundDeallocateMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion SoundDeallocateMethod

// FCsSoundElement
#pragma region

class USoundCue;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSoundElement
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TSoftObjectPtr<USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	UPROPERTY(Transient)
	USoundCue* Sound_Internal;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	FECsSound Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	ECsSoundPriority Priority;

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

public:

	FCsSoundElement() :
		Sound_LoadFlags(0),
		Sound_Internal(nullptr),
		bSpatialize(false),
		IsLooping(false)
	{
		Type = EMCsSound::Get().GetMAX();
		Priority = ECsSoundPriority::Medium;
		Duration = 0.05f;
		VolumeMultiplier = 1.0f;
		PitchMultiplier = 1.0f;
		Bone = NAME_None;
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

	FORCEINLINE USoundCue* Get() const
	{
		return Sound_Internal;
	}
};

#pragma endregion FCsSoundElement

// FCsFpvSoundElement
#pragma region

/**
*/
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

// NoiseEvent
#pragma region

/**
*/
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

// FCsSound
#pragma region

class USoundBase;
class USoundAttenuation;

/**
* Container holding general information for a Sound Asset.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSound
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> Sound;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(Transient, BlueprintReadOnly)
	USoundBase* Sound_Internal;

	/** The Sound Type. This is used to group Sound into different categories 
	    and can be used by a Manager pooling Sound objects to Spawn the correct
		Sound object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsSound Type;

	/** Soft reference to Sound Attenuation Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundAttenuation> Attenuation;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Attenuation_LoadFlags;

	/** Hard reference to a Sound Attenuation Asset. */
	UPROPERTY(Transient, BlueprintReadOnly)
	USoundAttenuation* Attenuation_Internal;

	/** Condition to determine when to deallocate the Sound object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsSoundDeallocateMethod DeallocateMethod;

	/** Valid if the DeallocateMethod == ECsSoundDeallocateMethod::LifeTime.
		- If a Sound IS attached to a Parent object, 
		   LifeTime == 0.of means the Sound object will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the Sound object.
	    - If a Sound is NOT attached to a Parent object,
		   LifeTime == 0.0f means the Sound object will stay active forever.
		   LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
	        the FX object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** Valid if the Sound is attached to a Parent object or when an Sound object is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the Sound is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Bone;

	/** Which of the components of Transform to apply to the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the FX.
		If the Sound is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;

public:

	FCsSound() :
		Sound(nullptr),
		Sound_LoadFlags(0),
		Sound_Internal(nullptr),
		Type(),
		Attenuation(nullptr),
		Attenuation_LoadFlags(0),
		Attenuation_Internal(nullptr),
		DeallocateMethod(ECsSoundDeallocateMethod::Complete),
		LifeTime(0.0f),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity)
	{
	}
	
	/**
	* Get the Hard reference to the Sound Asset.
	*
	* return Sound Asset
	*/
	FORCEINLINE USoundBase* Get() const
	{
		return Sound_Internal;
	}

	/**
	* Get the Hard reference to the Sound Attenuation Asset.
	*
	* return Sound Attenuation Asset
	*/
	FORCEINLINE USoundAttenuation* GetAttenuation() const
	{
		return Attenuation_Internal;
	}
};

#pragma endregion FCsSound