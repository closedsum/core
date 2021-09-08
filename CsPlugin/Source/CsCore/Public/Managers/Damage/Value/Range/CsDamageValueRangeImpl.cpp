// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "CsCore.h"

const FName NCsDamage::NValue::NRange::FImpl::Name = FName("NCsDamage::NValue::NRange::FImpl");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			FImpl::FImpl() :
				InterfaceMap(),
				// IRange
				MinValue(0.0f),
				MaxValue(0.0f)
			{
				InterfaceMap.SetRoot<FImpl>(this);

				InterfaceMap.Add<IValue>(static_cast<IValue*>(this));
				InterfaceMap.Add<IRange>(static_cast<IRange*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
			}

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				MinValue = 0.0f;
				MaxValue = 0.0f;
			}

			#pragma endregion ICsReset
		}
	}
}