{ Parsed from Appkit.framework NSRunningApplication.h }
{ Version: 2.1.2 - Wed Dec 8 10:06:07 CET 2010 }


{$ifdef TYPES}
{$ifndef NSRUNNINGAPPLICATION_PAS_T}
{$define NSRUNNINGAPPLICATION_PAS_T}

{ Constants }

const
  NSApplicationActivateAllWindows = 1 shl 0;
  NSApplicationActivateIgnoringOtherApps = 1 shl 1;

const
  NSApplicationActivationPolicyRegular = 0;
  NSApplicationActivationPolicyAccessory = 1;
  NSApplicationActivationPolicyProhibited = 2;

{ Types }
type
  NSApplicationActivationOptions = NSUInteger;
  NSApplicationActivationOptionsPtr = ^NSApplicationActivationOptions;
  NSApplicationActivationPolicy = NSInteger;
  NSApplicationActivationPolicyPtr = ^NSApplicationActivationPolicy;

{$endif}
{$endif}

{$ifdef RECORDS}
{$ifndef NSRUNNINGAPPLICATION_PAS_R}
{$define NSRUNNINGAPPLICATION_PAS_R}

{$endif}
{$endif}

{$ifdef FUNCTIONS}
{$ifndef NSRUNNINGAPPLICATION_PAS_F}
{$define NSRUNNINGAPPLICATION_PAS_F}

{$endif}
{$endif}

{$ifdef EXTERNAL_SYMBOLS}
{$ifndef NSRUNNINGAPPLICATION_PAS_S}
{$define NSRUNNINGAPPLICATION_PAS_S}

{$endif}
{$endif}

{$ifdef FORWARD}
  NSRunningApplication = objcclass;
  NSRunningApplicationPointer = ^NSRunningApplication;
  NSRunningApplicationPtr = NSRunningApplicationPointer;

{$endif}

{$ifdef CLASSES}
{$ifndef NSRUNNINGAPPLICATION_PAS_C}
{$define NSRUNNINGAPPLICATION_PAS_C}

{ NSRunningApplication }
  NSRunningApplication = objcclass(NSObject)
  private
    _superReserved: id;
    _asn: Pointer; {garbage collector: __strong }
    _helpers: PPointer; {garbage collector: __strong }
    _obsInfo: Pointer;
    _lock: NSLock;
    _bundleID: NSString;
    _localizedName: NSString;
    _bundleURL: NSURL;
    _executableURL: NSURL;
    _launchDate: NSDate;
    _icon: NSImage;
    _pid: cint;
    _lastSeed: cuint;
    _activeSeed: cuint;
    _staleSeed: cuint;
    _obsMask: culonglong;
    __aflags: bitpacked record
      case byte of
       0: (_anonbitfield_NSRunningApplication0: cuint);
       1: (
        fetchedDynamic: 0..1;
        deadToUs: 0..1;
        terminated: 0..1;
        finishedLaunching: 0..1;
        hidden: 0..1;
        active: 0..1;
        arch: 0..((1 shl 3)-1);
        activationPolicy: 0..((1 shl 3)-1);
        reserved1: 0..((1 shl 20)-1);
      );
      end;
    _appReserved: id;
    
  public
    class function alloc: NSRunningApplication; message 'alloc';

    function terminated: Boolean; message 'terminated';
    function finishedLaunching: Boolean; message 'finishedLaunching';
    function hidden: Boolean; message 'hidden';
    function active: Boolean; message 'active';
    function activationPolicy: NSApplicationActivationPolicy; message 'activationPolicy';
    function localizedName: NSString; message 'localizedName';
    function bundleIdentifier: NSString; message 'bundleIdentifier';
    function bundleURL: NSURL; message 'bundleURL';
    function executableURL: NSURL; message 'executableURL';
    function processIdentifier: pid_t; message 'processIdentifier';
    function launchDate: NSDate; message 'launchDate';
    function icon: NSImage; message 'icon';
    function executableArchitecture: NSInteger; message 'executableArchitecture';
    function hide: Boolean; message 'hide';
    function unhide: Boolean; message 'unhide';
    function activateWithOptions(options: NSApplicationActivationOptions): Boolean; message 'activateWithOptions:';
    function terminate: Boolean; message 'terminate';
    function forceTerminate: Boolean; message 'forceTerminate';
    class function runningApplicationsWithBundleIdentifier(bundleIdentifier_: NSString): NSArray; message 'runningApplicationsWithBundleIdentifier:';
    class function runningApplicationWithProcessIdentifier(pid: pid_t): NSRunningApplication; message 'runningApplicationWithProcessIdentifier:';
    class function currentApplication: NSRunningApplication; message 'currentApplication';
  end; external;

{ NSWorkspaceRunningApplicationsCategory }
  NSWorkspaceRunningApplicationsCategory = objccategory(NSWorkspace)
    function runningApplications: NSArray; message 'runningApplications';
  end; external;

{$endif}
{$endif}