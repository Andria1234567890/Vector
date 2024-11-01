#include <iostream>
#include <stdexcept>

template <typename T> class Vector {
public:
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // constuctors

  Vector() : ptr_(nullptr), size_(0), capacity_(0) {}

  Vector(size_t n) {
    ptr_ = new T[n];
    size_ = n;
    capacity_ = n;
  }

  Vector(size_t n, const T &value) {
    ptr_ = new T[n];
    for (size_t i = 0; i < n; ++i) {
      ptr_[i] = value;
    }
    size_ = n;
    capacity_ = n;
  }

  Vector(const Vector &other) {
    ptr_ = new T[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (size_t i = 0; i < size_; ++i) {
      ptr_[i] = other.ptr_[i];
    }
  }

  Vector(Vector &&other) noexcept {
    ptr_ = other.ptr_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.ptr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector(std::initializer_list<T> list) {
    size_ = list.size();
    capacity_ = size_;
    ptr_ = new T[capacity_];
    int iter = 0;
    for (auto &it : list) {
      ptr_[iter] = it;
      ++iter;
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // operators

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      if (ptr_ != nullptr) {
        delete[] ptr_;
      }
      ptr_ = new T[other.capacity_];
      size_ = other.size_;
      capacity_ = other.capacity_;
      for (size_t i = 0; i < size_; ++i) {
        ptr_[i] = other.ptr_[i];
      }
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      if (ptr_ != nullptr) {
        delete[] ptr_;
      }
      ptr_ = other.ptr_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.ptr_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    return *this;
  }

  T &operator[](size_t ind) {
    if (ind + 1 > size_) {
      throw std::out_of_range("Invalid Index!!!");
    }
    return ptr_[ind];
  }

  const T &operator[](size_t ind) const {
    if (ind + 1 > size_) {
      throw std::out_of_range("Invalid Index!!!");
    }
    return ptr_[ind];
  }

  bool operator==(const Vector &other) const {
    for (int i = 0; i < size_; ++i) {
      if (ptr_[i] != other.ptr_[i]) {
        return false;
      }
    }
    return (size_ == other.size_);
  }

  bool operator!=(const Vector &other) const { return (!(*this == other)); }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  ~Vector() {
    if (ptr_ != nullptr) {
      delete[] ptr_;
    }
  }

  void Clear() { size_ = 0; }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // vector operations

  void PushBack(const T &value) {
    if (size_ == capacity_) {
      if (capacity_ == 0) {
        ResizeCap(1);
      } else {
        ResizeCap(capacity_ * 2);
      }
    }
    ptr_[size_++] = value;
  }

  void PopBack() {
    if (!Empty()) {
      --size_;
    } else {
      throw std::out_of_range("Vector is empty!!!");
    }
  }

  T &Front() {
    if (!Empty()) {
      return ptr_[0];
    } else {
      throw std::out_of_range("Vector is empty!!!");
    }
  }

  const T &Front() const {
    if (!Empty()) {
      return ptr_[0];
    } else {
      throw std::out_of_range("Vector is empty!!!");
    }
  }

  T &Back() {
    if (!Empty()) {
      return ptr_[size_ - 1];
    } else {
      throw std::out_of_range("Vector is empty!!!");
    }
  }

  const T &Back() const {
    if (!Empty()) {
      return ptr_[size_ - 1];
    } else {
      throw std::out_of_range("Vector is empty!!!");
    }
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // other functions

  void Resize(size_t n) {
    if (n > capacity_) {
      T *new_ptr = new T[n];
      for (size_t i = 0; i < size_; ++i) {
        new_ptr[i] = ptr_[i];
      }
      if (ptr_ != nullptr) {
        delete[] ptr_;
      }
      ptr_ = new_ptr;
      capacity_ = n;
    }
    size_ = n;
  }

  void ResizeCap(size_t n) {
    if (n > capacity_) {
      T *new_ptr = new T[n];
      for (size_t i = 0; i < size_; ++i) {
        new_ptr[i] = ptr_[i];
      }
      if (ptr_ != nullptr) {
        delete[] ptr_;
      }
      ptr_ = new_ptr;
      capacity_ = n;
    }
  }

  void Reverse() {
    for (size_t i = 0; i < size_ / 2; ++i) {
      std::swap(ptr_[i], ptr_[size_ - i - 1]);
    }
  }

  void Swap(Vector &other) {
    std::swap(ptr_, other.ptr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  bool Empty() { return (size_ == 0); }

  size_t GetSize() const { return size_; }

private:
  T *ptr_;
  size_t size_;
  size_t capacity_;
};