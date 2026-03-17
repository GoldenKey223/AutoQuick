# include "NetworkDrive.h"

int mapNetworkDrive(const NetworkDrive& drive) {
    NETRESOURCEW nr;
    ZeroMemory(&nr, sizeof(NETRESOURCEW));

    nr.dwType = RESOURCETYPE_DISK;
    nr.lpLocalName = const_cast<LPWSTR>(drive.local_name.c_str());
    nr.lpRemoteName = const_cast<LPWSTR>(drive.remote_name.c_str());
    nr.lpProvider = NULL;

    LPCWSTR username = drive.username.c_str();
    LPCWSTR password = drive.password.c_str();


    std::wcout << L"Attempting to connect..." << std::endl;

    DWORD result = WNetAddConnection2W(&nr, password, username, CONNECT_UPDATE_PROFILE);

    if (result == NO_ERROR) {
        std::wcout << L"Successfully connected WebDAV to Z:" << std::endl;
    } else {
        std::wcout << L"Failed to connect. Error code: " << result << std::endl;
        // Error 1204 = The specified network provider name is invalid (WebClient service might be stopped)
        // Error 86 = Invalid password
        // Error 1244 = Not authenticated
    }

    return 0;
}