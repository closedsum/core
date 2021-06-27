/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsDelegate1 = require("Cs/Types/Delegate/Delegate.js")
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;

module.exports = class NJsDelegate
{
    static FSinglecastBase = class SinglecastBase
    {
        constructor(argCount /*int*/)
        {
            this.Delegate = null; // NJsDelegate.FDelegateBases 

            checkf(CommonLibrary.IsIntChecked("NJsDelegate.FSinglecastBase.ctor: ", argCount));
            checkf(argCount >= 0, "NJsDelegate.FSinglecastBase.ctor: argCount: " + argCount + " is NOT >= 0.");

            this.ArgCount = argCount;
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         * @returns {NJsDelegate.FDelegate}
         */
        // NJsDelegate.FDelegate CreateDelegate(object: params)

        /**
         * @param {function}    fn 
         * @param {object}      caller
         */
        Bind(fn /*function*/, caller /*object*/)
        {
            let context = this.Add.name;

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));
            check(IsValidObjectChecked(context, caller));

            checkf(this.Delegate.Fn !== fn && this.Delegate.Caller !== caller, context + ": fn and caller have ALREADY been bound.");

            let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: -1};

            this.Delegate.Set(params);
        }

        /**
         * @param {function} fn
         */
        BindStatic(fn /*function*/)
        {
            let context = this.AddStatic.name;

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

             checkf(this.Delegate.Fn !== fn, context + ": fn has ALREADY been added.");

            let params = {Fn: fn, Caller: caller, bStatic: true, TerminationCount: -1};

            this.Delegate.Set(params);
        }

        Unbind()
        {
           this.Delegate.Reset();
        }

        /*bool*/ IsBound() { return this.Delegate.IsSet(); }
    }

    static FSinglecast = class Singlecast extends NJsDelegate.FSinglecastBase
    {
        constructor()
        {
            super(0);

            this.Delegate = new FJsDelegate1.FDelegate();
        }

        /**
         * @returns {any}
         */
        /*any*/ Execute()
        {
            let context = this.Execute.name;

            checkf(this.Delegate.IsSet(), context + ": delegate is NOT bound.");
            return this.Delegate.Execute();
        }

        /**
         * @returns {any} 
         */
        /*any*/ ExecuteIfBound()
        {
            if (this.Delegate.IsSet())
                return this.Delegate.Execute();
            return undefined;
        }
    }

    static FSinglecast_OneParam = class Singlecast_OneParam extends NJsDelegate.FSinglecastBase
    {
        constructor()
        {
            super(1);

            this.Delegate = new FJsDelegate1.FDelegate_OneParam();
        }

        /**
         * @param {any} param1
         * @returns {any} 
         */
        /*any*/ Execute(param1 /*any*/)
        {
            let context = this.Execute.name;

            checkf(this.Delegate.IsSet(), context + ": delegate is NOT bound.");
            return this.Delegate.Execute(param1);
        }

        /**
         * @param {any} param1
         * @returns {any} 
         */
        /*any*/ ExecuteIfBound(param1 /*any*/)
        {
            if (this.Delegate.IsSet())
                return this.Delegate.Execute();
            return undefined;
        }
    }
};