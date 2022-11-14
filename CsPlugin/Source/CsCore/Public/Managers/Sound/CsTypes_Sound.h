// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_AttachDetach.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Sound.generated.h"

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
	typedef EMCsSound EnumMapType;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TSoftObjectPtr<USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Sound")
	USoundCue* Sound_Internal;

	FCsSoundCue() :
		Sound(),
		Sound_LoadFlags(0),
		Sound_Internal(nullptr)
	{
	}

	FORCEINLINE USoundCue* Get() const { return Sound_Internal; }

	FORCEINLINE USoundCue* GetChecked() const
	{
		checkf(Sound.ToSoftObjectPath().IsValid(), TEXT("FCsSoundCue::GetChecked: Sound is NULL."));

		checkf(Sound_Internal, TEXT("FCsSoundCue::GetChecked: Sound is NULL. Sound @ %s is NOT Loaded."), *(Sound.ToSoftObjectPath().ToString()));

		return Sound_Internal;
	}

	FORCEINLINE USoundCue* GetChecked(const FString& Context) const
	{
		checkf(Sound.ToSoftObjectPath().IsValid(), TEXT("%s: Sound is NULL."), *Context);

		checkf(Sound_Internal, TEXT("%s: Sound is NULL. Sound @ %s is NOT Loaded."), *Context, *(Sound.ToSoftObjectPath().ToString()));

		return Sound_Internal;
	}
};

#pragma endregion FCsSoundCue

// FCsSoundBase
#pragma region

class USoundBase;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSoundBase
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TSoftObjectPtr<USoundBase> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Sound")
	USoundBase* Sound_Internal;

	FCsSoundBase() :
		Sound(),
		Sound_LoadFlags(0),
		Sound_Internal(nullptr)
	{
	}

	FORCEINLINE USoundBase* Get() const { return Sound_Internal; }

	FORCEINLINE USoundBase** GetPtr() { return &Sound_Internal; }

	FORCEINLINE USoundBase* GetChecked() const
	{
		checkf(Sound.ToSoftObjectPath().IsValid(), TEXT("FCsSoundBase::GetChecked: Sound is NULL."));

		checkf(Sound_Internal, TEXT("FCsSoundBase::GetChecked: Sound is NULL. Sound @ %s is NOT Loaded."), *(Sound.ToSoftObjectPath().ToString()));

		return Sound_Internal;
	}

	FORCEINLINE USoundBase* GetChecked(const FString& Context) const
	{
		checkf(Sound.ToSoftObjectPath().IsValid(), TEXT("%s: Sound is NULL."), *Context);

		checkf(Sound_Internal, TEXT("%s: Sound is NULL. Sound @ %s is NOT Loaded."), *Context, *(Sound.ToSoftObjectPath().ToString()));

		return Sound_Internal;
	}
};

#pragma endregion FCsSoundCue

// FCsTArraySoundBase
#pragma region

class USoundBase;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoundBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TArray<TSoftObjectPtr<USoundBase>> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sounds_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Sound")
	TArray<USoundBase*> Sounds_Internal;

public:

	FCsTArraySoundBase() :
		Sounds(),
		Sounds_LoadFlags(0),
		Sounds_Internal()
	{
	}

	FORCEINLINE const TArray<USoundBase*>& Get() const { return Sounds_Internal; }

	FORCEINLINE TArray<USoundBase*>* GetPtr() { return &Sounds_Internal; }
	FORCEINLINE const TArray<USoundBase*>* GetPtr() const { return &Sounds_Internal; }

	/**
	* Get the Hard references to the array of Sounds of type: USoundBase.
	*
	* @param Context	The calling context.
	* return			Sounds
	*/
	FORCEINLINE const TArray<USoundBase*>& GetChecked(const FString& Context) const
	{ 
		checkf(Sounds.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);

		checkf(Sounds.Num() == Sounds_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to sounds, %d != %d."), *Context, Sounds.Num(), Sounds_Internal.Num());

		const int32 Count = Sounds.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<USoundBase>& SoftObject = Sounds[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: USoundBase[%d] is NULL."), *Context, I);

			USoundBase* Sound = Sounds_Internal[I];
	
			checkf(Sound, TEXT("%s: Sounds[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Sounds_Internal;
	}

	/**
	* Get the Hard references to the array of Sounds of type: USoundInterface.
	*
	* @param Context	The calling context.
	* return			Sounds
	*/
	FORCEINLINE const TArray<USoundBase*>& GetChecked() const
	{
		checkf(Sounds.Num() > CS_EMPTY, TEXT("FCsTArraySoundBase::GetChecked: No Sounds set."));

		checkf(Sounds.Num() == Sounds_Internal.Num(), TEXT("FCsTArraySoundBase::GetChecked: Mismatch between Soft and Hard references to sounds, %d != %d."), Sounds.Num(), Sounds_Internal.Num());

		const int32 Count = Sounds.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<USoundBase>& SoftObject = Sounds[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("FCsTArraySoundBase::GetChecked: Sounds[%d] is NULL."), I);

			USoundBase* Sound = Sounds_Internal[I];

			checkf(Sound, TEXT("FCsTArraySoundBase::GetChecked: Sounds[%d] has NOT been loaded from Path @ %s."), I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Sounds_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		checkf(Sounds.Num() > CS_EMPTY, TEXT("%s: No Sounds set."), *Context);

		checkf(Sounds.Num() == Sounds_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to sounds, %d != %d."), *Context, Sounds.Num(), Sounds_Internal.Num());

		const int32 Count = Sounds.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<USoundBase>& SoftObject = Sounds[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Sounds[%d] is NULL."), *Context, I);

			USoundBase* Sound = Sounds_Internal[I];

			checkf(Sound, TEXT("%s: Sounds[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return true;
	}
};

#pragma endregion FCsTArraySoundBase

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

// NCsSound::EDeallocateMethod
CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_1(NCsSound, EDeallocateMethod)

/**
* Container holding general information for a Sound Asset.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSound
{
	GENERATED_USTRUCT_BODY()

private:

	typedef NCsSound::EDeallocateMethod DeallocateMethodType;

public:

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TSoftObjectPtr<USoundBase> Sound;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Sound")
	USoundBase* Sound_Internal;

	/** The Sound Type. This is used to group Sound into different categories 
	    and can be used by a Manager pooling Sound objects to Spawn the correct
		Sound object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	FECsSound Type;

	/** Soft reference to Sound Attenuation Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TSoftObjectPtr<USoundAttenuation> Attenuation;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Attenuation_LoadFlags;

	/** Hard reference to a Sound Attenuation Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Sound")
	USoundAttenuation* Attenuation_Internal;

	/** Condition to determine when to deallocate the Sound object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	ECsSoundDeallocateMethod DeallocateMethod;

	/** Valid if the DeallocateMethod == ECsSoundDeallocateMethod::LifeTime.
		- If a Sound IS attached to a Parent object, 
		   LifeTime == 0.0f means the Sound object will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the Sound object.
	    - If a Sound is NOT attached to a Parent object,
		   LifeTime == 0.0f means the Sound object will stay active forever.
		   LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
	        the Sound object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** The amount to scale the Sound's duration. 
		Only Valid if DeallocateMethod == ECsSoundDeallocateMethod::Complete. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float DurationMultiplier;

	/** Valid if the Sound is attached to a Parent object or when an Sound object is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the Sound is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	FName Bone;

	/** Which of the components of Transform to apply to the Sound. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the Sound.
		If the Sound is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
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
		DurationMultiplier(1.0f),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity)
	{
	}
	
	FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *((DeallocateMethodType*)(&DeallocateMethod)); }

	/**
	* Get the Hard reference to the Sound Asset.
	*
	* return Sound Asset
	*/
	FORCEINLINE USoundBase* Get() const { return Sound_Internal; }

	/**
	* Get the Hard reference to the Sound Asset.
	*
	* @param Context	The calling context.
	* return			Sound Asset
	*/
	FORCEINLINE USoundBase* GetChecked(const FString& Context) const
	{
		checkf(Sound.ToSoftObjectPath().IsValid(), TEXT("%s: Sound is NULL or the Path is NOT Valid."), *Context);

		checkf(Sound_Internal, TEXT("%s: Failed to load Sound @ %s."), *Context, *(Sound.ToSoftObjectPath().ToString()));

		return Sound_Internal;
	}

	/**
	* Get the Hard reference to the Sound Asset.
	*
	* return Sound Asset
	*/
	FORCEINLINE USoundBase* GetChecked() const
	{
		checkf(Sound.ToSoftObjectPath().IsValid(), TEXT("FCsSound::GetChecked: Sound is NULL or the Path is NOT Valid."));

		checkf(Sound_Internal, TEXT("FCsSound::GetChecked: Failed to load Sound @ %s."), *(Sound.ToSoftObjectPath().ToString()));

		return Sound_Internal;
	}

	USoundBase* SafeLoad(const FString& Context) const;

	/**
	* Get the Hard reference to the Sound Attenuation Asset.
	*
	* return Sound Attenuation Asset
	*/
	FORCEINLINE USoundAttenuation* GetAttenuation() const
	{
		return Attenuation_Internal;
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void Reset();
};

#pragma endregion FCsSound

// NCsSound::NPayload::EChange
#pragma region

namespace NCsSound
{
	namespace NPayload
	{
		enum class EChange : uint32
		{
			KeepRelativeTransform			= 1 << 0,
			KeepWorldTransform				= 1 << 1,
			SnapToTargetNotIncludingScale	= 1 << 2,
			SnapToTargetIncludingScale		= 1 << 3,
			Transform						= 1 << 4
		};

		namespace NChange
		{
			FORCEINLINE bool HasAttach(const uint32& Mask)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale))
					return true;
				return false;
			}

			FORCEINLINE bool HasAttach(const uint32& Mask, const ECsAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					Rules == ECsAttachmentTransformRules::KeepRelativeTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					Rules == ECsAttachmentTransformRules::KeepWorldTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					Rules == ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					Rules == ECsAttachmentTransformRules::SnapToTargetIncludingScale)
					return true;
				return false;
			}

			FORCEINLINE uint32 GetAttachAsMask(const uint32& Mask)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform))
					return (uint32)EChange::KeepRelativeTransform;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform))
					return (uint32)EChange::KeepWorldTransform;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale))
					return (uint32)EChange::SnapToTargetNotIncludingScale;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale))
					return (uint32)EChange::SnapToTargetIncludingScale;
				return 0;
			}

			FORCEINLINE EChange FromTransformAttachmentRule(const ECsAttachmentTransformRules& Rules)
			{
				if (Rules == ECsAttachmentTransformRules::KeepRelativeTransform)
					return EChange::KeepRelativeTransform;
				if (Rules == ECsAttachmentTransformRules::KeepWorldTransform)
					return EChange::KeepWorldTransform;
				if (Rules == ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return EChange::SnapToTargetNotIncludingScale;
				if (Rules == ECsAttachmentTransformRules::SnapToTargetIncludingScale)
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			struct CSCORE_API FCounter
			{
			protected:
				FCounter() :
					Preserved(0),
					PreservedPercent(0.0f),
					Changed(0),
					ChangedPercent(0.0f),
					Cleared(0),
					ClearedPercent(0.0f),
					Total(0)
				{
				}
				FCounter(const FCounter&) = delete;
				FCounter(FCounter&&) = delete;
			public:
				virtual ~FCounter() {}
			private:
				uint32 Preserved;
				float PreservedPercent;
				uint32 Changed;
				float ChangedPercent;
				uint32 Cleared;
				float ClearedPercent;
				uint32 Total;
			public:
				static FCounter& Get()
				{
					static FCounter Instance;
					return Instance;
				}

			public:

				FORCEINLINE void AddPreserved()
				{
					++Preserved;
					++Total;
					PreservedPercent = (float)Preserved / (float)Total;
				}

				FORCEINLINE void AddChanged()
				{
					++Changed;
					++Total;
					ChangedPercent = (float)Changed / (float)Total;
				}

				FORCEINLINE void AddCleared()
				{
					++Cleared;
					++Total;
					ClearedPercent = (float)Cleared / (float)Total;
				}

				void Reset()
				{
					Preserved = 0;
					PreservedPercent = 0.0f;
					Changed = 0;
					ChangedPercent = 0.0f;
					Cleared = 0;
					ClearedPercent = 0.0f;
					Total = 0;
				}

				FORCEINLINE FString ToString() const
				{
					return FString::Printf(TEXT("Preserved: (%3.3f = %d/%d) Changed: (%3.3f = %d/%d) Cleared: (%3.3f = %d/%d)"), PreservedPercent, Preserved, Total, ChangedPercent, Changed, Total, ClearedPercent, Cleared, Total);
				}
			};
		}
	}
}

#pragma endregion NCsSound::NPayload::EChange