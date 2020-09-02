// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Handler/CsManager_UserWidget_Datahandler.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUILibrary_DataRootSet.h"
#include "Library/CsLibrary_Property.h"
// UserWidget
//#include "Data/CsData_UserWidgetEmuSlice.h"

// Cached
#pragma region

namespace NCsManagerUserWidgetDataHandler
{
	namespace Name
	{
	}
}

#pragma endregion Cached

FCsManager_UserWidget_DataHandler::FCsManager_UserWidget_DataHandler()
{
}

// TCsManager_PooledObject_DataHandler Interface
#pragma region

void FCsManager_UserWidget_DataHandler::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
{
	UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

	TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.UserWidgets;

	checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().Projectiles is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

	checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

	OutDataTables.Add(DataTable);
	OutDataTableSoftObjects.Add(DataTableSoftObject);
}

/*
bool FCsManager_UserWidget_DataHandler::HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const
{
	UObject* DataRootSetImpl			 = FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsPrjDataRootSet& DataRootSet = FCsPrjLibrary_DataRootSet::GetChecked(Context, MyRoot);

	checkf(Index < DataRootSet.Projectiles.Num(), TEXT("%s: Index < %s.GetCsPrjDataRootSet().Projectiles.Num() (%d >= %d)."), *Context, *(DataRootSetImpl->GetName()), DataRootSet.Projectiles.Num());

	return DataRootSet.Projectiles[Index].EmulatedDataInterfaces.Num() >  CS_EMPTY;
	return false;
}
*/

/*
void FCsManager_UserWidget_DataHandler::CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
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

			checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataMap.Add(Name, Data);

			FCsData_UserWidgetInterfaceMap* EmulatedInterfaceMap = new FCsData_UserWidgetInterfaceMap();

			checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

			FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<ICsData_UserWidget>(FCsData_UserWidgetEnumSlice::Name, static_cast<ICsData_UserWidget*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(FCsData_UserWidgetEnumSlice::Name, Data);

			DataMap.Add(Name, Data);
		}
	}
}
*/

/*
bool FCsManager_UserWidget_DataHandler::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
{
	// FCsData_UserWidgetEnumSlice
	if (InterfaceImplName == FCsData_UserWidgetEnumSlice::Name)
	{
		delete static_cast<FCsData_UserWidgetEnumSlice*>(Data);
		return true;
	}
	return false;
}
*/

#pragma endregion TCsManager_PooledObject_DataHandler Interface

/*
const TSet<FECsUserWidgetData>& FCsManager_UserWidget_DataHandler::GetEmulatedDataInterfaces(const FString& Context, const int32& Index)
{
	UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

	return DataRootSet.UserWidgets[Index].EmulatedDataInterfaces;
}
*/