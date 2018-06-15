namespace CgCore
{
    using System;

    public interface ICgBlockchainAccount
    {
        #region "Data Members"

        string Nickname { get; set; }

        #endregion // Data Members

        string ToStr();
        void Parse(string str);
        void ParseFromFilePath(string path);
    }

    [Serializable]
    public abstract class FCgBlockchainAccount : ICgBlockchainAccount
    {
        #region "Data Members"

            #region "Interface"

        private string _Nickname;
        public string Nickname
        {
            get { return _Nickname; }
            set { _Nickname = value; }
        }

            #endregion // Interface

        #endregion // Data Members

        public FCgBlockchainAccount()
        {
        }

        public abstract string ToStr();
        public abstract void Parse(string str);
        public abstract void ParseFromFilePath(string path);
    }
}