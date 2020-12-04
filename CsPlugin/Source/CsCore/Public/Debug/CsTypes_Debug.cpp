// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Debug/CsTypes_Debug.h"

// Types
#include "Types/CsTypes_Collision.h"
// Library
#include "Debug/CsLibrary_Debug_Draw.h"
// Collision
#include "CollisionShape.h"
// World
#include "Engine/World.h"

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

bool FCsDebugDrawBox::CanDraw(UWorld* World) const
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

void FCsDebugDrawBox::Draw(UWorld* World, const FTransform& Transform) const
{
	if (CanDraw(World))
	{
		if (bSolid)
			DrawDebugSolidBox(World, Transform.GetTranslation() + Location, Extent, Rotation.Quaternion(), Color, false, LifeTime, 0);
		else
			DrawDebugBox(World, Transform.GetTranslation() + Location, Extent, Rotation.Quaternion(), Color, false, LifeTime, 0, Thickness);
	}
}

#pragma endregion FCsDebugDrawBox

// FCsDebugDrawCircle
#pragma region

bool FCsDebugDrawCircle::CanDraw(UWorld* World) const
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

void FCsDebugDrawCircle::Draw(UWorld* World, const FTransform& Transform) const
{
	if (CanDraw(World))
	{
		const float Min = FMath::Min(MinRadius, MaxRadius);
		const float Max = FMath::Max(MinRadius, MaxRadius);

		if (Max == 0.0f)
			return;

		// Draw Circle
		if (Min == 0.0f || Min == Max)
		{
			DrawDebugCircle(World, Transform.GetTranslation() + Location, Max, Segments, Color, false, LifeTime, 0, Thickness);
		}
		// Draws 2D Donut
		else
		{
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
}

#pragma endregion FCsDebugDrawCircle

// FCsDebugDrawSphere
#pragma region

bool FCsDebugDrawSphere::CanDraw(UWorld* World) const
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

void FCsDebugDrawSphere::Draw(UWorld* World, const FTransform& Transform) const
{
	if (CanDraw(World))
	{
		const float Min = FMath::Min(MinRadius, MaxRadius);
		const float Max = FMath::Max(MinRadius, MaxRadius);

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

// FCsDebugDrawTraceLine
#pragma region

bool FCsDebugDrawTraceLine::CanDraw(UWorld* World) const
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

void FCsDebugDrawTraceLine::Draw(UWorld* World, const FVector& Start, const FVector& End, const FHitResult& Hit) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::LineTraceSingle(World, Start, End, EDrawDebugTrace::ForDuration, Hit.bBlockingHit, Hit, Color, HitColor, LifeTime);
	}
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

// FCsDebugDrawString
#pragma region

bool FCsDebugDrawString::CanDraw(UWorld* World) const
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

void FCsDebugDrawString::Draw(UWorld* World, const FVector& Location, const FString& Text) const
{
	if (CanDraw(World))
	{
		NCsDebug::NDraw::FLibrary::String(World, Location + LocationOffset, Text, nullptr, Color, LifeTime, bDropShadow, FontScale);
	}
}

#pragma endregion FCsDebugDrawString