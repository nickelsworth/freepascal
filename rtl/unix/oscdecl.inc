{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2007 by the Free Pascal development team
    
    This file should become an alternative to the syscalls in due time,
    to import the base calls from libc.
    Be very careful though. Kernel types and libc types are often not the
    same on Linux.
    
    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
                                              
 ***********************************************************************}


{ ********************************************************************* }
{ fpioctl                                                               }
{ ********************************************************************* }

function  real_FpIOCtl   (Handle:cint;Ndx: TIOCtlRequest):cint; cdecl; varargs; external clib name 'ioctl';

function  FpIOCtl   (Handle:cint;Ndx: TIOCtlRequest;Data: Pointer):cint;
begin
  FpIOCtl:=real_FpIOCtl(Handle, Ndx, Data);
end;


{ ********************************************************************* }
{ fpfcntl                                                               }
{ ********************************************************************* }

function real_FpFcntl (fildes : cInt; cmd : cInt): cInt; cdecl; varargs; external clib name 'fcntl';

Function  FpFcntl      (fildes : cInt; cmd : cInt): cInt;
begin
  FpFcntl:=real_FpFcntl(fildes, cmd);
end;


Function  FpFcntl      (fildes : cInt; cmd : cInt; arg :cInt): cInt;
begin
  FpFcntl:=real_FpFcntl(fildes, cmd, arg);
end;


Function  FpFcntl      (fildes : cInt; cmd : cInt; var arg : flock): cInt;
begin
  FpFcntl:=real_FpFcntl(fildes, cmd, @arg);
end;

