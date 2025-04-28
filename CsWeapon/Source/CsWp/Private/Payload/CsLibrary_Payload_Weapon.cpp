// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Weapon.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Payload/CsPayload_WeaponImplSlice.h"

namespace NCsWeapon
{
	namespace NPayload
	{
		namespace NLibrary
		{
			bool FLibrary::CopyChecked(const FString& Context, const PayloadType* From, PayloadType* To)
			{
				bool Result = false;

				// PooledObject
				{
					using SliceType = NCsPooledObject::NPayload::FImplSlice;
					using PayloadInterfaceType = NCsPooledObject::NPayload::IPayload;

					Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
				}
				// Weapon
				{
					using SliceType = NCsWeapon::NPayload::NImplSlice::FImplSlice;
					using PayloadInterfaceType = NCsWeapon::NPayload::IPayload;

					Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
				}
				return Result;
			}
		}
	}
}