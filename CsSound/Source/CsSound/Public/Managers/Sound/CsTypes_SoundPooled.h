// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Math.h"
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
#include "Types/CsTypes_Sound.h"
// Log
#include "Utility/CsSoundLog.h"

#include "CsTypes_SoundPooled.generated.h"

// Sound
#pragma region

USTRUCT(BlueprintType)
struct CSSOUND_API FECsSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSound)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSound)

struct CSSOUND_API EMCsSound : public TCsEnumStructMap<FECsSound, uint8>
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

	CSSOUND_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Sound

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
struct CSSOUND_API FCsSound
{
	GENERATED_USTRUCT_BODY()

private:

	typedef NCsSound::EDeallocateMethod DeallocateMethodType;

public:

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TSoftObjectPtr<USoundBase> Sound;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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

	/** The amount of time it takes to Fade In the Sound to the default Volume Multiplier. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float FadeInTime;

	/** Valid if the Sound is attached to a Parent object or when an Sound object is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	FCsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the Sound is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	FName Bone;

	/** Which of the components of Transform to apply to the Sound. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound", meta = (Bitmask, BitmaskEnum = "/Script.CsTypes.ECsTransformRules"))
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
		FadeInTime(0.0f),
		AttachmentTransformRules(FCsAttachmentTransformRules::SnapToTargetNotIncludingScale),
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
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSound::FLog::Warning) const;

	void Reset();
};

#pragma endregion FCsSound

// NCsSound::NPayload::EChange
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsSoundPayloadChange : uint8
{
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),				// 0
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),				// 1
	SnapToTargetNotIncludingScale	UMETA(DisplayName = "Snap to Target not Including Scale"),	// 2
	SnapToTargetIncludingScale		UMETA(DisplayName = "Snap to Target Including Scale"),		// 3
	Transform						UMETA(DisplayName = "Transform"),							// 4
};

struct CSSOUND_API EMCsSoundPayloadChange : public TCsEnumFlagMap<ECsSoundPayloadChange>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsSoundPayloadChange, ECsSoundPayloadChange)
};

namespace NCsSoundPayloadChange
{
	typedef ECsSoundPayloadChange Type;

	namespace Ref
	{
		extern CSSOUND_API const Type KeepRelativeTransform;
		extern CSSOUND_API const Type KeepWorldTransform;
		extern CSSOUND_API const Type SnapToTargetNotIncludingScale;
		extern CSSOUND_API const Type SnapToTargetIncludingScale;
		extern CSSOUND_API const Type Transform;
	}

	extern CSSOUND_API const int32 None;
	extern CSSOUND_API const int32 All;
}

#define CS_SOUND_PAYLOAD_CHANGE_NONE 0

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

			FORCEINLINE bool HasAttach(const uint32& Mask, const FCsAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					Rules == FCsAttachmentTransformRules::KeepRelativeTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					Rules == FCsAttachmentTransformRules::KeepWorldTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					Rules == FCsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					Rules == FCsAttachmentTransformRules::SnapToTargetIncludingScale)
					return true;
				return false;
			}

			FORCEINLINE bool HasAttach(const uint32& Mask, const FAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepRelativeTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepWorldTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetNotIncludingScale))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetIncludingScale))
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

			FORCEINLINE EChange FromTransformAttachmentRule(const FCsAttachmentTransformRules& Rules)
			{
				if (Rules == FCsAttachmentTransformRules::KeepRelativeTransform)
					return EChange::KeepRelativeTransform;
				if (Rules == FCsAttachmentTransformRules::KeepWorldTransform)
					return EChange::KeepWorldTransform;
				if (Rules == FCsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return EChange::SnapToTargetNotIncludingScale;
				if (Rules == FCsAttachmentTransformRules::SnapToTargetIncludingScale)
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			FORCEINLINE EChange FromTransformAttachmentRule(const FAttachmentTransformRules& Rules)
			{
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepRelativeTransform))
					return EChange::KeepRelativeTransform;
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepWorldTransform))
					return EChange::KeepWorldTransform;
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetNotIncludingScale))
					return EChange::SnapToTargetNotIncludingScale;
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetIncludingScale))
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			struct CSSOUND_API FCounter
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