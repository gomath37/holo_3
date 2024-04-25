#include "pch.h"
#include "MediaCaptureHelper.h"

#include <winrt/Windows.Media.Capture.h>
#include <winrt/Windows.Media.Capture.Frames.h>
#include <winrt/Windows.Media.Devices.Core.h> // Make sure this is included for CameraIntrinsics

using namespace winrt;
using namespace Windows::Media::Capture;
using namespace Windows::Media::Capture::Frames;
using namespace winrt::Windows::Media::Devices::Core; // This is important for CameraIntrinsics

MediaCaptureHelper::MediaCaptureHelper() {}

void MediaCaptureHelper::InitializeMediaFrameReader(MediaCapture mediaCapture) {
    //auto frameSource = mediaCapture.FrameSources().First().Current().Value(); // Simplified for example
    MediaFrameSource frameSource = nullptr;
    for (auto&& item : mediaCapture.FrameSources())
    {
        auto frameSource_temp = item.Value();
        auto sourceInfo = frameSource_temp.Info();
        if (sourceInfo.SourceKind() == MediaFrameSourceKind::Color)
        {
            // Found the color video source; proceed with using 'frameSource'
            frameSource = item.Value();
            break;
        }
    }
    m_frameReader = mediaCapture.CreateFrameReaderAsync(frameSource).get();
    m_frameReader.FrameArrived({ this, &MediaCaptureHelper::ExtractCameraIntrinsics });
    m_frameReader.StartAsync().get();
}

//void MediaCaptureHelper::ExtractCameraIntrinsics(MediaFrameReference frame) {
void MediaCaptureHelper::ExtractCameraIntrinsics(MediaFrameReader sender, MediaFrameArrivedEventArgs args) {
    auto frame = sender.TryAcquireLatestFrame();
    if (frame) {
        auto videoFrame = frame.VideoMediaFrame();
        if (videoFrame) {
			auto cameraIntrinsics = videoFrame.CameraIntrinsics();
			if (cameraIntrinsics) {
                // Process camera intrinsics here
				// Store camera intrinsics in double precision
				focalLengthX = cameraIntrinsics.FocalLength().x;
				focalLengthY = cameraIntrinsics.FocalLength().y;
				principalPointX = cameraIntrinsics.PrincipalPoint().x;
				principalPointY = cameraIntrinsics.PrincipalPoint().y;
				radialDistortion[0] = cameraIntrinsics.RadialDistortion().x;
				radialDistortion[1] = cameraIntrinsics.RadialDistortion().y;
				radialDistortion[2] = cameraIntrinsics.RadialDistortion().z;
				tangentialDistortionX = cameraIntrinsics.TangentialDistortion().x;
				tangentialDistortionY = cameraIntrinsics.TangentialDistortion().y;
			}
		}
	}
}
