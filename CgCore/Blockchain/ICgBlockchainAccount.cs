namespace CgCore
{
    public interface ICgBlockchainAccount
    {
        #region "Data Members"

        string Nickname { get; set; }

        #endregion // Data Members
    }

    public abstract class CgBlockchainAccount : ICgBlockchainAccount
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

        public CgBlockchainAccount(string nickname)
        {
            Nickname = nickname;
        }
    }
}