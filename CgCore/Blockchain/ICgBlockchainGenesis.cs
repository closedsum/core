// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;

    public interface ICgBlockchainGenesis
    {
        string ToStr();
        void Parse(string str);
        void ParseFromFile(string filename);
    }

    [Serializable]
    public abstract class CgBlockchainGenesis : ICgBlockchainGenesis
    {
        public abstract string ToStr();
        public abstract void Parse(string str);
        public abstract void ParseFromFile(string filename);
    }
}
