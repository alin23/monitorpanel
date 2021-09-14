import Cocoa
import ColorSync
import Foundation

enum OSDImage: Int64 {
    case brightness = 1
    case contrast = 11
    case volume = 3
    case muted = 4
}

func displayInfoDictionary(_ id: CGDirectDisplayID) -> NSDictionary? {
    let unmanagedDict = CoreDisplay_DisplayCreateInfoDictionary(id)
    let retainedDict = unmanagedDict?.takeRetainedValue()
    guard let dict = retainedDict as NSDictionary? else {
        return nil
    }

    return dict
}

func name(for id: CGDirectDisplayID) -> String? {
    guard let dict = displayInfoDictionary(id),
          let name = (dict["DisplayProductName"] as? [String: String])?["en_US"]
    else {
        return nil
    }

    return name
}

func showOsd(osdImage: OSDImage, value: UInt32, displayID: CGDirectDisplayID, locked: Bool = false, respectMirroring: Bool = true) {
    guard let manager = OSDManager.sharedManager() as? OSDManager else {
        print("No OSDManager available")
        return
    }

    var osdID = displayID
    if respectMirroring {
        let mirroredID = CGDisplayMirrorsDisplay(displayID)
        osdID = mirroredID != kCGNullDirectDisplay ? mirroredID : displayID
    }

    manager.showImage(
        osdImage.rawValue,
        onDisplayID: osdID,
        priority: 0x1F4,
        msecUntilFade: 1500,
        filledChiclets: value,
        totalChiclets: 100,
        locked: locked
    )
}

let maxDisplays: UInt32 = 16
var onlineDisplays = [CGDirectDisplayID](repeating: 0, count: Int(maxDisplays))
var displayCount: UInt32 = 0

let err = CGGetOnlineDisplayList(maxDisplays, &onlineDisplays, &displayCount)
let displayIDs = onlineDisplays.prefix(Int(displayCount))

print("Online Display IDs: \(displayIDs)")

func getModeDetails(_ mode: MPDisplayMode?, prefix: String = "\t") -> String {
    guard let mode = mode else { return "nil" }
    var modeDesc = _CGSDisplayModeDescription()
    mode.getDescription(&modeDesc)
    return """
        \(prefix)refreshString: \(mode.refreshString ?? "Unknown")
        \(prefix)resolutionString: \(mode.resolutionString ?? "Unknown")
        \(prefix)isSafeMode: \(mode.isSafeMode)
        \(prefix)tvModeEquiv: \(mode.tvModeEquiv)
        \(prefix)tvMode: \(mode.tvMode)
        \(prefix)isTVMode: \(mode.isTVMode)
        \(prefix)isSimulscan: \(mode.isSimulscan)
        \(prefix)isInterlaced: \(mode.isInterlaced)
        \(prefix)isNativeMode: \(mode.isNativeMode)
        \(prefix)isDefaultMode: \(mode.isDefaultMode)
        \(prefix)isStretched: \(mode.isStretched)
        \(prefix)isUserVisible: \(mode.isUserVisible)
        \(prefix)isHiDPI: \(mode.isHiDPI)
        \(prefix)isRetina: \(mode.isRetina)
        \(prefix)scanRate: \(mode.scanRate ?? 0)
        \(prefix)roundedScanRate: \(mode.roundedScanRate)
        \(prefix)scale: \(mode.scale)
        \(prefix)aspectRatio: \(mode.aspectRatio)
        \(prefix)fixPtRefreshRate: \(mode.fixPtRefreshRate)
        \(prefix)refreshRate: \(mode.refreshRate)
        \(prefix)dotsPerInch: \(mode.dotsPerInch)
        \(prefix)vertDPI: \(mode.vertDPI)
        \(prefix)horizDPI: \(mode.horizDPI)
        \(prefix)pixelsHigh: \(mode.pixelsHigh)
        \(prefix)pixelsWide: \(mode.pixelsWide)
        \(prefix)height: \(mode.height)
        \(prefix)width: \(mode.width)
        \(prefix)modeNumber: \(mode.modeNumber)
        \(prefix)modeDescription:
            \(prefix)displayModeNumber: \(modeDesc.displayModeNumber)
            \(prefix)flags: \(modeDesc.flags)
            \(prefix)width: \(modeDesc.width)
            \(prefix)height: \(modeDesc.height)
            \(prefix)depth: \(modeDesc.depth)
            \(prefix)rowBytes: \(modeDesc.rowBytes)
            \(prefix)bitsPerPixel: \(modeDesc.bitsPerPixel)
            \(prefix)bitsPerSample: \(modeDesc.bitsPerSample)
            \(prefix)samplesPerPixel: \(modeDesc.samplesPerPixel)
            \(prefix)refreshRate: \(modeDesc.refreshRate)
            \(prefix)horizontalResolution: \(modeDesc.horizontalResolution)
            \(prefix)verticalResolution: \(modeDesc.verticalResolution)
            \(prefix)version: \(modeDesc.version)
            \(prefix)length: \(modeDesc.length)
            \(prefix)fixPtRefreshRate: \(modeDesc.fixPtRefreshRate)
            \(prefix)ioModeInfoFlags: \(modeDesc.ioModeInfoFlags)
            \(prefix)ioDisplayModeNumber: \(modeDesc.ioDisplayModeNumber)
            \(prefix)pixelsWide: \(modeDesc.pixelsWide)
            \(prefix)pixelsHigh: \(modeDesc.pixelsHigh)
            \(prefix)encoding: \(modeDesc.encoding)
            \(prefix)resolution: \(modeDesc.resolution)
    """
}

func getMonitorPanelData(_ display: MPDisplay) -> String {
    return """
        ID: \(display.displayID)
        Alias ID: \(display.aliasID)
        canChangeOrientation: \(display.canChangeOrientation())
        hasRotationSensor: \(display.hasRotationSensor)
        hasZeroRate: \(display.hasZeroRate)
        hasMultipleRates: \(display.hasMultipleRates)
        isSidecarDisplay: \(display.isSidecarDisplay)
        isAirPlayDisplay: \(display.isAirPlayDisplay)
        isProjector: \(display.isProjector)
        is4K: \(display.is4K)
        isTV: \(display.isTV)
        isMirrorMaster: \(display.isMirrorMaster)
        isMirrored: \(display.isMirrored)
        isBuiltIn: \(display.isBuiltIn)
        isHiDPI: \(display.isHiDPI)
        hasTVModes: \(display.hasTVModes)
        hasSimulscan: \(display.hasSimulscan)
        hasSafeMode: \(display.hasSafeMode)
        isSmartDisplay: \(display.isSmartDisplay)
        orientation: \(display.orientation)

        Default mode:
        \(getModeDetails(display.defaultMode, prefix: "\t"))

        Native mode:
        \(getModeDetails(display.nativeMode, prefix: "\t"))

        Current mode:
        \(getModeDetails(display.currentMode, prefix: "\t"))

        All modes:
        \((display.allModes() as? [MPDisplayMode])?.map { "\t\($0.description.replacingOccurrences(of: "\n", with: ", ")):\n\(getModeDetails($0, prefix: "\t\t"))" }.joined(separator: "\n\n") ?? "nil")
    """
}

func printData() {
    for id in displayIDs {
        let displayName = name(for: id) ?? "unknown"
        print("Display \(displayName) [id: \(id)]")
    }
    guard let mgr = MPDisplayMgr(), let displays = mgr.displays as? [MPDisplay] else { return }
    for panel in displays {
        print(panel.displayName ?? "Unknown name")

        print(getMonitorPanelData(panel))
    }
}

func testRotation(_ id: CGDirectDisplayID) {
    guard let mgr = MPDisplayMgr(), let displays = mgr.displays as? [MPDisplay],
          let panel = displays.first(where: { $0.displayID == id })
    else {
        print("No panel for ID '\(id)'")
        return
    }
    guard panel.canChangeOrientation() else {
        print("Display '\(panel.displayName ?? "Unknown")' can't change orientation")
        return
    }

    print("Rotating '\(panel.displayName ?? "Unknown")' 90 degrees")
    panel.orientation = 90

    print("Waiting 5 seconds...")
    sleep(5)

    print("Rotating '\(panel.displayName ?? "Unknown")' 180 degrees")
    panel.orientation = 180

    print("Waiting 5 seconds...")
    sleep(5)

    print("Rotating '\(panel.displayName ?? "Unknown")' 270 degrees")
    panel.orientation = 270

    print("Waiting 5 seconds...")
    sleep(5)

    print("Rotating '\(panel.displayName ?? "Unknown")' back to 0 degrees")
    panel.orientation = 0
}

func printGamma(_ id: CGDirectDisplayID) {
    var redMin: CGGammaValue = 0.0
    var redMax: CGGammaValue = 1.0
    var redGamma: CGGammaValue = 1.0
    var greenMin: CGGammaValue = 0.0
    var greenMax: CGGammaValue = 1.0
    var greenGamma: CGGammaValue = 1.0
    var blueMin: CGGammaValue = 0.0
    var blueMax: CGGammaValue = 1.0
    var blueGamma: CGGammaValue = 1.0

    var redTable = [CGGammaValue](repeating: 0, count: 255)
    var greenTable = [CGGammaValue](repeating: 0, count: 255)
    var blueTable = [CGGammaValue](repeating: 0, count: 255)
    var sampleCount: UInt32 = 0

    let displayName = name(for: id) ?? "unknown"
    print("Display \(displayName) [id: \(id)]")
    CGGetDisplayTransferByFormula(id, &redMin, &redMax, &redGamma, &greenMin, &greenMax, &greenGamma, &blueMin, &blueMax, &blueGamma)
    print("""
        redMin: \(redMin)
        redMax: \(redMax)
        redGamma: \(redGamma)
        greenMin: \(greenMin)
        greenMax: \(greenMax)
        greenGamma: \(greenGamma)
        blueMin: \(blueMin)
        blueMax: \(blueMax)
        blueGamma: \(blueGamma)
    """)

    CGGetDisplayTransferByTable(id, 255, &redTable, &greenTable, &blueTable, &sampleCount)
    print("""
        Red Gamma Table: \(redTable)
        Green Gamma Table: \(greenTable)
        Blue Gamma Table: \(blueTable)
    """)
}

func testGamma(_ id: CGDirectDisplayID) {
    var redTable = [CGGammaValue](repeating: 0, count: 255)
    var greenTable = [CGGammaValue](repeating: 0, count: 255)
    var blueTable = [CGGammaValue](repeating: 0, count: 255)
    var sampleCount: UInt32 = 0

    CGGetDisplayTransferByTable(id, 255, &redTable, &greenTable, &blueTable, &sampleCount)
    print("""
        Red Gamma Table: \(redTable)
        Green Gamma Table: \(greenTable)
        Blue Gamma Table: \(blueTable)
    """)
    for brightness in stride(from: 1.00, to: 0.40, by: -0.01) {
        CGSetDisplayTransferByTable(
            id,
            sampleCount,
            redTable.map { $0 * Float(brightness) },
            greenTable.map { $0 * Float(brightness) },
            blueTable.map { $0 * Float(brightness) }
        )
        Thread.sleep(forTimeInterval: 0.01)
    }
    sleep(200)
}


for id in displayIDs {
    printGamma(id)
//     // testGamma(id)
}

printData()

// if let idArg = CommandLine.arguments.prefix(2).last, let id = CGDirectDisplayID(idArg) {
//     testRotation(id)
// }
