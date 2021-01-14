// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data.h"
#include "CsCore.h"

// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsData
{
	UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		UGameInstance* GameInstance = World->GetGameInstance();

		checkf(GameInstance, TEXT("%s: Failed to get GameInstace from World: %s."), *Context, *(World->GetName()));

		return GameInstance;
	}

	FString FLibrary::PrintObjectAndClass(UObject* Object)
	{
		return FString::Printf(TEXT("Object: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	FString FLibrary::PrintObjectAndClass(ICsData* Data, const FString& MemberName)
	{
		return FString::Printf(TEXT("%s: %s with Class: %s"), *MemberName, *(Data->_getUObject()->GetName()), *(Data->_getUObject()->GetClass()->GetName()));
	}

	FString FLibrary::PrintObjectAndClass(ICsData* Data)
	{
		if (UObject* O = Data->_getUObject())
			return PrintObjectAndClass(O);
		return FString::Printf(TEXT("INVALID (Non-UObject)"));
	}

	#define DataType NCsData::IData
	DataType* FLibrary::SafeLoadData(const FString& Context, UObject* Object)
	{
		if (!Object)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Object is NULL."), *Context);
			return nullptr;
		}

		ICsData* UData = Cast<ICsData>(Object);

		if (!UData)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s does NOT implement interface: ICsData."), *Context, *PrintObjectAndClass(Object));
			return nullptr;
		}

		UData->Load(NCsLoadFlags::All);

		DataType* Data = UData->_getIData();

		if (!Data)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));
			return nullptr;
		}
		return Data;
	}
	#undef DataType

	#define DataType NCsData::IData
	DataType* FLibrary::GetSafeData(const FString& Context, UObject* Object)
	{
		if (!Object)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Object is NULL."), *Context);
			return nullptr;
		}

		ICsData* UData = Cast<ICsData>(Object);

		if (!UData)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s does NOT implement interface: ICsData."), *Context, *PrintObjectAndClass(Object));
			return nullptr;
		}

		DataType* Data = UData->_getIData();

		if (!Data)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));
			return nullptr;
		}
		return Data;
	}
	#undef DataType

	#define DataType NCsData::IData
	DataType* FLibrary::GetDataChecked(const FString& Context, UObject* WorldContext, const FName& DataName)
	{
		ICsData* UData = UCsManager_Data::Get(GetContextRootChecked(Context, WorldContext))->GetDataChecked(Context, DataName);
		DataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));

		return Data;
	}
	#undef DataType

	#define DataType NCsData::IData
	DataType* FLibrary::GetDataChecked(const FString& Context, UObject* Object)
	{
	#undef DataType

		checkf(Object, TEXT("%s: Object is NULL."), *Context);

		ICsData* UData = Cast<ICsData>(Object);

		checkf(UData, TEXT("%s: Object: %s does NOT implement the interface: ICsData."), *Context, *(Object->GetName()));

		return GetDataChecked(Context, UData);
	}

	#define DataType NCsData::IData
	DataType* FLibrary::GetDataChecked(const FString& Context, ICsData* UData)
	{
		checkf(UData, TEXT("%s: UData is NULL."), *Context);

		DataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));

		return Data;
	}
	#undef DataType
}