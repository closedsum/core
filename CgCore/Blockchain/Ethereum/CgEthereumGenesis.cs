namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

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

        public void Init()
        {
            balance = "0";
        }
    }

    [Serializable]
    public struct CgEthereumGenesisAllocTemp
    {
    }

    [Serializable]
    public class CgEthereumGenesis : CgBlockchainGenesis
    {
        public CgEthereumGenesisConfig config;
        public string difficulty = "20";
        public string gasLimit = "2100000";
        // TODO: Need to be able to Serialize / Deserialize Dictionary
        public CgEthereumGenesisAllocTemp alloc;
        //public Dictionary<string, CgEthereumGenesisAddressBalance> alloc;

        public CgEthereumGenesis()
        {
            config.Init();
            //alloc = new Dictionary<string, CgEthereumGenesisAddressBalance>();
            alloc = new CgEthereumGenesisAllocTemp();
        }

        public override void Parse(string str)
        {
            CgEthereumGenesis genesis = JsonUtility.FromJson<CgEthereumGenesis>(str);
            Copy(genesis);
        }

        public void Copy(CgEthereumGenesis copy)
        {
            config      = copy.config;
            difficulty  = copy.difficulty;
            gasLimit    = copy.gasLimit;
            alloc       = copy.alloc;
        }
    }
}