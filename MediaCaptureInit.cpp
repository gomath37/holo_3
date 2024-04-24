//ABJL
#include "pch.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Capture.h>
#include <winrt/Windows.Media.Capture.Frames.h>
#include <iostream>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Media::Capture;
using namespace Windows::Media::Capture::Frames;

int main() {
    init_apartment();  // Initialize the COM apartment.

    MediaCapture mediaCapture{};
    MediaCaptureInitializationSettings settings{};
    settings.StreamingCaptureMode(StreamingCaptureMode::Video);

    // Initialize MediaCapture
    try {
        mediaCapture.InitializeAsync(settings).get();
        std::cout << "MediaCapture initialized successfully.\n";

        // Get the frame source
        auto frameSources = mediaCapture.FrameSources();
        MediaFrameSource frameSource = nullptr;

        for (auto&& source : frameSources) {
            auto sourceInfo = source.Value().Info();
            auto sourceKind = sourceInfo.SourceKind();
            if (sourceKind == MediaFrameSourceKind::Color) { // Checking for a color video source
                frameSource = source.Value();
                break;
            }
        }

        if (frameSource != nullptr) {
            std::cout << "Video frame source found.\n";
        }
        else {
            std::cout << "Video frame source not found.\n";
        }
    }
    catch (const hresult_error& ex) {
        std::wcerr << L"Initialization failed with error: " << ex.message().c_str() << std::endl;
    }

    uninit_apartment();  // Clean up the COM apartment.
    return 0;
}
