// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_WeaponImplSlice.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"

#define SliceType NCsWeapon::NData::FImplSlice

SliceType* FCsData_WeaponImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_WeaponImplSlice::SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_WeaponImplSlice::SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return nullptr;

	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData DataType;
	typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	if (!DataHandler)
		return nullptr;
	
	SliceType* Slice = DataHandler->SafeConstructData<SliceType, EMCsWeapon>(Context, Name);
	
	return Slice;
}

void FCsData_WeaponImplSlice::CopyToSlice(SliceType* Slice)
{
}

void FCsData_WeaponImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
}

#undef SliceType

bool FCsData_WeaponImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	return true;
}

const FName NCsWeapon::NData::FImplSlice::Name = FName("NCsWeapon::NData::FImplSlice");

namespace NCsWeapon
{
	namespace NData
	{
		namespace NImplSlice
		{
			namespace NCached
			{
				namespace Name
				{
					const FName WeaponSlice = FName("WeaponSlice");
				}
			}
		}

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define CS_TEMP_GET_SAFE_DATA_HANDLER \
			typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary; \
			typedef NCsWeapon::NData::IData DataType; \
			typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType; \
			\
			DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log); \
			\
			if (!DataHandler) \
				return nullptr;

		/*static*/ FImplSlice* FImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			using namespace NCsWeapon::NData::NImplSlice::NCached;

			CS_IS_PTR_NULL_RET_NULL(Object)

			#define DataHandlerType NCsData::NManager::NHandler::TData
			typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
			typedef NCsWeapon::NData::IData DataType;
			typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;
			
			DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
			
			#undef DataHandlerType

			if (!DataHandler)
				return nullptr;

			FImplSlice* Slice = DataHandler->SafeConstructData<FImplSlice, EMCsWeapon>(Context, DataName);

			if (!Slice)
				return nullptr;

			// Check for properties matching interface: WeaponDataType (NCsWeapon::NData::IData)
			typedef NCsProperty::FLibrary PropertyLibrary;

			bool Success = false;

			// Try FCsData_WeaponImplSlice
			if (FCsData_WeaponImplSlice* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<FCsData_WeaponImplSlice>(Context, Object, Object->GetClass(), Name::WeaponSlice, nullptr))
			{
				SliceAsStruct->CopyToSlice(Slice);
				Success = true;
			}
			// Try individual properties
			else
			{
				Success = true;
			}

			if (!Success)
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsWeapon::NData::IData.")));
					Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_WeaponImplSlice with name: WeaponSlice.")));
				}
			}

			// NOTE: If this technique is to be used in a shipping build, this will need to be slightly altered to
			//		 allow destroying the object when the data needs to be "unloaded"
			typedef NCsData::NManager::FLibrary DataManagerLibrary;

			DataManagerLibrary::AddDataCompositionObject_Loaded_Checked(Context, WorldContext, FName(*DataName), Object, FImplSlice::Name);

			return Slice;
		}

		bool FImplSlice::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			return true;
		}
	}
}