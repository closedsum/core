namespace CgCore
{
    using System;
    using System.IO;

    using Newtonsoft.Json;

    using System.Collections.Generic;

    // TODO: Need a custom read/write to json
    [Serializable]
    public sealed class FCgEthereumABI
    {
        public bool constant;
        public List<string> inputs;
        public string name;
        public List<string> outputs;
        public bool payable;
        public string stateMutability;
        public string type;

        public FCgEthereumABI()
        {
            inputs = new List<string>();
            outputs = new List<string>();
        }
    }

    [Serializable]
    public sealed class FCgEthereumContract : FCgBlockchainContract
    {
        public List<FCgEthereumABI> ABI;
        public string Address;
        public string ContractVariableName;
        public string InstanceVariableName;

        public FCgEthereumContract(string name) : base(name)
        {
            ABI = new List<FCgEthereumABI>();
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

        public string GetAddressAsArg()
        {
            return "'0x" + Address + "'";
        }
    }

    public struct FCgEthereumWeb3DeployLink
    {
        public readonly ECgBlockchainContract Contract;
        public readonly string Link;

        public FCgEthereumWeb3DeployLink(ECgBlockchainContract contract, string link)
        {
            Contract = contract;
            Link = link;
        }
    }
}