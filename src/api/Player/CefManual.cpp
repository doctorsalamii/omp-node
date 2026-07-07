#include "../Impl.hpp"
#include "../API.hpp"
#include <Server/Components/Pawn/pawn.hpp>

// 1. Создать браузер
DECLARE_API(Player, CefCreateBrowser, objectPtr player, int browser_id, StringCharPtr url, bool hidden, bool focused)
{
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn) {
		auto native = pawn->findNative("cef_create_browser");
		if (native) {
			cell params[6];
			params[0] = 5 * sizeof(cell);
			params[1] = (cell)Runtime::Instance().GetOMPAPI()->Player.GetID(player);
			params[2] = (cell)browser_id;
			params[3] = reinterpret_cast<cell>(url); 
			params[4] = (cell)hidden;
			params[5] = (cell)focused;
			pawn->executeNative(*native, params);
			API_RETURN(bool true);
		}
	}
	API_RETURN(bool false);
}

// 2. Уничтожить браузер
DECLARE_API(Player, CefDestroyBrowser, objectPtr player, int browser_id)
{
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn) {
		auto native = pawn->findNative("cef_destroy_browser");
		if (native) {
			cell params[3];
			params[0] = 2 * sizeof(cell);
			params[1] = (cell)Runtime::Instance().GetOMPAPI()->Player.GetID(player);
			params[2] = (cell)browser_id;
			pawn->executeNative(*native, params);
			API_RETURN(bool true);
		}
	}
	API_RETURN(bool false);
}

// 3. Скрыть/Показать
DECLARE_API(Player, CefHideBrowser, objectPtr player, int browser_id, bool hide)
{
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn && pawn->findNative("cef_hide_browser")) {
		cell params[4];
		params[0] = 3 * sizeof(cell);
		params[1] = (cell)Runtime::Instance().GetOMPAPI()->Player.GetID(player);
		params[2] = (cell)browser_id;
		params[3] = (cell)hide;
		pawn->executeNative(*pawn->findNative("cef_hide_browser"), params);
		API_RETURN(bool true);
	}
	API_RETURN(bool false);
}

// 4. Фокус (курсор)
DECLARE_API(Player, CefFocusBrowser, objectPtr player, int browser_id, bool focused)
{
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn && pawn->findNative("cef_focus_browser")) {
		cell params[4];
		params[0] = 3 * sizeof(cell);
		params[1] = (cell)Runtime::Instance().GetOMPAPI()->Player.GetID(player);
		params[2] = (cell)browser_id;
		params[3] = (cell)focused;
		pawn->executeNative(*pawn->findNative("cef_focus_browser"), params);
		API_RETURN(bool true);
	}
	API_RETURN(bool false);
}
