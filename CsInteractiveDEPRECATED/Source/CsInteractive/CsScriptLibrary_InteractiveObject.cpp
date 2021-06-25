// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.

#include "CsScriptLibrary_InteractiveObject.h"
#include "CsInteractive.h"

// Types
#include "Managers/Params/CsTypes_Manager_InteractiveObject_Params.h"
// Library
#include "Library/Script/CsScriptLibrary_Common.h"
// Interactive
#include "CsInteractiveObject.h"
#include "CsScriptInteractiveObject.h"
// Game
#include "Engine/GameInstance.h"

// Cached
#pragma region

namespace NCsScriptLibraryInteractiveObject
{
	namespace Str
	{
		const FString Hold = TEXT("UCsScriptLibrary_InteractiveObject::Hold");
	}
}

#pragma endregion Cached

UCsScriptLibrary_InteractiveObject::UCsScriptLibrary_InteractiveObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCsScriptLibrary_InteractiveObject::Freeze(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Freeze();
	}
}

void UCsScriptLibrary_InteractiveObject::UnFreeze(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->UnFreeze();
	}
}

void UCsScriptLibrary_InteractiveObject::Hold(UObject* Target, const FCsScriptInteractiveObjectHoldParams& Params)
{
	if (Target)
	{
		UClass* Class = Target->GetClass();

		// Interface
		if (ICsInteractiveObject* Interface = Cast<ICsInteractiveObject>(Target))
		{
			if (UGameInstance* GameInstance = UCsScriptLibrary_Common::GetGameInstanceFromContext(NCsScriptLibraryInteractiveObject::Str::Hold, Target))
			{
				FCsScopedInteractiveObjectHoldParams ScopedParams(GameInstance);
				FCsInteractiveObjectHoldParams* Ptr = ScopedParams.Get<FCsInteractiveObjectHoldParams>();

				Params.CopyToNonScriptContainer(*Ptr);

				Interface->Hold(Ptr);
			}
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsInteractiveObject::StaticClass()))
		{
			if (Class->ImplementsInterface(UCsScriptInteractiveObject::StaticClass()))
			{
				ICsScriptInteractiveObject::Execute_Script_Hold(Target, Params);
			}
			else
			{
				UE_LOG(LogCsInteractive, Warning, TEXT("UCsScriptLibrary_InteractiveObject::Hold: Target implements an unsupported Interface deriving from: ICsInterfaceObject."));
			}
		}
		// Emulate Interface
	}
	else
	{
		UE_LOG(LogCsInteractive, Warning, TEXT("UCsScriptLibrary_InteractiveObject::Hold: Target is NULL."));
	}
}

void UCsScriptLibrary_InteractiveObject::Release(UObject* Target)
{
}

void UCsScriptLibrary_InteractiveObject::Touch(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Touch();
	}
}

void UCsScriptLibrary_InteractiveObject::Hover(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Hover();
	}
}

void UCsScriptLibrary_InteractiveObject::UnHover(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->UnHover();
	}
}

void UCsScriptLibrary_InteractiveObject::Collide(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Collide();
	}
}

void UCsScriptLibrary_InteractiveObject::UnCollide(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->UnCollide();
	}
}

void UCsScriptLibrary_InteractiveObject::Remove(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Remove();
	}
}