using UnityEngine;
using System;
using System.Linq;
using System.Collections;

public class ConsoleSubmitAction : ConsoleAction
{
    public ConsoleGUI consoleGUI;
    private ConsoleCommandsRepository CommandsRepository;
    private ConsoleLog Log;

    private void Start()
    {
        CommandsRepository  = ConsoleCommandsRepository.Instance;
        Log                 = ConsoleLog.Instance;
    }

    public override void Activate()
    {
        string[] parts = consoleGUI.CurrentInput.Split(' ');
        string command = parts[0];
        string[] args  = parts.Skip(1).ToArray();

        Log.Log("> " + consoleGUI.CurrentInput);

        if (CommandsRepository.HasCommand(command))
        {
            Log.Log(CommandsRepository.ExecuteCommand(command, args));
        }
        else
        {
            Log.Log("Command " + command + " not found");
        }
    }
}
