using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public delegate string ConsoleCommandCallback(params string[] args);

public class ConsoleCommandsRepository
{
    private static ConsoleCommandsRepository instance;
    public static ConsoleCommandsRepository Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new ConsoleCommandsRepository();
            }
            return instance;
        }
    }

    private Dictionary<string, ConsoleCommandCallback> Repository;

    public ConsoleCommandsRepository()
    {
        Repository = new Dictionary<string, ConsoleCommandCallback>();
    }

    public void RegisterCommand(string command, ConsoleCommandCallback callback)
    {
        Repository[command] = new ConsoleCommandCallback(callback);
    }

    public bool HasCommand(string command)
    {
        return Repository.ContainsKey(command);
    }

    public List<string> SearchCommands(string str)
    {
        string[] keys = new string[Repository.Count];

        Repository.Keys.CopyTo(keys, 0);

        List<string> output = new List<string>();

        foreach (string key in keys)
        {
            if (key.StartsWith(str))
                output.Add(key);
        }
        return output;
    }

    public string ExecuteCommand(string command, string[] args)
    {
        if (HasCommand(command))
        {
            return Repository[command](args);
        }
        else
        {
            return "Command not found";
        } 
    }
}
