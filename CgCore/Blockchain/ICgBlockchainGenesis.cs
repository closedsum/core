namespace CgCore
{
    using System;

    public interface ICgBlockchainGenesis
    {
        string Filename { get; set; }

        void Parse(string str);
    }

    [Serializable]
    public abstract class CgBlockchainGenesis : ICgBlockchainGenesis
    {
        private string _Filename;
        public string Filename
        {
            get { return _Filename; }
            set { _Filename = value; }
        }

        public abstract void Parse(string str);
    }
}
