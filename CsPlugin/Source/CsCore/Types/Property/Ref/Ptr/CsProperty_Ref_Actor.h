// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

class AActor;

struct CSCORE_API FCsProperty_Ref_Actor : public TCsProperty_Ref_Ptr<AActor>
{
private:
	typedef TCsProperty_Ref_Ptr<AActor> Super;

public:

	FCsProperty_Ref_Actor() : Super() {}
	~FCsProperty_Ref_Actor() {}
};

typedef FCsProperty_Ref_Actor TCsActor_Ref;