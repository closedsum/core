// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.IO;
    using System.Collections.Generic;

    using Newtonsoft.Json;

    [Serializable]
    public struct FCgEthereumGenesisConfig
    {
        public int chainId;
        public int homesteadBlock;
        public int eip155Block;
        public int eip158Block;

        public void Init()
        {
            chainId = 15;
            homesteadBlock = 0;
            eip155Block = 0;
            eip158Block = 0;
        }
    }

    [Serializable]
    public struct FCgEthereumGenesisAddressBalance
    {
        public string balance;

        public FCgEthereumGenesisAddressBalance(string _balance)
        {
            balance = _balance;
        }
    }

    [Serializable]
    public class FCgEthereumGenesis : FCgBlockchainGenesis
    {
        public FCgEthereumGenesisConfig config;
        public string difficulty = "0x20";
        public string gasLimit = "0x2540BE400";
        public Dictionary<string, FCgEthereumGenesisAddressBalance> alloc;

        public FCgEthereumGenesis()
        {
            config.Init();
            alloc = new Dictionary<string, FCgEthereumGenesisAddressBalance>();
        }

        public override string ToStr()
        {
            return JsonConvert.SerializeObject(this);
        }

        public override void Parse(string str)
        {
            JsonConvert.PopulateObject(str, (object)this);
        }

        public override void ParseFromFilePath(string path)
        {
            if (File.Exists(path))
                Parse(File.ReadAllText(path));
        }
    }
}