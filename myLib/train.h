#ifndef TRAIN_H
#define TRAIN_H

#include "wagon.h"

using namespace lab2SimpleClass;

namespace lab2ComplexClass {

  /**
   * @brief The Train class represents a train with multiple wagons.
   *
   * This class manages a train with a variable number of wagons and provides various operations
   * for manipulating the train, including adding and removing wagons, redistributing passengers,
   * and optimizing the train's configuration.
   */
  class Train {
    private:
      int numWagons; // Текущее количество вагонов в поезде
      Wagon* wagons; // Массив вагонов
      int capacity;  // Емкость массива (количество доступных мест)

    public:

      /**
       * @brief Equality operator for comparing two Train objects.
       *
       * This operator checks if two Train objects are equal by comparing the number of wagons
       * and the types of wagons they contain. Two trains are considered equal if they have the same
       * number of wagons and each pair of corresponding wagons in the trains is equal.
       *
       * @param other The Train object to compare with.
       * @return True if the two trains are equal, false otherwise.
       *
       * @note Two trains are considered equal if they have the same number of wagons and each pair
       * of corresponding wagons in the trains is equal.
       */
      bool operator==(const Train& other) const;

      /**
       * @brief Default constructor for the Train class.
       */
      Train(); // Конструктор по умолчанию

      /**
       * @brief Constructor that initializes the train with an array of wagons.
       *
       * @param wagons An array of wagons.
       * @param numWagons The number of wagons in the array.
       */
      explicit Train(const Wagon wagons[], int numWagons); // Конструктор с инициализацией вагонов из массива

      /**
       * @brief Constructor that initializes the train with a single wagon.
       *
       * @param wagon The wagon to be added to the train.
       */
      explicit Train(const Wagon &wagon); // Конструктор с инициализацией одним вагоном

      /**
       * @brief Copy constructor for the Train class.
       *
       * @param other Another Train object to be copied.
       */
      Train(const Train& other); // Копирующий конструктор

      /**
       * @brief Move constructor for the Train class.
       *
       * @param other Another Train object to be moved.
       */
      Train(Train&& other); // Перемещающий конструктор

      // Геттеры
      /**
       * @brief Get the number of wagons in the train.
       *
       * @return The number of wagons in the train.
       */
      int getNumWagons() const; // Геттер для числа вагонов
  
      /**
       * @brief Get the array of wagons in the train.
       *
       * @return A pointer to the array of wagons.
       */
      const Wagon* getWagons() const; // Геттер для вагонов
  
      /**
       * @brief Get the capacity of the wagon array (number of available seats).
       *
       * @return The capacity of the wagon array.
       */
      int getCapacity() const; // Геттер для capacity

      // Сеттеры
      /**
       * @brief Set the number of wagons in the train.
       *
       * @param numWagons The new number of wagons.
       */
      void setNumWagons(int numWagons); // Сеттер для числа вагонов
  
      /**
       * @brief Set the array of wagons in the train.
       *
       * @param wagons An array of wagons.
       * @param numWagons The number of wagons in the array.
       */
      void setWagons(const Wagon* wagons, int numWagons); // Сеттер для вагонов
  
      /**
       * @brief Set the capacity of the wagon array (number of available seats).
       *
       * @param capacity The new capacity of the wagon array.
       */
      void setCapacity(int capacity); // Сеттер для capacity 

      /**
       * @brief Destructor for the Train class.
       */
      ~Train(); // Деструктор

      /**
       * @brief Add a wagon to the train.
       *
       * @param wagon The wagon to be added to the train.
       */
      void addWagon(const Wagon &wagon); // Метод добавления вагона в поезд

      /**
       * @brief Get a wagon from the train by its index.
       *
       * @param index The index of the wagon to be retrieved.
       * @return The wagon object.
       */
      const Wagon& getWagonByIndex(int index) const; // Метод получения вагона по его номеру (возврат по ссылке)

      /**
       * @brief Remove a wagon from the train by its index.
       *
       * @param index The index of the wagon to be removed.
       */
      void removeWagonByIndex(int index); //Удаление вагона с заданным номером из поезда

      /**
       * @brief Board a specified number of passengers to the most available wagon of the given class.
       *
       * This method boards passengers to the wagon with the highest available capacity of the specified class.
       *
       * @param passengers The number of passengers to board.
       * @param wagonType The class of wagon to target.
       */
      void boardPassengersToMostAvailableWagon(int passengers, WagonType wagonType); // Посадить пассажиров в наиболее свободный вагон

      /**
       * @brief Get the count of passengers in the train by wagon type and the maximum capacity for that type.
       *
       * This method calculates the number of occupied seats and the maximum capacity for wagons of a given class.
       *
       * @param wagonType The class of wagon for which to calculate the counts.
       * @param occupiedSeats The count of currently occupied seats for the specified class.
       * @param maxCapacity The maximum capacity for the specified class of wagons.
       */
      void getPassengerCountByType(lab2SimpleClass::WagonType wagonType, int& occupiedSeats, int& maxCapacity); // Счетчик пассажиров в однотипных вагонах

      /**
       * @brief Redistribute passengers between wagons to maximize occupancy balance.
       *
       * This method redistributes passengers among wagons to achieve a balanced occupancy percentage across all wagons.
       */
      void redistributePassengers(); // Сбалансировать пассажиров по вагонам

      /**
       * @brief Optimize the train by minimizing the number of wagons.
       *
       * This method reduces the number of wagons by transferring passengers between wagons and removing empty wagons from the vector.
       */
      void optimizeTrain(); // Оптимизировать поезд перераспределив пассажиров

      /**
       * @brief Add a new wagon to the train at the specified index.
       *
       * This method adds a new wagon to the train at the specified index in the vector of wagons.
       *
       * @param newWagon The new wagon to be added.
       * @param index The index at which to insert the new wagon.
       */
      void addWagonAtIndex(const Wagon& newWagon, int index); // Добавить вагон по индексу

      /**
       * @brief Optimize the placement of restaurant wagons in the train for balanced occupancy.
       *
       * This method optimizes the placement of restaurant wagons to achieve approximately equal passenger counts before and after each restaurant wagon.
       */
      void optimizeRestaurantPlacement();

      /**
       * @brief Overloaded operator for adding a wagon to the train.
       *
       * @param wagon The wagon to be added to the train.
       * @return A reference to the modified train.
       */
      Train& operator+=(const Wagon& wagon); // Добавление нового вагона в поезд

      /**
       * @brief Overloaded subscript operator for accessing wagons by index.
       *
       * @param index The index of the wagon to be accessed.
       * @return A reference to the wagon object.
       */
      Wagon& operator[](int index); // Получение вагона по его номеру (возврат по ссылке)
  
      /**
       * @brief Overloaded const subscript operator for accessing wagons by index.
       *
       * @param index The index of the wagon to be accessed.
       * @return A const reference to the wagon object.
       */
      const Wagon& operator[](int index) const;

      /**
       * @brief Overloaded assignment operator for copying another train.
       *
       * @param other Another Train object to be copied.
       * @return A reference to the modified train.
       */
      Train& operator=(const Train& other); // Перегрузка оператора "=" для копирования экземпляра класса

      /**
       * @brief Overloaded move assignment operator for moving another train.
       *
       * @param other Another Train object to be moved.
       * @return A reference to the modified train.
       */
      Train& operator=(Train&& other); // Перемещающий оператор присваивания

      /**
       * @brief Overloaded input operator for reading a Train object from an input stream.
       *
       * This operator allows you to read the state of a Train object from an input stream using the '>>' operator.
       *
       * @param is The input stream from which the train data is read.
       * @param train The Train object to store the read data.
       * @return The input stream after reading the train data.
       */
      friend std::istream& operator>>(std::istream& is, Train& train); // Перегрузка оператора >> для ввода экземпляра поезда

      /**
       * @brief Overloaded output operator for writing a Train object to an output stream.
       *
       * This operator allows you to write the state of a Train object to an output stream using the '<<' operator.
       *
       * @param os The output stream to which the train data is written.
       * @param train The Train object to be written to the output stream.
       * @return The output stream after writing the train data.
       */
      friend std::ostream& operator<<(std::ostream& os, const Train& train); // Перегрузка оператора "<<" для вывода поезда в выходной поток
  };

} // namespace lab2ComplexClass

#endif // TRAIN_H
