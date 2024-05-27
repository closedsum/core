// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsGameplayAbilitiesRegisterStructOpsData.h"

#include "CsStructOps_Data.h"
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
			namespace NData
			{
				void FRegister::Execute()
				{
					typedef NCsStruct::NOps::NData::FTool ToolType;

				#define REGISTER_UNLOAD_FN(__Struct) ToolType::Get().RegisterUnloadFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_Data_Unload)

					// Attribute
					{
						REGISTER_UNLOAD_FN(FCsAttributeSet);
					}
					// Ability
					{
						REGISTER_UNLOAD_FN(FCsGameplayAbility);
						REGISTER_UNLOAD_FN(FCsGameplayAbilityInfo);
					}
					// Effect
					{
						REGISTER_UNLOAD_FN(FCsGameplayEffect);
					}

				#undef REGISTER_UNLOAD_FN
				}
			}
		}
	}
}