// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Point/CsData_DamagePointImplSlice.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Handler/CsManager_Damage_DataHandler.h"

#define SliceType NCsDamage::NData::NPoint::FImplSlice

SliceType* FCsData_DamagePointImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_DamagePointImplSlice::SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_DamagePointImplSlice::SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return nullptr;

	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
	typedef NCsDamage::NData::IData DataType;
	typedef NCsDamage::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* DataHandler = DamageManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;

	SliceType* Slice = DataHandler->SafeConstructData<SliceType, EMCsDamageData>(Context, Name);

	return Slice;
}

void FCsData_DamagePointImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetValue(&Value);
	Slice->SetType(&Type);
}

void FCsData_DamagePointImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetValue(Value);
	Slice->SetType(Type);
}

#undef SliceType

bool FCsData_DamagePointImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageType, FECsDamageType, Type)
	return true;
}

const FName NCsDamage::NData::NPoint::FImplSlice::Name = FName("NCsDamage::NData::NPoint::FImplSlice");

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName DamagePointSlice = FName("DamagePointSlice");

						const FName Value = FName("Value");
						const FName Type = FName("Type");
					}
				}
			}

			/*static*/ FImplSlice* FImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
			{
				using namespace NCsDamage::NData::NPoint::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(Object)

				FImplSlice* Slice = SafeConstruct_Internal(Context, WorldContext, DataName, Log);

				if (!Slice)
					return nullptr;

				// Check for properties matching interface: ProjectileDataType (NCsProjectile::NData::IData)
				typedef NCsProperty::FLibrary PropertyLibrary;

				bool Success = false;

				// Try FCsData_DamagePointImplSlice
				typedef FCsData_DamagePointImplSlice StructSliceType;

				if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::DamagePointSlice, nullptr))
				{
					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}
				// Try individual properties
				else
				{
					float* ValuePtr			= PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::Value, nullptr);
					FECsDamageType* TypePtr = PropertyLibrary::GetStructPropertyValuePtr<FECsDamageType>(Context, Object, Object->GetClass(), Name::Type, nullptr);

					if (ValuePtr &&
						TypePtr)
					{
						Slice->SetValue(ValuePtr);
						Slice->SetType(TypePtr);
						Success = true;
					}
				}

				if (!Success)
				{
					if (Log)
					{
						typedef NCsObject::FLibrary ObjectLibrary;

						Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: NCsDamage::NData::IData."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_DamagePointImplSlice with name: DamagePointSlice."), *Context));
						Log(FString::Printf(TEXT("%s: - OR"), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: Value."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FECsDamageType with name: Type."), *Context));
					}
				}

				// NOTE: If this technique is to be used in a shipping build, this will need to be slightly altered to
				//		 allow destroying the object when the data needs to be "unloaded"
				typedef NCsData::NManager::FLibrary DataManagerLibrary;

				DataManagerLibrary::AddDataCompositionObject_Loaded_Checked(Context, WorldContext, FName(*DataName), Object, FImplSlice::Name);

				return Slice;
			}

			/*static*/ FImplSlice* FImplSlice::SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& DataName, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
			{
				#define DataHandlerType NCsData::NManager::NHandler::TData
				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
				typedef NCsDamage::NData::IData DataType;
				typedef NCsDamage::NData::FInterfaceMap DataInterfaceMapType;
	
				DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* DataHandler = DamageManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
				#undef DataHandlerType

				if (!DataHandler)
					return nullptr;

				FImplSlice* Slice = DataHandler->SafeConstructData<FImplSlice, EMCsDamageData>(Context, DataName);

				return Slice;
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				check(EMCsDamageType::Get().IsValidEnumChecked(Context, GetType()));
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageType, FECsDamageType, GetType())
				return true;
			}
		}
	}
}