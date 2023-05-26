// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

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