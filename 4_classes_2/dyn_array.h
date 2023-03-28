#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <iostream>
#include <algorithm> // std::swap
#include <cstddef> // size_t
#include <initializer_list>

class DynArray {
private:
	size_t size_;
	size_t capacity_;
	double* arr_;
public:
	explicit DynArray(size_t cap = 0) : size_(0), capacity_(cap), arr_(new double[capacity_]) {}
	DynArray(std::initializer_list<double> lst) :
		size_(lst.size()), capacity_(lst.size()), arr_(new double[capacity_]) {
		auto it = lst.begin();
		for (size_t i = 0; i < capacity_; ++i) {
			arr_[i] = *it;
			++it;
		}
	}
	~DynArray() {
		delete[] arr_;
	}
	DynArray(DynArray const& rhs) : size_(rhs.size_), capacity_(rhs.capacity_), arr_(new double[capacity_]) {
		for (size_t i = 0; i < capacity_; ++i) {
			arr_[i] = rhs.arr_[i];
		}
	}
	void swap(DynArray& rhs) noexcept {
		std::swap(size_, rhs.size_);
		std::swap(capacity_, rhs.capacity_);
		std::swap(arr_, rhs.arr_);
	}
	DynArray& operator= (DynArray const& rhs) {
		if (this != &rhs) {
			DynArray(rhs).swap(*this);
		}
		return *this;
	}
	void reserve(size_t new_cap) {
		DynArray temp(new_cap);
		auto n = new_cap > size_ ? size_ : new_cap;
		for (size_t i = 0; i < n; ++i) {
			temp[i] = arr_[i];
		}
		temp.size_ = n;
		temp.swap(*this);
	}
	void append(double x) {
		if (size_ == capacity_) {
			reserve(size_ * 2);
		}
		arr_[size_] = x;
		++size_;
	}
	double get(size_t i) const {
		return arr_[i];
	}
	double operator[](size_t i) const {
		return arr_[i];
	}
	double& operator[](size_t i) {
		return arr_[i];
	}
	size_t size() const noexcept {
		return size_;
	}
	DynArray& operator+=(DynArray const& rhs) {
		reserve(size_ + rhs.size_);
		for (size_t i = 0; i < rhs.size(); ++i) {
			append(rhs[i]);
		}
		return *this;
	}
	DynArray& operator<<=(int k) noexcept {
		if (k < 0) {
			return operator>>=(-k);
		}
		size_t n = (size_t)k % size_;
		for (size_t i = 0; i < n; ++i) {
			for (size_t i = 0; i < size_ - 1; ++i) {
				std::swap(arr_[i], arr_[(i + 1) % size_]);
			}
		}
		return *this;
	}
	DynArray& operator>>=(int k) noexcept {
		if (k < 0) {
			return operator<<=(-k);
		}
		size_t n = (size_t)k % size_;
		for (size_t i = 0; i < n; ++i) {
			for (size_t i = size_ - 1; i >= 1; --i) {
				std::swap(arr_[i], arr_[i - 1]);
			}
		}
		return *this;
	}
};
DynArray operator+(DynArray lhs, DynArray const& rhs) {
	return lhs += rhs;
}
DynArray operator<<(DynArray lhs, int k) noexcept {
	return lhs <<= k;
}
DynArray operator>>(DynArray lhs, int k) noexcept {
	return lhs >>= k;
}
std::ostream& operator<<(std::ostream& os, DynArray const& rhs) noexcept {
	for (size_t i = 0; i < rhs.size(); ++i) {
		os << rhs[i] << " ";
	}
	return os;
}

#endif