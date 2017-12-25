// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"

#include "CsTypes_Projectile.generated.h"
#pragma once

// Projectile
#pragma region

// ACsData_Projectile
USTRUCT(BlueprintType)
struct FCsData_ProjectilePtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_Projectile> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_Projectile* Data_Internal;

public:
	FCsData_ProjectilePtr()
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FCsData_ProjectilePtr& operator=(const FCsData_ProjectilePtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsData_ProjectilePtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsData_ProjectilePtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_Projectile* Get() const
	{
		return Data_Internal;
	}
};

// ACsData_ProjectileImpact
USTRUCT(BlueprintType)
struct FCsData_ProjectileImpactPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_ProjectileImpact> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_ProjectileImpact* Data_Internal;

public:
	FCsData_ProjectileImpactPtr()
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FCsData_ProjectileImpactPtr& operator=(const FCsData_ProjectileImpactPtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsData_ProjectileImpactPtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsData_ProjectileImpactPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_ProjectileImpact* Get() const
	{
		return Data_Internal;
	}
};

UENUM(BlueprintType)
namespace ECsProjectileRelevance
{
	enum Type
	{
		RealVisible					UMETA(DisplayName = "Real Visible"),
		RealInvisible				UMETA(DisplayName = "Real Invisible"),
		Fake						UMETA(DisplayName = "Fake"),
		ECsProjectileRelevance_MAX	UMETA(Hidden),
	};
}

namespace ECsProjectileRelevance
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString RealVisible = TCsString(TEXT("RealVisible"), TEXT("realvisible"));
		const TCsString RealInvisible = TCsString(TEXT("RealInvisible"), TEXT("realinvisible"));
		const TCsString Fake = TCsString(TEXT("Fake"), TEXT("fake"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::RealVisible) { return Str::RealVisible.Value; }
		if (EType == Type::RealInvisible) { return Str::RealInvisible.Value; }
		if (EType == Type::Fake) { return Str::Fake.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::RealVisible) { return Type::RealVisible; }
		if (String == Str::RealInvisible) { return Type::RealInvisible; }
		if (String == Str::Fake) { return Type::Fake; }
		return Type::ECsProjectileRelevance_MAX;
	}
}

#define ECS_PROJECTILE_RELEVANCE_MAX (uint8)ECsProjectileRelevance::ECsProjectileRelevance_MAX
typedef TEnumAsByte<ECsProjectileRelevance::Type> TCsProjectileRelevance;

namespace ECsProjectileType
{
	enum Type : uint8;
}

typedef ECsProjectileType::Type TCsProjectileType;

UENUM(BlueprintType)
namespace ECsProjectileState
{
	enum Type
	{
		Active				   UMETA(DisplayName = "Active"),
		DeActivating		   UMETA(DisplayName = "DeActivating"),
		InActive			   UMETA(DisplayName = "InActive"),
		ECsProjectileState_MAX UMETA(Hidden),
	};
}

namespace ECsProjectileState
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Active = TCsString(TEXT("Active"), TEXT("active"));
		const TCsString DeActivating = TCsString(TEXT("DeActivating"), TEXT("deactivating"));
		const TCsString InActive = TCsString(TEXT("InActive"), TEXT("inactive"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Active) { return Str::Active.Value; }
		if (EType == Type::DeActivating) { return Str::DeActivating.Value; }
		if (EType == Type::InActive) { return Str::InActive.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Active) { return Type::Active; }
		if (String == Str::DeActivating) { return Type::DeActivating; }
		if (String == Str::InActive) { return Type::InActive; }
		return Type::ECsProjectileState_MAX;
	}
}

#define ECS_PROJECTILE_STATE_MAX (uint8)ECsProjectileState::ECsProjectileState_MAX
typedef TEnumAsByte<ECsProjectileState::Type> TCsProjectileState;

UENUM(BlueprintType)
namespace ECsProjectileDeActivate
{
	enum Type
	{
		Collision					UMETA(DisplayName = "Collision"),
		Movement					UMETA(DisplayName = "Movement"),
		Mesh						UMETA(DisplayName = "Mesh"),
		ECsProjectileDeActivate_MAX UMETA(Hidden),
	};
}

namespace ECsProjectileDeActivate
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Collision = TCsString(TEXT("Collision"), TEXT("collision"));
		const TCsString Movement = TCsString(TEXT("Movement"), TEXT("movement"));
		const TCsString Mesh = TCsString(TEXT("Mesh"), TEXT("mesh"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Collision) { return Str::Collision.Value; }
		if (EType == Type::Movement) { return Str::Movement.Value; }
		if (EType == Type::Mesh) { return Str::Mesh.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Collision) { return Type::Collision; }
		if (String == Str::Movement) { return Type::Movement; }
		if (String == Str::Mesh) { return Type::Mesh; }
		return Type::ECsProjectileDeActivate_MAX;
	}
}

#define ECS_PROJECTILE_DEACTIVATE_MAX (uint8)ECsProjectileDeActivate::ECsProjectileDeActivate_MAX
typedef TEnumAsByte<ECsProjectileDeActivate::Type> TCsProjectileDeActivate;

USTRUCT(BlueprintType)
struct FCsProjectileFireCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool IsAllocated;

	UPROPERTY()
	float Time;
	UPROPERTY()
	float RealTime;
	UPROPERTY()
	uint64 Frame;

	UPROPERTY()
	float ChargePercent;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float AdditionalSpeed;

	UPROPERTY()
	TWeakObjectPtr<AActor> HomingTarget;

	UPROPERTY()
	FName HomingBoneName;

	UPROPERTY()
	float HomingAccelerationMagnitude;

	FCsProjectileFireCache()
	{
		Reset();
	}

	FCsProjectileFireCache& operator=(const FCsProjectileFireCache& B)
	{
		IsAllocated = B.IsAllocated;
		Time = B.Time;
		RealTime = B.RealTime;
		Frame = B.Frame;
		ChargePercent = B.ChargePercent;
		Location = B.Location;
		Direction = B.Direction;
		AdditionalSpeed = B.AdditionalSpeed;
		HomingTarget = B.HomingTarget;
		HomingBoneName = B.HomingBoneName;
		HomingAccelerationMagnitude = B.HomingAccelerationMagnitude;
		return *this;
	}

	bool operator==(const FCsProjectileFireCache& B) const
	{
		return IsAllocated == B.IsAllocated &&
			Time == B.Time &&
			RealTime == B.RealTime &&
			Frame == B.Frame &&
			ChargePercent == B.ChargePercent &&
			Location == B.Location &&
			Direction == B.Direction &&
			AdditionalSpeed == B.AdditionalSpeed &&
			HomingTarget == B.HomingTarget &&
			HomingBoneName == B.HomingBoneName &&
			HomingAccelerationMagnitude == B.HomingAccelerationMagnitude;
	}

	bool operator!=(const FCsProjectileFireCache& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		IsAllocated = false;
		Time = 0.0f;
		RealTime = 0.0f;
		Frame = 0;
		ChargePercent = 0.0f;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		AdditionalSpeed = 0.0f;
		HomingTarget.Reset();
		HomingTarget = NULL;
		HomingBoneName = NAME_None;
		HomingAccelerationMagnitude = 0.0f;
	}

	AActor* GetHomingTarget() const
	{
		return HomingTarget.IsValid() ? HomingTarget.Get() : NULL;
	}
};

#pragma endregion Projectile