// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgManagerInput_Action_Default : TCgMulticastDelegate_TwoParams<FECgInputAction, ECgInputEvent> { }
    public class FCgManagerInput_Action : TCgMulticastDelegate_OneParam<FECgInputAction> { }
    public class FCgManagerInput_Axis_Default : TCgMulticastDelegate_ThreeParams<FECgInputAction, ECgInputEvent, float> { }
    public class FCgManagerInput_Axis : TCgMulticastDelegate_TwoParams<FECgInputAction, float> { }
    public class FCgManagerInput_Location_Default : TCgMulticastDelegate_ThreeParams<FECgInputAction, ECgInputEvent, Vector3> { }
    public class FCgManagerInput_Location : TCgMulticastDelegate_TwoParams<FECgInputAction, Vector3> { }
    public class FCgManagerInput_Location_Raw : TCgMulticastDelegate_OneParam<Vector3> { }
    public class FCgManagerInput_Rotation_Default : TCgMulticastDelegate_ThreeParams<FECgInputAction, ECgInputEvent, Vector3> { }
    public class FCgManagerInput_Rotation : TCgMulticastDelegate_TwoParams<FECgInputAction, Vector3> { }
    public class FCgManagerInput_Rotation_Raw : TCgMulticastDelegate_OneParam<Vector3> { }

    public class FCgManager_Input
    {
        #region "Constants"

        public static readonly int INPUT_POOL_SIZE = 65535;
        public static readonly int MAX_INPUT_FRAMES = 300;

        #endregion // Constants
        
        #region "Delegates"

        #endregion // Delegates

        #region "Data Members"

        public MonoBehaviour InputOwner;

        //public float CurrentDeltaTime;

        private Dictionary<KeyCode, FCgKeyInput> RawKeyInputs;
        public List<FCgKeyInput> RawKeyInputsPressed;

        public FCgInput[] InputPool;

        public List<FCgInput> QueuedInputsForNextFrame;

        private int CurrentInputPoolIndex;

        public FCgInputFrame[] InputFrames;

        public int CurrentInputFrameIndex;

        public FCgInputFrame CurrentInputFrame;

        public int CurrentInputActionMap;

        public List<FECgGameEvent> QueuedGameEventsForNextFrame;

        public FCgInputProfile InputProfile;

        #region "Actions"

        protected List<FCgInput_Base> Inputs;
        protected List<FCgInputInfo> Infos;

                #region "Pressed Events"

        public FCgManagerInput_Action_Default Action_Event;
        public FCgManagerInput_Action FirstPressed_Event;
        public FCgManagerInput_Action Pressed_Event;
        public FCgManagerInput_Action FirstReleased_Event;

                #endregion // Pressed Events

                #region "Axis Events

        public FCgManagerInput_Axis_Default Axis_Event;
        public FCgManagerInput_Axis Axis_FirstMoved_Event;
        public FCgManagerInput_Axis Axis_Moved_Event;
        public FCgManagerInput_Axis Axis_FirstStationary_Event;
        public FCgManagerInput_Axis Axis_Stationary_Event;

                #endregion // Axis Events

                #region "Location Events"

        public FCgManagerInput_Location_Default Location_Event;
        public FCgManagerInput_Location Location_FirstMoved_Event;
        public FCgManagerInput_Location Location_Moved_Event;
        public FCgManagerInput_Location Location_FirstStationary_Event;
        public FCgManagerInput_Location Location_Stationary_Event;

                    // Mouse

        public Vector3 CurrentMousePosition;

        public FCgManagerInput_Location_Raw Mouse_Location_Raw;

                    // VR

        public FCgManagerInput_Location_Raw HMD_Location_Raw;
        public FCgManagerInput_Location_Raw LeftHand_Location_Raw;
        public FCgManagerInput_Location_Raw RightHand_Location_Raw;

                #endregion // Location Events

                #region "Rotation Events"

        public FCgManagerInput_Rotation_Default Rotation_Event;
        public FCgManagerInput_Rotation Rotation_FirstMoved_Event;
        public FCgManagerInput_Rotation Rotation_Moved_Event;
        public FCgManagerInput_Rotation Rotation_FirstStationary_Event;
        public FCgManagerInput_Rotation Rotation_Stationary_Event;

                    // VR

        public FCgManagerInput_Rotation_Raw HMD_Rotation_Raw;
        public FCgManagerInput_Rotation_Raw LeftHand_Rotation_Raw;
        public FCgManagerInput_Rotation_Raw RigthHand_Rotation_Raw;

                #endregion // Rotation Events

        #endregion // Action

        #endregion // Data Members

        public FCgManager_Input()
        {
            // InputPool
            InputPool = new FCgInput[INPUT_POOL_SIZE];

            for (ushort i = 0; i < INPUT_POOL_SIZE; ++i)
            {
                InputPool[i] = new FCgInput(i);
            }

            QueuedInputsForNextFrame = new List<FCgInput>();

            // InputFrames
            InputFrames = new FCgInputFrame[MAX_INPUT_FRAMES];

            for (ushort i = 0; i < MAX_INPUT_FRAMES; ++i)
            {
                InputFrames[i] = new FCgInputFrame();
            }

            // Initialize array of RawKeyInputs
            Array keyValues  = Enum.GetValues(typeof(KeyCode));
            int keyCodeCount = keyValues.Length;

            RawKeyInputs = new Dictionary<KeyCode, FCgKeyInput>(new FKeyCodeEqualityComparer());

            for (int i = 0; i < keyCodeCount; ++i)
            {
                KeyCode key = (KeyCode)keyValues.GetValue(i);
                // RightCommand and RightApple have the same value
                if (RawKeyInputs.ContainsKey(key))
                    continue;
                RawKeyInputs.Add(key, new FCgKeyInput(key));
            }

            RawKeyInputsPressed = new List<FCgKeyInput>();

            QueuedGameEventsForNextFrame = new List<FECgGameEvent>();

            Inputs = new List<FCgInput_Base>();
            Infos = new List<FCgInputInfo>();

            // Events
             Action_Event = new FCgManagerInput_Action_Default();
            FirstPressed_Event = new FCgManagerInput_Action();
            Pressed_Event = new FCgManagerInput_Action();
            FirstReleased_Event = new FCgManagerInput_Action();

            Axis_Event = new FCgManagerInput_Axis_Default();
            Axis_FirstMoved_Event = new FCgManagerInput_Axis();
            Axis_Moved_Event = new FCgManagerInput_Axis();
            Axis_FirstStationary_Event = new FCgManagerInput_Axis();
            Axis_Stationary_Event = new FCgManagerInput_Axis();

            Location_Event = new FCgManagerInput_Location_Default();
            Location_FirstMoved_Event = new FCgManagerInput_Location();
            Location_Moved_Event = new FCgManagerInput_Location();
            Location_FirstStationary_Event = new FCgManagerInput_Location();
            Location_Stationary_Event = new FCgManagerInput_Location();

            Mouse_Location_Raw = new FCgManagerInput_Location_Raw();

            HMD_Location_Raw = new FCgManagerInput_Location_Raw();
            LeftHand_Location_Raw = new FCgManagerInput_Location_Raw();
            RightHand_Location_Raw = new FCgManagerInput_Location_Raw();

            Rotation_Event = new FCgManagerInput_Rotation_Default();
            Rotation_FirstMoved_Event = new FCgManagerInput_Rotation();
            Rotation_Moved_Event = new FCgManagerInput_Rotation();
            Rotation_FirstStationary_Event = new FCgManagerInput_Rotation();
            Rotation_Stationary_Event = new FCgManagerInput_Rotation();

            HMD_Rotation_Raw = new FCgManagerInput_Rotation_Raw();
            LeftHand_Rotation_Raw = new FCgManagerInput_Rotation_Raw();
            RigthHand_Rotation_Raw = new FCgManagerInput_Rotation_Raw();
        }

        protected void DefineInputActionValue(FCgInput_Action input, FECgInputAction action, int ActionMap)
        {
            input.Manager_Input = this;
            input.Action = action;
            input.ActionMap = ActionMap;
            Inputs[(byte)action] = input;
            Infos[(byte)action] = input.Info;
        }

        protected virtual void BindInputs()
        {
        }

        protected void BindInput(KeyCode key, FECgInputAction action, ECgInputEvent e, CgMulticastDelegate.Event del)
        {
            FCgKeyInput keyInput;
            RawKeyInputs.TryGetValue(key, out keyInput);
            keyInput.Bind(action, e, del);
        }

        protected void BindInputAction(KeyCode key, FCgInput_Action input)
        {
            BindInput(key, input.Action, ECgInputEvent.FirstPressed, input.FirstPressed);
            BindInput(key, input.Action, ECgInputEvent.FirstReleased, input.FirstReleased);
        }

        private void RecordRawInputs()
        {
            RawKeyInputsPressed.Clear();

            Dictionary<KeyCode, FCgKeyInput>.ValueCollection keyInputs = RawKeyInputs.Values;

            foreach (FCgKeyInput keyInput in keyInputs)
            {
                KeyCode key     = keyInput.Key;
                ECgInputEvent e = keyInput.Event;

                // Pressed
                if (Input.GetKey(key))
                {
                    if (e == ECgInputEvent.FirstPressed || e == ECgInputEvent.Pressed)
                        keyInput.Set(ECgInputEvent.Pressed, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstPressed, Time.time, Time.unscaledTime, 0);
                    RawKeyInputsPressed.Add(keyInput);
                }
                // Released
                else
                {
                    if (e == ECgInputEvent.FirstReleased || e == ECgInputEvent.Released)
                        keyInput.Set(ECgInputEvent.Released, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstReleased, Time.time, Time.unscaledTime, 0);
                }
            }
        }

        public virtual void PreProcessInput(float deltaTime)
        {
            //CurrentDeltaTime       = deltaTime;
            CurrentInputFrameIndex = (CurrentInputFrameIndex + 1) % MAX_INPUT_FRAMES;
            InputFrames[CurrentInputFrameIndex].Init(Time.time, Time.unscaledTime, deltaTime, (ulong)Time.frameCount);

            RecordRawInputs();

            CurrentMousePosition = Input.mousePosition;

            if (Mouse_Location_Raw != null)
                Mouse_Location_Raw.Broadcast(CurrentMousePosition);

            // VR
        }

        public virtual void PostProcessInput(float deltaTime)
        {
            // TODO: Potentially also capture sustained "released" inputs

            // TODO: This would be the place to process an action that is a combination of multiple inputs in a frame (or over multiple frames)

            FCgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            // Add Queued Inputs
            int queuedInputCount = QueuedInputsForNextFrame.Count;

            for (int i = 0; i < queuedInputCount; ++i)
            {
                inputFrame.Inputs.Add(QueuedInputsForNextFrame[i]);
            }
            QueuedInputsForNextFrame.Clear();

            // Set FirstReleased Events to Released after 1 Frame

            // TODO: Potentially Optimize to O(n) versus O(n^2)
            for (byte i = 0; i < EMCgInputAction.Get().Count; ++i)
            {
                FCgInputInfo info      = Infos[i];
                FECgInputAction action = EMCgInputAction.Get().GetEnumAt(i);
                int inputCount        = inputFrame.Inputs.Count;

                // Transition From FirstPressed to Pressed
                if (info.Event == ECgInputEvent.FirstPressed &&
                    info.Last_Event == ECgInputEvent.FirstPressed)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (inputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Pressed;
                }
                // Transition from FirstReleased to Released
                if (info.Event == ECgInputEvent.FirstReleased &&
                    info.Last_Event == ECgInputEvent.FirstReleased)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (inputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Released;
                }
                // Transition From FireMoved to Moved
                if (info.Event == ECgInputEvent.FirstMoved &&
                    info.Last_Event == ECgInputEvent.FirstMoved)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (inputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Moved;
                }
                // Transition from FirstStationary to Stationary
                if (info.Event == ECgInputEvent.FirstStationary &&
                    info.Last_Event == ECgInputEvent.FirstStationary)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (inputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Stationary;
                }
                // Update Last_Actions.
                info.Last_Event = info.Event;

                // Currently NO Bindings for PRESSED Inputs, so manually add them
                if (info.Event == ECgInputEvent.Pressed)
                    AddInput(action, ECgInputEvent.Pressed);
            }
            // Process Inputs
            int _inputCount = inputFrame.Inputs.Count;

            for (byte i = 0; i < _inputCount; ++i)
            {
                ProcessInput(InputOwner, null, inputFrame.Inputs[i], deltaTime);
            }

            // Log Actions
            if (FCgCVars.LogInputs.Log())
            {
                string inputActionMapAsString = EMCgInputActionMap.Get().MaskToStr(CurrentInputActionMap);

                Debug.Log("FCgManager_Input.PostProcessInput: ActionMap: " + inputActionMapAsString + " Frame: " + inputFrame.Frame + " Time: " + inputFrame.Time + " DeltaTime: " + inputFrame.DeltaTime + " Count: " + inputFrame.Inputs.Count);

                for (byte i = 0; i < _inputCount; ++i)
                {
                    FCgInput input = inputFrame.Inputs[i];

                    string action = input.Action.Name;
                    string e      = input.Event.ToString();

                    // Void - No Value
                    if ((FCgCVars.LogInputAll.Log() || FCgCVars.LogInputActions.Log()) &&
                        Infos[(byte)input.Action].ValueType == ECgInputValue.Void)
                    {
                        Debug.Log("FCgManager_Input.PostProcessInput: " + action + ": " + e);
                    }
                    // Float
                    if ((FCgCVars.LogInputAll.Log() || FCgCVars.LogInputAxis.Log()) &&
                        Infos[(byte)input.Action].ValueType == ECgInputValue.Float)
                    {
                        Debug.Log("FCgManager_Input.PostProcessInput: " + action + ": " + e + " Value: " + input.Value);
                    }
                    // Vector
                    if ((FCgCVars.LogInputAll.Log() || FCgCVars.LogInputLocations.Log()) &&
                        Infos[(byte)input.Action].ValueType == ECgInputValue.Vector)
                    {
                        Debug.Log("FCgManager_Input.PostProcessInput: " + action + ": " + e + " Value: " + input.Location.ToString());
                    }
                    // Rotator
                    if ((FCgCVars.LogInputAll.Log() || FCgCVars.LogInputRotations.Log()) &&
                        Infos[(byte)input.Action].ValueType == ECgInputValue.Rotator)
                    {
                        Debug.Log("FCgManager_Input.PostProcessInput: " + action + ": " + e + " Value: " + input.Rotation.ToString());
                    }
                }
            }
            
            // Copy the Current Input Frame
            CurrentInputFrame = inputFrame;
            // Determine Game Events
            //DetermineGameEvents(InputFrame.Inputs);
        }

        public virtual void ProcessInput(MonoBehaviour actionOwner, FCgInput previousInput, FCgInput currentInput, float deltaTime)
        {
            if (currentInput == null)
                return;

            FECgInputAction action   = currentInput.Action;
            ECgInputEvent e         = currentInput.Event;
            ECgInputEvent last_e    = Infos[(byte)action].Last_Event;
            float value             = currentInput.Value;
            Vector3 location        = currentInput.Location;
            Vector3 rotation        = currentInput.Rotation;

            FCgInputInfo info = Infos[(byte)action];

            // Action
            if (info.Type == ECgInputType.Action)
            {
                if (e == ECgInputEvent.Pressed &&
                    (last_e == ECgInputEvent.FirstPressed || last_e == ECgInputEvent.Pressed))
                {
                    info.Duration += deltaTime;
                }
                else
                {
                    info.Duration = 0.0f;
                }

                Action_Event.Broadcast(action, e);

                // FirstPressed
                if (e == ECgInputEvent.FirstPressed)
                    FirstPressed_Event.Broadcast(action);
                // Pressed
                else
                if (e == ECgInputEvent.Pressed)
                    Pressed_Event.Broadcast(action);
                // FirstReleased
                else
                if (e == ECgInputEvent.FirstReleased)
                    FirstReleased_Event.Broadcast(action);
            }
            // Axis
            if (info.Type == ECgInputType.Axis)
            {
                if ((e == ECgInputEvent.FirstMoved || e == ECgInputEvent.Moved) &&
                    (last_e == ECgInputEvent.FirstMoved || last_e == ECgInputEvent.Moved))
                {
                    info.Duration += deltaTime;
                }
                else
                {
                    info.Duration = 0.0f;
                }

                Axis_Event.Broadcast(action, e, value);

                // FirstMoved
                if (e == ECgInputEvent.FirstMoved)
                    Axis_FirstMoved_Event.Broadcast(action, value);
                // Moved
                else
                if (e == ECgInputEvent.Moved)
                    Axis_Moved_Event.Broadcast(action, value);
                // FirstStationary
                else
                if (e == ECgInputEvent.FirstStationary)
                    Axis_FirstStationary_Event.Broadcast(action, value);
                // Stationary
                else
                if (e == ECgInputEvent.Stationary)
                    Axis_Stationary_Event.Broadcast(action, value);
            }
            // Location
            else
            if (info.Type == ECgInputType.Location)
            {
                Location_Event.Broadcast(action, e, location);

                // FirstMoved
                if (e == ECgInputEvent.FirstMoved)
                    Location_FirstMoved_Event.Broadcast(action, location);
                // Moved
                else
                if (e == ECgInputEvent.Moved)
                    Location_Moved_Event.Broadcast(action, location);
                // FirstStationary
                else
                if (e == ECgInputEvent.FirstStationary)
                    Location_FirstStationary_Event.Broadcast(action, location);
                // Stationary
                else
                if (e == ECgInputEvent.Stationary)
                    Location_Stationary_Event.Broadcast(action, location);
            }
            // Rotation
            else
            if (info.Type == ECgInputType.Rotation)
            {
                Rotation_Event.Broadcast(action, e, rotation);

                // FirstMoved
                if (e == ECgInputEvent.FirstMoved)
                    Rotation_FirstMoved_Event.Broadcast(action, rotation);
                // Moved
                else
                if (e == ECgInputEvent.Moved)
                    Rotation_Moved_Event.Broadcast(action, rotation);
                // FirstStationary
                else
                if (e == ECgInputEvent.FirstStationary)
                    Rotation_FirstStationary_Event.Broadcast(action, rotation);
                // Stationary
                else
                if (e == ECgInputEvent.Stationary)
                    Rotation_Stationary_Event.Broadcast(action, rotation);
            }
        }

        public FCgInput AllocateInput(FECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
            for (int i = 0; i < INPUT_POOL_SIZE; ++i)
            {
                CurrentInputPoolIndex = (CurrentInputPoolIndex + i) % INPUT_POOL_SIZE;
                FCgInput input         = InputPool[CurrentInputPoolIndex];

                // Add Input to InputFrame
                if (!input.IsAllocated)
                {
                    input.Allocate(action, e, value, location, rotation);
                    return input;
                }
            }
            Debug.LogError("FCgManager_Input::AllocateInput: Input Pool has been exhaused.");
            return null;
        }

        public virtual void AddInput(FECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
            FCgInput input = AllocateInput(action, e, value, location, rotation);
            InputFrames[CurrentInputFrameIndex].Inputs.Add(input);
        }

        public virtual void QueueInput(FECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
	        FCgInput input = AllocateInput(action, e, value, location, rotation);

            QueuedInputsForNextFrame.Add(input);
        }

        public void ConsumeInput(FECgInputAction action)
        {
            FCgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                {
                    input.IsConsumed = true;
                    break;
                }
            }

            count = CurrentInputFrame.Inputs.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                FCgInput input = CurrentInputFrame.Inputs[i];

                if (input.Action == action)
                {
                    CurrentInputFrame.Inputs.RemoveAt(i);
                    break;
                }
            }
        }

        public void SetCurrentInputActionMap(FECgInputActionMap actionMap)
        {
	        CurrentInputActionMap |= actionMap;
        }

        public void SetCurrentInputActionMap(int actionMap)
        {
            CurrentInputActionMap |= actionMap;
        }

        public void ClearCurrentInputActionMap(FECgInputActionMap actionMap)
        {
            CurrentInputActionMap &= actionMap;
        }

        public void ClearCurrentInputActionMap(int actionMap)
        {
            CurrentInputActionMap &= actionMap;
        }

        public FCgInput GetPreviousInputAction(FECgInputAction action)
        {
	        int lastInputFrame   = FCgMath.Mod(CurrentInputFrameIndex - 1, MAX_INPUT_FRAMES);
            FCgInput input       = InputFrames[lastInputFrame].GetInput(action);

	        return input;
        }

        public FCgInput GetPreviousInputAction(FECgInputAction action, ECgInputEvent e)
        {
            int lastInputFrame  = FCgMath.Mod(CurrentInputFrameIndex - 1, MAX_INPUT_FRAMES);
            FCgInput input       = InputFrames[lastInputFrame].GetInput(action, e);

            return input;
        }

        public FCgInput GetPreviousInputAction(FECgInputAction action, List<ECgInputEvent> events)
        {
            int lastInputFrame  = FCgMath.Mod(CurrentInputFrameIndex - 1, MAX_INPUT_FRAMES);
            FCgInput input       = InputFrames[lastInputFrame].GetInput(action, events);

            return input;
        }

        public FCgInput GetPreviousPreviousInputAction(FECgInputAction action)
        {
	        int lastInputFrame  = FCgMath.Mod(CurrentInputFrameIndex - 2, MAX_INPUT_FRAMES);
            FCgInput input       = InputFrames[lastInputFrame].GetInput(action);

	        return input;
        }

        public void QueueGameEvent(FECgGameEvent e)
        {
            QueuedGameEventsForNextFrame.Add(e);
        }

        public void ClearQueuedGameEvents()
        {
            QueuedGameEventsForNextFrame.Clear();
        }

        public void DetermineGameEvents(List<FCgInput> inputs)
        {
        }

        public bool HasActionEventOccured(FECgInputAction action, ECgInputEvent e)
        {
            FCgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgInput input = inputFrame.Inputs[i];

                if (input.Action == action && input.Event == e)
                    return true;
            }
            return false;
        }

        public float GetInputValue(FECgInputAction action)
        {
	        FCgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

	        int count = inputFrame.Inputs.Count;

	        for (int i = 0; i < count; ++i)
	        {
		        FCgInput input = inputFrame.Inputs[i];

		        if (input.Action == action)
			        return input.Value;
	        }
	        return 0.0f;
        }

        public Vector3 GetInputLocation(FECgInputAction action)
        {
            FCgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                    return input.Location;
            }
            return Vector3.zero;
        }

        public ECgInputEvent GetInputEvent(FECgInputAction action)
        {
            FCgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                    return input.Event;
            }
            return ECgInputEvent.MAX;
        }

        public float GetInputDuration(FECgInputAction action)
        {
            return Infos[(byte)action].Duration;
        }

        #region "Profile"

        public bool CanSaveInputActionMapping(ECgInputDevice device, FECgInputAction action)
        {
	        return true;
        }

        public string GetSavePath()
        {
            //return FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/");
            return "";
        }

        public string GetInputProfileFilenameAndPath()
        {
            //return GetSavePath() + TEXT("InputProfile") + FString::FromInt(ControllerId) + TEXT(".json");
            return "";
        }

        public void SaveInputProfile()
        {
            /*
            FString OutputString;
            TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory <>::Create(&OutputString);

            JsonWriter->WriteObjectStart();

            UCsCommon_Load::WriteStructToJson(JsonWriter, (void*)(&InputProfile), FCsInputProfile::StaticStruct(), nullptr);

            JsonWriter->WriteObjectEnd();

            JsonWriter->Close();

            const FString Filename = GetInputProfileFilenameAndPath();

            FFileHelper::SaveStringToFile(OutputString, *Filename);
            */
        }

        public void LoadDefaultInputProfile()
        {
            /*
            InputProfile.Reset();

            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            // ActionMappings
            int actionCount = PlayerInput->ActionMappings.Count;

            for (int i = 0; i < actionCount; ++i)
            {
                FInputActionKeyMapping & Mapping = PlayerInput->ActionMappings[i];

                ECgInputAction action = ECgInputAction.ToType(Mapping.ActionName);

                if (Action == InputAction_MAX)
                    continue;

                string actionName     = action.name;;
                KeyCode key           = Mapping.Key;
                const FString keyName = key.ToString();

                // MouseAndKeyboard
                if (CanSaveInputActionMapping(ECgInputDevice.MouseAndKeyboard, action) &&
                    IsValidKey(ECgInputDevice.MouseAndKeyboard, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.MouseAndKeyboard, actionName, action, keyName, Key);
                }
                // Gamepad
                if (CanSaveInputActionMapping(ECgInputDevice.Gamepad, action) &&
                    IsValidKey(ECgInputDevice.Gamepad, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.Gamepad, actionName, action, keyName, key);
                }
            }
            // AxisMappings
            int axisCount = PlayerInput->AxisMappings.Count;

            for (int i = 0; i < axisCount; ++i)
            {
                FInputAxisKeyMapping & Mapping = PlayerInput->AxisMappings[i];

                ECgInputAction action = ECgInputAction.ToType(Mapping.AxisName);

                if (action == null)
                    continue;

                string actionName   = ECgInputAction.ToStr(Action);
                KeyCode key         = Mapping.Key;
                string keyName      = key.ToString();

                // MouseAndKeyboard
                if (CanSaveInputActionMapping(ECgInputDevice.MouseAndKeyboard, action) &&
                    IsValidKey(ECgInputDevice.MouseAndKeyboard, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.MouseAndKeyboard, actionName, action, keyName, key);
                }
                // Gamepad
                if (CanSaveInputActionMapping(ECgInputDevice.Gamepad, action) &&
                    IsValidKey(ECgInputDevice.Gamepad, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.Gamepad, actionName, action, keyName, key);
                }
            }
            */
        }

        public void LoadInputProfile()
        {
            /*
            string inputProfileFilename = GetInputProfileFilenameAndPath();

            string dataJson;

            if (FFileHelper::LoadFileToString(DataJson, *InputProfileFilename))
            {
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory < TCHAR >::Create(DataJson);

                TSharedPtr<FJsonObject> JsonParsed;

                if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
                {
                    UCsCommon_Load::ReadStructFromJson(JsonParsed, &InputProfile, FCsInputProfile::StaticStruct(), nullptr);
                    // Update Action and Key members

                    for (int32 I = 0; I < ECS_INPUT_DEVICE_MAX; ++I)
                    {
                        FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[I];
                        TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

                        const int32 Count = Mappings.Num();

                        for (int32 J = 0; J < Count; J++)
                        {
                            FCsInputActionMapping & Mapping = Mappings[J];

                            Mapping.Action = (*StringToInputAction)(Mapping.ActionName);
                            Mapping.Key = GetKey(Mapping.KeyName);
                        }
                    }
                }
                else
                {
                    UE_LOG(LogCs, Warning, TEXT("ACsManager_Input::LoadInputProfile: %s is NOT Valid"), *InputProfileFilename);
                }
            }
            else
            {
                UE_LOG(LogCs, Warning, TEXT("ACsManager_Input::LoadInputProfile: %s NOT found. Loading Default Input Profile."), *InputProfileFilename);

                LoadDefaultInputProfile();
            }
            */
        }

        public bool IsValidKey(ECgInputDevice device, KeyCode key)
        {
	        if (key == KeyCode.None)
		        return false;

	        // MouseAndKeyboard
	        if (device == ECgInputDevice.MouseAndKeyboard)
	        {
		        if (FCgKey.IsGamepadKey(key))
			        return false;
	        }
	        // Gamepad
	        if (device == ECgInputDevice.Gamepad)
	        {
		        if (!FCgKey.IsGamepadKey(key))
			        return false;
	        }
	        return true;
        }

        public KeyCode GetKey(string keyName)
        {
            if (keyName == "")
                return KeyCode.None;

            return (KeyCode)Enum.Parse(typeof(KeyCode), keyName);
        }

        public FECgInputAction GetActionFromKey(ECgInputDevice device, KeyCode key)
        {
            /*
            FCsInputActionMappings & DeviceMapping   = InputProfile.DeviceMappings[(uint8)Device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            count = Mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (Mapping.Key == key)
                    return Mapping.Action;
            }
            */
            return null;
        }

        public KeyCode GetKeyFromAction(ECgInputDevice device, FECgInputAction action)
        {
            /*
            FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[(uint8)Device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            const count = Mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (Mapping.Action == action)
                    return Mapping.Key;
            }
            */
            return KeyCode.None;
        }

        public KeyCode GetKeyFromAction(FECgInputAction action)
        {
            /*
            UPlayerInput* PlayerInput = UCsCommon::GetLocalPlayerInput(GetWorld());

            string ActionName = ECgInputAction.ToStr(action);

            int actionCount = PlayerInput->ActionMappings.Count;

            for (int i = 0; i < actionCount; ++i)
            {
                FInputActionKeyMapping & Mapping = PlayerInput->ActionMappings[i];

                if (actionName == Mapping.ActionName)
                    return Mapping.Key;
            }

            int axisCount = PlayerInput->AxisMappings.Count;

            for (int i = 0; i < axisCount; ++i)
            {
                FInputAxisKeyMapping & Mapping = PlayerInput->AxisMappings[i];

                if (actionName == Mapping.AxisName)
                    return Mapping.Key;
            }
            */
            return KeyCode.None;
        }

        public void UnbindActionMapping(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput       = Controller->PlayerInput;

            string actionName = ECgInputAction.ToStr(action);
            // Remove binding from PlayerInput ActionMapping
            int mappingCount = PlayerInput->ActionMappings.Count;

            for (int i = mappingCount - 1; i >= 0; --i)
            {
                FInputActionKeyMapping & Mapping = PlayerInput->ActionMappings[I];

                if (actionName == Mapping.ActionName &&
                    key == Mapping.Key)
                {
                    PlayerInput->ActionMappings.RemoveAt(i);
                    break;
                }
            }
            // Clear Key on Mapping from InputProfile
            FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[(uint8)Device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            int count = Mappings.Count;

            for (i = count - 1; i >= 0; --i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (actionName == Mapping.ActionName &&
                    Key == Mapping.Key)
                {
                    Mapping.KeyName = "";
                    Mapping.Key = KeyCode.None;
                    break;
                }
            }
            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void UnbindAxisMapping(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            string actionName = ECgInputAction.ToStr(action);
            // Remove binding from PlayerInput ActionMapping
            int mappingCount = PlayerInput->AxisMappings.Count;

            for (int i = mappingCount - 1; i >= 0; --i)
            {
                FInputAxisKeyMapping & Mapping = PlayerInput->AxisMappings[i];

                if (actionName == Mapping.AxisName &&
                    key == Mapping.Key)
                {
                    PlayerInput->AxisMappings.RemoveAt(i);
                    break;
                }
            }
            // Clear Key on Mapping from InputProfile
            FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[(byte)device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            int count = Mappings.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (actionName == Mapping.ActionName &&
                    key == Mapping.Key)
                {
                    Mapping.KeyName = "";
                    Mapping.Key = KeyCode.None;
                    break;
                }
            }
            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void UnbindMapping(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            if (Infos[(byte)action].Type == ECgInputType.Action)
                UnbindActionMapping(device, action, key);
            if (Infos[(byte)action].Type == ECgInputType.Axis)
                UnbindAxisMapping(device, action, key);
        }

        // TODO: Need to store the original Key "Keyboard" mappings for Input. Do similar for control setup

        public void RebindActionMapping(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            if (!IsValidKey(device, key))
                return;
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            FCsInputActionMapping & Mapping = InputProfile.GetMapping(device, action);
            KeyCode previousKey = Mapping.Key;

            // If it is the SAME Key, Do Nothing
            if (key == previousKey)
                return;

            // Check if another Action is already mapped to the Key
            ECgInputAction otherAction = GetActionFromKey(device, key);

            // Unbind ActionMapping for OtherAction bound to Key
            if (otherAction != ECgInputAction.GetMAX())
            {
                UnbindMapping(Device, OtherAction, Key);
            }

            string actionName = ECgInputAction.ToStr(action);
            int count         = PlayerInput->ActionMappings.Count;

            bool found = false;

            for (int i = 0; i < count; ++i)
            {
                FInputActionKeyMapping & ActionMapping = PlayerInput->ActionMappings[i];

                if (actionName == ActionMapping.ActionName &&
                    previousKey == ActionMapping.Key)
                {
                    ActionMapping.Key = key;
                    found = true;
                    break;
                }
            }
            // Add Mapping if it is NOT found
            if (!found)
            {
                PlayerInput->ActionMappings.AddDefaulted();

                FInputActionKeyMapping & ActionMapping = PlayerInput->ActionMappings[count];
                ActionMapping.ActionName = Mapping.ActionName;
                ActionMapping.Key = Mapping.Key;
            }

            InputProfile.SetKey(device, action, key);

            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void RebindAxisMapping(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            if (!IsValidKey(device, key))
                return;
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            FCsInputActionMapping & Mapping = InputProfile.GetMapping(device, action);
            KeyCode previousKey = Mapping.Key;

            // If it is the SAME Key, Do Nothing
            if (key == previousKey)
                return;

            // Check if another Action is already mapped to the Key
            ECgInputAction otherAction = GetActionFromKey(device, key);

            // Unbind ActionMapping for OtherAction bound to Key
            if (otherAction != ECgInputAction.GetMAX())
            {
                UnbindMapping(device, otherAction, key);
            }

            string actionName = ECgInputAction.ToStr(action);
            int count         = PlayerInput->AxisMappings.Count;

            bool found = false;

            for (int i = 0; i < count; ++i)
            {
                FInputAxisKeyMapping & AxisMapping = PlayerInput->AxisMappings[i];

                if (actionName == AxisMapping.AxisName &&
                    previousKey == AxisMapping.Key)
                {
                    AxisMapping.Key = key;
                    found = true;
                    break;
                }
            }
            // Add Mapping if it is NOT found
            if (!found)
            {
                PlayerInput->AxisMappings.AddDefaulted();

                FInputAxisKeyMapping & AxisMapping = PlayerInput->AxisMappings[dount];
                AxisMapping.AxisName = Mapping.ActionName;
                AxisMapping.Key = Mapping.Key;
                AxisMapping.Scale = Mapping.Scale;
            }
            InputProfile.SetKey(device, action, key);

            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void RebindMapping(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            if (Infos[(byte)action].Type == ECgInputType.Action)
                RebindActionMapping(device, action, key);
            if (Infos[(byte)action].Type == ECgInputType.Axis)
                RebindAxisMapping(device, action, key);
        }

        #endregion // Profile

        #region "Game Events"

        public void CreateGameEventDefinitionSimple(List<FCgGameEventDefinition> definitions, FECgGameEvent gameEvent, FECgInputAction action, ECgInputEvent e)
        {
            definitions.Add(new FCgGameEventDefinition());
            FCgGameEventDefinition def = definitions[definitions.Count - 1];
	        def.Event = gameEvent;
	        // Sentence
	        {
		        FCgInputSentence sentence = def.Sentence;
		        sentence.Phrases.Add(new FCgInputPhrase());
		        // Phrase
		        {
			        FCgInputPhrase phrase = sentence.Phrases[sentence.Phrases.Count - 1];
			        phrase.Words.Add(new FCgInputWord());
			        // Word
			        {
				        FCgInputWord word = phrase.Words[phrase.Words.Count - 1];
				        word.AddOrInput(action, e);
			        }
                }
	        }
        }

        #endregion // Game Events
    }
}
