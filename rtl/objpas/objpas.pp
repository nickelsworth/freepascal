{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by the Free Pascal development team

    This unit makes Free Pascal as much as possible Delphi compatible

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}
{$Mode ObjFpc}
{$I-}
{$ifndef Unix}
  {$S-}
{$endif}
unit objpas;

  interface

    { first, in object pascal, the integer type must be redefined }
    const
       MaxInt  = MaxLongint;
    type
       Integer  = longint;
       PInteger = ^Integer;

       { Ansistring are the default }
       PString = PAnsiString;

       { array types }
{$ifdef CPU16}
       IntegerArray  = array[0..$eff] of Integer;
{$else CPU16}
       IntegerArray  = array[0..$effffff] of Integer;
{$endif CPU16}
       TIntegerArray = IntegerArray;
       PIntegerArray = ^IntegerArray;
{$ifdef CPU16}
       PointerArray  = array [0..16*1024-2] of Pointer;
{$else CPU16}
       PointerArray  = array [0..512*1024*1024-2] of Pointer;
{$endif CPU16}
       TPointerArray = PointerArray;
       PPointerArray = ^PointerArray;
       TBoundArray = array of integer;

{$ifdef FPC_HAS_FEATURE_CLASSES}
Var
   ExceptionClass: TClass; { Exception base class (must actually be Exception, defined in sysutils ) }
{$endif FPC_HAS_FEATURE_CLASSES}

{****************************************************************************
                             Compatibility routines.
****************************************************************************}

{$ifdef FPC_HAS_FEATURE_FILEIO}
    { Untyped file support }

     Procedure AssignFile(out f:File;const Name:string);
     Procedure AssignFile(out f:File;p:pchar);
     Procedure AssignFile(out f:File;c:char);
     Procedure CloseFile(var f:File);
{$endif FPC_HAS_FEATURE_FILEIO}

{$ifdef FPC_HAS_FEATURE_TEXTIO}
     { Text file support }
     Procedure AssignFile(out t:Text;const s:string);
     Procedure AssignFile(out t:Text;p:pchar);
     Procedure AssignFile(out t:Text;c:char);
     Procedure CloseFile(Var t:Text);
{$endif FPC_HAS_FEATURE_TEXTIO}

{$ifdef FPC_HAS_FEATURE_FILEIO}
     { Typed file supoort }

     Procedure AssignFile(out f:TypedFile;const Name:string);
     Procedure AssignFile(out f:TypedFile;p:pchar);
     Procedure AssignFile(out f:TypedFile;c:char);
{$endif FPC_HAS_FEATURE_FILEIO}

{$ifdef FPC_HAS_FEATURE_COMMANDARGS}
     { ParamStr should return also an ansistring }
     Function ParamStr(Param : Integer) : Ansistring;
{$endif FPC_HAS_FEATURE_COMMANDARGS}

{$if defined(FPC_HAS_FEATURE_FILEIO) and defined(FPC_HAS_FEATURE_ANSISTRINGS)}
     Procedure MkDir(s:ansistring);overload;
     Procedure RmDir(s:ansistring);overload;
     Procedure ChDir(s:ansistring);overload;
{$endif defined(FPC_HAS_FEATURE_FILEIO) and defined(FPC_HAS_FEATURE_ANSISTRINGS)}

{****************************************************************************
                             Resource strings.
****************************************************************************}

{$ifdef FPC_HAS_FEATURE_RESOURCES}
   type
     TResourceIterator = Function (Name,Value : AnsiString; Hash : Longint; arg:pointer) : AnsiString;

   Function Hash(S : AnsiString) : LongWord;
   Procedure ResetResourceTables;
   Procedure FinalizeResourceTables;
   Procedure SetResourceStrings (SetFunction :  TResourceIterator;arg:pointer);
   Procedure SetUnitResourceStrings (const UnitName:string;SetFunction :  TResourceIterator;arg:pointer);
{$ifndef RESSTRSECTIONS}
   Function ResourceStringTableCount : Longint;
   Function ResourceStringCount(TableIndex : longint) : longint;
   Function GetResourceStringName(TableIndex,StringIndex : Longint) : Ansistring;
   Function GetResourceStringHash(TableIndex,StringIndex : Longint) : Longint;
   Function GetResourceStringDefaultValue(TableIndex,StringIndex : Longint) : AnsiString;
   Function GetResourceStringCurrentValue(TableIndex,StringIndex : Longint) : AnsiString;
   Function SetResourceStringValue(TableIndex,StringIndex : longint; Value : Ansistring) : Boolean;
{$endif RESSTRSECTIONS}

   { Delphi compatibility }
   type
     PResStringRec=^AnsiString;
     TResStringRec=AnsiString;
   Function LoadResString(p:PResStringRec):AnsiString;
{$endif FPC_HAS_FEATURE_RESOURCES}

  implementation

{****************************************************************************
                             Compatibility routines.
****************************************************************************}

{$ifdef FPC_HAS_FEATURE_FILEIO}
Procedure MkDirpchar(s: pchar;len:sizeuint);[IOCheck]; external name 'FPC_SYS_MKDIR';
Procedure ChDirpchar(s: pchar;len:sizeuint);[IOCheck]; external name 'FPC_SYS_CHDIR';
Procedure RmDirpchar(s: pchar;len:sizeuint);[IOCheck]; external name 'FPC_SYS_RMDIR';

{ Untyped file support }

Procedure AssignFile(out f:File;const Name:string);

begin
  System.Assign (F,Name);
end;

Procedure AssignFile(out f:File;p:pchar);

begin
  System.Assign (F,P);
end;

Procedure AssignFile(out f:File;c:char);

begin
  System.Assign (F,C);
end;

Procedure CloseFile(Var f:File); [IOCheck];

begin
  { Catch Runtime error/Exception }
  System.Close(f);
end;
{$endif FPC_HAS_FEATURE_FILEIO}

{$ifdef FPC_HAS_FEATURE_TEXTIO}
{ Text file support }

Procedure AssignFile(out t:Text;const s:string);

begin
  System.Assign (T,S);
end;

Procedure AssignFile(out t:Text;p:pchar);

begin
  System.Assign (T,P);
end;

Procedure AssignFile(out t:Text;c:char);

begin
  System.Assign (T,C);
end;

Procedure CloseFile(Var t:Text); [IOCheck];

begin
  { Catch Runtime error/Exception }
  System.Close(T);
end;
{$endif FPC_HAS_FEATURE_TEXTIO}

{$ifdef FPC_HAS_FEATURE_FILEIO}
{ Typed file support }

Procedure AssignFile(out f:TypedFile;const Name:string);

begin
  system.Assign(F,Name);
end;

Procedure AssignFile(out f:TypedFile;p:pchar);

begin
  system.Assign (F,p);
end;

Procedure AssignFile(out f:TypedFile;c:char);

begin
  system.Assign (F,C);
end;
{$endif FPC_HAS_FEATURE_FILEIO}

{$ifdef FPC_HAS_FEATURE_COMMANDARGS}
Function ParamStr(Param : Integer) : Ansistring;

Var Len : longint;

begin
{
  Paramstr(0) should return the name of the binary.
  Since this functionality is included in the system unit,
  we fetch it from there.
  Normally, pathnames are less than 255 chars anyway,
  so this will work correct in 99% of all cases.
  In time, the system unit should get a GetExeName call.
}
  if (Param=0) then
    Result:=System.Paramstr(0)
  else if (Param>0) and (Param<argc) then
    begin
    Len:=0;
    While Argv[Param][Len]<>#0 do
      Inc(len);
    SetLength(Result,Len);
    If Len>0 then
      Move(Argv[Param][0],Result[1],Len);
    end
  else
    paramstr:='';
end;
{$endif FPC_HAS_FEATURE_COMMANDARGS}


{$if defined(FPC_HAS_FEATURE_FILEIO) and defined(FPC_HAS_FEATURE_ANSISTRINGS)}
{ xxDirPChar procedures can adjust directory separators in supplied string (at least
  Windows implementation does so). Therefore full copy of argument is needed,
  just passing by value isn't enough because it won't copy a string literal. }
Procedure MkDir(s:ansistring);[IOCheck];
begin
  UniqueString(s);
  mkdirpchar(pchar(s),length(s));
end;

Procedure RmDir(s:ansistring);[IOCheck];
begin
  UniqueString(s);
  RmDirpchar(pchar(s),length(s));
end;

Procedure ChDir(s:ansistring);[IOCheck];
begin
  UniqueString(s);
  ChDirpchar(pchar(s),length(s));
end;
{$endif defined(FPC_HAS_FEATURE_FILEIO) and defined(FPC_HAS_FEATURE_ANSISTRINGS)}

{$ifdef FPC_HAS_FEATURE_RESOURCES}
{ ---------------------------------------------------------------------
    ResourceString support
  ---------------------------------------------------------------------}
Function Hash(S : AnsiString) : LongWord;
Var
  thehash,g,I : LongWord;
begin
   thehash:=0;
   For I:=1 to Length(S) do { 0 terminated }
     begin
     thehash:=thehash shl 4;
     inc(theHash,Ord(S[i]));
     g:=thehash and LongWord($f shl 28);
     if g<>0 then
       begin
       thehash:=thehash xor (g shr 24);
       thehash:=thehash xor g;
       end;
     end;
   If theHash=0 then
     Hash:=$ffffffff
   else
     Hash:=TheHash;
end;

{$ifdef RESSTRSECTIONS}
Type
  PResourceStringRecord = ^TResourceStringRecord;
  TResourceStringRecord = Packed Record
     Name,
     CurrentValue,
     DefaultValue : AnsiString;
     HashValue    : LongWord;
{$ifdef cpu64}
     Dummy        : LongWord; // alignment
{$endif cpu64}
   end;

   TResourceStringTableList = Packed Record
     Count : ptrint;
     Tables : Array[Word] of record
       TableStart,
       TableEnd   : PResourceStringRecord;
     end;
   end;

{ Support for string constants initialized with resourcestrings }
{$ifdef FPC_HAS_RESSTRINITS}
   PResStrInitEntry = ^TResStrInitEntry;
   TResStrInitEntry = record
     Addr: PPointer;
     Data: PResourceStringRecord;
   end;

   TResStrInitTable = packed record
     Count: longint;
     Tables: packed array[1..32767] of PResStrInitEntry;
   end;

var
  ResStrInitTable : TResStrInitTable; external name 'FPC_RESSTRINITTABLES';

procedure UpdateResourceStringRefs;
var
  i: Longint;
  ptable: PResStrInitEntry;
begin
  for i:=1 to ResStrInitTable.Count do
    begin
      ptable:=ResStrInitTable.Tables[i];
      while Assigned(ptable^.Addr) do
        begin
          AnsiString(ptable^.Addr^):=ptable^.Data^.CurrentValue;
          Inc(ptable);
        end;
    end;
end;
{$endif FPC_HAS_RESSTRINITS}

Var
  ResourceStringTable : TResourceStringTableList; External Name 'FPC_RESOURCESTRINGTABLES';

Procedure SetResourceStrings (SetFunction :  TResourceIterator;arg:pointer);
Var
  ResStr : PResourceStringRecord;
  i      : Longint;
  s      : AnsiString;
begin
  With ResourceStringTable do
    begin
      For i:=0 to Count-1 do
        begin
          ResStr:=Tables[I].TableStart;
          { Skip first entry (name of the Unit) }
          inc(ResStr);
          while ResStr<Tables[I].TableEnd do
            begin
              s:=SetFunction(ResStr^.Name,ResStr^.DefaultValue,Longint(ResStr^.HashValue),arg);
              if s<>'' then
                ResStr^.CurrentValue:=s;
              inc(ResStr);
            end;
        end;
    end;
{$ifdef FPC_HAS_RESSTRINITS}
  UpdateResourceStringRefs;
{$endif FPC_HAS_RESSTRINITS}
end;


Procedure SetUnitResourceStrings (const UnitName:string;SetFunction :  TResourceIterator;arg:pointer);
Var
  ResStr : PResourceStringRecord;
  i      : Longint;
  s,
  UpUnitName : AnsiString;
begin
  With ResourceStringTable do
    begin
      UpUnitName:=UpCase(UnitName);
      For i:=0 to Count-1 do
        begin
          ResStr:=Tables[I].TableStart;
          { Check name of the Unit }
          if ResStr^.Name<>UpUnitName then
            continue;
          inc(ResStr);
          while ResStr<Tables[I].TableEnd do
            begin
              s:=SetFunction(ResStr^.Name,ResStr^.DefaultValue,Longint(ResStr^.HashValue),arg);
              if s<>'' then
                ResStr^.CurrentValue:=s;
              inc(ResStr);
            end;
        end;
    end;
{$ifdef FPC_HAS_RESSTRINITS}
  { Resourcestrings of one unit may be referenced from other units,
    so updating everything is the only option. }
  UpdateResourceStringRefs;
{$endif FPC_HAS_RESSTRINITS}
end;


Procedure ResetResourceTables;
Var
  ResStr : PResourceStringRecord;
  i      : Longint;
begin
  With ResourceStringTable do
    begin
      For i:=0 to Count-1 do
        begin
          ResStr:=Tables[I].TableStart;
          { Skip first entry (name of the Unit) }
          inc(ResStr);
          while ResStr<Tables[I].TableEnd do
            begin
              ResStr^.CurrentValue:=ResStr^.DefaultValue;
              inc(ResStr);
            end;
        end;
    end;
end;


Procedure FinalizeResourceTables;
Var
  ResStr : PResourceStringRecord;
  i      : Longint;
begin
  With ResourceStringTable do
    begin
      For i:=0 to Count-1 do
        begin
          ResStr:=Tables[I].TableStart;
          { Skip first entry (name of the Unit) }
          inc(ResStr);
          while ResStr<Tables[I].TableEnd do
            begin
              ResStr^.CurrentValue:='';
              inc(ResStr);
            end;
        end;
    end;
end;

{$else RESSTRSECTIONS}

Type
  PResourceStringRecord = ^TResourceStringRecord;
  TResourceStringRecord = Packed Record
     DefaultValue,
     CurrentValue : AnsiString;
     HashValue    : LongWord;
     Name         : AnsiString;
   end;

   TResourceStringTable = Packed Record
     Count : longint;
     Resrec : Array[Word] of TResourceStringRecord;
   end;
   PResourceStringTable = ^TResourceStringTable;

   TResourceTableList = Packed Record
     Count : longint;
     Tables : Array[Word] of PResourceStringTable;
     end;

Var
  ResourceStringTable : TResourceTablelist; External Name 'FPC_RESOURCESTRINGTABLES';

Function GetResourceString(Const TheTable: TResourceStringTable;Index : longint) : AnsiString;[Public,Alias : 'FPC_GETRESOURCESTRING'];
begin
  If (Index>=0) and (Index<TheTAble.Count) then
     Result:=TheTable.ResRec[Index].CurrentValue
  else
     Result:='';
end;


Procedure SetResourceStrings (SetFunction :  TResourceIterator;arg:pointer);

Var I,J : longint;

begin
  With ResourceStringTable do
    For I:=0 to Count-1 do
      With Tables[I]^ do
         For J:=0 to Count-1 do
           With ResRec[J] do
             CurrentValue:=SetFunction(Name,DefaultValue,Longint(HashValue),arg);
end;


Procedure SetUnitResourceStrings (const UnitName:string;SetFunction :  TResourceIterator;arg:pointer);
begin
  SetResourceStrings (SetFunction,arg);
end;


Procedure ResetResourceTables;

Var I,J : longint;

begin
  With ResourceStringTable do
  For I:=0 to Count-1 do
    With Tables[I]^ do
        For J:=0 to Count-1 do
          With ResRec[J] do
            CurrentValue:=DefaultValue;
end;

Procedure FinalizeResourceTables;

Var I,J : longint;

begin
  With ResourceStringTable do
  For I:=0 to Count-1 do
    With Tables[I]^ do
        For J:=0 to Count-1 do
          With ResRec[J] do
            CurrentValue:='';
end;

Function ResourceStringTableCount : Longint;

begin
  Result:=ResourceStringTable.Count;
end;

Function CheckTableIndex (Index: longint) : Boolean;
begin
  Result:=(Index<ResourceStringTable.Count) and (Index>=0)
end;

Function CheckStringIndex (TableIndex,Index: longint) : Boolean;
begin
  Result:=(TableIndex<ResourceStringTable.Count) and (TableIndex>=0) and
          (Index<ResourceStringTable.Tables[TableIndex]^.Count) and (Index>=0)
end;

Function ResourceStringCount(TableIndex : longint) : longint;

begin
  If not CheckTableIndex(TableIndex) then
     Result:=-1
  else
    Result:=ResourceStringTable.Tables[TableIndex]^.Count;
end;

Function GetResourceStringName(TableIndex,StringIndex : Longint) : Ansistring;

begin
  If not CheckStringIndex(Tableindex,StringIndex) then
    Result:=''
  else
    result:=ResourceStringTable.Tables[TableIndex]^.ResRec[StringIndex].Name;
end;

Function GetResourceStringHash(TableIndex,StringIndex : Longint) : Longint;

begin
  If not CheckStringIndex(Tableindex,StringIndex) then
    Result:=0
  else
    result:=ResourceStringTable.Tables[TableIndex]^.ResRec[StringIndex].HashValue;
end;

Function GetResourceStringDefaultValue(TableIndex,StringIndex : Longint) : AnsiString;

begin
  If not CheckStringIndex(Tableindex,StringIndex) then
    Result:=''
  else
    result:=ResourceStringTable.Tables[TableIndex]^.ResRec[StringIndex].DefaultValue;
end;

Function GetResourceStringCurrentValue(TableIndex,StringIndex : Longint) : AnsiString;

begin
  If not CheckStringIndex(Tableindex,StringIndex) then
    Result:=''
  else
    result:=ResourceStringTable.Tables[TableIndex]^.ResRec[StringIndex].CurrentValue;
end;

Function SetResourceStringValue(TableIndex,StringIndex : longint; Value : Ansistring) : Boolean;

begin
  Result:=CheckStringIndex(Tableindex,StringIndex);
  If Result then
   ResourceStringTable.Tables[TableIndex]^.ResRec[StringIndex].CurrentValue:=Value;
end;

{$endif RESSTRSECTIONS}

Function LoadResString(p:PResStringRec):AnsiString;
begin
  Result:=p^;
end;
{$endif FPC_HAS_FEATURE_RESOURCES}


{$ifdef FPC_HAS_FEATURE_RESOURCES}
Initialization
{  ResetResourceTables;}
finalization
  FinalizeResourceTables;
{$endif FPC_HAS_FEATURE_RESOURCES}
end.
