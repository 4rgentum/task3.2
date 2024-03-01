#ifndef GETNUM_H
#define GETNUM_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>


/**
 * @brief Template function for reading a numeric input within a specified range.
 *
 * This function reads a numeric input (of type T) from the standard input stream (std::cin) and validates it against the specified range.
 *
 * @param min The minimum valid value for the input (default is the minimum value for the data type).
 * @param max The maximum valid value for the input (default is the maximum value for the data type).
 * @return The valid input value within the specified range.
 * @throws std::runtime_error if EOF is encountered or an unrecoverable input error occurs.
 */
template <class T>
T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
  T a;
  while (true) {
    std::cin >> a;
    if (std::cin.eof()) { // обнаружен конец файла
      throw std::runtime_error("Failed to read number: EOF");
    } else if (std::cin.bad()) { // обнаружена невосстановимая ошибка входного
                                 // потока
      throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
    } else if (std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
      std::cin.clear(); // очищаем флаги состояния потока
      // игнорируем все символы до конца строки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "You are wrong; repeat please!" << std::endl;
    } else if (a >= min && a <= max) { // если число входит в заданный диапазон
      return a;
    } else {
      std::cerr << "Number out of range. Please enter a valid number." << std::endl;
    }
  }
}

#endif // GETNUM_H
