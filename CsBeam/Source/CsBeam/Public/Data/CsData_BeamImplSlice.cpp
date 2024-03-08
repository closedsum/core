// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsData_BeamImplSlice.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"

#define SliceType NCsBeam::NData::FImplSlice

SliceType* FCsData_BeamImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_BeamImplSlice::SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_BeamImplSlice::SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return nullptr;

	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
	typedef NCsBeam::NData::IData DataType;
	typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;

	SliceType* Slice = DataHandler->SafeConstructData<SliceType, EMCsBeam>(Context, Name);

	return Slice;
}

void FCsData_BeamImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetLifeTime(&LifeTime);
}

void FCsData_BeamImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetLifeTime(LifeTime);
}

#undef SliceType

bool FCsData_BeamImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(LifeTime, 0.0f)

	return true;
}

const FName NCsBeam::NData::FImplSlice::Name = FName("NCsBeam::NData::FImplSlice");

namespace NCsBeam
{
	namespace NData
	{
		namespace NImplSlice
		{
			namespace NCached
			{
				namespace Name
				{
					const FName BeamSlice = FName("BeamSlice");

					const FName LifeTime = FName("LifeTime");
				}
			}
		}

		/*static*/ FImplSlice* FImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			using namespace NCsBeam::NData::NImplSlice::NCached;

			CS_IS_PTR_NULL_RET_NULL(Object)

			FImplSlice* Slice = SafeConstruct_Internal(Context, WorldContext, DataName, Log);

			if (!Slice)
				return nullptr;

			// Check for properties matching interface: BeamDataType (NCsBeam::NData::IData)
			typedef NCsProperty::FLibrary PropertyLibrary;

			bool Success = false;

			// Try FCsData_BeamImplSlice
			if (FCsData_BeamImplSlice* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<FCsData_BeamImplSlice>(Context, Object, Object->GetClass(), Name::BeamSlice, nullptr))
			{
				SliceAsStruct->CopyToSlice(Slice);
				Success = true;
			}
			// Try individual properties
			else
			{
				#define CS_TEMP_GET_SAFE_FLOAT_PTR(__PropertyName) PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)

				float* LifeTimePtr		= CS_TEMP_GET_SAFE_FLOAT_PTR(LifeTime);

				#undef CS_TEMP_GET_SAFE_FLOAT_PTR

				if (LifeTimePtr)
				{
					Slice->SetLifeTime(LifeTimePtr);
					Success = true;
				}
			}

			if (!Success)
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsBeam::NData::IData."), *Context));
					Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_BeamImplSlice with name: BeamSlice."), *Context));
					Log(FString::Printf(TEXT("%s: - OR"), *Context));
					Log(FString::Printf(TEXT("%s: - Failed to get float property with name: LifeTime."), *Context));
				}
			}

			// NOTE: If this technique is to be used in a shipping build, this will need to be slightly altered to
			//		 allow destroying the object when the data needs to be "unloaded"
			typedef NCsData::NManager::FLibrary DataManagerLibrary;

			DataManagerLibrary::AddDataCompositionObject_Loaded_Checked(Context, WorldContext, FName(*DataName), Object, FImplSlice::Name);

			return Slice;
		}

		/*static*/ FImplSlice* FImplSlice::SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& DataName, void(*Log)(const FString&) /*=&FCLog::Warning*/)
		{
			#define DataHandlerType NCsData::NManager::NHandler::TData
			typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
			typedef NCsBeam::NData::IData DataType;
			typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;
	
			DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
			#undef DataHandlerType

			if (!DataHandler)
				return nullptr;

			FImplSlice* Slice = DataHandler->SafeConstructData<FImplSlice, EMCsBeam>(Context, DataName);

			return Slice;
		}

		bool FImplSlice::IsValidChecked(const FString& Context) const
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetLifeTime(), 0.0f)
			return true;
		}

		bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetLifeTime(), 0.0f)
			return true;
		}
	}
}