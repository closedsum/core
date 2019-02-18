// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_Pool.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"

#include "CsTypes_FX.generated.h"
#pragma once

#define CS_MAX_EMITTER_COUNT 256

USTRUCT()
struct CSCORE_API FCsParticleSystem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	TSoftObjectPtr<class UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Particle_LoadFlags;

private:
	UPROPERTY(Transient)
	class UParticleSystem* Particle_Internal;

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

// FxPriority
#pragma region

UENUM(BlueprintType)
namespace ECsFxPriority
{
	enum Type
	{
		Low				  UMETA(DisplayName = "Low"),
		Medium			  UMETA(DisplayName = "Medium"),
		High			  UMETA(DisplayName = "High"),
		ECsFxPriority_MAX UMETA(Hidden),
	};
}

typedef ECsFxPriority::Type TCsFxPriority;

struct CSCORE_API EMCsFxPriority : public TCsEnumMap<ECsFxPriority::Type>
{
protected:
	EMCsFxPriority() {}
	EMCsFxPriority(const EMCsFxPriority &) = delete;
	EMCsFxPriority(EMCsFxPriority &&) = delete;
public:
	~EMCsFxPriority() {}
private:
	static EMCsFxPriority* Instance;

public:
	static EMCsFxPriority& Get();
};

namespace ECsFxPriority
{
	namespace Ref
	{
		extern CSCORE_API const Type Low;
		extern CSCORE_API const Type Medium;
		extern CSCORE_API const Type High;
		extern CSCORE_API const Type ECsFxPriority_MAX;
	}
}

#pragma endregion FxPriority

USTRUCT(BlueprintType)
struct CSCORE_API FCsFxElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	TSoftObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Particle_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "FX")
	TEnumAsByte<ECsFxPriority::Type> Priority;

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

	FCsFxElement() :
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
		Priority = ECsFxPriority::Medium;
	}

	FORCEINLINE FCsFxElement& operator=(const FCsFxElement& B)
	{
		Particle = B.Particle;
		Particle_LoadFlags = B.Particle_LoadFlags;
		LifeTime = B.LifeTime;
		DeathTime = B.DeathTime;
		Scale = B.Scale;
		DrawDistances = B.DrawDistances;
		Bone = B.Bone;
		Location = B.Location;
		Rotation = B.Rotation;

		Particle_Internal = B.Particle_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsFxElement& B) const
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

	FORCEINLINE bool operator!=(const FCsFxElement& B) const
	{
		return !(*this == B);
	}
	
	FORCEINLINE void Set(class UParticleSystem* InParticle)
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
		Priority = ECsFxPriority::Medium;
		DrawDistances.Reset();
		Bone = NAME_None;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;

		Particle_Internal = nullptr;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvFxElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFxElement Effect1P;

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFxElement Effect3P;

	FCsFpvFxElement()
	{
		CS_SET_BLUEPRINT_BITFLAG(Effect1P.Particle_LoadFlags, ECsLoadFlags::Game1P);
		CS_SET_BLUEPRINT_BITFLAG(Effect3P.Particle_LoadFlags, ECsLoadFlags::Game3P);
	}

	FORCEINLINE FCsFxElement* Get(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return &Effect1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return &Effect3P;
		if (ViewType == ECsViewType::VR)
			return &Effect1P;
		return &Effect3P;
	}

	FORCEINLINE FCsFpvFxElement& operator=(const FCsFpvFxElement& B)
	{
		Effect1P = B.Effect1P;
		Effect3P = B.Effect3P;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsFpvFxElement& B) const
	{
		return Effect1P == B.Effect1P && Effect3P == B.Effect3P;
	}

	FORCEINLINE bool operator!=(const FCsFpvFxElement& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE const FName& GetBone(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Effect1P.Bone;
		if (ViewType == ECsViewType::ThirdPerson)
			return Effect3P.Bone;
		return ECsCached::Name::None;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFxPayload : public FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Payload")
	TWeakObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "Payload")
	TEnumAsByte<ECsFxPriority::Type> Priority;

	UPROPERTY(EditAnywhere, Category = "Payload", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	UPROPERTY(EditAnywhere, Category = "Payload", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DeathTime;

	UPROPERTY(EditAnywhere, Category = "Payload", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Scale;

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFpvDrawDistance DrawDistances;

	UPROPERTY(EditAnywhere, Category = "FX")
	FName Bone;

	UPROPERTY(EditAnywhere, Category = "FX")
	FVector Location;

	UPROPERTY(EditAnywhere, Category = "FX")
	FRotator Rotation;

	FCsFxPayload() 
	{
		Reset();
	}
	~FCsFxPayload() {}

	FORCEINLINE void Set(FCsFxElement* Element)
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

	FORCEINLINE void Set(FCsFxElement& Element)
	{
		Set(&Element);
	}

	FORCEINLINE virtual void Reset() override
	{
		FCsPooledObjectPayload::Reset();

		Particle = nullptr;
		Priority = ECsFxPriority::Medium;
		LifeTime = 0.0f;
		DeathTime = 0.0f;
		Scale = 1.0f;
		DrawDistances.Reset();
		Bone = NAME_None;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}

	FORCEINLINE UParticleSystem* GetParticle() { return Particle.IsValid() ? Particle.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetParticle() { return Cast<T>(GetParticle()); }
};