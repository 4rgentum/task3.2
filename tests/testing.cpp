#define CATCH_CONFIG_MAIN
#include "../myLib/getnum.h"
#include "../myLib/train.h"
#include "../myLib/wagon.h"
#include <catch2/catch.hpp>
#include <sstream>

using namespace lab2ComplexClass;
using namespace lab2SimpleClass;

TEST_CASE("Default constructor initializes values correctly") {
  Wagon wagon;
  REQUIRE(wagon.getMaxCapacity() == 0);
  REQUIRE(wagon.getOccupiedSeats() == 0);
  REQUIRE(wagon.getType() == WagonType::RESTAURANT);
}

TEST_CASE("Parameterized constructor initializes values correctly") {
  Wagon wagon(100, 50, WagonType::SITTING);
  REQUIRE(wagon.getMaxCapacity() == 100);
  REQUIRE(wagon.getOccupiedSeats() == 50);
  REQUIRE(wagon.getType() == WagonType::SITTING);
  Wagon wagoh(100, 50, WagonType::RESTAURANT);
  REQUIRE(wagoh.getMaxCapacity() == 0);
  REQUIRE(wagoh.getOccupiedSeats() == 0);
  REQUIRE(wagoh.getType() == WagonType::RESTAURANT);
}

TEST_CASE("Constructor with type initialization sets values correctly") {
  Wagon sittingWagon(WagonType::SITTING);
  REQUIRE(sittingWagon.getMaxCapacity() == 100);
  REQUIRE(sittingWagon.getOccupiedSeats() == 0);
  REQUIRE(sittingWagon.getType() == WagonType::SITTING);

  Wagon luxuryWagon(WagonType::LUXURY);
  REQUIRE(luxuryWagon.getMaxCapacity() == 30);
  REQUIRE(luxuryWagon.getOccupiedSeats() == 0);
  REQUIRE(luxuryWagon.getType() == WagonType::LUXURY);

  Wagon restaurantWagon(WagonType::RESTAURANT);
  REQUIRE(restaurantWagon.getMaxCapacity() == 0);
  REQUIRE(restaurantWagon.getOccupiedSeats() == 0);
  REQUIRE(restaurantWagon.getType() == WagonType::RESTAURANT);
}

TEST_CASE("Occupied seats cannot exceed max capacity") {
  REQUIRE_THROWS_AS(Wagon(50, 100, WagonType::ECONOMY), std::invalid_argument);
}

TEST_CASE("Equality operator works correctly") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2(100, 50, WagonType::SITTING);
    Wagon wagon3(50, 30, WagonType::ECONOMY);

    REQUIRE(wagon1 == wagon2); // wagons with the same data should be equal
    REQUIRE(!(wagon1 == wagon3)); // wagons with different data should not be equal
}

TEST_CASE("Assignment operator works correctly") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2;

    wagon2 = wagon1; // Assign wagon1 to wagon2

    REQUIRE(wagon2 == wagon1); // wagon2 should now be equal to wagon1
    REQUIRE(&(wagon1 = wagon1) == &wagon1); // Self-assignment should return the same object

    // Test whether data was correctly copied
    REQUIRE(wagon2.getMaxCapacity() == 100);
    REQUIRE(wagon2.getOccupiedSeats() == 50);
    REQUIRE(wagon2.getType() == WagonType::SITTING);
}

TEST_CASE("Occupancy percentage for non-restaurant wagon is calculated correctly") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);
    Wagon luxuryWagon(30, 15, WagonType::LUXURY);

    // The occupancy percentage should be calculated correctly
    REQUIRE(sittingWagon.getOccupancyPercentage() == Approx(50.0));
    REQUIRE(economyWagon.getOccupancyPercentage() == Approx(60.0));
    REQUIRE(luxuryWagon.getOccupancyPercentage() == Approx(50.0));
}

TEST_CASE("Occupancy percentage for restaurant wagon is always 0%") {
    Wagon restaurantWagon(WagonType::RESTAURANT);
    REQUIRE(restaurantWagon.getOccupancyPercentage() == Approx(0.0));
}

TEST_CASE("Boarding passengers into a non-restaurant wagon works correctly") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);

    // Boarding passengers within capacity should work without exceptions
    REQUIRE_NOTHROW(sittingWagon.boardPassengers(10));
    REQUIRE_NOTHROW(economyWagon.boardPassengers(20));

    // Occupied seats should be updated correctly
    REQUIRE(sittingWagon.getOccupiedSeats() == 60);
    REQUIRE(economyWagon.getOccupiedSeats() == 50);
}

TEST_CASE("Cannot board a negative number of passengers") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);

    // Trying to board a negative number of passengers should throw an exception
    REQUIRE_THROWS_AS(sittingWagon.boardPassengers(-10), std::invalid_argument);
}

TEST_CASE("Cannot board more passengers than capacity") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);

    // Trying to board more passengers than capacity should throw an exception
    REQUIRE_THROWS_AS(sittingWagon.boardPassengers(60), std::invalid_argument);
    REQUIRE_THROWS_AS(economyWagon.boardPassengers(31), std::invalid_argument);
}

TEST_CASE("Cannot board passengers to a restaurant wagon") {
    Wagon restaurantWagon(WagonType::RESTAURANT);

    // Trying to board passengers to a restaurant wagon should throw an exception
    REQUIRE_THROWS_AS(restaurantWagon.boardPassengers(10), std::invalid_argument);
}

TEST_CASE("Disembarking passengers from a non-restaurant wagon works correctly") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);

    // Disembarking passengers within capacity should work without exceptions
    REQUIRE_NOTHROW(sittingWagon.disembarkPassengers(10));
    REQUIRE_NOTHROW(economyWagon.disembarkPassengers(20));

    // Occupied seats should be updated correctly
    REQUIRE(sittingWagon.getOccupiedSeats() == 40);
    REQUIRE(economyWagon.getOccupiedSeats() == 10);
}

TEST_CASE("Cannot disembark a negative number of passengers") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);

    // Trying to disembark a negative number of passengers should throw an exception
    REQUIRE_THROWS_AS(sittingWagon.disembarkPassengers(-10), std::invalid_argument);
}

TEST_CASE("Cannot disembark more passengers than available") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);

    // Trying to disembark more passengers than available should throw an exception
    REQUIRE_THROWS_AS(sittingWagon.disembarkPassengers(60), std::invalid_argument);
    REQUIRE_THROWS_AS(economyWagon.disembarkPassengers(31), std::invalid_argument);
}

TEST_CASE("Cannot disembark from a restaurant wagon") {
    Wagon restaurantWagon(WagonType::RESTAURANT);

    // Trying to disembark from a restaurant wagon should throw an exception
    REQUIRE_THROWS_AS(restaurantWagon.disembarkPassengers(10), std::invalid_argument);
}

TEST_CASE("Get maximum capacity of the wagon") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);
    Wagon restaurantWagon(WagonType::RESTAURANT);

    REQUIRE(sittingWagon.getMaxCapacity() == 100);
    REQUIRE(economyWagon.getMaxCapacity() == 50);
    REQUIRE(restaurantWagon.getMaxCapacity() == 0);
}

TEST_CASE("Get number of occupied seats in the wagon") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);
    Wagon restaurantWagon(WagonType::RESTAURANT);

    REQUIRE(sittingWagon.getOccupiedSeats() == 50);
    REQUIRE(economyWagon.getOccupiedSeats() == 30);
    REQUIRE(restaurantWagon.getOccupiedSeats() == 0);
}

TEST_CASE("Get type of the wagon") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);
    Wagon restaurantWagon(WagonType::RESTAURANT);

    REQUIRE(sittingWagon.getType() == WagonType::SITTING);
    REQUIRE(economyWagon.getType() == WagonType::ECONOMY);
    REQUIRE(restaurantWagon.getType() == WagonType::RESTAURANT);
}

TEST_CASE("Set maximum capacity of the wagon") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);

    SECTION("Setting valid maximum capacity") {
        sittingWagon.setMaxCapacity(120);
        economyWagon.setMaxCapacity(60);

        REQUIRE(sittingWagon.getMaxCapacity() == 120);
        REQUIRE(economyWagon.getMaxCapacity() == 60);
    }

    SECTION("Setting negative maximum capacity") {
        REQUIRE_THROWS(sittingWagon.setMaxCapacity(-10));
        REQUIRE_THROWS(economyWagon.setMaxCapacity(-5));
    }

    SECTION("Setting maximum capacity less than occupied seats") {
        REQUIRE_THROWS(sittingWagon.setMaxCapacity(40));
        REQUIRE_THROWS(economyWagon.setMaxCapacity(20));
    }

    SECTION("Setting maximum capacity for a restaurant wagon") {
        Wagon restaurantWagon(WagonType::RESTAURANT);
        REQUIRE_THROWS(restaurantWagon.setMaxCapacity(100));
    }
}

TEST_CASE("Set number of occupied seats in the wagon") {
    Wagon sittingWagon(100, 50, WagonType::SITTING);
    Wagon economyWagon(50, 30, WagonType::ECONOMY);

    SECTION("Setting valid number of occupied seats") {
        sittingWagon.setOccupiedSeats(60);
        economyWagon.setOccupiedSeats(40);

        REQUIRE(sittingWagon.getOccupiedSeats() == 60);
        REQUIRE(economyWagon.getOccupiedSeats() == 40);
    }

    SECTION("Setting negative number of occupied seats") {
        REQUIRE_THROWS(sittingWagon.setOccupiedSeats(-10));
        REQUIRE_THROWS(economyWagon.setOccupiedSeats(-5));
    }

    SECTION("Setting occupied seats exceeding maximum capacity") {
        REQUIRE_THROWS(sittingWagon.setOccupiedSeats(110));
        REQUIRE_THROWS(economyWagon.setOccupiedSeats(60));
    }

    SECTION("Setting occupied seats for a restaurant wagon") {
        Wagon restaurantWagon(WagonType::RESTAURANT);
        REQUIRE_THROWS(restaurantWagon.setOccupiedSeats(10));
    }
}

TEST_CASE("Set type of the wagon") {
    Wagon wagon(100, 50, WagonType::SITTING);

    SECTION("Setting valid wagon type") {
        wagon.setType(WagonType::ECONOMY);
        REQUIRE(wagon.getType() == WagonType::ECONOMY);
    }

    SECTION("Setting type that exceeds current occupied seats") {
        REQUIRE_THROWS(wagon.setType(WagonType::LUXURY));
    }

    SECTION("Setting restaurant type") {
        wagon.setType(WagonType::RESTAURANT);
        REQUIRE(wagon.getType() == WagonType::RESTAURANT);
    }
}

TEST_CASE("Transfer passengers between wagons") {
    Wagon sittingWagon1(100, 60, WagonType::SITTING);
    Wagon sittingWagon2(100, 40, WagonType::SITTING);
    Wagon economyWagon1(50, 30, WagonType::ECONOMY);
    Wagon economyWagon2(50, 20, WagonType::ECONOMY);

    SECTION("Transfer passengers between two wagons of the same type") {
        sittingWagon1.transferPassengers(sittingWagon2);

        REQUIRE(sittingWagon1.getOccupiedSeats() == 50);
        REQUIRE(sittingWagon2.getOccupiedSeats() == 50);
    }

    SECTION("Transfer passengers from a wagon to another of different type") {
        REQUIRE_THROWS(sittingWagon1.transferPassengers(economyWagon1));
    }

    SECTION("Transfer passengers to/from a restaurant wagon") {
        Wagon restaurantWagon(WagonType::RESTAURANT);
        REQUIRE_THROWS(sittingWagon1.transferPassengers(restaurantWagon));
        REQUIRE_THROWS(restaurantWagon.transferPassengers(sittingWagon2));
    }
}

TEST_CASE("Overloaded operator '>>' for transferring passengers") {
    Wagon sittingWagon1(100, 60, WagonType::SITTING);
    Wagon sittingWagon2(100, 40, WagonType::SITTING);
    Wagon economyWagon1(50, 30, WagonType::ECONOMY);
    Wagon economyWagon2(50, 20, WagonType::ECONOMY);

    SECTION("Transfer passengers using '>>' operator between two wagons of the same type") {
        sittingWagon1 >> sittingWagon2;

        REQUIRE(sittingWagon1.getOccupiedSeats() == 50);
        REQUIRE(sittingWagon2.getOccupiedSeats() == 50);
    }

    SECTION("Transfer passengers using '>>' operator from a wagon to another of different type") {
        REQUIRE_THROWS(economyWagon1 >> sittingWagon1);
    }

    SECTION("Transfer passengers using '>>' operator to/from a restaurant wagon") {
        Wagon restaurantWagon(WagonType::RESTAURANT);
        REQUIRE_THROWS(sittingWagon1 >> restaurantWagon);
        REQUIRE_THROWS(restaurantWagon >> sittingWagon2);
    }
}

TEST_CASE("Input operator (>>) for reading a wagon from an input stream") {
    Wagon wagon;

    SECTION("Valid input for SITTING wagon") {
        std::stringstream input("0\n100\n50\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::SITTING);
        REQUIRE(wagon.getMaxCapacity() == 100);
        REQUIRE(wagon.getOccupiedSeats() == 50);
    }

    SECTION("Valid input for ECONOMY wagon") {
        std::stringstream input("1\n50\n20\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::ECONOMY);
        REQUIRE(wagon.getMaxCapacity() == 50);
        REQUIRE(wagon.getOccupiedSeats() == 20);
    }

    SECTION("Valid input for LUXURY wagon") {
        std::stringstream input("2\n30\n5\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::LUXURY);
        REQUIRE(wagon.getMaxCapacity() == 30);
        REQUIRE(wagon.getOccupiedSeats() == 5);
    }

    SECTION("Valid input for RESTAURANT wagon") {
        std::stringstream input("3\n0\n0\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::RESTAURANT);
        REQUIRE(wagon.getMaxCapacity() == 0);
        REQUIRE(wagon.getOccupiedSeats() == 0);
    }

    SECTION("Invalid input with negative values") {
        std::stringstream input("1\n-50\n20\n");
        input >> wagon;

        // Input should fail, and wagon should not be modified.
        REQUIRE(input.fail());
    }

    SECTION("Invalid input with maxCapacity less than occupiedSeats") {
        std::stringstream input("2\n10\n20\n");
        input >> wagon;

        // Input should fail, and wagon should not be modified.
        REQUIRE(input.fail());
    }

    SECTION("Invalid input with inconsistent values") {
        std::stringstream input("0\n100\n110\n");
        input >> wagon;

        // Input should fail, and wagon should not be modified.
        REQUIRE(input.fail());
    }
}

TEST_CASE("Wagon output operator test", "[Wagon]") {
    // Создаем объект Wagon для теста
    Wagon myWagon(50, 20, WagonType::ECONOMY);

    // Создаем поток для записи вывода
    std::ostringstream output;

    // Перенаправляем вывод в поток output
    output << myWagon;

    // Ожидаемый результат
    std::string expectedOutput = "50\n20\n1\n";

    // Проверяем, что вывод соответствует ожиданиям
    REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("Default Constructor for Train") {
    Train train;
    REQUIRE(train.getNumWagons() == 0);
    REQUIRE(train.getCapacity() == 0);
    REQUIRE(train.getWagons() == nullptr);
}

TEST_CASE("Constructor for Train with Array of Wagons") {
    Wagon wagons[] = {
        Wagon(100, 50, WagonType::SITTING),
        Wagon(150, 70, WagonType::ECONOMY)
    };
    int numWagons = 2;
    Train train(wagons, numWagons);
    REQUIRE(train.getNumWagons() == numWagons);
    REQUIRE(train.getCapacity() == numWagons);
    REQUIRE(train.getWagons() != nullptr);
}

TEST_CASE("Constructor for Train with Single Wagon") {
    Wagon wagon(100, 50, WagonType::SITTING);
    Train train(wagon);
    REQUIRE(train.getNumWagons() == 1);
    REQUIRE(train.getCapacity() == 1);
    REQUIRE(train.getWagons() != nullptr);
    REQUIRE(train[0] == wagon);
}

TEST_CASE("Copy Constructor for Train") {
    Wagon wagons[] = {
        Wagon(100, 50, WagonType::SITTING),
        Wagon(150, 70, WagonType::ECONOMY)
    };
    int numWagons = 2;
    Train originalTrain(wagons, numWagons);
    Train copiedTrain(originalTrain);
    REQUIRE(copiedTrain.getNumWagons() == numWagons);
    REQUIRE(copiedTrain.getCapacity() == numWagons);
    REQUIRE(copiedTrain.getWagons() != nullptr);
    REQUIRE(copiedTrain == originalTrain);
}

TEST_CASE("Move Constructor for Train") {
    Wagon wagons[] = {
        Wagon(100, 50, WagonType::SITTING),
        Wagon(150, 70, WagonType::ECONOMY)
    };
    int numWagons = 2;
    Train originalTrain(wagons, numWagons);
    Train movedTrain(std::move(originalTrain));
    REQUIRE(movedTrain.getNumWagons() == numWagons);
    REQUIRE(movedTrain.getCapacity() == numWagons);
    REQUIRE(movedTrain.getWagons() != nullptr);
    REQUIRE(originalTrain.getNumWagons() == 0);
    REQUIRE(originalTrain.getCapacity() == 0);
    REQUIRE(originalTrain.getWagons() == nullptr);
}

TEST_CASE("Get Number of Wagons in the Train") {
    Train train;
    REQUIRE(train.getNumWagons() == 0);
}

TEST_CASE("Get Array of Wagons in the Train") {
    Wagon wagons[] = {
        Wagon(100, 50, WagonType::SITTING),
        Wagon(150, 70, WagonType::ECONOMY)
    };
    int numWagons = 2;
    Train train(wagons, numWagons);
    const Wagon* trainWagons = train.getWagons();
    REQUIRE(trainWagons != nullptr);
    REQUIRE(trainWagons[0] == wagons[0]);
    REQUIRE(trainWagons[1] == wagons[1]);
}

TEST_CASE("Get Capacity of the Train's Wagon Array") {
    Wagon wagons[] = {
        Wagon(100, 50, WagonType::SITTING),
        Wagon(150, 70, WagonType::ECONOMY)
    };
    int numWagons = 2;
    Train train(wagons, numWagons);
    REQUIRE(train.getCapacity() == numWagons);
}

TEST_CASE("Train::setNumWagons", "[Train]") {
    // Create a Train with initial data
    Wagon initialWagon;
    Train train(initialWagon);

    SECTION("Set number of wagons to a valid positive value") {
        train.setNumWagons(5);
        REQUIRE(train.getNumWagons() == 5);
    }

    SECTION("Try to set number of wagons to a negative value") {
        REQUIRE_THROWS_AS(train.setNumWagons(-2), std::invalid_argument);
    }

    SECTION("Try to set number of wagons less than previous numWagons") {
        REQUIRE_THROWS_AS(train.setNumWagons(0), std::invalid_argument);
    }
}

TEST_CASE("Train::setWagons", "[Train]") {
    // Create an array of wagons
    Wagon wagons[3];
    wagons[0] = Wagon();
    wagons[1] = Wagon(100, 50, WagonType::ECONOMY);
    wagons[2] = Wagon(200, 75, WagonType::SITTING);

    // Create a Train
    Train train;

    SECTION("Set wagons with valid data") {
        REQUIRE_NOTHROW(train.setWagons(wagons, 3));
        REQUIRE(train.getNumWagons() == 3);
    }

    SECTION("Try to set wagons with a negative number of wagons") {
        REQUIRE_THROWS_AS(train.setWagons(wagons, -1), std::invalid_argument);
    }

    SECTION("Try to set wagons with a null pointer") {
        REQUIRE_THROWS_AS(train.setWagons(nullptr, 3), std::invalid_argument);
    }
}

TEST_CASE("Train::setCapacity", "[Train]") {
    // Create a Train with initial data
    Wagon initialWagon;
    Train train(initialWagon);

    SECTION("Set capacity to a valid positive value") {
        REQUIRE_NOTHROW(train.setCapacity(10));
        REQUIRE(train.getCapacity() == 10);
    }

    SECTION("Set capacity equal to the current numWagons") {
        REQUIRE_NOTHROW(train.setCapacity(1));
        REQUIRE(train.getCapacity() == 1);
    }

    SECTION("Try to set capacity to a negative value") {
        REQUIRE_THROWS_AS(train.setCapacity(-5), std::invalid_argument);
    }

    SECTION("Try to set capacity less than the current numWagons") {
        REQUIRE_THROWS_AS(train.setCapacity(0), std::invalid_argument);
    }
}

TEST_CASE("Train::addWagon", "[Train]") {
    // Create a Train
    Train train;

    // Create wagons
    Wagon wagon1;
    Wagon wagon2(200, 100, WagonType::ECONOMY);

    SECTION("Add a single wagon") {
        train.addWagon(wagon1);
        REQUIRE(train.getNumWagons() == 1);
        REQUIRE(train.getWagonByIndex(0) == wagon1);
    }

    SECTION("Add multiple wagons") {
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        REQUIRE(train.getNumWagons() == 2);
        REQUIRE(train.getWagonByIndex(0) == wagon1);
        REQUIRE(train.getWagonByIndex(1) == wagon2);
    }

    SECTION("Add multiple wagons exceeding initial capacity") {
        // Force an initial capacity of 1
        train.setCapacity(1);
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        REQUIRE(train.getNumWagons() == 2);
        REQUIRE(train.getWagonByIndex(0) == wagon1);
        REQUIRE(train.getWagonByIndex(1) == wagon2);
    }
}

TEST_CASE("Train::getWagonByIndex", "[Train]") {
    Train train;
    Wagon wagon1;
    Wagon wagon2(200, 100, WagonType::ECONOMY);

    // Add wagons to the train
    train.addWagon(wagon1);
    train.addWagon(wagon2);

    SECTION("Get a wagon by valid index") {
        const Wagon& retrievedWagon = train.getWagonByIndex(0);
        REQUIRE(retrievedWagon == wagon1);
    }

    SECTION("Get a wagon by a different valid index") {
        const Wagon& retrievedWagon = train.getWagonByIndex(1);
        REQUIRE(retrievedWagon == wagon2);
    }

    SECTION("Get a wagon by an invalid index") {
        REQUIRE_THROWS_AS(train.getWagonByIndex(2), std::out_of_range);
        REQUIRE_THROWS_AS(train.getWagonByIndex(-1), std::out_of_range);
    }
}

TEST_CASE("Train::removeWagonByIndex", "[Train]") {
    Train train;
    Wagon wagon1;
    Wagon wagon2(200, 100, WagonType::ECONOMY);

    // Add wagons to the train
    train.addWagon(wagon1);
    train.addWagon(wagon2);

    SECTION("Remove a wagon by valid index") {
        train.removeWagonByIndex(0);
        REQUIRE(train.getNumWagons() == 1);
        const Wagon& remainingWagon = train.getWagonByIndex(0);
        REQUIRE(remainingWagon == wagon2);
    }

    SECTION("Remove a different wagon by a valid index") {
        train.removeWagonByIndex(1);
        REQUIRE(train.getNumWagons() == 1);
        const Wagon& remainingWagon = train.getWagonByIndex(0);
        REQUIRE(remainingWagon == wagon1);
    }

    SECTION("Remove a wagon by an invalid index") {
        REQUIRE_THROWS_AS(train.removeWagonByIndex(2), std::out_of_range);
        REQUIRE_THROWS_AS(train.removeWagonByIndex(-1), std::out_of_range);
    }
}

TEST_CASE("Train::boardPassengersToMostAvailableWagon", "[Train]") {
    Train train;
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    // Add wagons to the train
    train.addWagon(economyWagon);
    train.addWagon(luxuryWagon);

    SECTION("Board passengers into an economy wagon") {
        // Board 50 passengers into an economy wagon
        train.boardPassengersToMostAvailableWagon(50, WagonType::ECONOMY);
        const Wagon& economyWagonAfterBoarding = train.getWagonByIndex(0);
        REQUIRE(economyWagonAfterBoarding.getOccupiedSeats() == 150); // 100 seats + 50 boarded
    }

    SECTION("Board more passengers than it can take into a luxury") {
        // Board 50 passengers into a luxury wagon
        REQUIRE_THROWS_AS(train.boardPassengersToMostAvailableWagon(50, WagonType::LUXURY), std::invalid_argument);
    }
}

TEST_CASE("Train::getPassengerCountByType", "[Train]") {
    Train train;
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    // Add wagons to the train
    train.addWagon(economyWagon);
    train.addWagon(luxuryWagon);

    SECTION("Calculate passenger count for economy wagons") {
        int occupiedSeats = 0;
        int maxCapacity = 0;
        train.getPassengerCountByType(WagonType::ECONOMY, occupiedSeats, maxCapacity);
        REQUIRE(occupiedSeats == 100); // Occupied seats in the economy wagon
        REQUIRE(maxCapacity == 200);   // Maximum capacity of economy wagons
    }

    SECTION("Calculate passenger count for luxury wagons") {
        int occupiedSeats = 0;
        int maxCapacity = 0;
        train.getPassengerCountByType(WagonType::LUXURY, occupiedSeats, maxCapacity);
        REQUIRE(occupiedSeats == 10); // Occupied seats in the luxury wagon
        REQUIRE(maxCapacity == 50);   // Maximum capacity of luxury wagons
    }
}

TEST_CASE("Train::redistributePassengers", "[Train]") {
    Train train;
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon(150, 70, WagonType::SITTING);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    // Add wagons to the train
    train.addWagon(economyWagon);
    train.addWagon(sittingWagon);
    train.addWagon(luxuryWagon);

    SECTION("Redistribute passengers to achieve balance") {
        train.redistributePassengers();

        REQUIRE(economyWagon.getOccupiedSeats() == 100);
        REQUIRE(sittingWagon.getOccupiedSeats() == 70);
        REQUIRE(luxuryWagon.getOccupiedSeats() == 10);
    }
}

TEST_CASE("Train::optimizeTrain", "[Train]") {
    Train train;
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon(150, 70, WagonType::SITTING);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);
    Wagon economyWagon1(200, 90, WagonType::ECONOMY);

    // Add wagons to the train
    train.addWagon(economyWagon);
    train.addWagon(sittingWagon);
    train.addWagon(luxuryWagon);
    train.addWagon(economyWagon1);

    SECTION("Optimize the train by minimizing the number of wagons") {

        // Expected number of remaining wagons after optimization
        int expectedRemainingWagons = 3;

        train.optimizeTrain();

        // Check the number of wagons after optimization
        REQUIRE(train.getNumWagons() == expectedRemainingWagons);

        // Check that each wagon type has as many passengers as possible
        for (int i = 0; i < train.getNumWagons(); i++) {
            if (train.getWagonByIndex(i).getType() == WagonType::ECONOMY) {
                REQUIRE(train.getWagonByIndex(i).getOccupiedSeats() == 190);
            }
            else if (train.getWagonByIndex(i).getType() == WagonType::SITTING) {
                REQUIRE(train.getWagonByIndex(i).getOccupiedSeats() == 70);
            }
            else if (train.getWagonByIndex(i).getType() == WagonType::LUXURY) {
                REQUIRE(train.getWagonByIndex(i).getOccupiedSeats() == 10);
            }
        }
    }
}

TEST_CASE("Train::addWagonAtIndex", "[Train]") {
  Train train;
  Wagon economyWagon(200, 100, WagonType::ECONOMY);
  Wagon sittingWagon(150, 70, WagonType::SITTING);
  Wagon luxuryWagon(50, 10, WagonType::LUXURY);
  Wagon additionalWagon(100, 50, WagonType::SITTING);

  // Add initial wagons to the train
  train.addWagon(economyWagon);
  train.addWagon(sittingWagon);
  train.addWagon(luxuryWagon);

  SECTION("Add a new wagon at the beginning of the train") {
      int index = 0;

      // The expected number of wagons after adding the new wagon
      int expectedNumWagons = 4;

      train.addWagonAtIndex(additionalWagon, index);

      REQUIRE(train.getNumWagons() == expectedNumWagons);
      REQUIRE(train.getWagonByIndex(index) == additionalWagon);
  }

  SECTION("Add a new wagon in the middle of the train") {
      int index = 1;

      // The expected number of wagons after adding the new wagon
      int expectedNumWagons = 4;

      train.addWagonAtIndex(additionalWagon, index);

      REQUIRE(train.getNumWagons() == expectedNumWagons);
      REQUIRE(train.getWagonByIndex(index) == additionalWagon);
  }

  SECTION("Add a new wagon at the end of the train") {
      int index = train.getNumWagons(); // Add at the end

      // The expected number of wagons after adding the new wagon
      int expectedNumWagons = 4;

      train.addWagonAtIndex(additionalWagon, index);

      REQUIRE(train.getNumWagons() == expectedNumWagons);
      REQUIRE(train.getWagonByIndex(index) == additionalWagon);
  }

  SECTION("Attempt to add a new wagon with an out-of-bounds index") {
      int invalidIndex = train.getNumWagons() + 1; // Index is out of bounds

      // The expected number of wagons remains unchanged
      int expectedNumWagons = 3;

      REQUIRE_THROWS_AS(train.addWagonAtIndex(additionalWagon, invalidIndex), std::invalid_argument);
      REQUIRE(train.getNumWagons() == expectedNumWagons);
  }
}

TEST_CASE("Train::optimizeRestaurantPlacement", "[Train]") {
    Train train;

    Wagon economyWagon1(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon1(150, 70, WagonType::SITTING);
    Wagon sittingWagon2(150, 70, WagonType::SITTING);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    train.addWagon(economyWagon1);
    train.addWagon(sittingWagon1);
    train.addWagon(sittingWagon2);
    train.addWagon(luxuryWagon);

    SECTION("Optimize restaurant placement in the middle") {
        train.optimizeRestaurantPlacement();
        REQUIRE(train.getWagonByIndex(1).getType() == lab2SimpleClass::WagonType::RESTAURANT);
    }
}

TEST_CASE("Train::operator+=", "[Train]") {
    Train train;
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon(150, 70, WagonType::SITTING);

    train += economyWagon;

    REQUIRE(train.getNumWagons() == 1);
    REQUIRE(train.getWagonByIndex(0) == economyWagon);

    train += sittingWagon;

    REQUIRE(train.getNumWagons() == 2);
    REQUIRE(train.getWagonByIndex(1) == sittingWagon);
}

TEST_CASE("Train::operator[]", "[Train]") {
    Train train;

    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon(150, 70, WagonType::SITTING);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    train += economyWagon;
    train += sittingWagon;
    train += luxuryWagon;

    SECTION("Access a wagon by index with non-const operator[]") {
        Wagon& wagon = train[0]; // Access the first wagon

        REQUIRE(wagon == economyWagon);
    }

    SECTION("Access a wagon by index with const operator[]") {
        const Train& constTrain = train; // Create a const reference to the train
        const Wagon& wagon = constTrain[1]; // Access the second wagon

        REQUIRE(wagon == sittingWagon);
    }

    SECTION("Access an out-of-range index with non-const operator[]") {
        REQUIRE_THROWS_AS(train[3], std::invalid_argument);
    }

    SECTION("Access an out-of-range index with const operator[]") {
        const Train& constTrain = train;
        REQUIRE_THROWS_AS(constTrain[3], std::out_of_range);
    }
}

TEST_CASE("Train::operator= (copy assignment)", "[Train]") {
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon(150, 70, WagonType::SITTING);

    SECTION("Copy assignment operator should make a deep copy of another train") {
        Train originalTrain;
        originalTrain += economyWagon;
        originalTrain += sittingWagon;

        Train copiedTrain;
        copiedTrain = originalTrain; // Use the copy assignment operator

        // Verify that the copiedTrain is a deep copy of the originalTrain
        REQUIRE(copiedTrain == originalTrain);
        REQUIRE(&copiedTrain != &originalTrain); // Make sure they are different objects
    }

    SECTION("Copy assignment operator should handle self-assignment") {
        Train train;
        train += economyWagon;

        // Self-assignment: train = train
        train = train; // Use the copy assignment operator with self-assignment

        // The train object should remain unchanged
        REQUIRE(train.getNumWagons() == 1);
    }
}

TEST_CASE("Train::operator= (move assignment)", "[Train]") {
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    SECTION("Move assignment operator should transfer resources efficiently") {
        Train sourceTrain;
        sourceTrain += luxuryWagon;

        Train targetTrain;

        // Move assignment: targetTrain = std::move(sourceTrain)
        targetTrain = std::move(sourceTrain); // Use the move assignment operator

        // Verify that the targetTrain has acquired the resources from the sourceTrain
        REQUIRE(targetTrain.getNumWagons() == 1);
        REQUIRE(sourceTrain.getNumWagons() == 0); // The sourceTrain should be empty
    }

    SECTION("Move assignment operator should handle self-assignment") {
        Train train;
        train += luxuryWagon;

        // Self-assignment: train = std::move(train)
        train = std::move(train); // Use the move assignment operator with self-assignment

        // The train object should remain unchanged
        REQUIRE(train.getNumWagons() == 1);
    }
}

TEST_CASE("Train::operator>> (input stream operator)", "[Train]") {
    // Создайте строку, содержащую представление объекта Train
    std::string trainInput = "3\n"
                            "1\n200\n100\n"
                            "0\n150\n70\n"
                            "2\n50\n10\n";

    std::istringstream iss(trainInput); // Создайте входной поток из строки
    Train train;

    // Введите данные из входного потока
    iss >> train;

    // Проверьте, что данные были введены корректно
    REQUIRE(train.getNumWagons() == 3);
    REQUIRE(train[0].getMaxCapacity() == 200);
    REQUIRE(train[1].getMaxCapacity() == 150);
    REQUIRE(train[2].getMaxCapacity() == 50);
}

TEST_CASE("Train::operator<< (output stream operator)", "[Train]") {
    Wagon economyWagon(200, 100, WagonType::ECONOMY);
    Wagon sittingWagon(150, 70, WagonType::SITTING);
    Wagon luxuryWagon(50, 10, WagonType::LUXURY);

    Train train;
    train += economyWagon;
    train += sittingWagon;
    train += luxuryWagon;

    std::ostringstream oss; // Создайте выходной поток

    // Выведите данные в выходной поток
    oss << train;

    // Получите строковое представление данных из выходного потока
    std::string trainOutput = oss.str();

    // Проверьте, что данные были выведены корректно
    REQUIRE(trainOutput == "3\n200\n100\n1\n150\n70\n0\n50\n10\n2\n");
}
