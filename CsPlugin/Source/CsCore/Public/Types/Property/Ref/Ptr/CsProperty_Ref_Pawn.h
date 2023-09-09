// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

class APawn;

struct FCsProperty_Ref_Pawn : public TCsProperty_Ref_Ptr<APawn>
{
private:
	typedef TCsProperty_Ref_Ptr<APawn> Super;

public:

	FCsProperty_Ref_Pawn() : Super() {}
	~FCsProperty_Ref_Pawn() {}
};

typedef FCsProperty_Ref_Pawn TCsPawn_Ref;