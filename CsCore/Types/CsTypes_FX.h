// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"
#include "CsTypes_FX.generated.h"
#pragma once

// FX
#pragma region

#define CS_MAX_EMITTER_COUNT 256

USTRUCT()
struct FCsParticleSystem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	TAssetPtr<class UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Particle_LoadFlags;

private:
	UPROPERTY(Transient)
	class UParticleSystem* Particle_Internal;

public:
	FCsParticleSystem()
	{
		CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);
	}

	UParticleSystem* Get() const
	{
		return Particle_Internal;
	}
};

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

namespace ECsFxPriority
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Low = TCsString(TEXT("Low"), TEXT("low"));
		const TCsString Medium = TCsString(TEXT("Medium"), TEXT("medium"));
		const TCsString High = TCsString(TEXT("High"), TEXT("high"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Low) { return Str::Low.Value; }
		if (EType == Type::Medium) { return Str::Medium.Value; }
		if (EType == Type::High) { return Str::High.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Low) { return Type::Low; }
		if (String == Str::Medium) { return Type::Medium; }
		if (String == Str::High) { return Type::High; }
		return Type::ECsFxPriority_MAX;
	}
}

#define ECS_FX_PRIORITY_MAX (uint8)ECsFxPriority::ECsFxPriority_MAX
typedef ECsFxPriority::Type TCsFxPriority;

USTRUCT(BlueprintType)
struct FCsFxElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	TAssetPtr<UParticleSystem> Particle;

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
	FCsFpsDrawDistance DrawDistances;

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

	FCsFxElement()
	{
		CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);

		DeathTime = 1.0f;
		Scale = 1.0f;
		Priority = ECsFxPriority::Medium;
	}

	FCsFxElement& operator=(const FCsFxElement& B)
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

	bool operator==(const FCsFxElement& B) const
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

	bool operator!=(const FCsFxElement& B) const
	{
		return !(*this == B);
	}
	
	void Set(class UParticleSystem* InParticle)
	{
		//Particle		  = TAssetPtr<UParticleSystem>(InParticle);
		Particle_Internal = InParticle;
	}
	
	UParticleSystem* Get() const
	{
		return Particle_Internal;
	}

	void Reset()
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
struct FCsFpsFxElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFxElement Effect1P;

	UPROPERTY(EditAnywhere, Category = "FX")
	FCsFxElement Effect3P;

	FCsFpsFxElement()
	{
		CS_SET_BLUEPRINT_BITFLAG(Effect1P.Particle_LoadFlags, ECsLoadFlags::Game1P);
		CS_SET_BLUEPRINT_BITFLAG(Effect3P.Particle_LoadFlags, ECsLoadFlags::Game3P);
	}

	FCsFxElement* Get(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return &Effect1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return &Effect3P;
		if (ViewType == ECsViewType::VR)
			return &Effect1P;
		return &Effect3P;
	}

	FCsFpsFxElement& operator=(const FCsFpsFxElement& B)
	{
		Effect1P = B.Effect1P;
		Effect3P = B.Effect3P;
		return *this;
	}

	bool operator==(const FCsFpsFxElement& B) const
	{
		return Effect1P == B.Effect1P && Effect3P == B.Effect3P;
	}

	bool operator!=(const FCsFpsFxElement& B) const
	{
		return !(*this == B);
	}

	FName GetBone(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Effect1P.Bone;
		if (ViewType == ECsViewType::ThirdPerson)
			return Effect3P.Bone;
		return NAME_None;
	}
};

#pragma endregion FX