#include <iostream>

#define TASK_2

#ifdef TASK_1
class DynArray {
	double* arr_;
	int size_;
	int maxSize_;
public:
	DynArray(int n) {
		this->arr_ = new double[n];
		this->size_ = 0;
		this->maxSize_ = n;
	}
	~DynArray() {
		delete[] this->arr_;
	}
	void append(double x) {
		if (this->size_ < this->maxSize_) {
			this->arr_[this->size_++] = x;
			return;
		}
		auto arr = new double[this->maxSize_ * 2];
		for (int i = 0; i < this->maxSize_; ++i) {
			arr[i] = this->arr_[i];
		}
		delete[] this->arr_;
		this->arr_ = arr;
		this->maxSize_ *= 2;
		this->append(x);
	}
	double get(int i) {
		return this->arr_[i];
	}
	int size() {
		return this->size_;
	}
};
void solve() {
	DynArray arr(10);
	arr.append(1.0);
	for (size_t i = 0; i < 15; i++) {
		arr.append(i + 0.0);
	}
	for (size_t j = 0; j < arr.size(); j++) {
		std::cout << arr.get(j) << ' ';
	}
	std::cout << std::endl;
}
#endif

#ifdef TASK_2
class MyStack {
	int size_;
	int maxSize_;
	int* arr_;
public: 
	MyStack(int n) {
		this->arr_ = new int[n];
		this->size_ = 0;
		this->maxSize_ = n;
	}
	~MyStack() {
		delete[] this->arr_;
	}
	void append(int x) {
		if (this->size_ < this->maxSize_) {
			this->arr_[this->size_++] = x;
			return;
		}
		auto arr = new int[this->maxSize_ * 2];
		for (int i = 0; i < this->maxSize_; ++i) {
			arr[i] = this->arr_[i];
		}
		delete[] this->arr_;
		this->arr_ = arr;
		this->maxSize_ *= 2;
		this->append(x);
	}
	bool pop(int index = -1) {
		if ((index >= 0 && index >= this->size_) || (index < 0 && index > this->size_)) {
			return false;
		}
		index = (this->size_ + index) % this->size_;
		for (int i = index + 1; i < this->size_; ++i) {
			std::swap(this->arr_[i], this->arr_[i - 1]);
		}
		--this->size_;
		return true;
	}
	int get(int index) {
		return this->arr_[(this->size_ + index) % this->size_];
	}
	int find(int x) {
		for (int i = 0; i < this->size_; ++i) {
			if (this->arr_[i] == x) {
				return i;
			}
		}
		return -1;
	}
	void print() {
		for (int i = 0; i < this->size_; ++i) {
			std::cout << this->arr_[i] << " ";
		}
		std::cout << std::endl;
	}
	void clear() {
		this->size_ = 0;
	}
};
void solve() {
	MyStack arr(10);
	arr.append(1);
	for (int i = 0; i < 15; ++i) {
		arr.append(i);
	}
	arr.print();
	arr.pop();
	arr.print();
	int tests[3] = {0, 1, -2};
	for (auto i : tests) {
		arr.pop(i);
		arr.print();
	}
	std::cout << arr.find(3) << std::endl;
}
#endif

int main() {
	solve();
	return 0;
}