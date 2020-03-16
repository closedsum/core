// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_Load.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_TwoParams.h"

#include "CsTypes_Interactive.generated.h"
#pragma once

// Interactives
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsInteractiveType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsInteractiveType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsInteractiveType)

struct CSCORE_API EMCsInteractiveType : public TCsEnumStructMap<FECsInteractiveType, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsInteractiveType)
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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInteractiveState)
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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInteractiveInstigator)
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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInteractiveCollision)
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
}

USTRUCT(BlueprintType)
struct CSCORE_API FCsInteractiveMaterials
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TSoftObjectPtr<class UMaterialInstanceConstant> Materials[ECsInteractiveState::ECsInteractiveState_MAX];

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstanceConstant* Materials_Internal[ECsInteractiveState::ECsInteractiveState_MAX];

public:
	FCsInteractiveMaterials() :
		Materials_LoadFlags(0)
	{
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::UI);

		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; ++I)
		{
			Materials_Internal[I] = nullptr;
		}
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

	CS_ENUM_UINT8_BODY(FECsPickupFX)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsPickupFX)

struct CSCORE_API EMCsPickupFX : public TCsEnumStructMap<FECsPickupFX, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsPickupFX)
};

USTRUCT(BlueprintType)
struct CSCORE_API FECsPickupSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsPickupSound)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsPickupSound)

struct CSCORE_API EMCsPickupSound : public TCsEnumStructMap<FECsPickupSound, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsPickupSound)
};

class UCsData_Interactive;

struct CSCORE_API FCsInteractiveActorPayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	TWeakObjectPtr<UCsData_Interactive> Data;

	float LifeTime;

	bool bLocation;

	bool bRotation;

	bool bScale;

	FTransform Transform;

	void* Blob;

	FCsInteractiveActorPayload()
	{
		Reset();
	}
	~FCsInteractiveActorPayload() {}

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

		LifeTime = 0.0f;
		bLocation = false;
		bRotation = false;
		bScale = false;
		Transform = FTransform::Identity;
		Blob = nullptr;
	}

#pragma endregion ICsPooledObjectPayload

	FORCEINLINE UCsData_Interactive* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData() { return Cast<T>(GetData()); }
};

#pragma endregion Pickup