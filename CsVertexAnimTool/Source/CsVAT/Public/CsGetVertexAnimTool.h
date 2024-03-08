// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsGetVertexAnimTool.generated.h"

class UCsVertexAnimProfile;

namespace NCsAnimation
{
	namespace NVertex
	{
		namespace NTool
		{
			struct CSVAT_API FImpl
			{
			public:

				void(*DoBackProcessImpl)(UCsVertexAnimProfile*);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSVAT_API UCsGetVertexAnimTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSVAT_API ICsGetVertexAnimTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define VertexAnimToolType NCsAnimation::NVertex::NTool::FImpl

	virtual VertexAnimToolType* GetVertexAnimTool() = 0;

#undef VertexAnimToolType
};