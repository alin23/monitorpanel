import Cocoa
import ColorSync
import Foundation

let maxDisplays: UInt32 = 16
var onlineDisplays = [CGDirectDisplayID](repeating: 0, count: Int(maxDisplays))
var displayCount: UInt32 = 0

let err = CGGetOnlineDisplayList(maxDisplays, &onlineDisplays, &displayCount)
let displayIDs = onlineDisplays.prefix(Int(displayCount))

print("Online Display IDs: \(displayIDs)")

func printCADisplay(_ d: CAWindowServerDisplay) {
    print("name", d.name ?? "")
    print("    deviceName", d.deviceName ?? "")
    print("    displayId", d.displayId)
    print("    brightnessCapabilities", d.brightnessCapabilities ?? "")
    print("    brightnessAvailable", d.brightnessAvailable)
    print("    nits", d.nits)
    print("    contrast", d.contrast)
    print("    minimumLuminance", d.minimumLuminance)
    print("    maximumReferenceLuminance", d.maximumReferenceLuminance)
    print("    brightnessAvailable", d.brightnessAvailable)
    print("    maximumHDRLuminance", d.maximumHDRLuminance)
    print("    maximumBrightness", d.maximumBrightness)
    print("    maximumLuminance", d.maximumLuminance)
    print("    maximumSDRLuminance", d.maximumSDRLuminance)
}

// WindowServer    Display 1 setting nits to 888.889
// corebrightnessd SDR - perceptual ramp clocked: 227.095169 -> 252.268112 - 49.169426% (239.142059 Nits)
// WindowServer    Display 1 commitBrightness sdr: 211.603, headroom: 4.20075, ambient: 4.3396, filtered ambient: 13.6333, limit: 1600

func setToMax(_ d: CAWindowServerDisplay) {
    d.setBrightnessLimit(1600)
    d.setHeadroom(1)
    d.maximumBrightness = 1000.0
    d.setSDRBrightness(600)
    d.maximumHDRLuminance = 1600
    d.maximumReferenceLuminance = 1600
    d.maximumSDRLuminance = 1000
    d.contrast = 1.1
    d.commitBrightness(1)
    // d.update() // segfault
}

let ws: CAWindowServer? = (CAWindowServer.server(withOptions: nil) as? CAWindowServer)
if let ws = ws,
   let displays = ws.displays as? [CAWindowServerDisplay],
   let d = displays.first(where: { $0.deviceName == "primary" })
{
    printCADisplay(d)

    setToMax(d)
    printCADisplay(d)

    DispatchQueue.main.async {
        while true {
            sleep(2)
            setToMax(d)
            printCADisplay(d)
        }
    }
}

dispatchMain()
