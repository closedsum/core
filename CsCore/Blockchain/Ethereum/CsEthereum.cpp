// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereum.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Coroutine/CsCoroutineScheduler.h"

#include "Blockchain/Ethereum/CsEthereumAccount.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

// Enums
#pragma region

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

#pragma endregion Enums

// Cache
#pragma region

namespace ECsEthereumCachedName
{
	namespace Name
	{
		// Functions
		const FName CreateKeystore_Internal = FName("UCsEthereum::CreateKeystore_Internal");
		const FName SetupAccount_Internal = FName("UCsEthereum::SetupAccount_Internal");
		const FName BringBalanceToThreshold_Internal = FName("UCsEthereum::BringBalanceToThreshold_Internal");
		const FName DeployContract_Internal = FName("UCsEthereum::DeployContract_Internal");
		const FName SetupContract_Internal = FName("UCsEthereum::SetupContract_Internal");
		const FName RunContractStateChangeFunction_Internal = FName("UCsEthereum::RunContractStateChangeFunction_Internal");
		const FName CheckTransactionHasBeenMined_Internal = FName("UCsEthereum::CheckTransactionHasBeenMined_Internal");
	};
}

namespace ECsEthereumCachedString
{
	namespace Str
	{
		// Functions
		const FString CreateKeystore_Internal = TEXT("UCsEthereum::CreateKeystore_Internal");
		const FString SetupAccount_Internal = TEXT("UCsEthereum::SetupAccount_Internal");
		const FString BringBalanceToThreshold_Internal = TEXT("UCsEthereum::BringBalanceToThreshold_Internal");
		const FString DeployContract_Internal = TEXT("UCsEthereum::DeployContract_Internal");
		const FString SetupContract_Internal = TEXT("UCsEthereum::SetupContract_Internal");
		const FString RunContractStateChangeFunction_Internal = TEXT("UCsEthereum::RunContractStateChangeFunction_Internal");
		const FString CheckTransactionHasBeenMined_Internal = TEXT("UCsEthereum::CheckTransactionHasBeenMined_Internal");
	};
}

#pragma endregion Cache

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

void UCsEthereum::UnlockAccount(class ICsBlockchainAccount* IAccount)
{
	CommandFlag = false;

	CsEthereumAccount* Account = (CsEthereumAccount*)IAccount;

	TArray<FCsBlockchainCommandArgument> Args;
	Account->CreateUnlockArguments(Args);

	CurrentCommandInfo.Set(ECsEthereumCommand::NewAccount, Args, IAccount);

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::UnlockAccount);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::UnlockAccount, Args);
}

void UCsEthereum::ListAccounts()
{
	TArray<FCsBlockchainCommandArgument> Arguments;
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::ListAccounts, Arguments);
}

#pragma endregion Account

	// Miner
#pragma region

void UCsEthereum::StartMiner()
{
	if (IsMining)
		return;

	CommandFlag = false;

	CurrentCommandInfo.Set(ECsEthereumCommand::StartMiner);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::StartMiner);
	TArray<FCsBlockchainCommandArgument> Args;
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::StartMiner, Args);
	IsMining = true;
}

void UCsEthereum::StopMiner()
{
	if (!IsMining)
		return;

	CommandFlag = false;

	CurrentCommandInfo.Set(ECsEthereumCommand::StopMiner);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::StopMiner);
	TArray<FCsBlockchainCommandArgument> Args;
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::StopMiner, Args);

	IsMining = false;
}

#pragma endregion Miner

#pragma endregion // Interface

// Routines
#pragma region

/*static*/ void UCsEthereum::AddRoutine(UObject* InBlockchain, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsEthereum>(InBlockchain)->AddRoutine_Internal(Routine, Type);
}

bool UCsEthereum::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsEthereumRoutine RoutineType = (TCsEthereumRoutine)Type;

	// CreateKeystore_Internal
	if (RoutineType == ECsEthereumRoutine::CreateKeystore_Internal)
	{
		CreateKeystore_Internal_Routine = Routine;
		return true;
	}
	// SetupAccount_Internal
	if (RoutineType == ECsEthereumRoutine::SetupAccount_Internal)
	{
		SetupAccount_Internal_Routine = Routine;
		return true;
	}
	// BringBalanceToThreshold_Internal
	if (RoutineType == ECsEthereumRoutine::BringBalanceToThreshold_Internal)
	{
		BringBalanceToThreshold_Internal_Routine = Routine;
		return true;
	}
	// DeployContract_Internal
	if (RoutineType == ECsEthereumRoutine::DeployContract_Internal)
	{
		DeployContract_Internal_Routine = Routine;
		return true;
	}
	// SetupContract_Internal
	if (RoutineType == ECsEthereumRoutine::SetupContract_Internal)
	{
		SetupContract_Internal_Routine = Routine;
		return true;
	}
	// RunContractStateChangeFunction_Internal
	if (RoutineType == ECsEthereumRoutine::RunContractStateChangeFunction_Internal)
	{
		RunContractStateChangeFunction_Internal_Routine = Routine;
		return true;
	}
	// CheckTransactionHasBeenMined_Internal
	if (RoutineType == ECsEthereumRoutine::CheckTransactionHasBeenMined_Internal)
	{
		CheckTransactionHasBeenMined_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void UCsEthereum::RemoveRoutine(UObject* InBlockchain, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsEthereum>(InBlockchain)->RemoveRoutine_Internal(Routine, Type);
}

bool UCsEthereum::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsEthereumRoutine RoutineType = (TCsEthereumRoutine)Type;

	// CreateKeystore_Internal
	if (RoutineType == ECsEthereumRoutine::CreateKeystore_Internal)
	{
		check(CreateKeystore_Internal_Routine == Routine);
		CreateKeystore_Internal_Routine = nullptr;
		return true;
	}
	// SetupAccount_Internal
	if (RoutineType == ECsEthereumRoutine::SetupAccount_Internal)
	{
		check(SetupAccount_Internal_Routine == Routine);
		SetupAccount_Internal_Routine = nullptr;
		return true;
	}
	// BringBalanceToThreshold_Internal
	if (RoutineType == ECsEthereumRoutine::BringBalanceToThreshold_Internal)
	{
		check(BringBalanceToThreshold_Internal_Routine == Routine);
		BringBalanceToThreshold_Internal_Routine = nullptr;
		return true;
	}
	// DeployContract_Internal
	if (RoutineType == ECsEthereumRoutine::DeployContract_Internal)
	{
		check(DeployContract_Internal_Routine == Routine);
		DeployContract_Internal_Routine = nullptr;
		return true;
	}
	// SetupContract_Internal
	if (RoutineType == ECsEthereumRoutine::SetupContract_Internal)
	{
		check(SetupContract_Internal_Routine == Routine);
		SetupContract_Internal_Routine = nullptr;
		return true;
	}
	// RunContractStateChangeFunction_Internal
	if (RoutineType == ECsEthereumRoutine::RunContractStateChangeFunction_Internal)
	{
		check(RunContractStateChangeFunction_Internal_Routine == Routine);
		RunContractStateChangeFunction_Internal_Routine = nullptr;
		return true;
	}
	// CheckTransactionHasBeenMined_Internal
	if (RoutineType == ECsEthereumRoutine::CheckTransactionHasBeenMined_Internal)
	{
		check(CheckTransactionHasBeenMined_Internal_Routine == Routine);
		CheckTransactionHasBeenMined_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

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
	CommandCompleted_Event.Broadcast(EMCsBlockchainCommand::Get().GetEnum(Name));
}

	// I/O
#pragma region

void UCsEthereum::OnProcessOutputRecieved(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIORunning->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Process (Output): %s"), *Output);
	}
}

void UCsEthereum::OnProcessErrorRecieved(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIORunning->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Process (Error): %s"), *Output);
	}
}

void UCsEthereum::OnProcessExited(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIORunning->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Blockchain (Process) Exited"));
	}

	UCsProcess* P = Processes[ECsBlockchainProcessType::RunningInstance];

	Processes[ECsBlockchainProcessType::RunningInstance] = nullptr;
	//IsRunningInstanceOpen = false;
	//IsRunningInstanceCloseFlag.Set(true);
	P->DeAllocate();
}

void UCsEthereum::OnConsoleOutputRecieved(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Console (Output): %s"), *Output);
	}

	const FECsBlockchainCommand& Command = CurrentCommandInfo.Command;

	// NewAccount
	if (Command == ECsEthereumCommand::NewAccount)
	{
		// Check for account address
		if (Output.StartsWith("\"0x"))
		{
			FCsEthereumAccountInfo* Info = (FCsEthereumAccountInfo*)CurrentCommandInfo.Payload_ptr;

			const FString& Nickname   = Info->Nickname;
			FString Address			  = Output.Replace(TEXT("\""), TEXT(""));
			Address					  = Address.Replace(TEXT("0x"), TEXT(""));
			const FString& Passphrase = Info->Passphrase;

			CsEthereumAccount* Account =  new CsEthereumAccount(Nickname, Address, Passphrase);

			const FString Json = Account->ToString();
			const FString AccountFilePath = AccountsDirectory + TEXT("\\") + Nickname + TEXT("-") + Address;

			FFileHelper::SaveStringToFile(Json, *AccountFilePath);

			if (CsCVarLogBlockchainAccountCreated->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("Creating Account: %s"), *Nickname);
				UE_LOG(LogCs, Log, TEXT("-- Address: %s"), *Address);
				UE_LOG(LogCs, Log, TEXT("-- PassPhrase: %s"), *Passphrase);
				UE_LOG(LogCs, Log, TEXT("-- writing to: %s"), *AccountFilePath);
			}

			Accounts.Add(Nickname, Account);

			CreateKeystore(Account);

			AccountCreated_Event.Broadcast(Account);
			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// GetBalanceEther
	if (Command == ECsEthereumCommand::GetBalanceEther)
	{
		const float Balance			  = FCString::Atof(*Output);
		const FString BalanceAsString = FString::SanitizeFloat(Balance);

		if (Output == BalanceAsString)
		{
			CurrentCommandOuput.Value_int32 = Balance;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// DeployContract
	if (Command == ECsEthereumCommand::DeployContract)
	{
		const FString Mined = TEXT("Contract mined! address: ");

		if (Output.StartsWith(Mined))
		{
			// Remove "Contract minded! address: 0x"
			const FString Right = Output.RightChop(Mined.Len() + 2);
			// Get the first 40 characters for the address
			const FString Address = Right.Left(40);

			// Update Contract with the address
			FECsBlockchainContract* EContract = (FECsBlockchainContract*)CurrentCommandInfo.Payload_ptr;

			CsEthereumContract* Contract = (CsEthereumContract*)Contracts[*EContract];
			Contract->Address			 = Address;

			CurrentCommandOuput.Value_FString = Address;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// RunContractConstantFunction
	if (Command == ECsEthereumCommand::RunContractConstantFunction)
	{
		if (!Output.StartsWith(TEXT(">")))
		{
			CurrentCommandOuput.Value_FString = Output;

			CommandCompleted_Event.Broadcast(Command);

			FCsBlockchainContractFunctionPayload* Payload = (FCsBlockchainContractFunctionPayload*)CurrentCommandInfo.Payload_ptr;

			ContractFunctionCompleted_Event.Broadcast(Payload->Contract, Payload->Function);
		}
	}
	// RunContractStateChangeFunction
	if (Command == ECsEthereumCommand::RunContractStateChangeFunction)
	{
		if (!Output.StartsWith(TEXT(">")))
		{
			CurrentCommandOuput.Value_FString = Output;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// GetGasEstimate
	if (Command == ECsEthereumCommand::GetGasEstimate)
	{
		const int32 Estimate		   = FCString::Atoi(*Output);
		const FString EstimateAsString = FString::FromInt(Estimate);

		if (Output == EstimateAsString)
		{
			CurrentCommandOuput.Value_int32 = Estimate;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// GetTransactionReceipt
	if (Command == ECsEthereumCommand::GetTransactionReceipt)
	{
		if (Output == TEXT("null"))
		{
			CurrentCommandOuput.Value_bool = false;

			CommandCompleted_Event.Broadcast(Command);
		}

		if (Output.Contains(TEXT("transactionIndex:")))
		{
			CurrentCommandOuput.Value_bool = true;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
}

void UCsEthereum::OnConsoleErrorRecieved(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Console (Error): %s"), *Output);
	}
}

void UCsEthereum::OnConsoleExited(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Blockchain (Console): Exited"));
	}

	Processes[ECsBlockchainProcessType::Console]->DeAllocate();
	Processes[ECsBlockchainProcessType::Console] = nullptr;
	//IsConsoleOpen = false;
}

#pragma endregion I/O

#pragma endregion Processc

// Accounts
#pragma region

FString UCsEthereum::GetKeystoreFilePath(const FString &Address)
{
	IFileManager& FileManager = FFileManagerGeneric::Get();

	TArray<FString> Paths;
	FileManager.FindFiles(Paths, *KeystoreDirectory, nullptr);

	const int32 Count = Paths.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FString& Path = Paths[I];

		if (Path.Contains(Address))
		{
			return Path;
		}
	}
	return ECsCachedString::Str::Empty;
}

void UCsEthereum::CreateKeystore(CsEthereumAccount* Account)
{
	const FString Path = GetKeystoreFilePath(Account->Address);

	if (Path == ECsCachedString::Str::Empty)
	{
		UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
		FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

		const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

		Payload->Schedule		= Schedule;
		Payload->Function		= &UCsEthereum::CreateKeystore_Internal;
		Payload->Object			= this;
		Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
		Payload->Add			= &UCsEthereum::AddRoutine;
		Payload->Remove			= &UCsEthereum::RemoveRoutine;
		Payload->Type			= (uint8)ECsEthereumRoutine::CreateKeystore_Internal;
		Payload->DoInit			= true;
		Payload->PerformFirstRun = false;
		Payload->Name			= ECsEthereumCachedName::Name::CreateKeystore_Internal;
		Payload->NameAsString	= ECsEthereumCachedString::Str::CreateKeystore_Internal;

		FCsRoutine* R = Scheduler->Allocate(Payload);

		R->strings[CS_FIRST]	  = ECsCachedString::Str::Empty;
		R->voidPointers[CS_FIRST] = Account;

		Scheduler->StartRoutine(Schedule, R);
	}
	else
	{
		FCsEthereumKeystore Keystore;
		Keystore.ParseFromFilePath(Path);

		Keystores.Add(Account->Nickname, Keystore);

		if (CsCVarLogBlockchainAccountCreated->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainAccountLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("CgEthereum::CreateKeystore: Keystore linked to Account with Nickname: %s"), *(Account->Nickname));
			UE_LOG(LogCs, Log, TEXT("-- saved to: %s"), *Path);
		}
	}
}

CS_COROUTINE(UCsEthereum, CreateKeystore_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	FString& KeystoreFilePath  = r->strings[CS_FIRST];
	CsEthereumAccount* Account = (CsEthereumAccount*)r->voidPointers[CS_FIRST];

	IFileManager& FileManager = FFileManagerGeneric::Get();

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			TArray<FString> Paths;
			FileManager.FindFiles(Paths, *(eth->KeystoreDirectory));

			const int32 Count = Paths.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString& Path = Paths[I];

				if (Path.Contains(*(Account->Address)))
				{
					KeystoreFilePath = Path;
					break;
				}

				if (KeystoreFilePath != ECsCachedString::Str::Empty)
					break;
			}
		}

		if (KeystoreFilePath == ECsCachedString::Str::Empty)
		{
			CS_COROUTINE_YIELD(r);
		}
	} while (KeystoreFilePath == ECsCachedString::Str::Empty);

	{
		FCsEthereumKeystore Keystore;
		Keystore.ParseFromFilePath(KeystoreFilePath);

		eth->Keystores.Add(Account->Nickname, Keystore);

		if (CsCVarLogBlockchainAccountCreated->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("CgEthereum::CreateKeystore: Keystore created for Account with Nickname: %s"), *(Account->Nickname));
			UE_LOG(LogCs, Log, TEXT("-- saved to: %s"), *KeystoreFilePath);
		}
	}

	CS_COROUTINE_END(r);
}

void UCsEthereum::SetCoinbase(ICsBlockchainAccount* IAccount)
{
	CommandFlag = false;

	// payload = nickname
	CsEthereumAccount* Account = (CsEthereumAccount*)IAccount;

	const uint8 ADDRESS = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.AddDefaulted();
	Args[ADDRESS].Value_FString	= Account->Address;
	Args[ADDRESS].ValueType		= ECsBlockchainCommandArgumentType::StringString;

	CurrentCommandInfo.Set(ECsEthereumCommand::SetEtherbase, Args, IAccount);

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::SetEtherbase);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::SetEtherbase, Args);
}

void UCsEthereum::GetBalanceEther(ICsBlockchainAccount* IAccount)
{
	CommandFlag = false;

	CsEthereumAccount* Account = (CsEthereumAccount*)IAccount;

	const uint8 ADDRESS = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.AddDefaulted();
	Args[ADDRESS].Value_FString	= Account->Address;
	Args[ADDRESS].ValueType		= ECsBlockchainCommandArgumentType::StringString;

	const FString& Nickname = Account->Nickname;

	CurrentCommandInfo.Set(ECsEthereumCommand::GetBalanceEther, Args, Nickname);
	CurrentCommandOuput.Reset();

	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::GetBalanceEther, Args);
}

void UCsEthereum::SetupAccount(void* Payload)
{
	SetupAccountFlag = false;

	UCsCoroutineScheduler* Scheduler		= UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* CoroutinePayload	= Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CoroutinePayload->Schedule		= Schedule;
	CoroutinePayload->Function		= &UCsEthereum::SetupAccount_Internal;
	CoroutinePayload->Object		= this;
	CoroutinePayload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	CoroutinePayload->Add			= &UCsEthereum::AddRoutine;
	CoroutinePayload->Remove		= &UCsEthereum::RemoveRoutine;
	CoroutinePayload->Type			= (uint8)ECsEthereumRoutine::SetupAccount_Internal;
	CoroutinePayload->DoInit		= true;
	CoroutinePayload->PerformFirstRun = false;
	CoroutinePayload->Name			= ECsEthereumCachedName::Name::SetupAccount_Internal;
	CoroutinePayload->NameAsString	= ECsEthereumCachedString::Str::SetupAccount_Internal;

	FCsRoutine* R = Scheduler->Allocate(CoroutinePayload);

	R->voidPointers[CS_FIRST] = Payload;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsEthereum, SetupAccount_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	FCsEthereumAccountInfo* Info = (FCsEthereumAccountInfo*)r->voidPointers[CS_FIRST];
	const FString& Nickname		 = Info->Nickname;

	ICsBlockchainAccount** IAccount = eth->Accounts.Find(Nickname);
	CsEthereumAccount* Account		= IAccount ? (CsEthereumAccount*)(*IAccount) : nullptr;

	CS_COROUTINE_BEGIN(r);

	{
		// Check Account exists
		{
			if (!eth->Accounts.Find(Nickname))
			{
				eth->NewAccount(Info);
				// Waittill NewAccount command has completed
				CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

				if (CsCVarLogBlockchainAccountSetup->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("CgEthereum::SetupAccount: Created Account for: %s"), *Nickname);
				}
			}
		}
		// Unlock Account
		eth->UnlockAccount(Account);
		// Waittill UnlockAccount command has completed
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

		if (CsCVarLogBlockchainAccountSetup->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("CgEthereum::SetupAccount: Unlocked Account (%s): %s"), *Nickname, *(Account->Address));
		}

		// Check Balance is above Threshold
		{
			const int32 THRESHOLD = 20;

			eth->BringBalanceToThreshold(Account, THRESHOLD);
		}
		CS_COROUTINE_WAIT_UNTIL(r, eth->BringBalanceToThresholdFlag);

		eth->SetupAccountFlag = true;
	}

	CS_COROUTINE_END(r);
}

void UCsEthereum::BringBalanceToThreshold(ICsBlockchainAccount* IAccount, const int32 &Threshold)
{
	BringBalanceToThresholdFlag = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsEthereum::BringBalanceToThreshold_Internal;
	Payload->Object			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			= &UCsEthereum::AddRoutine;
	Payload->Remove			= &UCsEthereum::RemoveRoutine;
	Payload->Type			= (uint8)ECsEthereumRoutine::BringBalanceToThreshold_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsEthereumCachedName::Name::BringBalanceToThreshold_Internal;
	Payload->NameAsString	= ECsEthereumCachedString::Str::BringBalanceToThreshold_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->voidPointers[CS_FIRST] = IAccount;
	R->ints[CS_FIRST]		  = Threshold;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsEthereum, BringBalanceToThreshold_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	CsEthereumAccount* Account = (CsEthereumAccount*)r->voidPointers[CS_FIRST];
	const FString& Nickname	   = Account->Nickname;

	const float& Threshold = r->ints[CS_FIRST];

	float& Balance = r->floats[CS_FIRST];

	float& Timer = r->timers[CS_FIRST];
	Timer		+= r->deltaSeconds;

	const float INTERVAL = 0.5f;

	CS_COROUTINE_BEGIN(r);

	{
		eth->GetBalanceEther(Account);
		// Waittill GetBalanceEther command has completed
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

		// If the balance is below the threshold, Start Mining
		Balance = eth->CurrentCommandOuput.Value_float;

		if (Balance < Threshold)
		{
			// Set Coinbase
			eth->SetCoinbase(Account);
			// Waittill SetEtherbase command has completed
			CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Setting Account (%s): %s as coinbase."), *Nickname, *(Account->Address));
			}

			// Start Mining
			eth->StartMiner();
			// Waittill StartMiner command has completed
			CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Account (%s): %s balance is: %d < %d. Start mining."), *Nickname, *(Account->Address), Balance, Threshold);
			}

			Timer = 0.0f;

			do
			{
				{
					CS_COROUTINE_WAIT_UNTIL(r, Timer >= INTERVAL);

					// Check Balance
					eth->GetBalanceEther(Account);
					// Waittill GetBalanceEther command has completed
					CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

					// If the balance is below the threshold, Start Mining
					Balance = eth->CurrentCommandOuput.Value_float;

					if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
					{
						UE_LOG(LogCs, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Account (%s): %s balance is: %d"), *Nickname, *(Account->Address), Balance);
					}
				}
			} while (Balance < Threshold);

			// Stop Mining
			eth->StopMiner();
			// Waittill StopMiner command has completed
			CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Finished mining."));
			}
		}
		// Finish
		else
		{
			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Finished setup for Account (%s): %d"), *Nickname, *(Account->Address));
			}
		}
		eth->BringBalanceToThresholdFlag = true;
	}
	CS_COROUTINE_END(r);
}

#pragma endregion Accounts

// Contract
#pragma region

void UCsEthereum::DeployContract(FECsBlockchainContract &EContract, TArray<FCsBlockchainContractArgument> &Args)
{
	DeployContractFlag = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsEthereum::DeployContract_Internal;
	Payload->Object			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			= &UCsEthereum::AddRoutine;
	Payload->Remove			= &UCsEthereum::RemoveRoutine;
	Payload->Type			= (uint8)ECsEthereumRoutine::DeployContract_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsEthereumCachedName::Name::DeployContract_Internal;
	Payload->NameAsString	= ECsEthereumCachedString::Str::DeployContract_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->voidPointers[0] = &EContract;
	R->voidPointers[1] = &Args;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsEthereum, DeployContract_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const FECsBlockchainContract EContract	  = *((FECsBlockchainContract*)r->voidPointers[0]);
	TArray<FCsBlockchainContractArgument> Args = *((TArray<FCsBlockchainContractArgument>*)r->voidPointers[1]);

	CS_COROUTINE_BEGIN(r);

	// Start Miner
	eth->StartMiner();
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Setup Contract with the correct arguments
	{
		FString Snippet = eth->Web3DeployLinkedSnippets[EContract];

		if (Args.Num() > CS_EMPTY)
		{
			const int32 Count = Args.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FCsBlockchainContractArgument& Arg = Args[I];

				Snippet = Snippet.Replace(*(Arg.Name), *(Arg.ToString()));
			}
		}

		// Deploy Contract
		eth->CommandFlag = false;
		TArray<FCsBlockchainCommandArgument> CommandArgs;
		eth->CurrentCommandInfo.Set(ECsEthereumCommand::DeployContract, CommandArgs, r->voidPointers[0]);
		eth->CurrentCommandOuput.Reset();
		eth->RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Snippet);
	}
	// Waittill Contract has been mined
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Write out pertinent detail of Contract
	{
		CsEthereumContract* Contract = (CsEthereumContract*)eth->Contracts[EContract];
		const FString Path			 = eth->ContractsDeployedDirectory + TEXT("\\") + Contract->Address + TEXT("-") + EContract.Name + TEXT(".txt");

		FFileHelper::SaveStringToFile(Contract->ToString(), *Path);
	}
	// Stop Miner
	eth->StopMiner();
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	eth->DeployContractFlag = true;

	CS_COROUTINE_END(r);
}

void UCsEthereum::LoadContract(const FECsBlockchainContract &EContract, const FECsEthereumJavascript &EScript)
{
	ICsBlockchainContract** IContract = Contracts.Find(EContract);

	if (!IContract)
	{
		UE_LOG(LogCs, Warning, TEXT("CgEthereum::LoadContract: Contract with name: %s does NOT exist. Make sure a Contract was initialized with name: %s in the constructor."), *(EContract.Name), *(EContract.Name));
		return;
	}

	CsEthereumContract* Contract = (CsEthereumContract*)(*IContract);

	// Check if Contract file exists
	IFileManager& FileManager = FFileManagerGeneric::Get();
	
	TArray<FString> FilePaths;
	FileManager.FindFiles(FilePaths, *ContractsDeployedDirectory);

		// Only keep Files ending with EContract.Name + TEXT(".txt")
	int32 Count			 = FilePaths.Num();
	const FString Suffix = EContract.Name + TEXT(".txt");

	for (int32 I = 0; I < Count; ++I)
	{
		const FString& Path = FilePaths[I];

		if (Path.EndsWith(Suffix))
		{
			Contract->ParseFromFilePath(Path);
		}
	}

	// Check if Contract ABI file exists
	const FString ABIPath = ABIDirectory + TEXT("\\") + Suffix;

	if (FileManager.FileExists(*ABIPath))
	{
		FString File;
		FFileHelper::LoadFileToString(File, *ABIPath);
		ABISnippets.Add(EContract, File);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("CgEthereum::LoadContract: Failed to find ABI for Contract: %s at: %s"), *(EContract.Name), *ABIPath);
	}

	// If Contract is "new", setup Web3Deploy and Javascript file
	if (!Contract->IsValid())
	{
		// Check if Contract Web3Deploy file exists
		const FString Web3DeployPath = Web3DeployDirectory + TEXT("\\") + Suffix;

		if (FileManager.FileExists(*Web3DeployPath))
		{
			FString File;
			FFileHelper::LoadFileToString(File, *Web3DeployPath);
			Web3DeploySnippets.Add(EContract, File);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("CgEthereum::LoadContract: Failed to find Web3Deploy for Contract: %s at: %s"), *(EContract.Name), *Web3DeployPath);
		}

		// Check if Contract Web3Deploy Linked (Libraries linked) file exists

		const FString Web3DeployLinkedPath = Web3DeployLinkedDirectory + TEXT("\\") + Suffix;

		if (FileManager.FileExists(*Web3DeployLinkedPath))
		{
			FString File;
			FFileHelper::LoadFileToString(File, *Web3DeployLinkedPath);
			Web3DeployLinkedSnippets.Add(EContract, File);
		}

		CreatedWeb3DeployLinked(EContract);
		CreatedJavascriptContractLinked(EContract, EScript);
	}
	else
	{
		const FString Web3DeployLinkedPath = Web3DeployLinkedDirectory + TEXT("\\") + Suffix;

		if (!FileManager.FileExists(*Web3DeployLinkedPath))
		{
			UE_LOG(LogCs, Warning, TEXT("CgEthereum::LoadContract: Failed to find Web3DeployLinkedPath for Contract: %s at: %s"), *(EContract.Name), *Web3DeployLinkedPath);
		}
		FString File;
		FFileHelper::LoadFileToString(File, *Web3DeployLinkedPath);
		Web3DeployLinkedSnippets.Add(EContract, File);
	}
}

void UCsEthereum::CreatedWeb3DeployLinked(const FECsBlockchainContract &EContract)
{
	FString Snippet = Web3DeploySnippets[EContract];

	// Update all Links with the appropriate addresses
	/*
	List<CgEthereumWeb3DeployLink> links = Web3DeployLinks[econtract];

	if (links != null)
	{
	foreach (CgEthereumWeb3DeployLink l in links)
	{
	CgEthereumContract contract = (CgEthereumContract)Contracts[l.Contract];

	snippet = snippet.Replace(l.Link, contract.Address);
	}
	}
	*/
	// Change eth.accounts[0] to eth.coinbase
	Snippet = Snippet.Replace(TEXT("eth.accounts[0]"), TEXT("eth.coinbase"));
	//snippet = snippet.Replace("\r", "");
	//snippet = snippet.Replace("\n", "");

	const FString Path = Web3DeployLinkedDirectory + TEXT("\\") + EContract.Name + TEXT(".txt");

	FFileHelper::SaveStringToFile(Snippet, *Path);

	if (Web3DeployLinkedSnippets.Find(EContract))
	{
		Web3DeployLinkedSnippets[EContract] = Snippet;
	}
	else
	{
		Web3DeployLinkedSnippets.Add(EContract, Snippet);
	}
}

void UCsEthereum::CreatedJavascriptContractLinked(const FECsBlockchainContract &EContract, const FECsEthereumJavascript &EScript)
{
	FString* Path = ScriptPaths.Find(EScript);

	if (!Path)
	{
		UE_LOG(LogCs, Warning, TEXT("CgEthereum::CreatedJavascriptContractLinked: No script path set for script: %s. Make sure a ScriptPath is set for: %s in the constructor."), *(EScript.Name), *(EScript.Name));
		return;
	}

	FString Script;
	FFileHelper::LoadFileToString(Script, **Path);

	// Update all Links with the appropriate addresses
	TArray<FCsEthereumJavascriptContractLink>* Links = ScriptContractLinks.Find(EContract);

	if (Links)
	{
		const int32 Count = Links->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FCsEthereumJavascriptContractLink& Link = (*Links)[I];
			CsEthereumContract* Contract				  = (CsEthereumContract*)Contracts[Link.Contract];

			Script = Script.Replace(*(Link.Link), *(Contract->Address));
		}
	}
	FFileHelper::SaveStringToFile(Script, *(ScriptLinkedPaths[EContract]));
}

void UCsEthereum::CreateContractABI(const FECsBlockchainContract &EContract)
{
	CommandFlag = false;

	// %s
	const uint8 ABI = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.AddDefaulted();
	Args[ABI].Value_FString = ABISnippets[EContract];
	Args[ABI].ValueType		= ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::CreateContractABI, Args, EContract);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::CreateContractABI);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::CreateContractABI, Args);
}

void UCsEthereum::CreateContractInstance(ICsBlockchainContract* IContract)
{
	CommandFlag = false;

	// var %s = %s.at(%s)
	const uint8 INSTANCE = 0;
	const uint8 ABI = 1;
	const uint8 ADDRESS = 2;

	CsEthereumContract* Contract = (CsEthereumContract*)IContract;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.AddDefaulted();
	Args[INSTANCE].Value_FString = Contract->InstanceVariableName;
	Args[INSTANCE].ValueType	 = ECsBlockchainCommandArgumentType::String;
	Args.AddDefaulted();
	Args[ABI].Value_FString = Contract->ContractVariableName;
	Args[ABI].ValueType		= ECsBlockchainCommandArgumentType::String;
	Args.AddDefaulted();
	Args[ADDRESS].Value_FString = Contract->AddressAsArg();
	Args[ADDRESS].ValueType		= ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::CreateContractInstance, Args);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::CreateContractInstance);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::CreateContractInstance, Args);
}

void UCsEthereum::SetupContract(FECsBlockchainContract &EContract, FECsEthereumJavascript &EScript)
{
	SetupContractFlag = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsEthereum::SetupContract_Internal;
	Payload->Object			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			= &UCsEthereum::AddRoutine;
	Payload->Remove			= &UCsEthereum::RemoveRoutine;
	Payload->Type			= (uint8)ECsEthereumRoutine::SetupContract_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsEthereumCachedName::Name::SetupContract_Internal;
	Payload->NameAsString	= ECsEthereumCachedString::Str::SetupContract_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->voidPointers[0] = &EContract;
	R->voidPointers[1] = &EScript;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsEthereum, SetupContract_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	FECsBlockchainContract& EContract = *((FECsBlockchainContract*)r->voidPointers[0]);
	FECsEthereumJavascript& EScript	  = *((FECsEthereumJavascript*)r->voidPointers[1]);

	ICsBlockchainContract** IContract = eth->Contracts.Find(EContract);
	CsEthereumContract* Contract	  = IContract ? (CsEthereumContract*)(*IContract) : nullptr;

	CS_COROUTINE_BEGIN(r);

	eth->LoadContract(EContract, EScript);
	eth->LoadScript(EScript, eth->ScriptLinkedPaths[EContract]);
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	if (!Contract->IsValid())
	{
		{
			TArray<FCsBlockchainContractArgument> Args;
			eth->DeployContract(EContract, Args);
		}
		CS_COROUTINE_WAIT_UNTIL(r, eth->DeployContractFlag);
	}
	else
	{
		eth->CreateContractABI(EContract);
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);
		eth->CreateContractInstance(Contract);
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);
	}
	eth->SetupContractFlag = true;

	CS_COROUTINE_END(r);
}

void UCsEthereum::RunContractConstantFunction(const FECsBlockchainContract &EContract, const FECsBlockchainContractFunction &EFn, const TArray<FCsBlockchainContractFunctionArgument> &Args)
{
	CommandFlag = false;

	TArray<FCsBlockchainCommandArgument> CommandArgs;

	FCsBlockchainContractFunction Fn = ContractFunctions[EContract][EFn];
	Fn.SetArguments(Args);
	const FString Command = Fn.BuildConstantFunction();

	FCsBlockchainContractFunctionPayload Payload = FCsBlockchainContractFunctionPayload(EContract, EFn);

	CurrentCommandInfo.Set(ECsEthereumCommand::RunContractConstantFunction, CommandArgs, Payload);
	CurrentCommandOuput.Reset();

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("CgEthereum::RunContractConstantFunction: Running command: %s"), *(ECsEthereumCommand::RunContractConstantFunction.Name));
	}
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Command);
}

void UCsEthereum::RunContractStateChangeFunction(FECsBlockchainContract &EContract, ICsBlockchainAccount* IAccount, FECsBlockchainContractFunction &EFn, TArray<FCsBlockchainContractFunctionArgument> &Args)
{
	RunContractStateChangeFunctionFlag = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsEthereum::RunContractStateChangeFunction_Internal;
	Payload->Object			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			= &UCsEthereum::AddRoutine;
	Payload->Remove			= &UCsEthereum::RemoveRoutine;
	Payload->Type			= (uint8)ECsEthereumRoutine::RunContractStateChangeFunction_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsEthereumCachedName::Name::RunContractStateChangeFunction_Internal;
	Payload->NameAsString	= ECsEthereumCachedString::Str::RunContractStateChangeFunction_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->voidPointers[0] = &EContract;
	R->voidPointers[1] = IAccount;
	R->voidPointers[2] = &EFn;
	R->voidPointers[3] = &Args;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsEthereum, RunContractStateChangeFunction_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const FECsBlockchainContract EContract	= *((FECsBlockchainContract*)r->voidPointers[0]);
	ICsBlockchainAccount* IAccount			= (ICsBlockchainAccount*)r->voidPointers[1];
	CsEthereumAccount* Account				= (CsEthereumAccount*)IAccount;
	const FECsBlockchainContractFunction EFn = *((FECsBlockchainContractFunction*)r->voidPointers[2]);
	const TArray<FCsBlockchainContractFunctionArgument> Args = *((TArray<FCsBlockchainContractFunctionArgument>*)r->voidPointers[3]);

	const int32 THRESHOLD = 10;

	CS_COROUTINE_BEGIN(r);

	// Check Balance
	eth->BringBalanceToThreshold(IAccount, THRESHOLD);
	CS_COROUTINE_WAIT_UNTIL(r, eth->BringBalanceToThresholdFlag);

	// GetGasEstimage
	eth->GetGasEstimate(EContract, IAccount, EFn, Args);
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Start Miner
	eth->StartMiner();
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Run State Change Function
	eth->CommandFlag = false;

	{
		const FString Address = Account->AddressAsArg();

		FCsBlockchainContractFunction Fn = eth->ContractFunctions[EContract][EFn];
		Fn.SetArguments(Args);
		const int32 GAS_PADDING = 10000;
		int32 Gas				= eth->CurrentCommandOuput.Value_int32;
		Gas						+= GAS_PADDING;
		const FString Command	= Fn.BuildStateChangeFunction(Address, Gas);

		eth->CurrentCommandInfo.Set(ECsEthereumCommand::RunContractStateChangeFunction);
		eth->CurrentCommandOuput.Reset();

		if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("CgEthereum::RunContractStateChangeFunction_Internal: Running command: %s"), *(ECsEthereumCommand::RunContractStateChangeFunction.Name));
		}
		eth->RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Command);
	}
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Check Transaction has been Mined
	{
		const FString& TransactionHash = eth->CurrentCommandOuput.Value_FString;

		eth->CheckTransactionHasBeenMined(TransactionHash);
	}
	CS_COROUTINE_WAIT_UNTIL(r, eth->TransactionMinedFlag);

	// Stop Miner
	eth->StopMiner();
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	eth->RunContractStateChangeFunctionFlag = true;
	eth->ContractFunctionCompleted_Event.Broadcast(EContract, EFn);

	CS_COROUTINE_END(r);
}

void UCsEthereum::GetGasEstimate(const FECsBlockchainContract &EContract, ICsBlockchainAccount* IAccount, const FECsBlockchainContractFunction &EFn, const TArray<FCsBlockchainContractFunctionArgument> &Args)
{
	CommandFlag = false;

	CsEthereumAccount* Account	= (CsEthereumAccount*)IAccount;
	const FString Address		= Account->AddressAsArg();

	FCsBlockchainContractFunction Fn = ContractFunctions[EContract][EFn];
	Fn.SetArguments(Args);
	const FString Command = Fn.BuildEstimateFunction(Address);

	CurrentCommandInfo.Set(ECsEthereumCommand::GetGasEstimate);
	CurrentCommandOuput.Reset();

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("CgEthereum::GetGasEstimate: Running command: &s"), *(ECsEthereumCommand::GetGasEstimate.Name));
	}
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Command);
}

void UCsEthereum::GetTransactionReceipt(const FString& TransactionHash)
{
	CommandFlag = false;

	const uint8 TRANSACTION = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.AddDefaulted();
	Args[TRANSACTION].Value_FString = TransactionHash;
	Args[TRANSACTION].ValueType		= ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::GetTransactionReceipt, Args);
	CurrentCommandOuput.Reset();

	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::GetTransactionReceipt, Args);
}

void UCsEthereum::CheckTransactionHasBeenMined(const FString &TransactionHash)
{
	TransactionMinedFlag = false;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsEthereum::CheckTransactionHasBeenMined_Internal;
	Payload->Object			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			= &UCsEthereum::AddRoutine;
	Payload->Remove			= &UCsEthereum::RemoveRoutine;
	Payload->Type			= (uint8)ECsEthereumRoutine::CheckTransactionHasBeenMined_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsEthereumCachedName::Name::CheckTransactionHasBeenMined_Internal;
	Payload->NameAsString	= ECsEthereumCachedString::Str::CheckTransactionHasBeenMined_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->strings[CS_FIRST] = TransactionHash;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsEthereum, CheckTransactionHasBeenMined_Internal)
{
	UCsEthereum* eth		 = r->GetRObject<UCsEthereum>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const FString& TransactionHash = r->strings[CS_FIRST];

	bool& Success		 = r->flags[CS_FIRST];
	const float INTERVAL = 0.1f;
	float& Elapsed		 = r->timers[CS_FIRST];
	Elapsed				+= r->deltaSeconds;

	CS_COROUTINE_BEGIN(r);

	do
	{
		eth->GetTransactionReceipt(TransactionHash);
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

		Success = eth->CurrentCommandOuput.Value_bool;

		if (!Success)
		{
			Elapsed = 0.0f;

			CS_COROUTINE_WAIT_UNTIL(r, Elapsed >= INTERVAL);
		}
	} while (!Success);

	eth->TransactionMinedFlag = true;

	CS_COROUTINE_END(r);
}

#pragma endregion Contract

void UCsEthereum::LoadScript(FECsEthereumJavascript &EScript, const FString &Path)
{
	CommandFlag = false;

	// loadScript(%s)
	const uint8 PATH = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.AddDefaulted();
	Args[PATH].Value_FString = TEXT("'") + Path + TEXT("'");
	Args[PATH].ValueType	 = ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::LoadScript, Args, &EScript);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::LoadScript);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::LoadScript, Args);
}