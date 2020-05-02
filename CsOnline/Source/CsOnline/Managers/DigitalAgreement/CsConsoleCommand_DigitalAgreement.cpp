// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/DigitalAgreement/CsConsoleCommand_DigitalAgreement.h"
#include "CsOnline.h"

// Library
#include "Library/CsLibrary_String.h"
// Managers
#include "Managers/DigitalAgreement/CsManager_DigitalAgreement.h"

// Cached
#pragma region

namespace NCsConsoleCommandDigitalAgreement
{
	namespace Cmd
	{
		// DigitalAgreement
		const FString DigitalAgreementReset = TEXT("digitalagreementreset");
		const FString DigitalAgreement_Reset = TEXT("digitalagreement reset");
		const FString DigitalAgreementResetAll = TEXT("digitalagreementresetall");
		const FString DigitalAgreement_ResetAll = TEXT("digitalagreement resetall");
		const FString DigitalAgreement_UA_Reset = TEXT("digitalagreement ua accept");
		const FString DigitalAgreement_PCP_Reset = TEXT("digitalagreement pcp accept");

		const FString DigitalAgreementAccept = TEXT("digitalagreementaccept");
		const FString DigitalAgreement_Accept = TEXT("digitalagreement accept");
		const FString DigitalAgreement_UA_Accept = TEXT("digitalagreement ua accept");
		const FString DigitalAgreement_PCP_Accept = TEXT("digitalagreement pcp accept");

		const FString DigitalAgreementDoNotAccept = TEXT("digitalagreementdonotaccept");
		const FString DigitalAgreement_DoNotAccept = TEXT("digitalagreement donotaccept");
		const FString DigitalAgreement_UA_DoNotAccept = TEXT("digitalagreement ua donotaccept");
		const FString DigitalAgreement_PCP_DoNotAccept = TEXT("digitalagreement pcp donotaccept");
		// UserAgreement
		const FString UserAgreementReset = TEXT("useragreementreset");
		const FString UserAgreement_Reset = TEXT("useragreement reset");

		const FString UserAgreementAccept = TEXT("useragreementaccept");
		const FString UserAgreement_Accept = TEXT("useragreement accept");

		const FString UserAgreementDoNotAccept = TEXT("useragreementdonotaccept");
		const FString UserAgreement_DoNotAccept = TEXT("useragreement donotaccept");
		// PrivacyAndCookiePolicy
		const FString PrivacyAndCookiePolicyReset = TEXT("privacyandcookiepolicyreset");
		const FString PrivacyAndCookiePolicy_Reset = TEXT("privacyandcookiepolicy reset");

		const FString PrivacyAndCookiePolicyAccept = TEXT("privacyandcookiepolicyaccept");
		const FString PrivacyAndCookiePolicy_Accept = TEXT("privacyandcookiepolicy accept");

		const FString PrivacyAndCookiePolicyDoNotAccept = TEXT("privacyandcookiepolicydonotaccept");
		const FString PrivacyAndCookiePolicy_DoNotAccept = TEXT("privacyandcookiepolicy donotaccept");
	}
}

#pragma endregion Cached

FCsConsoleCommand_DigitalAgreement::FCsConsoleCommand_DigitalAgreement(UObject* InRoot)
{
	MyRoot = InRoot;
}

bool FCsConsoleCommand_DigitalAgreement::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out /*=*GLog*/)
{
	// DigitalAgreementReset | DigitalAgreement Reset | DigitalAgreementResetAll | DigitalAgreement ResetAll 
	// DigitalAgreement UA Reset | DigitalAgreement PCP Reset
	if (Exec_DigitalAgreementReset(Cmd))
		return true;
	// DigitalAgreementAccept | DigitalAgreement Accept | DigitalAgreement UA Accept | DigitalAgreement PCP Accept
	if (Exec_DigitalAgreementAccept(Cmd))
		return true;
	// DigitalAgreementDoNotAccept | DigitalAgreement DoNotAccept | DigitalAgreement UA DoNotAccept | DigitalAgreement PCP DoNotAccept
	if (Exec_DigitalAgreementDoNotAccept(Cmd))
		return true;
	// UserAgreementReset | UserAgreement Reset
	if (Exec_UserAgreementReset(Cmd))
		return true;
	// UserAgreementAccept | UserAgreement Accept
	if (Exec_UserAgreementAccept(Cmd))
		return true;
	// UserAgreementDoNotAccept | UserAgreement DoNotAccept
	if (Exec_UserAgreementDoNotAccept(Cmd))
		return true;
	// PrivacyAndCookiePolicyReset | PrivacyAndCookiePolicy Reset
	if (Exec_PrivacyAndCookiePolicyReset(Cmd))
		return true;
	// PrivacyAndCookiePolicyAccept | PrivacyAndCookiePolicy Accept
	if (Exec_PrivacyAndCookiePolicyAccept(Cmd))
		return true;
	// PrivacyAndCookiePolicyDoNotAccept | PrivacyAndCookiePolicy DoNotAccept
	if (Exec_PrivacyAndCookiePolicyDoNotAccept(Cmd))
		return true;
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_DigitalAgreementReset(const TCHAR* Cmd)
{
	bool Match = false;
	bool All = false;
	bool UA = false;
	bool PCP = false;

	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// DigitalAgreementReset | DigitalAgreement Reset | DigitalAgreementResetAll | DigitalAgreement ResetAll
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreementReset ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_Reset ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreementResetAll ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_ResetAll)
	{
		Match = true;
		All = true;
	}
	// DigitalAgreement UA Reset
	else
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_UA_Reset)
	{
		Match = true;
		UA = true;
	}
	// DigitalAgreement PCP Reset
	else
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_PCP_Reset)
	{
		Match = true;
		PCP = true;
	}

	if (Match)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_DigitalAgreementReset: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		if (All)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->ResetAll();
		}
		// User Agreement
		else
		if (UA)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->Reset(ECsDigitalAgreement::UserAgreement);
		}
		// Privacy and Cookie Policy
		else
		if (PCP)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->Reset(ECsDigitalAgreement::PrivacyAndCookiePolicy);
		}
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_DigitalAgreementAccept(const TCHAR* Cmd)
{
	bool Match = false;
	bool UA = false;
	bool PCP = false;

	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// DigitalAgreementAccept | DigitalAgreement Accept
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreementAccept ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_Accept)
	{
		Match = true;
		UA = true;
		PCP = true;
	}
	// DigitalAgreement UA Accept
	else
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_UA_Accept)
	{
		Match = true;
		UA = true;
	}
	// DigitalAgreement PCP Accept
	else
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_PCP_Accept)
	{
		Match = true;
		PCP = true;
	}

	if (Match)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_DigitalAgreementAccept: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		// User Agreement
		if (UA)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->Accept(ECsDigitalAgreement::UserAgreement);
		}
		// Privacy and Cookie Policy
		if (PCP)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->Accept(ECsDigitalAgreement::PrivacyAndCookiePolicy);
		}
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_DigitalAgreementDoNotAccept(const TCHAR* Cmd)
{
	bool Match = false;
	bool UA = false;
	bool PCP = false;

	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// DigitalAgreementDoNotAccept | DigitalAgreement DoNotAccept
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreementDoNotAccept ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_DoNotAccept)
	{
		Match = true;
		UA = true;
		PCP = true;
	}
	// DigitalAgreement UA DoNotAccept
	else
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_UA_DoNotAccept)
	{
		Match = true;
		UA = true;
	}
	// DigitalAgreement PCP DoNotAccept
	else
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::DigitalAgreement_PCP_DoNotAccept)
	{
		Match = true;
		PCP = true;
	}

	if (Match)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_DigitalAgreementDoNotAccept: MyRoot is NULL."));
			return false;
		}

		// User Agreement
		if (UA)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->DoNotAccept(ECsDigitalAgreement::UserAgreement);
		}
		// Privacy and Cookie Policy
		if (PCP)
		{
			UCsManager_DigitalAgreement::Get(MyRoot)->DoNotAccept(ECsDigitalAgreement::PrivacyAndCookiePolicy);
		}
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_UserAgreementReset(const TCHAR* Cmd)
{
	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// UserAgreementReset | UserAgreement Reset
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::UserAgreementReset ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::UserAgreement_Reset)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_UserAgreementReset: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		UCsManager_DigitalAgreement::Get(MyRoot)->Reset(ECsDigitalAgreement::UserAgreement);
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_UserAgreementAccept(const TCHAR* Cmd)
{
	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// UserAgreementAccept | UserAgreement Accept
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::UserAgreementAccept ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::UserAgreement_Accept)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_UserAgreementAccept: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		UCsManager_DigitalAgreement::Get(MyRoot)->Accept(ECsDigitalAgreement::UserAgreement);
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_UserAgreementDoNotAccept(const TCHAR* Cmd)
{
	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// UserAgreementDoNotAccept | UserAgreement DoNotAccept
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::UserAgreementAccept ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::UserAgreement_Accept)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_UserAgreementDoNotAccept: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		UCsManager_DigitalAgreement::Get(MyRoot)->DoNotAccept(ECsDigitalAgreement::UserAgreement);
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_PrivacyAndCookiePolicyReset(const TCHAR* Cmd)
{
	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// PrivacyAndCookiePolicyReset | PrivacyAndCookiePolicy Reset
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::PrivacyAndCookiePolicyReset ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::PrivacyAndCookiePolicy_Reset)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_PrivacyAndCookiePolicyReset: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		UCsManager_DigitalAgreement::Get(MyRoot)->Reset(ECsDigitalAgreement::PrivacyAndCookiePolicy);
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_PrivacyAndCookiePolicyAccept(const TCHAR* Cmd)
{
	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// PrivacyAndCookiePolicyAccept | PrivacyAndCookiePolicy Accept
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::PrivacyAndCookiePolicyAccept ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::PrivacyAndCookiePolicy_Accept)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_PrivacyAndCookiePolicyAccept: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		UCsManager_DigitalAgreement::Get(MyRoot)->Accept(ECsDigitalAgreement::PrivacyAndCookiePolicy);
		return true;
	}
	return false;
}

bool FCsConsoleCommand_DigitalAgreement::Exec_PrivacyAndCookiePolicyDoNotAccept(const TCHAR* Cmd)
{
	FString OutString;
	FParse::Line(&Cmd, OutString, true);

	OutString.ToLower();

	// PrivacyAndCookiePolicyDoNotAccept | PrivacyAndCookiePolicy DoNotAccept
	if (OutString == NCsConsoleCommandDigitalAgreement::Cmd::PrivacyAndCookiePolicyDoNotAccept ||
		OutString == NCsConsoleCommandDigitalAgreement::Cmd::PrivacyAndCookiePolicy_DoNotAccept)
	{
		if (!MyRoot)
		{
			UE_LOG(LogCsOnline, Warning, TEXT("FCsConsoleCommand_DigitalAgreement::Exec_PrivacyAndCookiePolicyDoNotAccept: MyRoot (UR6GameInstance) is NULL."));
			return false;
		}

		UCsManager_DigitalAgreement::Get(MyRoot)->DoNotAccept(ECsDigitalAgreement::PrivacyAndCookiePolicy);
		return true;
	}
	return false;
}