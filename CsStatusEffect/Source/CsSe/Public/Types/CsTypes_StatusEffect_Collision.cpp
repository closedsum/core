// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_StatusEffect_Collision.h"

// Library
#include "Library/CsLibrary_Valid.h"

// StatusEffectCollisionMethod
#pragma region

namespace NCsStatusEffectCollisionMethod
{
	namespace Ref
	{
		typedef EMCsStatusEffectCollisionMethod EnumMapType;

		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsSweep, "Physics Sweep");
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsOverlap, "Physics Overlap");
		CSSE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStatusEffectCollisionMethod_MAX, "MAX");
	}
}

namespace NCsStatusEffect
{
	namespace NCollision
	{
		namespace NMethod
		{
			namespace Ref
			{
				typedef EMMethod EnumMapType;

				CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsSweep, "Physics Sweep");
				CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsOverlap, "Physics Overlap");
				CSSE_API CS_ADD_TO_ENUM_MAP(Custom);
				CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
			}
		}
	}
}

#pragma endregion StatusEffectCollisionMethod

// FCsStatusEffect_CollisionInfo
#pragma region

#define InfoType NCsStatusEffect::NCollision::FInfo

void FCsStatusEffect_CollisionInfo::CopyToInfo(InfoType* Info)
{
	typedef NCsStatusEffect::NCollision::EMethod MethodType;

	Info->SetMethod((MethodType*)(&Method));
	Info->SetChannel((ECollisionChannel*)(&Channel));
	Info->SetCount(&Count);
}

void FCsStatusEffect_CollisionInfo::CopyToInfoAsValue(InfoType* Info) const
{
	typedef NCsStatusEffect::NCollision::EMethod MethodType;

	Info->SetMethod((MethodType)Method);
	Info->SetChannel((ECollisionChannel)Channel);
	Info->SetCount(Count);
}

#undef InfoType

bool FCsStatusEffect_CollisionInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsStatusEffectCollisionMethod, Method);

	checkf(Channel != ECollisionChannel::ECC_OverlapAll_Deprecated && Channel != ECollisionChannel::ECC_MAX, TEXT("%s: Channel == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context);
	
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Count, 0)
	return true;
}

bool FCsStatusEffect_CollisionInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsStatusEffectCollisionMethod, ECsStatusEffectCollisionMethod, Method);

	if (Channel == ECollisionChannel::ECC_OverlapAll_Deprecated ||
		Channel == ECollisionChannel::ECC_MAX)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Channel == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context));
		return true;
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Count, 0)
	return true;
}

namespace NCsStatusEffect
{
	namespace NCollision
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			typedef NCsStatusEffect::NCollision::EMMethod MethodMapType;

			CS_IS_ENUM_VALID_CHECKED(MethodMapType, GetMethod());

			checkf(GetChannel() != ECollisionChannel::ECC_OverlapAll_Deprecated && GetChannel() != ECollisionChannel::ECC_MAX, TEXT("%s: GetChannel() == (ECollisionChannel::ECC_OverlapAll_Deprecated | ECollisionChannel::ECC_MAX) is NOT Valid."), *Context);
			
			CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCount(), 0)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) const
		{
			typedef NCsStatusEffect::NCollision::EMMethod MethodMapType;
			typedef NCsStatusEffect::NCollision::EMethod MethodType;

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

#pragma endregion FCsStatusEffect_CollisionInfo