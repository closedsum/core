// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCvars.h"
//#include "CsCVars.generated.h"

// Blockchain
#pragma region

extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarBlockchainRebuild;
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainIO;
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainIORunning;
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainIOConsole;
//Process
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarShowBlockchainProcessWindow;
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainProcessStart;
// Command
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainCommandCompleted;
// Account
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountCreated;

	// Ethereum
#pragma region

extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountLoad;
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountSetup;
extern CSBLOCKCHAIN_API TAutoConsoleVariable<int32> CsCVarLogBlockchainBalance;

#pragma endregion Ethereum

#pragma endregion Blockchain

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Blockchain
	extern CSBLOCKCHAIN_API const Type LogBlockchainIO;
	extern CSBLOCKCHAIN_API const Type LogBlockchainIORunning;
	extern CSBLOCKCHAIN_API const Type LogBlockchainIOConsole;
		// Process
	extern CSBLOCKCHAIN_API const Type LogBlockchainProcessStart;
		// Command
	extern CSBLOCKCHAIN_API const Type LogBlockchainCommandCompleted;
		// Account
	extern CSBLOCKCHAIN_API const Type LogBlockchainAccountCreated;
		// Ethereum
	extern CSBLOCKCHAIN_API const Type LogBlockchainAccountLoad;
	extern CSBLOCKCHAIN_API const Type LogBlockchainAccountSetup;
	extern CSBLOCKCHAIN_API const Type LogBlockchainBalance;
	
	namespace Map
	{
	}
}

#pragma endregion CVarLog