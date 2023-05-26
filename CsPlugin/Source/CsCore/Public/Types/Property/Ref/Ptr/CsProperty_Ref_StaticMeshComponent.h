// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

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