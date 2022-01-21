// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectilePooled.h"
#include "CsPrj.h"

#include "Managers/Projectile/CsProjectile.h"

const FCsProjectilePooled FCsProjectilePooled::Empty;

FCsProjectilePooled::FCsProjectilePooled() :
	Super(),
	Projectile(nullptr),
	bScriptProjectile(false),
	Script_GetOwner_Impl(),
	Script_GetInstigator_Impl()
{
}

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

void FCsProjectilePooled::Reset()
{
	Super::Reset();

	Projectile = nullptr;
}

#pragma endregion TCsInterfaceObject

// ICsProjectile
#pragma region

UObject* FCsProjectilePooled::GetOwner() const
{
	if (bScript)
		return Script_GetOwner_Impl.Execute(Object);
	return Projectile->GetOwner();
}

UObject* FCsProjectilePooled::GetInstigator() const
{
	if (bScript)
		return Script_GetInstigator_Impl.Execute(Object);
	return Projectile->GetInstigator();
}

#pragma endregion ICsProjectile

void FCsProjectilePooled::SetPooledObject(const FCsPooledObject& PooledObject)
{
	SetInterface(PooledObject.GetInterface());
	SetObject(PooledObject.GetObject());

	if (PooledObject.IsScript())
		SetScript();

	Script_GetCache_Impl = PooledObject.Script_GetCache_Impl;
	Script_Allocate_Impl = PooledObject.Script_Allocate_Impl;
	Script_Update_Impl = PooledObject.Script_Update_Impl;
	Script_Deallocate_Impl = PooledObject.Script_Deallocate_Impl;

	if (bScript)
	{
		// GetCache
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}