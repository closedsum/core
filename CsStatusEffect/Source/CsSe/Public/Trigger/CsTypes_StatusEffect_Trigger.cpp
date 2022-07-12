// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Trigger/CsTypes_StatusEffect_Trigger.h"
#include "CsSe.h"

// Library
#include "Library/CsLibrary_Valid.h"

// StatusEffectTriggerCondition
#pragma region

namespace NCsStatusEffectTriggerCondition
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(OnParentTrigger, "On Parent Trigger");
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(OnHit, "On Hit");
}

#pragma endregion StatusEffectTriggerCondition

// StatusEffectTriggerFrequency
#pragma region

namespace NCsStatusEffectTriggerFrequency
{
	namespace Ref
	{
		typedef EMCsStatusEffectTriggerFrequency EnumMapType;

		CSSE_API CS_ADD_TO_ENUM_MAP(Once);
		CSSE_API CS_ADD_TO_ENUM_MAP(Count);
		CSSE_API CS_ADD_TO_ENUM_MAP(Time);
		CSSE_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStatusEffectTriggerFrequency_MAX, "MAX");
	}

	CSSE_API const uint8 MAX = (uint8)Type::ECsStatusEffectTriggerFrequency_MAX;
}

namespace NCsStatusEffect
{
	namespace NTrigger
	{
		namespace NFrequency
		{
			namespace Ref
			{
				typedef EMFrequency EnumMapType;

				CSSE_API CS_ADD_TO_ENUM_MAP(Once);
				CSSE_API CS_ADD_TO_ENUM_MAP(Count);
				CSSE_API CS_ADD_TO_ENUM_MAP(Time);
				CSSE_API CS_ADD_TO_ENUM_MAP(Infinite);
				CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFrequency_MAX, "MAX");
			}
		}
	}
}

#pragma endregion StatusEffectTriggerFrequency

// StatusEffectTransferFrequency
#pragma region

namespace NCsStatusEffectTransferFrequency
{
	namespace Ref
	{
		typedef EMCsStatusEffectTransferFrequency EnumMapType;

		CSSE_API CS_ADD_TO_ENUM_MAP(None);
		CSSE_API CS_ADD_TO_ENUM_MAP(Once);
		CSSE_API CS_ADD_TO_ENUM_MAP(Count);
		CSSE_API CS_ADD_TO_ENUM_MAP(Time);
		CSSE_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStatusEffectTransferFrequency_MAX, "MAX");
	}

	CSSE_API const uint8 MAX = (uint8)Type::ECsStatusEffectTransferFrequency_MAX;
}

namespace NCsStatusEffect
{
	namespace NTransfer
	{
		namespace NFrequency
		{
			namespace Ref
			{
				typedef EMFrequency EnumMapType;

				CSSE_API CS_ADD_TO_ENUM_MAP(None);
				CSSE_API CS_ADD_TO_ENUM_MAP(Once);
				CSSE_API CS_ADD_TO_ENUM_MAP(Count);
				CSSE_API CS_ADD_TO_ENUM_MAP(Time);
				CSSE_API CS_ADD_TO_ENUM_MAP(Infinite);
				CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFrequency_MAX, "MAX");
			}
		}
	}
}

#pragma endregion StatusEffectTransferFrequency

// FCsStatusEffect_TriggerFrequencyParams
#pragma region

#define ParamsType NCsStatusEffect::NTrigger::NFrequency::FParams

void FCsStatusEffect_TriggerFrequencyParams::CopyToParams(ParamsType* Params)
{
	typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

	Params->SetType((FrequencyType*)(&Type));
	Params->SetDelay(&Delay);
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
	Params->SetTime(&Time);
}

void FCsStatusEffect_TriggerFrequencyParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

	Params->SetType((FrequencyType)Type);
	Params->SetDelay(Delay);
	Params->SetCount(Count);
	Params->SetInterval(Interval);
	Params->SetTime(Time);
}

#undef ParamsType

bool FCsStatusEffect_TriggerFrequencyParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsStatusEffectTriggerFrequency, Type)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Delay, 0.0f)

	// Once
	if (Type == ECsStatusEffectTriggerFrequency::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == ECsStatusEffectTriggerFrequency::Count)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsStatusEffectTriggerFrequency::Count."), *Context);

		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsStatusEffectTriggerFrequency::Count."), *Context);
	}
	// Time
	else
	if (Type == ECsStatusEffectTriggerFrequency::Time)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsStatusEffectTriggerFrequency::Time."), *Context);

		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsStatusEffectTriggerFrequency::Time."), *Context);
	}
	// Infinite
	else
	if (Type == ECsStatusEffectTriggerFrequency::Infinite)
	{
		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsStatusEffectTriggerFrequency::Infinite."), *Context);
	}
	return true;
}

bool FCsStatusEffect_TriggerFrequencyParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsStatusEffectTriggerFrequency, ECsStatusEffectTriggerFrequency, Type)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Delay, 0.0f)

	// Once
	if (Type == ECsStatusEffectTriggerFrequency::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == ECsStatusEffectTriggerFrequency::Count)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsStatusEffectTriggerFrequency::Count."), *Context));
			return false;
		}

		if (Interval < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be >= 0.0f if Type == ECsStatusEffectTriggerFrequency::Count."), *Context));
			return false;
		}
	}
	// Time
	else
	if (Type == ECsStatusEffectTriggerFrequency::Time)
	{
		if (Interval < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be >= 0.0f if Type == ECsStatusEffectTriggerFrequency::Time."), *Context));
			return false;
		}
	}
	// Infinite
	else
	if (Type == ECsStatusEffectTriggerFrequency::Infinite)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsStatusEffectTriggerFrequency::Infinite."), *Context));
			return false;
		}
	}
	return true;
}

namespace NCsStatusEffect
{
	namespace NTrigger
	{
		namespace NFrequency
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				typedef NCsStatusEffect::NTrigger::EMFrequency FrequencyMapType;
				typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

				CS_IS_ENUM_VALID_CHECKED(FrequencyMapType, GetType())

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetDelay(), 0.0f)

				// Once
				if (GetType() == FrequencyType::Once)
				{
					// No checks
				}
				// Count
				else
				if (GetType() == FrequencyType::Count)
				{
					checkf(GetCount() >= 1, TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Count."), *Context);

					checkf(GetInterval() >= 0.0f, TEXT("%s: GetInterval() MUST be >= 0.0f if GetType() == FrequencyType::Count."), *Context);
				}
				// Time
				else
				if (GetType() == FrequencyType::Time)
				{
					checkf(GetCount() >= 1, TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Time."), *Context);

					checkf(GetInterval() >= 0.0f, TEXT("%s: GetInterval() MUST be >= 0.0f if GetType() == FrequencyType::Time."), *Context);
				}
				// Infinite
				else
				if (GetType() == FrequencyType::Infinite)
				{
					checkf(GetInterval() >= 0.0f, TEXT("%s: GetInterval() MUST be >= 0.0f if GetType() == FrequencyType::Infinite."), *Context);
				}
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) const
			{
				typedef NCsStatusEffect::NTrigger::EMFrequency FrequencyMapType;
				typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

				CS_IS_ENUM_VALID(FrequencyMapType, FrequencyType, GetType())

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Delay, 0.0f)

				// Once
				if (GetType() == FrequencyType::Once)
				{
					// No checks
				}
				// Count
				else
				if (GetType() == FrequencyType::Count)
				{
					if (GetCount() < 1)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Count."), *Context));
						return false;
					}

					if (GetInterval() < 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be >= 0.0f if GetType() == FrequencyType::Count."), *Context));
						return false;
					}
				}
				// Time
				else
				if (GetType() == FrequencyType::Time)
				{
					if (GetCount() < 1)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if Type == FrequencyType::Time."), *Context));
						return false;
					}

					if (GetInterval() < 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be >= 0.0f if GetType() == FrequencyType::Time."), *Context));
						return false;
					}
				}
				// Infinite
				else
				if (GetType() == FrequencyType::Infinite)
				{
					if (GetInterval() <= 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be > 0.0f if GetType() == FrequencyType::Infinite."), *Context));
						return false;
					}
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsStatusEffect_TriggerFrequencyParams

// FCsStatusEffect_TransferFrequencyParams
#pragma region

#define ParamsType NCsStatusEffect::NTransfer::NFrequency::FParams

void FCsStatusEffect_TransferFrequencyParams::CopyToParams(ParamsType* Params)
{
	typedef NCsStatusEffect::NTransfer::EFrequency FrequencyType;

	Params->SetType((FrequencyType*)(&Type));
	Params->SetCount(&Count);
	Params->SetTime(&Time);
}

void FCsStatusEffect_TransferFrequencyParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsStatusEffect::NTransfer::EFrequency FrequencyType;

	Params->SetType((FrequencyType)Type);
	Params->SetCount(Count);
	Params->SetTime(Time);
}

#undef ParamsType

bool FCsStatusEffect_TransferFrequencyParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsStatusEffectTransferFrequency, Type)

	// Once
	if (Type == ECsStatusEffectTransferFrequency::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == ECsStatusEffectTransferFrequency::Count)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsStatusEffectTransferFrequency::Count."), *Context);
	}
	// Time
	else
	if (Type == ECsStatusEffectTransferFrequency::Time)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsStatusEffectTransferFrequency::Time."), *Context);
	}
	// Infinite
	else
	if (Type == ECsStatusEffectTransferFrequency::Infinite)
	{
	}
	return true;
}

bool FCsStatusEffect_TransferFrequencyParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsStatusEffectTransferFrequency, ECsStatusEffectTransferFrequency, Type)

	// Once
	if (Type == ECsStatusEffectTransferFrequency::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == ECsStatusEffectTransferFrequency::Count)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsStatusEffectTransferFrequency::Count."), *Context));
			return false;
		}
	}
	// Time
	else
	if (Type == ECsStatusEffectTransferFrequency::Time)
	{
	}
	// Infinite
	else
	if (Type == ECsStatusEffectTransferFrequency::Infinite)
	{
	}
	return true;
}

namespace NCsStatusEffect
{
	namespace NTransfer
	{
		namespace NFrequency
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				typedef NCsStatusEffect::NTransfer::EMFrequency FrequencyMapType;
				typedef NCsStatusEffect::NTransfer::EFrequency FrequencyType;

				CS_IS_ENUM_VALID_CHECKED(FrequencyMapType, GetType())

				// Once
				if (GetType() == FrequencyType::Once)
				{
					// No checks
				}
				// Count
				else
				if (GetType() == FrequencyType::Count)
				{
					checkf(GetCount() >= 1, TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Count."), *Context);
				}
				// Time
				else
				if (GetType() == FrequencyType::Time)
				{
					checkf(GetCount() >= 1, TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Time."), *Context);

				}
				// Infinite
				else
				if (GetType() == FrequencyType::Infinite)
				{
				}
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) const
			{
				typedef NCsStatusEffect::NTransfer::EMFrequency FrequencyMapType;
				typedef NCsStatusEffect::NTransfer::EFrequency FrequencyType;

				CS_IS_ENUM_VALID(FrequencyMapType, FrequencyType, GetType())

				// Once
				if (GetType() == FrequencyType::Once)
				{
					// No checks
				}
				// Count
				else
				if (GetType() == FrequencyType::Count)
				{
					if (GetCount() < 1)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Count."), *Context));
						return false;
					}
				}
				// Time
				else
				if (GetType() == FrequencyType::Time)
				{
					if (GetCount() < 1)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if Type == FrequencyType::Time."), *Context));
						return false;
					}
				}
				// Infinite
				else
				if (GetType() == FrequencyType::Infinite)
				{
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsStatusEffect_TransferFrequencyParams