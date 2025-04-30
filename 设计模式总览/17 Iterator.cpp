#include <iostream>
#include <vector>
/**
 * 迭代器模式
 * 迭代器模式是一种行为设计模式，让你能在不暴露复杂数据结构内部细节的情况下遍历其中所有的元素。
 * 迭代器模式与组合模式一样，能用于遍历递归结构。
 * 迭代器模式包含以下几个角色：
 * 1. 迭代器接口：定义了访问和遍历元素的接口。
 * 2. 具体迭代器：实现了迭代器接口，用于遍历集合中的元素。
 * 3. 集合接口：定义了创建迭代器的接口。
 * 4. 具体集合：实现了集合接口，用于存储元素。
 */

template <typename T, typename U>
class Iterator {
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void First() {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void Next() {
        m_it_++;
    }

    bool IsDone() {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    iter_type Current() {
        return m_it_;
    }
private:
    U* m_p_data_;
    iter_type m_it_;
    bool m_reverse_;
};
// 容器类，用于存储元素
template <class T>
class Container {
    friend class Iterator<T, Container>;
public:
    void Add(T a) {
        m_data_.push_back(a);
    }
    // 创建迭代器
    Iterator<T, Container>* CreateIterator() {
        return new Iterator<T, Container>(this);
    } 
private:
    std::vector<T> m_data_;
};

class Data {
public:
    Data(int data) : m_data_(data) {}

    void set_data(int data) {
        m_data_ = data; 
    }
    int get_data() {
        return m_data_; 
    }
private:
    int m_data_;
};

void ClientCode() {
    std::cout << "________________Iterator with int______________________________________" << std::endl;
    Container<int> cont;
    for (int i = 0; i < 10; i++) {
        cont.Add(i);
    }
    // 存储int类型的容器的迭代器
    Iterator<int, Container<int>>* it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next()) {
        std::cout << *it->Current() << std::endl;
    }
    std::cout << "________________Iterator with Data______________________________________" << std::endl;
    Container<Data> cont2;
    for (int i = 0; i < 10; i++) {
        Data data(i);
        cont2.Add(data);
    }
    // 存储Data类型的容器的迭代器
    Iterator<Data, Container<Data>>* it2 = cont2.CreateIterator();
    for (it2->First();!it2->IsDone(); it2->Next()) {
        std::cout << it2->Current()->get_data() << std::endl;
    }
    delete it;
    delete it2;
}

int main() {
    ClientCode();
    return 0; 
}
