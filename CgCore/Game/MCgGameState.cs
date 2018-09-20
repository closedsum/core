namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

        #region "GameStateOnBoard"

    public sealed class FECgGameStateOnBoard : FECgEnum_byte
    {
        public FECgGameStateOnBoard(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgGameStateOnBoardEqualityComparer : IEqualityComparer<FECgGameStateOnBoard>
    {
        public bool Equals(FECgGameStateOnBoard lhs, FECgGameStateOnBoard rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameStateOnBoard x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgGameStateOnBoard : TCgEnumMap<FECgGameStateOnBoard, byte>
    {
        private static EMCgGameStateOnBoard _Instance;
        public static EMCgGameStateOnBoard Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameStateOnBoard();
                }
                return _Instance;
            }
        }

        public static EMCgGameStateOnBoard Get()
        {
            return Instance;
        }
    }

        #endregion // GameStateOnBoard

        #region "GameState"

    public sealed class FECgGameState : FECgEnum_byte
    {
        public FECgGameState(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgGameStateEqualityComparer : IEqualityComparer<FECgGameState>
    {
        public bool Equals(FECgGameState lhs, FECgGameState rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameState x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgGameState : TCgEnumMap<FECgGameState, byte>
    {
        private static EMCgGameState _Instance;
        public static EMCgGameState Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameState();
                }
                return _Instance;
            }
        }

        public static EMCgGameState Get()
        {
            return Instance;
        }
    }

        #endregion // GameState

        #region "GameStateRoutine"

    public sealed class FECgGameStateRoutine : FECgEnum_byte
    {
        public FECgGameStateRoutine(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgGameStateRoutineEqualityComparer : IEqualityComparer<FECgGameStateRoutine>
    {
        public bool Equals(FECgGameStateRoutine lhs, FECgGameStateRoutine rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameStateRoutine x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgGameStateRoutine : TCgEnumMap<FECgGameStateRoutine, byte>
    {
        private static EMCgGameStateRoutine _Instance;
        public static EMCgGameStateRoutine Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameStateRoutine();
                }
                return _Instance;
            }
        }

        public static EMCgGameStateRoutine Get()
        {
            return Instance;
        }
    }

        #endregion // GameStateRoutine

    #endregion // Enums

    public class MCgGameState : MonoBehaviour
    {
        #region "Constants"

        public static readonly int AUTO_ASSIGN_CONTROLLER = -1;
        public static readonly int INDEX_NONE = -1;

        #endregion // Constants

        #region "Data Members"

        private static MCgGameState _Instance;

        public FECgGameStateOnBoard OnBoardState;
        public FECgGameState CurrentState;

        [FCgReadOnly]
        public List<MCgPlayerController> PlayerControllers;

        // TODO: Look at having a Scene Manager
            #region "World"

        public List<MCgPawn> Pawns;
        public List<MCgPawn> PlayerPawns;

        //public 
            #endregion // World

        #endregion // Data Members

        public static MCgGameState Get()
        {
            return _Instance;
        }

        public static T Get<T>() 
            where T : MCgGameState
        {
            return (T)_Instance;
        }

        public virtual void Init()
        {
            if (_Instance != null)
                return;

            _Instance = this;

            PlayerControllers = new List<MCgPlayerController>();

            Pawns = new List<MCgPawn>();
            PlayerPawns = new List<MCgPawn>();
        }

        #region "OnBeginPlay"

        public virtual void OnBeginPlay()
        {
            OnBeginPlay_Handle_Pawns();
        }

        private void OnBeginPlay_Handle_Pawns()
        {
            MCgPawn[] pawns = FindObjectsOfType<MCgPawn>();

            foreach (MCgPawn p in pawns)
            {
                // Auto Possess
                if (p.bAutoPossess)
                {
                    bool possessed = false;

                    // Players

                    // Auto Assign Controller
                    if (p.ControllerIndex <= AUTO_ASSIGN_CONTROLLER)
                    {
                        foreach (MCgPlayerController pc in PlayerControllers)
                        {
                            if (pc.Pawn != null)
                            {
                                pc.Possess(p);

                                possessed = true;
                                break;
                            }
                        }

                        if (!possessed)
                        {
                            FCgDebug.LogWarning("MCgGameInstance.OnBeginPlay_Handle_Pawns: Failed to AutoPossess Pawn: " + p.name + " of type: " + p.GetType().ToString());
                        }
                    }
                    // Search for controller with matching index
                    else
                    {
                        if (p.ControllerIndex >= PlayerControllers.Count)
                        {
                            FCgDebug.LogWarning("MGgGameInstance.OnBeginPlay_Handle_Pawns: Failed to AutoPossess Pawn: " + p.name + " of type: " + p.GetType().ToString() + ". No PlayerController found with index: " + p.ControllerIndex);
                        }
                        else
                        {
                            int index = p.ControllerIndex;

                            if (PlayerControllers[index].Pawn != null)
                            {
                                FCgDebug.LogWarning("MGgGameInstance.OnBeginPlay_Handle_Pawns: Failed to AutoPossess Pawn: " + p.name + " of type: " + p.GetType().ToString());
                                FCgDebug.LogWarning("MGgGameInstance.OnBeginPlay_Handle_Pawns: PlayerController with index: " + index + " is already possessing Pawn: " + PlayerControllers[index].Pawn.name);
                            }
                            else
                            {
                                PlayerControllers[index].Possess(p);
                            }
                        }
                    }

                    // TODO: AI
                }

                p.bPlacedInWorld = true;

                p.Init();
            }
        }

        private void OnBeginPlay_Handle_Weapons()
        {
            MCgWeapon[] weapons = FindObjectsOfType<MCgWeapon>();

            foreach (MCgWeapon w in weapons)
            {
                w.bPlacedInWorld = true;
            }
        }

        #endregion // OnBeginPlay

        public virtual void OnUpdate(float deltaTime) { }

        #region "Routines"

        public virtual bool AddRoutine(FCgRoutine routine)
        {
            return false;
        }

        public virtual bool RemoveRoutine(FCgRoutine routine)
        {
            return false;
        }

        #endregion // Routines
    }
}
