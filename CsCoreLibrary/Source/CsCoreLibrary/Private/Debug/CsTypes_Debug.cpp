// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Debug/CsTypes_Debug.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Debug/CsLibrary_Debug_Draw.h"
#include "Library/CsLibrary_Math.h"
// Collision
#include "CollisionShape.h"
// Engine
#include "GameFramework/Actor.h"
// World
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Debug)

// DebugDrawPriority
#pragma region

namespace NCsDebugDrawPriority
{
	namespace Ref
	{
		typedef EMCsDebugDrawPriority EnumMapType;

		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(Any);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(CVar);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(Flag);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDebugDrawPriority_MAX, "MAX");
	}

	CSCORELIBRARY_API const uint8 MAX = (uint8)Type::ECsDebugDrawPriority_MAX;
}

#pragma endregion DebugDrawPriority

// DebugDrawFrequency
#pragma region

namespace NCsDebugDrawFrequency
{
	namespace Ref
	{
		typedef EMCsDebugDrawFrequency EnumMapType;

		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(Once);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(Update);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDebugDrawFrequency_MAX, "MAX");
	}

	CSCORELIBRARY_API const uint8 MAX = (uint8)Type::ECsDebugDrawFrequency_MAX;
}

#pragma endregion DebugDrawFrequency

// DebugDrawRotation
#pragma region

namespace NCsDebugDrawRotation
{
	namespace Ref
	{
		typedef EMCsDebugDrawRotation EnumMapType;

		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(Absolute);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP(Offset);
		CSCORELIBRARY_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDebugDrawRotation_MAX, "MAX");
	}

	CSCORELIBRARY_API const uint8 MAX = (uint8)Type::ECsDebugDrawRotation_MAX;
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

void FCsDebugDrawBox::Draw(const UObject* WorldContext, const FTransform3f& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform, FVector3f::ZeroVector);
	}
}

void FCsDebugDrawBox::Draw(const UObject* WorldContext, const FTransform3f& Transform, const FVector3f& InExtent) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform, InExtent);
	}
}

void FCsDebugDrawBox::Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform, const FVector3f& InExtent) const
{
	typedef NCsWorld::FLibrary WorldLibrary;
	typedef NCsDebug::NDraw::FLibrary DrawLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (bSolid)
		DrawLibrary::DrawDebugSolidBox(World, Transform.GetTranslation() + Location, InExtent + Extent, Rotation.Quaternion() * Transform.GetRotation(), Color, false, LifeTime, 0);
	else
		DrawLibrary::DrawDebugBox(World, Transform.GetTranslation() + Location, InExtent + Extent, Rotation.Quaternion() * Transform.GetRotation(), Color, false, LifeTime, 0, Thickness);
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

void FCsDebugDrawCircle::Draw(const UObject* WorldContext, const FTransform3f& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform);
	}
}

void FCsDebugDrawCircle::Draw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar, const FVector3f& InLocation, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext, OtherCVar))
	{
		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext))
	{
		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::DrawAtLocation(AActor* Actor, const FECsCVarDraw& OtherCVar, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(Actor, OtherCVar))
	{
		typedef NCsMath::FLibrary MathLibrary;

		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(MathLibrary::Convert(Actor->GetActorLocation()));

		Draw_Internal(Actor, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::DrawAtLocation(AActor* Actor, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(Actor))
	{
		typedef NCsMath::FLibrary MathLibrary;

		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(MathLibrary::Convert(Actor->GetActorLocation()));

		Draw_Internal(Actor, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawCircle::DrawAtLocation(AActor* Actor, const float& Radius) const
{
	DrawAtLocation(Actor, Radius, Radius);
}

void FCsDebugDrawCircle::Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform) const
{
	Draw_Internal(WorldContext, Transform, MinRadius, MaxRadius);
}

void FCsDebugDrawCircle::Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform, const float& InMinRadius, const float& InMaxRadius) const
{
	typedef NCsWorld::FLibrary WorldLibrary;
	typedef NCsDebug::NDraw::FLibrary DrawLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	const float Min = FMath::Min(InMinRadius, InMaxRadius);
	const float Max = FMath::Max(InMinRadius, InMaxRadius);

	if (Max == 0.0f)
		return;

	FTransform3f AdjustedTransfrom = Transform;
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
		FQuat4f Quat   = AdjustedTransfrom.GetRotation();
		FRotator3f Rot = Quat.Rotator();
		Rot			+= Rotation;
				
		AdjustedTransfrom.SetRotation(Rot.Quaternion());
	}

	FMatrix44f Matrix = AdjustedTransfrom.ToMatrixNoScale();

	// Draw Circle
	if (Min == 0.0f || Min == Max)
	{
		DrawLibrary::DrawDebugCircle(World, Matrix, Max, Segments, Color, false, LifeTime, 0, Thickness);
	}
	// Draws 2D Donut
	else
	{
		DrawLibrary::DrawDebug2DDonut(World, Matrix, Min, Max, 2.0f * Segments, Color, false, LifeTime, 0, Thickness);
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

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FTransform3f& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform);
	}
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FTransform3f& Transform, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Transform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& InMinRadius, const float& InMaxRadius) const
{
	if (CanDraw(WorldContext))
	{
		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InTransform, InMinRadius, InMaxRadius);
	}
}

void FCsDebugDrawSphere::Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& Radius) const
{
	Draw(WorldContext, InLocation, Radius, Radius);
}

void FCsDebugDrawSphere::Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform) const
{
	Draw_Internal(WorldContext, Transform, MinRadius, MaxRadius);
}

void FCsDebugDrawSphere::Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform, const float& InMinRadius, const float& InMaxRadius) const
{
	typedef NCsWorld::FLibrary WorldLibrary;
	typedef NCsDebug::NDraw::FLibrary DrawLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	const float Min = FMath::Min(InMinRadius, InMaxRadius);
	const float Max = FMath::Max(InMinRadius, InMaxRadius);

	if (Max == 0.0f)
		return;

	// Draw Sphere
	if (Min == 0.0f || Min == Max)
	{
		DrawLibrary::DrawDebugSphere(World, Transform.GetTranslation() + Location, Max, Segments, Color, false, LifeTime, 0, Thickness);
	}
	// Draw Sphere + 2D Donut
	else
	{
		DrawLibrary::DrawDebugSphere(World, Transform.GetTranslation() + Location, Max, Segments, Color, false, LifeTime, 0, Thickness);

		FTransform3f AdjustedTransfrom = Transform;
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
			FQuat4f Quat   = AdjustedTransfrom.GetRotation();
			FRotator3f Rot = Quat.Rotator();
			Rot			+= Rotation;
				
			AdjustedTransfrom.SetRotation(Rot.Quaternion());
		}

		FMatrix44f Matrix = AdjustedTransfrom.ToMatrixNoScale();

		DrawLibrary::DrawDebug2DDonut(World, Matrix, Min, Max, 2.0f * Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawSphere

// FCsDebugDrawPie
#pragma region

bool FCsDebugDrawPie::CanDraw(const UObject* WorldContext) const
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

bool FCsDebugDrawPie::CanDraw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar) const
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

void FCsDebugDrawPie::Draw(const UObject* WorldContext, const FTransform3f& Transform) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, Angle, Transform);
	}
}

void FCsDebugDrawPie::Draw(const UObject* WorldContext, const float& InAngle, const FTransform3f& Transform, const float& InRadius) const
{
	if (CanDraw(WorldContext))
	{
		Draw_Internal(WorldContext, InAngle, Transform, InRadius);
	}
}

void FCsDebugDrawPie::Draw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar, const float& InAngle, const FVector3f& InLocation, const float& InRadius) const
{
	if (CanDraw(WorldContext, OtherCVar))
	{
		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, InAngle, InTransform, InRadius);
	}
}

void FCsDebugDrawPie::Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& InRadius) const
{
	if (CanDraw(WorldContext))
	{
		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(InLocation);

		Draw_Internal(WorldContext, Angle, InTransform, InRadius);
	}
}

void FCsDebugDrawPie::DrawAtLocation(AActor* Actor, const FECsCVarDraw& OtherCVar, const float& InRadius) const
{
	if (CanDraw(Actor, OtherCVar))
	{
		typedef NCsMath::FLibrary MathLibrary;

		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(MathLibrary::Convert(Actor->GetActorLocation()));

		Draw_Internal(Actor, Angle, InTransform, InRadius);
	}
}

void FCsDebugDrawPie::DrawAtLocation(AActor* Actor, const float& InRadius) const
{
	if (CanDraw(Actor))
	{
		typedef NCsMath::FLibrary MathLibrary;

		FTransform3f InTransform = FTransform3f::Identity;
		InTransform.SetLocation(MathLibrary::Convert(Actor->GetActorLocation()));

		Draw_Internal(Actor, Angle, InTransform, InRadius);
	}
}

void FCsDebugDrawPie::Draw_Internal(const UObject* WorldContext, const float& InAngle, const FTransform3f& Transform) const
{
	Draw_Internal(WorldContext, InAngle, Transform, Radius);
}

void FCsDebugDrawPie::Draw_Internal(const UObject* WorldContext, const float& InAngle, const FTransform3f& Transform, const float& InRadius) const
{
	typedef NCsWorld::FLibrary WorldLibrary;
	typedef NCsDebug::NDraw::FLibrary DrawLibrary;

	UWorld* World = WorldLibrary::GetSafe(WorldContext);

	if (InAngle == 0.0f)
		return;

	if (InRadius == 0.0f)
		return;

	FTransform3f AdjustedTransfrom = Transform;
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
		FQuat4f Quat   = AdjustedTransfrom.GetRotation();
		FRotator3f Rot = Quat.Rotator();
		Rot			+= Rotation;
				
		AdjustedTransfrom.SetRotation(Rot.Quaternion());
	}

	const FVector3f Origin	= AdjustedTransfrom.GetTranslation();
	const FVector3f Direction = AdjustedTransfrom.GetRotation().Vector();
	
	DrawLibrary::DrawDebugCone(World, Origin, Direction, InRadius, FMath::DegreesToRadians(InAngle), FMath::DegreesToRadians(1.0f), Segments, Color, false, LifeTime, 0, Thickness);
}

#pragma endregion FCsDebugDrawCircle

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

void FCsDebugDrawPoint::Draw(UWorld* World, const FVector3f& Location) const
{
	if (CanDraw(World))
	{
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		DrawLibrary::DrawDebugSphere(World, Location + Offset, Radius, Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawPoint

// FCsDebugDrawLine
#pragma region

bool FCsDebugDrawLine::CanDraw(const UObject* WorldContext) const
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

void FCsDebugDrawLine::Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& End) const
{
	if (CanDraw(WorldContext))
	{
		typedef NCsWorld::FLibrary WorldLibrary;
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		UWorld* World = WorldLibrary::GetSafe(WorldContext);

		DrawLibrary::DrawDebugLine(World, Start + StartOffset, End + EndOffset, Color, false, LifeTime, 0, Thickness);
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

void FCsDebugDrawLineAndPoint::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& InLifeTime) const
{
	if (CanDraw(World))
	{
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		DrawLibrary::DrawDebugLine(World, Start + StartOffset, End + EndOffset, Color, false, InLifeTime, 0, Thickness);
		DrawLibrary::DrawDebugSphere(World, End + EndOffset, Radius, Segments, Color, false, InLifeTime, 0, Thickness);
	}
}

void FCsDebugDrawLineAndPoint::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End) const
{
	Draw(World, Start, End, LifeTime);
}

void FCsDebugDrawLineAndPoint::DrawOnlyLine(UWorld* World, const FVector3f& Start, const FVector3f& End) const
{
	if (CanDraw(World))
	{
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		DrawLibrary::DrawDebugLine(World, Start + StartOffset, End + EndOffset, Color, false, LifeTime, 0, Thickness);
	}
}

void FCsDebugDrawLineAndPoint::DrawOnlyPoint(UWorld* World, const FVector3f& Location) const
{
	if (CanDraw(World))
	{
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		DrawLibrary::DrawDebugSphere(World, Location + StartOffset, Radius, Segments, Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawLineAndPoint

// FCsDebugDrawDirectionArrow
#pragma region

bool FCsDebugDrawDirectionArrow::CanDraw(const UObject* WorldContext) const
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

void FCsDebugDrawDirectionArrow::Draw(const UObject* WorldContext, const FVector3f& Start, const FRotator3f& InRotation) const
{
	Draw(WorldContext, Start, InRotation, Length);
}

void FCsDebugDrawDirectionArrow::Draw(const UObject* WorldContext, const FVector3f& Start, const FRotator3f& InRotation, const float& InLength) const
{
	if (CanDraw(WorldContext))
	{
		typedef NCsWorld::FLibrary WorldLibrary;
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		UWorld* World = WorldLibrary::GetSafe(WorldContext);

		const FVector3f NewStart		= Start + StartOffset;
		const FRotator3f NewRotation  = RotationType == ECsDebugDrawRotation::Absolute ? InRotation : Rotation + InRotation;
		const FVector3f Direction		= NewRotation.Vector();
		const FVector3f End			= NewStart + (InLength * Direction) + EndOffset;

		DrawLibrary::DrawDebugDirectionalArrow(World, NewStart, End, Size, Color, false, LifeTime, 0, Thickness);
	}
}

void FCsDebugDrawDirectionArrow::Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& Direction, const float& InLength) const
{
	Draw(WorldContext, Start, Direction.Rotation(), InLength);
}

void FCsDebugDrawDirectionArrow::Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& Direction) const
{
	Draw(WorldContext, Start, Direction.Rotation(), Length);
}

#pragma endregion FCsDebugDrawDirectionArrow

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

void FCsDebugDrawString::Draw(const UObject* WorldContext, const FVector3f& Location, const FString& Text) const
{
	if (CanDraw(WorldContext))
	{
		typedef NCsWorld::FLibrary WorldLibrary;
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;

		UWorld* World = WorldLibrary::GetSafe(WorldContext);

		DrawLibrary::DrawDebugString(World, Location, Text, nullptr, Color, LifeTime, bDrawShadow, FontScale);
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

void FCsDebugDrawTraceLine::Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& End, const FHitResult& Hit) const
{
	if (CanDraw(WorldContext))
	{
		typedef NCsWorld::FLibrary WorldLibrary;
		typedef NCsDebug::NDraw::FLibrary DrawLibrary;
		typedef NCsMath::FLibrary MathLibrary;

		UWorld* World = WorldLibrary::GetSafe(WorldContext);

		if (Hit.bBlockingHit)
		{
			const FVector3f ImpactPoint = MathLibrary::Convert(Hit.ImpactPoint);

			DrawLibrary::DrawDebugLine(World, Start, ImpactPoint, Color, false, LifeTime, 0 , Thickness);
			DrawLibrary::DrawDebugLine(World, ImpactPoint, End, HitColor, false, LifeTime, 0, Thickness);
			DrawLibrary::DrawDebugPoint(World, ImpactPoint, HitSize, HitColor, false, LifeTime);
		}
		else
		{
			DrawLibrary::DrawDebugLine(World, Start, End, Color, false, LifeTime, 0, Thickness);
		}
	}
}

void FCsDebugDrawTraceLine::Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& End, const bool& BlockingHit, const FVector3f& ImpactPoint) const
{
	typedef NCsMath::FLibrary MathLibrary;

	FHitResult Hit;
	Hit.bBlockingHit = BlockingHit;
	Hit.ImpactPoint  = MathLibrary::Convert(ImpactPoint);

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

void FCsDebugDrawTraceBox::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f& HalfSize, const FRotator3f& Rotation, const FHitResult& Hit) const
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

void FCsDebugDrawTraceSphere::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const FHitResult& Hit) const
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

void FCsDebugDrawTraceCapsule::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const float& HalfHeight, const FHitResult& Hit) const
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

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::LineTraceSingle(World, Start, End, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f& HalfSize, const FRotator3f& Rotation, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::BoxTraceSingle(World, Start, End, HalfSize, Rotation, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::SphereTraceSingle(World, Start, End, Radius, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const float& HalfHeight, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::CapsuleTraceSingle(World, Start, End, Radius, HalfHeight, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
}

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FCollisionShape* Shape, const FHitResult& Hit) const
{
	// Line
	if (!Shape)
	{
		Draw(World, Start, End, Hit);
	}
	else
	{
		typedef NCsMath::FLibrary MathLibrary;

		// Line
		if (Shape->IsLine())
			Draw(World, Start, End, Hit);
		// Box
		else
		if (Shape->IsBox())
			Draw(World, Start, End, MathLibrary::Convert(Shape->GetExtent()), FRotator3f::ZeroRotator, Hit);
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

void FCsDebugDrawTraceShape::Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FCollisionShape* Shape) const
{
	Draw(World, Start, End, Shape, NCsCollision::NHit::Default);
}

#pragma endregion FCsDebugDrawTraceShape