#include "../Impl.hpp"
#include "../API.hpp"
#include "../../Manager.hpp"

// Исправляем ошибку 'amx/amx.h' not found, определяя тип cell вручную
typedef int32_t cell;

// Интерфейс для взаимодействия с Pawn (чтобы не подключать тяжелые заголовки)
struct ICustomPawn {
	virtual void* findNative(const char* name) = 0;
	virtual int executeNative(void* native, cell* params) = 0;
};

// Функция создания браузера
static void CefCreateBrowser_JS(const v8::FunctionCallbackInfo<v8::Value>& info) {
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
	if (info.Length() < 4) return;

	int browser_id = info[0]->Int32Value(ctx).ToChecked();
	v8::String::Utf8Value url_v8(isolate, info[1]);
	bool hidden = info[2]->BooleanValue(isolate);
	bool focused = info[3]->BooleanValue(isolate);

	IPlayer* player = reinterpret_cast<IPlayer*>(info.Data().As<v8::External>()->Value());
	
	// Используем универсальный способ поиска Pawn
	auto pawn = reinterpret_cast<ICustomPawn*>(Runtime::Instance().GetCore()->queryExtension(UID(0x3673c4d5162a0d70ull))); // UID компонента Pawn
	
	if (pawn && player) {
		void* native = pawn->findNative("cef_create_browser");
		if (native) {
			cell params[6] = {5 * 4, (cell)player->getID(), (cell)browser_id, reinterpret_cast<cell>(*url_v8), (cell)hidden, (cell)focused};
			pawn->executeNative(native, params);
		}
	}
}

// Авто-регистратор
class CefInitializer {
public:
	CefInitializer() {
		APIManager::Instance().Register("Player", "cefCreateBrowser", &CefCreateBrowser_JS);
	}
} _cefInit;
