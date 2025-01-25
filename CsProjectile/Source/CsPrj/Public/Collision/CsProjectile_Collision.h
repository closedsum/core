// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Engine/HitResult.h"

#include "CsProjectile_Collision.generated.h"

class UPrimitiveComponent;
class AActor;

namespace NCsProjectile
{
	namespace NCollision
	{
		namespace NHit
		{
			struct CSPRJ_API FResult
			{
				UPrimitiveComponent* MyComponent;

				AActor* OtherActor;

				UPrimitiveComponent* OtherComponent;

				FVector3f NormalImpulse;

				FHitResult Hit;

				int32 OtherType;

				int32 OtherID;

				FResult() :
					MyComponent(nullptr),
					OtherActor(nullptr),
					OtherComponent(nullptr),
					NormalImpulse(0.0f),
					Hit(),
					OtherType(INDEX_NONE),
					OtherID(INDEX_NONE)
				{
				}

				FORCEINLINE UPrimitiveComponent* GetMyComponent() const { return MyComponent; }
				FORCEINLINE AActor* GetOtherActor() const { return OtherActor; }
				FORCEINLINE UPrimitiveComponent* GetOtherComponent() const { return OtherComponent; }
			};
		}
	}
}

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

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ResultType = NCsProjectile::NCollision::NHit::FResult;
	};

public:

	virtual void Hit(const _::ResultType& Result) = 0;
};