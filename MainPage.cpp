#include "pch.h"

//ABJL
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Capture.h>
#include <winrt/Windows.Media.Capture.Frames.h>
#include <iostream>

#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

//ABJL
using namespace Windows::Foundation;
using namespace Windows::Media::Capture;
using namespace Windows::Media::Capture::Frames;

namespace winrt::holo_3::implementation
{
    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        //myButton().Content(box_value(L"Clicked"));
        //<TextBlock x:Name="myTextBlock" Text="Hello, Windows 10!" />
        //myTextBlock().Text(L"Hello World");

        init_apartment(winrt::apartment_type::single_threaded);

        try {
            MediaCapture mediaCapture{};
            MediaCaptureInitializationSettings settings{};
            settings.StreamingCaptureMode(StreamingCaptureMode::Video);

            mediaCapture.InitializeAsync(settings).get();
            auto frameSources = mediaCapture.FrameSources();
            MediaFrameSource frameSource = nullptr;

            for (auto&& source : frameSources) {
                auto sourceInfo = source.Value().Info();
                auto sourceKind = sourceInfo.SourceKind();
                if (sourceKind == MediaFrameSourceKind::Color) {
                    frameSource = source.Value();
                    break;
                }
            }

            if (frameSource != nullptr) {
                statusTextBlock().Text(L"Color video frame source found.");
            }
            else {
                statusTextBlock().Text(L"Color video frame source not found.");
            }
        }
        catch (const winrt::hresult_error& ex) {
            statusTextBlock().Text(L"Initialization failed with error: " + ex.message());
        }

        uninit_apartment();
    }
}
