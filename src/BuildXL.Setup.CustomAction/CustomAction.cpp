#include "stdafx.h"
#include "resource.h"

using namespace ATL;

#pragma warning(disable: 6031)

INT __stdcall BrowseForInstallFolder(MSIHANDLE hInstall)
{
    HRESULT hr = S_OK;
    CComPtr<IFileDialog2> fileDialog;
    CComPtr<IModalWindow> modalWindow;
    CComPtr<IShellItem> shellItem;
    CStringW strTitle, filePath;
    HWND hWndParent = FindWindowW(L"MsiDialogCloseClass", nullptr);

    hr = WcaInitialize(hInstall, "BrowseForInstallFolder");
    ExitOnFailure(hr, "Failed to initialize");
    
    hr = fileDialog.CoCreateInstance(CLSID_FileOpenDialog);
    ExitOnFailure(hr, "Could not CoCreateInstance(CLSID_FileOpenDialog)");

    strTitle.LoadStringW(IDS_SELECT_FOLDER_DIALOG_TITLE);
    hr = fileDialog->SetTitle(strTitle);
    ExitOnFailure(hr, "IFileDialog::SetTitle() failed");

    hr = fileDialog->SetOptions(FOS_FORCEFILESYSTEM | FOS_PICKFOLDERS | FOS_NOTESTFILECREATE | FOS_DONTADDTORECENT);
    ExitOnFailure(hr, "IFileDialog::SetOptions() failed");

    hr = fileDialog.QueryInterface(&modalWindow);
    ExitOnFailure(hr, "IFileDialog::QueryInterface(IModalWindow) failed");
    
    hr = modalWindow->Show(hWndParent);
    if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
    {
        // User cancelled. This is not an error.
        hr = S_OK;
        goto LExit;
    }
    ExitOnFailure(hr, "IFileDialog::Show() failed");

    hr = fileDialog->GetResult(&shellItem);
    ExitOnFailure(hr, "IFileDialog::GetResult() failed");

    auto buffer = filePath.GetBuffer(MAX_PATH);
    hr = shellItem->GetDisplayName(SIGDN_FILESYSPATH, &buffer);
    filePath.ReleaseBuffer();
    ExitOnFailure(hr, "Could not extract filesystem path from IShellItem");

    hr = WcaSetProperty(L"WIXUI_INSTALLDIR", filePath.GetString());
    ExitOnFailure(hr, "MsiSetPropertyW() failed");
    
    hr = S_OK;

LExit:
    // Don't fail the install if an error occurred here.
    // Instead, display an error dialog.
    if (FAILED(hr)) {
        CString title; title.LoadStringW(IDS_TITLE);
        CString message; message.FormatMessageW(IDS_SELECT_FOLDER_ERROR_MESSAGE, hr);
        ::MessageBoxW(hWndParent, message.GetString(), title.GetString(), MB_OK | MB_ICONERROR);
    }

    return WcaFinalize(ERROR_SUCCESS);
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason, LPVOID)
{
    switch (ulReason)
    {
    case DLL_PROCESS_ATTACH:
        WcaGlobalInitialize(hInst);
        break;

    case DLL_PROCESS_DETACH:
        WcaGlobalFinalize();
        break;
    }

    return TRUE;
}
