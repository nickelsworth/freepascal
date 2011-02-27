{$ifndef ALLPACKAGES}
{$mode objfpc}{$H+}
program fpmake;

uses fpmkunit;

Var
  P : TPackage;
  T : TTarget;
begin
  With Installer do
    begin
{$endif ALLPACKAGES}

    P:=AddPackage('libogcfpc');
{$ifdef ALLPACKAGES}
    P.Directory:='libogcfpc';
{$endif ALLPACKAGES}
    P.Version:='2.5.1';
    P.SourcePath.Add('src');
//    P.Dependencies.Add('x11');

    // not linux compilable, skip

{$ifndef ALLPACKAGES}
    Run;
    end;
end.
{$endif ALLPACKAGES}