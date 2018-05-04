// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.IO;
    using System.Collections.Generic;

    using Newtonsoft.Json;

    [Serializable]
    public struct CgEthereumGenesisConfig
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
    public struct CgEthereumGenesisAddressBalance
    {
        public string balance;

        public CgEthereumGenesisAddressBalance(string _balance)
        {
            balance = _balance;
        }
    }

    [Serializable]
    public class CgEthereumGenesis : CgBlockchainGenesis
    {
        public CgEthereumGenesisConfig config;
        public string difficulty = "20";
        public string gasLimit = "2100000";
        public Dictionary<string, CgEthereumGenesisAddressBalance> alloc;

        public CgEthereumGenesis()
        {
            config.Init();
            alloc = new Dictionary<string, CgEthereumGenesisAddressBalance>();
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