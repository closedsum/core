// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsSkeletalMeshSettings;
class UObject;

struct FECsSkeletalMeshActor;

namespace NCsSkeletalMesh
{
	namespace NSettings
	{
		/**
		*/
		class CSSKELETALMESH_API FLibrary
		{
		public:
			
			static UCsSkeletalMeshSettings* Get();
		
		// SkeletalMesh
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_SkeletalMeshActor();
			static const FString& GetSettingsEnumPath_SkeletalMeshActor();
			static FECsSkeletalMeshActor* GetDefault_ECsSkeletalMeshActor();

		#pragma endregion SkeletaMesh
		};
	}
}