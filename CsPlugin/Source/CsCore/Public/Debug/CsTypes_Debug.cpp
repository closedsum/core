// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Debug/CsTypes_Debug.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Debug/CsLibrary_Debug_Draw.h"
// Collision
#include "CollisionShape.h"
// Engine
#include "GameFramework/Actor.h"

// DebugDrawPriority
#pragma region

namespace NCsDebugDrawPriority
{
	namespace Ref
	{
		typedef EMCsDebugDrawPriority EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Any);
		CSCORE_API CS_ADD_TO_ENUM_MAP(CVar);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Flag);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDebugDrawPriority_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDebugDrawPriority_MAX;
}

#pragma endregion DebugDrawPriority

// DebugDrawFrequency
#pragma region

namespace NCsDebugDrawFrequency
{
	namespace Ref
	{
		typedef EMCsDebugDrawFrequency EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Once);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Update);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDebugDrawFrequency_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDebugDrawFrequency_MAX;
}

#pragma endregion DebugDrawFrequency

// DebugDrawRotation
#pragma region

namespace NCsDebugDrawRotation
{
	namespace Ref
	{
		typedef EMCsDebugDrawRotation EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Absolute);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Offset);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDebugDrawRotation_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDebugDrawRotation_MAX;
}

#pragma endregion DebugDrawRotation

// FCsDebugDrawBox
#pragma region

bool FCsDebugDrawBox::CanDraw(const UObject* WorldContext) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawBox::Draw(const UObject* WorldContext, const FTransform& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform, FVector::ZeroVector);
	}
}

void FCsDebugDrawBox::Draw(const UObject* WorldContext, const FTransform& Transform, const FVector& InExtent) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform, InExtent);
	}
}

void FCsDebugDrawBox::Draw_Internal(const UObject* WorldContext, const FTransform& Transform, const FVector& InExtent) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (bSolid)
		DrawDebugSolidBox(World, Transform.GetTranslation() + Location, InExtent + Extent, Rotation.Quaternion() * Transform.GetRotation(), Color, false, LifeTime, 0);
	else
		DrawDebugBox(World, Transform.GetTranslation() + Location, InExtent + Extent, Rotation.Quaternion() * Transform.GetRotation(), Color, false, LifeTime, 0, Thickness);
}

#pragma endregion FCsDebugDrawBox

// FCsDebugDrawCircle
#pragma region

bool FCsDebugDrawCircle::CanDraw(const UObject* WorldContext) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

bool FCsDebugDrawCircle::CanDraw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar) const
{
	if (CanDraw(WorldContext))
		return true;

	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		return FCsCVarDrawMap::Get().IsDrawing(OtherCVar);
	}
	return false;
}

void FCsDebugDrawCircle::Draw(const UObject* WorldContext, const FTransform& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform);
	}
}

void FCsDebugDrawCircle::Draw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar, const FVector& InLocation, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext, OtherCVar))
	{
		FTransform InTransform = FTransform::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::Draw(const UObject* WorldContext, const FVector& InLocation, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext))
	{
		FTransform InTransform = FTransform::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::DrawAtLocation(AActor* Actor, const FECsCVarDraw& OtherCVar, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(Actor, OtherCVar))
	{
		FTransform InTransform = FTransform::Identity;
		InTransform.SetLocation(Actor->GetActorLocation());

		Draw_Internal(Actor, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::DrawAtLocation(AActor* Actor, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(Actor))
	{
		FTransform InTransform = FTransform::Identity;
		InTransform.SetLocation(Actor->GetActorLocation());

		Draw_Internal(Actor, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::DrawAtLocation(AActor* Actor, const float& Radius) const
{
	DrawAtLocation(Actor, Radius, Radius);
}

void FCsDebugDrawCircle::Draw_Internal(const UObject* WorldContext, const FTransform& Transform) const
{
	Draw_Internal(WorldContext, Transform, MinRadius, MaxRadius);
}

void FCsDebugDrawCircle::Draw_Internal(const UObject* WorldContext, const FTransform& Transform, const float& InMinRadius, const float& InMaxRadius) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	const float Min = FMath::Min(InMinRadius, InMaxRadius);
	const float Max = FMath::Max(InMinRadius, InMaxRadius);

	if (Max == 0.0f)
		return;

	FTransform AdjustedTransfrom = Transform;
	AdjustedTransfrom.AddToTranslation(Location);

	// Absolute
	if (RotationType == ECsDebugDrawRotation::Absolute)
	{
		AdjustedTransfrom.SetRotation(Rotation.Quaternion());
	}
	// Offset
	else
	if (RotationType == ECsDebugDrawRotation::Offset)
	{
		FQuat Quat   = AdjustedTransfrom.GetRotation();
		FRotator Rot = Quat.Rotator();
		Rot			+= Rotation;
				
		AdjustedTransfrom.SetRotation(Rot.Quaternion());
	}

	FMatrix Matrix = AdjustedTransfrom.ToMatrixNoScale();

	// Draw Circle
	if (Min == 0.0f || Min == Max)
	{
		DrawDebugCircle(World, Matrix, Max, Segments, Color, false, LifeTime, 0, Thickness);
	}
	// Draws 2D Donut
	else
	{
		DrawDebug2DDonut(World, Matrix, Min, Max, 2.0f * Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawCircle

// FCsDebugDrawSphere
#pragma region

bool FCsDebugDrawSphere::CanDraw(const UObject* WorldContext) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FTransform& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform);
	}
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FTransform& Transform, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FVector& InLocation, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext))
	{
		FTransform InTransform = FTransform::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FVector& InLocation, const float& Radius) const
{
	Draw(WorldContext, InLocation, Radius, Radius);
}

void FCsDebugDrawSphere::Draw_Internal(const UObject* WorldContext, const FTransform& Transform) const
{
	Draw_Internal(WorldContext, Transform, MinRadius, MaxRadius);
}

void FCsDebugDrawSphere::Draw_Internal(const UObject* WorldContext, const FTransform& Transform, const float& InMinRadius, const float& InMaxRadius) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	const float Min = FMath::Min(InMinRadius, InMaxRadius);
	const float Max = FMath::Max(InMinRadius, InMaxRadius);

	if (Max == 0.0f)
		return;

	// Draw Sphere
	if (Min == 0.0f || Min == Max)
	{
		DrawDebugSphere(World, Transform.GetTranslation() + Location, Max, Segments, Color, false, LifeTime, 0, Thickness);
	}
	// Draw Sphere + 2D Donut
	else
	{
		DrawDebugSphere(World, Transform.GetTranslation() + Location, Max, Segments, Color, false, LifeTime, 0, Thickness);

		FTransform AdjustedTransfrom = Transform;
		AdjustedTransfrom.AddToTranslation(Location);

		// Absolute
		if (RotationType == ECsDebugDrawRotation::Absolute)
		{
			AdjustedTransfrom.SetRotation(Rotation.Quaternion());
		}
		// Offset
		else
		if (RotationType == ECsDebugDrawRotation::Offset)
		{
			FQuat Quat   = AdjustedTransfrom.GetRotation();
			FRotator Rot = Quat.Rotator();
			Rot			+= Rotation;
				
			AdjustedTransfrom.SetRotation(Rot.Quaternion());
		}

		FMatrix Matrix = AdjustedTransfrom.ToMatrixNoScale();

		DrawDebug2DDonut(World, Matrix, Min, Max, 2.0f * Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawSphere

// FCsDebugDrawPoint
#pragma region

bool FCsDebugDrawPoint::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawPoint::Draw(UWorld* World, const FVector& Location) const
{
	if (CanDraw(World))
	{
		DrawDebugSphere(World, Location + Offset, Radius, Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawPoint

// FCsDebugDrawLine
#pragma region

bool FCsDebugDrawLine::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawLine::Draw(UWorld* World, const FVector& Start, const FVector& End) const
{
	if (CanDraw(World))
	{
		DrawDebugLine(World, Start + StartOffset, End + EndOffset, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawLine

// FCsDebugDrawLineAndPoint
#pragma region

bool FCsDebugDrawLineAndPoint::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawLineAndPoint::Draw(UWorld* World, const FVector& Start, const FVector& End, const float& InLifeTime) const
{
	if (CanDraw(World))
	{
		DrawDebugLine(World, Start + StartOffset, End + EndOffset, Color, false, InLifeTime, 0, Thickness);

		DrawDebugSphere(World, End + EndOffset, Radius, Segments, Color, false, InLifeTime, 0, Thickness);
	}
}

void FCsDebugDrawLineAndPoint::Draw(UWorld* World, const FVector& Start, const FVector& End) const
{
	Draw(World, Start, End, LifeTime);
}

void FCsDebugDrawLineAndPoint::DrawOnlyLine(UWorld* World, const FVector& Start, const FVector& End) const
{
	if (CanDraw(World))
	{
		DrawDebugLine(World, Start + StartOffset, End + EndOffset, Color, false, LifeTime, 0, Thickness);
	}
}

void FCsDebugDrawLineAndPoint::DrawOnlyPoint(UWorld* World, const FVector& Location) const
{
	if (CanDraw(World))
	{
		DrawDebugSphere(World, Location + StartOffset, Radius, Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawLineAndPoint

// FCsDebugDrawString
#pragma region

bool FCsDebugDrawString::CanDraw(const UObject* WorldContext) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawString::Draw(const UObject* WorldContext, const FVector& Location, const FString& Text) const
{
	if (CanDraw(WorldContext))
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(WorldContext);

		DrawDebugString(World, Location, Text, nullptr, Color, LifeTime, bDrawShadow, FontScale);
	}
}

#pragma endregion FCsDebugDrawString

// FCsDebugDrawTraceLine
#pragma region

bool FCsDebugDrawTraceLine::CanDraw(const UObject* WorldContext) const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawTraceLine::Draw(const UObject* WorldContext, const FVector& Start, const FVector& End, const FHitResult& Hit) const
{
	if (CanDraw(WorldContext))
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(WorldContext);

		if (Hit.bBlockingHit)
		{
			DrawDebugLine(World, Start, Hit.ImpactPoint, Color, false, LifeTime, 0 , Thickness);
			DrawDebugLine(World, Hit.ImpactPoint, End, HitColor, false, LifeTime, 0, Thickness);
			DrawDebugPoint(World, Hit.ImpactPoint, HitSize, HitColor, false, LifeTime);
		}
		else
		{
			DrawDebugLine(World, Start, End, Color, false, LifeTime, 0, Thickness);
		}
	}
}

void FCsDebugDrawTraceLine::Draw(const UObject* WorldContext, const FVector& Start, const FVector& End, const bool& BlockingHit, const FVector& ImpactPoint) const
{
	FHitResult Hit;
	Hit.bBlockingHit = BlockingHit;
	Hit.ImpactPoint  = ImpactPoint;

	Draw(WorldContext, Start, End, Hit);
}

#pragma endregion FCsDebugDrawTraceLine

// FCsDebugDrawTraceBox
#pragma region

bool FCsDebugDrawTraceBox::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawTraceBox::Draw(UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Rotation, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::BoxTraceSingle(World, Start, End, HalfSize, Rotation, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

#pragma endregion FCsDebugDrawTraceBox

// FCsDebugDrawTraceSphere
#pragma region

bool FCsDebugDrawTraceSphere::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawTraceSphere::Draw(UWorld* World, const FVector& Start, const FVector& End, const float& Radius, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::SphereTraceSingle(World, Start, End, Radius, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

#pragma endregion FCsDebugDrawTraceSphere

// FCsDebugDrawTraceCapsule
#pragma region

bool FCsDebugDrawTraceCapsule::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawTraceCapsule::Draw(UWorld* World, const FVector& Start, const FVector& End, const float& Radius, const float& HalfHeight, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::CapsuleTraceSingle(World, Start, End, Radius, HalfHeight, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

#pragma endregion FCsDebugDrawTraceCapsule

// FCsDebugDrawTraceShape
#pragma region

bool FCsDebugDrawTraceShape::CanDraw(UWorld* World) const
{
	if (!World)
		return false;

	// Preview
	if (World->WorldType == EWorldType::Editor ||
		World->WorldType == EWorldType::EditorPreview)
	{
		return bEnableInPreview;
	}
	// Play
	if (World->WorldType == EWorldType::Game ||
		World->WorldType == EWorldType::PIE)
	{
		// Any
		if (PriorityInPlay == ECsDebugDrawPriority::Any)
			return bEnableInPlay || FCsCVarDrawMap::Get().IsDrawing(CVar);
		// CVar
		if (PriorityInPlay == ECsDebugDrawPriority::CVar)
			return FCsCVarDrawMap::Get().IsDrawing(CVar);
		// Flag
		if (PriorityInPlay == ECsDebugDrawPriority::Flag)
			return bEnableInPlay;
	}
	return false;
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector& Start, const FVector& End, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::LineTraceSingle(World, Start, End, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Rotation, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::BoxTraceSingle(World, Start, End, HalfSize, Rotation, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector& Start, const FVector& End, const float& Radius, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::SphereTraceSingle(World, Start, End, Radius, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector& Start, const FVector& End, const float& Radius, const float& HalfHeight, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::CapsuleTraceSingle(World, Start, End, Radius, HalfHeight, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector& Start, const FVector& End, const FCollisionShape* Shape, const FHitResult& Hit) const
{
	// Line
	if (!Shape)
	{
		Draw(World, Start, End, Hit);
	}
	else
	{
		// Line
		if (Shape->IsLine())
			Draw(World, Start, End, Hit);
		// Box
		else
		if (Shape->IsBox())
			Draw(World, Start, End, Shape->GetExtent(), FRotator::ZeroRotator, Hit);
		// Sphere
		else
		if (Shape->IsSphere())
			Draw(World, Start, End, Shape->Sphere.Radius, Hit);
		// Capsule
		else
		if (Shape->IsCapsule())
			Draw(World, Start, End, Shape->Capsule.Radius, Shape->Capsule.HalfHeight, Hit);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector& Start, const FVector& End, const FCollisionShape* Shape) const
{
	Draw(World, Start, End, Shape, NCsCollision::NHit::Default);
}

#pragma endregion FCsDebugDrawTraceShape