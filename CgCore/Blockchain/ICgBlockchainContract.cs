namespace CgCore
{
    using System;
    using System.Collections.Generic;

    public class CgBlockchainContractKey
    {
        public string Key;
    }

    public sealed class CgBlockchainContractKeyEqualityComparer : IEqualityComparer<CgBlockchainContractKey>
    {
        public bool Equals(CgBlockchainContractKey lhs, CgBlockchainContractKey rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(CgBlockchainContractKey x)
        {
            return x.GetHashCode();
        }
    }


    public interface ICgBlockchainContract
    {
        string Name { get; set; }

        bool IsValid();
        string ToStr();
        void Parse(string str);
        void ParseFromFilePath(string path);
    }

    [Serializable]
    public abstract class CgBlockchainContract : ICgBlockchainContract
    {
        private string _Name;
        public string Name
        {
            get { return _Name; }
            set { _Name = value; }
        }

        public CgBlockchainContract(){}
        public CgBlockchainContract(string name)
        {
            Name = name;
        }

        public abstract bool IsValid();
        public abstract string ToStr();
        public abstract void Parse(string str);
        public abstract void ParseFromFilePath(string path);
    }
}
