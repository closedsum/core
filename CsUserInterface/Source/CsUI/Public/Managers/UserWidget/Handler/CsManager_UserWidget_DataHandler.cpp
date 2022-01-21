// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Handler/CsManager_UserWidget_Datahandler.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUILibrary_DataRootSet.h"
#include "Library/CsLibrary_Property.h"
// UserWidget
//#include "Data/CsData_UserWidgetImplSlice.h"

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
			FData::FData()
			{
			}

			// DataHandlerType (NCsData::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.UserWidgets;

				checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsUIDataRootSet().Projectiles is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UDataTable* DataTable = Manager_Data->GetDataTableChecked(Context, DataTableSoftObject);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			/*
			bool FData::HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const
			{
				UObject* DataRootSetImpl			 = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsPrjDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				checkf(Index < DataRootSet.Projectiles.Num(), TEXT("%s: Index < %s.GetCsPrjDataRootSet().Projectiles.Num() (%d >= %d)."), *Context, *(DataRootSetImpl->GetName()), DataRootSet.Projectiles.Num());

				return DataRootSet.Projectiles[Index].EmulatedDataInterfaces.Num() >  CS_EMPTY;
				return false;
			}
			*/

			/*
			void FData::CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
			{
				using namespace NCsManagerUserWidgetDataHandler;

				const UScriptStruct* RowStruct = DataTable->GetRowStruct();

				const TSet<FECsUserWidgetData>& EmulatedDataInterfaces = GetEmulatedDataInterfaces(Context, Index);

				checkf(EmulatedDataInterfaces.Find(NCsUserWidgetData::UserWidget), TEXT("%s: Emulated Data Interfaces must include ICsData_UserWidget."), *Context);

				// ICsData_UserWidget
				bool Emulates_ICsDataUserWidget = true;

				// Get Manager_Data
				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				// Check which rows from the DataTable have been loaded
				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& Name = Pair.Key;
					uint8* RowPtr	  = Manager_Data->GetDataTableRow(DataTableSoftObject, Name);

					if (!RowPtr)
						continue;

					// ICsData_UserWidget
					if (Emulates_ICsDataUserWidget)
					{
						FCsData_UserWidgetEnumSlice* Data = new FCsData_UserWidgetEnumSlice();

						checkf(ImplDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

						ImplDataMap.Add(Name, Data);

						typedef NCsUserWidget::NData::FInterfaceMap InterfaceMapType;

						InterfaceMapType* ImplInterfaceMap = new InterfaceMapType();

						checkf(ImplDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

						ImplDataInterfaceMap.Add(Name, ImplInterfaceMap);

						FCsInterfaceMap* InterfaceMap = ImplInterfaceMap->GetInterfaceMap();

						InterfaceMap->Add<ICsData_UserWidget>(FCsData_UserWidgetEnumSlice::Name, static_cast<ICsData_UserWidget*>(Data));

						Data->SetInterfaceMap(InterfaceMap);

						TMap<FName, void*>& InterfaceImplMap = ImplDataSliceByNameMap.FindOrAdd(Name);
						InterfaceImplMap.Add(FCsData_UserWidgetEnumSlice::Name, Data);

						DataMap.Add(Name, Data);
					}
				}
			}
			*/

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)

			/*
			const TSet<FECsUserWidgetData>& FData::GetEmulatedDataInterfaces(const FString& Context, const int32& Index)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				return DataRootSet.UserWidgets[Index].EmulatedDataInterfaces;
			}
			*/
		}
	}
}