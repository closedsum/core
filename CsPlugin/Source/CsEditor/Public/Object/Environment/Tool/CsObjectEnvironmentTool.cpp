// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/Environment/Tool/CsObjectEnvironmentTool.h"

// Interface
#include "Asset/Tool/CsGetAssetTool.h"
// Engine
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
// Editor
#include "Subsystems/EditorActorSubsystem.h"

namespace NCsObject
{
	namespace NEnvironment
	{
		#define DetailsType NCsObject::NEnvironment::FDetails
		DetailsType FTool::GetDetails(UObject* Object)
		{
			DetailsType Details;

			if (!IsValid(Object))
			{
				// Log
				return Details;
			}

			if (AActor* Actor = Cast<AActor>(Object))
			{
				// Level
				
				// Selected Actors
				{
					TArray<AActor*> OutActors = GEditor->GetEditorSubsystem<UEditorActorSubsystem>()->GetSelectedLevelActors();

					for (AActor* A : OutActors)
					{
						if (Actor == A ||
							Actor->GetClass()->GetDefaultObject() == A->GetClass()->GetDefaultObject())
						{
							Details.Type	  = NCsObject::EEnvironment::Editor;
							Details.bSelected = true;
							return Details;
						}
					}
				}
				// All Actors
				{
					TArray<AActor*> OutActors = GEditor->GetEditorSubsystem<UEditorActorSubsystem>()->GetAllLevelActors();

					for (AActor* A : OutActors)
					{
						if (Actor == A ||
							Actor->GetClass()->GetDefaultObject() == A->GetClass()->GetDefaultObject())
						{
							Details.Type	  = NCsObject::EEnvironment::Editor;
							Details.bSelected = false;
							return Details;
						}
					}
				}
			}

			// Blueprint
				
			// Get Opened Assets
			typedef NCsAsset::NTool::FImpl AssetToolType;

			AssetToolType* AssetTool							= Cast<ICsGetAssetTool>(GEngine)->GetAssetTool();
			const TArray<TWeakObjectPtr<UObject>>& OpenedAssets = AssetTool->GetOpenedAssetsImpl();

			for (const TWeakObjectPtr<UObject>& O : OpenedAssets)
			{
				UObject* Asset = O.IsValid() ? O.Get() : nullptr;

				if (!IsValid(Asset))
					continue;

				if (Object == Asset)
				{
					Details.Type	  = NCsObject::EEnvironment::EditorPreview;
					Details.bSelected = false;
					return Details;
				}
			}
			return Details;
		}
		#undef DetailsType
	}
}