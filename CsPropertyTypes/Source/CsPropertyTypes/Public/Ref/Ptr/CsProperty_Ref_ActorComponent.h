// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Ref/Ptr/CsProperty_Ref_Ptr.h"

class UActorComponent;

struct FCsProperty_Ref_ActorComponent : public TCsProperty_Ref_Ptr<UActorComponent>
{
private:
	typedef TCsProperty_Ref_Ptr<UActorComponent> Super;

public:

	FCsProperty_Ref_ActorComponent() : Super() {}
	~FCsProperty_Ref_ActorComponent() {}
};

typedef FCsProperty_Ref_ActorComponent TCsActorComponent_Ref;