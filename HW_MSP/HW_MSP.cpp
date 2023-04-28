
#include <iostream>

template <typename T>
class MyUniquePtr
{
private:
	T* pointer;
public:
	MyUniquePtr()
	{
		pointer = nullptr;
	}
	MyUniquePtr(T &obj)
	{
		pointer = &obj;
	}
	MyUniquePtr(T* obj)
	{
		pointer = obj;
	}

	void reset()
	{
		if (pointer)
		{
			delete[] pointer;
		}
	}
	void reset(T &obj)
	{
		if (pointer)
		{
			delete[] pointer;
		}
		pointer = &obj;
	}

	T* getPtr()
	{
		return pointer;
	}

	MyUniquePtr operator=(MyUniquePtr &obj)
	{
		if (this->pointer)
		{
			delete[] this->pointer;
		}
		this->pointer = obj.pointer;
		obj.pointer = nullptr;
		return *this;
	}
	MyUniquePtr operator=(T &obj)
	{
		if (this->pointer)
		{
			delete[] this->pointer;
		}
		pointer = &obj;
	}
	MyUniquePtr operator=(T* obj)
	{
		if (this->pointer)
		{
			delete[] this->pointer;
		}
		pointer = obj;
	}

	~MyUniquePtr()
	{
		if (pointer != nullptr)
		{
			delete[] pointer;
		}
	}
};

class Control
{
private:
	int count;
public:
	Control()
	{
		count = 1;
	}

	int get()
	{
		return count;
	}
	void inc()
	{
		count++;
	}
	void dec()
	{
		count--;
	}
};
template <typename T>
class MySharedPtr
{
private:
	T* pointer;
	Control* control;
public:
	MySharedPtr()
	{
		pointer = nullptr;
		control = new Control;
	}
	MySharedPtr(T& obj)
	{
		pointer = &obj;
		control = new Control;
	}
	MySharedPtr(T* obj)
	{
		pointer = obj;
		control = new Control;
	}
	MySharedPtr(MySharedPtr& obj)
	{
		this->pointer = obj.pointer;
		this->control = obj.control;
		this->control->inc();
	}
	MySharedPtr(MyUniquePtr<T>& obj)
	{
		this->pointer = obj.getPtr();
		this->control = new Control;
	}

	T* getPtr()
	{
		return pointer;
	}
	void reset()
	{
		if (this->control->get() == 1)
		{
			delete[] this->pointer;
			delete[] this->control;
		}
	}

	MySharedPtr operator=(MySharedPtr& obj)
	{
		if (this->control->get() == 1)
		{
			delete[] control;
			delete[] pointer;
		}
		else
		{
			this->control->dec();
		}
		this->pointer = obj.pointer;
		this->control = obj.control;
		this->control->inc();
	}

	~MySharedPtr()
	{
		std::cout << "Destroying\n";
		if (this->control->get() == 1)
		{
			if (this->pointer != nullptr)
			{
				delete[] pointer;
			}
			delete[] this->control;
		}
		else
		{
			this->control->dec();
		}
	}
};

int main()
{
	//MyUniquePtr<int> test(new int);
	//(*test.getPtr()) = 5;
	//std::cout << (*test.getPtr());
	//MySharedPtr<int> test(new int);
	//(*test.getPtr()) = 8;
	//MySharedPtr<int> help = test;
	//std::cout << (*help.getPtr()) << '\n';
	//std::cout << (*test.getPtr()) << '\n';
}