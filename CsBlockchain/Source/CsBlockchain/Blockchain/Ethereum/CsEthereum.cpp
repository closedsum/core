// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereum.h"
#include "CsBlockchain.h"
#include "CsBlockchainCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Process/CsManager_Process.h"

#include "Blockchain/Ethereum/CsEthereumGenesis.h"
#include "Blockchain/Ethereum/CsEthereumAccount.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

// Enums
#pragma region

namespace ECsEthereumCommand
{
	CSBLOCKCHAIN_API const FECsBlockchainCommand InitBlockchain = EMCsBlockchainCommand::Get().Create(TEXT("InitBlockchain"), TEXT("Init Blockchain"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand SetDataDirectory = EMCsBlockchainCommand::Get().Create(TEXT("SetDataDirectory"), TEXT("Set Data Directory"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand AttachToConsole = EMCsBlockchainCommand::Get().Create(TEXT("AttachToConsole"), TEXT("Attach to Console"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand ExitConsole = EMCsBlockchainCommand::Get().Create(TEXT("ExitConsole"), TEXT("Exit Console"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand NewAccount = EMCsBlockchainCommand::Get().Create(TEXT("NewAccount"), TEXT("New Account"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand UnlockAccount = EMCsBlockchainCommand::Get().Create(TEXT("UnlockAccount"), TEXT("Unlock Account"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand ListAccounts = EMCsBlockchainCommand::Get().Create(TEXT("ListAccounts"), TEXT("List Accounts"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand SetEtherbase = EMCsBlockchainCommand::Get().Create(TEXT("SetEtherbase"), TEXT("Set Etherbase"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand GetBalanceEther = EMCsBlockchainCommand::Get().Create(TEXT("GetBalanceEther"), TEXT("Get Balance Ether"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand GetBalanceWei = EMCsBlockchainCommand::Get().Create(TEXT("GetBalanceWei"), TEXT("Get Balance Wei"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand StartMiner = EMCsBlockchainCommand::Get().Create(TEXT("StartMiner"), TEXT("Start Miner"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand StopMiner = EMCsBlockchainCommand::Get().Create(TEXT("StopMiner"), TEXT("Stop Miner"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand DeployContract = EMCsBlockchainCommand::Get().Create(TEXT("DeployContract"), TEXT("Deploy Contract"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand LoadScript = EMCsBlockchainCommand::Get().Create(TEXT("LoadScript"), TEXT("Load Script"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand CreateContractABI = EMCsBlockchainCommand::Get().Create(TEXT("CreateContractABI"), TEXT("Create Contract ABI"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand CreateContractInstance = EMCsBlockchainCommand::Get().Create(TEXT("CreateContractInstance"), TEXT("Create Contract Instance"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand RunContractConstantFunction = EMCsBlockchainCommand::Get().Create(TEXT("RunContractConstantFunction"), TEXT("Run Contract Constant Function"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand RunContractStateChangeFunction = EMCsBlockchainCommand::Get().Create(TEXT("RunContractStateChangeFunction"), TEXT("Run Contract State Change Function"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand GetGasEstimate = EMCsBlockchainCommand::Get().Create(TEXT("GetGasEstimate"), TEXT("Get Gas Estimate"));
	CSBLOCKCHAIN_API const FECsBlockchainCommand GetTransactionReceipt = EMCsBlockchainCommand::Get().Create(TEXT("GetTransactionReceipt"), TEXT("Get Transaction Receipt"));
}

namespace ECsEthereumRoutine
{
	namespace Str
	{
		const TCsString StartPrivateChain_Internal = TCsString(TEXT("StartPrivateChain_Internal"), TEXT("startprivatechain_internal"));
		const TCsString OpenConsole_Internal = TCsString(TEXT("OpenConsole_Internal"), TEXT("openconsole_internal"));
		const TCsString CreateKeystore_Internal = TCsString(TEXT("CreateKeystore_Internal"), TEXT("createkeystore_internal"));
		const TCsString SetupAccount_Internal = TCsString(TEXT("SetupAccount_Internal"), TEXT("setupaccount_internal"));
		const TCsString BringBalanceToThreshold_Internal = TCsString(TEXT("BringBalanceToThreshold_Internal"), TEXT("bringbalancetothreshold_internal"));
		const TCsString DeployContract_Internal = TCsString(TEXT("DeployContract_Internal"), TEXT("deploycontract_internal"));
		const TCsString SetupContract_Internal = TCsString(TEXT("SetupContract_Internal"), TEXT("setupcontract_internal"));
		const TCsString RunContractStateChangeFunction_Internal = TCsString(TEXT("RunContractStateChangeFunction_Internal"), TEXT("runcontractstatechangefunction_internal"));
		const TCsString CheckTransactionHasBeenMined_Internal = TCsString(TEXT("CheckTransactionHasBeenMined_Internal"), TEXT("checktransactionhasbeenmined_internal"));
	}

	namespace Ref
	{
		const Type StartPrivateChain_Internal = Type::StartPrivateChain_Internal;
		const Type OpenConsole_Internal = Type::OpenConsole_Internal;
		const Type CreateKeystore_Internal = Type::CreateKeystore_Internal;
		const Type SetupAccount_Internal = Type::SetupAccount_Internal;
		const Type BringBalanceToThreshold_Internal = Type::BringBalanceToThreshold_Internal;
		const Type DeployContract_Internal = Type::DeployContract_Internal;
		const Type SetupContract_Internal = Type::SetupContract_Internal;
		const Type RunContractStateChangeFunction_Internal = Type::RunContractStateChangeFunction_Internal;
		const Type CheckTransactionHasBeenMined_Internal = Type::CheckTransactionHasBeenMined_Internal;
		const Type ECsEthereumRoutine_MAX = Type::ECsEthereumRoutine_MAX;
	}
}

	// EthereumJavascript
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsEthereumJavascript)

#pragma endregion Enums

// JavascriptContractLink
#pragma region

FCsEthereumJavascriptContractLink::FCsEthereumJavascriptContractLink() {}
FCsEthereumJavascriptContractLink::FCsEthereumJavascriptContractLink(const FECsBlockchainContract &InContract, const FString &InLink)
{
	Contract = InContract;
	Link = InLink;
}

FCsEthereumJavascriptContractLink::~FCsEthereumJavascriptContractLink() {}

FCsEthereumJavascriptContractLink& FCsEthereumJavascriptContractLink::operator=(const FCsEthereumJavascriptContractLink& B)
{
	Contract = B.Contract;
	Link = B.Link;
	return *this;
}

bool FCsEthereumJavascriptContractLink::operator==(const FCsEthereumJavascriptContractLink& B) const
{
	return Contract == B.Contract && Link == B.Link;
}

bool FCsEthereumJavascriptContractLink::operator!=(const FCsEthereumJavascriptContractLink& B) const
{
	return !(*this == B);
}

void FCsEthereumJavascriptContractLink::Set(const FECsBlockchainContract &InContract, const FString &InLink)
{
	Contract = InContract;
	Link = InLink;
}

#pragma endregion JavascriptContractLink

// Cache
#pragma region

namespace NCsEthereumCached
{
	namespace Name
	{
		// Functions
		const FName StartPrivateChain_Internal = FName("UCsEthereum::StartPrivateChain_Internal");
		const FName OpenConsole_Internal = FName("UCsEthereum::OpenConsole_Internal");
		const FName CreateKeystore_Internal = FName("UCsEthereum::CreateKeystore_Internal");
		const FName SetupAccount_Internal = FName("UCsEthereum::SetupAccount_Internal");
		const FName BringBalanceToThreshold_Internal = FName("UCsEthereum::BringBalanceToThreshold_Internal");
		const FName DeployContract_Internal = FName("UCsEthereum::DeployContract_Internal");
		const FName SetupContract_Internal = FName("UCsEthereum::SetupContract_Internal");
		const FName RunContractStateChangeFunction_Internal = FName("UCsEthereum::RunContractStateChangeFunction_Internal");
		const FName CheckTransactionHasBeenMined_Internal = FName("UCsEthereum::CheckTransactionHasBeenMined_Internal");
	};

	namespace Str
	{
		// Functions
		const FString StartPrivateChain_Internal = TEXT("UCsEthereum::StartPrivateChain_Internal");
		const FString OpenConsole_Internal = TEXT("UCsEthereum::OpenConsole_Internal");
		const FString CreateKeystore_Internal = TEXT("UCsEthereum::CreateKeystore_Internal");
		const FString SetupAccount_Internal = TEXT("UCsEthereum::SetupAccount_Internal");
		const FString BringBalanceToThreshold_Internal = TEXT("UCsEthereum::BringBalanceToThreshold_Internal");
		const FString DeployContract_Internal = TEXT("UCsEthereum::DeployContract_Internal");
		const FString SetupContract_Internal = TEXT("UCsEthereum::SetupContract_Internal");
		const FString RunContractStateChangeFunction_Internal = TEXT("UCsEthereum::RunContractStateChangeFunction_Internal");
		const FString CheckTransactionHasBeenMined_Internal = TEXT("UCsEthereum::CheckTransactionHasBeenMined_Internal");

		const FString Geth = TEXT("Geth");

		const FString ConsolePrompt = TEXT(">");
		const FString ContractMined = TEXT("Contract mined! address: ");
		const FString null = TEXT("null");
		const FString transactionIndex = TEXT("transactionIndex:");
	};
}

#pragma endregion Cache

UCsEthereum::UCsEthereum(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

void UCsEthereum::Initialize()
{
	Super::Initialize();

	Genesis = NewObject<UCsEthereumGenesis>(GetTransientPackage(), UCsEthereumGenesis::StaticClass(), TEXT("Ethereum_Genesis"), RF_Transient);
	Genesis->AddToRoot();

	ConsoleFilename = TEXT("geth.exe");
	const FString Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());

	ConsoleDirectory = Path + TEXT("Blockchain/Ethereum/Geth");
	ConsoleFullPath = ConsoleDirectory + "/" + ConsoleFilename;
	RootDirectory = Path + TEXT("Blockchain/Ethereum");
	GenesisFilePath = RootDirectory + TEXT("/genesis.json");

	ChainDirectory = Path + TEXT("Blockchain/Ethereum/chaindata");
	AccountsDirectory = RootDirectory + "/Accounts";

	KeystoreDirectory = ChainDirectory + TEXT("/keystore");

	ContractsDirectory = RootDirectory + TEXT("/Contracts");
	ContractsDeployedDirectory = ContractsDirectory + TEXT("/Deployed");

	ABIDirectory = ContractsDirectory + TEXT("/ABI");
	
	Web3DeployDirectory = ContractsDirectory + TEXT("/Web3Deploy");

	Web3DeployLinkedDirectory = Web3DeployDirectory + TEXT("/Linked");

	JavascriptDirectory = RootDirectory + TEXT("/Javascript");
	JavascriptLinkedDirectory = JavascriptDirectory + TEXT("/Linked");

	CurrentCommandInfo.Reset();

	// Commands
	{
		// InitBlockchain
		SetCommand(ECsEthereumCommand::InitBlockchain, TEXT("--datadir=\"") + ChainDirectory + TEXT("\" init \"") + RootDirectory + TEXT("\\genesis.json\""));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("database=lightchaindata"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::InitBlockchain, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::InitBlockchain, E);
		}
		// SetDataDirectory
		SetCommand(ECsEthereumCommand::SetDataDirectory, TEXT("--datadir=\"") + ChainDirectory + TEXT("\" --networkid 15 --gcmode archive"));
		{
			// TODO: also include "url=\\\\.\\pipe\\geth.ipc"?
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("IPC endpoint opened"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::SetDataDirectory, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::SetDataDirectory, E);
		}
		// AttachToConsole
		SetCommand(ECsEthereumCommand::AttachToConsole, TEXT("attach ipc:\\\\.\\pipe\\geth.ipc"));
		{
			FCsStringParagraph P;
			P.AddSentence(NCsStringParagraphHelper::CreateOneWordSentence(TEXT("welcome"), ECsStringWordRule::Lower));
			P.AddSentence(NCsStringParagraphHelper::CreateOneWordSentence(TEXT("instance:"), ECsStringWordRule::Lower));
			P.AddSentence(NCsStringParagraphHelper::CreateOneWordSentence(TEXT("modules:"), ECsStringWordRule::Lower));

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::AttachToConsole, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::AttachToConsole, E);
		}
		// ExitConsole
		SetCommand(ECsEthereumCommand::ExitConsole, TEXT("exit"));
		// NewAccount
		SetCommand(ECsEthereumCommand::NewAccount, TEXT("personal.newAccount(%s)"));
		// UnlockAccount
		SetCommand(ECsEthereumCommand::UnlockAccount, TEXT("personal.unlockAccount(%s,%s,%s)"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("true"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::UnlockAccount, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::UnlockAccount, E);
		}
		// ListAccounts
		SetCommand(ECsEthereumCommand::ListAccounts, TEXT("personal.listAccounts"));
		// SetEtherbase
		SetCommand(ECsEthereumCommand::SetEtherbase, TEXT("miner.setEtherbase(%s);"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("true"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::SetEtherbase, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::SetEtherbase, E);
		}
		// GetBalanceEther
		SetCommand(ECsEthereumCommand::GetBalanceEther, TEXT("web3.fromWei(eth.getBalance(%s))"));
		// StartMiner
		SetCommand(ECsEthereumCommand::StartMiner, TEXT("miner.start();"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("null"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::StartMiner, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::StartMiner, E);
		}
		// StopMiner
		SetCommand(ECsEthereumCommand::StopMiner, TEXT("miner.stop();"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("true"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::StopMiner, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::StopMiner, E);
		}
		// LoadScript
		SetCommand(ECsEthereumCommand::LoadScript, TEXT("loadScript(%s)"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("true"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::LoadScript, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::LoadScript, E);
		}
		// CreateContractABI
		SetCommand(ECsEthereumCommand::CreateContractABI, TEXT("%s"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT(""), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::CreateContractABI, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::CreateContractABI, E);
		}
		// CreateContractInstance
		SetCommand(ECsEthereumCommand::CreateContractInstance, TEXT("var %s = %s.at(%s)"));
		{
			FCsStringParagraph P = NCsStringParagraphHelper::CreateOneWordParagraph(TEXT("undefined"), ECsStringWordRule::MatchCase);

			FCsProcessMonitorOutputEvent E(ECsEthereumCommand::CreateContractInstance, P, ECsProcessMonitorOutputEventPurpose::FireOnce);
			E.Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);

			MonitorOutputEvents.Add(ECsEthereumCommand::CreateContractInstance, E);
		}
		// GetTransactionReceipt
		SetCommand(ECsEthereumCommand::GetTransactionReceipt, TEXT("eth.getTransactionReceipt(%s)"));

		CommandCompleted_Event.AddUObject(this, &UCsEthereum::OnCommandCompleted);
		//AccountCreated_Event.AddUObject(this, &UCsEthereum::OnAccountCreated);
	}

	if (CsCVarBlockchainRebuild->GetInt() == CS_CVAR_VALID)
	{
		Rebuild();
	}
}

void UCsEthereum::CleanUp()
{
	Super::CleanUp();

	if (Genesis && !Genesis->IsPendingKill())
	{
		Genesis->RemoveFromRoot();
		Genesis->ConditionalBeginDestroy();
	}
}

#pragma endregion Singleton

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
		UE_LOG(LogCsBlockchain, Warning, TEXT("UCsEthereum::RunCommand: Failed to run command: %s. Process Console has NOT started. Make sure OpenConsole() has been called."), *Command);
		return;
	}

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("Console (Input): %s"), *Command);
	}
	P->RunCommand(Command);
}

void UCsEthereum::RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments)
{
	FString* Value = Commands.Find(Command);

	if (!Value)
	{
		UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::RunCommand: No command set for %s"), *(Command.Name));
		return;
	}

	FString Composite = *Value;

	// Rebuild command if arguments where passed in
	if (Arguments.Num() > CS_EMPTY)
	{
		if (Composite == TEXT("%s") &&
			Arguments.Num() == 1)
		{
			Composite = Arguments[CS_FIRST].ToString();
		}
		else
		{
			TArray<FString> Parts;
			Value->ParseIntoArray(Parts, TEXT("%s"), true);

			// Add in arguments
			if ((Parts.Num() - 1) == Arguments.Num())
			{
				Composite = NCsCached::Str::Empty;

				int32 Count = Arguments.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					Composite += Parts[I] + Arguments[I].ToString();
				}
				Composite += Parts[Count];
			}
			else
			{
				UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum.RunCommand: Failed to run command: %s. Wildcard count (%d) != Argument count (%d)"), *(Command.Name), Parts.Num(), Arguments.Num());
			}
		}
	}

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum.RunCommand: Running command: %s"), *(Command.Name));
	}
	RunCommand(ConsoleIndex, Composite);
}

void UCsEthereum::SetProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, UCsProcess* Process)
{
	// TODO: Later handle PrivateMultiNode
	Processes[ProcessType] = Process;
}

UCsProcess* UCsEthereum::GetProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index) 
{ 
	return Processes[ProcessType]; 
}

void UCsEthereum::StartProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo)
{
	UCsProcess* Process = GetProcess(ProcessType, Index);

	if (!Process)
	{
		FCsProcessPayload* Payload = UICsManager_Process::Get()->AllocatePayload();

		Payload->URL				 = StartInfo.Filename;
		Payload->Params				 = StartInfo.Arguments;
		Payload->bLaunchDetached	 = CsCVarShowBlockchainProcessWindow->GetInt() == CS_CVAR_SHOW;
		Payload->bLaunchHidden		 = CsCVarShowBlockchainProcessWindow->GetInt() == CS_CVAR_HIDE;
		Payload->bLaunchReallyHidden = CsCVarShowBlockchainProcessWindow->GetInt() == CS_CVAR_HIDE;


		if (CsCVarLogBlockchainProcessStart->GetInt() == CS_CVAR_SHOW_LOG)
		{
			const FString& ProcessTypeAsString = EMCsBlockchainProcessType::Get().ToString(ProcessType);

			UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::StartProcess: Starting Process (%s): %s %s"), *ProcessTypeAsString, *(StartInfo.Filename), *(StartInfo.Arguments));
		}

		Process = UICsManager_Process::Get()->Spawn(EMCsProcess::Get()[NCsEthereumCached::Str::Geth], Payload);

		if (ProcessType == ECsBlockchainProcessType::RunningInstance)
		{
			Payload->Name = TEXT("Geth-Running");
			Process->OnOutputRecieved_Event.AddUObject(this, &UCsEthereum::OnProcessOutputRecieved);
			Process->DeAllocate_Event.AddUObject(this, &UCsEthereum::OnProcessExited);
		}
		else
		if (ProcessType == ECsBlockchainProcessType::Console)
		{
			Payload->Name = TEXT("Geth-Console");
			Process->OnOutputRecieved_Event.AddUObject(this, &UCsEthereum::OnConsoleOutputRecieved);
			Process->DeAllocate_Event.AddUObject(this, &UCsEthereum::OnConsoleExited);
		}

		for (const FCsProcessMonitorOutputEvent& Event : StartInfo.MonitorOutputEvents)
		{
			Process->AddMonitorOutputEvent(Event);
		}

		SetProcess(ProcessType, Index, Process);
	}
	else
	{
		const FString& ProcessTypeAsString = EMCsBlockchainProcessType::Get().ToString(ProcessType);

		UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::StartProcess: StartProcess called for running Process: %s BUT the process is already RUNNING."));
	}
}

void UCsEthereum::StopProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index)
{
	if (Processes[ProcessType] == nullptr)
		return;
	Processes[ProcessType]->DeAllocate();
	Processes[ProcessType] = nullptr;
}

void UCsEthereum::OpenRunningInstance()
{
	/*
	if (IsRunningInstanceOpen)
	return;
	*/

	CommandFlag = false;

	const FECsBlockchainCommand& Command = ECsEthereumCommand::SetDataDirectory;

	FCsBlockchainProcessStartInfo StartInfo;
	StartInfo.Filename				= ConsoleFullPath;
	StartInfo.Arguments				= Commands[Command];
	StartInfo.RedirectStandardInput = false;
	StartInfo.AddMonitorOutputEvent(MonitorOutputEvents[Command]);

	const ECsBlockchainProcessType& ProcessType = NCsBlockchainProcessType::Ref::RunningInstance;

	StartProcess(ProcessType, 0, StartInfo);

	//IsRunningInstanceOpen = true;
	IsRunningInstanceCloseFlag = false;
}

void UCsEthereum::CreatePrivateChain()
{
	IFileManager& FileManager = FFileManagerGeneric::Get();

	// Create chaindata Directory
	if (!FileManager.DirectoryExists(*ChainDirectory))
		FileManager.MakeDirectory(*ChainDirectory);

	// Create genesis.json
	FString Json = Genesis->ToString();

	FFileHelper::SaveStringToFile(Json, *GenesisFilePath);

	// Create Accounts Directory
	if (!FileManager.DirectoryExists(*AccountsDirectory))
		FileManager.MakeDirectory(*AccountsDirectory);

	CommandFlag = false;

	const FECsBlockchainCommand& Command = ECsEthereumCommand::InitBlockchain;

	// Init
	//IsRunningInstanceOpen = true;
	IsRunningInstanceCloseFlag = false;

	FCsBlockchainProcessStartInfo StartInfo;
	StartInfo.Filename				= ConsoleFullPath;
	StartInfo.Arguments				= Commands[Command];
	StartInfo.RedirectStandardInput = false;
	StartInfo.AddMonitorOutputEvent(MonitorOutputEvents[Command]);

	StartProcess(ECsBlockchainProcessType::RunningInstance, 0, StartInfo);
}

void UCsEthereum::StartPrivateChain()
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::StartPrivateChain_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);
	Payload->SetName(NCsEthereumCached::Str::StartPrivateChain_Internal);
	Payload->SetFName(NCsEthereumCached::Name::StartPrivateChain_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, StartPrivateChain_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	CS_COROUTINE_BEGIN(r);

	// Start if the Blockchain has already been initialized
	if (FFileManagerGeneric::Get().FileExists(*(eth->GenesisFilePath)))
	{
		eth->OpenRunningInstance();
	}
	// Initialize then Start
	else
	{
		eth->CreatePrivateChain();

		// TODO: Running Instance might NOT get closed
		//CS_COROUTINE_WAIT_UNTIL(r, eth->IsRunningInstanceCloseFlag);
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

		eth->PrivateChainCreated_Event.Broadcast(CS_BLOCKCHAIN_SINGLE_NODE_INDEX);

		eth->StopProcess(ECsBlockchainProcessType::RunningInstance, CS_BLOCKCHAIN_SINGLE_NODE_INDEX);

		eth->OpenRunningInstance();
	}
	// Parse the Genesis file
	eth->Genesis->ParseFromFilePath(eth->GenesisFilePath);

	// Waittill DataDirectory has been set
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	eth->PrivateChainStarted_Event.Broadcast(CS_BLOCKCHAIN_SINGLE_NODE_INDEX);

	CS_COROUTINE_END(r);
}

void UCsEthereum::OpenConsole()
{
	//if (IsConsoleOpen)
	//	return;

	CommandFlag = false;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::OpenConsole_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);
	Payload->SetName(NCsEthereumCached::Str::OpenConsole_Internal);
	Payload->SetFName(NCsEthereumCached::Name::OpenConsole_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, OpenConsole_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	CS_COROUTINE_BEGIN(r);

	{
		const FECsBlockchainCommand& Command = ECsEthereumCommand::AttachToConsole;

		FCsBlockchainProcessStartInfo StartInfo;
		StartInfo.Filename				= eth->ConsoleFullPath;
		StartInfo.Arguments				= eth->Commands[Command];
		StartInfo.RedirectStandardInput = true;
		StartInfo.AddMonitorOutputEvent(eth->MonitorOutputEvents[Command]);

		const ECsBlockchainProcessType& ProcessType = NCsBlockchainProcessType::Ref::Console;

		eth->StartProcess(ProcessType, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, StartInfo);
	}
	// Waittill Console has opened
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	eth->ConsoleOpened_Event.Broadcast(CS_BLOCKCHAIN_SINGLE_NODE_INDEX);

	CS_COROUTINE_END(r);
}

void UCsEthereum::CloseConsole()
{
	// TODO: Later handle PrivateMultiNode
	//if (!IsConsoleOpen)
	//	return;

	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::ExitConsole);

	//IsConsoleOpen = false;
}

	// Account
#pragma region

void UCsEthereum::LoadAccounts()
{
	IFileManager& FileManager = FFileManagerGeneric::Get();

	TArray<FString> FoundFiles;
	FileManager.FindFiles(FoundFiles, *AccountsDirectory);

	for (const FString& File : FoundFiles)
	{
		CsEthereumAccount* Account = new CsEthereumAccount();
		const FString Path = AccountsDirectory + TEXT("/") + File;
		Account->ParseFromFilePath(Path);
		Accounts.Add(Account->Nickname, Account);
	}
	
	// Check there is a matching Keystore for each Account

	FoundFiles.Reset();
	FileManager.FindFiles(FoundFiles, *KeystoreDirectory);

	TArray<FString> Keys;
	Accounts.GetKeys(Keys);

	TMap<FString, bool> ValidAccounts;

	for (const FString& File : FoundFiles)
	{
		CsEthereumAccount* LinkedAcccount = nullptr;

		for (const FString& Key : Keys)
		{
			CsEthereumAccount* Account = (CsEthereumAccount*)Accounts[Key];

			if (File.Contains(Account->Address))
			{
				LinkedAcccount = Account;
				ValidAccounts.Add(Key, true);
				break;
			}
		}

		// Delete the Keystore if it is not linked to an account
		if (LinkedAcccount == nullptr)
		{
			const FString Path = KeystoreDirectory + TEXT("/") + File;

			FileManager.Delete(*Path, false, true, true);

			if (CsCVarLogBlockchainAccountLoad->GetInt() == CS_CVAR_SHOW_LOG)
			{
				TArray<FString> Parts;
				File.ParseIntoArray(Parts, TEXT("--"), true);
				const FString& Address = Parts[2];

				UE_LOG(LogCsBlockchain, Log, TEXT("CsEthereum::LoadAccounts: Failed to link Keystore with address: %s to an Account."), *Address);
				UE_LOG(LogCsBlockchain, Log, TEXT("-- deleting: %s"), *Path);
			}
		}
		else
		{
			CreateKeystore(LinkedAcccount);
		}
	}
	// Check remaining Accounts that did NOT get matched with a keystore

	for (const FString& Key : Keys)
	{
		if (ValidAccounts.Find(Key))
			continue;

		CsEthereumAccount* Account = (CsEthereumAccount*)Accounts[Key];

		// Delete the Account file
		const FString Path = AccountsDirectory + TEXT("/") + Key + TEXT("--") + Account->Address + TEXT(".json");

		if (FileManager.FileExists(*Path))
			FileManager.Delete(*Path);

		// Remove the Account
		Accounts.Remove(Key);

		if (CsCVarLogBlockchainAccountLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCsBlockchain, Log, TEXT("CsEthereum::LoadAccounts: Failed to link Account with Nickname: %s and address: %s to any Keystore."), *Key, *(Account->Address));
			UE_LOG(LogCsBlockchain, Log, TEXT("-- deleting: %s"), *Path);
		}
	}
}

void UCsEthereum::NewAccount(void* Payload)
{
	FCsEthereumAccountInfo* Info = (FCsEthereumAccountInfo*)Payload;

	if (Accounts.Find(Info->Nickname))
	{
		UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::NewAccount: Account with Nickname: %s already exists."), *(Info->Nickname));
		return;
	}

	CommandFlag = false;

	const uint8 ARGUMENTS = 1;
	const uint8 PASSPHRASE = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
	Args[PASSPHRASE].Set(ECsBlockchainCommandArgumentType::StringString, Info->Passphrase);

	CurrentCommandInfo.Set(ECsEthereumCommand::NewAccount, Args, Payload);

	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::NewAccount, Args);
}

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

	// StartPrivateChain_Internal
	if (RoutineType == ECsEthereumRoutine::StartPrivateChain_Internal)
	{
		StartPrivateChain_Internal_Routine = Routine;
		return true;
	}
	// OpenConsole_Internal
	if (RoutineType == ECsEthereumRoutine::OpenConsole_Internal)
	{
		OpenConsole_Internal_Routine = Routine;
		return true;
	}
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

	// StartPrivateChain_Internal
	if (RoutineType == ECsEthereumRoutine::StartPrivateChain_Internal)
	{
		check(StartPrivateChain_Internal_Routine == Routine);
		StartPrivateChain_Internal_Routine = nullptr;
		return true;
	}
	// OpenConsole_Internal
	if (RoutineType == ECsEthereumRoutine::OpenConsole_Internal)
	{
		check(OpenConsole_Internal_Routine == Routine);
		OpenConsole_Internal_Routine = nullptr;
		return true;
	}
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

		for (const FString& File : FoundFiles)
		{
			const FString Path = AccountsDirectory + TEXT("/") + File;

			FileManager.Delete(*Path, false, true, true);
		}
	}
	// chaindata
	if (FileManager.DirectoryExists(*ChainDirectory))
		FileManager.DeleteDirectory(*ChainDirectory, false, true);
	// genesis.json
	if (FileManager.FileExists(*GenesisFilePath))
		FileManager.Delete(*GenesisFilePath, false, true, true);
	// Contracts Deployed
	if (FileManager.DirectoryExists(*ContractsDeployedDirectory))
	{
		TArray<FString> FoundFiles;
		FileManager.FindFiles(FoundFiles, *ContractsDeployedDirectory, nullptr);

		for (const FString& File : FoundFiles)
		{
			const FString Path = ContractsDeployedDirectory + TEXT("/") + File;

			FileManager.Delete(*Path, false, true, true);
		}
	}
	// Web3Deploy Linked
	if (FileManager.DirectoryExists(*Web3DeployLinkedDirectory))
	{
		TArray<FString> FoundFiles;
		FileManager.FindFiles(FoundFiles, *Web3DeployLinkedDirectory, nullptr);

		for (const FString& File : FoundFiles)
		{
			const FString Path = Web3DeployLinkedDirectory + TEXT("/") + File;

			FileManager.Delete(*Path, false, true, true);
		}
	}
	// Javascript Contract Linked
	if (FileManager.DirectoryExists(*JavascriptLinkedDirectory))
	{
		TArray<FString> FoundFiles;
		FileManager.FindFiles(FoundFiles, *JavascriptLinkedDirectory, nullptr);

		for (const FString& File : FoundFiles)
		{
			const FString Path = JavascriptLinkedDirectory + TEXT("/") + File;

			FileManager.Delete(*Path, false, true, true);
		}
	}
}

// Process
#pragma region

void UCsEthereum::AddMonitorOutputEvenToProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, const FCsProcessMonitorOutputEvent &Event)
{
	// TODO: Later handle PrivateMultiNode
	Processes[ProcessType]->AddMonitorOutputEvent(Event);
}

void UCsEthereum::AddMonitorOutputEvenToProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, const FECsBlockchainCommand& Command)
{
	// TODO: Later handle PrivateMultiNode
	AddMonitorOutputEvenToProcess(ProcessType, Index, MonitorOutputEvents[Command]);
}

void UCsEthereum::OnCommandCompleted(const FECsBlockchainCommand &Command)
{
	if (CsCVarLogBlockchainCommandCompleted->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum.OnCommandCompleted: Completed command: %s"), *(Command.Name));
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
	CommandCompleted_Event.Broadcast(EMCsBlockchainCommand::Get()[Name]);
}

	// I/O
#pragma region

void UCsEthereum::OnProcessOutputRecieved(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIORunning->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("Process (Output): %s"), *Output);
	}
}

void UCsEthereum::OnProcessExited()
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIORunning->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("Blockchain (Process) Exited"));
	}

	Processes[ECsBlockchainProcessType::RunningInstance] = nullptr;
	//IsRunningInstanceOpen = false;
	//IsRunningInstanceCloseFlag.Set(true);
}

void UCsEthereum::OnConsoleOutputRecieved(const FString &Output)
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("Console (Output): %s"), *Output);
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
			const FString AccountFilePath = AccountsDirectory + TEXT("\\") + Nickname + TEXT("-") + Address + NCsCached::Ext::json;

			FFileHelper::SaveStringToFile(Json, *AccountFilePath);

			if (CsCVarLogBlockchainAccountCreated->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCsBlockchain, Log, TEXT("Creating Account: %s"), *Nickname);
				UE_LOG(LogCsBlockchain, Log, TEXT("-- Address: %s"), *Address);
				UE_LOG(LogCsBlockchain, Log, TEXT("-- Passphrase: %s"), *Passphrase);
				UE_LOG(LogCsBlockchain, Log, TEXT("-- writing to: %s"), *AccountFilePath);
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
		// Output != TEXT("") && !Output.StartsWith(TEXT(">"))
		if (Output != NCsCached::Str::Empty &&
			!Output.StartsWith(NCsEthereumCached::Str::ConsolePrompt))
		{
			CurrentCommandOuput.Value_float = FCString::Atof(*Output);

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// DeployContract
	if (Command == ECsEthereumCommand::DeployContract)
	{
		const FString& Mined = NCsEthereumCached::Str::ContractMined;

		// Output.StartsWith(TEXT("Contract mined! address: "))
		if (Output.StartsWith(Mined))
		{
			// Remove "Contract minded! address: 0x"
			const FString Right = Output.RightChop(Mined.Len() + 2);
			// Get the first 40 characters for the address
			const FString Address = Right.Left(40);

			// Update Contract with the address
			const FString& SContract				= CurrentCommandInfo.Payload_FString;
			const FECsBlockchainContract& EContract = EMCsBlockchainContract::Get()[SContract];

			CsEthereumContract* Contract = (CsEthereumContract*)Contracts[EContract];
			Contract->Name				 = CurrentCommandInfo.Payload_FString;
			Contract->Address			 = Address;

			CurrentCommandOuput.Value_FString = Address;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// RunContractConstantFunction
	if (Command == ECsEthereumCommand::RunContractConstantFunction)
	{
		// Output != TEXT("") && !Output.StartsWith(TEXT(">"))
		if (Output != NCsCached::Str::Empty &&
			!Output.StartsWith(NCsEthereumCached::Str::ConsolePrompt))
		{
			CurrentCommandOuput.Value_FString = Output;

			CommandCompleted_Event.Broadcast(Command);

			const FCsBlockchainContractFunctionPayload& Payload = CurrentContractFunctionPayload;

			ContractFunctionCompleted_Event.Broadcast(Payload.Contract, Payload.Function);
		}
	}
	// RunContractStateChangeFunction
	if (Command == ECsEthereumCommand::RunContractStateChangeFunction)
	{
		// Output != TEXT("") && !Output.StartsWith(TEXT(">"))
		if (Output != NCsCached::Str::Empty &&
			!Output.StartsWith(NCsEthereumCached::Str::ConsolePrompt))
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
			CurrentCommandOuput.Value_int32 = FCString::Atoi(*Output);

			CommandCompleted_Event.Broadcast(Command);
		}
	}
	// GetTransactionReceipt
	if (Command == ECsEthereumCommand::GetTransactionReceipt)
	{
		// Output == TEXT("null")
		if (Output == NCsEthereumCached::Str::null)
		{
			CurrentCommandOuput.Value_bool = false;

			CommandCompleted_Event.Broadcast(Command);
		}
		// Output.Contains(NCsEthereumCached::Str::transactionIndex)
		if (Output.Contains(NCsEthereumCached::Str::transactionIndex))
		{
			CurrentCommandOuput.Value_bool = true;

			CommandCompleted_Event.Broadcast(Command);
		}
	}
}

void UCsEthereum::OnConsoleExited()
{
	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("Blockchain (Console): Exited"));
	}

	Processes[ECsBlockchainProcessType::Console] = nullptr;
	//IsConsoleOpen = false;
}

#pragma endregion I/O

#pragma endregion Process

// Accounts
#pragma region

FString UCsEthereum::GetKeystoreFilePath(const FString &Address)
{
	IFileManager& FileManager = FFileManagerGeneric::Get();

	TArray<FString> FoundFiles;
	FileManager.FindFiles(FoundFiles, *KeystoreDirectory, nullptr);

	for (const FString& File : FoundFiles)
	{
		if (File.Contains(Address))
		{
			return KeystoreDirectory + TEXT("/") + File;
		}
	}
	return NCsCached::Str::Empty;
}

void UCsEthereum::CreateKeystore(CsEthereumAccount* Account)
{
	const FString Path = GetKeystoreFilePath(Account->Address);

	if (Path == NCsCached::Str::Empty)
	{
		const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

		UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
		FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
		FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

		Payload->Coroutine.BindStatic(&UCsEthereum::CreateKeystore_Internal);
		Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
		Payload->Owner.SetObject(this);

		Payload->SetName(NCsEthereumCached::Str::CreateKeystore_Internal);
		Payload->SetFName(NCsEthereumCached::Name::CreateKeystore_Internal);
	
		Payload->SetValue_String(CS_FIRST, NCsCached::Str::Empty);
		Payload->SetValue_Void(CS_FIRST, Account);

		Scheduler->Start(Payload);
	}
	else
	{
		FCsEthereumKeystore Keystore;
		Keystore.ParseFromFilePath(Path);

		Keystores.Add(Account->Nickname, Keystore);

		if (CsCVarLogBlockchainAccountCreated->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainAccountLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::CreateKeystore: Keystore linked to Account with Nickname: %s"), *(Account->Nickname));
			UE_LOG(LogCsBlockchain, Log, TEXT("-- saved to: %s"), *Path);
		}
	}
}

CS_COROUTINE(UCsEthereum, CreateKeystore_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	FString& KeystoreFilePath  = r->GetValue_String(CS_FIRST);
	CsEthereumAccount* Account = r->GetValue_Void<CsEthereumAccount>(CS_FIRST);

	IFileManager& FileManager = FFileManagerGeneric::Get();

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			TArray<FString> FoundFiles;
			FileManager.FindFiles(FoundFiles, *(eth->KeystoreDirectory));

			for (const FString& File : FoundFiles)
			{
				if (File.Contains(*(Account->Address)))
				{
					KeystoreFilePath = eth->KeystoreDirectory + TEXT("/") + File;
					break;
				}

				if (KeystoreFilePath != NCsCached::Str::Empty)
					break;
			}
		}

		if (KeystoreFilePath == NCsCached::Str::Empty)
		{
			CS_COROUTINE_YIELD(r);
		}
	} while (KeystoreFilePath == NCsCached::Str::Empty);

	{
		FCsEthereumKeystore Keystore;
		Keystore.ParseFromFilePath(KeystoreFilePath);

		eth->Keystores.Add(Account->Nickname, Keystore);

		if (CsCVarLogBlockchainAccountCreated->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::CreateKeystore: Keystore created for Account with Nickname: %s"), *(Account->Nickname));
			UE_LOG(LogCsBlockchain, Log, TEXT("-- saved to: %s"), *KeystoreFilePath);
		}
	}

	CS_COROUTINE_END(r);
}

void UCsEthereum::SetCoinbase(ICsBlockchainAccount* IAccount)
{
	CommandFlag = false;

	// payload = nickname
	CsEthereumAccount* Account = (CsEthereumAccount*)IAccount;

	static const uint8 ARGUMENTS = 1;
	static const uint8 ADDRESS = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
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

	static const uint8 ARGUMENTS = 1;
	static const uint8 ADDRESS = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
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

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* CoroutinePayload		   = PayloadContainer->Get();

	CoroutinePayload->Coroutine.BindStatic(&UCsEthereum::SetupAccount_Internal);
	CoroutinePayload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	CoroutinePayload->Owner.SetObject(this);

	CoroutinePayload->SetName(NCsEthereumCached::Str::SetupAccount_Internal);
	CoroutinePayload->SetFName(NCsEthereumCached::Name::SetupAccount_Internal);

	CoroutinePayload->SetValue_Void(CS_FIRST, Payload);

	Scheduler->Start(CoroutinePayload);
}

CS_COROUTINE(UCsEthereum, SetupAccount_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	FCsEthereumAccountInfo* Info = r->GetValue_Void<FCsEthereumAccountInfo>(CS_FIRST);
	const FString& Nickname		 = Info->Nickname;

	ICsBlockchainAccount** IAccount = eth->Accounts.Find(Nickname);
	CsEthereumAccount* Account		= IAccount ? (CsEthereumAccount*)(*IAccount) : nullptr;

	CS_COROUTINE_BEGIN(r);

	{
		// Check Account exists
		{
			if (!Account)
			{
				eth->NewAccount(Info);
				// Waittill NewAccount command has completed
				CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

				if (CsCVarLogBlockchainAccountSetup->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::SetupAccount: Created Account for: %s"), *Nickname);
				}
			}
		}
		// Unlock Account
		eth->UnlockAccount(Account);
		// Waittill UnlockAccount command has completed
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

		if (CsCVarLogBlockchainAccountSetup->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::SetupAccount: Unlocked Account (%s): %s"), *Nickname, *(Account->Address));
		}

		// Check Balance is above Threshold
		{
			static const int32 THRESHOLD = 20;

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

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::BringBalanceToThreshold_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsEthereumCached::Str::BringBalanceToThreshold_Internal);
	Payload->SetFName(NCsEthereumCached::Name::BringBalanceToThreshold_Internal);

	Payload->SetValue_Void(CS_FIRST, IAccount);
	Payload->SetValue_Int(CS_FIRST, Threshold);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, BringBalanceToThreshold_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	CsEthereumAccount* Account = r->GetValue_Void<CsEthereumAccount>(CS_FIRST);
	const FString& Nickname	   = Account->Nickname;

	const int32& Threshold = r->GetValue_Int(CS_FIRST);

	float& Balance = r->GetValue_Float(CS_FIRST);

	const FCsTime& CurrentTime = UCsManager_Time::Get(eth->GetMyRoot())->GetTime(r->Group);
	FCsDeltaTime& ElapsedTime  = r->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += r->DeltaTime;

	static const float INTERVAL = 0.5f;

	CS_COROUTINE_BEGIN(r);

	ElapsedTime.Reset();

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
				UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Setting Account (%s): %s as coinbase."), *Nickname, *(Account->Address));
			}

			// Start Mining
			eth->StartMiner();
			// Waittill StartMiner command has completed
			CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Account (%s): %s balance is: %d < %d. Start mining."), *Nickname, *(Account->Address), Balance, Threshold);
			}

			ElapsedTime.Reset();

			do
			{
				{
					CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime.Time >= INTERVAL);

					// Check Balance
					eth->GetBalanceEther(Account);
					// Waittill GetBalanceEther command has completed
					CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

					// If the balance is below the threshold, Start Mining
					Balance = eth->CurrentCommandOuput.Value_float;

					if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
					{
						UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Account (%s): %s balance is: %d"), *Nickname, *(Account->Address), Balance);
					}
				}
			} while (Balance < Threshold);

			// Stop Mining
			eth->StopMiner();
			// Waittill StopMiner command has completed
			CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Finished mining."));
			}
		}
		// Finish
		else
		{
			if (CsCVarLogBlockchainBalance->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::BringBalanceToThreshold_Internal: Finished setup for Account (%s): %d"), *Nickname, *(Account->Address));
			}
		}
		eth->BringBalanceToThresholdFlag = true;
	}
	CS_COROUTINE_END(r);
}

#pragma endregion Accounts

// Contract
#pragma region

void UCsEthereum::DeployContract(const FECsBlockchainContract &EContract, TArray<FCsBlockchainContractArgument> &Args)
{
	DeployContractFlag = false;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::DeployContract_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsEthereumCached::Str::DeployContract_Internal);
	Payload->SetFName(NCsEthereumCached::Name::DeployContract_Internal);

	Payload->SetValue_String(CS_FIRST, EContract.Name);
	Payload->SetValue_Void(CS_FIRST, &Args);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, DeployContract_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	const FString& SContract				   = r->GetValue_String(CS_FIRST);
	const FECsBlockchainContract& EContract	   = EMCsBlockchainContract::Get()[SContract];
	TArray<FCsBlockchainContractArgument>& Args = *(r->GetValue_Void<TArray<FCsBlockchainContractArgument>>(CS_FIRST));

	CS_COROUTINE_BEGIN(r);

	// Start Miner
	eth->StartMiner();
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Setup Contract with the correct arguments
	{
		FString Snippet = eth->Web3DeployLinkedSnippets[EContract];

		for (const FCsBlockchainContractArgument& Arg : Args)
		{
			Snippet = Snippet.Replace(*(Arg.Name), *(Arg.ToString()), ESearchCase::CaseSensitive);
		}

		// Deploy Contract
		eth->CommandFlag = false;
		TArray<FCsBlockchainCommandArgument> CommandArgs;
		eth->CurrentCommandInfo.Set(ECsEthereumCommand::DeployContract, CommandArgs, SContract);
		eth->CurrentCommandOuput.Reset();
		eth->RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Snippet);
	}
	// Waittill Contract has been mined
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Write out pertinent detail of Contract
	{
		CsEthereumContract* Contract = (CsEthereumContract*)eth->Contracts[EContract];
		const FString Path			 = eth->ContractsDeployedDirectory + TEXT("\\") + Contract->Address + TEXT("-") + EContract.Name + TEXT(".json");

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
		UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::LoadContract: Contract with name: %s does NOT exist. Make sure a Contract was initialized with name: %s in the constructor."), *(EContract.Name), *(EContract.Name));
		return;
	}

	CsEthereumContract* Contract = (CsEthereumContract*)(*IContract);

	// Check if Contract file exists
	IFileManager& FileManager = FFileManagerGeneric::Get();
	
	TArray<FString> FilePaths;
	FileManager.FindFiles(FilePaths, *ContractsDeployedDirectory);

	// Only keep Files ending with EContract.Name + TEXT(".json")
	const FString JsonSuffix = EContract.Name + NCsCached::Ext::json;

	for (const FString& File : FilePaths)
	{
		if (File.EndsWith(JsonSuffix))
		{
			const FString Path = ContractsDeployedDirectory + TEXT("/") + File;

			Contract->ParseFromFilePath(Path);
		}
	}

	// Check if Contract ABI file exists
	const FString TxtSuffix = EContract.Name + NCsCached::Ext::txt;
	const FString ABIPath   = ABIDirectory + TEXT("\\") + TxtSuffix;

	if (FileManager.FileExists(*ABIPath))
	{
		FString File;
		FFileHelper::LoadFileToString(File, *ABIPath);
		ABISnippets.Add(EContract, File);
	}
	else
	{
		UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::LoadContract: Failed to find ABI for Contract: %s at: %s"), *(EContract.Name), *ABIPath);
	}

	// If Contract is "new", setup Web3Deploy and Javascript file
	if (!Contract->IsValid())
	{
		// Check if Contract Web3Deploy file exists
		const FString Web3DeployPath = Web3DeployDirectory + TEXT("\\") + TxtSuffix;

		if (FileManager.FileExists(*Web3DeployPath))
		{
			FString File;
			FFileHelper::LoadFileToString(File, *Web3DeployPath);
			Web3DeploySnippets.Add(EContract, File);
		}
		else
		{
			UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::LoadContract: Failed to find Web3Deploy for Contract: %s at: %s"), *(EContract.Name), *Web3DeployPath);
		}

		// Check if Contract Web3Deploy Linked (Libraries linked) file exists

		const FString Web3DeployLinkedPath = Web3DeployLinkedDirectory + TEXT("\\") + TxtSuffix;

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
		const FString Web3DeployLinkedPath = Web3DeployLinkedDirectory + TEXT("\\") + TxtSuffix;

		if (!FileManager.FileExists(*Web3DeployLinkedPath))
		{
			UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::LoadContract: Failed to find Web3DeployLinkedPath for Contract: %s at: %s"), *(EContract.Name), *Web3DeployLinkedPath);
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
		UE_LOG(LogCsBlockchain, Warning, TEXT("CgEthereum::CreatedJavascriptContractLinked: No script path set for script: %s. Make sure a ScriptPath is set for: %s in the constructor."), *(EScript.Name), *(EScript.Name));
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
	const uint8 ARGUMENTS = 1;
	const uint8 ABI = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
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
	const uint8 ARGUMENTS = 3;
	const uint8 INSTANCE = 0;
	const uint8 ABI = 1;
	const uint8 ADDRESS = 2;

	CsEthereumContract* Contract = (CsEthereumContract*)IContract;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
	Args[INSTANCE].Value_FString = Contract->InstanceVariableName;
	Args[INSTANCE].ValueType	 = ECsBlockchainCommandArgumentType::String;
	Args[ABI].Value_FString = Contract->ContractVariableName;
	Args[ABI].ValueType		= ECsBlockchainCommandArgumentType::String;
	Args[ADDRESS].Value_FString = Contract->GetAddressAsArg();
	Args[ADDRESS].ValueType		= ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::CreateContractInstance, Args);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::CreateContractInstance);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::CreateContractInstance, Args);
}

void UCsEthereum::SetupContract(const FECsBlockchainContract &EContract, const FECsEthereumJavascript &EScript)
{
	SetupContractFlag = false;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::SetupContract_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsEthereumCached::Str::SetupContract_Internal);
	Payload->SetFName(NCsEthereumCached::Name::SetupContract_Internal);

	static const uint8 CONTRACT_NAME = 0;
	Payload->SetValue_String(CONTRACT_NAME, EContract.Name);

	static const uint8 SCRIPT_NAME = 1;
	Payload->SetValue_String(SCRIPT_NAME, EScript.Name);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, SetupContract_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	static const uint8 CONTRACT_NAME = 0;
	const FString& SContract				= r->GetValue_String(CONTRACT_NAME);
	const FECsBlockchainContract& EContract = EMCsBlockchainContract::Get()[SContract];

	static const uint8 SCRIPT_NAME = 1;
	const FString& SScript					= r->GetValue_String(SCRIPT_NAME);
	const FECsEthereumJavascript& EScript	= EMCsEthereumJavascript::Get()[SScript];

	ICsBlockchainContract** IContract = eth->Contracts.Find(EContract);
	CsEthereumContract* Contract	  = IContract ? (CsEthereumContract*)(*IContract) : nullptr;

	CS_COROUTINE_BEGIN(r);

	eth->LoadContract(EContract, EScript);
	eth->LoadScript(EScript, eth->ScriptLinkedPaths[EContract]);
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	if (!Contract ||
		!Contract->IsValid())
	{
		{
			eth->CurrentContractArguments.Reset();
			eth->DeployContract(EContract, eth->CurrentContractArguments);
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

	CurrentContractFunctionPayload.Set(EContract, EFn);

	CurrentCommandInfo.Set(ECsEthereumCommand::RunContractConstantFunction, CommandArgs);
	CurrentCommandOuput.Reset();

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::RunContractConstantFunction: Running command: %s"), *(ECsEthereumCommand::RunContractConstantFunction.Name));
	}
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Command);
}

void UCsEthereum::RunContractStateChangeFunction(const FECsBlockchainContract &EContract, ICsBlockchainAccount* IAccount, const FECsBlockchainContractFunction &EFn, TArray<FCsBlockchainContractFunctionArgument> &Args)
{
	RunContractStateChangeFunctionFlag = false;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::RunContractStateChangeFunction_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsEthereumCached::Str::RunContractStateChangeFunction_Internal);
	Payload->SetFName(NCsEthereumCached::Name::RunContractStateChangeFunction_Internal);
	
	static const uint8 CONTRACT_NAME = 0;
	Payload->SetValue_String(CONTRACT_NAME,	EContract.Name);

	static const uint8 ACCOUNT = 0;
	Payload->SetValue_Void(ACCOUNT, IAccount);

	static const uint8 FN_NAME = 1;
	Payload->SetValue_String(FN_NAME, EFn.Name);

	static const uint8 ARGS = 1;
	Payload->SetValue_Void(ARGS, &Args);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, RunContractStateChangeFunction_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	static const uint8 CONTRACT_NAME = 0;
	const FString& SContract				= r->GetValue_String(CONTRACT_NAME);
	const FECsBlockchainContract& EContract	= EMCsBlockchainContract::Get()[SContract];

	static const uint8 ACCOUNT = 0;
	ICsBlockchainAccount* IAccount	= r->GetValue_Void<ICsBlockchainAccount>(ACCOUNT);
	CsEthereumAccount* Account		= (CsEthereumAccount*)IAccount;

	static const uint8 FN_NAME = 1;
	const FString& SFn						= r->GetValue_String(FN_NAME);
	const FECsBlockchainContractFunction EFn = EMCsBlockchainContractFunction::Get()[SFn];

	static const uint8 ARGS = 1;
	const TArray<FCsBlockchainContractFunctionArgument>& Args = *(r->GetValue_Void<TArray<FCsBlockchainContractFunctionArgument>>(ARGS));

	int32& Gas = r->GetValue_Indexer(CS_FIRST);

	const int32 THRESHOLD = 10;

	CS_COROUTINE_BEGIN(r);

	// Check Balance
	eth->BringBalanceToThreshold(IAccount, THRESHOLD);
	CS_COROUTINE_WAIT_UNTIL(r, eth->BringBalanceToThresholdFlag);

	// GetGasEstimage
	eth->GetGasEstimate(EContract, IAccount, EFn, Args);
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	Gas = eth->CurrentCommandOuput.Value_int32;

	// Start Miner
	eth->StartMiner();
	CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

	// Run State Change Function
	eth->CommandFlag = false;

	{
		const FString& Address = Account->GetAddressAsArg();

		FCsBlockchainContractFunction Fn = eth->ContractFunctions[EContract][EFn];
		Fn.SetArguments(Args);
		static const int32 GAS_PADDING = 10000;
		Gas						+= GAS_PADDING;
		const FString Command	= Fn.BuildStateChangeFunction(Address, Gas);

		eth->CurrentCommandInfo.Set(ECsEthereumCommand::RunContractStateChangeFunction);
		eth->CurrentCommandOuput.Reset();

		if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::RunContractStateChangeFunction_Internal: Running command: %s"), *(ECsEthereumCommand::RunContractStateChangeFunction.Name));
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
	const FString& Address		= Account->GetAddressAsArg();

	FCsBlockchainContractFunction Fn = ContractFunctions[EContract][EFn];
	Fn.SetArguments(Args);
	const FString Command = Fn.BuildEstimateFunction(Address);

	CurrentCommandInfo.Set(ECsEthereumCommand::GetGasEstimate);
	CurrentCommandOuput.Reset();

	if (CsCVarLogBlockchainIO->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogBlockchainIOConsole->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsBlockchain, Log, TEXT("CgEthereum::GetGasEstimate: Running command: &s"), *(ECsEthereumCommand::GetGasEstimate.Name));
	}
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, Command);
}

void UCsEthereum::GetTransactionReceipt(const FString& TransactionHash)
{
	CommandFlag = false;

	static const uint8 ARGUMENTS = 1;
	static const uint8 TRANSACTION = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
	Args[TRANSACTION].Value_FString = TransactionHash;
	Args[TRANSACTION].ValueType		= ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::GetTransactionReceipt, Args);
	CurrentCommandOuput.Reset();

	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::GetTransactionReceipt, Args);
}

void UCsEthereum::CheckTransactionHasBeenMined(const FString &TransactionHash)
{
	TransactionMinedFlag = false;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&UCsEthereum::CheckTransactionHasBeenMined_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsEthereumCached::Str::CheckTransactionHasBeenMined_Internal);
	Payload->SetFName(NCsEthereumCached::Name::CheckTransactionHasBeenMined_Internal);

	Payload->SetValue_String(CS_FIRST, TransactionHash);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsEthereum, CheckTransactionHasBeenMined_Internal)
{
	UCsEthereum* eth = r->GetOwnerAsObject<UCsEthereum>();

	const FString& TransactionHash = r->GetValue_String(CS_FIRST);

	bool& Success				= r->GetValue_Flag(CS_FIRST);
	static const float INTERVAL = 0.1f;

	const FCsTime& CurrentTime = UCsManager_Time::Get(eth->GetMyRoot())->GetTime(r->Group);
	FCsDeltaTime& ElapsedTime  = r->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += r->DeltaTime;

	CS_COROUTINE_BEGIN(r);

	ElapsedTime.Reset();

	do
	{
		eth->GetTransactionReceipt(TransactionHash);
		CS_COROUTINE_WAIT_UNTIL(r, eth->CommandFlag);

		Success = eth->CurrentCommandOuput.Value_bool;

		if (!Success)
		{
			ElapsedTime.Reset();

			CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime.Time >= INTERVAL);
		}
	} while (!Success);

	eth->TransactionMinedFlag = true;

	CS_COROUTINE_END(r);
}

#pragma endregion Contract

void UCsEthereum::LoadScript(const FECsEthereumJavascript &EScript, const FString &Path)
{
	CommandFlag = false;

	// loadScript(%s)
	const uint8 ARGUMENTS = 1;
	const uint8 PATH = 0;

	TArray<FCsBlockchainCommandArgument> Args;
	Args.SetNum(ARGUMENTS);
	Args[PATH].Value_FString = TEXT("'") + Path + TEXT("'");
	Args[PATH].ValueType	 = ECsBlockchainCommandArgumentType::String;

	CurrentCommandInfo.Set(ECsEthereumCommand::LoadScript, Args, EScript.Name);
	CurrentCommandOuput.Reset();

	AddMonitorOutputEvenToProcess(ECsBlockchainProcessType::Console, CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::LoadScript);
	RunCommand(CS_BLOCKCHAIN_SINGLE_NODE_INDEX, ECsEthereumCommand::LoadScript, Args);
}