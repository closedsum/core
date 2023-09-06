// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Payload/CsPayload_BeamImpl.h"

#include "Containers/CsInterfaceMap.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPayload_Beam
#pragma region

#define PayloadType NCsBeam::NPayload::FImpl
void FCsPayload_Beam::CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const
{
#undef PayloadType
	
	Payload->UpdateType	 = (NCsPooledObject::EUpdate)UpdateType;
	Payload->Instigator = Instigator;
	Payload->Owner = Owner;
	Payload->Parent = Parent;
	//Payload->Time = Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	Payload->Type = Type;
	Payload->AttachRules = AttachRules;
	Payload->Location = Location;
	Payload->Direction = Direction;
	Payload->Scale = Scale;
}

bool FCsPayload_Beam::IsValidChecked(const FString& Context) const
{
	check(EMCsBeam::Get().IsValidEnumChecked(Context, Type));

	//CS_IS_VECTOR_ZERO_CHECKED(Direction)

	CS_IS_VECTOR_ZERO_CHECKED(Scale)
	return true;
}

bool FCsPayload_Beam::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsBeam, FECsBeam, Type)

	//CS_IS_VECTOR_ZERO(Direction)

	CS_IS_VECTOR_ZERO(Scale)
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
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// BeamPayloadType (NCsBeam::NPayload::IPayload)
			Type(),
			AttachRules(FCsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Location(0.0f),
			Direction(0.0f),
			Scale(0.0f)			
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
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
			// BeamPayloadType (NCsBeam::NPayload::IPayload)
			Type = EMCsBeam::Get().GetMAX();
			AttachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Location = FVector3f::ZeroVector;
			Direction = FVector3f::ZeroVector;
			Scale = FVector3f::OneVector;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}