// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetLevelEditorTool.generated.h"

class UObject;
class AActor;
class UClass;

namespace NCsLevel
{
	namespace NEditor
	{
		namespace NTool
		{
			struct CSCORE_API FImpl
			{
			public:

			// Object - TODO: DEPRECATE?

				const TArray<UObject*>&(*GetObjectsImpl)();

				const TArray<UObject*>&(*GetObjectsByClassImpl)(UClass* /*Class*/);

				const TArray<UObject*>&(*GetSelectedObjectsImpl)();

			// Actor

				void(*GetActorsImpl)(TArray<AActor*>& /*OutActors*/);

				void(*GetActorsByClassImpl)(UClass* /*Class*/, TArray<AActor*>& /*OutActors*/);

				void(*GetActorsByInterfaceImpl)(UClass* /*Class*/, TArray<AActor*>& /*OutActors*/);

				void(*GetSelectedActorsImpl)(TArray<AActor*>& /*OutActors*/);
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