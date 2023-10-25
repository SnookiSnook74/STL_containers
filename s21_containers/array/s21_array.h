/**
 * @brief Класс Array (массив) представляет собой последовательный контейнер,
 * инкапсулирующий в себе статический массив. В контейнере Array нельзя
 * добавлять новые элементы; можно только модифицировать значения элементов,
 * заданных изначально.
 *
 * Array сочетает в себе свойства статического массива с организацией данных,
 * характерной для контейнерных классов. Например, он хранит размер массива и
 * предоставляет итераторы для удобного доступа к элементам. Подобно вектору,
 * Array занимает последовательную область памяти и может быть передан в
 * функцию как обычный массив в Си. Вторым шаблонным аргументом класса Array
 * является его фактический размер.
 *
 * @tparam T Тип элементов, хранимых в массиве.
 * @tparam Size Фиксированный размер массива.
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_H_
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
namespace s21 {
template <typename T, long unsigned S>

/**
 * @brief Класс контейнера с фиксированным размером.
 *
 * Этот класс предоставляет контейнер с фиксированным размером с различными
 * методами для доступа, изменения и управления элементами.
 *
 * @tparam T Тип элементов, хранимых в массиве.
 * @tparam S Максимальное количество элементов в массиве.
 */

class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /**
   * @brief Конструктор по умолчанию, создает пустой массив.
   */
  array() {}

  /**
   * @brief Конструктор с инициализацией через список инициализации, создает
   * массив, инициализированный с использованием std::initializer_list.
   *
   * @param items Список инициализации элементов для инициализации массива.
   */
  explicit array(std::initializer_list<value_type> const &items) {
    if (items.size() > S) {
    }
    int i = 0;
    for (const_reference item : items) {
      data_[i] = item;
      ++i;
    }
  }

  /**
   * @brief Конструктор копирования.
   *
   * @param a Другой массив для копирования элементов.
   */
  array(const array &a) {
    if (a.size_ == size_) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i] = a.data_[i];
      }
    }
  }

  /**
   * @brief Конструктор перемещения.
   *
   * @param a Другой массив для перемещения элементов.
   */
  array(array &&a) {
    if (a.size_ == size_) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i] = std::move(a.data_[i]);
      }
    }
  }

  /**
   * @brief Деструктор.
   */
  ~array() {}

  /**
   * @brief Перегрузка оператора присваивания для перемещения объекта.
   *
   * @param a Другой массив для перемещения элементов.
   * @return Ссылка на измененный массив.
   */
  array &operator=(array &&a) {
    if (a.size_ == size_) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i] = std::move(a.data_[i]);
      }
    }
    return *this;
  }

  /**
   * @brief Доступ к указанному элементу с проверкой границ.
   *
   * Этот метод позволяет получить доступ к элементу в массиве по заданному
   * индексу с проверкой на выход за границы.
   *
   * @param pos Позиция элемента в массиве.
   * @return Ссылка на элемент по указанной позиции.
   * @throws std::out_of_range если `pos` превышает размер массива.
   */
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("array::at: __n (which is " +
                              std::to_string(pos) + ") >= _Nm (which is " +
                              std::to_string(this->size_) + ")");
    }
    return data_[pos];
  }

  /**
   * @brief Доступ к указанному элементу без проверки границ.
   *
   * Этот метод позволяет получить доступ к элементу в массиве по заданному
   * индексу без проверки на выход за границы.
   *
   * @param pos Позиция элемента в массиве.
   * @return Ссылка на элемент по указанной позиции.
   */
  reference operator[](size_type pos) { return data_[pos]; }

  /**
   * @brief Доступ к первому элементу массива.
   *
   * Этот метод позволяет получить доступ к первому элементу массива.
   *
   * @return Константная ссылка на первый элемент массива.
   */
  const_reference front() { return data_[0]; }

  /**
   * @brief Доступ к последнему элементу массива.
   *
   * Этот метод позволяет получить доступ к последнему элементу массива.
   *
   * @return Константная ссылка на последний элемент массива.
   */
  const_reference back() { return data_[size_ - 1]; }

  /**
   * @brief Получение указателя на внутренний массив данных.
   *
   * Этот метод возвращает указатель на внутренний массив данных контейнера.
   *
   * @return Указатель на внутренний массив данных.
   */
  iterator data() { return data_; }

  /**
   * @brief Получение итератора, указывающего на начало массива.
   *
   * Этот метод возвращает итератор, указывающий на начало массива.
   *
   * @return Итератор, указывающий на начало массива.
   */
  iterator begin() { return data_; }

  /**
   * @brief Получение итератора, указывающего на конец массива.
   *
   * Этот метод возвращает итератор, указывающий на конец массива.
   *
   * @return Итератор, указывающий на конец массива.
   */
  iterator end() { return data_ + size_; }

  /**
   * @brief Проверка, является ли массив пустым.
   *
   * Этот метод проверяет, является ли массив пустым (не содержит элементов).
   *
   * @return true, если массив пуст; в противном случае - false.
   */
  bool empty() {
    bool result = true;
    if (size_) {
      result = false;
    }
    return result;
  }

  /**
   * @brief Получение текущего размера массива.
   *
   * Этот метод возвращает текущий размер массива, то есть количество элементов
   * в нем.
   *
   * @return Размер массива.
   */
  size_type size() { return size_; }

  /**
   * @brief Получение максимально возможного размера массива.
   *
   * Этот метод возвращает максимально возможный размер массива, который
   * соответствует заданному максимальному количеству элементов.
   *
   * @return Максимально возможный размер массива.
   */
  size_type max_size() { return size_; }

  /**
   * @brief Обмен содержимого массива с другим массивом.
   *
   * Этот метод позволяет обменять содержимое текущего массива с содержимым
   * другого массива, при условии, что их размеры равны.
   *
   * @param other Другой массив, с которым будет выполнен обмен.
   */
  void swap(array &other) {
    if (other.size_ == size_) {
      std::swap(other.data_, data_);
    }
  }

  /**
   * @brief Заполнение массива заданным значением.
   *
   * Этот метод заполняет весь массив заданным значением.
   *
   * @param value Значение, которым будет заполнен весь массив.
   */
  void fill(const_reference value) { std::fill(data_, data_ + size_, value); }

 private:
  value_type data_[S];  // Основной массив для хранения элементов
  size_type size_ = S;  // Максимальное количество элементов в массиве.
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_H_