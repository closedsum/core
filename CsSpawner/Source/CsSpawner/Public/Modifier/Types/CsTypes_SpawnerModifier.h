// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_SpawnerModifier.generated.h"

// SpawnerModifier
#pragma region

USTRUCT(BlueprintType)
struct CSSPAWNER_API FECsSpawnerModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSpawnerModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSpawnerModifier)

struct CSSPAWNER_API EMCsSpawnerModifier : public TCsEnumStructMap<FECsSpawnerModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSpawnerModifier, FECsSpawnerModifier, uint8)
};

namespace NCsSpawnerModifier
{
	typedef FECsSpawnerModifier Type;
	typedef EMCsSpawnerModifier EnumMapType;

	// Movement
	extern CSSPAWNER_API const Type MovementSpeed;
	extern CSSPAWNER_API const Type SteeringSeparateForcePriority;
	extern CSSPAWNER_API const Type SteeringSeparateForceRadius;
	// Collision
	extern CSSPAWNER_API const Type CollisionRadius;
	extern CSSPAWNER_API const Type KnockbackEnabled;
	// Attack
	extern CSSPAWNER_API const Type AttackSpeed;
}

#pragma endregion SpawnerModifier

// SpawnerModifierImpl
#pragma region

namespace NCsSpawner
{
	namespace NModifier
	{
		enum class EImpl : uint8 
		{
			Int,
			Float,
			Toggle,
			EImpl_MAX
		};
	}
}

using CsSpawnerModifierImplType = NCsSpawner::NModifier::EImpl;

#pragma endregion SpawnerModifierImpl

// SpawnerModifier_Int
#pragma region

USTRUCT(BlueprintType)
struct CSSPAWNER_API FECsSpawnerModifier_Int : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSpawnerModifier_Int)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSpawnerModifier_Int)

struct CSSPAWNER_API EMCsSpawnerModifier_Int : public TCsEnumStructMap<FECsSpawnerModifier_Int, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSpawnerModifier_Int, FECsSpawnerModifier_Int, uint8)
};

namespace NCsSpawnerModifier_Int
{
	typedef FECsSpawnerModifier_Int Type;
	typedef EMCsSpawnerModifier_Int EnumMapType;

	// Movement
	extern CSSPAWNER_API const Type SteeringSeparateForcePriority;

	FORCEINLINE const Type& ConvertFrom(const FECsSpawnerModifier& BaseType)
	{
		return EMCsSpawnerModifier_Int::Get().GetEnum(BaseType.GetName());
	}

	FORCEINLINE const FECsSpawnerModifier& ConvertTo(const Type& InType)
	{
		return EMCsSpawnerModifier::Get().GetEnum(InType.GetName());
	}
}

#pragma endregion SpawnerModifier_Int

// SpawnerModifier_Float
#pragma region

USTRUCT(BlueprintType)
struct CSSPAWNER_API FECsSpawnerModifier_Float : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSpawnerModifier_Float)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSpawnerModifier_Float)

struct CSSPAWNER_API EMCsSpawnerModifier_Float : public TCsEnumStructMap<FECsSpawnerModifier_Float, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSpawnerModifier_Float, FECsSpawnerModifier_Float, uint8)
};

namespace NCsSpawnerModifier_Float
{
	typedef FECsSpawnerModifier_Float Type;
	typedef EMCsSpawnerModifier_Float EnumMapType;

	// Movement
	extern CSSPAWNER_API const Type MovementSpeed;
	extern CSSPAWNER_API const Type SteeringSeparateForceRadius;
	// Collision
	extern CSSPAWNER_API const Type CollisionRadius;
	// Attack
	extern CSSPAWNER_API const Type AttackSpeed;

	FORCEINLINE const Type& ConvertFrom(const FECsSpawnerModifier& BaseType)
	{
		return EMCsSpawnerModifier_Float::Get().GetEnum(BaseType.GetName());
	}

	FORCEINLINE const FECsSpawnerModifier& ConvertTo(const Type& InType)
	{
		return EMCsSpawnerModifier::Get().GetEnum(InType.GetName());
	}
}

#pragma endregion SpawnerModifier_Float

// SpawnerModifier_Toggle
#pragma region

USTRUCT(BlueprintType)
struct CSSPAWNER_API FECsSpawnerModifier_Toggle : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSpawnerModifier_Toggle)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSpawnerModifier_Toggle)

struct CSSPAWNER_API EMCsSpawnerModifier_Toggle : public TCsEnumStructMap<FECsSpawnerModifier_Toggle, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSpawnerModifier_Toggle, FECsSpawnerModifier_Toggle, uint8)
};

namespace NCsSpawnerModifier_Toggle
{
	typedef FECsSpawnerModifier_Toggle Type;
	typedef EMCsSpawnerModifier_Toggle EnumMapType;

	// Collision
	extern CSSPAWNER_API const Type KnockbackEnabled;

	FORCEINLINE const Type& ConvertFrom(const FECsSpawnerModifier& BaseType)
	{
		return EMCsSpawnerModifier_Toggle::Get().GetEnum(BaseType.GetName());
	}

	FORCEINLINE const FECsSpawnerModifier& ConvertTo(const Type& InType)
	{
		return EMCsSpawnerModifier::Get().GetEnum(InType.GetName());
	}
}

#pragma endregion SpawnerModifier_Float