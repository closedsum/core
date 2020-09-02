// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

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