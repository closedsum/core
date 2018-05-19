// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereum.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

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

void UCsEthereum::RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments){}

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