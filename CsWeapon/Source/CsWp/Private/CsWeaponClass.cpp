// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsWeaponClass.h"

// Weapon
#include "CsWeapon.h"

const FCsWeaponClass FCsWeaponClass::Empty;

FCsWeaponClass::FCsWeaponClass() :
	Super()
{
}

// TCsInterfaceObject
#pragma region

void FCsWeaponClass::SetInterface(ICsWeapon* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT("FCsWeaponClass::SetInterface: This is NOT supported. InInterface must be a UObject."))
	}
}

void FCsWeaponClass::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsWeapon
		{
			// Interface
			if (ICsWeapon* O = Cast<ICsWeapon>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsWeapon::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsWeaponClass:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()), *(Object->GetClass()->GetName()));
			}
		}
	}
}

#pragma endregion TCsInterfaceObject