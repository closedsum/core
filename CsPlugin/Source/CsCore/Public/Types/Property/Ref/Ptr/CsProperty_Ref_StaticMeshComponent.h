// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

class UStaticMeshComponent;

struct FCsProperty_Ref_StaticMeshComponent : public TCsProperty_Ref_Ptr<UStaticMeshComponent>
{
private:
	typedef TCsProperty_Ref_Ptr<UStaticMeshComponent> Super;

public:

	FCsProperty_Ref_StaticMeshComponent() : Super() {}
	~FCsProperty_Ref_StaticMeshComponent() {}
};

typedef FCsProperty_Ref_StaticMeshComponent TCsStaticMeshComponent_Ref;