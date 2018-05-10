namespace CgCore
{
    using System;
    using System.IO;

    using Newtonsoft.Json;

    using System.Collections.Generic;

    public sealed class CgEthereumABIData
    {
        public bool constant;
        public List<string> inputs;
        public string name;
        public List<string> outputs;
        public bool payable;
        public string stateMutability;
        public string type;
    }

    [Serializable]
    public sealed class CgEthereumContract : CgBlockchainContract
    {
        public string Address;
        public string ContractVariableName;
        public string InstanceVariableName;

        public CgEthereumContract(string name) : base(name)
        {
            Address = "";
            ContractVariableName = name.ToLower() + "Contract";
            InstanceVariableName = name.ToLower() + "Instance";
        }

        public override bool IsValid()
        {
            return Address != "";
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

    public struct CgEthereumWeb3DeployLink
    {
        public string ContractName;
        public string LinkName;

        public CgEthereumWeb3DeployLink(string contract, string link)
        {
            ContractName = contract;
            LinkName = link;
        }
    }
}