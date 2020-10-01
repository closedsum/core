// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "CsCore.h"

const FName NCsDamage::NValue::NPoint::FImpl::Name = FName("NCsDamage::NValue::NPoint::FImpl");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(),
				// IPoint
				Value(0.0f)
			{
				// ICsGetInterfaceMap
				InterfaceMap.SetRootName(FImpl::Name);

				InterfaceMap.Add<IValue>(static_cast<IValue*>(this));
				InterfaceMap.Add<IPoint>(static_cast<IPoint*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
			}

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				Value = 0.0f;
			}

			#pragma endregion ICsReset
		}
	}
}