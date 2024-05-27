// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsGameplayAbilitiesRegisterStructOpsIsValid.h"

#include "CsStructOps_IsValid.h"
// Structs
#include "Attribute/CsAttributeSet.h"
#include "Ability/CsTypes_GameplayAbility.h"
#include "Effect/CsGameplayEffect.h"

namespace NCsGameplayAbilities
{
	namespace NStruct
	{
		namespace NOps
		{
			namespace NIsValid
			{
				void FRegister::Execute()
				{
					typedef NCsStruct::NOps::NIsValid::FTool ToolType;

				#define REGISTER_IS_VALID_FNS(__Struct) ToolType::Get().RegisterIsValidCheckedFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsValidChecked); \
					ToolType::Get().RegisterIsValidFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsValid); \
					ToolType::Get().RegisterIsTopValidCheckedFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsTopValidChecked); \
					ToolType::Get().RegisterIsTopValidFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsTopValid);

					// Attribute
					{
						REGISTER_IS_VALID_FNS(FCsAttributeSet);
					}
					// Ability
					{
						REGISTER_IS_VALID_FNS(FCsGameplayAbility);
						REGISTER_IS_VALID_FNS(FCsGameplayAbilityInfo);
					}
					// Effect
					{
						REGISTER_IS_VALID_FNS(FCsGameplayEffect);
					}

				#undef REGISTER_IS_VALID_FNS
				}
			}
		}
	}
}