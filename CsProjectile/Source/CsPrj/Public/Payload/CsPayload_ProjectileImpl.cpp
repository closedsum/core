// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileImpl.h"

#include "Containers/CsInterfaceMap.h"

// FCsPayload_Projectile
#pragma region

#define PayloadType NCsProjectile::NPayload::FImpl
void FCsPayload_Projectile::CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const
{
#undef PayloadType
	
	Payload->Instigator = Instigator;
	Payload->Owner = Owner;
	Payload->Parent = Parent;
	//Payload->Time = Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	Payload->Type		= Type;
	Payload->Location	= Location;
	Payload->Direction	= Direction;
}

bool FCsPayload_Projectile::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsPayload_Projectile::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsPayload_Projectile

const FName NCsProjectile::NPayload::FImpl::Name = FName("NCsProjectile::NPayload::FImpl");;

namespace NCsProjectile
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
			// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
			Type(),
			Direction(0.0f),
			Location(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsProjectile::NPayload::IPayload ProjectilePayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<ProjectilePayloadType>(static_cast<ProjectilePayloadType*>(this));
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
			// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
			Type = EMCsProjectile::Get().GetMAX();
			Direction = FVector::ZeroVector;
			Location = FVector::ZeroVector;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}