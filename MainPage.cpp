#include "pch.h"

//ABJL
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Capture.h>
#include <winrt/Windows.Media.Capture.Frames.h>
#include <iostream>

#include "MainPage.h"
#include "MainPage.g.cpp"

#include <winrt/Windows.Storage.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

//ABJL
using namespace Windows::Foundation;
using namespace Windows::Media::Capture;
using namespace Windows::Media::Capture::Frames;

using namespace winrt::Windows::Storage;

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

        //init_apartment(winrt::apartment_type::single_threaded);

        auto captureUI = CameraCaptureUI();
        captureUI.PhotoSettings().Format(CameraCaptureUIPhotoFormat::Jpeg);
        captureUI.PhotoSettings().CroppedSizeInPixels({ 800, 600 });

        captureUI.CaptureFileAsync(CameraCaptureUIMode::Photo).Completed([](IAsyncOperation<StorageFile> asyncInfo, AsyncStatus status)
            {
                auto file = asyncInfo.GetResults();
                if (file)
                {
                    // Use file.Path() to get the file path
                    // Optionally, display the photo in the UI
                    // statusTextBlock().Text(L"Picture Taken.");
                }
            });


        //uninit_apartment();
    }
}
