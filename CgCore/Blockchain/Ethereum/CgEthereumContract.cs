namespace CgCore
{
    using System.Collections;
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

    public sealed class CgEthereumContract : CgBlockchainContract
    {
        public List<CgEthereumABIData> ABI;
        public string Contruction;
        public string Instantiation;

        public string from;
        public string data;
        public string gas;
    }
}