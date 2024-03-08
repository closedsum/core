// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

class UPrimitiveComponent;

struct FCsProperty_Ref_PrimitiveComponent : public TCsProperty_Ref_Ptr<UPrimitiveComponent>
{
private:
	typedef TCsProperty_Ref_Ptr<UPrimitiveComponent> Super;

public:

	FCsProperty_Ref_PrimitiveComponent() : Super() {}
	~FCsProperty_Ref_PrimitiveComponent() {}
};

typedef FCsProperty_Ref_PrimitiveComponent TCsPrimitiveComponent_Ref;