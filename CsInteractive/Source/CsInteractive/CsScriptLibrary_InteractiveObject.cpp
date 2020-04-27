// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.

#include "CsScriptLibrary_InteractiveObject.h"
#include "CsInteractive.h"

#include "CsInteractiveObject.h"
#include "CsScriptInteractiveObject.h"

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

void UCsScriptLibrary_InteractiveObject::Hold(TScriptInterface<ICsInteractiveObject>& Target, const FCsScriptInteractiveObjectHoldParams& Params)
{
	if (UObject* O = Target.GetObject())
	{
		UClass* Class = O->GetClass();

		// Interface
		if (ICsInteractiveObject* Interface = Cast<ICsInteractiveObject>(O))
		{
			// TODO: Need Manager for this
			FCsInteractiveObjectHoldParams* Ptr = new FCsInteractiveObjectHoldParams();
			*Ptr = Params.ConvertToNonScriptContainer();

			Interface->Hold(Ptr);

			delete Ptr;
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsInteractiveObject::StaticClass()))
		{
			if (Class->ImplementsInterface(UCsScriptInteractiveObject::StaticClass()))
			{
				ICsScriptInteractiveObject::Execute_Script_Hold(O, Params);
			}
			else
			{
				// Log Warning
			}
		}
	}
	else
	{
		UE_LOG(LogCsInteractive, Warning, TEXT("UCsScriptLibrary_InteractiveObject::Hold: Target is NULL."));
	}
}

void UCsScriptLibrary_InteractiveObject::Release(TScriptInterface<ICsInteractiveObject>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Release();
	}
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