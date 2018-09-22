namespace CgCore
{
    using System;
    using System.Diagnostics;
    using System.Collections.Generic;

    public sealed class FECgProcess : FECgEnum_byte
    {
        public FECgProcess(byte value, string name) : base(value, name) { }
    }
    
    public class EMCgProcess : TCgEnumMap<FECgProcess, byte>
    {
        private static EMCgProcess _Instance;
        public static EMCgProcess Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgProcess();
                }
                return _Instance;
            }
        }

        public static EMCgProcess Get()
        {
            return Instance;
        }
    }

    public sealed class FCgProcessCache : TCgPooledObjectCache<FECgProcess, TCgPooledObject<FECgProcess, FCgProcessPayload>, FCgProcessPayload>
    {
    }

    public enum ECgProcessMonitorOutputEventPurpose : byte
    {
        FireOnce,
        Loop,
        MAX
    }

    public sealed class FCgProcessMonitorOutputEvent
    {
        public sealed class CompletedEvent : TCgMulticastDelegate_OneParam<string> { }

        private string Name;
        public ECgProcessMonitorOutputEventPurpose Purpose;
        private FCgStringParagraph Paragraph;
        private bool Completed;
        private CompletedEvent Event;

        public FCgProcessMonitorOutputEvent(string name, FCgStringParagraph paragraph, ECgProcessMonitorOutputEventPurpose purpose = ECgProcessMonitorOutputEventPurpose.FireOnce)
        {
            Name = name;
            Paragraph = paragraph;
            Event = new CompletedEvent();
        }

        public void AddEvent(CompletedEvent.Event e)
        {
            Event.Add(e);
        }

        public void ProcessOutput(string output)
        {
            if (Completed)
                return;

            Paragraph.ProcessInput(output);

            Completed = Paragraph.HasCompleted();

            if (Completed)
            {
                Event.Broadcast(Name);
            }
        }

        public void Clear()
        {
            Completed = false;
            Paragraph.Clear();
        }

        public void Reset()
        {
            Clear();
            Event.Clear();
        }

        public bool HasCompleted()
        {
            return Completed;
        }
    }

    public class FCgProcess : TCgPooledObject<FECgProcess, FCgProcessPayload>
    {
        public static FCgConsoleVariableLog LogCommandRequest = new FCgConsoleVariableLog("log.process.command.request", false, "Log Process Command Request", (int)ECgConsoleVariableFlag.Console);

        public sealed class FOutputDataRecieved : TCgMulticastDelegate_TwoParams<object, DataReceivedEventArgs> { }
        public sealed class FErrorDataRecieved : TCgMulticastDelegate_TwoParams<object, DataReceivedEventArgs> { }
        public sealed class FExited : TCgMulticastDelegate_TwoParams<object, EventArgs> { }

        #region "Data Members"

        public Process P;
        public bool IsRunning;

        public FOutputDataRecieved OutputDataRecieved_Event;
        public FErrorDataRecieved ErrorDataRecieved_Event;
        public FExited Exited_Event;

        private List<FCgProcessMonitorOutputEvent> MonitorOuputEvents;

        #endregion // Data Members

        public FCgProcess() : base()
        {
            Cache = new FCgProcessCache();

            OutputDataRecieved_Event = new FOutputDataRecieved();
            ErrorDataRecieved_Event = new FErrorDataRecieved();
            Exited_Event = new FExited();

            MonitorOuputEvents = new List<FCgProcessMonitorOutputEvent>();
        }

        #region "Interface"

        public override void Allocate(FCgProcessPayload payload)
        {
            base.Allocate(payload);

            P.StartInfo.CreateNoWindow = payload.CreateNoWindow;
            P.StartInfo.UseShellExecute = payload.UseShellExecute;
            P.StartInfo.FileName = payload.Filename;
            P.StartInfo.Arguments = payload.Arguments;
            P.StartInfo.ErrorDialog = payload.ErrorDialog;
            P.StartInfo.RedirectStandardInput = payload.RedirectStandardInput;
            P.StartInfo.RedirectStandardOutput = payload.RedirectStandardOutput;
            P.StartInfo.RedirectStandardError = payload.RedirectStandardError;
            P.EnableRaisingEvents = payload.EnableRaisingEvents;

            payload.OutputDataRecieved_Event.CopyTo(OutputDataRecieved_Event);
            payload.ErrorDataRecieved_Event.CopyTo(ErrorDataRecieved_Event);
            payload.Exited_Event.CopyTo(Exited_Event);

            foreach (FCgProcessMonitorOutputEvent e in payload.MonitorOuputEvents)
            {
                MonitorOuputEvents.Add(e);
            }

            IsRunning = true;

            P.Start();

            if (payload.RedirectStandardError)
                P.BeginErrorReadLine();
            if (payload.RedirectStandardOutput)
                P.BeginOutputReadLine();
        }

        public override void DeAllocate()
        {
            base.DeAllocate();

            OutputDataRecieved_Event.Clear();
            ErrorDataRecieved_Event.Clear();
            Exited_Event.Clear();

            MonitorOuputEvents.Clear();

            if (IsRunning)
                P.Kill();

            IsRunning = false;
        }

        #endregion // Interface

        public void RunCommand(string command)
        {
            P.StandardInput.Write(command);
            P.StandardInput.Write("\n");
            P.StandardInput.Flush();

            // TODO: Have an option to choose encoding
            /*
            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            P.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            P.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            P.StandardInput.BaseStream.Flush();
            */
        }

        public void AddMonitorOuputEvent(FCgProcessMonitorOutputEvent e)
        {
            MonitorOuputEvents.Add(e);
        }

        public void ProcessMonitorOutputEvents(string ouput)
        {
            int count = MonitorOuputEvents.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                FCgProcessMonitorOutputEvent o = MonitorOuputEvents[i];

                o.ProcessOutput(ouput);

                if (o.HasCompleted())
                {
                    o.Clear();

                    // FireOnce
                    if (o.Purpose == ECgProcessMonitorOutputEventPurpose.FireOnce)
                        MonitorOuputEvents.RemoveAt(i);
                }
            }
        }

        public void OnOutputDataRecieved(object sender, DataReceivedEventArgs e)
        {
            OutputDataRecieved_Event.Broadcast(sender, e);
            ProcessMonitorOutputEvents(e.Data);
        }

        public void OnErrorDataRecieved(object sender, DataReceivedEventArgs e)
        {
            ErrorDataRecieved_Event.Broadcast(sender, e);
            ProcessMonitorOutputEvents(e.Data);
        }

        public void OnExited(object sender, EventArgs e)
        {
            Exited_Event.Broadcast(sender, e);

            IsRunning = false;
        }
    }
}
