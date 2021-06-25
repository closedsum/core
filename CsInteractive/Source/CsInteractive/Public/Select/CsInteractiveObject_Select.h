// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsInteractiveObject_Select.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSINTERACTIVE_API UCsInteractiveObject_Select : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsInteractive::NObject::NSelect::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsInteractive, NObject, NSelect, NParams, IParams)
// NCsInteractive::NObject::NDeselect::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsInteractive, NObject, NDeselect, NParams, IParams)

class CSINTERACTIVE_API ICsInteractiveObject_Select
{
	GENERATED_IINTERFACE_BODY()

public:

#define SelectParamsType NCsInteractive::NObject::NSelect::NParams::IParams
#define DeselectParamsType NCsInteractive::NObject::NDeselect::NParams::IParams

	virtual void Select(SelectParamsType* Params) = 0;

	virtual void Deselect(DeselectParamsType* Params) = 0;

#undef SelectParamsType
#undef DeselectParamsType
};