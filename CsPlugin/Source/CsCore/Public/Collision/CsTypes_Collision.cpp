// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Collision/CsTypes_Collision.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Physics
#include "PhysicalMaterials/PhysicalMaterial.h"

// TraceTypeQuery
#pragma region

namespace NCsTraceTypeQuery
{
	namespace Ref
	{
		typedef EMCsTraceTypeQuery EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery1, "Trace Type, Query 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery2, "Trace Type, Query 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery3, "Trace Type, Query 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery4, "Trace Type, Query 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery5, "Trace Type, Query 5");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery6, "Trace Type, Query 6");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery7, "Trace Type, Query 7");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery8, "Trace Type, Query 8");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery9, "Trace Type, Query 9");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery10, "Trace Type, Query 10");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery11, "Trace Type, Query 11");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery12, "Trace Type, Query 12");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery13, "Trace Type, Query 13");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery14, "Trace Type, Query 14");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery15, "Trace Type, Query 15");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery16, "Trace Type, Query 16");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery17, "Trace Type, Query 17");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery18, "Trace Type, Query 18");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery19, "Trace Type, Query 19");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery20, "Trace Type, Query 20");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery21, "Trace Type, Query 21");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery22, "Trace Type, Query 22");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery23, "Trace Type, Query 23");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery24, "Trace Type, Query 24");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery25, "Trace Type, Query 25");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery26, "Trace Type, Query 26");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery27, "Trace Type, Query 27");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery28, "Trace Type, Query 28");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery29, "Trace Type, Query 29");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery30, "Trace Type, Query 30");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery31, "Trace Type, Query 31");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery32, "Trace Type, Query 32");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TraceTypeQuery_MAX, "MAX");
	}
}

#pragma endregion TraceTypeQuery

// CollisionEnabled
#pragma region

namespace ECollisionEnabled
{
	namespace Ref
	{
		typedef EMCollisionEnabled EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(NoCollision);
		CSCORE_API CS_ADD_TO_ENUM_MAP(QueryOnly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(PhysicsOnly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(QueryAndPhysics);
	}
}

#pragma endregion CollisionEnabled

// CollisionChannel
#pragma region

namespace NCsCollisionChannel
{
	namespace Ref
	{
		typedef EMCsCollisionChannel EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_WorldStatic, "World Static");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_WorldDynamic, "World Dynamic");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Pawn, "Pawn");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Visibility, "Visibility");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Camera, "Camera");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_PhysicsBody, "Physics Body");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Vehicle, "Vehicle");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Destructible, "Destructible");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel1, "EngineTraceChannel 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel2, "EngineTraceChannel 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel3, "EngineTraceChannel 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel4, "EngineTraceChannel 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel5, "EngineTraceChannel 5");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel6, "EngineTraceChannel 6");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel1, "GameTraceChannel 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel2, "GameTraceChannel 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel3, "GameTraceChannel 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel4, "GameTraceChannel 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel5, "GameTraceChannel 6");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel6, "GameTraceChannel 7");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel7, "GameTraceChannel 8");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel8, "GameTraceChannel 9");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel9, "GameTraceChannel 10");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel10, "GameTraceChannel 11");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel11, "GameTraceChannel 12");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel12, "GameTraceChannel 13");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel13, "GameTraceChannel 14");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel14, "GameTraceChannel 15");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel15, "GameTraceChannel 16");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel16, "GameTraceChannel 17");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel17, "GameTraceChannel 18");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_MAX, "MAX");
	}
}

#pragma endregion CollisionChannel

// CollisionResponse
#pragma region

namespace NCsCollisionResponse
{
	namespace Ref
	{
		typedef EMCollisionResponse EnumMapType;

		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_Ignore, "Ignore");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_Overlap, "Overlap");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_Block, "Block");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_MAX, "MAX");
	}
}

#pragma endregion CollisionResponse

// CollisionShape
#pragma region

namespace NCsCollisionShape
{
	namespace Ref
	{
		typedef EMCsCollisionShape EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Line);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Box);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sphere);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Capsule);
	}
}

#pragma endregion CollisionShape

// FCsCollisionShape
#pragma region

FCollisionShape FCsCollisionShape::ToShape() const
{
	if (Type == ECsCollisionShapeType::Line)
		return FCollisionShape();
	if (Type == ECsCollisionShapeType::Box)
		return FCollisionShape::MakeBox(HalfExtent);
	if (Type == ECsCollisionShapeType::Sphere)
		return FCollisionShape::MakeSphere(Radius);
	if (Type == ECsCollisionShapeType::Capsule)
		return FCollisionShape::MakeCapsule(Radius, HalfHeight);
	return FCollisionShape();
}

bool FCsCollisionShape::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (Type == ECsCollisionShapeType::ECsCollisionShapeType_MAX)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Type: ECsCollisionShapeType::ECsCollisionShapeType_MAX is NOT Valid."), *Context));
		return false;
	}

	// Box
	if (Type == ECsCollisionShapeType::Box)
	{
		CS_IS_FLOAT_GREATER_THAN(HalfExtent.X, 0.0f)
		CS_IS_FLOAT_GREATER_THAN(HalfExtent.Y, 0.0f)
		CS_IS_FLOAT_GREATER_THAN(HalfExtent.Z, 0.0f)
	}
	// Sphere
	if (Type == ECsCollisionShapeType::Sphere)
	{
		CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)
	}
	// Capsule
	if (Type == ECsCollisionShapeType::Capsule)
	{
		CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)
		CS_IS_FLOAT_GREATER_THAN(HalfHeight, 0.0f)
	}
	return true;
}

#pragma endregion FCsCollisionShape

// FCsCollisionPreset
#pragma region

void FCsCollisionPreset::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
{
	CS_IS_PTR_NULL_CHECKED(Component)

	check(IsValidChecked(Context));

	if (CollisionEnabled != ECollisionEnabled::NoCollision)
	{
		Component->SetCollisionObjectType(ObjectType);
		Component->SetCollisionResponseToChannels(CollisionResponses);

		Component->SetNotifyRigidBodyCollision(bSimulationGeneratesHitEvents);
		Component->SetGenerateOverlapEvents(bGenerateOverlapEvents);

		Component->SetCollisionEnabled(CollisionEnabled);
	}
}

bool FCsCollisionPreset::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL(Component)

	if (!IsValid(Context, Log))
		return false;

	if (CollisionEnabled != ECollisionEnabled::NoCollision)
	{
		Component->SetCollisionObjectType(ObjectType);
		Component->SetCollisionResponseToChannels(CollisionResponses);

		Component->SetNotifyRigidBodyCollision(bSimulationGeneratesHitEvents);
		Component->SetGenerateOverlapEvents(bGenerateOverlapEvents);

		Component->SetCollisionEnabled(CollisionEnabled);
	}
	return true;
}

bool FCsCollisionPreset::IsValidChecked(const FString& Context) const
{
	if (CollisionEnabled != ECollisionEnabled::NoCollision)
	{
		checkf(ObjectType != ECollisionChannel::ECC_OverlapAll_Deprecated, TEXT("%s: ObjectType == ECollisionChannel::ECC_OverlapAll_Deprecated is NOT Valid."), *Context);

		checkf(ObjectType != ECollisionChannel::ECC_MAX, TEXT("%s: ObjectType == ECollisionChannel::ECC_MAX is NOT Valid."), *Context);

		bool bAllIgnore = true;

		for (const ECollisionChannel& Channel : EMCsCollisionChannel::Get())
		{
			const ECollisionResponse Response = CollisionResponses.GetResponse(Channel);

			if (Response != ECR_Ignore &&
				Response != ECR_MAX)
			{
				bAllIgnore = false;
				break;
			}
		}

		checkf(!bAllIgnore, TEXT("%s: ALL channels in CollisionResponses are either ECollisionResponse::ECR_Ignore or ECollisionResponse::ECR_MAX. At least ONE channel must be ECollisionResponse::ECR_Overlap or ECollisionResponse::ECR_Block."), *Context);
	}
	return true;
}

bool FCsCollisionPreset::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (CollisionEnabled != ECollisionEnabled::NoCollision)
	{
		if (ObjectType == ECollisionChannel::ECC_OverlapAll_Deprecated)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ObjectType == ECollisionChannel::ECC_OverlapAll_Deprecated is NOT Valid."), *Context));
			return false;
		}

		if (ObjectType == ECollisionChannel::ECC_MAX)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ObjectType == ECollisionChannel::ECC_MAX is NOT Valid."), *Context));
			return false;
		}

		bool bAllIgnore = true;

		for (const ECollisionChannel& Channel : EMCsCollisionChannel::Get())
		{
			const ECollisionResponse Response = CollisionResponses.GetResponse(Channel);

			if (Response != ECR_Ignore &&
				Response != ECR_MAX)
			{
				bAllIgnore = false;
			}
		}

		if (bAllIgnore)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ALL channels in CollisionResponses are either ECollisionResponse::ECR_Ignore or ECollisionResponse::ECR_MAX. At least ONE channel must be ECollisionResponse::ECR_Overlap or ECollisionResponse::ECR_Block."), *Context));
			return false;
		}
	}
	return true;
}

#pragma endregion FCsCollisionPreset

// Collision
#pragma region

CSCORE_API const FHitResult NCsCollision::NHit::Default = FHitResult();

#pragma endregion Collision

namespace NCsCollisionQueryParams
{
	void ResetComponentListUnique(FCollisionQueryParams& Params)
	{
		// A bit of a hack to get access to Params.bComponentListUnique, which is private.
		// Access is needed to when calling Reset

		// Get pointer to start of Params.StatId
		//FName* TraceTag = ((FName*)(&Params));
		//char* Base = (char*)TraceTag;
		TStatId* StatdId = &(Params.StatId);
		char* Base = (char*)StatdId;

		size_t Offset = 0;
		/*
		// Offset by TraceTag
		size_t Offset = sizeof(FName);
		// Offset by OwnerTag
		Offset += sizeof(FName);
		// Offset by bTraceComplex
		Offset += sizeof(bool);
		// Offset by bFindInitialOverlaps
		Offset += sizeof(bool);
		// Offset by bReturnFaceIndex
		Offset += sizeof(bool);
		// Offset by bReturnPhysicalMaterial
		Offset += sizeof(bool);
		// Offset by bIgnoreBlocks
		Offset += sizeof(bool);
		// Offset by bIgnoreTouches
		Offset += sizeof(bool);
		// Offset by bSkipNarrowPhase
		Offset += sizeof(bool);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 1;
		// Offset by MobilityType
		Offset += sizeof(EQueryMobilityType);
		// Offset by IgnoreMask
		Offset += sizeof(FMaskFilter);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 3;
		*/
		// Offset by StatId
		Offset += sizeof(TStatId);
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
		// Offset by bDebugQuery
		Offset += sizeof(bool);
#endif
		*((bool*)(Base + Offset)) = true;
	}

	TArray<uint32, TInlineAllocator<8>>& GetIgnoreComponents(FCollisionQueryParams& Params)
	{
		// A bit of a hack to get access to Params.IgnoreComponents, which is private.
		// Access is needed to efficiently reset the Array.

		// Get pointer to start of Params.StatId
		//FName* TraceTag = ((FName*)(&Params));
		TStatId* StatdId = &(Params.StatId);
		char* Base = (char*)StatdId;

		size_t Offset = 0;
		/*
		// Offset by TraceTag
		size_t Offset = sizeof(FName);
		// Offset by OwnerTag
		Offset += sizeof(FName);
		// Offset by bTraceComplex
		Offset += sizeof(bool);
		// Offset by bFindInitialOverlaps
		Offset += sizeof(bool);
		// Offset by bReturnFaceIndex
		Offset += sizeof(bool);
		// Offset by bReturnPhysicalMaterial
		Offset += sizeof(bool);
		// Offset by bIgnoreBlocks
		Offset += sizeof(bool);
		// Offset by bIgnoreTouches
		Offset += sizeof(bool);
		// Offset by bSkipNarrowPhase
		Offset += sizeof(bool);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 1;
		// Offset by MobilityType
		Offset += sizeof(EQueryMobilityType);
		// Offset by IgnoreMask
		Offset += sizeof(FMaskFilter);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 3;
		*/
		// Offset by StatId
		Offset += sizeof(TStatId);
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
		// Offset by bDebugQuery
		Offset += sizeof(bool);
#endif
		// Offset by bComponentListUnique
		Offset += sizeof(bool);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 6;

		return *((TArray<uint32, TInlineAllocator<8>>*)(Base + Offset));
	}

	TArray<uint32, TInlineAllocator<4>>& GetIgnoreActors(FCollisionQueryParams& Params)
	{
		// A bit of a hack to get access to Params.IgnoreActors, which is private.
		// Access is needed to efficiently reset the Array.

		// Get pointer to start of struct
		//FName* TraceTag = ((FName*)(&Params));
		//char* Base = (char*)TraceTag;
		TStatId* StatdId = &(Params.StatId);
		char* Base = (char*)StatdId;

		size_t Offset = 0;
		/*
		// Offset by TraceTag
		size_t Offset = sizeof(FName);
		// Offset by OwnerTag
		Offset += sizeof(FName);
		// Offset by bTraceComplex
		Offset += sizeof(bool);
		// Offset by bFindInitialOverlaps
		Offset += sizeof(bool);
		// Offset by bReturnFaceIndex
		Offset += sizeof(bool);
		// Offset by bReturnPhysicalMaterial
		Offset += sizeof(bool);
		// Offset by bIgnoreBlocks
		Offset += sizeof(bool);
		// Offset by bIgnoreTouches
		Offset += sizeof(bool);
		// Offset by bSkipNarrowPhase
		Offset += sizeof(bool);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 1;
		// Offset by MobilityType
		Offset += sizeof(EQueryMobilityType);
		// Offset by IgnoreMask
		Offset += sizeof(FMaskFilter);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 3;
		*/
		// Offset by StatId
		Offset += sizeof(TStatId);
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
		// Offset by bDebugQuery
		Offset += sizeof(bool);
#endif
		// Offset by bComponentListUnique
		Offset += sizeof(bool);
		// TODO: HACK: Need to debug why there is an extra byte here
		Offset += 6;
		// Offset by IgnoreComponents
		Offset += sizeof(TArray<uint32, TInlineAllocator<8>>);

		return *((TArray<uint32, TInlineAllocator<4>>*)(Base + Offset));
	}

	void ConditionalResetIgnoreComponents(FCollisionQueryParams& Params)
	{
		TArray<uint32, TInlineAllocator<8>>& IgnoreComponents = GetIgnoreComponents(Params);

		if (IgnoreComponents.Max() > 8)
			IgnoreComponents.Reset(8);
		else
			IgnoreComponents.Reset(IgnoreComponents.Max());
	}

	void ConditionalResetIgnoreActors(FCollisionQueryParams& Params)
	{
		TArray<uint32, TInlineAllocator<4>>& IgnoreActors = GetIgnoreActors(Params);

		if (IgnoreActors.Max() > 4)
			IgnoreActors.Reset(4);
		else
			IgnoreActors.Reset(IgnoreActors.Max());
	}

	void Reset(FCollisionQueryParams& Params)
	{
		Params.TraceTag = NAME_None;
		Params.OwnerTag = NAME_None;
		Params.bTraceComplex = false;
		Params.bFindInitialOverlaps = true;
		Params.bReturnFaceIndex = false;
		Params.bReturnPhysicalMaterial = false;
		Params.bIgnoreBlocks = false;
		Params.bIgnoreTouches = false;
		Params.bSkipNarrowPhase = false;
		Params.MobilityType = EQueryMobilityType::Any;
		Params.IgnoreMask = 0;
		Params.StatId = FCollisionQueryParams::GetUnknownStatId();
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
		Params.bDebugQuery = false;
#endif
		ResetComponentListUnique(Params);
		ConditionalResetIgnoreComponents(Params);
		ConditionalResetIgnoreActors(Params);
	}
}

// FCsCollisionQueryParams
#pragma region

bool FCsCollisionQueryParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE(IgnoreComponents, UPrimitiveComponent*, 8)

	CS_IS_TARRAY_ANY_NULL(IgnoreComponents, UPrimitiveComponent)

	CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE(IgnoreActors, AActor*, 4)

	CS_IS_TARRAY_ANY_NULL(IgnoreActors, AActor)

	return true;
}

#pragma endregion FCsCollisionQueryParams

// FCsCollisionObjectQueryParams
#pragma region

bool FCsCollisionObjectQueryParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_TARRAY_EMPTY(ObjectTypesToQuery, TEnumAsByte<EObjectTypeQuery>)
	return true;
}

#pragma endregion FCsCollisionObjectQueryParams

namespace NCsHitResult
{
	EPhysicalSurface GetPhysSurfaceType(const FHitResult& Hit)
	{
		UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;

		return PhysMaterial ? (EPhysicalSurface)PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;
	}
}