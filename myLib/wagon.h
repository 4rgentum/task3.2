#ifndef WAGON_H
#define WAGON_H

#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace lab2SimpleClass {
  
  /// @brief Enumeration for wagon types.
  enum class WagonType { SITTING, ECONOMY, LUXURY, RESTAURANT };

  /// @brief Class representing a train wagon.
  class Wagon {
  private:
    int maxCapacity;        ///< Maximum capacity of the wagon.
    int occupiedSeats;      ///< Number of currently occupied seats.
    WagonType type;         ///< Type of the wagon.

  public:

    /// @brief Equality operator for comparing two wagon objects.
    /// @param other The other wagon to compare to.
    /// @return True if the wagons are equal, false otherwise.
    bool operator==(const Wagon& other) const;

    /// @brief Assignment operator overload for the Wagon class. This operator allows copying the data from another Wagon object.
    /// @param other The Wagon object to be copied.
    /// @return A reference to the current Wagon object.
    Wagon& operator=(const Wagon& other);

    /// @brief Default constructor (implicit constructor).
    Wagon();

    /// @brief Constructor with parameters.
    /// @param maxCapacity Maximum capacity of the wagon.
    /// @param occupiedSeats Number of currently occupied seats.
    /// @param type Type of the wagon.
    Wagon(int maxCapacity, int occupiedSeats, WagonType type);

    /// @brief Constructor with initialization of only the type.
    /// @param type Type of the wagon.
    Wagon(WagonType type);

    /// @brief Get the percentage of occupancy of the wagon.
    /// @return The percentage of occupancy.
    double getOccupancyPercentage() const;

    /// @brief Board a specified number of passengers into the wagon.
    /// @param passengers Number of passengers to board.
    void boardPassengers(int passengers);

    /// @brief Disembark a specified number of passengers from the wagon.
    /// @param passengers Number of passengers to disembark.
    void disembarkPassengers(int passengers);

    /// @brief Get the maximum capacity of the wagon.
    /// @return Maximum capacity.
    int getMaxCapacity() const;

    /// @brief Get the number of currently occupied seats in the wagon.
    /// @return Number of occupied seats.
    int getOccupiedSeats() const;

    /// @brief Get the type of the wagon.
    /// @return Type of the wagon.
    WagonType getType() const;

    /// @brief Set the maximum capacity of the wagon.
    /// @param capacity Maximum capacity to set.
    void setMaxCapacity(int capacity);

    /// @brief Set the number of currently occupied seats in the wagon.
    /// @param seats Number of occupied seats to set.
    void setOccupiedSeats(int seats);

    /// @brief Set the type of the wagon.
    /// @param wagonType Type of the wagon to set.
    void setType(WagonType wagonType);

    /// @brief Transfer passengers from the current wagon to another wagon.
    /// @param otherWagon The target wagon for passenger transfer.
    void transferPassengers(Wagon &otherWagon);

    /// @brief Overloaded operator for transferring passengers from one wagon to another.
    /// @param other The target wagon for passenger transfer.
    /// @return Reference to the current wagon.
    Wagon &operator>>(Wagon &other);

    /// @brief Friend function to overload the input stream operator (>>).
    /// @param is Input stream.
    /// @param wagon Wagon object to read into.
    /// @return Reference to the input stream.
    friend std::istream& operator>>(std::istream& is, Wagon& wagon);

    /// @brief Friend function to overload the output stream operator (<<).
    /// @param os Output stream.
    /// @param wagon Wagon object to write.
    /// @return Reference to the output stream.
    friend std::ostream& operator<<(std::ostream& os, const Wagon& wagon);
  };

} // namespace lab2SimpleClass

#endif // WAGON_H
