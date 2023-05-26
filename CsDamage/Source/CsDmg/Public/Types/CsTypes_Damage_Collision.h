// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Engine/EngineTypes.h"
// Utility
#include "Utility/CsDmgLog.h"

#include "CsTypes_Damage_Collision.generated.h"

// DamageCollisionMethod
#pragma region

/**
* Describes how to check if an object should receive damage.
* The "collision" is determined by the data associated with the damage.
*  Data should implement the interface: DamageShapeType (NCsDamage::NData::NShape::IShape).
*/
UENUM(BlueprintType)
enum class ECsDamageCollisionMethod : uint8
{
	PhysicsSweep					UMETA(DisplayName = "Physics Sweep"),
	PhysicsOverlap					UMETA(DisplayName = "Physics Overlap"),
	Custom							UMETA(DisplayName = "Custom"),
	ECsDamageCollisionMethod_MAX	UMETA(Hidden),
};

struct CSDMG_API EMCsDamageCollisionMethod final : public TCsEnumMap<ECsDamageCollisionMethod>
{
	CS_ENUM_MAP_BODY(EMCsDamageCollisionMethod, ECsDamageCollisionMethod)
};

namespace NCsDamageCollisionMethod
{
	typedef ECsDamageCollisionMethod Type;

	namespace Ref
	{
		extern CSDMG_API const Type PhysicsSweep;
		extern CSDMG_API const Type PhysicsOverlap;
		extern CSDMG_API const Type Custom;
		extern CSDMG_API const Type ECsDamageCollisionMethod_MAX;
	}
}

namespace NCsDamage
{
	namespace NCollision
	{
		/**
		* Describes how to check if an object should receive damage.
		* The "collision" is determined by the data associated with the damage.
		*  Data should implement the interface: DamageShapeType (NCsDamage::NData::NShape::IShape).
		*/
		enum class EMethod : uint8
		{
			PhysicsSweep,
			PhysicsOverlap,
			Custom,
			EMethod_MAX
		};

		struct CSDMG_API EMMethod final : public TCsEnumMap<EMethod>
		{
			CS_ENUM_MAP_BODY(EMMethod, EMethod)
		};

		namespace NMethod
		{
			typedef EMethod Type;

			namespace Ref
			{
				extern CSDMG_API const Type PhysicsSweep;
				extern CSDMG_API const Type PhysicsOverlap;
				extern CSDMG_API const Type Custom;
				extern CSDMG_API const Type EMethod_MAX;
			}
		}
	}
}

#pragma endregion DamageCollisionMethod

// FCsDamage_CollisionInfo
#pragma region

// NCsDamage::NCollision::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NCollision, FInfo)

/**
* Describes any information related to Collision for Damage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamage_CollisionInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes how to check if an object should receive damage.
		The "collision" is determined by the data associated with the damage. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Collision")
	ECsDamageCollisionMethod Method;

	/** The Channel the Damage is broadcasted on. 
		Damage will "collide" with objects that block this Channel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Collision")
	TEnumAsByte<ECollisionChannel> Channel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Collision", meta = (UIMin = "0", ClampMin = "0"))
	int32 Count;

	FCsDamage_CollisionInfo() :
		Method(ECsDamageCollisionMethod::PhysicsSweep),
		Channel(ECollisionChannel::ECC_WorldDynamic),
		Count(0)
	{
	}

#define InfoType NCsDamage::NCollision::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

namespace NCsDamage
{
	namespace NCollision
	{
		/**
		* Describes any information related to Collision for Damage.
		*/
		struct CSDMG_API FInfo
		{
		#define MethodType NCsDamage::NCollision::EMethod

		private:

			/** Describes how to check if an object should receive damage.
				The "collision" is determined by the data associated with the damage. */
			CS_DECLARE_MEMBER_WITH_PROXY(Method, MethodType)
			/** The Channel the Damage is broadcasted on.
				Damage will "collide" with objects that block this Channel. */
			CS_DECLARE_MEMBER_WITH_PROXY(Channel, ECollisionChannel)
			CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Method, MethodType::PhysicsSweep),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Channel, ECollisionChannel::ECC_WorldDynamic),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 0)
			{
				CS_CTOR_SET_MEMBER_PROXY(Method);
				CS_CTOR_SET_MEMBER_PROXY(Channel);
				CS_CTOR_SET_MEMBER_PROXY(Count);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Method, MethodType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Channel, ECollisionChannel)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)

			FORCEINLINE void CopyProxy(FInfo* From)
			{
				SetMethod(From->GetMethodPtr());
				SetChannel(From->GetChannelPtr());
				SetCount(From->GetCountPtr());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

		#undef MethodType
		};
	}
}

#pragma endregion FCsDamage_CollisionInfo