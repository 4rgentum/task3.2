#include <iostream>
#include "train.h"
#include <vector>

using namespace lab2SimpleClass;

namespace lab2ComplexClass {

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
  bool Train::operator==(const Train& other) const {
    if (numWagons != other.numWagons) {
      return false; 
    }

    for (int i = 0; i < numWagons; i++) {
      if (wagons[i] == other.wagons[i]) {
        return true; 
      } else {
        return false;
      }
    }

    return true; 
  }
  
  /**
   * @brief Default constructor for the Train class.
   *
   * This constructor initializes a Train object with default values, resulting in an empty train.
   */
  Train::Train() : numWagons(0), wagons(nullptr), capacity(0) {}

  /**
   * @brief Constructor for the Train class with initialization from an array of wagons.
   *
   * This constructor initializes a Train object with an array of wagons provided as an argument.
   *
   * @param wagons An array of Wagon objects to initialize the train with.
   * @param numWagons The number of wagons in the array.
   */
  Train::Train(const Wagon wagons[], int numWagons) : numWagons(numWagons), wagons(new Wagon[numWagons]), capacity(numWagons) {
    for (int i = 0; i < numWagons; ++i) {
      this->wagons[i] = wagons[i];
    }
  }

  /**
   * @brief Constructor for the Train class with initialization from a single wagon.
   *
   * This constructor initializes a Train object with a single wagon provided as an argument.
   *
   * @param wagon A single Wagon object to initialize the train with.
   */
  Train::Train(const Wagon& wagon) : numWagons(1), wagons(new Wagon[1]), capacity(1) {
      wagons[0] = wagon;
  }

  /**
   * @brief Copy constructor for the Train class.
   *
   * This constructor creates a new Train object as a copy of another Train object.
   *
   * @param other The Train object to be copied.
   */
  Train::Train(const Train& other) : numWagons(other.numWagons), wagons(new Wagon[other.capacity]), capacity(other.capacity) {
    for (int i = 0; i < numWagons; i++) {
        wagons[i] = other.wagons[i];
    }
  }

  /**
   * @brief Move constructor for the Train class.
   *
   * This constructor moves the content of another Train object to create a new Train object.
   *
   * @param other The Train object whose content is being moved.
   */
  Train::Train(Train&& other) : numWagons(other.numWagons), wagons(other.wagons), capacity(other.capacity) {
      other.numWagons = 0;
      other.wagons = nullptr;
      other.capacity = 0;
  }

  /**
   * @brief Get the number of wagons in the train.
   *
   * This method returns the current number of wagons in the train.
   *
   * @return The number of wagons in the train.
   */
  int Train::getNumWagons() const { return numWagons; }

  /**
   * @brief Get a pointer to the array of wagons in the train.
   *
   * This method returns a pointer to the array of wagons in the train. The wagons can be accessed using this pointer.
   *
   * @return A pointer to the array of wagons in the train.
   */
  const Wagon* Train::getWagons() const { return wagons; }

  /**
   * @brief Get the capacity of the train's wagon array.
   *
   * This method returns the capacity (the number of available slots) of the train's wagon array.
   *
   * @return The capacity of the train's wagon array.
   */
  int Train::getCapacity() const { return capacity; }

  /**
   * @brief Set the number of wagons in the train.
   *
   * This method sets the number of wagons in the train. It dynamically allocates memory for the wagons based on the new number.
   *
   * @param numWagons The new number of wagons for the train.
   *
   * @throws std::invalid_argument if numWagons is negative.
   */
  void Train::setNumWagons(int numWagon) {
    if (numWagon < getNumWagons()) {
      throw std::invalid_argument("Number of wagons cannot be less than previous numWagons.");
    }
    if (numWagon < 0) {
      throw std::invalid_argument("Number of wagons cannot be negative.");
    }

    if (numWagon != this->numWagons) {
      
      // Allocate new memory
      Wagon* newWagons = new Wagon[numWagon];

      // Copy data from the old array to the new one
      for (int i = 0; i < this->numWagons; i++) {
        newWagons[i] = wagons[i];
      }
      
      // Free the existing memory
      delete[] wagons;

      // Update the object's data
      this->numWagons = numWagon;
      this->capacity = numWagon;
      wagons = newWagons;
    }
  }

  /**
   * @brief Set the wagons for the train.
   *
   * This method sets the wagons for the train based on an array of wagons and the number of wagons.
   *
   * @param wagons An array of wagons to set for the train.
   * @param numWagons The number of wagons in the array.
   */
  void Train::setWagons(const Wagon* wagons, int numWagons) {
    if (numWagons < 0) {
      throw std::invalid_argument("Number of wagons cannot be negative.");
    }

    if (wagons == nullptr) {
      throw std::invalid_argument("Invalid input: wagons pointer is null.");
    }

    // Free the existing memory
    delete[] this->wagons;

    // Allocate new memory
    this->wagons = new Wagon[numWagons];
    this->numWagons = numWagons;

    // Copy data from the input array to the object's array
    for (int i = 0; i < numWagons; ++i) {
      this->wagons[i] = wagons[i];
    }
  }

  /**
   * @brief Set the capacity of the train's wagon array.
   *
   * This method sets the capacity (the number of available slots) of the train's wagon array. It dynamically allocates memory for the wagons based on the new capacity.
   *
   * @param capacity The new capacity for the train's wagon array.
   *
   * @throws std::invalid_argument if capacity is negative.
   */
  void Train::setCapacity(int capacity) {
    if (capacity < numWagons) {
      throw std::invalid_argument("Capacity cannot be less than numWagons in train.");
    }
    if (capacity < 0) {
      throw std::invalid_argument("Capacity cannot be negative.");
    }

    if (capacity != this->capacity) {
      
      // Allocate new memory
      Wagon* newWagons = new Wagon[capacity];

      // Copy data from the old array to the new one
      for (int i = 0; i < this->numWagons; i++) {
        newWagons[i] = wagons[i];
      }
      
      // Free the existing memory
      delete[] wagons;

      // Update the object's data
      this->capacity = capacity;
      wagons = newWagons;
    }
  }
  
  /**
   * @brief Destructor for the Train class.
   *
   * This destructor is responsible for releasing the memory used by the train's wagon array when the Train object is destroyed.
   */
  Train::~Train() {
      delete[] wagons; // Release memory when the object is destroyed
  }

  /**
   * @brief Add a wagon to the train.
   *
   * This method adds a new wagon to the train. If the capacity of the train's wagon array is exceeded,
   * it dynamically increases the capacity by doubling it and reallocates memory to accommodate the new wagon.
   *
   * @param wagon The wagon to be added to the train.
   */
  void Train::addWagon(const Wagon &wagon) {
    
    // Check if there is enough space in the array for the new wagon
    if (numWagons >= capacity) {
      // If not, increase the capacity of the array
      int newCapacity = (capacity == 0) ? 1 : capacity * 2; // Удвоение емкости
      // Create a new array with the increased capacity
      Wagon* newWagons = new Wagon[newCapacity];

      // Copy existing wagons into the new array
      for (int i = 0; i < numWagons; i++) {
        newWagons[i] = wagons[i];
      }

      // Delete the old wagon array
      delete[] wagons;

      // Update the pointer to the new array and its capacity
      wagons = newWagons;
      capacity = newCapacity;
    }
    
    // Add the new wagon to the end of the array
    wagons[numWagons] = wagon;
    numWagons++;
  }

  /**
   * @brief Get a wagon from the train by its index.
   *
   * This method retrieves a wagon from the train by its index and returns it by reference.
   *
   * @param index The index of the wagon to retrieve (0-based).
   * @return A reference to the wagon at the specified index.
   * @throws std::out_of_range if the index is invalid (less than 0 or greater than or equal to the number of wagons).
   */
  const Wagon& Train::getWagonByIndex(int index) const {
    if (index < 0 || index >= numWagons) {
      throw std::out_of_range("Invalid wagon index.");
    }
    return wagons[index];
  }

  /**
   * @brief Remove a wagon from the train by its index.
   *
   * This method removes a wagon from the train by its index and shifts the wagons with higher indices to the left.
   *
   * @param index The index of the wagon to remove (0-based).
   * @throws std::out_of_range if the index is invalid (less than 0 or greater than or equal to the number of wagons).
   */
  void Train::removeWagonByIndex(int index) {
    if (index < 0 || index >= numWagons) {
      throw std::out_of_range("Invalid wagon index.");
    }

    // Shift wagons with higher indices to the left
    for (int i = index; i < numWagons - 1; i++) {
      wagons[i] = wagons[i + 1];
    }

    numWagons--; // Decrease the number of wagons
  }

  /**
   * @brief Board a specified number of passengers into the most available wagon of a given class.
   *
   * This method boards the specified number of passengers into the most available wagon of the specified class.
   *
   * @param passengers The number of passengers to board.
   * @param wagonType The class of wagon to board passengers into.
   * @throws std::invalid_argument if an error occurs while boarding passengers.
   * @throws std::runtime_error if there are no available wagons of the specified class that can accommodate the passengers.
   */
  void Train::boardPassengersToMostAvailableWagon(int passengers, WagonType wagonType) {

    int availableWagonsCount = 0;
    std::vector<int> availableWagonsIndices;
    std::vector<int> availableWagonsOccupancy;

    // Find all wagons of the specified class that can accommodate the specified number of passengers
    for (int i = 0; i < numWagons; ++i) {
      if (wagons[i].getType() == wagonType && wagons[i].getMaxCapacity() - wagons[i].getOccupiedSeats() >= passengers) {
        availableWagonsIndices.push_back(i);
        availableWagonsOccupancy.push_back(wagons[i].getOccupiedSeats());
        ++availableWagonsCount;
      }
    }

    if (availableWagonsCount == 0) {
      throw std::invalid_argument("No available wagons of the specified type can accommodate the specified number of passengers.");
    }

    int mostAvailableIndex = availableWagonsIndices[0];
    int mostAvailableSeats = availableWagonsOccupancy[0];

    // Find the most available wagon among the available options
    for (int i = 1; i < availableWagonsCount; ++i) {
      if (availableWagonsOccupancy[i] > mostAvailableSeats) {
        mostAvailableIndex = availableWagonsIndices[i];
        mostAvailableSeats = availableWagonsOccupancy[i];
      }
    }

    // Board passengers into the most available wagon of the specified class
    wagons[mostAvailableIndex].boardPassengers(passengers);
  }

  /**
   * @brief Get the number of passengers and maximum capacity in wagons of a specified class.
   *
   * This auxiliary method calculates the total number of passengers and maximum capacity in the wagons
   * of the specified class in the train.
   *
   * @param wagonType The class of wagons to consider.
   * @param occupiedSeats Output parameter to store the total number of occupied seats in wagons of the specified class.
   * @param maxCapacity Output parameter to store the total maximum capacity of wagons of the specified class.
   */
  void Train::getPassengerCountByType(lab2SimpleClass::WagonType wagonType, int& occupiedSeats, int& maxCapacity) {
    occupiedSeats = 0;
    maxCapacity = 0;

    for (int i = 0; i < numWagons; i++) {
      if (wagons[i].getType() == wagonType) {
        occupiedSeats += wagons[i].getOccupiedSeats();
        maxCapacity += wagons[i].getMaxCapacity();
      }
    }
  }

  /**
   * @brief Redistribute passengers among wagons to maximize occupancy balance.
   *
   * This method redistributes passengers among wagons of different classes (economy, sitting, luxury)
   * to achieve a balanced occupancy percentage among all wagons. It calculates the average occupancy
   * percentages for each class of wagons and adjusts the number of passengers in each wagon accordingly.
   */
  void Train::redistributePassengers() {
    int occupiedSeatsByEconomy,  occupiedSeatsBySitting, occupiedSeatsByLuxury, maxCapacityByEconomy, maxCapacityBySitting, maxCapacityByLuxury;

    // Determine the number of occupied seats and total capacity for each wagon class
    getPassengerCountByType(WagonType::SITTING, occupiedSeatsBySitting, maxCapacityBySitting);
    getPassengerCountByType(WagonType::ECONOMY, occupiedSeatsByEconomy, maxCapacityByEconomy);
    getPassengerCountByType(WagonType::LUXURY, occupiedSeatsByLuxury, maxCapacityByLuxury);

    // Calculate the average occupancy percentage for each wagon class
    double occupancyPercentageMidSitting = static_cast<double>(occupiedSeatsBySitting) / maxCapacityBySitting;
    double occupancyPercentageMidEconomy = static_cast<double>(occupiedSeatsByEconomy) / maxCapacityByEconomy;
    double occupancyPercentageMidLuxury = static_cast<double>(occupiedSeatsByLuxury) / maxCapacityByLuxury;

    // Set the number of passengers in each wagon to achieve the calculated occupancy percentages
    for (int i = 0; i < numWagons; i++) {
      if (wagons[i].getType() == WagonType::SITTING) {
        wagons[i].setOccupiedSeats(static_cast<int>(wagons[i].getMaxCapacity() * occupancyPercentageMidSitting));
      } else if (wagons[i].getType() == WagonType::ECONOMY) {
        wagons[i].setOccupiedSeats(static_cast<int>(wagons[i].getMaxCapacity() * occupancyPercentageMidEconomy));
      } else if (wagons[i].getType() == lab2SimpleClass::WagonType::LUXURY) {
        wagons[i].setOccupiedSeats(static_cast<int>(wagons[i].getMaxCapacity() * occupancyPercentageMidLuxury));
      }
    }
  }

  /**
   * @brief Optimize the train by minimizing the number of wagons and redistributing passengers.
   *
   * This method minimizes the number of wagons by redistributing passengers among them and removing
   * wagons with no passengers. It ensures that each wagon type (economy, sitting, luxury) has as many
   * passengers as possible, reducing the number of empty or underutilized wagons.
   */
  void Train::optimizeTrain() {
    int occupiedSeatsByEconomy,  occupiedSeatsBySitting, occupiedSeatsByLuxury, maxCapacityByEconomy, maxCapacityBySitting, maxCapacityByLuxury;

    // Determine the number of occupied seats and total capacity for each wagon class
    getPassengerCountByType(WagonType::SITTING, occupiedSeatsBySitting, maxCapacityBySitting);
    getPassengerCountByType(WagonType::ECONOMY, occupiedSeatsByEconomy, maxCapacityByEconomy);
    getPassengerCountByType(WagonType::LUXURY, occupiedSeatsByLuxury, maxCapacityByLuxury);

    
    
    for (int i = 0; i < numWagons; i++) {

      if (wagons[i].getType() == WagonType::SITTING) {
        if (occupiedSeatsBySitting > wagons[i].getMaxCapacity()) {
          wagons[i].setOccupiedSeats(wagons[i].getMaxCapacity());
          occupiedSeatsBySitting -= wagons[i].getMaxCapacity();
        } else {
          wagons[i].setOccupiedSeats(occupiedSeatsBySitting);
          occupiedSeatsBySitting = 0;
        }
      }

      if (wagons[i].getType() == WagonType::ECONOMY) {
        if (occupiedSeatsByEconomy > wagons[i].getMaxCapacity()) {
          wagons[i].setOccupiedSeats(wagons[i].getMaxCapacity());
          occupiedSeatsByEconomy -= wagons[i].getMaxCapacity();
        } else {
          wagons[i].setOccupiedSeats(occupiedSeatsByEconomy);
          occupiedSeatsByEconomy = 0;
        }
      }

      if (wagons[i].getType() == WagonType::LUXURY) {
        if (occupiedSeatsByLuxury > wagons[i].getMaxCapacity()) {
          wagons[i].setOccupiedSeats(wagons[i].getMaxCapacity());
          occupiedSeatsByLuxury -= wagons[i].getMaxCapacity();
        } else {
          wagons[i].setOccupiedSeats(occupiedSeatsByLuxury);
          occupiedSeatsByLuxury = 0;
        }
      }

    }

    for (int j = 0; j < numWagons; j++) {
      if (wagons[j].getOccupiedSeats() == 0) {
        removeWagonByIndex(j);
        j--;
      }
    }
  }
  
  /**
   * @brief Add a new wagon at the specified index.
   *
   * This method adds a new wagon to the train at the specified index. The method increases the capacity
   * of the train and shifts existing wagons to accommodate the new wagon at the given position.
   *
   * @param newWagon The new wagon to add.
   * @param index The index at which to insert the new wagon.
   *
   * @throw std::invalid_argument if the index is out of bounds.
   */
  void Train::addWagonAtIndex(const Wagon& newWagon, int index) {
    if (index < 0 || index > numWagons) {
      throw std::invalid_argument("Invalid index for adding a wagon.");
    }

    // Calculate the new array size
    int newCapacity = capacity + 1;
    int newnumWagons = numWagons + 1;

    // Create a new array of wagons with increased capacity
    Wagon* newWagons = new Wagon[newCapacity];

    // Copy existing wagons to the new array before the specified index
    for (int i = 0; i < index; i++) {
      newWagons[i] = wagons[i];
    }

    // Copy the remaining wagons after the specified index
    for (int i = index + 1; i < newCapacity; i++) {
      newWagons[i] = wagons[i - 1];
    }

    newWagons[index] = newWagon;

    // Delete the old array of wagons
    delete[] wagons;

    // Update the pointer to the new array and its capacity
    wagons = newWagons;
    capacity = newCapacity;
    numWagons = newnumWagons;
  }

  /**
   * @brief Optimize the placement of a restaurant wagon for even distribution of passengers.
   *
   * This method optimizes the placement of a restaurant wagon within the train to achieve an approximately even
   * distribution of passengers before and after the restaurant wagon. It calculates the position where the restaurant
   * wagon should be inserted, taking into account the number of passengers in different wagon types. The restaurant wagon
   * is then added to the train at the optimal position.
   */
  void Train::optimizeRestaurantPlacement() {
    int totalPassengers = 0;
    for (int i = 0; i < numWagons; i++) {
      if (wagons[i].getType() != WagonType::LUXURY) {
        totalPassengers += wagons[i].getOccupiedSeats();
      }
    }

    int midPassengers = totalPassengers / 2;

    int needPosition = 0;
    for (int j = 0; j < numWagons; j++) {
      if (wagons[j].getType() != WagonType::LUXURY) {
        totalPassengers -= wagons[j].getOccupiedSeats();
        if (totalPassengers != midPassengers) {
            j++;
            needPosition = j;
            break;
        } else {
            needPosition = j;
	    break;
        }
      }
    }

    // Insert the restaurant wagon at the optimal position
    Wagon restaurantWagon;
    addWagonAtIndex(restaurantWagon, needPosition);
  }

  /**
   * @brief Add a new wagon to the train using the '+=' operator.
   *
   * This operator allows you to add a new wagon to the train by using the '+=' operator. The provided wagon is added to
   * the train's collection of wagon.
   *
   * @param wagon The wagon to be added to the train.
   * @return A reference to the modified train after adding the wagon.
   */
  Train& Train::operator+=(const Wagon& wagon) {
    addWagon(wagon);
    return *this;
  }

  /**
   * @brief Access a wagon by its index using the '[]' operator.
   *
   * This operator allows you to access a wagon within the train's collection of wagons using an index.
   *
   * @param index The index of the wagon to be accessed.
   * @return A reference to the wagon at the specified index.
   * @throws std::invalid_argument if the provided index is out of bounds.
   */
  Wagon& Train::operator[](int index) {
    if (index < 0 || index >= numWagons) {
      throw std::invalid_argument("Invalid wagon index.");
    }

    return wagons[index];
  }

  /**
   * @brief Access a wagon by its index using the '[]' operator (const version).
   *
   * This operator allows you to access a wagon within the train's collection of wagons using an index, and it is a const version that ensures the train remains unmodified.
   *
   * @param index The index of the wagon to be accessed.
   * @return A constant reference to the wagon at the specified index.
   * @throws std::out_of_range if the provided index is out of bounds.
   */
  const Wagon& Train::operator[](int index) const {
    if (index < 0 || index >= numWagons) {
      throw std::out_of_range("Index out of range");
    }
    return wagons[index];
  }

  /**
   * @brief Copy assignment operator.
   *
   * This operator overloads the assignment operator to allow you to make a deep copy of another train object.
   * It checks for self-assignment to prevent unnecessary work.
   *
   * @param other The train object to be copied.
   * @return A reference to the modified train object.
   */
  Train& Train::operator=(const Train& other) {
    if (this == &other) {
      return *this; // Check for self-assignment
    }

    numWagons = other.numWagons;
    wagons = new Wagon[numWagons];
    capacity = other.capacity;

    for (int i = 0; i < numWagons; ++i) {
      wagons[i] = other.wagons[i];
    }

    return *this;
  }

  /**
   * @brief Move assignment operator.
   *
   * This operator overloads the move assignment operator, allowing you to efficiently transfer the resources
   * (e.g., wagons) from one train object to another. It checks for self-assignment to avoid issues and releases
   * the resources of the current object before moving the resources from the other object.
   *
   * @param other The train object to move resources from.
   * @return A reference to the modified train object.
   */
  Train& Train::operator=(Train&& other) {
    if (this == &other) {
      return *this; // Check for self-assignment
    }

    // Release resources of the current object
    delete[] wagons;

    // Move resources from 'other' to 'this'
    numWagons = other.numWagons;
    wagons = other.wagons;
    capacity = other.capacity;

    // Reset 'other' to a valid but empty state
    other.numWagons = 0;
    other.wagons = nullptr;
    other.capacity = 0;

    return *this;
  }
    
  /**
   * @brief Overload of the input stream operator (>>) to input a train instance.
   *
   * This operator allows you to input a `Train` object from an input stream, which consists of an integer
   * representing the number of wagons in the train followed by the details of each wagon. It validates the
   * input to ensure it's well-formed and constructs a new `Train` object based on the input data.
   *
   * @param is The input stream to read the train data from.
   * @param train The `Train` object to populate with the input data.
   * @return A reference to the input stream after reading the train data.
   */
  std::istream& operator>>(std::istream& is, Train& train) {
    int numWagons;
    is >> numWagons;

    // Check for EOF
    if (!is.good()) {
        return is;
    }

    // Check for invalid input
    if (numWagons < 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    Train tempTrain;

    tempTrain.wagons = new Wagon[numWagons];
    tempTrain.capacity = numWagons;
    tempTrain.numWagons = numWagons;

    for (int i = 0; i < numWagons; i++) {
      is >> tempTrain.wagons[i];
      if (!is.good()) {
        return is;
      }
    }

    train  = std::move(tempTrain);

    return is;
  }

  /**
   * @brief Overload of the output stream operator (<<) to output the train to an output stream.
   *
   * This operator allows you to output a `Train` object to an output stream. It prints the number of wagons in the
   * train and the details of each wagon. This makes it easy to display the entire state of the train in a formatted way.
   *
   * @param os The output stream to which the train should be written.
   * @param train The `Train` object to be written to the output stream.
   * @return A reference to the output stream after writing the train data.
   */
  std::ostream& operator<<(std::ostream& os, const Train& train) {
    os << train.numWagons << std::endl;
    for (int i = 0; i < train.numWagons; i++) {
        os << train.wagons[i];
    }
    return os;
  }

}
