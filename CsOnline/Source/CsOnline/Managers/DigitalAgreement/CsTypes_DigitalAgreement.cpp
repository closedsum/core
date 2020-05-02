// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/DigitalAgreement/CsTypes_DigitalAgreement.h"

// DigitalAgreement
#pragma region

namespace NCsDigitalAgreement
{
	namespace Ref
	{
		CSONLINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDigitalAgreement, UserAgreement, "User Agreement");
		CSONLINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDigitalAgreement, PrivacyAndCookiePolicy, "Privacy and Cookie Policy");
		CSONLINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDigitalAgreement, ECsDigitalAgreement_MAX, "MAX");
	}

	CSONLINE_API const uint8 MAX = (uint8)Type::ECsDigitalAgreement_MAX;
}

#pragma endregion DigitalAgreement