vpath %.swift Sources

.build/arm64-apple-macosx/debug/monitorpanel: $(wildcard Sources/monitorpanel/*.swift) $(wildcard Sources/*.h)
	swift build \
	    -Xswiftc -F$$PWD/Sources \
	    -Xswiftc -F/System/Library/PrivateFrameworks \
	    -Xswiftc -framework -Xswiftc DisplayServices \
	    -Xswiftc -framework -Xswiftc CoreDisplay \
	    -Xswiftc -framework -Xswiftc OSD \
	    -Xswiftc -framework -Xswiftc MonitorPanel \
	    -Xswiftc -import-objc-header -Xswiftc Sources/Bridging-Header.h

.build/x86_64-apple-macosx/debug/monitorpanel: $(wildcard Sources/monitorpanel/*.swift) $(wildcard Sources/*.h)
	swift build \
		--arch x86_64 \
	    -Xswiftc -F$$PWD/Sources \
	    -Xswiftc -F/System/Library/PrivateFrameworks \
	    -Xswiftc -framework -Xswiftc DisplayServices \
	    -Xswiftc -framework -Xswiftc CoreDisplay \
	    -Xswiftc -framework -Xswiftc OSD \
	    -Xswiftc -framework -Xswiftc MonitorPanel \
	    -Xswiftc -import-objc-header -Xswiftc Sources/Bridging-Header.h

.build/arm64-apple-macosx/release/monitorpanel: $(wildcard Sources/monitorpanel/*.swift) $(wildcard Sources/*.h)
	swift build \
		-c release \
		--arch x86_64 \
	    -Xswiftc -F$$PWD/Sources \
	    -Xswiftc -F/System/Library/PrivateFrameworks \
	    -Xswiftc -framework -Xswiftc DisplayServices \
	    -Xswiftc -framework -Xswiftc CoreDisplay \
	    -Xswiftc -framework -Xswiftc OSD \
	    -Xswiftc -framework -Xswiftc MonitorPanel \
	    -Xswiftc -import-objc-header -Xswiftc Sources/Bridging-Header.h

.build/x86_64-apple-macosx/release/monitorpanel: $(wildcard Sources/monitorpanel/*.swift) $(wildcard Sources/*.h)
	swift build \
		-c release \
	    -Xswiftc -F$$PWD/Sources \
	    -Xswiftc -F/System/Library/PrivateFrameworks \
	    -Xswiftc -framework -Xswiftc DisplayServices \
	    -Xswiftc -framework -Xswiftc CoreDisplay \
	    -Xswiftc -framework -Xswiftc OSD \
	    -Xswiftc -framework -Xswiftc MonitorPanel \
	    -Xswiftc -import-objc-header -Xswiftc Sources/Bridging-Header.h

debug-x86: .build/x86_64-apple-macosx/debug/monitorpanel
release-x86: .build/x86_64-apple-macosx/release/monitorpanel
debug: .build/arm64-apple-macosx/debug/monitorpanel
release: .build/arm64-apple-macosx/release/monitorpanel

build: debug
all: build

run-x86: debug-x86
	.build/x86_64-apple-macosx/debug/monitorpanel

run: debug
	.build/arm64-apple-macosx/debug/monitorpanel

watch:
	rg --files -t swift -t h | entr make run
