#include "pch.h"

//ABJL
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Capture.h>
#include <winrt/Windows.Media.Capture.Frames.h>
#include <iostream>

#include "MainPage.h"
#include "MainPage.g.cpp"
#include "MediaCaptureHelper.h"

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

            MediaCaptureHelper helper{};
            helper.InitializeMediaFrameReader(mediaCapture);

            // Print the extracted camera intrinsics
            double focalLengthX = helper.GetFocalLengthX();
            std::string focalLengthX_str = std::to_string(focalLengthX);
            std::wstring focalLengthX_wstr(focalLengthX_str.begin(), focalLengthX_str.end());
            winrt::hstring focalLengthX_hstr(focalLengthX_wstr);
            //auto dispatcher = Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher();
            //dispatcher.RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [this, focalLengthX_hstr]() {
            //    statusTextBlock().Text(focalLengthX_hstr);
            //    });
            std::wcout << "Focal Length X: " << focalLengthX << std::endl;

        }
        catch (const winrt::hresult_error& ex) {
            statusTextBlock().Text(L"Initialization failed with error: " + ex.message());
        }

        uninit_apartment();
    }
}
