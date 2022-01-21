// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

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