// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Data/Handler/CsManager_Data_ClassHandler.h"
// Types
#include "Types/CsTypes_Beam.h"
#include "Managers/Beam/CsBeamPooled.h"

namespace NCsBeam
{
	namespace NManager
	{
		namespace NHandler
		{
		#define ClassHandlerType NCsData::NManager::NHandler::TClass

			/**
			*/
			class CSBEAM_API FClass : public ClassHandlerType<FCsBeamPooled, FCsBeamPtr, FECsBeamClass>
			{
			private:

				typedef ClassHandlerType<FCsBeamPooled, FCsBeamPtr, FECsBeamClass> Super;

			public:

				FClass();

			// ClassHandlerType
			#pragma region
			protected:

				virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

			#pragma endregion ClassHandlerType
			};

		#undef ClassHandlerType
		}
	}
}