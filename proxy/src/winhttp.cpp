#include "winhttp.hpp"

#include <filesystem>
#include <libloaderapi.h>
#include <sysinfoapi.h>

#define WINHTTP_FUNC(name)                                      \
    FARPROC o##name;                                            \
    extern "C" __declspec(dllexport) void WINAPI name() {   \
        o##name();                                              \
    }

#define LOAD_FUNC(name) o##name = GetProcAddress(hinst, #name)

WINHTTP_FUNC(WinHttpAddRequestHeaders)
WINHTTP_FUNC(WinHttpAddRequestHeadersEx)
WINHTTP_FUNC(WinHttpAutoProxySvcMain)
WINHTTP_FUNC(WinHttpCloseHandle)
WINHTTP_FUNC(WinHttpConnect)
WINHTTP_FUNC(WinHttpConnectionDeletePolicyEntries)
WINHTTP_FUNC(WinHttpConnectionDeleteProxyInfo)
WINHTTP_FUNC(WinHttpConnectionFreeNameList)
WINHTTP_FUNC(WinHttpConnectionFreeProxyInfo)
WINHTTP_FUNC(WinHttpConnectionFreeProxyList)
WINHTTP_FUNC(WinHttpConnectionGetNameList)
WINHTTP_FUNC(WinHttpConnectionGetProxyInfo)
WINHTTP_FUNC(WinHttpConnectionGetProxyList)
WINHTTP_FUNC(WinHttpConnectionSetPolicyEntries)
WINHTTP_FUNC(WinHttpConnectionSetProxyInfo)
WINHTTP_FUNC(WinHttpConnectionUpdateIfIndexTable)
WINHTTP_FUNC(WinHttpCrackUrl)
WINHTTP_FUNC(WinHttpCreateProxyResolver)
WINHTTP_FUNC(WinHttpCreateUrl)
WINHTTP_FUNC(WinHttpDetectAutoProxyConfigUrl)
WINHTTP_FUNC(WinHttpFreeProxyResult)
WINHTTP_FUNC(WinHttpFreeProxyResultEx)
WINHTTP_FUNC(WinHttpFreeProxySettings)
WINHTTP_FUNC(WinHttpGetDefaultProxyConfiguration)
WINHTTP_FUNC(WinHttpGetIEProxyConfigForCurrentUser)
WINHTTP_FUNC(WinHttpGetProxyForUrl)
WINHTTP_FUNC(WinHttpGetProxyForUrlEx)
WINHTTP_FUNC(WinHttpGetProxyForUrlEx2)
WINHTTP_FUNC(WinHttpGetProxyForUrlHvsi)
WINHTTP_FUNC(WinHttpGetProxyResult)
WINHTTP_FUNC(WinHttpGetProxyResultEx)
WINHTTP_FUNC(WinHttpGetProxySettingsVersion)
WINHTTP_FUNC(WinHttpGetTunnelSocket)
WINHTTP_FUNC(WinHttpOpen)
WINHTTP_FUNC(WinHttpOpenRequest)
WINHTTP_FUNC(WinHttpPacJsWorkerMain)
WINHTTP_FUNC(WinHttpProbeConnectivity)
WINHTTP_FUNC(WinHttpQueryAuthSchemes)
WINHTTP_FUNC(WinHttpQueryDataAvailable)
WINHTTP_FUNC(WinHttpQueryHeaders)
WINHTTP_FUNC(WinHttpQueryOption)
WINHTTP_FUNC(WinHttpReadData)
WINHTTP_FUNC(WinHttpReadProxySettings)
WINHTTP_FUNC(WinHttpReadProxySettingsHvsi)
WINHTTP_FUNC(WinHttpReceiveResponse)
WINHTTP_FUNC(WinHttpResetAutoProxy)
WINHTTP_FUNC(WinHttpSaveProxyCredentials)
WINHTTP_FUNC(WinHttpSendRequest)
WINHTTP_FUNC(WinHttpSetCredentials)
WINHTTP_FUNC(WinHttpSetDefaultProxyConfiguration)
WINHTTP_FUNC(WinHttpSetOption)
WINHTTP_FUNC(WinHttpSetProxySettingsPerUser)
WINHTTP_FUNC(WinHttpSetSecureLegacyServersAppCompat)
WINHTTP_FUNC(WinHttpSetStatusCallback)
WINHTTP_FUNC(WinHttpSetTimeouts)
WINHTTP_FUNC(WinHttpTimeFromSystemTime)
WINHTTP_FUNC(WinHttpTimeToSystemTime)
WINHTTP_FUNC(WinHttpWebSocketClose)
WINHTTP_FUNC(WinHttpWebSocketCompleteUpgrade)
WINHTTP_FUNC(WinHttpWebSocketQueryCloseStatus)
WINHTTP_FUNC(WinHttpWebSocketReceive)
WINHTTP_FUNC(WinHttpWebSocketSend)
WINHTTP_FUNC(WinHttpWebSocketShutdown)
WINHTTP_FUNC(WinHttpWriteData)
WINHTTP_FUNC(WinHttpWriteProxySettings)

void load_funcs(const HMODULE hinst) {
    LOAD_FUNC(WinHttpAddRequestHeaders);
    LOAD_FUNC(WinHttpAddRequestHeadersEx);
    LOAD_FUNC(WinHttpAutoProxySvcMain);
    LOAD_FUNC(WinHttpCloseHandle);
    LOAD_FUNC(WinHttpConnect);
    LOAD_FUNC(WinHttpConnectionDeletePolicyEntries);
    LOAD_FUNC(WinHttpConnectionDeleteProxyInfo);
    LOAD_FUNC(WinHttpConnectionFreeNameList);
    LOAD_FUNC(WinHttpConnectionFreeProxyInfo);
    LOAD_FUNC(WinHttpConnectionFreeProxyList);
    LOAD_FUNC(WinHttpConnectionGetNameList);
    LOAD_FUNC(WinHttpConnectionGetProxyInfo);
    LOAD_FUNC(WinHttpConnectionGetProxyList);
    LOAD_FUNC(WinHttpConnectionSetPolicyEntries);
    LOAD_FUNC(WinHttpConnectionSetProxyInfo);
    LOAD_FUNC(WinHttpConnectionUpdateIfIndexTable);
    LOAD_FUNC(WinHttpCrackUrl);
    LOAD_FUNC(WinHttpCreateProxyResolver);
    LOAD_FUNC(WinHttpCreateUrl);
    LOAD_FUNC(WinHttpDetectAutoProxyConfigUrl);
    LOAD_FUNC(WinHttpFreeProxyResult);
    LOAD_FUNC(WinHttpFreeProxyResultEx);
    LOAD_FUNC(WinHttpFreeProxySettings);
    LOAD_FUNC(WinHttpGetDefaultProxyConfiguration);
    LOAD_FUNC(WinHttpGetIEProxyConfigForCurrentUser);
    LOAD_FUNC(WinHttpGetProxyForUrl);
    LOAD_FUNC(WinHttpGetProxyForUrlEx);
    LOAD_FUNC(WinHttpGetProxyForUrlEx2);
    LOAD_FUNC(WinHttpGetProxyForUrlHvsi);
    LOAD_FUNC(WinHttpGetProxyResult);
    LOAD_FUNC(WinHttpGetProxyResultEx);
    LOAD_FUNC(WinHttpGetProxySettingsVersion);
    LOAD_FUNC(WinHttpGetTunnelSocket);
    LOAD_FUNC(WinHttpOpen);
    LOAD_FUNC(WinHttpOpenRequest);
    LOAD_FUNC(WinHttpPacJsWorkerMain);
    LOAD_FUNC(WinHttpProbeConnectivity);
    LOAD_FUNC(WinHttpQueryAuthSchemes);
    LOAD_FUNC(WinHttpQueryDataAvailable);
    LOAD_FUNC(WinHttpQueryHeaders);
    LOAD_FUNC(WinHttpQueryOption);
    LOAD_FUNC(WinHttpReadData);
    LOAD_FUNC(WinHttpReadProxySettings);
    LOAD_FUNC(WinHttpReadProxySettingsHvsi);
    LOAD_FUNC(WinHttpReceiveResponse);
    LOAD_FUNC(WinHttpResetAutoProxy);
    LOAD_FUNC(WinHttpSaveProxyCredentials);
    LOAD_FUNC(WinHttpSendRequest);
    LOAD_FUNC(WinHttpSetCredentials);
    LOAD_FUNC(WinHttpSetDefaultProxyConfiguration);
    LOAD_FUNC(WinHttpSetOption);
    LOAD_FUNC(WinHttpSetProxySettingsPerUser);
    LOAD_FUNC(WinHttpSetSecureLegacyServersAppCompat);
    LOAD_FUNC(WinHttpSetStatusCallback);
    LOAD_FUNC(WinHttpSetTimeouts);
    LOAD_FUNC(WinHttpTimeFromSystemTime);
    LOAD_FUNC(WinHttpTimeToSystemTime);
    LOAD_FUNC(WinHttpWebSocketClose);
    LOAD_FUNC(WinHttpWebSocketCompleteUpgrade);
    LOAD_FUNC(WinHttpWebSocketQueryCloseStatus);
    LOAD_FUNC(WinHttpWebSocketReceive);
    LOAD_FUNC(WinHttpWebSocketSend);
    LOAD_FUNC(WinHttpWebSocketShutdown);
    LOAD_FUNC(WinHttpWriteData);
    LOAD_FUNC(WinHttpWriteProxySettings);
}

void init_proxy() {
    char system_path[MAX_PATH];
    GetSystemDirectoryA(system_path, MAX_PATH);

    const std::filesystem::path system32_path = system_path;
    const std::filesystem::path winhttp_path = system32_path / "winhttp.dll";
    // load original dll
    const HMODULE winhttp_dll = LoadLibraryW(winhttp_path.c_str());
    load_funcs(winhttp_dll); // provide a handle so our methods call the original methods
}