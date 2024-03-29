// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sense/CsSenseInfo.h"
#include "CsSense.h"

#include "Managers/Sense/CsSensingObject.h"

// ICsSenseInfo
#pragma region

const FCsSensedObject& FCsSenseInfo::GetObject() const
{
	return Object;
}

void FCsSenseInfo::SetObject(ICsSensedObject* InSenseObject, UObject* InObject)
{
	Object.SetInterface(InSenseObject);
	Object.SetObject(InObject);
}

#pragma endregion ICsSenseInfo

void FCsSenseInfo::Update(const float& CurrentTime, ICsSensingObject* SensingObject)
{
	ICsSensedObject* SensedObject = Object.GetInterface();

	for (TPair<FCsSenseInfoKey, FCsSenseInfoValue>& Pair : Data)
	{
		const FCsSenseInfoKey& Key = Pair.Key;
		FCsSenseInfoValue& Value   = Pair.Value;

		FVector3f& MeToObject = Value.MeToObject;
		float& Distance		= Value.Distance;
		float& DistanceSq	= Value.DistanceSq;
		float& DistanceXY	= Value.DistanceXY;
		float& DistanceSqXY = Value.DistanceSqXY;
		FVector3f& Direction	= Value.Direction;
		FVector3f& DirectionXY = Value.DirectionXY;
		float& Dot			= Value.Dot;
		float& DotXY		= Value.DotXY;

		const FVector3f FromLocation = SensingObject->GetCustomLocation(Key.From);
		const FVector3f ToLocation   = SensedObject->GetCustomLocation(Key.To);

		MeToObject = ToLocation - FromLocation;
		// Distance
		DistanceSqXY = MeToObject.SizeSquared2D();
		DistanceSq	 = DistanceSqXY + FMath::Square(MeToObject.Z);
		Distance	 = FMath::Sqrt(DistanceSq);
		DistanceXY   = FMath::Sqrt(DistanceSqXY);
		// Direction
		Direction = MeToObject;
		{
			if (DistanceSq == 1.f)
			{
				// Do Nothing
			}
			else 
			if (DistanceSq < SMALL_NUMBER)
			{
				Direction = FVector3f::ZeroVector;
			}
			else
			{
				const float Scale = FMath::InvSqrt(DistanceSq);
				Direction *= Scale;
			}
		}
		DirectionXY   = MeToObject;
		DirectionXY.Z = 0.0f;
		{
			if (DistanceSqXY == 1.f)
			{
				// Do Nothing
			}
			else 
			if (DistanceSqXY < SMALL_NUMBER)
			{
				DirectionXY = FVector3f::ZeroVector;
			}
			else
			{
				const float Scale = FMath::InvSqrt(DistanceSqXY);
				DirectionXY *= Scale;
			}
		}
		// Dot
		const FVector3f DotDirection = SensingObject->GetCustomDirection(Key.Direction);

		if (DotDirection != FVector3f::ZeroVector)
		{
			Dot   = FVector3f::DotProduct(DotDirection, Direction);
			DotXY = DotDirection.X * Direction.X + DotDirection.Y * Direction.Y;
		}
		else
		{
			Dot   = 0.0f;
			DotXY = 0.0f;
		}
	}
}