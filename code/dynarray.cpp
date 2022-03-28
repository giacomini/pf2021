#include <algorithm>
#include <cassert>
#include <iostream>

template <class T>
class DynamicArray
{
  int m_size;
  T* m_data;

 public:
  ~DynamicArray()
  {
    delete[] m_data;
  }
  DynamicArray(int size, int value = 0) : m_size(size), m_data(new T[m_size])
  {
    std::fill(m_data, m_data + m_size, value);
  }
  DynamicArray(DynamicArray const& other)
      : m_size(other.m_size), m_data(new T[m_size])
  {
    std::copy(other.m_data, other.m_data + m_size, m_data);
  }
  DynamicArray& operator=(DynamicArray const& other)
  {
    if (&other != this) {
      delete[] m_data;

      m_size = other.m_size;
      m_data = new T[m_size];
      std::copy(other.m_data, other.m_data + m_size, m_data);
    }
    return *this;
  }
  DynamicArray(DynamicArray&& other) noexcept
    : m_size(std::exchange(other.m_size, 0)), m_data(std::exchange(other.m_data, nullptr))
  {
  }
  DynamicArray& operator=(DynamicArray&& other) noexcept
  {
    m_size = std::exchange(other.m_size, 0);
    m_data = std::exchange(other.m_data, nullptr);
    return *this;
  }
  int size() const
  {
    return m_size;
  }

  using reference = T&;
  using const_reference = T const&;
  using iterator = T*;
  using const_iterator = T const*;

  reference operator[](int i)
  {
    assert(i >= 0 && i < m_size);
    return m_data[i];
  }
  const_reference operator[](int i) const
  {
    assert(i >= 0 && i < m_size);
    return m_data[i];
  }

  iterator begin()
  {
    return m_data;
  }
  const_iterator begin() const
  {
    return m_data;
  }
  iterator end()
  {
    return m_data + m_size;
  }
  const_iterator end() const
  {
    return m_data + m_size;
  }
};

template <class T>
inline auto operator==(DynamicArray<T> const& a, DynamicArray<T> const& b)
{
  return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template <class T>
inline auto operator!=(DynamicArray<T> const& a, DynamicArray<T> const& b)
{
  return !(a == b);
}

int main()
{
  std::cout << "Size of array: ";
  int n;
  std::cin >> n;
  assert(n > 0 && n < 32);
  DynamicArray<int> a(n);
  a[0] = 5;
  std::cout << a[0] << '\n';
  auto b{a};
  a = b;
  assert(a == b);
  std::cout << a[0] << '\n';
  a = a;
  std::cout << a[0] << '\n';

  auto c{std::move(a)};
  a = std::move(b);
  b = std::move(c);
  std::cout << b[0] << '\n';
  std::cout << a.size() << ' ' << b.size() << ' ' << c.size() << '\n';

  std::swap(b, b);
  std::cout << b[0] << '\n';
  std::cout << b.size() << '\n';
}
