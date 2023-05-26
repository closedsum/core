// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Damage_Collision.h"

// Library
#include "Library/CsLibrary_Valid.h"

// DamageCollisionMethod
#pragma region

namespace NCsDamageCollisionMethod
{
	namespace Ref
	{
		typedef EMCsDamageCollisionMethod EnumMapType;

		CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsSweep, "Physics Sweep");
		CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsOverlap, "Physics Overlap");
		CSDMG_API CS_ADD_TO_ENUM_MAP(Custom);
		CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDamageCollisionMethod_MAX, "MAX");
	}
}

namespace NCsDamage
{
	namespace NCollision
	{
		namespace NMethod
		{
			namespace Ref
			{
				typedef EMMethod EnumMapType;

				CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsSweep, "Physics Sweep");
				CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsOverlap, "Physics Overlap");
				CSDMG_API CS_ADD_TO_ENUM_MAP(Custom);
				CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
			}
		}
	}
}

#pragma endregion DamageCollisionMethod

// FCsDamage_CollisionInfo
#pragma region

#define InfoType NCsDamage::NCollision::FInfo

void FCsDamage_CollisionInfo::CopyToInfo(InfoType* Info)
{
	typedef NCsDamage::NCollision::EMethod MethodType;

	Info->SetMethod((MethodType*)(&Method));
	Info->SetChannel((ECollisionChannel*)(&Channel));
	Info->SetCount(&Count);
}

void FCsDamage_CollisionInfo::CopyToInfoAsValue(InfoType* Info) const
{
	typedef NCsDamage::NCollision::EMethod MethodType;

	Info->SetMethod((MethodType)Method);
	Info->SetChannel((ECollisionChannel)Channel);
	Info->SetCount(Count);
}

#undef InfoType

bool FCsDamage_CollisionInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsDamageCollisionMethod, Method);

	checkf(Channel != ECollisionChannel::ECC_OverlapAll_Deprecated && Channel != ECollisionChannel::ECC_MAX, TEXT("%s: Channel == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context);
	
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Count, 0)
	return true;
}

bool FCsDamage_CollisionInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsDamageCollisionMethod, ECsDamageCollisionMethod, Method);

	if (Channel == ECollisionChannel::ECC_OverlapAll_Deprecated ||
		Channel == ECollisionChannel::ECC_MAX)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Channel == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context));
		return true;
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Count, 0)
	return true;
}

namespace NCsDamage
{
	namespace NCollision
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			typedef NCsDamage::NCollision::EMMethod MethodMapType;

			CS_IS_ENUM_VALID_CHECKED(MethodMapType, GetMethod());

			checkf(GetChannel() != ECollisionChannel::ECC_OverlapAll_Deprecated && GetChannel() != ECollisionChannel::ECC_MAX, TEXT("%s: GetChannel() == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context);
			
			CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCount(), 0)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
		{
			typedef NCsDamage::NCollision::EMMethod MethodMapType;
			typedef NCsDamage::NCollision::EMethod MethodType;

			CS_IS_ENUM_VALID(MethodMapType, MethodType, GetMethod())

			if (GetChannel() == ECollisionChannel::ECC_OverlapAll_Deprecated ||
				GetChannel() == ECollisionChannel::ECC_MAX)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetChannel() == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context));
				return true;
			}
			CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCount(), 0)
			return true;
		}
	}
}

#pragma endregion FCsDamage_CollisionInfo