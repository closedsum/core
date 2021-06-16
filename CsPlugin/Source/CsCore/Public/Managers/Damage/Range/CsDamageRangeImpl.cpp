// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsDamageRangeImpl.h"
#include "CsCore.h"

const FName NCsDamage::NRange::FImpl::Name = FName("NCsDamage::NRange::FImpl");

namespace NCsDamage
{
	namespace NRange
	{
		FImpl::FImpl() :
			InterfaceMap(),
			// IRange
			MinRange(0.0f),
			MaxRange(0.0f)
		{
			InterfaceMap.SetRoot<FImpl>(this);

			InterfaceMap.Add<IRange>(static_cast<IRange*>(this));
			InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
		}

		// ICsReset
		#pragma region

		void FImpl::Reset()
		{
			MinRange = 0.0f;
			MaxRange = 0.0f;
		}

		#pragma endregion ICsReset
	}
}