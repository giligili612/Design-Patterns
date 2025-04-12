#ifndef CHECKBOX_H
#define CHECKBOX_H

class Checkbox{
public:
    bool ifIsChecked(){
        return isChecked;
    }
    void clickCheckbox(){
        isChecked = !isChecked;
    }
    //不同系统勾选checkbox时显示的颜色不同
    virtual void CheckedColor() = 0;
    virtual ~Checkbox() = default;
    
protected:
    bool isChecked = false;
};

#endif