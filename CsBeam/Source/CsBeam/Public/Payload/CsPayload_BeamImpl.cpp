// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_BeamImpl.h"

#include "Containers/CsInterfaceMap.h"

// FCsPayload_Beam
#pragma region

#define PayloadType NCsBeam::NPayload::FImpl
void FCsPayload_Beam::CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const
{
#undef PayloadType
	
	Payload->Instigator = Instigator;
	Payload->Owner = Owner;
	Payload->Parent = Parent;
	//Payload->Time = Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	Payload->Type = Type;
	Payload->Location = Location;
	Payload->Direction = Direction;
}

bool FCsPayload_Beam::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsPayload_Beam::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsPayload_Beam

const FName NCsBeam::NPayload::FImpl::Name = FName("NCsBeam::NPayload::FImpl");;

namespace NCsBeam
{
	namespace NPayload
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// BeamPayloadType (NCsBeam::NPayload::IPayload)
			Type(),
			Direction(0.0f),
			Location(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsBeam::NPayload::IPayload BeamPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<BeamPayloadType>(static_cast<BeamPayloadType*>(this));
		}

		FImpl::~FImpl()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region

		void FImpl::Reset()
		{
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
			// BeamPayloadType (NCsBeam::NPayload::IPayload)
			Type = EMCsBeam::Get().GetMAX();
			Direction = FVector::ZeroVector;
			Location = FVector::ZeroVector;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}