program KSJDemo;

uses
  Forms,
  MainFrm in 'MainFrm.pas' {KSJDemoDelphi},
  KSJApiB in 'KSJApiB.pas',
  KSJCode in 'KSJCode.pas',
  KSJApiC in 'KSJApiC.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TKSJDemoDelphi, KSJDemoDelphi);
  Application.Run;
end.
