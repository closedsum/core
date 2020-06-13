// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObjectPayload.h"
#include "Types/CsTypes_Load.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_TwoParams.h"

#include "CsTypes_Interactive.generated.h"
#pragma once

// InteractiveType
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsInteractiveType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsInteractiveType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsInteractiveType)

struct CSCOREDEPRECATED_API EMCsInteractiveType : public TCsEnumStructMap<FECsInteractiveType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsInteractiveType, FECsInteractiveType, uint8)
};

#pragma endregion InteractiveType

// InteractiveState
#pragma region

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

struct CSCOREDEPRECATED_API EMCsInteractiveState : public TCsEnumMap<ECsInteractiveState::Type>
{
	CS_ENUM_MAP_BODY(EMCsInteractiveState, ECsInteractiveState::Type)
};

namespace ECsInteractiveState
{
	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type None;
		extern CSCOREDEPRECATED_API const Type FirstFreeze;
		extern CSCOREDEPRECATED_API const Type Freeze;
		extern CSCOREDEPRECATED_API const Type FirstUnFreeze;
		extern CSCOREDEPRECATED_API const Type FirstHold;
		extern CSCOREDEPRECATED_API const Type Hold;
		extern CSCOREDEPRECATED_API const Type Release;
		extern CSCOREDEPRECATED_API const Type FirstTouch;
		extern CSCOREDEPRECATED_API const Type Touch;
		extern CSCOREDEPRECATED_API const Type FirstHover;
		extern CSCOREDEPRECATED_API const Type Hover;
		extern CSCOREDEPRECATED_API const Type FirstUnHover;
		extern CSCOREDEPRECATED_API const Type FirstCollide;
		extern CSCOREDEPRECATED_API const Type Collide;
		extern CSCOREDEPRECATED_API const Type FirstUnCollide;
		extern CSCOREDEPRECATED_API const Type Remove;
		extern CSCOREDEPRECATED_API const Type ECsInteractiveState_MAX;
	}

	FORCEINLINE const FString& ToString(const Type& EType)
	{
		return EMCsInteractiveState::Get().ToString(EType);
	}

	FORCEINLINE Type ToType(const FString& String)
	{
		return EMCsInteractiveState::Get().ToType(String);
	}
}

#define ECS_INTERACTIVE_STATE_MAX (uint8)ECsInteractiveState::ECsInteractiveState_MAX
typedef ECsInteractiveState::Type TCsInteractiveState;

#pragma endregion InteractiveState

// InteractiveInstigator
#pragma region

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

struct CSCOREDEPRECATED_API EMCsInteractiveInstigator : public TCsEnumMap<ECsInteractiveInstigator::Type>
{
	CS_ENUM_MAP_BODY(EMCsInteractiveInstigator, ECsInteractiveInstigator::Type)
};

namespace ECsInteractiveInstigator
{
	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Look;
		extern CSCOREDEPRECATED_API const Type LeftHand;
		extern CSCOREDEPRECATED_API const Type RightHand;
		extern CSCOREDEPRECATED_API const Type Actor;
		extern CSCOREDEPRECATED_API const Type ECsInteractiveInstigator_MAX;
	}
}

#pragma endregion InteractiveInstigator

// InteractiveCollision
#pragma region

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

struct CSCOREDEPRECATED_API EMCsInteractiveCollision : public TCsEnumMap<ECsInteractiveCollision::Type>
{
	CS_ENUM_MAP_BODY(EMCsInteractiveCollision, ECsInteractiveCollision::Type)
};

namespace ECsInteractiveCollision
{
	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Box;
		extern CSCOREDEPRECATED_API const Type Sphere;
		extern CSCOREDEPRECATED_API const Type DistanceSquared;
		extern CSCOREDEPRECATED_API const Type Trace;
		extern CSCOREDEPRECATED_API const Type Mesh;
		extern CSCOREDEPRECATED_API const Type ECsInteractiveCollision_MAX;
	}
}

#pragma endregion InteractiveCollision

// FCsInteractiveMaterials
#pragma region

class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsInteractiveMaterials
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UMaterialInstanceConstant> Materials[ECsInteractiveState::ECsInteractiveState_MAX];

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

private:
	UPROPERTY(Transient)
	UMaterialInstanceConstant* Materials_Internal[ECsInteractiveState::ECsInteractiveState_MAX];

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

	FORCEINLINE UMaterialInstanceConstant* Get(const int32 Index)
	{
		return Index < ECS_INTERACTIVE_STATE_MAX ? Materials_Internal[Index] : nullptr;
	}
};

#pragma endregion FCsInteractiveMaterials

// InteractivePhysicsState
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsInteractivePhysicsState : uint8
{
	Grounded	UMETA(DisplayName = "Grounded"),
	Airborne	UMETA(DisplayName = "Airborne"),
	Ragdoll		UMETA(DisplayName = "Ragdoll"),
	Held		UMETA(DisplayName = "Held"),
	Custom		UMETA(DisplayName = "Custom"),
};

#pragma endregion InteractivePhysicsState

// InteractivePhysicsState_Editor
#pragma region

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

#pragma endregion InteractivePhysicsState_Editor

// FCsInteractedActorInfo
#pragma region

class UObject;
class AActor;
class USceneComponent;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsInteractedActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<AActor> Actor;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<USceneComponent> Component;

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

	FORCEINLINE AActor* GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }
	FORCEINLINE UObject* GetInstigator() const { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	FORCEINLINE USceneComponent* GetComponent() const { return Component.IsValid() ? Component.Get() : nullptr; }
};

#pragma endregion FCsInteractedActorInfo

// PickupFX
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsPickupFX : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsPickupFX)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsPickupFX)

struct CSCOREDEPRECATED_API EMCsPickupFX : public TCsEnumStructMap<FECsPickupFX, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsPickupFX, FECsPickupFX, uint8)
};

#pragma endregion PickupFX

// PickupSound
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsPickupSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsPickupSound)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsPickupSound)

struct CSCOREDEPRECATED_API EMCsPickupSound : public TCsEnumStructMap<FECsPickupSound, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsPickupSound, FECsPickupSound, uint8)
};

#pragma endregion PickupSound

// FCsInteractiveActorPayload
#pragma region

class UCsData_Interactive;

struct CSCOREDEPRECATED_API FCsInteractiveActorPayload : public ICsPooledObjectPayload
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

#pragma endregion FCsInteractiveActorPayload