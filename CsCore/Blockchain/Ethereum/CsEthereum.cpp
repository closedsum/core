// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereum.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

namespace ECsEthereumCommand
{
	const FECsBlockchainCommand InitBlockchain = EMCsBlockchainCommand::Get().Create(TEXT("InitBlockchain"));
	const FECsBlockchainCommand SetDataDirectory = EMCsBlockchainCommand::Get().Create(TEXT("SetDataDirectory"));
	const FECsBlockchainCommand AttachToConsole = EMCsBlockchainCommand::Get().Create(TEXT("AttachToConsole"));
	const FECsBlockchainCommand ExitConsole = EMCsBlockchainCommand::Get().Create(TEXT("ExitConsole"));
	const FECsBlockchainCommand NewAccount = EMCsBlockchainCommand::Get().Create(TEXT("NewAccount"));
	const FECsBlockchainCommand UnlockAccount = EMCsBlockchainCommand::Get().Create(TEXT("UnlockAccount"));
	const FECsBlockchainCommand ListAccounts = EMCsBlockchainCommand::Get().Create(TEXT("ListAccounts"));
	const FECsBlockchainCommand SetEtherbase = EMCsBlockchainCommand::Get().Create(TEXT("SetEtherbase"));
	const FECsBlockchainCommand GetBalanceEther = EMCsBlockchainCommand::Get().Create(TEXT("GetBalanceEther"));
	const FECsBlockchainCommand GetBalanceWei = EMCsBlockchainCommand::Get().Create(TEXT("GetBalanceWei"));
	const FECsBlockchainCommand StartMiner = EMCsBlockchainCommand::Get().Create(TEXT("StartMiner"));
	const FECsBlockchainCommand StopMiner = EMCsBlockchainCommand::Get().Create(TEXT("StopMiner"));
	const FECsBlockchainCommand DeployContract = EMCsBlockchainCommand::Get().Create(TEXT("DeployContract"));
	const FECsBlockchainCommand LoadScript = EMCsBlockchainCommand::Get().Create(TEXT("LoadScript"));
	const FECsBlockchainCommand CreateContractABI = EMCsBlockchainCommand::Get().Create(TEXT("CreateContractABI"));
	const FECsBlockchainCommand CreateContractInstance = EMCsBlockchainCommand::Get().Create(TEXT("CreateContractInstance"));
	const FECsBlockchainCommand RunContractConstantFunction = EMCsBlockchainCommand::Get().Create(TEXT("RunContractConstantFunction"));
	const FECsBlockchainCommand RunContractStateChangeFunction = EMCsBlockchainCommand::Get().Create(TEXT("RunContractStateChangeFunction"));
	const FECsBlockchainCommand GetGasEstimate = EMCsBlockchainCommand::Get().Create(TEXT("GetGasEstimate"));
	const FECsBlockchainCommand GetTransactionReceipt = EMCsBlockchainCommand::Get().Create(TEXT("GetTransactionReceipt"));

	const FECsBlockchainCommand MAX = EMCsBlockchainCommand::Get().Create(TEXT("MAX"));
}

UCsEthereum::UCsEthereum(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Interface
#pragma region

	// Paths
#pragma region

void UCsEthereum::SetRootDirectory(const FString &Path){}
void UCsEthereum::SetChainDirectory(const FString &Path){}
void UCsEthereum::SetAccountsDirectory(const FString &Path){}
void UCsEthereum::SetContractsDirectory(const FString &Path){}
void UCsEthereum::SetContractsDeployedDirectory(const FString &Path){}

#pragma endregion Paths

	// Process
#pragma region

void UCsEthereum::SetConsoleFilename(const FString &Filename){}
void UCsEthereum::SetConsoleDirectory(const FString &Path){}

#pragma endregion Process

void UCsEthereum::Start() {}

void UCsEthereum::SetCommand(const FECsBlockchainCommand &Command, const FString &Str)
{
	FString* Value = Commands.Find(Command);

	if (Value)
	{
		*Value = Str;
	}
	else
	{
		Commands.Add(Command, Str);
	}
}

void UCsEthereum::RunCommand(const int32 &ConsoleIndex, const FString &Command) 
{
	UCsProcess* P = GetProcess(ECsBlockchainProcessType::Console, ConsoleIndex);

	if (!P)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsEthereum::RunCommand: Failed to run command: %s. Process Console has NOT started. Make sure OpenConsole() has been called."), *Command);
		return;
	}

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Console (Input): %s"), *Command);
	}
	P->RunCommand(Command);
}

void UCsEthereum::RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments)
{
	FString* Value = Commands.Find(Command);

	if (!Value)
	{
		UE_LOG(LogCs, Warning, TEXT("CgEthereum::RunCommand: No command set for %s"), *(Command.Name));
		return;
	}

	FString Composite = *Value;

	// Rebuild command if arguments where passed in
	if (Arguments.Num() > CS_EMPTY)
	{
		int32 Index = Value->Find(TEXT("%s"));
		int32 Start = 0;
		
		// Create list of all string parts
		TArray<FString> Parts;

		while (Index != INDEX_NONE)
		{
			Parts.Add(Value->Mid(Start, Index));

			const int32 ESCAPE_LEN  = 2;
			Start					= Index + ESCAPE_LEN;
			FString Remaining	    = Value->Mid(Start);
			Index					= Remaining.Find(TEXT("%s"));
		}

		// Add in arguments
		if ((Parts.Num() - 1) == Arguments.Num())
		{
			Composite = ECsCachedString::Str::Empty;

			int32 Count = Arguments.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Composite += Parts[I] + Arguments[I].ToString();
			}
			Composite += Parts[Count];
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("CgEthereum.RunCommand: Failed to run command: %s. Wildcard count (%d) != Argument count (%d)"), *(Command.Name), Parts.Num(), Arguments.Num());
		}
	}

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("CgEthereum.RunCommand: Running command: %s"), *(Command.Name));
	}
	RunCommand(ConsoleIndex, Composite);
}

void UCsEthereum::SetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, class UCsProcess* Process){}
UCsProcess* UCsEthereum::GetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index) { return nullptr; }
void UCsEthereum::StartProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo){}
void UCsEthereum::StopProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index){}

void UCsEthereum::OpenRunningInstance(){}
void UCsEthereum::CreatePrivateChain(){}
void UCsEthereum::StartPrivateChain(){}

void UCsEthereum::OpenConsole(){}
void UCsEthereum::CloseConsole(){}

	// Account
#pragma region

void UCsEthereum::LoadAccounts(){}
void UCsEthereum::NewAccount(void* Payload){}
void UCsEthereum::UnlockAccount(class ICsBlockchainAccount* IAccount){}

#pragma endregion Account

	// Miner
#pragma region

void UCsEthereum::StartMiner(){}
void UCsEthereum::StopMiner(){}

#pragma endregion Miner

#pragma endregion // Interface

void UCsEthereum::Rebuild()
{
	// Delete files in existing directories
	IFileManager& FileManager = FFileManagerGeneric::Get();

	// Accounts
	if (FileManager.DirectoryExists(*AccountsDirectory))
	{
		TArray<FString> FoundFiles;

		FileManager.FindFiles(FoundFiles, *AccountsDirectory, nullptr);

		const int32 Count = FoundFiles.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FileManager.Delete(*(FoundFiles[I]), false, true, true);
		}
	}
	// chaindata
	if (FileManager.DirectoryExists(*ChainDirectory))
	{
		TArray<FString> FoundFiles;

		FileManager.FindFiles(FoundFiles, *ChainDirectory, nullptr);

		const int32 Count = FoundFiles.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FileManager.Delete(*(FoundFiles[I]), false, true, true);
		}
	}
	// genesis.json
	if (FileManager.FileExists(*GenesisFilePath))
		FileManager.Delete(*GenesisFilePath, false, true, true);
	// Contracts Deployed
	if (FileManager.DirectoryExists(*ContractsDeployedDirectory))
	{
		TArray<FString> FoundFiles;

		FileManager.FindFiles(FoundFiles, *ContractsDeployedDirectory, nullptr);

		const int32 Count = FoundFiles.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FileManager.Delete(*(FoundFiles[I]), false, true, true);
		}
	}
	// Web3Deploy Linked
	if (FileManager.DirectoryExists(*Web3DeployLinkedDirectory))
	{
		TArray<FString> FoundFiles;

		FileManager.FindFiles(FoundFiles, *Web3DeployLinkedDirectory, nullptr);

		const int32 Count = FoundFiles.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FileManager.Delete(*(FoundFiles[I]), false, true, true);
		}
	}
	// Javascript Contract Linked
	if (FileManager.DirectoryExists(*JavascriptLinkedDirectory))
	{
		TArray<FString> FoundFiles;

		FileManager.FindFiles(FoundFiles, *JavascriptLinkedDirectory, nullptr);

		const int32 Count = FoundFiles.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FileManager.Delete(*(FoundFiles[I]), false, true, true);
		}
	}
}

// Process
#pragma region

void UCsEthereum::AddMonitorOutputEvenToProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsProcessMonitorOutputEvent &E)
{
	// TODO: Later handle PrivateMultiNode
	Processes[ProcessType]->AddMonitorOutputEvent(E);
}

void UCsEthereum::AddMonitorOutputEvenToProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FECsBlockchainCommand& Command)
{
	// TODO: Later handle PrivateMultiNode
	AddMonitorOutputEvenToProcess(ProcessType, Index, MonitorOutputEvents[Command]);
}

void UCsEthereum::OnCommandCompleted(const FECsBlockchainCommand &Command)
{
	if (CsCVarLogBlockchainCommandCompleted->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("CgEthereum.OnCommandCompleted: Completed command: %s"), *(Command.Name));
	}

	// SetDataDirectory
	if (Command == ECsEthereumCommand::SetDataDirectory)
	{
	}
	// AttachToConsole
	if (Command == ECsEthereumCommand::AttachToConsole)
	{
	}
	// UnlockAccount
	if (Command == ECsEthereumCommand::UnlockAccount)
	{
	}
	// SetEtherbase
	if (Command == ECsEthereumCommand::SetEtherbase)
	{
		// Get Nickname
		//CgEthereumAccount account = (CgEthereumAccount)CurrentCommandInfo.Payload;
	}
	// GetBalanceEther
	if (Command == ECsEthereumCommand::GetBalanceEther)
	{
	}
	CommandFlag = true;
}

void UCsEthereum::OnCommandCompleted(const FString &Name)
{
	//CommandCompleted_Event
}

#pragma endregion Process