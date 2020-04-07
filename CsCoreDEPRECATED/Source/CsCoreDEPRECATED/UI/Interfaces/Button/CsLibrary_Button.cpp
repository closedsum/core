// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.

#include "UI/Interfaces/Button/CsLibrary_Button.h"
#include "CsCoreDEPRECATED.h"

#include "UI/Interfaces/Button/CsButton.h"

UCsLibrary_Button::UCsLibrary_Button(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCsLibrary_Button::Press(TScriptInterface<ICsButton>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Press();
	}
}

void UCsLibrary_Button::Release(TScriptInterface<ICsButton>& Target)
{
	if (UObject* O = Target.GetObject())
	{
		Target->Release();
	}
}