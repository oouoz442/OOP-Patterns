#include <iostream>
#include <memory>
using namespace std;

// === Абстрактные продукты ===
class Window {
public:
    virtual void Draw() const = 0;
    virtual ~Window() = default;
};

class Button {
public:
    virtual void Click() const = 0;
    virtual ~Button() = default;
};

// === Конкретные продукты для Windows ===
class WinWindow : public Window {
public:
    void Draw() const override {
        cout << "Drawing Windows-style window\n";
    }
};

class WinButton : public Button {
public:
    void Click() const override {
        cout << "Clicking Windows-style button\n";
    }
};

// === Конкретные продукты для Mac ===
class MacWindow : public Window {
public:
    void Draw() const override {
        cout << "Drawing Mac-style window\n";
    }
};

class MacButton : public Button {
public:
    void Click() const override {
        cout << "Clicking Mac-style button\n";
    }
};

// === Абстрактная фабрика UI ===
class UIFactory {
public:
    virtual shared_ptr<Window> CreateWindow() const = 0;
    virtual shared_ptr<Button> CreateButton() const = 0;
    virtual ~UIFactory() = default;
};

// === Конкретные фабрики ===
class WinFactory : public UIFactory {
public:
    shared_ptr<Window> CreateWindow() const override {
        return make_shared<WinWindow>();
    }

    shared_ptr<Button> CreateButton() const override {
        return make_shared<WinButton>();
    }
};

class MacFactory : public UIFactory {
public:
    shared_ptr<Window> CreateWindow() const override {
        return make_shared<MacWindow>();
    }

    shared_ptr<Button> CreateButton() const override {
        return make_shared<MacButton>();
    }
};

// === Приложение-клиент ===
class Application {
private:
    shared_ptr<Window> window;
    shared_ptr<Button> button;

public:
    Application(shared_ptr<UIFactory> factory) {
        window = factory->CreateWindow();
        button = factory->CreateButton();
    }

    void RenderUI() {
        window->Draw();
        button->Click();
    }
};

// === main() ===
int main() {
    shared_ptr<UIFactory> factory1 = make_shared<WinFactory>();
    Application app1(factory1);
    app1.RenderUI();

    shared_ptr<UIFactory> factory2 = make_shared<MacFactory>();
    Application app2(factory2);
    app2.RenderUI();

    return 0;
}