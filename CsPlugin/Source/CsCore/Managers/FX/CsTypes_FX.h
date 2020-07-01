// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsTypes_FX.generated.h"
#pragma once

#define CS_MAX_EMITTER_COUNT 256

// FX
#pragma region

/**
* Enum for FX types
*/
USTRUCT(BlueprintType)
struct CSCORE_API FECsFX : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsFX)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsFX)

struct CSCORE_API EMCsFX final : public TCsEnumStructMap<FECsFX, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsFX, FECsFX, uint8)
};

namespace NCsFX
{
	typedef FECsFX Type;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion FX

// FCsParticleSystem
#pragma region

class UParticleSystem;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsParticleSystem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Particle_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UParticleSystem* Particle_Internal;

public:
	FCsParticleSystem() :
		Particle_LoadFlags(0),
		Particle_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UParticleSystem* Get() const
	{
		return Particle_Internal;
	}
};

#pragma endregion FCsParticleSystem

// FxPriority
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsFXPriority : uint8
{
	Low				  UMETA(DisplayName = "Low"),
	Medium			  UMETA(DisplayName = "Medium"),
	High			  UMETA(DisplayName = "High"),
	ECsFXPriority_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsFXPriority final : public TCsEnumMap<ECsFXPriority>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXPriority, ECsFXPriority)
};

namespace NCsFXPriority
{
	typedef ECsFXPriority Type;

	namespace Ref
	{
		extern CSCORE_API const Type Low;
		extern CSCORE_API const Type Medium;
		extern CSCORE_API const Type High;
		extern CSCORE_API const Type ECsFXPriority_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion FxPriority

// FCsFxElement_DEPRECATED
#pragma region

class UParticleSystem;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFxElement_DEPRECATED
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	TSoftObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Particle_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "FX")
	ECsFXPriority Priority;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DeathTime;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Scale;

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFpvDrawDistance DrawDistances;

	UPROPERTY(EditAnywhere, Category = "FX")
	FName Bone;

	UPROPERTY(EditAnywhere, Category = "FX")
	FVector Location;

	UPROPERTY(EditAnywhere, Category = "FX")
	FRotator Rotation;

private:

	UPROPERTY(Transient)
	class UParticleSystem* Particle_Internal;

public:

	FCsFxElement_DEPRECATED() :
		Particle_LoadFlags(0),
		LifeTime(0.0f),
		DeathTime(0.0f),
		DrawDistances(),
		Bone(NAME_None),
		Location(0.0f),
		Rotation(0.0f),
		Particle_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);

		DeathTime = 1.0f;
		Scale = 1.0f;
		Priority = ECsFXPriority::Medium;
	}

	FORCEINLINE bool operator==(const FCsFxElement_DEPRECATED& B) const
	{
		return (Particle == B.Particle &&
				Particle_LoadFlags == B.Particle_LoadFlags &&
				LifeTime == B.LifeTime &&
				DeathTime == B.DeathTime &&
				Scale == B.Scale &&
				DrawDistances == B.DrawDistances &&
				Bone == B.Bone &&
				Location == B.Location &&
				Rotation == B.Rotation &&
				Particle_Internal == B.Particle_Internal);
	}

	FORCEINLINE bool operator!=(const FCsFxElement_DEPRECATED& B) const
	{
		return !(*this == B);
	}
	
	FORCEINLINE void Set(UParticleSystem* InParticle)
	{
		//Particle		  = TSoftObjectPtr<UParticleSystem>(InParticle);
		Particle_Internal = InParticle;
	}
	
	FORCEINLINE UParticleSystem* Get() const
	{
		return Particle_Internal;
	}

	FORCEINLINE void Reset()
	{
		//Particle = nullptr;
		Particle_LoadFlags = 0;

		CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);

		LifeTime = 0.0f;
		DeathTime = 1.0f;
		Scale = 1.0f;
		Priority = ECsFXPriority::Medium;
		DrawDistances.Reset();
		Bone = NAME_None;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;

		Particle_Internal = nullptr;
	}
};

#pragma endregion FCsFxElement_DEPRECATED

// FCsFpvFxElement
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvFxElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFxElement_DEPRECATED Effect1P;

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFxElement_DEPRECATED Effect3P;

	FCsFpvFxElement()
	{
		CS_SET_BLUEPRINT_BITFLAG(Effect1P.Particle_LoadFlags, ECsLoadFlags::Game1P);
		CS_SET_BLUEPRINT_BITFLAG(Effect3P.Particle_LoadFlags, ECsLoadFlags::Game3P);
	}

	FORCEINLINE FCsFxElement_DEPRECATED* Get(const ECsViewType& ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return &Effect1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return &Effect3P;
		if (ViewType == ECsViewType::VR)
			return &Effect1P;
		return &Effect3P;
	}

	FORCEINLINE bool operator==(const FCsFpvFxElement& B) const
	{
		return Effect1P == B.Effect1P && Effect3P == B.Effect3P;
	}

	FORCEINLINE bool operator!=(const FCsFpvFxElement& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE const FName& GetBone(const ECsViewType& ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Effect1P.Bone;
		if (ViewType == ECsViewType::ThirdPerson)
			return Effect3P.Bone;
		return NCsCached::Name::None;
	}
};

#pragma endregion FCsFpvFxElement

// FCsFxPayload
#pragma region

class UObject;

struct CSCORE_API FCsFxPayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	FCsTime Time;

	TWeakObjectPtr<UParticleSystem> Particle;

	ECsFXPriority Priority;

	float LifeTime;

	float DeathTime;

	float Scale;

	FCsFpvDrawDistance DrawDistances;

	FName Bone;

	FVector Location;

	FRotator Rotation;

	FCsFxPayload() 
	{
		Reset();
	}
	~FCsFxPayload() {}

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

		Particle = nullptr;
		Priority = ECsFXPriority::Medium;
		LifeTime = 0.0f;
		DeathTime = 0.0f;
		Scale = 1.0f;
		DrawDistances.Reset();
		Bone = NAME_None;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}

#pragma endregion ICsPooledObjectPayload

	FORCEINLINE void Set(FCsFxElement_DEPRECATED* Element)
	{
		Particle = Element->Get();
		Priority = Element->Priority;
		LifeTime = Element->LifeTime;
		DeathTime = Element->DeathTime;
		Scale = Element->Scale;
		DrawDistances = Element->DrawDistances;
		Bone = Element->Bone;
		Location = Element->Location;
		Rotation = Element->Rotation;
	}

	FORCEINLINE void Set(FCsFxElement_DEPRECATED& Element)
	{
		Set(&Element);
	}

	FORCEINLINE UParticleSystem* GetParticle() { return Particle.IsValid() ? Particle.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetParticle() { return Cast<T>(GetParticle()); }
};

#pragma endregion FCsFxPayload

// FXDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate an FX.
*/
UENUM(BlueprintType)
enum class ECsFXDeallocateMethod : uint8
{
	/** If an FX is attached to a parent object,
		  LifeTime == 0.of means the FX object will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the FX object.
		If an FX is NOT attached to a parent object,
		  LifeTime == 0.0f means the FX object will stay active forever.
		  LifeTime > 0.0f means the FX will be deallocated after LifeTime amount of time after
		   the FX object has been allocated. */
	LifeTime				  UMETA(DisplayName = "LifeTime"),
	/** */
	Complete				  UMETA(DisplayName = "Complete"),
	ECsFXDeallocateMethod_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsFXDeallocateMethod final : public TCsEnumMap<ECsFXDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXDeallocateMethod, ECsFXDeallocateMethod)
};

namespace NCsFXDeallocateMethod
{
	typedef ECsFXDeallocateMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type LifeTime;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsFXDeallocateMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion FXDeallocateMethod

// FCsFX
#pragma region

class UNiagaraSystem;

/**
* Container holding general information for an FX System.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsFX
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to an FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UNiagaraSystem> FX;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 FX_LoadFlags;

	/** Hard reference to an FX System. */
	UPROPERTY(Transient, BlueprintReadOnly)
	UNiagaraSystem* FX_Internal;

	/** The FX Type. This is used to group FX into different categories 
	    and can be used by a Manager pooling FX objects to Spawn the correct
		FX object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsFX Type;

	/** Condition to determine when to deallocate the FX object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsFXDeallocateMethod DeallocateMethod;

	/** Valid if the DeallocateMethod == ECsFXDeallocateMethod::LifeTime.
		- If an FX IS attached to a Parent object, 
		   LifeTime == 0.of means the FX object will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the FX object.
	    - If an FX is NOT attached to a Parent object,
		   LifeTime == 0.0f means the FX object will stay active forever.
		   LifeTime > 0.0f means the FX will be deallocated after LifeTime amount of time after
	        the FX object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** Valid if the FX is attached to a Parent object or when an FX object is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the FX will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the FX is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Bone;

	/** Which of the components of Transform to apply to the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 TransformRules;

	/** The Transform to apply to the FX.
		If the FX is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;

public:

	FCsFX() :
		FX(nullptr),
		FX_LoadFlags(0),
		FX_Internal(nullptr),
		Type(),
		DeallocateMethod(ECsFXDeallocateMethod::Complete),
		LifeTime(0.0f),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(1), // NCsTransformRules::All
		Transform(FTransform::Identity)
	{
		//CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);
	}
	
	/**
	* Get the Hard reference to the FX System.
	*
	* return FX System
	*/
	FORCEINLINE UNiagaraSystem* Get() const
	{
		return FX_Internal;
	}
};

#pragma endregion FCsFX