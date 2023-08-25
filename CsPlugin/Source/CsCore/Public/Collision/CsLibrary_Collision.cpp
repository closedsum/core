// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Collision/CsLibrary_Collision.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "PhysicsEngine/PhysicsSettings.h"
// Component
#include "Components/PrimitiveComponent.h"
// Physics
#include "PhysicsEngine/BodySetup.h"

#if WITH_EDITOR
#include "Kismet/GameplayStatics.h" // TODO: FIX
#endif // #if WITH_EDITOR

namespace NCsCollision
{
	bool FLibrary::FindUVChecked(const FString& Context, const FHitResult& Hit, const int32& UVChannel, FVector2f& OutUV)
	{
		checkf(UPhysicsSettings::Get()->bSupportUVFromHitResults, TEXT("%s: 'Support UV From Hit Results' is NOT enabled in project settings. This is required for finding UV for collision results."), *Context);

		UPrimitiveComponent* Component = Hit.Component.Get();

		CS_IS_PTR_NULL_CHECKED(Component)

		UBodySetup* BodySetup = Component->GetBodySetup();

		CS_IS_PTR_NULL_CHECKED(BodySetup)

		const FVector3d LocalHitPos = Component->GetComponentToWorld().InverseTransformPosition(Hit.Location);

		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(UVChannel, 0)
		
		typedef NCsMath::FLibrary MathLibrary;

	#if WITH_EDITOR
		FVector2d UV;
		const bool Result = UGameplayStatics::FindCollisionUV(Hit, UVChannel, UV);
		OutUV = MathLibrary::Convert(UV);
		return Result;
	#else
		FVector2d UV;
		const bool Result = BodySetup->CalcUVAtLocation(LocalHitPos, Hit.FaceIndex, UVChannel, UV);
		OutUV = MathLibrary::Convert(UV);
		return Result;
	#endif // #if WITH_EDITOR
	}

	// HitResult
	#pragma region

	FVector3f FLibrary::GetLocation(const FHitResult& Hit)
	{
		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Hit.Location);
	}

	FRotator3f FLibrary::GetImpactRotation(const FHitResult& Hit)
	{
		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Hit.ImpactNormal.Rotation());
	}

	FQuat4f FLibrary::GetImpactQuat(const FHitResult& Hit)
	{
		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Hit.ImpactNormal.ToOrientationQuat());
	}

	#pragma endregion HitResult
}