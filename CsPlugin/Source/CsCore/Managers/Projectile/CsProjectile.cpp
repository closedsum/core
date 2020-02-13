// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectile.h"
#include "CsCore.h"

UCsProjectile::UCsProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsProjectilePooled
#pragma region

const FCsProjectilePooled FCsProjectilePooled::Empty;

// TCsInterfaceObject
#pragma region

void FCsProjectilePooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetProjectile((ICsProjectile*)InInterface);
#else
		SetProjectile(dynamic_cast<ICsProjectile*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsProjectilePooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		UClass* Class = Object->GetClass();

		// ICsProjectile
		{
			// Interface
			if (ICsProjectile* O = Cast<ICsProjectile>(Object))
			{
				SetProjectile(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsProjectile::StaticClass()))
			{
				SetScriptProjectile();
			}
			else
			{
				checkf(false, TEXT("FCsProjectilePooled:SetObject: Object: %s with Class; %s does NOT implement the interface: ICsProjectile."), *(Object->GetName()));
			}
		}
	}
}
	
#pragma endregion TCsInterfaceObject

#pragma endregion FCsProjectilePooled