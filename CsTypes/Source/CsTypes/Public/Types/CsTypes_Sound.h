// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsMacro_Misc.h"
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsTypes_Sound.generated.h"

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

struct CSTYPES_API EMCsSoundPriority : public TCsEnumMap<ECsSoundPriority>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSoundPriority, ECsSoundPriority)
};

namespace NCsSoundPriority
{
	typedef ECsSoundPriority Type;

	namespace Ref
	{
		extern CSTYPES_API const Type VeryLow;
		extern CSTYPES_API const Type Low;
		extern CSTYPES_API const Type Medium;
		extern CSTYPES_API const Type High;
		extern CSTYPES_API const Type VeryHigh;
		extern CSTYPES_API const Type ECsSoundPriority_MAX;
	}
}

#pragma endregion SoundPriority

// FCsSoundCue
#pragma region

class USoundCue;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsSoundCue
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Sound")
	TSoftObjectPtr<USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Sound", meta = (Bitmask, BitmaskEnum = "/Script/CsTypes.ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Sound")
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
struct CSTYPES_API FCsSoundBase
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to a Sound Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Sound")
	TSoftObjectPtr<USoundBase> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Sound", meta = (Bitmask, BitmaskEnum = "/Script/CsTypes.ECsLoadFlags"))
	int32 Sound_LoadFlags;

	/** Hard reference to a Sound Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Sound")
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

#pragma endregion FCsSoundBase

// FCsTArraySoundBase
#pragma region

class USoundBase;

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsTArraySoundBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Sound")
	TArray<TSoftObjectPtr<USoundBase>> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Sound", meta = (Bitmask, BitmaskEnum = "/Script/CsTypes.ECsLoadFlags"))
	int32 Sounds_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Sound")
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

struct CSTYPES_API EMCsSoundDeallocateMethod final : public TCsEnumMap<ECsSoundDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSoundDeallocateMethod, ECsSoundDeallocateMethod)
};

namespace NCsSoundDeallocateMethod
{
	typedef ECsSoundDeallocateMethod Type;

	namespace Ref
	{
		extern CSTYPES_API const Type LifeTime;
		extern CSTYPES_API const Type Complete;
		extern CSTYPES_API const Type ECsSoundDeallocateMethod_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsSound
{
	/**
	* Type for different ways to deallocate a Sound.
	*/
	enum class EDeallocateMethod : uint8
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
		LifeTime,
		/** */
		Complete,
		EDeallocateMethod_MAX
	};

	struct CSTYPES_API EMDeallocateMethod final : public TCsEnumMap<EDeallocateMethod>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDeallocateMethod, EDeallocateMethod)
	};

	namespace NDeallocateMethod
	{
		typedef EDeallocateMethod Type;

		namespace Ref
		{
			extern CSTYPES_API const Type LifeTime;
			extern CSTYPES_API const Type Complete;
			extern CSTYPES_API const Type EDeallocateMethod_MAX;
		}

		extern CSTYPES_API const uint8 MAX;
	}
}

#pragma endregion SoundDeallocateMethod

// NoiseEvent
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FECsNoiseEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsNoiseEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsNoiseEvent)

struct CSTYPES_API EMCsNoiseEvent final : public TCsEnumStructMap<FECsNoiseEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsNoiseEvent, FECsNoiseEvent, uint8)
};

namespace NCsNoiseEvent
{
	typedef FECsNoiseEvent Type;
}

#pragma endregion NoiseEvent