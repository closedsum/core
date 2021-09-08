// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
			{
				// ICsGetInterfaceMap
				InterfaceMap.SetRoot<FImpl>(this);

				InterfaceMap.Add<IValue>(static_cast<IValue*>(this));
				InterfaceMap.Add<IPoint>(static_cast<IPoint*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));

				CS_CTOR_SET_MEMBER_PROXY(Value);
			}

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Value, 0.0f)
			}

			#pragma endregion ICsReset
		}
	}
}