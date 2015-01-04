#ifndef RAIIHDESKTOP123_h
#define RAIIHDESKTOP123_h

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <memory>
#include <utility>
#include <type_traits>


namespace RemoteDesktop{
	struct HWNDTimer{
		HWND h; UINT_PTR id; 
		HWNDTimer(HWND hwnd, UINT_PTR i, UINT time) : h(hwnd), id(i) {
			SetTimer(h, id, time, nullptr); //every 500 ms windows will send a timer notice to the msg proc below. This allows the destructor to set _Running to false and the message proc to break
		}
	}; 
	struct SOCKETWrapper{
		SOCKET socket = INVALID_SOCKET;
		SOCKETWrapper(SOCKET s) : socket(s) {}
	};
	namespace INTERNAL{
		void dialogboxcleanup(HWND h);
		void hwndtimercleanup(HWNDTimer* h); 
		void socketcleanup(SOCKETWrapper* s);
	}
	typedef std::unique_ptr<std::remove_pointer<HANDLE>::type, decltype(&::CloseHandle)> RAIIHANDLE_TYPE;
#define RAIIHANDLE(handle) std::unique_ptr<std::remove_pointer<HANDLE>::type, decltype(&::CloseHandle)>(handle, &::CloseHandle)

	typedef std::unique_ptr<std::remove_pointer<HMODULE>::type, decltype(&::FreeLibrary)> RAIIHMODULE_TYPE;
#define RAIIHMODULE(handle) std::unique_ptr<std::remove_pointer<HMODULE>::type, decltype(&::FreeLibrary)>(handle, &::FreeLibrary)

	typedef std::unique_ptr<std::remove_pointer<HDESK>::type, decltype(&::CloseDesktop)> RAIIHDESKTOP_TYPE;
#define RAIIHDESKTOP(handle) std::unique_ptr<std::remove_pointer<HDESK>::type, decltype(&::CloseDesktop)>(handle, &::CloseDesktop)

	typedef std::unique_ptr<std::remove_pointer<SC_HANDLE>::type, decltype(&::CloseServiceHandle)> RAIISC_HANDLE_TYPE;
#define RAIISC_HANDLE(handle) std::unique_ptr<std::remove_pointer<SC_HANDLE>::type, decltype(&::CloseServiceHandle)>(handle, &::CloseServiceHandle)

	typedef std::unique_ptr<std::remove_pointer<HMENU>::type, decltype(&::DestroyMenu)> RAIIHMENU_TYPE;
#define RAIIHMENU(handle) std::unique_ptr<std::remove_pointer<HMENU>::type, decltype(&::DestroyMenu)>(handle, &::DestroyMenu)

	typedef std::unique_ptr<std::remove_pointer<HICON>::type, decltype(&::DestroyIcon)> RAIIHICON_TYPE;
#define RAIIHICON(handle) std::unique_ptr<std::remove_pointer<HICON>::type, decltype(&::DestroyIcon)>(handle, &::DestroyIcon)

	typedef std::unique_ptr<std::remove_pointer<HDC>::type, decltype(&::DeleteDC)> RAIIHDC_TYPE;
#define RAIIHDC(handle) std::unique_ptr<std::remove_pointer<HDC>::type, decltype(&::DeleteDC)>(handle, &::DeleteDC)

	typedef std::unique_ptr<std::remove_pointer<HBITMAP>::type, decltype(&::DeleteObject)> RAIIHBITMAP_TYPE;
#define RAIIHBITMAP(handle) std::unique_ptr<std::remove_pointer<HBITMAP>::type, decltype(&::DeleteObject)>(handle, &::DeleteObject)

	typedef std::unique_ptr<std::remove_pointer<HFONT>::type, decltype(&::DeleteObject)> RAIIHFONT_TYPE;
#define RAIIHFONT(handle) std::unique_ptr<std::remove_pointer<HFONT>::type, decltype(&::DeleteObject)>(handle, &::DeleteObject)	

	typedef std::unique_ptr<std::remove_pointer<HWND>::type, decltype(&RemoteDesktop::INTERNAL::dialogboxcleanup)> RAIIDIALOGBOX_TYPE;
#define RAIIDIALOGBOX(handle) std::unique_ptr<std::remove_pointer<HWND>::type, decltype(&RemoteDesktop::INTERNAL::dialogboxcleanup)>(handle, &RemoteDesktop::INTERNAL::dialogboxcleanup)	

	typedef std::unique_ptr<HWNDTimer, decltype(&RemoteDesktop::INTERNAL::hwndtimercleanup)> RAIIHWNDTIMER_TYPE;
#define RAIIHWNDTIMER(handle, id, time) std::unique_ptr<HWNDTimer, decltype(&RemoteDesktop::INTERNAL::hwndtimercleanup)>(new HWNDTimer(handle, id, time), &RemoteDesktop::INTERNAL::hwndtimercleanup)	

	typedef std::unique_ptr<std::remove_pointer<HWND>::type, decltype(&::RemoveClipboardFormatListener)> RAIICLIPBOARDLISTENER_TYPE;
#define RAIICLIPBOARDLISTENER(handle) std::unique_ptr<std::remove_pointer<HWND>::type, decltype(&::RemoveClipboardFormatListener)>(handle, &::RemoveClipboardFormatListener)	

	typedef std::unique_ptr<SOCKETWrapper, decltype(&RemoteDesktop::INTERNAL::socketcleanup)> RAIISOCKET_TYPE;
#define RAIISOCKET(handle) std::unique_ptr<SOCKETWrapper, decltype(&RemoteDesktop::INTERNAL::socketcleanup)>(new SOCKETWrapper(handle), &RemoteDesktop::INTERNAL::socketcleanup)	

}

#endif