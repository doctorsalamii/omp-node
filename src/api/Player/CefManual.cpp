#include "../Impl.hpp"
#include "../API.hpp"
#include <Server/Components/Pawn/pawn.hpp>

// 1. Создать браузер
static void CefCreateBrowser_JS(const v8::FunctionCallbackInfo<v8::Value>& info) {
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
	if (info.Length() < 4) return;
	int browser_id = info[0]->Int32Value(ctx).ToChecked();
	v8::String::Utf8Value url_v8(isolate, info[1]);
	bool hidden = info[2]->BooleanValue(isolate);
	bool focused = info[3]->BooleanValue(isolate);
	IPlayer* player = reinterpret_cast<IPlayer*>(info.Data().As<v8::External>()->Value());
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn && player) {
		auto native = pawn->findNative("cef_create_browser");
		if (native) {
			cell params[6] = {5 * 4, (cell)player->getID(), (cell)browser_id, reinterpret_cast<cell>(*url_v8), (cell)hidden, (cell)focused};
			pawn->executeNative(*native, params);
		}
	}
}

// 2. Уничтожить браузер
static void CefDestroyBrowser_JS(const v8::FunctionCallbackInfo<v8::Value>& info) {
	v8::Isolate* isolate = info.GetIsolate();
	if (info.Length() < 1) return;
	int browser_id = info[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();
	IPlayer* player = reinterpret_cast<IPlayer*>(info.Data().As<v8::External>()->Value());
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn && player) {
		auto native = pawn->findNative("cef_destroy_browser");
		if (native) {
			cell params[3] = {2 * 4, (cell)player->getID(), (cell)browser_id};
			pawn->executeNative(*native, params);
		}
	}
}

// 3. Скрыть браузер
static void CefHideBrowser_JS(const v8::FunctionCallbackInfo<v8::Value>& info) {
	v8::Isolate* isolate = info.GetIsolate();
	if (info.Length() < 2) return;
	int browser_id = info[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();
	bool hide = info[1]->BooleanValue(isolate);
	IPlayer* player = reinterpret_cast<IPlayer*>(info.Data().As<v8::External>()->Value());
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn && player) {
		auto native = pawn->findNative("cef_hide_browser");
		if (native) {
			cell params[4] = {3 * 4, (cell)player->getID(), (cell)browser_id, (cell)hide};
			pawn->executeNative(*native, params);
		}
	}
}

// 4. Фокус (курсор)
static void CefFocusBrowser_JS(const v8::FunctionCallbackInfo<v8::Value>& info) {
	v8::Isolate* isolate = info.GetIsolate();
	if (info.Length() < 2) return;
	int browser_id = info[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();
	bool focus = info[1]->BooleanValue(isolate);
	IPlayer* player = reinterpret_cast<IPlayer*>(info.Data().As<v8::External>()->Value());
	auto pawn = Runtime::Instance().GetCore()->queryExtension<IPawnComponent>();
	if (pawn && player) {
		auto native = pawn->findNative("cef_focus_browser");
		if (native) {
			cell params[4] = {3 * 4, (cell)player->getID(), (cell)browser_id, (cell)focus};
			pawn->executeNative(*native, params);
		}
	}
}

// Авто-регистратор всех функций сразу
class CefInitializer {
public:
	CefInitializer() {
		APIManager::Instance().Register("Player", "cefCreateBrowser", &CefCreateBrowser_JS);
		APIManager::Instance().Register("Player", "cefDestroyBrowser", &CefDestroyBrowser_JS);
		APIManager::Instance().Register("Player", "cefHideBrowser", &CefHideBrowser_JS);
		APIManager::Instance().Register("Player", "cefFocusBrowser", &CefFocusBrowser_JS);
	}
} _cefInit;
