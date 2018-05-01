// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using UnityEngine;

    using Sg;

    public enum ECgEthereumOnBoardState : byte
    {
        Init,
        Start,
        Attach,
        Complete,
        MAX
    }

    public static class ECgEthereumCommand
    {
        public static readonly ECgBlockchainCommand InitBlockchain = new ECgBlockchainCommand(0, "InitBlockchain");
        public static readonly ECgBlockchainCommand SetDataDirectory = new ECgBlockchainCommand(1, "SetDataDirectory");
        public static readonly ECgBlockchainCommand AttachToConsole = new ECgBlockchainCommand(2, "AttachToConsole");
        public static readonly ECgBlockchainCommand ExitConsole = new ECgBlockchainCommand(3, "ExitConsole");
        public static readonly ECgBlockchainCommand NewAccount = new ECgBlockchainCommand(4, "NewAccount");
        public static readonly ECgBlockchainCommand UnlockAccount = new ECgBlockchainCommand(5, "UnlockAccount");
        public static readonly ECgBlockchainCommand StartMiner = new ECgBlockchainCommand(6, "StartMiner");
        public static readonly ECgBlockchainCommand StopMiner = new ECgBlockchainCommand(7, "StopMiner");
    }

    public class CgEthereum : CgBlockchain
    {
        #region "Data Members"

        private static CgEthereum instance;
        public static CgEthereum Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new CgEthereum();
                }
                return instance;
            }
        }

        public string ConsoleFullPath;
        public string GenesisFullPath;

        public CgRoutine.BoolType IsRunningInstanceCloseFlag;

        ECgEthereumOnBoardState OnBoardState;
        TCgFlagType<ECgEthereumOnBoardState> OnBoardStateFlag;

        public SgGameInstance gi;

        #endregion // Data Members

        public CgEthereum()
        {
            Init();
        }

        protected override void Init()
        {
            Get = _Get;

            Genesis = new CgEthereumGenesis();

            StorageType = ECgBlockchainStorageType.Private;

            Processes = new Dictionary<ECgBlockchainProcessType, Process>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                Processes.Add((ECgBlockchainProcessType)i, null);
            }

            ProcessFlags = new Dictionary<ECgBlockchainProcessType, bool>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                ProcessFlags.Add((ECgBlockchainProcessType)i, false);
            }

            ConsoleFilename = "geth.exe";
            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);
           
            ConsoleDirectory = path + "Blockchain\\Ethereum\\Geth";
            ConsoleFullPath = ConsoleDirectory + "\\" + ConsoleFilename;
            RootDirectory   = path + "Blockchain\\Ethereum";
            GenesisFullPath = RootDirectory + "/genesis.json"; ;

            IsRunningInstanceCloseFlag = new CgRoutine.BoolType();
            IsRunningInstanceCloseFlag.Set(true);

            ChainDirectory  = path + "Blockchain\\Ethereum\\chaindata";

            Commands = new Dictionary<ECgBlockchainCommand, string>(new ECgBlockchainCommandEqualityComparer());
            CommandRequests = new Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>>(new ECgBlockchainProcessTypeEqualityComparer());
            CurrentCommandRequest = null;
            Accounts = new Dictionary<string, ICgBlockchainAccount>();

            //SetCommand(ECgEthereumCommand.InitBlockchain, "\"" + ConsoleFullPath + "\" --datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
            //SetCommand(ECgEthereumCommand.SetDataDirectory, "\"" + ConsoleFullPath + "\" --datadir=\"" + ChainDirectory + "\" --networkid 15");
            SetCommand(ECgEthereumCommand.InitBlockchain, "--datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
            SetCommand(ECgEthereumCommand.SetDataDirectory, "--datadir=\"" + ChainDirectory + "\" --networkid 15");
            //SetCommand(ECgEthereumCommand.ChangeToRootDirectory, "cd /d \"" + RootDirectory + "\"");
            //SetCommand(ECgEthereumCommand.AttachToConsole, "\"" + ConsoleFullPath + "\" attach ipc:\\\\.\\pipe\\geth.ipc");
            SetCommand(ECgEthereumCommand.AttachToConsole, "attach ipc:\\\\.\\pipe\\geth.ipc");
            SetCommand(ECgEthereumCommand.ExitConsole, "exit");
            SetCommand(ECgEthereumCommand.NewAccount, "personal.newAccount(%s)");
            SetCommand(ECgEthereumCommand.UnlockAccount, "personal.unlockAccount(%s,%s,%s)");
            SetCommand(ECgEthereumCommand.StartMiner, "miner.start();");
            SetCommand(ECgEthereumCommand.StopMiner, "miner.stop();");

            OnBoardState = ECgEthereumOnBoardState.Init;
            OnBoardStateFlag = new TCgFlagType<ECgEthereumOnBoardState>(ECgEthereumOnBoardState.Init, ECgEthereumOnBoardState.Init);
        }

        private ICgBlockchain _Get()
        {
            return Instance;
        }

        public void Log(string msg)
        {
            UnityEngine.Debug.Log(msg);
        }

        public override void Shutdown()
        {
            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                ECgBlockchainProcessType processType = (ECgBlockchainProcessType)i;
                Process p                            = Processes[processType];
                
                if (p != null)
                    p.Kill();

                ProcessFlags[processType] = false;
            }
        }

        public override void SetCommand(ECgBlockchainCommand command, string str)
        {
            string value;
            Commands.TryGetValue(command, out value);

            if (value == "")
            {
                Commands.Add(command, str);
            }
            else
            {
                Commands[command] = str;
            }
        }

        public override void RunCommand(ECgBlockchainProcessType processType, string command)
        {
            Process p = GetProcess(processType);

            // RunningInstance
            if (processType == ECgBlockchainProcessType.RunningInstance)
            {
                if (p == null)
                {
                    Log("CgEthereum.RunCommand: Failed to run command: " + command + ". Process " + processType.ToString() + " has NOT started. Call StartPrivateChain().");
                    return;
                }
            }
            // Console
            if (processType == ECgBlockchainProcessType.Console)
            {
                if (p == null)
                {
                    Log("CgEthereum.RunCommand: Failed to run command: " + command + ". Process " + processType.ToString() + " has NOT started. Call OpenShell().");
                    return;
                }
            }

            if (LogIO.Log())
            {
                if (processType == ECgBlockchainProcessType.RunningInstance)
                    Log("Process (Input): " + command);
                if (processType == ECgBlockchainProcessType.Console)
                    Log("Console (Input): " + command);
            }

            p = GetProcess(processType);

            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            p.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            p.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            p.StandardInput.BaseStream.Flush();
        }

        public override void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null)
        {
            string value;
            Commands.TryGetValue(command, out value);

            if (value == INVALID_COMMAND)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.RunCommand: No command set for " + command.Name);
                return;
            }

            // Rebuild command if arguments where passed in
            if (args != null && args.Length > EMPTY)
            {
                // Create list of all string parts
                List<string> parts = new List<string>();
                parts.Add("");
                int index = 0;

                int commandLength = value.Length;

                for (int i = 0; i < commandLength; ++i)
                {
                    char c = value[i];

                    // Check for Wildcards
                    if (c == '%')
                    {
                        // Check for type
                        if (i < commandLength - 1)
                        {
                            char w = value[i + 1];

                            if (w == 's')
                            {
                                parts.Add("");
                                ++index;
                            }
                        }
                        else
                        {
                            parts[index] += c;
                        }
                    }
                    else
                    {
                        parts[index] += c;
                    }
                }

                // Add in arguments
                if (parts.Count == args.Length)
                {
                    value = "";

                    int argumentLength = args.Length;

                    for (int i = 0; i < argumentLength; ++i)
                    {
                        value += parts[i] + args[i].ToStr();
                    }
                }
                else
                {
                    UnityEngine.Debug.Log("CgEthereum.RunCommand: Failed to run command: " + command.Name + ". Wildcard count != Argument count (" + parts.Count + "," + args.Length + ")");
                }
            }
            RunCommand(processType, value);
        }

        public override void AddCommandRequest(ECgBlockchainProcessType processType, CgBlockchainCommandRequest request)
        {
            CommandRequests[processType].Enqueue(request);

            if (CurrentCommandRequest == null)
            {
                CurrentCommandRequest = CommandRequests[processType].Peek();

                RunCommand(processType, request.Command, request.Arguments);
            }
        }

        static void ProcessOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Process (Output): " + e.Data);
            }
        }

        static void ProcessErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Process (Error): " + e.Data);
            }
        }

        public void ConsoleOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Console (Output): " + e.Data);
            }

            CurrentCommandRequest.HasCompleted(e.Data);

            if (CurrentCommandRequest.HasCompleted(e.Data))
            {
                ECgBlockchainProcessType processType = ECgBlockchainProcessType.Console;

                CommandRequests[processType].Dequeue();

                if (CommandRequests[processType].Count > EMPTY)
                {
                    CgBlockchainCommandRequest request = CommandRequests[processType].Peek();

                    RunCommand(processType, request.Command, request.Arguments);
                }
                else
                {
                    CurrentCommandRequest = null;
                }
            }
        }

        public void ConsoleErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Console (Error): " + e.Data);
            }
        }

        public void OnProcessExited(object sender, EventArgs e)
        {
            if(LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Process): Exited");
            }

            Processes[ECgBlockchainProcessType.RunningInstance] = null;
            ProcessFlags[ECgBlockchainProcessType.RunningInstance] = false;
            IsRunningInstanceOpen = false;
            IsRunningInstanceCloseFlag.Set(true);
        }

        public void OnConsoleExited(object sender, EventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Console): Exited");
            }

            Processes[ECgBlockchainProcessType.Console] = null;
            ProcessFlags[ECgBlockchainProcessType.Console] = false;
            IsConsoleOpen = false;
        }

        public override void SetProcess(ECgBlockchainProcessType processType, Process p)
        {
            Processes[processType]    = p;
            ProcessFlags[processType] = true;
        }

        public override Process GetProcess(ECgBlockchainProcessType processType)
        {
            return Processes[processType];
        }

        public override void StartProcess(ECgBlockchainProcessType processType, CgBlockchainProcessStartInfo startInfo)
        {
            Process p = GetProcess(processType);

            if (p != null)
                return;

            p = new Process();

            SetProcess(processType, p);

            // ProcessStartInfo
            ProcessStartInfo psi    = p.StartInfo;
            psi.CreateNoWindow      = !ShowProcessWindow.Get();
            psi.UseShellExecute     = false;
            psi.FileName            = startInfo.FileName;
            psi.Arguments           = startInfo.Arguments;
            psi.ErrorDialog         = false;
            psi.RedirectStandardInput = startInfo.RedirectStandardInput;
            psi.RedirectStandardOutput = true;
            psi.RedirectStandardError = true;
            p.EnableRaisingEvents = true;

            if (processType == ECgBlockchainProcessType.Console)
            {
                p.OutputDataReceived += ConsoleOutputRecieved;
                p.ErrorDataReceived += ConsoleErrorRecieved;
                p.Exited += OnConsoleExited;
            }
            else
            {
                p.OutputDataReceived += ProcessOutputRecieved;
                p.ErrorDataReceived += ProcessErrorRecieved;
                p.Exited += OnProcessExited;
            }

            p.Start();
            p.BeginErrorReadLine();
            p.BeginOutputReadLine();
        }

        public override void StopProcess(ECgBlockchainProcessType processType)
        {
            if (Processes[processType] == null)
                return;
            Processes[processType].Kill();
            Processes[processType]    = null;
            ProcessFlags[processType] = false;
        }

        public override void OpenRunningInstance()
        {
            if (IsRunningInstanceOpen)
                return;

            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);

            Process p = new Process();
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.FileName = path + "Blockchain\\Ethereum\\Geth\\geth.exe";

            string ChainDirectory = path + "Blockchain\\Ethereum\\chaindata";

            p.StartInfo.Arguments = "--datadir=\"" + ChainDirectory + "\" --networkid 15";

            p.StartInfo.ErrorDialog = false;
            p.StartInfo.RedirectStandardInput = true;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.ErrorDataReceived += ProcessErrorRecieved;
            p.OutputDataReceived += ProcessOutputRecieved;
            p.Start();
            p.BeginErrorReadLine();
            p.BeginOutputReadLine();
            /*
            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName              = ConsoleFullPath;
            startInfo.Arguments             = Commands[ECgEthereumCommand.SetDataDirectory];
            startInfo.RedirectStandardInput = false;

            StartProcess(ECgBlockchainProcessType.RunningInstance, startInfo);
            */
            IsRunningInstanceOpen = true;
            IsRunningInstanceCloseFlag.Set(false);
        }

        public override void CreatePrivateChain()
        {
            // Create chaindata Directory
            if (!Directory.Exists(ChainDirectory))
            {
                Directory.CreateDirectory(ChainDirectory);
            }

            // Create genesis.json
            string json = Genesis.ToStr();

            File.WriteAllText(GenesisFullPath, json, System.Text.Encoding.ASCII);

            // Init
            IsRunningInstanceOpen = true;
            IsRunningInstanceCloseFlag.Set(false);

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName = ConsoleFullPath;
            startInfo.Arguments = Commands[ECgEthereumCommand.InitBlockchain];
            startInfo.RedirectStandardInput = false;

            StartProcess(ECgBlockchainProcessType.RunningInstance, startInfo);

            OnBoardState = ECgEthereumOnBoardState.Init;

            if (LogOnBoard.Log())
            {
                Log("CgEthereum.CreatePrivateChain: State Change: -> ECgEthereumOnBoardState.Init.");
            }
        }

        public override void StartPrivateChain()
        {
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, StartPrivateChain_Internal(this));
        }

        public static IEnumerator StartPrivateChain_Internal(CgEthereum eth)
        {
            eth.gi.Test0();

            yield return 2.0f;

            eth.gi.Test1();
            /*
            // Start if the Blockchain has already been initialized
            bool genesisExists = File.Exists(eth.GenesisFullPath);

            if (genesisExists)
            {
                eth.OpenRunningInstance();

                eth.OnBoardState = ECgEthereumOnBoardState.Start;

                if (LogOnBoard.Log())
                {
                    eth.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Init -> ECgEthereumOnBoardState.Start.");
                }
            }
            // Initialize then Start
            else
            {
                eth.CreatePrivateChain();

                yield return eth.IsRunningInstanceCloseFlag;

                eth.OpenRunningInstance();

                eth.OnBoardState = ECgEthereumOnBoardState.Start;

                if (LogOnBoard.Log())
                {
                    eth.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Init -> ECgEthereumOnBoardState.Start.");
                }
            }
            // Parse the Genesis file
            eth.Genesis.ParseFromFile(eth.GenesisFullPath);

            float connectionTime = 4.0f;

            yield return connectionTime;
            */

            // Attach / Open Console

            /*
            eth.OnBoardState = ECgEthereumOnBoardState.Attach;

            if (LogOnBoard.Log())
            {
                eth.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Init -> ECgEthereumOnBoardState.Start.");
            }
            */

            /*
            eth.Log("open");
            eth.OpenConsole();
            */

            //yield return 10.0f;

            //eth.Log("start");
            //eth.StartMiner();
            /*
            yield return 2.0f;

            eth.Log("stop");
            eth.StopMiner();
            */
        }

        public override void OpenConsole()
        {
            if (IsConsoleOpen)
                return;

            /*
            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);

            Process p = new Process();
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.FileName = path + "Blockchain\\Ethereum\\Geth\\geth.exe";

            p.StartInfo.Arguments = "attach ipc:\\\\.\\pipe\\geth.ipc";
            UnityEngine.Debug.Log(p.StartInfo.FileName + " " + p.StartInfo.Arguments);
            p.StartInfo.ErrorDialog = false;
            p.StartInfo.RedirectStandardInput = true;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.ErrorDataReceived += ConsoleErrorRecieved;
            p.OutputDataReceived += ConsoleOutputRecieved;
            p.Start();
            p.BeginErrorReadLine();
            p.BeginOutputReadLine();
            return;
            */
            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            /*
            startInfo.FileName = "cmd.exe";
            startInfo.Arguments = "";// "/K";
            startInfo.RedirectStandardInput = false;
            */
            
            startInfo.FileName              = ConsoleFullPath;
            startInfo.Arguments             = Commands[ECgEthereumCommand.AttachToConsole];
            startInfo.RedirectStandardInput = true;
            Log(startInfo.FileName + " " + startInfo.Arguments);
            //CgBlockchainCommandRequest request = new CgBlockchainCommandRequest()

            StartProcess(ECgBlockchainProcessType.Console, startInfo);

            //RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.AttachToConsole);
            IsConsoleOpen = true;
        }

        public override void CloseConsole()
        {
            if (!IsConsoleOpen)
                return;

            // StopProcess(ECgBlockchainProcessType.Console);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.ExitConsole);

            IsConsoleOpen = false;
        }

        public override void NewAccount(object payload)
        {
            string nickname = (string)payload;
            
            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(nickname, out iaccount);

            if (iaccount != null)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.NewAccount: Account with Nickname: " + nickname + " already exists.");
                return;
            }

            CgBlockchainCommandArgument[] args = new CgBlockchainCommandArgument[1];
            args[0]                            = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, nickname);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.NewAccount, args);
            // TODO: Need to fill in account details in ProcessOutputRecieved
            Accounts.Add(nickname, new CgEthereumAccount(nickname));
        }

        public override void UnlockAccount(object payload)
        {
            string nickname = (string)payload;

            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(nickname, out iaccount);

            if (iaccount != null)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.UnlockAccount: Account with Nickname: " + nickname + " does NOT exist.");
                return;
            }

            CgEthereumAccount account = (CgEthereumAccount)iaccount;

            CgBlockchainCommandArgument[] args;
            account.CreateUnlockArguments(out args);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.UnlockAccount, args);
        }

        public override void StartMiner()
        {
            if (IsMining)
                return;
            //if (!IsConsoleOpen)
            //   OpenConsole();
            RunCommand(ECgBlockchainProcessType.Console,"personal.listAccounts");
            //RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.StartMiner, null);
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.StopMiner, null);

            IsMining = false;
        }

        public void Test0()
        {
            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);

            Process p = new Process();
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.FileName = path + "Blockchain\\Ethereum\\Geth\\geth.exe";

            string ChainDirectory = path + "Blockchain\\Ethereum\\chaindata";

            p.StartInfo.Arguments = "--datadir=\"" + ChainDirectory + "\" --networkid 15";

            p.StartInfo.ErrorDialog = false;
            p.StartInfo.RedirectStandardInput = true;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.ErrorDataReceived += ProcessErrorRecieved;
            p.OutputDataReceived += ProcessOutputRecieved;
            p.Start();
            p.BeginErrorReadLine();
            p.BeginOutputReadLine();
        }

        public void Test1()
        {
            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);

            Process p = new Process();
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.FileName = path + "Blockchain\\Ethereum\\Geth\\geth.exe";

            p.StartInfo.Arguments = "attach ipc:\\\\.\\pipe\\geth.ipc";
            UnityEngine.Debug.Log(p.StartInfo.FileName + " " + p.StartInfo.Arguments);
            p.StartInfo.ErrorDialog = false;
            p.StartInfo.RedirectStandardInput = true;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.ErrorDataReceived += ConsoleErrorRecieved;
            p.OutputDataReceived += ConsoleOutputRecieved;
            p.Start();
            p.BeginErrorReadLine();
            p.BeginOutputReadLine();
        }
    }
}
