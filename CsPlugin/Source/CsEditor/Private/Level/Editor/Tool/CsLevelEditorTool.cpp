// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Level/Editor/Tool/CsLevelEditorTool.h"

// Editor
#include "Subsystems/EditorActorSubsystem.h"

namespace NCsLevel
{
	namespace NEditor
	{
		//const TArray<UObject*>&(*GetObjectsImpl)();

		//const TArray<UObject*>&(*GetObjectsByClassImpl)(UClass* /*Class*/);

		//const TArray<UObject*>&(*GetSelectedObjectsImpl)();

		void FTool::GetActors(TArray<AActor*>& OutActors)
		{
			OutActors = GEditor->GetEditorSubsystem<UEditorActorSubsystem>()->GetAllLevelActors();
		}

		void FTool::GetActorsByClass(UClass* Class, TArray<AActor*>& OutActors)
		{
			TArray<AActor*> Actors = GEditor->GetEditorSubsystem<UEditorActorSubsystem>()->GetAllLevelActors();

			for (AActor* A : Actors)
			{
				if (A->GetClass()->IsChildOf(Class))
				{
					OutActors.Add(A);
				}
			}
		}

		void FTool::GetActorsByInterface(UClass* Class, TArray<AActor*>& OutActors)
		{
			TArray<AActor*> Actors = GEditor->GetEditorSubsystem<UEditorActorSubsystem>()->GetAllLevelActors();

			for (AActor* A : Actors)
			{
				if (A->GetClass()->ImplementsInterface(Class))
				{
					OutActors.Add(A);
				}
			}
		}

		void FTool::GetSelectedActors(TArray<AActor*>& OutActors)
		{
			OutActors = GEditor->GetEditorSubsystem<UEditorActorSubsystem>()->GetSelectedLevelActors();
		}
	}
}