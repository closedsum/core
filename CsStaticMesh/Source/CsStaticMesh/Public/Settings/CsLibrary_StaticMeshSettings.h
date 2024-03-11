// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsStaticMeshSettings;
class UObject;

struct FECsStaticMeshActor;

namespace NCsStaticMesh
{
	namespace NSettings
	{
		/**
		*/
		class CSSTATICMESH_API FLibrary
		{
		public:
			
			static UCsStaticMeshSettings* Get();
		
		// StaticMesh
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_StaticMeshActor();
			static const FString& GetSettingsEnumPath_StaticMeshActor();
			static FECsStaticMeshActor* GetDefault_ECsStaticMeshActor();

		#pragma endregion SkeletaMesh
		};
	}
}