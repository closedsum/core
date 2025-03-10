// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/ICsBeam.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ICsBeam)

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
				checkf(false, TEXT("FCsBeam:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsBeam."), *(Object->GetName()), *(Object->GetClass()->GetName()));
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