// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.
#include "Script/CsScriptLibrary_InteractiveObject.h"
#include "CsInteractive.h"

// Interactive
#include "Select/CsInteractiveObject_Select.h"
#include "Hover/CsInteractiveObject_Hover.h"

// Cached
#pragma region

namespace NCsScriptLibraryInteractiveObject
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InteractiveObject, Select);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InteractiveObject, Deselect);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InteractiveObject, Hover);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InteractiveObject, UnHover);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_InteractiveObject::UCsScriptLibrary_InteractiveObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UCsScriptLibrary_InteractiveObject::Select(const FString& Context, UObject* Target, const FCsInteractiveObject_Select_Params& Params)
{
	using namespace NCsScriptLibraryInteractiveObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Select : Context;

	void(*Log)(const FString&) = &NCsInteractive::FLog::Warning;

	if (!Target)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target is NULL."), *Ctxt));
		return false;
	}

	// TODO: Handle script objects that implement the interface

	ICsInteractiveObject_Select* ISelect = Cast<ICsInteractiveObject_Select>(Target);

	if (!ISelect)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target: %s with Class: %s does NOT implement interface: ICsInteractiveObject_Select."), *Ctxt, *(Target->GetName()), *(Target->GetClass()->GetName())));
		return false;
	}

	if (!Params.IsValid(Ctxt))
		return false;

	typedef NCsInteractive::NObject::NSelect::NParams::FImpl ParamsType;

	ParamsType ParamsImpl;
	Params.CopyToParams(&ParamsImpl);

	ISelect->Select(&ParamsImpl);
	return true;
}

bool UCsScriptLibrary_InteractiveObject::Deselect(const FString& Context, UObject* Target, const FCsInteractiveObject_Deselect_Params& Params)
{
	using namespace NCsScriptLibraryInteractiveObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Deselect : Context;

	void(*Log)(const FString&) = &NCsInteractive::FLog::Warning;

	if (!Target)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target is NULL."), *Ctxt));
		return false;
	}

	// TODO: Handle script objects that implement the interface

	ICsInteractiveObject_Select* ISelect = Cast<ICsInteractiveObject_Select>(Target);

	if (!ISelect)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target: %s with Class: %s does NOT implement interface: ICsInteractiveObject_Select."), *Ctxt, *(Target->GetName()), *(Target->GetClass()->GetName())));
		return false;
	}

	if (!Params.IsValid(Ctxt))
		return false;

	typedef NCsInteractive::NObject::NDeselect::NParams::FImpl ParamsType;

	ParamsType ParamsImpl;
	Params.CopyToParams(&ParamsImpl);

	ISelect->Deselect(&ParamsImpl);
	return true;
}

bool UCsScriptLibrary_InteractiveObject::Hover(const FString& Context, UObject* Target, const FCsInteractiveObject_Hover_Params& Params)
{
	using namespace NCsScriptLibraryInteractiveObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Hover : Context;

	void(*Log)(const FString&) = &NCsInteractive::FLog::Warning;

	if (!Target)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target is NULL."), *Ctxt));
		return false;
	}

	// TODO: Handle script objects that implement the interface

	ICsInteractiveObject_Hover* IHover = Cast<ICsInteractiveObject_Hover>(Target);

	if (!IHover)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target: %s with Class: %s does NOT implement interface: ICsInteractiveObject_Hover."), *Ctxt, *(Target->GetName()), *(Target->GetClass()->GetName())));
		return false;
	}

	if (!Params.IsValid(Ctxt))
		return false;

	typedef NCsInteractive::NObject::NHover::NParams::FImpl ParamsType;

	ParamsType ParamsImpl;
	Params.CopyToParams(&ParamsImpl);

	IHover->Hover(&ParamsImpl);
	return true;
}

bool UCsScriptLibrary_InteractiveObject::UnHover(const FString& Context, UObject* Target, const FCsInteractiveObject_UnHover_Params& Params)
{
	using namespace NCsScriptLibraryInteractiveObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::UnHover : Context;

	void(*Log)(const FString&) = &NCsInteractive::FLog::Warning;

	if (!Target)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target is NULL."), *Ctxt));
		return false;
	}

	// TODO: Handle script objects that implement the interface

	ICsInteractiveObject_Hover* IHover = Cast<ICsInteractiveObject_Hover>(Target);

	if (!IHover)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Target: %s with Class: %s does NOT implement interface: ICsInteractiveObject_Hover."), *Ctxt, *(Target->GetName()), *(Target->GetClass()->GetName())));
		return false;
	}

	if (!Params.IsValid(Ctxt))
		return false;

	typedef NCsInteractive::NObject::NUnHover::NParams::FImpl ParamsType;

	ParamsType ParamsImpl;
	Params.CopyToParams(&ParamsImpl);

	IHover->UnHover(&ParamsImpl);
	return true;
}