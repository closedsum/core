// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"

#include "CsTypes_Interactive.generated.h"
#pragma once

// Interactives
#pragma region

namespace ECsInteractiveType
{
	enum Type : uint8;
}

typedef ECsInteractiveType::Type TCsInteractiveType;

// InteractiveTypeToString
typedef const FString&(*TCsInteractiveTypeToString)(const TCsInteractiveType&);
// StringToInteractiveType
typedef const TCsInteractiveType&(*TCsStringToInteractiveType)(const FString&);

#define CS_DECLARE_INTERACTIVE_TYPE	TCsInteractiveType InteractiveType_MAX; \
									uint8 INTERACTIVE_TYPE_MAX; \
									TCsInteractiveTypeToString InteractiveTypeToString; \
									TCsStringToInteractiveType StringToInteractiveType;

#define CS_DEFINE_INTERACTIVE_TYPE	InteractiveType_MAX = ECsInteractiveType::ECsInteractiveType_MAX;\
									INTERACTIVE_TYPE_MAX = (uint8)InteractiveType_MAX; \
									InteractiveTypeToString = &ECsInteractiveType::ToString; \
									StringToInteractiveType = &ECsInteractiveType::ToType;

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

namespace ECsInteractiveState
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"), TEXT("none"));
		const TCsString FirstFreeze = TCsString(TEXT("FirstFreeze"), TEXT("firstfreeze"), TEXT("first freeze"));
		const TCsString Freeze = TCsString(TEXT("Freeze"), TEXT("freeze"), TEXT("freeze"));
		const TCsString FirstUnFreeze = TCsString(TEXT("FirstUnFreeze"), TEXT("firstunfreeze"), TEXT("first unfreeze"));
		const TCsString FirstHold = TCsString(TEXT("FirstHold"), TEXT("firsthold"), TEXT("first hold"));
		const TCsString Hold = TCsString(TEXT("Hold"), TEXT("hold"), TEXT("hold"));
		const TCsString Release = TCsString(TEXT("Release"), TEXT("release"), TEXT("release"));
		const TCsString FirstTouch = TCsString(TEXT("FirstTouch"), TEXT("firsttouch"), TEXT("first touch"));
		const TCsString Touch = TCsString(TEXT("Touch"), TEXT("touch"), TEXT("touch"));
		const TCsString FirstHover = TCsString(TEXT("FirstHover"), TEXT("firsthover"), TEXT("first hover"));
		const TCsString Hover = TCsString(TEXT("Hover"), TEXT("hover"), TEXT("hover"));
		const TCsString FirstUnHover = TCsString(TEXT("FirstUnHover"), TEXT("firstunhover"), TEXT("first unhover"));
		const TCsString FirstCollide = TCsString(TEXT("FirstCollide"), TEXT("firstcollide"), TEXT("first collide"));
		const TCsString Collide = TCsString(TEXT("Collide"), TEXT("collide"), TEXT("collide"));
		const TCsString FirstUnCollide = TCsString(TEXT("FirstUnCollide"), TEXT("firstuncollide"), TEXT("first uncollide"));
		const TCsString Remove = TCsString(TEXT("Remove"), TEXT("remove"), TEXT("remove"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::FirstFreeze) { return Str::FirstFreeze.Value; }
		if (EType == Type::Freeze) { return Str::Freeze.Value; }
		if (EType == Type::FirstUnFreeze) { return Str::FirstUnFreeze.Value; }
		if (EType == Type::FirstHold) { return Str::FirstHold.Value; }
		if (EType == Type::Hold) { return Str::Hold.Value; }
		if (EType == Type::Release) { return Str::Release.Value; }
		if (EType == Type::FirstTouch) { return Str::FirstTouch.Value; }
		if (EType == Type::Touch) { return Str::Touch.Value; }
		if (EType == Type::FirstHover) { return Str::FirstHover.Value; }
		if (EType == Type::Hover) { return Str::Hover.Value; }
		if (EType == Type::FirstUnHover) { return Str::FirstUnHover.Value; }
		if (EType == Type::FirstCollide) { return Str::FirstCollide.Value; }
		if (EType == Type::Collide) { return Str::Collide.Value; }
		if (EType == Type::FirstUnCollide) { return Str::FirstUnCollide.Value; }
		if (EType == Type::Remove) { return Str::Remove.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::FirstFreeze) { return Type::FirstFreeze; }
		if (String == Str::Freeze) { return Type::Freeze; }
		if (String == Str::FirstHold) { return Type::FirstHold; }
		if (String == Str::FirstUnFreeze) { return Type::FirstUnFreeze; }
		if (String == Str::Hold) { return Type::Hold; }
		if (String == Str::Release) { return Type::Release; }
		if (String == Str::FirstTouch) { return Type::FirstTouch; }
		if (String == Str::Touch) { return Type::Touch; }
		if (String == Str::FirstHover) { return Type::FirstHover; }
		if (String == Str::Hover) { return Type::Hover; }
		if (String == Str::FirstUnHover) { return Type::FirstUnHover; }
		if (String == Str::FirstCollide) { return Type::FirstCollide; }
		if (String == Str::Collide) { return Type::Collide; }
		if (String == Str::FirstUnCollide) { return Type::FirstUnCollide; }
		if (String == Str::Remove) { return Type::Remove; }
		return Type::ECsInteractiveState_MAX;
	}
}

#define ECS_INTERACTIVE_STATE_MAX (uint8)ECsInteractiveState::ECsInteractiveState_MAX
typedef ECsInteractiveState::Type TCsInteractiveState;

UENUM()
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

namespace ECsInteractiveInstigator
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Look = TCsString(TEXT("Look"), TEXT("look"), TEXT("look"));
		const TCsString LeftHand = TCsString(TEXT("LeftHand"), TEXT("lefthand"), TEXT("left hand"));
		const TCsString RightHand = TCsString(TEXT("RightHand"), TEXT("righthand"), TEXT("right hand"));
		const TCsString Actor = TCsString(TEXT("Actor"), TEXT("actor"), TEXT("actor"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Look) { return Str::Look.Value; }
		if (EType == Type::LeftHand) { return Str::LeftHand.Value; }
		if (EType == Type::RightHand) { return Str::RightHand.Value; }
		if (EType == Type::Actor) { return Str::Actor.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Look) { return Type::Look; }
		if (String == Str::LeftHand) { return Type::LeftHand; }
		if (String == Str::RightHand) { return Type::RightHand; }
		if (String == Str::Actor) { return Type::Actor; }
		return Type::ECsInteractiveInstigator_MAX;
	}
}

#define ECS_INTERACTIVE_INSTIGATOR_MAX (uint8)ECsInteractiveInstigator::ECsInteractiveInstigator_MAX
typedef ECsInteractiveInstigator::Type TCsInteractiveInstigator;

UENUM()
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

namespace ECsInteractiveCollision
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Box = TCsString(TEXT("Box"), TEXT("box"), TEXT("box"));
		const TCsString Sphere = TCsString(TEXT("Sphere"), TEXT("sphere"), TEXT("sphere"));
		const TCsString DistanceSquared = TCsString(TEXT("DistanceSquared"), TEXT("distancesquared"), TEXT("distance squared"));
		const TCsString Trace = TCsString(TEXT("Trace"), TEXT("trace"), TEXT("trace"));
		const TCsString Mesh = TCsString(TEXT("Mesh"), TEXT("mesh"), TEXT("mesh"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Box) { return Str::Box.Value; }
		if (EType == Type::Sphere) { return Str::Sphere.Value; }
		if (EType == Type::DistanceSquared) { return Str::DistanceSquared.Value; }
		if (EType == Type::Trace) { return Str::Trace.Value; }
		if (EType == Type::Mesh) { return Str::Mesh.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Box) { return Type::Box; }
		if (String == Str::Sphere) { return Type::Sphere; }
		if (String == Str::DistanceSquared) { return Type::DistanceSquared; }
		if (String == Str::Trace) { return Type::Trace; }
		if (String == Str::Mesh) { return Type::Mesh; }
		return Type::ECsInteractiveCollision_MAX;
	}
}

#define ECS_INTERACTIVE_COLLISION_MAX (uint8)ECsInteractiveCollision::ECsInteractiveCollision_MAX
typedef ECsInteractiveCollision::Type TCsInteractiveCollision;

USTRUCT()
struct FCsInteractiveMaterials
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

	FCsInteractiveMaterials& operator=(const FCsInteractiveMaterials& B)
	{
		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; ++I)
		{
			Materials[I] = B.Materials[I];
		}
		Materials_LoadFlags = B.Materials_LoadFlags;
		return *this;
	}

	bool operator==(const FCsInteractiveMaterials& B) const
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

	bool operator!=(const FCsInteractiveMaterials& B) const
	{
		return !(*this == B);
	}

	UMaterialInstanceConstant** Get()
	{
		return Materials_Internal;
	}

	class UMaterialInstanceConstant* Get(const int32 Index)
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
struct FCsInteractedActorInfo
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

	FCsInteractedActorInfo& operator=(const FCsInteractedActorInfo& B)
	{
		Instigator = B.Instigator;
		Actor = B.Actor;
		Component = B.Component;
		Location = B.Location;
		return *this;
	}

	bool operator==(const FCsInteractedActorInfo& B) const
	{
		return Instigator == B.Instigator && Actor == B.Actor && Component == B.Component && Location == B.Location;
	}

	bool operator!=(const FCsInteractedActorInfo& B) const
	{
		return !(*this == B);
	}

	class AActor* GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }
	class UObject* GetInstigator() const { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	class USceneComponent* GetComponent() const { return Component.IsValid() ? Component.Get() : nullptr; }
};

#pragma endregion Interactives

// Pickup
#pragma region

namespace ECsPickupFX
{
	enum Type : uint8;
}

typedef ECsPickupFX::Type TCsPickupFX;

// PickupFXToString
typedef const FString&(*TCsPickupFXToString)(const TCsPickupFX&);
// StringToPickupFX
typedef TCsPickupFX(*TCsStringToPickupFX)(const FString&);

#define CS_DECLARE_PICKUP_FX	TCsPickupFX PickupFX_MAX; \
								uint8 PICKUP_FX_MAX; \
								TCsPickupFXToString PickupFXToString; \
								TCsStringToPickupFX StringToPickupFX;

#define CS_DEFINE_PICKUP_FX	PickupFX_MAX = ECsPickupFX::ECsPickupFX_MAX;\
							PICKUP_FX_MAX = (uint8)PickupFX_MAX \
							PickupFXToString = &ECsPickupFX::ToString; \
							StringToPickupFX = &ECsPickupFX::ToType;

namespace ECsPickupSound
{
	enum Type : uint8;
}

typedef ECsPickupSound::Type TCsPickupSound;

// PickupSoundToString
typedef const FString&(*TCsPickupSoundToString)(const TCsPickupSound&);
// StringToPickupSound
typedef TCsPickupSound(*TCsStringToPickupSound)(const FString&);

#define CS_DECLARE_PICKUP_SOUND	TCsPickupSound PickupSound_MAX; \
								uint8 PICKUP_SOUND_MAX; \
								TCsPickupSoundToString PickupSoundToString; \
								TCsStringToPickupSound StringToPickupSound;

#define CS_DEFINE_PICKUP_SOUND	PickupSound_MAX = ECsPickupSound::ECsPickupSound_MAX;\
								PICKUP_SOUND_MAX = (uint8)PickupSound_MAX \
								PickupSoundToString = &ECsPickupSound::ToString; \
								StringToPickupSound = &ECsPickupSound::ToType;


struct FCsInteractiveActorPayload
{
	bool IsAllocated;
	TWeakObjectPtr<class ACsData_Interactive> Data;
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

	void Reset()
	{
		IsAllocated = false;
		LifeTime = 0.0f;
		bLocation = false;
		bRotation = false;
		bScale = false;
		Transform = FTransform::Identity;
		Blob = nullptr;
	}

	class ACsData_Interactive* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	T* GetData() { return Cast<T>(GetData()); }
};

#pragma endregion Pickup