#pragma once
#include <memory>
template<typename T>
class Singleton {
public:
	static T* instance() {//指针版
		if (_instance == nullptr) {//如果不存在，就新建一个
			_instance = new T();
		}
		return _instance;
	}
private:
	Singleton() {}//构造函数设为私有，无法调用
	Singleton(const Singleton<T>&);//不能复制，保证单例
	~Singleton() {}
private:
	static T* _instance;
};
//初始化
template<typename T>
T* Singleton<T>::_instance = nullptr;
