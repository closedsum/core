// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#pragma once

// DigitalAgreement
#pragma region

UENUM(BlueprintType)
enum class ECsDigitalAgreement : uint8
{
	UserAgreement				UMETA(DisplayName = "User Agreement"),
	PrivacyAndCookiePolicy		UMETA(DisplayName = "Privacy and Cookie Policy"),
	ECsDigitalAgreement_MAX		UMETA(Hidden),
};

struct CSONLINE_API EMCsDigitalAgreement : public TCsEnumMap<ECsDigitalAgreement>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDigitalAgreement, ECsDigitalAgreement)
};

namespace NCsDigitalAgreement
{
	typedef ECsDigitalAgreement Type;

	namespace Ref
	{
		extern CSONLINE_API const Type UserAgreement;
		extern CSONLINE_API const Type PrivacyAndCookiePolicy;
		extern CSONLINE_API const Type ECsDigitalAgreement_MAX;
	}

	extern CSONLINE_API const uint8 MAX;
}

#pragma endregion DigitalAgreement

struct CSONLINE_API FCsDigitalAgreementState
{
private:

	bool bAccepted;

public:

	FCsDigitalAgreementState() :
		bAccepted(false)
	{
	}

	FORCEINLINE bool IsAccepted() const
	{
		return bAccepted;
	}

	FORCEINLINE void Accept()
	{
		bAccepted = true;
	}

	FORCEINLINE void DoNotAccept()
	{
		bAccepted = false;
	}

	void Reset()
	{
		bAccepted = false;
	}
};