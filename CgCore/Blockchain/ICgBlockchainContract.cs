namespace CgCore
{
    using System.Collections;
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
    }

    public class CgBlockchainContract : ICgBlockchainContract
    {
        private string _Name;
        public string Name
        {
            get { return _Name; }
            set { _Name = value; }
        }
    }
}
