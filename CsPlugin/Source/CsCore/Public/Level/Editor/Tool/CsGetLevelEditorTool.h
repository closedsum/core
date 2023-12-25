// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetLevelEditorTool.generated.h"

class UObject;

namespace NCsLevel
{
	namespace NEditor
	{
		namespace NTool
		{
			struct CSCORE_API FImpl
			{
			public:

				const TArray<UObject*>&(*GetSelectedObjectsImpl)();
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetLevelEditorTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetLevelEditorTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define LevelEditorToolType NCsLevel::NEditor::NTool::FImpl

	virtual LevelEditorToolType* GetLevelEditorTool() = 0;

#undef LevelEditorToolType
};