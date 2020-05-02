// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/DigitalAgreement/CsCVars_DigitalAgreement.h"

TAutoConsoleVariable<int32> CsCVarDisableGameStartupDigitalAgreement(
	TEXT("disable.game.startup.digitalagreement"),
	0,
	TEXT("[Non Shipping][.ini - SystemSettings] Disable showing any Digital Agreement on Game Startup."),
	ECVF_SetBySystemSettingsIni
);