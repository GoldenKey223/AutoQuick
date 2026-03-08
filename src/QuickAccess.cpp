#include "QuickAccess.h"

int toggleQuickAccess(const std::wstring& path){
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.fMask = SEE_MASK_UNICODE | SEE_MASK_INVOKEIDLIST | SEE_MASK_FLAG_NO_UI;
    sei.lpVerb = L"pintohome";
    sei.lpFile = path.c_str();
    sei.nShow = SW_HIDE;

    if (!ShellExecuteExW(&sei)) {
        DWORD error = GetLastError();
        std::cerr << "ShellExecuteEx failed. Error: " << std::dec << error << std::endl;
    } else {
        std::wcout << L"Successfully invoked: " << L"pintohome" << L" on " << path << std::endl;
    }
    CoUninitialize();

    return 0;
}

int resetQuickAccess(){
    wchar_t* appDataPath = nullptr;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &appDataPath))) {
        std::filesystem::path path = appDataPath;
        path /= L"Microsoft\\Windows\\Recent\\AutomaticDestinations\\f01b4d95cf55d32a.automaticDestinations-ms";
        
        std::error_code ec;
        if (std::filesystem::remove(path, ec)) {
            std::cout << "Quick Access Reset Successfully." << std::endl;
        }
        CoTaskMemFree(appDataPath);
    }
    return 0;
}