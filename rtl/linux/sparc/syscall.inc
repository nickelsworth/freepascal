{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by Michael Van Canneyt,
    member of the Free Pascal development team.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{No debugging for syslinux include !}
{$IFDEF SYS_LINUX}
  {$UNDEF SYSCALL_DEBUG}
{$ENDIF SYS_LINUX}

{ This variable is needed in syscall.inc assembler code }
var
  fpc_threadvar_relocate_proc : TRelocateThreadVarHandler; public name 'FPC_THREADVAR_RELOCATE';
{$define THREADVAR_RELOCATED_ALREADY_DEFINED}


function get_got : pointer;assembler;{$ifndef FPC_PIC}nostackframe;{$endif} forward;

{$define FPC_SYSTEM_HAS_FPFORK}
{
  behaviour of result of fork on sparc/linux is different than on other
  linux flavours
}
function Fpfork : pid_t;  [public, alias : 'FPC_SYSC_FORK'];assembler;
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     2,%g1
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        ba      .LReturn
        mov     -1,%i0
.LSyscOK:
        // o1 contains 1 in the parent
        // and 0 in the child
        sub     %o1, 1, %o1
        and     %o0, %o1, %i0
.LReturn:
end;


{*****************************************************************************
                     --- Main:The System Call Self ---
*****************************************************************************}

function FpSysCall(sysnr:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL0'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


function FpSysCall(sysnr,param1:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL1'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        mov     %i1,%o0
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


function FpSysCall(sysnr,param1,param2:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL2'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        mov     %i1,%o0
        mov     %i2,%o1
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


function FpSysCall(sysnr,param1,param2,param3:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL3'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        mov     %i1,%o0
        mov     %i2,%o1
        mov     %i3,%o2
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


function FpSysCall(sysnr,param1,param2,param3,param4:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL4'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        mov     %i1,%o0
        mov     %i2,%o1
        mov     %i3,%o2
        mov     %i4,%o3
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


function FpSysCall(sysnr,param1,param2,param3,param4,param5:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL5'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        mov     %i1,%o0
        mov     %i2,%o1
        mov     %i3,%o2
        mov     %i4,%o3
        mov     %i5,%o4
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


function FpSysCall(sysnr,param1,param2,param3,param4,param5,param6:TSysParam):TSysResult; assembler;[public,alias:'FPC_SYSCALL6'];
{
  This function puts the registers in place, does the call, and then
  copies back the registers as they are after the SysCall.
}
asm
{$ifdef FPC_PIC}
  sethi %hi(_GLOBAL_OFFSET_TABLE_ -8),%l7
  or %l7,%lo(_GLOBAL_OFFSET_TABLE_ -4),%l7
  call get_got
  nop
{$endif FPC_PIC}
        mov     %i0,%g1
        mov     %i1,%o0
        mov     %i2,%o1
        mov     %i3,%o2
        mov     %i4,%o3
        ld      [%i6+92],%o5
        mov     %i5,%o4
        ta      0x10
        bcc     .LSyscOK
        nop
        mov     %o0,%l0
        sethi   %hi(fpc_threadvar_relocate_proc),%o2
        or      %o2,%lo(fpc_threadvar_relocate_proc),%o2
{$ifdef FPC_PIC}
        ld      [%o2+%l7],%o2
{$endif FPC_PIC}
        ld      [%o2],%o3
        cmp     %o3,0
        bne     .LThread
        nop
{$ifndef FPC_PIC}
        sethi   %hi(Errno+4),%o0
        ba      .LNoThread
        or      %o0,%lo(Errno+4),%o0
{$else FPC_PIC}
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
        ld      [%o0+%l7],%o0
        ba      .LNoThread
        add     %o0,4,%o0
{$endif FPC_PIC}
.LThread:
        sethi   %hi(Errno),%o0
        or      %o0,%lo(Errno),%o0
{$ifdef FPC_PIC}
        ld      [%o0+%l7],%o0
{$endif FPC_PIC}
        call    %o3
        ld      [%o0],%o0
.LNoThread:
        st      %l0,[%o0]
        mov     -1,%o0
.LSyscOK:
        mov     %o0,%i0
end;


