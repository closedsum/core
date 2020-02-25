// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsBlockchainCVars.h"
#include "CsBlockchain.h"

// Blockchain
#pragma region

TAutoConsoleVariable<int32> CsCVarBlockchainRebuild(
	TEXT("blockchain.rebuild"),
	0,
	TEXT("Rebuild Blockchain."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainIO(
	TEXT("log.blockchain.io"),
	0,
	TEXT("Log All Blockchain Input / Output Messages."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainIORunning(
	TEXT("log.blockchain.io.running"),
	0,
	TEXT("Log Running Blockchain Input / Output Messages."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainIOConsole(
	TEXT("log.blockchain.io.console"),
	0,
	TEXT("Log Console Blockchain Input / Output Messages."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarShowBlockchainProcessWindow(
	TEXT("show.blockchain.processwindow"),
	0,
	TEXT("Show Blockchain Process Window."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainProcessStart(
	TEXT("log.blockchain.process.start"),
	0,
	TEXT("Log Blockchain Process Starting."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainCommandCompleted(
	TEXT("log.blockchain.command.completed"),
	0,
	TEXT("Log Blockchain Command Completed."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountCreated(
	TEXT("log.blockchain.account.created"),
	0,
	TEXT("Log Blockchain Account Created."),
	ECVF_SetByConsole | ECVF_SetByCode
);

	// Ethereum
#pragma region

TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountLoad(
	TEXT("log.blockchain.account.load"),
	0,
	TEXT("Log Blockchain (Ethereum) when Accounts get loaded."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountSetup(
	TEXT("log.blockchain.account.setup"),
	0,
	TEXT("Log Blockchain (Ethereum) Account Setup."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainBalance(
	TEXT("log.blockchain.balance"),
	0,
	TEXT("Log Blockchain (Ethereum) Balance."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Ethereum

#pragma endregion Blockchain

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Blockchain
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainIO);
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainIORunning);
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainIOConsole);
		// Process
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainProcessStart);
		// Command
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainCommandCompleted);
		// Account
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainAccountCreated);
		// Ethereum
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainAccountLoad);
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainAccountSetup);
	CSBLOCKCHAIN_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainBalance);

	namespace Map
	{
	}
}

#pragma endregion CVarLog