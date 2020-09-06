// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Debug/CsTypes_Debug.h"

// World
#include "Engine/World.h"

// DebugDrawPriority
#pragma region

namespace NCsDebugDrawPriority
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsDebugDrawPriority, Any);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsDebugDrawPriority, CVar);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsDebugDrawPriority, Flag);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDebugDrawPriority, ECsDebugDrawPriority_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDebugDrawPriority_MAX;
}

#pragma endregion DebugDrawPriority

// DebugDrawRotation
#pragma region

namespace NCsDebugDrawRotation
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsDebugDrawRotation, Absolute);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsDebugDrawRotation, Offset);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDebugDrawRotation, ECsDebugDrawRotation_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDebugDrawRotation_MAX;
}

#pragma endregion DebugDrawRotation

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

void FCsDebugDrawCircle::Draw(UWorld* World, const FTransform& Transform)
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

void FCsDebugDrawSphere::Draw(UWorld* World, const FTransform& Transform)
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