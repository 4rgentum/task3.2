#include <iostream>
#include "wagon.h"

namespace lab2SimpleClass {

  /** @brief Equality operator for comparing two wagon objects.
  *
  * @param other The other wagon to compare to.
  *
  * @return True if the wagons are equal, false otherwise.
  */
  bool Wagon::operator==(const Wagon& other) const {
    return (maxCapacity == other.maxCapacity && occupiedSeats == other.occupiedSeats && type == other.type);
  }
  
  /**
   * @brief Assignment operator overload for the Wagon class.
   *
   * This operator allows copying the data from another Wagon object.
   *
   * @param other The Wagon object to be copied.
   * @return A reference to the current Wagon object.
   */
  Wagon& Wagon::operator=(const Wagon& other) {
    if (this == &other) {
      return *this; // Check for self-assignment
    }

    maxCapacity = other.maxCapacity;
    occupiedSeats = other.occupiedSeats;
    type = other.type;

    return *this;
  }
  
  /**
   * @brief Default constructor for the Wagon class.
   *
   * This constructor initializes a Wagon object with default values:
   * - Maximum capacity is set to 0.
   * - Occupied seats are set to 0.
   * - The wagon type is set to RESTAURANT.
   */
  Wagon::Wagon() : maxCapacity(0), occupiedSeats(0), type(WagonType::RESTAURANT) {}

  /**
   * @brief Constructor with parameters for the Wagon class.
   *
   * This constructor allows you to create a Wagon object with specified parameters.
   *
   * @param maxCapacity The maximum capacity of the wagon.
   * @param occupiedSeats The number of occupied seats in the wagon.
   * @param type The type of the wagon (e.g., SITTING, ECONOMY, LUXURY, RESTAURANT).
   *
   * @throw std::invalid_argument if the type is set to RESTAURANT, as restaurant wagons cannot have capacity or occupied seats.
   */
  Wagon::Wagon(int maxCapacit, int occupiedSeat, WagonType type) : type(type) {
    if (type == WagonType::RESTAURANT) {
      occupiedSeats = 0;
      maxCapacity = 0;
    } else {
      if (occupiedSeat > maxCapacit || occupiedSeat < 0 || maxCapacit < 0) {
        throw std::invalid_argument("Occupied seats cannot exceed max capacity.");
      }
      occupiedSeats = occupiedSeat;
      maxCapacity = maxCapacit;
    }
  }

  /**
   * @brief Constructor with type initialization for the Wagon class.
   *
   * This constructor allows you to create a Wagon object with an initial type. The constructor
   * automatically sets the maximum capacity and occupied seats based on the specified type.
   *
   * @param type The type of the wagon (e.g., SITTING, ECONOMY, LUXURY, RESTAURANT).
   */
  Wagon::Wagon(WagonType type) : type(type) {
    // Automatically set capacity and occupied seats based on the type.
    switch (type) {
      case WagonType::SITTING:
        maxCapacity = 100; // Example value for a sitting wagon.
        occupiedSeats = 0; // Number of occupied seats is initially 0.
        break;
      case WagonType::ECONOMY:
        maxCapacity = 50; // Example value for an economy-class wagon.
        occupiedSeats = 0; // Number of occupied seats is initially 0.
        break;
      case WagonType::LUXURY:
        maxCapacity = 30; // Example value for a luxury wagon.
        occupiedSeats = 0; // Number of occupied seats is initially 0.
        break;
      case WagonType::RESTAURANT:
        maxCapacity = 0; // The capacity for a restaurant wagon is always 0.
        occupiedSeats = 0; // Number of occupied seats is initially 0.
        break;
    }
  }

  /**
   * @brief Get the occupancy percentage of the wagon.
   *
   * This method calculates the percentage of occupied seats in the wagon based on its maximum capacity.
   *
   * @return The occupancy percentage as a double value. If the wagon is a restaurant, the occupancy percentage is always 0%.
   */
  double Wagon::getOccupancyPercentage() const {
    if (maxCapacity == 0) {
      return 0.0; // If the wagon is a restaurant, occupancy is always 0%.
    }
    return static_cast<double>(occupiedSeats) / maxCapacity * 100.0;
  }

  /**
   * @brief Board a specified number of passengers into the wagon.
   *
   * This method allows you to board a certain number of passengers into the wagon, but only if the wagon is not a restaurant and has available capacity.
   *
   * @param passengers The number of passengers to board.
   *
   * @throw std::invalid_argument if the wagon is full and cannot board more passengers.
   */
  void Wagon::boardPassengers(int passengers) {
    if (passengers < 0) {
      throw std::invalid_argument("Cannot board negative number of passengers");
    }
    if (maxCapacity != 0) {
      if (occupiedSeats + passengers > maxCapacity) {
        throw std::invalid_argument("Wagon is full. Cannot board more passengers.");
      }
      occupiedSeats += passengers;
    } else {
      throw std::invalid_argument("Cannot board to Restaurant");
    }
  }

  /**
   * @brief Disembark passengers from the wagon.
   *
   * This method is used to disembark a specified number of passengers from the wagon.
   * It checks if there are enough passengers in the wagon to disembark and then updates the count of occupied seats accordingly.
   *
   * @param passengers The number of passengers to disembark.
   *
   * @throws std::invalid_argument If there are not enough passengers in the wagon to disembark.
   */
  void Wagon::disembarkPassengers(int passengers) {
    if (passengers < 0) {
      throw std::invalid_argument("Cannot disembark negative number of passengers");
    }
    if (maxCapacity != 0) {
      if (occupiedSeats - passengers < 0) {
        throw std::invalid_argument("There are not enough people in the Wagon to disembark.");
      }
      occupiedSeats -= passengers;
    } else {
      throw std::invalid_argument("Cannot disembark from Restaurant");
    }
  }

  /**
   * @brief Get the maximum capacity of the wagon.
   *
   * @return The maximum capacity of the wagon as an integer.
   */
  int Wagon::getMaxCapacity() const { return maxCapacity; }

  /**
   * @brief Get the number of occupied seats in the wagon.
   *
   * @return The number of occupied seats in the wagon as an integer.
   */
  int Wagon::getOccupiedSeats() const { return occupiedSeats; }

  /**
   * @brief Get the type of the wagon.
   *
   * @return The type of the wagon (e.g., SITTING, ECONOMY, LUXURY, RESTAURANT) as a WagonType enum.
   */
  WagonType Wagon::getType() const { return type; }

  /**
   * @brief Set the maximum capacity of the wagon.
   *
   * This method allows you to set the maximum capacity of the wagon, but it must not be negative and must not be less than the number of occupied seats.
   *
   * @param capacity The new maximum capacity for the wagon.
   *
   * @throw std::invalid_argument if the capacity is negative or less than the number of occupied seats.
   */
  void Wagon::setMaxCapacity(int capacity) {
    if (type == WagonType::RESTAURANT) {
      throw std::invalid_argument("Can't set maxcapacity in restaurant wagon");
    }
    if (capacity < 0 || occupiedSeats > capacity) {
      throw std::invalid_argument("Max capacity cannot be negative or cannot be less than occupied seats.");
    }
    maxCapacity = capacity;
  }

  /**
   * @brief Set the number of occupied seats in the wagon.
   *
   * This method allows you to set the number of occupied seats in the wagon, but it must not be negative and must not exceed the maximum capacity of the wagon.
   *
   * @param seats The new number of occupied seats.
   *
   * @throw std::invalid_argument if the number of occupied seats is negative or exceeds the maximum capacity.
   */
  void Wagon::setOccupiedSeats(int seats) {
    if (type == WagonType::RESTAURANT) {
      throw std::invalid_argument("Can't set occupied seats in restaurant wagon");
    }
    if (seats < 0 || seats > maxCapacity) {
      throw std::invalid_argument("Invalid number of occupied seats.");
    }
    occupiedSeats = seats; 
  }

  /**
   * @brief Set the type of the wagon.
   *
   * This method allows you to set the type of the wagon, but it cannot be set to RESTAURANT, as restaurant wagons cannot have passengers.
   *
   * @param wagonType The new type of the wagon.
   *
   * @throw std::invalid_argument if the type is set to RESTAURANT, as restaurant wagons cannot have passengers.
   */
  void Wagon::setType(WagonType wagonType) {
    if (wagonType == WagonType::SITTING) {
      occupiedSeats = 100;
      maxCapacity = this->getOccupiedSeats();
    }
    if (wagonType == WagonType::ECONOMY) {
      if (this->getOccupiedSeats() > 50) {
        throw std::invalid_argument("Cann't change type");
      }
      occupiedSeats = 50;
      maxCapacity = this->getOccupiedSeats();
    }
    if (wagonType == WagonType::LUXURY) {
      if (this->getOccupiedSeats() > 30) {
        throw std::invalid_argument("Cann't change type");
      }
      occupiedSeats = 30;
      maxCapacity = this->getOccupiedSeats();
    }
    if (wagonType == WagonType::RESTAURANT) {
      occupiedSeats = 0;
      maxCapacity = 0;
    }
    type = wagonType; 
  }
  
  /**
   * @brief Transfer passengers from the current wagon to another wagon.
   *
   * This method allows the transfer of passengers between two wagons with the same type. The number of passengers to transfer is determined based on the average occupancy percentage of both wagons.
   *
   * @param otherWagon The wagon to which passengers are transferred.
   *
   * @throw std::invalid_argument if either of the wagons is a restaurant wagon or if the wagon types do not match.
   */
  void Wagon::transferPassengers(Wagon &otherWagon) {
    if (type == WagonType::RESTAURANT || otherWagon.getType() == WagonType::RESTAURANT) {
      throw std::invalid_argument("Passengers cannot be transferred to or from a restaurant wagon.");
    }
    if (getType() != otherWagon.getType()) {
      throw std::invalid_argument("Incorrect type of wagons");
    } else {
      int totalOccupiedSeats = occupiedSeats + otherWagon.getOccupiedSeats();
      int totalMaxCapacity = maxCapacity + otherWagon.getMaxCapacity();

       // Calculate the average occupancy percentage
      double occupancyPercentageMid = static_cast<double>(totalOccupiedSeats) / totalMaxCapacity;
      
      // Calculate the number of passengers to transfer based on the occupancy percentage
      int passengersThis = static_cast<int>(occupancyPercentageMid * maxCapacity);
      int passengersOther = static_cast<int>(occupancyPercentageMid * otherWagon.maxCapacity);

      // Update the number of occupied seats in both wagons
      setOccupiedSeats(passengersThis);
      otherWagon.setOccupiedSeats(passengersOther);
    }
  }

 /**
 * @brief Overloaded operator for transferring passengers from one wagon to another.
 *
 * This operator allows the transfer of passengers from the current wagon to another wagon using the `>>` operator.
 * It is a shorthand for calling the `transferPassengers` method.
 *
 * @param other The wagon to which passengers are transferred.
 *
 * @return A reference to the current wagon after the passengers have been transferred.
 *
 * @throw std::invalid_argument if either of the wagons is a restaurant wagon or if the wagon types do not match.
 */
  Wagon &Wagon::operator >>(Wagon &other) {
    this->transferPassengers(other);
    return *this;
  }

  /**
  * @brief Overloaded operator for inputting a wagon from an input stream.
  *
  * This operator allows you to input the state of a wagon from an input stream using the `>>` operator.
  *
  * @param is The input stream from which the wagon data is read.
  * @param wagon The wagon object to store the input data.
  *
  * @return The input stream after reading the wagon data.
  *
  * @throw std::ios::failbit if the input data is invalid (e.g., negative values or inconsistent values).
  */
  std::istream& operator>>(std::istream& is, Wagon& wagon) {
    Wagon tempWagon;
    
    int typeInt;
    is >> typeInt;
  
    // Check for EOF
    if (!is.good()) {
      return is;
    }

    // Check for invalid input
    if (typeInt < 0 || typeInt > 3) {
      is.setstate(std::ios::failbit);
      return is;
    }

    int capacity, occupied;
    is >> capacity;

    // Check for EOF
    if (!is.good()) {
      return is;
    }

    is >> occupied;

    // Check for EOF
    if (!is.good()) {
      return is;
    }

    // Check for invalid input
    if (capacity < 0 || occupied < 0 || (capacity < occupied && capacity != 0)) {
      is.setstate(std::ios::failbit);
      return is;
    }
    
    // Get the wagon type, and set appropriate values for restaurant wagons
    tempWagon.type = static_cast<WagonType>(typeInt);
    
    if (tempWagon.type == WagonType::RESTAURANT) {
      tempWagon.maxCapacity = 0;
      tempWagon.occupiedSeats = 0;
    } else {
      tempWagon.maxCapacity = capacity;
      tempWagon.occupiedSeats = occupied;
    }

    wagon = std::move(tempWagon);
  
    return is;
  }

/**
 * @brief Overloaded operator for outputting a wagon to an output stream.
 *
 * This operator allows you to output the state of a wagon to an output stream using the `<<` operator.
 *
 * @param os The output stream to which the wagon data is written.
 * @param wagon The wagon object to be written to the output stream.
 *
 * @return The output stream after writing the wagon data.
 */
  std::ostream& operator<<(std::ostream& os, const Wagon& wagon) {
    // Output the data of the Wagon object to the output stream
    os << wagon.maxCapacity << std::endl;
    os << wagon.occupiedSeats << std::endl;
    switch (wagon.type) {
        case WagonType::SITTING:
            os << 0;
            break;
        case WagonType::ECONOMY:
            os << 1;
            break;
        case WagonType::LUXURY:
            os << 2;
            break;
        case WagonType::RESTAURANT:
            os << 3;
            break;
    }
    os << std::endl;
    return os;
  }
}
