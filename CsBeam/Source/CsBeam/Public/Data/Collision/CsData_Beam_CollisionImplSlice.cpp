// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Collision/CsData_Beam_CollisionImplSlice.h"

// Library
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"

#define SliceType NCsBeam::NData::NCollision::FImplSlice

SliceType* FCsData_Beam_CollisionImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_CollisionImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_CollisionImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
	typedef NCsBeam::NData::IData DataType;
	typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;
	
	typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, CollisionDataType>(Context, Name);
	
	return Slice;
}

void FCsData_Beam_CollisionImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetCollisionPreset(&Preset);
	Slice->ConditionalSetCollisionShape(Shape.ConstructShape());
	FrequencyParams.CopyToParams(Slice->GetCollisionFrequencyParamsPtr());
	Slice->SetCollisionCount(&CollisionCount);
	Slice->SetIgnoreCollidingObjectAfterCollision(&bIgnoreCollidingObjectAfterCollision);
	Slice->SetIgnoreCollidingObjectClasses(&IgnoreCollidingObjectClasses);
}

void FCsData_Beam_CollisionImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetCollisionPreset(Preset);
	Slice->ConditionalSetCollisionShape(Shape.ConstructShapeAsValue());
	FrequencyParams.CopyToParamsAsValue(Slice->GetCollisionFrequencyParamsPtr());
	Slice->SetCollisionCount(CollisionCount);
	Slice->SetIgnoreCollidingObjectAfterCollision(bIgnoreCollidingObjectAfterCollision);
	Slice->SetIgnoreCollidingObjectClasses(IgnoreCollidingObjectClasses);
}

#undef SliceType

bool FCsData_Beam_CollisionImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	if (!Preset.IsValid(Context, Log))
		return false;

	CS_IS_VALID_CHECKED(Shape);

	CS_IS_INT_GREATER_THAN_OR_EQUAL(CollisionCount, 0)

	const int32 Count = IgnoreCollidingObjectClasses.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const TSubclassOf<UObject>& O = IgnoreCollidingObjectClasses[I];

		if (!O.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: IgnoreCollidingObjectClasses[%d] is NULL."), *Context, I));
		}
	}
	return true;
}

const FName NCsBeam::NData::NCollision::FImplSlice::Name = FName("NCsBeam::NData::NCollision::FImplSlice");

namespace NCsBeam
{
	namespace NData
	{
		namespace NCollision
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName CollisionSlice = FName("CollisionSlice");

						const FName CollisionPreset = FName("CollisionPreset");
						const FName CollisionShape = FName("CollisionShape");
						const FName CollisionFrequencyParams = FName("CollisionFrequencyParams");
						const FName CollisionCount = FName("CollisionCount");
						const FName bIgnoreCollidingObjectAfterCollision = FName("bIgnoreCollidingObjectAfterCollision");
						const FName IgnoreCollidingObjectClasses = FName("IgnoreCollidingObjectClasses");
					}
				}
			}

			/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
			{
				using namespace NCsBeam::NData::NCollision::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(Object)

				#define DataHandlerType NCsData::NManager::NHandler::TData
				typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
				typedef NCsBeam::NData::IData DataType;
				typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;

				DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
				#undef DataHandlerType

				if (!DataHandler)
					return nullptr;

				typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

				FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, CollisionDataType>(Context, DataName);

				if (!Slice)
					return nullptr;

				// Check for properties matching interface: CollisionDataType (NCsBeam::NData::NCollision::ICollision)
				typedef NCsProperty::FLibrary PropertyLibrary;

				bool Success = false;

				// Try FCsData_Beam_CollisionImplSlice
				typedef FCsData_Beam_CollisionImplSlice StructSliceType;

				if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::CollisionSlice, nullptr))
				{
					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}
				// Try individual properties
				else
				{
					FCsCollisionPreset* CollisionPresetPtr			= PropertyLibrary::GetStructPropertyValuePtr<FCsCollisionPreset>(Context, Object, Object->GetClass(), Name::CollisionPreset, nullptr);
					FCsBeamCollisionShape* CollisionShapePtr		= PropertyLibrary::GetStructPropertyValuePtr<FCsBeamCollisionShape>(Context, Object, Object->GetClass(), Name::CollisionShape, nullptr);
					FCsBeamCollisionFrequencyParams* CollisionFrequencyParamsPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsBeamCollisionFrequencyParams>(Context, Object, Object->GetClass(), Name::CollisionFrequencyParams, nullptr);
					int32* CollisionCountPtr						= PropertyLibrary::GetIntPropertyValuePtr(Context, Object, Object->GetClass(), Name::CollisionCount, nullptr);
					bool* bIgnoreCollidingObjectAfterCollisionPtr	= PropertyLibrary::GetBoolPropertyValuePtr(Context, Object, Object->GetClass(), Name::bIgnoreCollidingObjectAfterCollision, nullptr);

					// TODO: Need to implement getting TArray<TSubclassOf<ClassType>>

					if (CollisionPresetPtr &&
						CollisionShapePtr &&
						CollisionFrequencyParamsPtr &&
						CollisionCountPtr &&
						bIgnoreCollidingObjectAfterCollisionPtr)
					{
						Slice->SetCollisionPreset(CollisionPresetPtr);
						Slice->ConditionalSetCollisionShape(CollisionShapePtr->ConstructShape());
						CollisionFrequencyParamsPtr->CopyToParamsAsValue(Slice->GetCollisionFrequencyParamsPtr());
						Slice->SetCollisionCount(CollisionCountPtr);
						Slice->SetIgnoreCollidingObjectAfterCollision(bIgnoreCollidingObjectAfterCollisionPtr);

						Success = true;
					}
				}

				if (!Success)
				{
					if (Log)
					{
						typedef NCsObject::FLibrary ObjectLibrary;

						Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: CollisionDataType (NCsBeam::NData::NCollision::ICollision)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Beam_CollisionImplSlice with name: CollisionSlice."), *Context));
						Log(FString::Printf(TEXT("%s: - OR"), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsCollisionPreset with name: CollisionPreset."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsBeamCollisionShape with name: CollisionShape."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsBeamCollisionFrequencyParams with name: CollisionFrequencyParams."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get int property with name: CollisionCount."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bIgnoreCollidingObjectAfterCollision."), *Context));
						// Log(FString::Printf(TEXT("%s: - Failed to get array property of type: TSubclassOf<UObject> with name: IgnoreCollidingObjectClasses."), *Context));
					}
				}
				return Slice;
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				CS_IS_VALID_CHECKED(GetCollisionPreset());

				check(GetCollisionShape()->IsValidChecked(Context));

				CS_IS_VALID_CHECKED(GetCollisionFrequencyParams());

				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCollisionCount(), 0)

				CS_IS_ARRAY_ANY_NULL_CHECKED(GetIgnoreCollidingObjectClasses(), UObject)

				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_VALID(GetCollisionPreset())

				if (!GetCollisionShape()->IsValid(Context, Log))
					return false;

				CS_IS_VALID(GetCollisionFrequencyParams());

				CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCollisionCount(), 0)

				CS_IS_ARRAY_ANY_NULL(GetIgnoreCollidingObjectClasses(), UObject)

				return true;
			}
		}
	}
}