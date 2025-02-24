// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Collision/CsLibrary_Collision.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "PhysicsEngine/PhysicsSettings.h"
// Component
#include "Components/PrimitiveComponent.h"
// Physics
#include "PhysicsEngine/BodySetup.h"
// Collision
#include "Engine/CollisionProfile.h"

#if WITH_EDITOR
#include "Kismet/GameplayStatics.h" // TODO: FIX
#endif // #if WITH_EDITOR

namespace NCsCollision
{
	bool FLibrary::FindUVChecked(const FString& Context, const FHitResult& Hit, const int32& UVChannel, FVector2D& OutUV)
	{
		checkf(UPhysicsSettings::Get()->bSupportUVFromHitResults, TEXT("%s: 'Support UV From Hit Results' is NOT enabled in project settings. This is required for finding UV for collision results."), *Context);

		UPrimitiveComponent* Component = Hit.Component.Get();

		CS_IS_PTR_NULL_CHECKED(Component)

		UBodySetup* BodySetup = Component->GetBodySetup();

		CS_IS_PTR_NULL_CHECKED(BodySetup)

		const FVector LocalHitPos = Component->GetComponentToWorld().InverseTransformPosition(Hit.Location);

		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(UVChannel, 0)

	#if WITH_EDITOR
		const bool Result = UGameplayStatics::FindCollisionUV(Hit, UVChannel, OutUV);
		return Result;
	#else
		const bool Result = BodySetup->CalcUVAtLocation(LocalHitPos, Hit.FaceIndex, UVChannel, OutUV);
		return Result;
	#endif // #if WITH_EDITOR
	}

	bool FLibrary::FindUV2fChecked(const FString& Context, const FHitResult& Hit, const int32& UVChannel, FVector2f& OutUV)
	{
		checkf(UPhysicsSettings::Get()->bSupportUVFromHitResults, TEXT("%s: 'Support UV From Hit Results' is NOT enabled in project settings. This is required for finding UV for collision results."), *Context);

		UPrimitiveComponent* Component = Hit.Component.Get();

		CS_IS_PTR_NULL_CHECKED(Component)

		UBodySetup* BodySetup = Component->GetBodySetup();

		CS_IS_PTR_NULL_CHECKED(BodySetup)

		const FVector LocalHitPos = Component->GetComponentToWorld().InverseTransformPosition(Hit.Location);

		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(UVChannel, 0)

	#if WITH_EDITOR
		FVector2D UV;
		const bool Result = UGameplayStatics::FindCollisionUV(Hit, UVChannel, UV);
		OutUV = CsMathLibrary::Convert(UV);
		return Result;
	#else
		FVector2D UV;
		const bool Result = BodySetup->CalcUVAtLocation(LocalHitPos, Hit.FaceIndex, UVChannel, UV);
		OutUV = CsMathLibrary::Convert(UV);
		return Result;
	#endif // #if WITH_EDITOR
	}

	// HitResult
	#pragma region

	FVector3f FLibrary::GetLocation3f(const FHitResult& Hit)
	{
		return CsMathLibrary::Convert(Hit.Location);
	}

	FRotator3f FLibrary::GetImpactRotation3f(const FHitResult& Hit)
	{
		return CsMathLibrary::Convert(Hit.ImpactNormal.Rotation());
	}

	FQuat4f FLibrary::GetImpactQuat3f(const FHitResult& Hit)
	{
		return CsMathLibrary::Convert(Hit.ImpactNormal.ToOrientationQuat());
	}

	#pragma endregion HitResult

	namespace NProfile
	{
		bool FLibrary::IsValidChecked(const FString& Context, const FName& Name)
		{
			CS_IS_NAME_NONE_CHECKED(Name)

			UCollisionProfile* Settings = UCollisionProfile::Get();

			checkf(Settings, TEXT("%s: Failed to Get CollisionProfile settings."), *Context);

			static TArray<TSharedPtr<FName>> Names;
			Names.Reset(Names.Max());

			Settings->GetProfileNames(Names);

			bool Found = false;

			for (const TSharedPtr<FName>& N : Names)
			{
				if (*N == Name)
				{
					Found = true;
					break;
				}
			}

			checkf(Found, TEXT("%s: Failed to find a Collision Profile with Name: %s."), *Context, *(Name.ToString()));
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const FName& Name, void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/)
		{
			CS_IS_NAME_NONE_CHECKED(Name)

			UCollisionProfile* Settings = UCollisionProfile::Get();

			if (!Settings)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to Get CollisionProfile settings."), *Context));
				return false;
			}

			static TArray<TSharedPtr<FName>> Names;
			Names.Reset(Names.Max());

			Settings->GetProfileNames(Names);

			bool Found = false;

			for (const TSharedPtr<FName>& N : Names)
			{
				if (*N == Name)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find a Collision Profile with Name: %s."), *Context, *(Name.ToString())));
				return false;
			}
			return true;
		}
	}
}