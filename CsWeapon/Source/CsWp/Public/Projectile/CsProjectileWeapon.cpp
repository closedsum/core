// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/CsProjectileWeapon.h"
#include "CsWp.h"

// Weapon
#include "CsWeapon.h"
// Update
#include "Managers/Time/CsUpdate.h"

UCsProjectileWeapon::UCsProjectileWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsProjectileWeapon
#pragma region

const FCsProjectileWeapon FCsProjectileWeapon::Empty;

// TCsInterfaceObject
#pragma region

void FCsProjectileWeapon::SetInterface(ICsProjectileWeapon* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetUpdate((ICsUpdate*)InInterface);
#else
		SetUpdate(dynamic_cast<ICsUpdate*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsProjectileWeapon::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsWeapon
		{
			// Interface
			if (ICsWeapon* O = Cast<ICsWeapon>(Object))
			{
				SetWeapon(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsWeapon::StaticClass()))
			{
				SetScriptWeapon();
			}
			else
			{
				checkf(false, TEXT("FCsProjectileWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()));
			}
		}
		// ICsProjectileWeapon
		{
			// Interface
			if (ICsProjectileWeapon* O = Cast<ICsProjectileWeapon>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsProjectileWeapon::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsProjectileWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsProjectileWeapon."), *(Object->GetName()));
			}
		}
		// ICsUpdate
		{
			// Interface
			if (ICsUpdate* U = Cast<ICsUpdate>(Object))
			{
				SetUpdate(U);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsUpdate::StaticClass()))
			{
				SetScriptUpdate();
			}
		}
	}
}

void FCsProjectileWeapon::Reset()
{
	Super::Reset();

	Weapon = nullptr;
	bScriptWeapon = false;

	_Update = nullptr;
	bScriptUpdate = false;

	Script_GetData_Impl.Unbind();
	Script_StartFire_Impl.Unbind();
	Script_StopFire_Impl.Unbind();
	Script_Update_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsUpdate
#pragma region

void FCsProjectileWeapon::Update(const FCsDeltaTime& DeltaTime)
{
	if (bScriptUpdate)
		Script_Update_Impl.Execute(Object, DeltaTime);
	else
		_Update->Update(DeltaTime);
}

#pragma endregion ICsUpdate

#pragma endregion FCsProjectileWeapon