// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsProjectile.h"
#include "CsPrj.h"

UCsProjectile::UCsProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsProjectile
#pragma region

const FCsProjectile FCsProjectile::Empty;

	// TCsInterfaceObject
#pragma region

void FCsProjectile::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsProjectile
		{
			// Interface
			if (ICsProjectile* O = Cast<ICsProjectile>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsProjectile::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsProjectile:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsProjectile."), *(Object->GetName()));
			}
		}
	}
}

#pragma endregion TCsInterfaceObject

	// ICsProjectile
#pragma region

UObject* FCsProjectile::GetOwner()
{
	if (bScript)
		return Script_GetOwner_Impl.Execute(Object);
	return Interface->GetOwner();
}

UObject* FCsProjectile::GetInstigator()
{
	if (bScript)
		return Script_GetInstigator_Impl.Execute(Object);
	return Interface->GetInstigator();
}

#pragma endregion ICsProjectile

#pragma endregion FCsWeapon