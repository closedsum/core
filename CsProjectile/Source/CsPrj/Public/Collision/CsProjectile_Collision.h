// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsProjectile_Collision.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile_Collision : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UPrimitiveComponent;
class AActor;

class CSPRJ_API ICsProjectile_Collision
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) = 0;
};