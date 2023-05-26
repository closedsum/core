// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Beam/ICsBeam.h"
#include "CsBeam.h"

UCsBeam::UCsBeam(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsBeam
#pragma region

const FCsBeam FCsBeam::Empty;

	// TCsInterfaceObject
#pragma region

void FCsBeam::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsBeam
		{
			// Interface
			if (ICsBeam* O = Cast<ICsBeam>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsBeam::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsBeam:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsBeam."), *(Object->GetName()));
			}
		}
	}
}

#pragma endregion TCsInterfaceObject

	// ICsBeam
#pragma region

UObject* FCsBeam::GetOwner()
{
	if (bScript)
		return Script_GetOwner_Impl.Execute(Object);
	return Interface->GetOwner();
}

UObject* FCsBeam::GetInstigator()
{
	if (bScript)
		return Script_GetInstigator_Impl.Execute(Object);
	return Interface->GetInstigator();
}

#pragma endregion ICsBeam

#pragma endregion FCsWeapon