/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

declare class FJsProperty {
    Value: any;
    Get(): any;
    IsBoolean(): boolean;
    IsNumber(): boolean;
    IsInt(): boolean;
    IsFloat(): boolean;
    IsString(): boolean;
    IsObject(): boolean;
    IsNonNullObject(): boolean;
}