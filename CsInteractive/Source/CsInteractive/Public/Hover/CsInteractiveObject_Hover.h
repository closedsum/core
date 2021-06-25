// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsInteractiveObject_Hover.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSINTERACTIVE_API UCsInteractiveObject_Hover : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsInteractive::NObject::NHover::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsInteractive, NObject, NHover, NParams, IParams)
// NCsInteractive::NObject::NUnHover::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsInteractive, NObject, NUnHover, NParams, IParams)

class CSINTERACTIVE_API ICsInteractiveObject_Hover
{
	GENERATED_IINTERFACE_BODY()

public:

#define HoverParamsType NCsInteractive::NObject::NHover::NParams::IParams
#define UnHoverParamsType NCsInteractive::NObject::NUnHover::NParams::IParams

	virtual void Hover(HoverParamsType* Params) = 0;

	virtual void UnHover(UnHoverParamsType* Params) = 0;

#undef HoverParamsType
#undef UnHoverParamsType
};