#pragma once
#include <winrt/Windows.Media.Capture.Frames.h>
#include <winrt/Windows.Media.Capture.h>

//AL
#include <winrt/Windows.Foundation.h>
#include <array>

using namespace winrt;
using namespace Windows::Media::Capture;
using namespace Windows::Media::Capture::Frames;

class MediaCaptureHelper {
public:
    MediaCaptureHelper();
    void InitializeMediaFrameReader(MediaCapture mediaCapture);

    // Getters for camera intrinsics, AL
    double GetFocalLengthX() const { return focalLengthX; }
    double GetFocalLengthY() const { return focalLengthY; }
    double GetPrincipalPointX() const { return principalPointX; }
    double GetPrincipalPointY() const { return principalPointY; }
    std::array<double, 3> GetRadialDistortion() const { return radialDistortion; }
    double GetTangentialDistortionX() const { return tangentialDistortionX; }
    double GetTangentialDistortionY() const { return tangentialDistortionY; }

private:
    void ExtractCameraIntrinsics(MediaFrameReader sender, MediaFrameArrivedEventArgs args);
    MediaFrameReader m_frameReader{ nullptr };

    // Variables to store camera intrinsics, AL
    double focalLengthX = 0.0;
    double focalLengthY = 0.0;
    double principalPointX = 0.0;
    double principalPointY = 0.0;
    std::array<double, 3> radialDistortion{};
    double tangentialDistortionX = 0.0;
    double tangentialDistortionY = 0.0;

};