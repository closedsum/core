// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Collision/CsLibrary_Collision.h"
#include "CsCore.h"

// Library
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
		return UGameplayStatics::FindCollisionUV(Hit, UVChannel, OutUV);
	#else
		return BodySetup->CalcUVAtLocation(LocalHitPos, Hit.FaceIndex, UVChannel, OutUV);
	#endif // #if WITH_EDITOR
	}
}