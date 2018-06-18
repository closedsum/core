// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Pool.h"

#include "CsTypes_Interactive.generated.h"
#pragma once

// Interactives
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsInteractiveType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsInteractiveType() {}
	FECsInteractiveType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsInteractiveType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsInteractiveType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsInteractiveType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInteractiveType : public TCsEnumStructMap<FECsInteractiveType, uint8>
{
protected:
	EMCsInteractiveType() {}
	EMCsInteractiveType(const EMCsInteractiveType &) = delete;
	EMCsInteractiveType(EMCsInteractiveType &&) = delete;
public:
	~EMCsInteractiveType() {}
private:
	static EMCsInteractiveType* Instance;

public:
	static EMCsInteractiveType& Get();
};

UENUM(BlueprintType)
namespace ECsInteractiveState
{
	enum Type
	{
		None					UMETA(DisplayName = "None"),
		FirstFreeze				UMETA(DisplayName = "Fire Freeze"),
		Freeze					UMETA(DisplayName = "Freeze"),
		FirstUnFreeze			UMETA(DisplayName = "First UnFreeze"),
		FirstHold				UMETA(DisplayName = "First Hold"),
		Hold					UMETA(DisplayName = "Hold"),
		Release					UMETA(DisplayName = "Release"),
		FirstTouch				UMETA(DisplayName = "First Touch"),
		Touch					UMETA(DisplayName = "Touch"),
		FirstHover				UMETA(DisplayName = "First Hover"),
		Hover					UMETA(DisplayName = "Hover"),
		FirstUnHover			UMETA(DisplayName = "First UnHover"),
		FirstCollide			UMETA(DisplayName = "First Collide"),
		Collide					UMETA(DisplayName = "Collide"),
		FirstUnCollide			UMETA(DisplayName = "First UnCollide"),
		Remove					UMETA(DisplayName = "Remove"),
		ECsInteractiveState_MAX	UMETA(Hidden),
	};
}

struct CSCORE_API EMCsInteractiveState : public TCsEnumMap<ECsInteractiveState::Type>
{
protected:
	EMCsInteractiveState() {}
	EMCsInteractiveState(const EMCsInteractiveState &) = delete;
	EMCsInteractiveState(EMCsInteractiveState &&) = delete;
public:
	~EMCsInteractiveState() {}
private:
	static EMCsInteractiveState* Instance;

public:
	static EMCsInteractiveState& Get();
};

namespace ECsInteractiveState
{
	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type FirstFreeze;
		extern CSCORE_API const Type Freeze;
		extern CSCORE_API const Type FirstUnFreeze;
		extern CSCORE_API const Type FirstHold;
		extern CSCORE_API const Type Hold;
		extern CSCORE_API const Type Release;
		extern CSCORE_API const Type FirstTouch;
		extern CSCORE_API const Type Touch;
		extern CSCORE_API const Type FirstHover;
		extern CSCORE_API const Type Hover;
		extern CSCORE_API const Type FirstUnHover;
		extern CSCORE_API const Type FirstCollide;
		extern CSCORE_API const Type Collide;
		extern CSCORE_API const Type FirstUnCollide;
		extern CSCORE_API const Type Remove;
		extern CSCORE_API const Type ECsInteractiveState_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return EMCsInteractiveState::Get().ToString(EType);
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return EMCsInteractiveState::Get().ToType(String);
	}
}

#define ECS_INTERACTIVE_STATE_MAX (uint8)ECsInteractiveState::ECsInteractiveState_MAX
typedef ECsInteractiveState::Type TCsInteractiveState;

UENUM(BlueprintType)
namespace ECsInteractiveInstigator
{
	enum Type
	{
		Look							UMETA(DisplayName = "Look"),
		LeftHand						UMETA(DisplayName = "Left Hand"),
		RightHand						UMETA(DisplayName = "Right Hand"),
		Actor							UMETA(DisplayName = "Actor"),
		ECsInteractiveInstigator_MAX	UMETA(Hidden),
	};
}

typedef ECsInteractiveInstigator::Type TCsInteractiveInstigator;

struct CSCORE_API EMCsInteractiveInstigator : public TCsEnumMap<ECsInteractiveInstigator::Type>
{
protected:
	EMCsInteractiveInstigator() {}
	EMCsInteractiveInstigator(const EMCsInteractiveInstigator &) = delete;
	EMCsInteractiveInstigator(EMCsInteractiveInstigator &&) = delete;
public:
	~EMCsInteractiveInstigator() {}
private:
	static EMCsInteractiveInstigator* Instance;

public:
	static EMCsInteractiveInstigator& Get();
};

namespace ECsInteractiveInstigator
{
	namespace Ref
	{
		extern CSCORE_API const Type Look;
		extern CSCORE_API const Type LeftHand;
		extern CSCORE_API const Type RightHand;
		extern CSCORE_API const Type Actor;
		extern CSCORE_API const Type ECsInteractiveInstigator_MAX;
	}
}

UENUM(BlueprintType)
namespace ECsInteractiveCollision
{
	enum Type
	{
		Box							UMETA(DisplayName = "Box"),
		Sphere						UMETA(DisplayName = "Sphere"),
		DistanceSquared				UMETA(DisplayName = "DistanceSquared"),
		Trace						UMETA(DisplayName = "Trace"),
		Mesh						UMETA(DisplayName = "Mesh"),
		ECsInteractiveCollision_MAX	UMETA(Hidden),
	};
}

typedef ECsInteractiveCollision::Type TCsInteractiveCollision;

struct CSCORE_API EMCsInteractiveCollision : public TCsEnumMap<ECsInteractiveCollision::Type>
{
protected:
	EMCsInteractiveCollision() {}
	EMCsInteractiveCollision(const EMCsInteractiveCollision &) = delete;
	EMCsInteractiveCollision(EMCsInteractiveCollision &&) = delete;
public:
	~EMCsInteractiveCollision() {}
private:
	static EMCsInteractiveCollision* Instance;

public:
	static EMCsInteractiveCollision& Get();
};

namespace ECsInteractiveCollision
{
	namespace Ref
	{
		extern CSCORE_API const Type Box;
		extern CSCORE_API const Type Sphere;
		extern CSCORE_API const Type DistanceSquared;
		extern CSCORE_API const Type Trace;
		extern CSCORE_API const Type Mesh;
		extern CSCORE_API const Type ECsInteractiveCollision_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return EMCsInteractiveCollision::Get().ToString(EType);
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return EMCsInteractiveCollision::Get().ToType(String);
	}
}

USTRUCT(BlueprintType)
struct CSCORE_API FCsInteractiveMaterials
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TAssetPtr<class UMaterialInstanceConstant> Materials[ECsInteractiveState::ECsInteractiveState_MAX];

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstanceConstant* Materials_Internal[ECsInteractiveState::ECsInteractiveState_MAX];

public:
	FCsInteractiveMaterials()
	{
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::UI);
	}

	FORCEINLINE FCsInteractiveMaterials& operator=(const FCsInteractiveMaterials& B)
	{
		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; ++I)
		{
			Materials[I] = B.Materials[I];
		}
		Materials_LoadFlags = B.Materials_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInteractiveMaterials& B) const
	{
		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; ++I)
		{
			if (Materials[I] != B.Materials[I])
				return false;
		}

		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; ++I)
		{
			if (Materials_Internal[I] != B.Materials_Internal[I])
				return false;
		}
		return Materials_LoadFlags == B.Materials_LoadFlags;
	}

	FORCEINLINE bool operator!=(const FCsInteractiveMaterials& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UMaterialInstanceConstant** Get()
	{
		return Materials_Internal;
	}

	FORCEINLINE class UMaterialInstanceConstant* Get(const int32 Index)
	{
		return Index < ECS_INTERACTIVE_STATE_MAX ? Materials_Internal[Index] : nullptr;
	}
};

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsInteractivePhysicsState : uint8
{
	Grounded	UMETA(DisplayName = "Grounded"),
	Airborne	UMETA(DisplayName = "Airborne"),
	Ragdoll		UMETA(DisplayName = "Ragdoll"),
	Held		UMETA(DisplayName = "Held"),
	Custom		UMETA(DisplayName = "Custom"),
};

UENUM(BlueprintType)
namespace ECsInteractivePhysicsState_Editor
{
	enum Type
	{
		Grounded								UMETA(DisplayName = "Grounded"),
		Airborne								UMETA(DisplayName = "Airborne"),
		Ragdoll									UMETA(DisplayName = "Ragdoll"),
		Held									UMETA(DisplayName = "Held"),
		Custom									UMETA(DisplayName = "Custom"),
		ECsInteractivePhysicsState_Editor_MAX	UMETA(Hidden),
	};
}

namespace ECsInteractivePhysicsState_Editor
{
	typedef TCsProperty_Multi_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Grounded = TCsString(TEXT("Grounded"), TEXT("grounded"));
		const TCsString Airborne = TCsString(TEXT("Airborne"), TEXT("airborne"));
		const TCsString Ragdoll = TCsString(TEXT("Ragdoll"), TEXT("ragdoll"));
		const TCsString Custom = TCsString(TEXT("Custom"), TEXT("custom"));
		const TCsString Held = TCsString(TEXT("Held"), TEXT("held"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Grounded) { return Str::Grounded.Value; }
		if (EType == Type::Airborne) { return Str::Airborne.Value; }
		if (EType == Type::Ragdoll) { return Str::Ragdoll.Value; }
		if (EType == Type::Held) { return Str::Held.Value; }
		if (EType == Type::Custom) { return Str::Custom.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToString(const ECsInteractivePhysicsState &EType)
	{
		if (EType == ECsInteractivePhysicsState::Grounded) { return Str::Grounded.Value; }
		if (EType == ECsInteractivePhysicsState::Airborne) { return Str::Airborne.Value; }
		if (EType == ECsInteractivePhysicsState::Ragdoll) { return Str::Ragdoll.Value; }
		if (EType == ECsInteractivePhysicsState::Held) { return Str::Held.Value; }
		if (EType == ECsInteractivePhysicsState::Custom) { return Str::Custom.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Grounded) { return Type::Grounded; }
		if (String == Str::Airborne) { return Type::Airborne; }
		if (String == Str::Ragdoll) { return Type::Ragdoll; }
		if (String == Str::Held) { return Type::Held; }
		if (String == Str::Custom) { return Type::Custom; }
		return Type::ECsInteractivePhysicsState_Editor_MAX;
	}
}

#define ECS_INTERACTIVE_PHYSICS_STATE_EDITOR_MAX (uint8)ECsInteractivePhysicsState_Editor::ECsInteractivePhysicsState_Editor_MAX
typedef ECsInteractivePhysicsState_Editor::Type TCsInteractivePhysicsState_Editor;

USTRUCT(BlueprintType)
struct CSCORE_API FCsInteractedActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<class UObject> Instigator;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<class AActor> Actor;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<class USceneComponent> Component;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	FVector Location;

public:

	FORCEINLINE FCsInteractedActorInfo& operator=(const FCsInteractedActorInfo& B)
	{
		Instigator = B.Instigator;
		Actor = B.Actor;
		Component = B.Component;
		Location = B.Location;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInteractedActorInfo& B) const
	{
		return Instigator == B.Instigator && Actor == B.Actor && Component == B.Component && Location == B.Location;
	}

	FORCEINLINE bool operator!=(const FCsInteractedActorInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class AActor* GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }
	FORCEINLINE class UObject* GetInstigator() const { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	FORCEINLINE class USceneComponent* GetComponent() const { return Component.IsValid() ? Component.Get() : nullptr; }
};

#pragma endregion Interactives

// Pickup
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsPickupFX : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsPickupFX() {}
	FECsPickupFX(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsPickupFX(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsPickupFX() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsPickupFX& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsPickupFX : public TCsEnumStructMap<FECsPickupFX, uint8>
{
protected:
	EMCsPickupFX() {}
	EMCsPickupFX(const EMCsPickupFX &) = delete;
	EMCsPickupFX(EMCsPickupFX &&) = delete;
public:
	~EMCsPickupFX() {}
private:
	static EMCsPickupFX* Instance;

public:
	static EMCsPickupFX& Get();
};

USTRUCT(BlueprintType)
struct CSCORE_API FECsPickupSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsPickupSound() {}
	FECsPickupSound(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsPickupSound(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsPickupSound() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsPickupSound& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsPickupSound : public TCsEnumStructMap<FECsPickupSound, uint8>
{
protected:
	EMCsPickupSound() {}
	EMCsPickupSound(const EMCsPickupSound &) = delete;
	EMCsPickupSound(EMCsPickupSound &&) = delete;
public:
	~EMCsPickupSound() {}
private:
	static EMCsPickupSound* Instance;

public:
	static EMCsPickupSound& Get();
};

USTRUCT(BlueprintType)
struct FCsInteractiveActorPayload : public FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TWeakObjectPtr<class ACsData_Interactive> Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	float LifeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	bool bLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	bool bRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	bool bScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FTransform Transform;

	void* Blob;

	FCsInteractiveActorPayload()
	{
		Reset();
	}
	~FCsInteractiveActorPayload() {}

	FORCEINLINE virtual void Reset() override
	{
		FCsPooledObjectPayload::Reset();

		LifeTime = 0.0f;
		bLocation = false;
		bRotation = false;
		bScale = false;
		Transform = FTransform::Identity;
		Blob = nullptr;
	}

	FORCEINLINE class ACsData_Interactive* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData() { return Cast<T>(GetData()); }
};

#pragma endregion Pickup