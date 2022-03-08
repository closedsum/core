// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Script/CsScriptLibrary_Data_Weapon.h"
#include "CsWp.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/CsData_ProjectileImplSlice.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"
// Params
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTraceImpl.h"
// Log
#include "Utility/CsWpLog.h"

// Cached
#pragma region

namespace NCsScriptLibraryDataWeapon
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, Construct);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, ConstructFromObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSlice_ProjectileWeapon);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSliceFromObject_ProjectileWeapon);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddToSlice_ProjectileWeapon_LaunchTraceParams);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddToSliceFromObject_ProjectileWeapon_LaunchTraceParams);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSlice_GetProjectileType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSliceFromObject_GetProjectileType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSlice_ProjectileWeapon_VisualFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSliceFromObject_ProjectileWeapon_VisualFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSlice_ProjectileWeapon_SoundFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon, AddSliceFromObject_ProjectileWeapon_SoundFire);
		}

		namespace Name
		{
			const FName ProjectileTypeSlice = FName("ProjectileTypeSlice");

			const FName ProjectileType = FName("ProjectileType");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Weapon::UCsScriptLibrary_Data_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Data_Weapon::Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_WeaponImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Construct : Context;

	typedef NCsWeapon::NData::FImplSlice DataSliceType;

	if (!Slice.IsValid(Ctxt))
		return false;

	DataSliceType* DataSlice = Slice.SafeConstructAsValue(Ctxt, WorldContextObject, Name);

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructFromObject : Context;

	typedef NCsWeapon::NData::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::SafeConstruct(Ctxt, WorldContextObject, Name, Object);

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSlice_ProjectileWeapon(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileWeaponImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_ProjectileWeapon : Context;

	typedef NCsWeapon::NProjectile::NData::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSliceFromObject_ProjectileWeapon(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_ProjectileWeapon : Context;

	typedef NCsWeapon::NProjectile::NData::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Ctxt, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddToSlice_ProjectileWeapon_LaunchTraceParams(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsProjectileWeaponLaunchTraceParams& Params)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddToSlice_ProjectileWeapon_LaunchTraceParams : Context;

	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl ParamsType;

	ParamsType* ParamsImpl = Params.AddSafeToSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return ParamsImpl && ParamsImpl->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddToSliceFromObject_ProjectileWeapon_LaunchTraceParams(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddToSliceFromObject_ProjectileWeapon_LaunchTraceParams : Context;

	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl ParamsType;

	ParamsType* ParamsImpl = ParamsType::AddSafeToSlice(Ctxt, WorldContextObject, FName(*Name), Object);

	return ParamsImpl && ParamsImpl->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSlice_GetProjectileType(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_GetProjectileTypeImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_GetProjectileType : Context;

	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData DataType;
	typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Ctxt, WorldContextObject);

	#undef DataHandlerType

	if (!DataHandler)
		return false;

	typedef NCsProjectile::NData::NType::FImplSlice SliceType;

	SliceType* SliceImpl = DataHandler->AddSafeDataSlice<SliceType, ICsData_GetProjectileType>(Ctxt, FName(*Name));

	if (!SliceImpl)
		return false; 

	Slice.CopyToSliceAsValue(SliceImpl);

	return SliceImpl->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSliceFromObject_GetProjectileType(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_GetProjectileType : Context;

	void(*Log)(const FString&) = &NCsWeapon::FLog::Warning;

	CS_IS_PTR_NULL_RET_NULL(Object)

	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData DataType;
	typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;

	DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Ctxt, WorldContextObject, Log);
				
	#undef DataHandlerType

	if (!DataHandler)
		return false;

	typedef NCsProjectile::NData::NType::FImplSlice SliceType;

	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, ICsData_GetProjectileType>(Ctxt, FName(*Name));

	if (!Slice)
		return false;

	// Check for properties matching interface: PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	// Try FCsData_GetProjectileTypeImplSlice
	typedef FCsData_GetProjectileTypeImplSlice StructSliceType;

	if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::ProjectileTypeSlice, nullptr))
	{
		SliceAsStruct->CopyToSlice(Slice);
		Success = true;
	}
	// Try individual properties
	else
	{
		FECsProjectile* ProjectileTypePtr = PropertyLibrary::GetStructPropertyValuePtr<FECsProjectile>(Ctxt, Object, Object->GetClass(), Name::ProjectileType, nullptr);

		if (ProjectileTypePtr)
		{
			Slice->SetProjectileType(ProjectileTypePtr);
			Success = true;
		}
	}

	if (!Success)
	{
		if (Log)
		{
			Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: ICsData_GetProjectileType.")));
			Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_GetProjectileTypeImplSlice with name: ProjectileTypeSlice.")));
			Log(FString::Printf(TEXT("%s: - OR")));
			Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FECsProjectile with name: ProjectileType.")));
		}
	}
	return Success;
}

bool UCsScriptLibrary_Data_Weapon::AddSlice_ProjectileWeapon_VisualFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileWeapon_VisualFireImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_ProjectileWeapon_VisualFire : Context;

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSliceFromObject_ProjectileWeapon_VisualFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_ProjectileWeapon_VisualFire : Context;

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Ctxt, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSlice_ProjectileWeapon_SoundFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileWeapon_SoundFireImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_ProjectileWeapon_SoundFire : Context;

	typedef NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Ctxt);
}

bool UCsScriptLibrary_Data_Weapon::AddSliceFromObject_ProjectileWeapon_SoundFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_ProjectileWeapon_SoundFire : Context;

	typedef NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Ctxt, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Ctxt);
}