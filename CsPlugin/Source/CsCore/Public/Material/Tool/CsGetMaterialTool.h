// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetMaterialTool.generated.h"

class UMaterial;
class UMaterialFunction;

namespace NCsMaterial
{
	namespace NTool
	{
		struct CSCORE_API FImpl
		{
		public:

			void(*ApplyAndSaveImpl)(UMaterial*);
			void(*ApplyAndSaveFunctionImpl)(UMaterialFunction*);
		};
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetMaterialTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetMaterialTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define MaterialToolType NCsMaterial::NTool::FImpl

	virtual MaterialToolType* GetMaterialTool() = 0;

#undef MaterialToolType
};