#include <iostream>
#include <memory>
#include <string>

// 抽象产品：按钮接口
class Button {
public:
    // 纯虚函数，用于绘制按钮，具体实现由派生类完成
    virtual void paint() = 0;
    // 虚析构函数，确保正确释放派生类对象
    virtual ~Button() = default;
};

// 抽象产品：复选框接口
class Checkbox {
public:
    // 检查复选框是否被选中
    bool ifIsChecked() {
        return isChecked;
    }
    // 点击复选框，切换选中状态
    void clickCheckbox() {
        isChecked = !isChecked;
    }
    // 纯虚函数，用于设置复选框选中时的颜色，具体实现由派生类完成
    virtual void CheckedColor() = 0;
    // 虚析构函数，确保正确释放派生类对象
    virtual ~Checkbox() = default;

protected:
    bool isChecked = false;
};

// 抽象产品：文本接口
class Text {
public:
    // 纯虚函数，用于设置字体，具体实现由派生类完成
    virtual void setFont(const std::string& s) = 0;
    // 纯虚函数，用于显示文本，具体实现由派生类完成
    virtual void show() = 0;
    // 设置文本内容
    void setText(const std::string& s) {
        text = s;
    }
    // 虚析构函数，确保正确释放派生类对象
    virtual ~Text() = default;

protected:
    std::string text;
};

// 抽象工厂接口
class GUIFactory {
public:
    // 纯虚函数，用于创建按钮，具体实现由派生类完成
    virtual std::unique_ptr<Button> createButton() = 0;
    // 纯虚函数，用于创建复选框，具体实现由派生类完成
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    // 纯虚函数，用于创建文本，具体实现由派生类完成
    virtual std::unique_ptr<Text> createText() = 0;
    // 虚析构函数，确保正确释放派生类对象
    virtual ~GUIFactory() = default;
};

// 具体产品：Windows按钮
class WinButton : public Button {
public:
    // 实现绘制按钮的方法
    void paint() override {
        std::cout << "windows button paint.\n";
    }
};

// 具体产品：Windows复选框
class WinCheckBox : public Checkbox {
public:
    // 实现设置复选框选中时颜色的方法
    void CheckedColor() override {
        std::cout << "Windows Checkbox now is checked\n";
        std::cout << "Windows Checkbox's color is red!\n";
    }
};

// 具体产品：Windows文本
class WinText : public Text {
public:
    // 实现设置字体的方法
    void setFont(const std::string& s = "Consolas") override {
        std::cout << "Windows font now is " << s << '\n';
    }
    // 实现显示文本的方法
    void show() override {
        if (!text.empty()) {
            std::cout << "Windows:" << text << '\n';
        } else {
            std::cout << "there is no text.\n";
        }
    }
};

// 具体工厂：Windows工厂
class WinFactory : public GUIFactory {
public:
    // 实现创建按钮的方法
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WinButton>();
    }
    // 实现创建复选框的方法
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WinCheckBox>();
    }
    // 实现创建文本的方法
    std::unique_ptr<Text> createText() override {
        return std::make_unique<WinText>();
    }
};

// 具体产品：Mac按钮
class MacButton : public Button {
public:
    // 实现绘制按钮的方法
    void paint() override {
        std::cout << "mac button paint.\n";
    }
};

// 具体产品：Mac复选框
class MacCheckBox : public Checkbox {
public:
    // 实现设置复选框选中时颜色的方法
    void CheckedColor() override {
        std::cout << "MacOS Checkbox now is checked\n";
        std::cout << "MacOS Checkbox's color is red!\n";
    }
};

// 具体产品：Mac文本
class MacText : public Text {
public:
    // 实现设置字体的方法
    void setFont(const std::string& s = "MacFont") override {
        std::cout << "MacOS font now is " << s << '\n';
    }
    // 实现显示文本的方法
    void show() override {
        if (!text.empty()) {
            std::cout << "MacOS:" << text << '\n';
        } else {
            std::cout << "there is no text.\n";
        }
    }
};

// 具体工厂：Mac工厂
class MacFactory : public GUIFactory {
public:
    // 实现创建按钮的方法
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    // 实现创建复选框的方法
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckBox>();
    }
    // 实现创建文本的方法
    std::unique_ptr<Text> createText() override {
        return std::make_unique<MacText>();
    }
};

// 具体产品：Linux按钮
class LinuxButton : public Button {
public:
    // 实现绘制按钮的方法
    void paint() override {
        std::cout << "linux button paint.\n";
    }
};

// 具体产品：Linux复选框
class LinuxCheckBox : public Checkbox {
public:
    // 实现设置复选框选中时颜色的方法
    void CheckedColor() override {
        std::cout << "LinuxOS Checkbox now is checked\n";
        std::cout << "LinuxOS Checkbox's color is red!\n";
    }
};

// 具体产品：Linux文本
class LinuxText : public Text {
public:
    // 实现设置字体的方法
    void setFont(const std::string& s = "LinuxFont") override {
        std::cout << "LinuxOS font now is " << s << '\n';
    }
    // 实现显示文本的方法
    void show() override {
        if (!text.empty()) {
            std::cout << "LinuxOS:" << text << '\n';
        } else {
            std::cout << "there is no text.\n";
        }
    }
};

// 具体工厂：Linux工厂
class LinuxFactory : public GUIFactory {
public:
    // 实现创建按钮的方法
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<LinuxButton>();
    }
    // 实现创建复选框的方法
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<LinuxCheckBox>();
    }
    // 实现创建文本的方法
    std::unique_ptr<Text> createText() override {
        return std::make_unique<LinuxText>();
    }
};

// 客户端应用类
class Application {
public:
    // 构造函数，接收一个抽象工厂指针
    Application(std::unique_ptr<GUIFactory> gui) : guifactory_(std::move(gui)) {
        btn = guifactory_->createButton();
        chkbox = guifactory_->createCheckbox();
        text = guifactory_->createText();
    }
    // 创建用户界面
    void createUI() {
        if (chkbox->ifIsChecked()) {
            chkbox->CheckedColor();
        }
        text->show();
    }
    // 设置文本内容
    void setText(const std::string& s) {
        text->setText(s);
    }
    // 点击复选框
    void clickCheckbox() {
        chkbox->clickCheckbox();
    }
    // 绘制界面
    void paint() {
        btn->paint();
        createUI();
    }

private:
    std::unique_ptr<GUIFactory> guifactory_;
    std::unique_ptr<Button> btn;
    std::unique_ptr<Checkbox> chkbox;
    std::unique_ptr<Text> text;
};

int main() {
    {
        Application app1(std::make_unique<WinFactory>());
        app1.createUI();
        app1.clickCheckbox();
        app1.setText("Windows Text!!!");
        app1.paint();
    }

    std::cout << "----------------------------------\n";

    {
        Application app2(std::make_unique<MacFactory>());
        app2.createUI();
        app2.clickCheckbox();
        app2.setText("MacOS Text!!!");
        app2.paint();
    }

    std::cout << "----------------------------------\n";

    {
        Application app3(std::make_unique<LinuxFactory>());
        app3.createUI();
        app3.clickCheckbox();
        app3.setText("Linux Text!!!");
        app3.paint();
    }

    return 0;
}    