// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Ref/Ptr/CsProperty_Ref_Ptr.h"

class AActor;

struct FCsProperty_Ref_Actor : public TCsProperty_Ref_Ptr<AActor>
{
private:
	typedef TCsProperty_Ref_Ptr<AActor> Super;

public:

	FCsProperty_Ref_Actor() : Super() {}
	~FCsProperty_Ref_Actor() {}
};

typedef FCsProperty_Ref_Actor TCsActor_Ref;