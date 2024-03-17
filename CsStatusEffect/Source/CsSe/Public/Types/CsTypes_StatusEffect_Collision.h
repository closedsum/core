// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Macro/CsMacro_Namespace.h"
#include "Types/CsTypes_Macro.h"
#include "Types/Enum/CsEnumMap.h"
#include "Engine/EngineTypes.h"
// Utility
#include "Utility/CsSeLog.h"

#include "CsTypes_StatusEffect_Collision.generated.h"

// StatusEffectCollisionMethod
#pragma region

/**
* Describes how to check if an object should receive a Status Effect.
* The "collision" is determined by the Data associated with the Status Effect.
*  Status Effect is an objects that implements the interface: NCsStatusEffect::IStatusEffect
*  Data is an object that implements the interface: DataType (NCsStatusEffect::NData::IData).
*/
UENUM(BlueprintType)
enum class ECsStatusEffectCollisionMethod : uint8
{
	PhysicsSweep						UMETA(DisplayName = "Physics Sweep"),
	PhysicsOverlap						UMETA(DisplayName = "Physics Overlap"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsStatusEffectCollisionMethod_MAX	UMETA(Hidden),
};

struct CSSE_API EMCsStatusEffectCollisionMethod final : public TCsEnumMap<ECsStatusEffectCollisionMethod>
{
	CS_ENUM_MAP_BODY(EMCsStatusEffectCollisionMethod, ECsStatusEffectCollisionMethod)
};

namespace NCsStatusEffectCollisionMethod
{
	typedef ECsStatusEffectCollisionMethod Type;

	namespace Ref
	{
		extern CSSE_API const Type PhysicsSweep;
		extern CSSE_API const Type PhysicsOverlap;
		extern CSSE_API const Type Custom;
		extern CSSE_API const Type ECsStatusEffectCollisionMethod_MAX;
	}
}

namespace NCsStatusEffect
{
	namespace NCollision
	{
		/**
		* Describes how to check if an object should receive a Status Effect.
		* The "collision" is determined by the Data associated with the Status Effect.
		*  Status Effect is an objects that implements the interface: NCsStatusEffect::IStatusEffect
		*  Data is an object that implements the interface: DataType (NCsStatusEffect::NData::IData).
		*/
		enum class EMethod : uint8
		{
			PhysicsSweep,
			PhysicsOverlap,
			Custom,
			EMethod_MAX
		};

		struct CSSE_API EMMethod final : public TCsEnumMap<EMethod>
		{
			CS_ENUM_MAP_BODY(EMMethod, EMethod)
		};

		namespace NMethod
		{
			typedef EMethod Type;

			namespace Ref
			{
				extern CSSE_API const Type PhysicsSweep;
				extern CSSE_API const Type PhysicsOverlap;
				extern CSSE_API const Type Custom;
				extern CSSE_API const Type EMethod_MAX;
			}
		}
	}
}

#pragma endregion StatusEffectCollisionMethod

// FCsStatusEffect_CollisionInfo
#pragma region

// NCsStatusEffect::NCollision::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NCollision, FInfo)

/**
* Describes any information related to Collision for a Status Effect.
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsStatusEffect_CollisionInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes how to check if an object should receive a Status Effect.
		The "collision" is determined by the Data associated with the Status Effect. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsSe|Collision")
	ECsStatusEffectCollisionMethod Method;

	/** The Channel the Status Effect is broadcasted on. 
		Status Effect will "collide" with objects that block this Channel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsSe|Collision")
	TEnumAsByte<ECollisionChannel> Channel;

	/** Whether to use Count to determine the number of times the Status Effect
		will "collide" in a given "check". 
		TRUE = Infinite.
		FALE = Count number of times. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsSe|Collision", meta = (ScriptName = "m_bCount", InlineEditConditionToggle))
	bool bCount;

	/** The number of times the Status Effect will "collide" in a given "check". 
		NOTE: bCount must be TRUE. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsSe|Collision", meta = (ScriptName = "m_Count", EditCondition = "bCount", UIMin = "0", ClampMin = "0"))
	int32 Count;

	FCsStatusEffect_CollisionInfo() :
		Method(ECsStatusEffectCollisionMethod::PhysicsSweep),
		Channel(ECollisionChannel::ECC_WorldDynamic),
		bCount(false),
		Count(0)
	{
	}

#define InfoType NCsStatusEffect::NCollision::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;
};

namespace NCsStatusEffect
{
	namespace NCollision
	{
		/**
		* Describes any information related to Collision for Damage.
		*/
		struct CSSE_API FInfo
		{
		#define MethodType NCsStatusEffect::NCollision::EMethod

		private:

			/** Describes how to check if an object should receive damage.
				The "collision" is determined by the data associated with the damage. */
			CS_DECLARE_MEMBER_WITH_PROXY(Method, MethodType)
			/** The Channel the Damage is broadcasted on.
				Damage will "collide" with objects that block this Channel. */
			CS_DECLARE_MEMBER_WITH_PROXY(Channel, ECollisionChannel)
			/** Whether to use Count to determine the number of times the Status Effect
				will "collide" in a given "check". 
				TRUE = Infinite.
				FALE = Count number of times. */
			CS_DECLARE_MEMBER_WITH_PROXY(bCount, bool)
			/** The number of times the Status Effect will "collide" in a given "check".
				NOTE: bCount must be TRUE. */
			CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Method, MethodType::PhysicsSweep),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Channel, ECollisionChannel::ECC_WorldDynamic),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bCount, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 0)
			{
				CS_CTOR_SET_MEMBER_PROXY(Method);
				CS_CTOR_SET_MEMBER_PROXY(Channel);
				CS_CTOR_SET_MEMBER_PROXY(bCount);
				CS_CTOR_SET_MEMBER_PROXY(Count);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Method, MethodType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Channel, ECollisionChannel)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCount, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)

			FORCEINLINE void CopyProxy(FInfo* From)
			{
				SetMethod(From->GetMethodPtr());
				SetChannel(From->GetChannelPtr());
				SetbCount(From->GetbCountPtr());
				SetCount(From->GetCountPtr());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;

		#undef MethodType
		};
	}
}

#pragma endregion FCsStatusEffect_CollisionInfo