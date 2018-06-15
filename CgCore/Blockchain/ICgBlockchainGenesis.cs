// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;

    public interface IFCgBlockchainGenesis
    {
        string ToStr();
        void Parse(string str);
        void ParseFromFilePath(string path);
    }

    [Serializable]
    public abstract class FCgBlockchainGenesis : IFCgBlockchainGenesis
    {
        public abstract string ToStr();
        public abstract void Parse(string str);
        public abstract void ParseFromFilePath(string path);
    }
}
