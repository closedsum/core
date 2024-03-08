// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Damage/CsData_Beam_DamagePointImplSlice.h"

// Library
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"

#define SliceType NCsBeam::NData::NDamage::NPoint::FImplSlice

SliceType* FCsData_Beam_DamagePointImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_DamagePointImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_DamagePointImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
	typedef NCsBeam::NData::IData DataType;
	typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;

	DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);

	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;

	typedef NCsBeam::NData::NDamage::IDamage DamageDataType;

	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, DamageDataType>(Context, Name);

	return Slice;
}

void FCsData_Beam_DamagePointImplSlice::CopyToSlice(SliceType* Slice)
{
	Damage.CopyToPoint(Slice->GetDamageDataImpl());
}

void FCsData_Beam_DamagePointImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Damage.CopyToPointAsValue(Slice->GetDamageDataImpl());
}

#undef SliceType

bool FCsData_Beam_DamagePointImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	if (!Damage.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsBeam::NData::NDamage::NPoint::FImplSlice::Name = FName("NCsBeam::NData::NDamage::NPoint::FImplSlice");

namespace NCsBeam
{
	namespace NData
	{
		namespace NDamage
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

							const FName DamagePoint = FName("DamagePoint");
						}
					}
				}

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
				{
					using namespace NCsBeam::NData::NDamage::NPoint::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(Object)

					#define DataHandlerType NCsData::NManager::NHandler::TData
					typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
					typedef NCsBeam::NData::IData DataType;
					typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;

					DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
					#undef DataHandlerType

					if (!DataHandler)
						return nullptr;

					typedef NCsBeam::NData::NDamage::IDamage DamageDataType;

					FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, DamageDataType>(Context, DataName);

					if (!Slice)
						return nullptr;

					// Check for properties matching interface: DamageDataType (NCsBeam::NData::NDamage::IDamage)
					typedef NCsProperty::FLibrary PropertyLibrary;

					bool Success = false;

					// Try FCsData_Beam_DamagePointImplSlice
					typedef FCsData_Beam_DamagePointImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::DamagePointSlice, nullptr))
					{
						SliceAsStruct->CopyToSlice(Slice);
						Success = true;
					}
					// Try individual properties
					else
					{
						FCsData_DamagePoint* DamagePointPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsData_DamagePoint>(Context, Object, Object->GetClass(), Name::DamagePoint, nullptr);

						if (DamagePointPtr)
						{
							DamagePointPtr->CopyToPoint(Slice->GetDamageDataImpl());
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							typedef NCsObject::FLibrary ObjectLibrary;

							Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: DamageDataType (NCsBeam::NData::NDamage::IDamage)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Beam_DamagePointImplSlice with name: DamagePointSlice."), *Context));
							Log(FString::Printf(TEXT("%s: - OR"), *Context));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_DamagePoint with name: DamagePoint."), *Context));
						}
					}
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					check(GetDamageDataImpl()->IsValidChecked(Context));
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
				{
					if (!GetDamageDataImpl()->IsValid(Context, Log))
						return false;
					return true;
				}
			}
		}
	}
}