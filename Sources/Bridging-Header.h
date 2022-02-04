#import <CommonCrypto/CommonDigest.h>
#import <CoreGraphics/CGColor.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <MonitorPanel/MPDisplay.h>
#import <MonitorPanel/MPDisplayMgr.h>
#import <MonitorPanel/MPDisplayMode.h>
#import <OSD/OSDManager.h>

double CoreDisplay_Display_GetUserBrightness(CGDirectDisplayID display);
double CoreDisplay_Display_GetLinearBrightness(CGDirectDisplayID display);
double CoreDisplay_Display_GetDynamicLinearBrightness(CGDirectDisplayID display);

void CoreDisplay_Display_SetUserBrightness(CGDirectDisplayID display, double brightness);
void CoreDisplay_Display_SetLinearBrightness(CGDirectDisplayID display, double brightness);
void CoreDisplay_Display_SetDynamicLinearBrightness(CGDirectDisplayID display, double brightness);

void CoreDisplay_Display_SetAutoBrightnessIsEnabled(CGDirectDisplayID, bool);

CFDictionaryRef CoreDisplay_DisplayCreateInfoDictionary(CGDirectDisplayID);

int DisplayServicesGetLinearBrightness(CGDirectDisplayID display, float* brightness);
int DisplayServicesSetLinearBrightness(CGDirectDisplayID display, float brightness);
int DisplayServicesGetBrightness(CGDirectDisplayID display, float* brightness);
int DisplayServicesSetBrightness(CGDirectDisplayID display, float brightness);
int DisplayServicesSetBrightnessSmooth(CGDirectDisplayID display, float brightness);
bool DisplayServicesCanChangeBrightness(CGDirectDisplayID display);
bool DisplayServicesHasAmbientLightCompensation(CGDirectDisplayID display);
bool DisplayServicesAmbientLightCompensationEnabled(CGDirectDisplayID display);
bool DisplayServicesIsSmartDisplay(CGDirectDisplayID display);
void DisplayServicesBrightnessChanged(CGDirectDisplayID display, double brightness);

int BCBrtControlGetMaxNits();

@class BCBrtControl;

@interface BCBrtControl : NSObject
- (id)init;
- (BOOL)isValid;
- (int)getNitsWithError;

@end

@interface CAWindowServer : NSObject {
    /* Warning: unhandled struct encoding: '{CAWindowServerImpl=^{__CFArray}I@}' */ struct CAWindowServerImpl {
        struct __CFArray {
        } * x1;
        unsigned int x2;
        id x3;
    } * _impl;
    bool _mirroringEnabled;
}

@property (readonly) NSArray* displays;
@property (getter=isMirroringEnabled) bool mirroringEnabled;
@property unsigned int rendererFlags;
@property (getter=isSecure) bool secure;

+ (id)context;
+ (id)contextWithOptions:(id)arg1;
+ (id)server;
+ (id)serverIfRunning;
+ (id)serverWithOptions:(id)arg1;

- (void)_detectDisplays;
- (id)_init;
- (void)_initializeBrightnessNotifications;
- (void)addDisplay:(id)arg1;
- (unsigned int)clientPortOfContextId:(unsigned int)arg1;
- (unsigned int)contextIdHostingContextId:(unsigned int)arg1;
- (void)dealloc;
- (id)description;
- (id)displayWithDisplayId:(unsigned int)arg1;
- (id)displayWithName:(id)arg1;
- (id)displayWithUniqueId:(id)arg1;
- (id)displays;
- (id)init;
- (id)insecureProcessIds;
- (bool)isMirroringEnabled;
- (bool)isSecure;
- (void)removeAllDisplays;
- (void)removeDisplay:(id)arg1;
- (unsigned int)rendererFlags;
- (id)secureModeViolations;
- (void)setMirroringEnabled:(bool)arg1;
- (void)setRendererFlags:(unsigned int)arg1;
- (void)setSecure:(bool)arg1;
- (unsigned int)taskNamePortOfContextId:(unsigned int)arg1;
- (unsigned int)taskPortOfContextId:(unsigned int)arg1;

@end

@protocol CAPresetTransaction <NSObject>

@property (assign, nonatomic) long long trinityCabalConfig;
@property (assign, nonatomic) BOOL preserveAppleSRGBGammaResponse;
@required
- (BOOL)preserveAppleSRGBGammaResponse;
- (void)setPreserveAppleSRGBGammaResponse:(BOOL)arg1;
- (long long)trinityCabalConfig;
- (BOOL)commitPreset;
- (void)setTrinityCabalConfig:(long long)arg1;
@end

@protocol CABrightnessControl <NSObject, NSObject>

@property (readonly) unsigned displayId;
@property (readonly) long long displayType;
@property (nonatomic, readonly) unsigned long long productId;
@property (nonatomic, readonly) unsigned long long vendorId;
@property (nonatomic, readonly) NSUUID* uuid;
@property (nonatomic, readonly) BOOL brightnessAvailable;
@property (nonatomic, readonly) BOOL whitePointAvailable;
@property (nonatomic, readonly) BOOL whitePointD50XYZ;
@property (nonatomic, readonly) NSDictionary* brightnessCapabilities;
@property (nonatomic, readonly) unsigned serviceObject;
@property (assign, nonatomic) double maximumHDRLuminance;
@property (assign, nonatomic) double maximumSDRLuminance;
@property (assign, nonatomic) double minimumLuminance;
@property (assign, nonatomic) double maximumReferenceLuminance;
@required
- (unsigned long long)vendorId;
- (void)setMinimumLuminance:(double)arg1;
- (unsigned)displayId;
- (void)setNotificationQueue:(id)arg1;
- (void)registerForNotifications:(id)arg1 withBlock:(/*^block*/ id)arg2;
- (unsigned long long)productId;
- (double)minimumLuminance;
- (double)maximumReferenceLuminance;
- (BOOL)brightnessAvailable;
- (unsigned)serviceObject;
- (void)unregisterNotificationBlocks;
- (NSDictionary*)brightnessCapabilities;
- (void)setMaximumReferenceLuminance:(double)arg1;
- (double)maximumHDRLuminance;
- (BOOL)whitePointAvailable;
- (double)maximumSDRLuminance;
- (NSUUID*)uuid;
- (BOOL)whitePointD50XYZ;
- (void)setMaximumHDRLuminance:(double)arg1;
- (void)setMaximumSDRLuminance:(double)arg1;
- (long long)displayType;
// -(BOOL)setWhitePoint:(SCD_Struct_CA3*)arg1 rampDuration:(double)arg2 error:(id*)arg3;
// -(BOOL)abortWhitePointRamp:(SCD_Struct_CA3*)arg1 error:(id*)arg2;
@end

@interface CAWindowServerDisplay : NSObject <CABrightnessControl, CAPresetTransaction> {

    // CAWindowServerDisplayImpl* _impl;
    BOOL _mirroringEnabled;
    unsigned long long _minimumFrameTime;
    unsigned long long _maximumFrameTime;
    unsigned long long _minimumVRRVBLDelta;
    unsigned long long _maximumVRRVBLDelta;
}
@property (readonly) CGRect bounds;
@property (readonly) CGSize nativeSize;
@property (assign) double scale;
@property (assign) CGSize scales;
@property (assign) BOOL scalePreservesAspect;
@property (readonly) double minimumScale;
@property (readonly) double maximumScale;
@property (readonly) CGSize panelPhysicalSize;
@property (readonly) unsigned long long panelPointsPerInch;
@property (readonly) NSString* name;
@property (readonly) NSString* deviceName;
@property (readonly) unsigned displayId;
@property (readonly) long long displayType;
@property (readonly) NSString* uniqueId;
@property (readonly) unsigned rendererFlags;
@property (readonly) NSSet* clones;
@property (readonly) CAWindowServerDisplay* cloneMaster;
@property (getter=isBlanked) BOOL blanked;
@property (getter=isFlipBookEnabled) BOOL flipBookEnabled;
@property (copy) NSString* orientation;
@property (copy) NSString* overscanAdjustment;
@property (assign) double overscanAmount;
@property (assign) CGSize overscanAmounts;
@property (assign) BOOL invertsColors;
@property (assign) BOOL allowsExtendedDynamicRange;
@property (getter=isGrayscale) BOOL grayscale;
@property (assign) float contrast;
@property (assign) float maximumBrightness;
@property (readonly) float maximumLuminance;
@property (assign) float nits;
@property (assign) float idealRefreshRate;
@property (assign) BOOL usesPreferredModeRefreshRate;
@property (nonatomic, copy) NSString* colorMode;
@property (assign) BOOL allowsVirtualModes;
@property (getter=isMirroringEnabled) BOOL mirroringEnabled; //@synthesize mirroringEnabled=_mirroringEnabled - In the implementation block
@property (readonly) BOOL supportsExtendedColors;
@property (assign) long long tag;
@property (assign) int processId;
@property (copy) NSString* TVMode;
@property (copy) NSString* TVSignalType;
@property (copy) id hotPlugCallback;
@property (copy) id brightnessCallback;
@property (copy) id updateRequestCallback;
@property (getter=isSecure) BOOL secure;
@property (assign) BOOL allowsDisplayCompositing;
@property (readonly) double nextWakeupTime;
@property (readonly) void* detachingDisplay;
@property (getter=isDetaching, readonly) BOOL detaching;
@property (readonly) CGRect detachingRect;
@property (readonly) unsigned long long vblDelta;
@property (readonly) unsigned long long previousVBL;
@property (readonly) unsigned long long minimumFrameTime; //@synthesize minimumFrameTime=_minimumFrameTime - In the implementation block
@property (readonly) unsigned long long maximumFrameTime; //@synthesize maximumFrameTime=_maximumFrameTime - In the implementation block
@property (readonly) unsigned long long minimumVRRVBLDelta; //@synthesize minimumVRRVBLDelta=_minimumVRRVBLDelta - In the implementation block
@property (readonly) unsigned long long maximumVRRVBLDelta; //@synthesize maximumVRRVBLDelta=_maximumVRRVBLDelta - In the implementation block
@property (assign) BOOL disablesUpdates;
@property (assign) BOOL disabled;
// @property (readonly) SCD_Struct_CA4 whitepoint;
// @property (readonly) SCD_Struct_CA5 chromaticities;
@property (readonly) float gamma;
@property (readonly) long long transportType;
@property (assign) BOOL enabled;
@property (readonly) unsigned framebufferFormat;
@property (readonly) BOOL needsUpdate;
@property (readonly) BOOL supportsCursor;
@property (readonly) CGSize maximumCursorSize;
@property (assign) CGPoint cursorPosition;
@property (copy) NSDictionary* cursorDictionary;
@property (assign) BOOL cursorHidden;
@property (assign) BOOL cursorEnabled;
@property (readonly) BOOL tripleBuffered;
// @property (retain) IOSurfaceRef cursorSurface;
@property (readonly) CGSize minimumVisibleCursorSize;
@property (readonly) BOOL wantedToDetach;
@property (readonly) unsigned long long minimumSourceRectSize;
@property (readonly) unsigned long long maximumSourceRectWidth;
@property (readonly) unsigned long long maximumSourceRectPixels;
@property (nonatomic, readonly) NSDictionary* brightnessCapabilities;
@property (readonly) BOOL supportsColorSpaces;
// @property (retain) CGColorSpaceRef blendColorSpace;
// @property (retain) CGColorSpaceRef displayColorSpace;
// @property (assign) CGColorTRC* systemGamma;
// @property (assign) CGColorTRC* blackpointAdaptation;
@property (assign) BOOL accessibilityFrameRateLimitEnabled;
@property (nonatomic, readonly) unsigned long long productId;
@property (nonatomic, readonly) unsigned long long vendorId;
@property (nonatomic, readonly) NSUUID* uuid;
@property (nonatomic, readonly) BOOL brightnessAvailable;
@property (nonatomic, readonly) BOOL whitePointAvailable;
@property (nonatomic, readonly) BOOL whitePointD50XYZ;
@property (nonatomic, readonly) unsigned serviceObject;
@property (assign, nonatomic) double maximumHDRLuminance;
@property (assign, nonatomic) double maximumSDRLuminance;
@property (assign, nonatomic) double minimumLuminance;
@property (assign, nonatomic) double maximumReferenceLuminance;
// @property (readonly) unsigned long long hash;
@property (readonly) Class superclass;
@property (copy, readonly) NSString* description;
@property (copy, readonly) NSString* debugDescription;
@property (assign, nonatomic) long long trinityCabalConfig;
@property (assign, nonatomic) BOOL preserveAppleSRGBGammaResponse;
- (float)nits;
- (NSSet*)clones;
- (unsigned long long)vendorId;
- (BOOL)isSecure;
- (void)setIdealRefreshRate:(float)arg1;
- (BOOL)usesPreferredModeRefreshRate;
- (void)postNotification:(id)arg1 payload:(id)arg2;
- (void)setMinimumLuminance:(double)arg1;
- (void)setDisabled:(BOOL)arg1;
- (unsigned)displayId;
- (long long)tag;
- (CGSize)scales;
- (BOOL)disabled;
- (void)freeze;
- (void)setOrientation:(NSString*)arg1;
// -(void)setBlackpointAdaptation:(CGColorTRC*)arg1 ;
- (float)contrast;
- (void)setScales:(CGSize)arg1;
- (void)powerStateDidChange:(id)arg1;
- (BOOL)accessibilityFrameRateLimitEnabled;
- (void)setNotificationQueue:(id)arg1;
- (CGColorSpaceRef)blendColorSpace;
- (void)setBrightnessLimit:(float)arg1;
- (void)setEnabled:(BOOL)arg1;
- (BOOL)needsUpdate;
- (BOOL)preserveAppleSRGBGammaResponse;
- (void)emitWhitePointError:(id*)arg1;
- (void)setGrayscale:(BOOL)arg1;
- (BOOL)allowsExtendedDynamicRange;
- (void)setScale:(double)arg1;
- (BOOL)enabled;
- (id)notificationQueue;
- (void)addClone:(id)arg1;
- (BOOL)canUpdateWithFlags:(unsigned)arg1;
- (void)setCursorEnabled:(BOOL)arg1;
- (void)setFilteredAmbient:(float)arg1;
- (CGPoint)cursorPosition;
- (void)setTag:(long long)arg1;
- (void)activateReplay;
- (void)setBrightnessCallback:(id)arg1;
- (void)registerForNotifications:(id)arg1 withBlock:(/*^block*/ id)arg2;
- (void)setOverscanAdjustment:(NSString*)arg1;
- (void)setProcessId:(int)arg1;
- (CGPoint)convertPoint:(CGPoint)arg1 toContextId:(unsigned)arg2;
- (void)setTVMode:(NSString*)arg1;
- (unsigned)framebufferFormat;
- (double)apertureOffset;
- (NSString*)uniqueId;
- (void)setAccessibilityFrameRateLimitEnabled:(BOOL)arg1;
- (void)setMinimumRefreshRate:(float)arg1;
- (BOOL)scalePreservesAspect;
- (void)setAllowsVirtualModes:(BOOL)arg1;
- (void)setCursorSurface:(IOSurfaceRef)arg1;
- (BOOL)isGrayscale;
- (CGRect)detachingRect;
- (CGPoint)convertPoint:(CGPoint)arg1 fromContextId:(unsigned)arg2;
- (unsigned long long)productId;
- (double)minimumScale;
- (void)setCursorDictionary:(NSDictionary*)arg1;
- (void*)detachingDisplay;
- (double)overscanAmount;
- (float)minimumRefreshRate;
- (void)setAccessibilityColorMatrix:(float*)arg1 scale:(float)arg2;
- (BOOL)cursorHidden;
- (void)setNits:(float)arg1;
- (BOOL)supportsCursor;
- (void)setOverscanAmounts:(CGSize)arg1;
- (double)minimumLuminance;
- (void)setInvertsColors:(BOOL)arg1;
- (unsigned long long)maximumSourceRectPixels;
- (void)addFramePresentationTimestamp:(unsigned long long)arg1;
- (void)setContrast:(float)arg1;
- (void)setPreserveAppleSRGBGammaResponse:(BOOL)arg1;
- (void)setHotPlugCallback:(id)arg1;
- (NSString*)TVMode;
// -(void)setGammaAdjustment:(CGColorTRC*)arg1 ;
- (void)setUserAdjustment:(float*)arg1 scale:(float)arg2;
- (void)copyDisplayTimingsFromDisplay:(id)arg1;
- (NSString*)description;
- (id)updateRequestCallback;
- (double)maximumReferenceLuminance;
- (BOOL)brightnessAvailable;
- (unsigned)serviceObject;
- (void)setMaximumRefreshRate:(float)arg1;
- (void)setUpdateRequestCallback:(id)arg1;
- (void)abortColorMatrixRamp:(float*)arg1 scale:(float*)arg2;
- (unsigned long long)panelPointsPerInch;
- (void)addClone:(id)arg1 options:(id)arg2;
- (void)setColorMode:(NSString*)arg1;
- (float)maximumRefreshRate;
- (void)unregisterNotificationBlocks;
- (CGSize)panelPhysicalSize;
- (double)scale;
- (float)idealRefreshRate;
- (CGColorSpaceRef)displayColorSpace;
- (void)setDisplayColorSpace:(CGColorSpaceRef)arg1;
- (NSDictionary*)brightnessCapabilities;
- (void)setHeadroom:(float)arg1;
- (void)renderForTime:(double)arg1;
- (NSString*)orientation;
- (CGRect)bounds;
- (BOOL)wantedToDetach;
- (NSString*)deviceName;
- (void)setMaximumReferenceLuminance:(double)arg1;
- (BOOL)allowsDisplayCompositing;
- (BOOL)finishExternalUpdate:(void*)arg1 withFlags:(unsigned)arg2 debugInfo:(unsigned long long)arg3;
- (double)maximumHDRLuminance;
- (BOOL)whitePointAvailable;
- (float)maximumBrightness;
- (BOOL)canUpdate:(BOOL)arg1;
- (void)setContrastEnhancer:(float)arg1 rampDuration:(double)arg2;
- (IOSurfaceRef)acquireFrozenSurface;
- (void)removeAllClones;
- (CGSize)overscanAmounts;
- (void)setAllowsDisplayCompositing:(BOOL)arg1;
- (float)maximumLuminance;
- (id)hitTestAtPosition:(CGPoint)arg1 options:(id)arg2;
- (long long)trinityCabalConfig;
- (void)presentSurface:(IOSurfaceRef)arg1 withOptions:(id)arg2;
- (void)setCalibrationPhase:(unsigned)arg1 forIdentifier:(unsigned)arg2;
- (double)maximumSDRLuminance;
- (void)setTVSignalType:(NSString*)arg1;
- (void)removeClone:(id)arg1;
- (NSDictionary*)cursorDictionary;
- (void)setDisablesUpdates:(BOOL)arg1;
- (NSString*)colorMode;
- (unsigned long long)previousVBL;
- (id)hotPlugCallback;
- (unsigned)clientPortOfContextId:(unsigned)arg1;
- (void)setSecure:(BOOL)arg1;
// -(CGColorTRC*)systemGamma;
- (void)setBlanked:(BOOL)arg1;
- (void)willUnblank;
- (CAWindowServerDisplay*)cloneMaster;
- (unsigned)contextIdAtPosition:(CGPoint)arg1 excludingContextIds:(id)arg2;
- (NSUUID*)uuid;
- (NSString*)overscanAdjustment;
- (double)maximumScale;
- (BOOL)tripleBuffered;
// -(SCD_Struct_CA4)whitepoint;
- (void)setMirroringEnabled:(BOOL)arg1;
- (BOOL)isBlanked;
- (void)invalidate;
- (void)setBlendColorSpace:(CGColorSpaceRef)arg1;
- (void)setFlipBookEnabled:(BOOL)arg1;
- (void)setCursorHidden:(BOOL)arg1;
- (unsigned long long)maximumSourceRectWidth;
// -(void)setSystemGamma:(CGColorTRC*)arg1 ;
- (BOOL)commitPreset;
- (NSString*)name;
- (void)setPotentialHeadroom:(float)arg1;
- (BOOL)whitePointD50XYZ;
- (void)setMaximumHDRLuminance:(double)arg1;
- (int)processId;
- (void)setMaximumSDRLuminance:(double)arg1;
- (IOSurfaceRef)cursorSurface;
- (void)emitBrightnessError:(id*)arg1;
- (unsigned)contextIdAtPosition:(CGPoint)arg1;
- (BOOL)allowsVirtualModes;
- (void)dealloc;
- (BOOL)disablesUpdates;
- (BOOL)supportsColorSpaces;
- (unsigned long long)maximumFrameTime;
- (CGSize)nativeSize;
// -(CATransform3D)transformFromLayerId:(unsigned long long)arg1 inContextId:(unsigned)arg2 ;
- (BOOL)isMirroringEnabled;
- (void)setScalePreservesAspect:(BOOL)arg1;
- (unsigned)taskNamePortOfContextId:(unsigned)arg1;
- (float)gamma;
- (CGSize)minimumVisibleCursorSize;
- (void)beginExternalUpdate:(void*)arg1 usingSoftwareRenderer:(BOOL)arg2;
- (unsigned)clientPortAtPosition:(CGPoint)arg1;
- (BOOL)finishExternalUpdate:(void*)arg1 withFlags:(unsigned)arg2;
- (BOOL)isFlipBookEnabled;
- (unsigned long long)minimumVRRVBLDelta;
- (BOOL)isDetaching;
// -(CGColorTRC*)blackpointAdaptation;
- (void)setCursorPosition:(CGPoint)arg1;
- (void)setApertureOffset:(double)arg1;
- (void)setSDRBrightness:(float)arg1;
- (void)setTrinityCabalConfig:(long long)arg1;
- (BOOL)supportsExtendedColors;
- (BOOL)setDigitalModes:(id)arg1 withTimings:(id)arg2;
- (void)abortContrastEnhancerRamp:(float*)arg1;
- (NSString*)TVSignalType;
- (unsigned)rendererFlags;
- (void)setMaximumBrightness:(float)arg1;
- (unsigned long long)minimumSourceRectSize;
- (id)brightnessCallback;
- (void)setAmbient:(float)arg1;
- (CGSize)maximumCursorSize;
- (void)setUsesPreferredModeRefreshRate:(BOOL)arg1;
- (unsigned long long)maximumVRRVBLDelta;
- (void)setColorMatrix:(float*)arg1 scale:(float)arg2 rampDuration:(double)arg3;
- (id)_initWithCADisplayServer:(void*)arg1;
- (long long)transportType;
- (BOOL)cursorEnabled;
- (BOOL)commitBrightness:(long)arg1;
- (unsigned long long)minimumFrameTime;
- (void)setOverscanAmount:(double)arg1;
- (long long)displayType;
- (void)setAllowsExtendedDynamicRange:(BOOL)arg1;
- (BOOL)invertsColors;
- (void)update;
// -(BOOL)setWhitePoint:(SCD_Struct_CA3*)arg1 rampDuration:(double)arg2 error:(id*)arg3 ;
// -(BOOL)abortWhitePointRamp:(SCD_Struct_CA3*)arg1 error:(id*)arg2 ;
- (double)nextWakeupTime;
- (unsigned long long)vblDelta;
// -(SCD_Struct_CA5)chromaticities;
@end