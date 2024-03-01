#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <sstream>
#include "../myLib/train.h"
#include "../myLib/wagon.h"
#include "../myLib/getnum.h"

using namespace lab2ComplexClass;
using namespace lab2SimpleClass;

TEST_CASE("Operator<< for Train class", "[train_operator<<]") {
	SECTION("Valid output") {
		Wagon wagon1(100, 50, WagonType::SITTING);
		Wagon wagon2(200, 100, WagonType::ECONOMY);
		Wagon wagon3(150, 75, WagonType::LUXURY);
		Train train;
		train.addWagon(wagon1);
		train.addWagon(wagon2);
		train.addWagon(wagon3);
		std::stringstream output;
		output << train;
		std::string expectedOutput = "Number of Wagons: 3\nMax Capacity: 100\nOccupied Seats: 50\nType: Sitting\nMax Capacity: 200\nOccupied Seats: 100\nType: Economy\nMax Capacity: 150\nOccupied Seats: 75\nType: Luxury\n";
		REQUIRE(output.str() == expectedOutput);
	}
}

TEST_CASE("writeToOutput for Train class", "[train_writeToOutput]") {
	SECTION("Valid output") {
		std::stringstream capturedOutput;
		std::streambuf* originalOutput = std::cout.rdbuf();
		std::cout.rdbuf(capturedOutput.rdbuf());
		Train train;
		train.setNumWagons(3);
		Wagon wagons[3] = {Wagon(100, 50, WagonType::SITTING),
		Wagon(200, 100, WagonType::ECONOMY), 
		Wagon(150, 75, WagonType::LUXURY)};
		train.setWagons(wagons, 3);
		train.writeToOutput();
		std::cout.rdbuf(originalOutput);
		std::string expectedOutput = "3\n100 50 0\n200 100 1\n150 75 2\n";
		REQUIRE(capturedOutput.str() == expectedOutput);
	}
}

TEST_CASE("Operator>> for Train class", "[train_operator>>]") {
    SECTION("Valid input") {
        std::string inputString = "3\n1\n100\n50\n2\n200\n100\n3\n";
        std::istringstream iss(inputString);
        Train train;
        REQUIRE(iss >> train);
	INFO("Input stream state: " << std::hex << iss.rdstate());
	if (iss.fail()) {INFO("Input operation failed");}
	if (iss.eof()) {INFO("End of file reached");}
	if (iss.bad()) {INFO("Stream state is bad");}
	if (iss.good()) {INFO("Stream state is good");}
	REQUIRE(train.getNumWagons() == 3);
	const Wagon* wagons = train.getWagons();
	REQUIRE(wagons[0].getMaxCapacity() == 100);
	REQUIRE(wagons[1].getMaxCapacity() == 200);
	REQUIRE(wagons[2].getMaxCapacity() == 0);
    }
    SECTION("Invalid input (negative numWagons)") {
        std::string inputString = "-2\n";
        std::istringstream iss(inputString);
	Train train;
	REQUIRE_FALSE(iss >> train);
	REQUIRE(iss.fail());
    }
    SECTION("Invalid input (unexpected end of file)") {
	std::string inputString = "2\n1\n100\n50\n";
	std::istringstream iss(inputString);
	Train train;
	REQUIRE_FALSE(iss >> train);
	REQUIRE(iss.fail());
    }
}

TEST_CASE("Accessing Wagon by Index in Train") {
    Train train;
    train += Wagon(10, 1, WagonType::SITTING);
    train += Wagon(20, 2, WagonType::ECONOMY);
    train += Wagon(30, 3, WagonType::LUXURY);

    SECTION("Accessing Wagon by Valid Index") {
        REQUIRE(train[0].getMaxCapacity() == 10);
        REQUIRE(train[1].getMaxCapacity() == 20);
        REQUIRE(train[2].getMaxCapacity() == 30);
    }

    SECTION("Accessing Wagon by Invalid Index") {
        REQUIRE_THROWS_AS(train[-1], std::invalid_argument);
        REQUIRE_THROWS_AS(train[3], std::invalid_argument);
    }

    const Train& constTrain = train;

    SECTION("Accessing Wagon by Valid Index in Const Train") {
        REQUIRE(constTrain[0].getMaxCapacity() == 10);
        REQUIRE(constTrain[1].getMaxCapacity() == 20);
        REQUIRE(constTrain[2].getMaxCapacity() == 30);
    }

    SECTION("Accessing Wagon by Invalid Index in Const Train") {
        REQUIRE_THROWS_AS(constTrain[-1], std::out_of_range);
        REQUIRE_THROWS_AS(constTrain[3], std::out_of_range);
    }
}

TEST_CASE("Train addWagonAtIndex Method") {
    SECTION("Add a Wagon to an Empty Train") {
        // Create an empty train
        Train train;
        Wagon newWagon(50, 10, WagonType::SITTING);
        int index = 0;

        // Call the addWagonAtIndex method
        train.addWagonAtIndex(newWagon, index);

        // Check if the train now has 1 wagon
        REQUIRE(train.getNumWagons() == 1);

        // Check if the added wagon matches the new wagon
        REQUIRE(train.getWagonByIndex(index) == newWagon);
    }

    SECTION("Add a Wagon to the Beginning of a Train with Existing Wagons") {
        // Create a train with existing wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);

        Wagon newWagon(40, 5, WagonType::LUXURY);
        int index = 0;

        // Call the addWagonAtIndex method
        train.addWagonAtIndex(newWagon, index);

        // Check if the train now has 3 wagons
        REQUIRE(train.getNumWagons() == 3);

        // Check if the added wagon is now at the beginning of the train
        REQUIRE(train.getWagonByIndex(index) == newWagon);
    }

    SECTION("Add a Wagon to the Middle of a Train with Existing Wagons") {
        // Create a train with existing wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);

        Wagon newWagon(40, 5, WagonType::LUXURY);
        int index = 1;

        // Call the addWagonAtIndex method
        train.addWagonAtIndex(newWagon, index);

        // Check if the train now has 3 wagons
        REQUIRE(train.getNumWagons() == 3);

        // Check if the added wagon is in the middle of the train
        REQUIRE(train.getWagonByIndex(index) == newWagon);
    }

    SECTION("Add a Wagon to the End of a Train with Existing Wagons") {
        // Create a train with existing wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);

        Wagon newWagon(40, 5, WagonType::LUXURY);
        int index = 2;

        // Call the addWagonAtIndex method
        train.addWagonAtIndex(newWagon, index);

        // Check if the train now has 3 wagons
        REQUIRE(train.getNumWagons() == 3);

        // Check if the added wagon is at the end of the train
        REQUIRE(train.getWagonByIndex(index) == newWagon);
    }
}

TEST_CASE("Train optimizeTrain Method") {
    SECTION("Optimize an Empty Train") {
        // Create an empty train
        Train train;

        // Call the optimizeTrain method
        train.optimizeTrain();

        // Since the train is empty, no changes are expected
        REQUIRE(train.getNumWagons() == 0);
    }

    SECTION("Optimize a Train with Various Wagon Types") {
        // Create a train with various types of wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        Wagon wagon3(40, 5, WagonType::LUXURY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        train.addWagon(wagon3);

        // Call the optimizeTrain method
        train.optimizeTrain();

        // Check if the number of wagons has been minimized
        REQUIRE(train.getNumWagons() == 3);

        // Check if empty wagons have been removed
        REQUIRE(train.getWagonByIndex(0).getOccupiedSeats() > 0);
        REQUIRE(train.getWagonByIndex(1).getOccupiedSeats() > 0);
        REQUIRE(train.getWagonByIndex(2).getOccupiedSeats() > 0);
    }

    SECTION("Optimize a Train with Empty Wagons") {
        // Create a train with empty wagons
        Train train;
        Wagon wagon1(50, 0, WagonType::SITTING);
        Wagon wagon2(60, 0, WagonType::ECONOMY);
        Wagon wagon3(40, 0, WagonType::LUXURY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        train.addWagon(wagon3);

        // Call the optimizeTrain method
        train.optimizeTrain();

        // Check if empty wagons have been removed
        REQUIRE(train.getNumWagons() == 0);
    }
}

TEST_CASE("Train redistributePassengers Method") {
    SECTION("Redistribute Passengers in an Empty Train") {
        // Create an empty train
        Train train;

        // Call the redistributePassengers method
        train.redistributePassengers();

        // Since the train is empty, there's nothing to redistribute, so no change is expected
        REQUIRE(train.getNumWagons() == 0);
    }

    SECTION("Redistribute Passengers in a Train with Various Wagon Types") {
        // Create a train with various types of wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(80, 20, WagonType::ECONOMY);
        Wagon wagon3(40, 10, WagonType::LUXURY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        train.addWagon(wagon3);

        // Call the redistributePassengers method
        train.redistributePassengers();

        // Check if the occupancy percentages for each wagon type match the expected values
        REQUIRE(train.getWagonByIndex(0).getOccupancyPercentage() == 20.0);
        REQUIRE(train.getWagonByIndex(1).getOccupancyPercentage() == 25.0);
        REQUIRE(train.getWagonByIndex(2).getOccupancyPercentage() == 25.0);
    }

    SECTION("Redistribute Passengers in a Train with All Wagons of the Same Type") {
        // Create a train with all wagons of the same type (Economy)
        Train train;
        Wagon wagon1(80, 10, WagonType::ECONOMY);
        Wagon wagon2(80, 20, WagonType::ECONOMY);
        Wagon wagon3(40, 10, WagonType::ECONOMY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        train.addWagon(wagon3);

        // Call the redistributePassengers method
        train.redistributePassengers();

        // Check if the occupancy percentages for all wagons match the expected common value
        REQUIRE(train.getWagonByIndex(0).getOccupancyPercentage() == 20);
        REQUIRE(train.getWagonByIndex(1).getOccupancyPercentage() == 20);
        REQUIRE(train.getWagonByIndex(2).getOccupancyPercentage() == 20);
    }
}

TEST_CASE("Train getPassengerCountByType Method") {
    // Create a train with different types of wagons
    Train train;
    Wagon wagon1(50, 10, WagonType::SITTING);
    Wagon wagon2(60, 20, WagonType::SITTING);
    Wagon wagon3(40, 5, WagonType::ECONOMY);
    Wagon wagon4(80, 10, WagonType::ECONOMY);
    train.addWagon(wagon1);
    train.addWagon(wagon2);
    train.addWagon(wagon3);
    train.addWagon(wagon4);

    SECTION("Count Passengers in Sitting Wagons") {
        int occupiedSeats = 0;
        int maxCapacity = 0;
        train.getPassengerCountByType(WagonType::SITTING, occupiedSeats, maxCapacity);

        // Check the calculated values
        REQUIRE(occupiedSeats == 10 + 20); // Sum of passengers in sitting wagons
        REQUIRE(maxCapacity == 50 + 60);    // Sum of max capacities of sitting wagons
    }

    SECTION("Count Passengers in Economy Wagons") {
        int occupiedSeats = 0;
        int maxCapacity = 0;
        train.getPassengerCountByType(WagonType::ECONOMY, occupiedSeats, maxCapacity);

        // Check the calculated values
        REQUIRE(occupiedSeats == 5 + 10);  // Sum of passengers in economy wagons
        REQUIRE(maxCapacity == 40 + 80);  // Sum of max capacities of economy wagons
    }

    SECTION("Count Passengers in Luxury Wagons") {
        int occupiedSeats = 0;
        int maxCapacity = 0;
        train.getPassengerCountByType(WagonType::LUXURY, occupiedSeats, maxCapacity);

        // Check the calculated values
        REQUIRE(occupiedSeats == 0);  // There are no luxury wagons
        REQUIRE(maxCapacity == 0);    // There are no luxury wagons
    }
}

TEST_CASE("Train boardPassengersToMostAvailableWagon Method") {
    SECTION("Board Passengers to Available Wagon") {
        // Create a train with some wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::SITTING);
        train.addWagon(wagon1);
        train.addWagon(wagon2);

        // Board passengers to the most available wagon
        train.boardPassengersToMostAvailableWagon(15, WagonType::SITTING);

        // Check if passengers were correctly boarded to the wagon
        REQUIRE(train.getWagonByIndex(0).getOccupiedSeats() == 10);
    }

    SECTION("Board Passengers to No Available Wagon") {
        // Create a train with some wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        train.addWagon(wagon1);

        // Try to board passengers to a wagon where it's not possible
        // It should throw an exception
        REQUIRE_THROWS_WITH(train.boardPassengersToMostAvailableWagon(60, WagonType::SITTING), "Error while boarding passengers.");
    }
}

TEST_CASE("Train removeWagonByIndex Method") {
    SECTION("Remove Wagon by Valid Index") {
        // Create a train with some wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        Wagon wagon3(70, 30, WagonType::LUXURY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);
        train.addWagon(wagon3);

        // Remove the second wagon by index (index 1)
        train.removeWagonByIndex(1);

        // Check if the train no longer contains the removed wagon
        REQUIRE(train.getNumWagons() == 2);
        REQUIRE(train.getWagonByIndex(0) == wagon1);
        REQUIRE(train.getWagonByIndex(1) == wagon3);
    }

    SECTION("Remove Wagon by Invalid Index") {
        // Create a train with some wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        train.addWagon(wagon1);

        // Try to remove a wagon with an invalid index
        // It should throw an exception of type std::out_of_range
        REQUIRE_THROWS_AS(train.removeWagonByIndex(1), std::out_of_range);
    }
}


TEST_CASE("Default constructor sets values correctly") {
    Wagon wagon;
    REQUIRE(wagon.getMaxCapacity() == 0);
    REQUIRE(wagon.getOccupiedSeats() == 0);
    REQUIRE(wagon.getType() == WagonType::RESTAURANT);
}

TEST_CASE("Explicit constructor with parameters sets values correctly") {
    Wagon wagon(100, 50, WagonType::SITTING);
    REQUIRE(wagon.getMaxCapacity() == 100);
    REQUIRE(wagon.getOccupiedSeats() == 50);
    REQUIRE(wagon.getType() == WagonType::SITTING);
}

TEST_CASE("Explicit constructor with invalid type throws an exception") {
    REQUIRE_THROWS_AS(Wagon(100, 50, WagonType::RESTAURANT), std::invalid_argument);
}

TEST_CASE("Explicit constructor with type sets values correctly") {
    Wagon wagon(WagonType::LUXURY);
    REQUIRE(wagon.getMaxCapacity() == 30);
    REQUIRE(wagon.getOccupiedSeats() == 0);
    REQUIRE(wagon.getType() == WagonType::LUXURY);
}

TEST_CASE("Occupancy percentage is 0% for a restaurant wagon") {
    Wagon wagon(WagonType::RESTAURANT);
    REQUIRE(wagon.getOccupancyPercentage() == 0.0);
}

TEST_CASE("Occupancy percentage is calculated correctly for other wagon types") {
    Wagon wagonSitting(100, 50, WagonType::SITTING);
    REQUIRE(wagonSitting.getOccupancyPercentage() == Approx(50.0));

    Wagon wagonEconomy(50, 25, WagonType::ECONOMY);
    REQUIRE(wagonEconomy.getOccupancyPercentage() == Approx(50.0));

    Wagon wagonLuxury(30, 10, WagonType::LUXURY);
    REQUIRE(wagonLuxury.getOccupancyPercentage() == Approx(33.333).epsilon(0.01)); // Approx with epsilon for floating-point comparison
}

TEST_CASE("Boarding passengers in a restaurant wagon should do nothing") {
    Wagon wagon(WagonType::RESTAURANT);
    wagon.boardPassengers(10); // Try to board passengers in a restaurant wagon
    REQUIRE(wagon.getOccupiedSeats() == 0);
}

TEST_CASE("Boarding passengers in other wagon types works correctly") {
    Wagon wagon(100, 50, WagonType::SITTING);
    wagon.boardPassengers(10); // Board 10 passengers
    REQUIRE(wagon.getOccupiedSeats() == 60);

    try {
        wagon.boardPassengers(50); // Try to board more passengers than max capacity
        FAIL("Exception should have been thrown");
    } catch (const std::invalid_argument& e) {
        REQUIRE(std::string(e.what()) == "Wagon is full. Cannot board more passengers.");
    }
}

TEST_CASE("Boarding passengers beyond max capacity should throw an exception") {
    Wagon wagon(50, 40, WagonType::ECONOMY);
    REQUIRE_THROWS_AS(wagon.boardPassengers(20), std::invalid_argument);
}

TEST_CASE("Disembarking passengers in a luxury wagon should do nothing") {
    Wagon wagon(WagonType::LUXURY);
  try {
    wagon.disembarkPassengers(1000); // Try to disembark passengers in a luxurywagon
    FAIL("Exception should have been thrown");
  } catch (const std::invalid_argument& e) {
    REQUIRE(std::string(e.what()) == "There are not enough people in the Wagon to disembark.");
  }
  REQUIRE(wagon.getOccupiedSeats() == 0); // Occupied seats should remain 0
}

TEST_CASE("Disembarking passengers in other wagon types works correctly") {
    Wagon wagon(100, 50, WagonType::SITTING);
    wagon.disembarkPassengers(10); // Disembark 10 passengers
    REQUIRE(wagon.getOccupiedSeats() == 40);

  try {
      wagon.disembarkPassengers(60); // Try to disembark more passengers than in wagon
      FAIL("Exception should have been thrown");
  } catch (const std::invalid_argument& e) {
      REQUIRE(std::string(e.what()) == "There are not enough people in the Wagon to disembark.");
  }
    REQUIRE(wagon.getOccupiedSeats() == 40); // Occupied seats should remain the same
}

TEST_CASE("Disembarking passengers when there are not enough passengers should throw an exception") {
    Wagon wagon(50, 40, WagonType::ECONOMY);
    REQUIRE_THROWS_AS(wagon.disembarkPassengers(50), std::invalid_argument);
}

TEST_CASE("Getters and setters work correctly") {
    Wagon wagon(100, 50, WagonType::SITTING);

    SECTION("Testing getters") {
        REQUIRE(wagon.getMaxCapacity() == 100);
        REQUIRE(wagon.getOccupiedSeats() == 50);
        REQUIRE(wagon.getType() == WagonType::SITTING);
    }

    SECTION("Testing setters") {
        // Test setMaxCapacity
        wagon.setMaxCapacity(150);
        REQUIRE(wagon.getMaxCapacity() == 150);

        // Test setOccupiedSeats
        wagon.setOccupiedSeats(60);
        REQUIRE(wagon.getOccupiedSeats() == 60);

        // Test setType
        wagon.setType(WagonType::ECONOMY);
        REQUIRE(wagon.getType() == WagonType::ECONOMY);
    }

    SECTION("Testing setters with invalid values should throw exceptions") {
        // Test setMaxCapacity with a negative value
        REQUIRE_THROWS_AS(wagon.setMaxCapacity(-50), std::invalid_argument);

        // Test setMaxCapacity with a value less than currently occupied seats
        REQUIRE_THROWS_AS(wagon.setMaxCapacity(40), std::invalid_argument);

        // Test setOccupiedSeats with a negative value
        REQUIRE_THROWS_AS(wagon.setOccupiedSeats(-10), std::invalid_argument);

        // Test setOccupiedSeats with a value greater than max capacity
        REQUIRE_THROWS_AS(wagon.setOccupiedSeats(200), std::invalid_argument);

        // Test setType with WagonType::RESTAURANT
        REQUIRE_THROWS_AS(wagon.setType(WagonType::RESTAURANT), std::invalid_argument);
    }
}


TEST_CASE("Transferring passengers between non-restaurant wagons works correctly") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2(100, 30, WagonType::SITTING);

    wagon1.transferPassengers(wagon2);

    REQUIRE(wagon1.getOccupiedSeats() == Approx(40));
    REQUIRE(wagon2.getOccupiedSeats() == Approx(40));
}

TEST_CASE("Transferring passengers involving a restaurant wagon should throw an exception") {
    Wagon restaurantWagon(WagonType::RESTAURANT);
    Wagon otherWagon(100, 50, WagonType::SITTING);

    REQUIRE_THROWS_AS(restaurantWagon.transferPassengers(otherWagon), std::invalid_argument);
    REQUIRE_THROWS_AS(otherWagon.transferPassengers(restaurantWagon), std::invalid_argument);
}

TEST_CASE("Transferring passengers between wagons of different types should throw an exception") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2(100, 30, WagonType::ECONOMY);

    REQUIRE_THROWS_AS(wagon1.transferPassengers(wagon2), std::invalid_argument);
}

TEST_CASE("Overloaded '>>' operator works correctly") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2(100, 30, WagonType::SITTING);

    // Test the '>>' operator by transferring passengers from wagon1 to wagon2
    wagon1 >> wagon2;

    REQUIRE(wagon1.getOccupiedSeats() == Approx(40));
    REQUIRE(wagon2.getOccupiedSeats() == Approx(40));
}

TEST_CASE("Input Method for Wagon") {
    SECTION("Valid Input for Sitting Wagon") {
        Wagon wagon;
        std::istringstream input("0\n50\n10\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::SITTING);
        REQUIRE(wagon.getMaxCapacity() == 50);
        REQUIRE(wagon.getOccupiedSeats() == 10);
    }

    SECTION("Valid Input for Economy Wagon") {
        Wagon wagon;
        std::istringstream input("1\n80\n20\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::ECONOMY);
        REQUIRE(wagon.getMaxCapacity() == 80);
        REQUIRE(wagon.getOccupiedSeats() == 20);
    }

    SECTION("Valid Input for Luxury Wagon") {
        Wagon wagon;
        std::istringstream input("2\n40\n5\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::LUXURY);
        REQUIRE(wagon.getMaxCapacity() == 40);
        REQUIRE(wagon.getOccupiedSeats() == 5);
    }

    SECTION("Valid Input for Restaurant Wagon") {
        Wagon wagon;
        std::istringstream input("3\n0\n0\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::RESTAURANT);
        REQUIRE(wagon.getMaxCapacity() == 0);
        REQUIRE(wagon.getOccupiedSeats() == 0);
    }

    SECTION("Invalid Input - Negative Values") {
        Wagon wagon;
        std::istringstream input("0\n-50\n-10\n");
        input >> wagon;

        REQUIRE(input.fail());
    }

    SECTION("Invalid Input - Max Capacity Less Than Occupied Seats") {
        Wagon wagon;
        std::istringstream input("1\n20\n30\n");
        input >> wagon;

        REQUIRE(input.fail());
    }

    SECTION("Invalid Input - Invalid Type") {
        Wagon wagon;
        std::istringstream input("4\n50\n10\n");
        input >> wagon;

        REQUIRE(input.fail());
    }

    SECTION("Invalid Input - Missing Data") {
        Wagon wagon;
        std::istringstream input("1\n50\n");
        input >> wagon;

        REQUIRE(input.fail());
    }
}

TEST_CASE("Input Operator for Wagon") {
    SECTION("Valid Input for Sitting Wagon") {
        Wagon wagon;
        std::istringstream input("0\n50\n10\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::SITTING);
        REQUIRE(wagon.getMaxCapacity() == 50);
        REQUIRE(wagon.getOccupiedSeats() == 10);
    }

    SECTION("Valid Input for Economy Wagon") {
        Wagon wagon;
        std::istringstream input("1\n80\n20\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::ECONOMY);
        REQUIRE(wagon.getMaxCapacity() == 80);
        REQUIRE(wagon.getOccupiedSeats() == 20);
    }

    SECTION("Valid Input for Luxury Wagon") {
        Wagon wagon;
        std::istringstream input("2\n40\n5\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::LUXURY);
        REQUIRE(wagon.getMaxCapacity() == 40);
        REQUIRE(wagon.getOccupiedSeats() == 5);
    }

    SECTION("Valid Input for Restaurant Wagon") {
        Wagon wagon;
        std::istringstream input("3\n0\n0\n");
        input >> wagon;

        REQUIRE(wagon.getType() == WagonType::RESTAURANT);
        REQUIRE(wagon.getMaxCapacity() == 0);
        REQUIRE(wagon.getOccupiedSeats() == 0);
    }

    SECTION("Invalid Input - Negative Values") {
        Wagon wagon;
        std::istringstream input("0\n-50\n-10\n");
        input >> wagon;

        REQUIRE(input.fail());
    }

    SECTION("Invalid Input - Max Capacity Less Than Occupied Seats") {
        Wagon wagon;
        std::istringstream input("1\n20\n30\n");
        input >> wagon;

        REQUIRE(input.fail());
    }

    SECTION("Invalid Input - Invalid Type") {
        Wagon wagon;
        std::istringstream input("4\n50\n10\n");
        input >> wagon;

        REQUIRE(input.fail());
    }

    SECTION("Invalid Input - Missing Data") {
        Wagon wagon;
        std::istringstream input("1\n50\n");
        input >> wagon;

        REQUIRE(input.fail());
    }
}

TEST_CASE("Output Operator for Wagon") {
    SECTION("Sitting Wagon Output") {
        Wagon wagon(50, 10, WagonType::SITTING);
        std::ostringstream output;
        output << wagon;

        std::string expectedOutput = "Max Capacity: 50\nOccupied Seats: 10\nType: Sitting\n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Economy Wagon Output") {
        Wagon wagon(80, 20, WagonType::ECONOMY);
        std::ostringstream output;
        output << wagon;

        std::string expectedOutput = "Max Capacity: 80\nOccupied Seats: 20\nType: Economy\n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Luxury Wagon Output") {
        Wagon wagon(40, 5, WagonType::LUXURY);
        std::ostringstream output;
        output << wagon;

        std::string expectedOutput = "Max Capacity: 40\nOccupied Seats: 5\nType: Luxury\n";
        REQUIRE(output.str() == expectedOutput);
    }
}

TEST_CASE("WriteToOutput Method for Wagon") {
    // Redirect stdout to a stringstream for capturing the output
    std::ostringstream capturedOutput;
    std::streambuf* originalOutput = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());

    SECTION("Sitting Wagon Output") {
        Wagon wagon(50, 10, WagonType::SITTING);
        wagon.writeToOutput();

        // Restore the original stdout
        std::cout.rdbuf(originalOutput);

        // Compare the captured output
        std::string expectedOutput = "50 10 0\n";
        REQUIRE(capturedOutput.str() == expectedOutput);
    }

    SECTION("Economy Wagon Output") {
        Wagon wagon(80, 20, WagonType::ECONOMY);
        wagon.writeToOutput();

        // Restore the original stdout
        std::cout.rdbuf(originalOutput);

        // Compare the captured output
        std::string expectedOutput = "80 20 1\n";
        REQUIRE(capturedOutput.str() == expectedOutput);
    }

    SECTION("Luxury Wagon Output") {
        Wagon wagon(40, 5, WagonType::LUXURY);
        wagon.writeToOutput();

        // Restore the original stdout
        std::cout.rdbuf(originalOutput);

        // Compare the captured output
        std::string expectedOutput = "40 5 2\n";
        REQUIRE(capturedOutput.str() == expectedOutput);
    }
}

TEST_CASE("Train Constructors") {
    SECTION("Default Constructor") {
        Train train;
        REQUIRE(train.getNumWagons() == 0);
        REQUIRE(train.getCapacity() == 0);
        REQUIRE(train.getWagons() == nullptr);
    }

    SECTION("Constructor with Wagon Array") {
        Wagon wagons[3]; // Initialize an array of Wagon objects
        // Populate the array with your test data
        Train train(wagons, 3);
        REQUIRE(train.getNumWagons() == 3);
        REQUIRE(train.getCapacity() == 3);
    }

    SECTION("Constructor with Single Wagon") {
        Wagon wagon(50, 10, WagonType::SITTING);
        Train train(wagon);
        REQUIRE(train.getNumWagons() == 1);
        REQUIRE(train.getCapacity() == 1);
    }

    SECTION("Copy Constructor") {
        Wagon wagons[3]; // Initialize an array of Wagon objects
        // Populate the array with your test data
        Train originalTrain(wagons, 3);
        Train copiedTrain(originalTrain);
        REQUIRE(copiedTrain.getNumWagons() == 3);
        REQUIRE(copiedTrain.getCapacity() == 3);
        // Optionally, add more checks to verify data is copied correctly
    }

    SECTION("Move Constructor") {
        Wagon wagons[3]; // Initialize an array of Wagon objects
        // Populate the array with your test data
        Train originalTrain(wagons, 3);
        Train movedTrain(std::move(originalTrain));
        REQUIRE(movedTrain.getNumWagons() == 3);
        REQUIRE(movedTrain.getCapacity() == 3);
        REQUIRE(originalTrain.getNumWagons() == 0); // Original should be moved from
        REQUIRE(originalTrain.getWagons() == nullptr);
    }
}

TEST_CASE("Train operator+= Method") {
    SECTION("Add Wagon to an Empty Train") {
        // Create an empty train
        Train train;

        // Create a wagon to add
        Wagon wagon(50, 10, WagonType::SITTING);

        // Add the wagon to the train using operator+=
        train += wagon;

        // Check if the train contains the added wagon
        REQUIRE(train.getNumWagons() == 1);
        REQUIRE(train.getWagonByIndex(0) == wagon);
    }

    SECTION("Add Wagon to a Train with Existing Wagons") {
        // Create a train with existing wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        train += wagon1;
        train += wagon2;

        // Create a new wagon to add
        Wagon newWagon(70, 30, WagonType::LUXURY);

        // Add the new wagon to the train using operator+=
        train += newWagon;

        // Check if the train contains the new wagon
        REQUIRE(train.getNumWagons() == 3);
        REQUIRE(train.getWagonByIndex(2) == newWagon);
    }
}

TEST_CASE("Train::readFromInput Method") {
    SECTION("Valid Input for a Train with Wagons") {
        // Create a stream with input data (e.g., a stringstream).
        std::stringstream input;
        input << "3" << std::endl;  // Number of wagons
        input << "SITTING 50 10" << std::endl; // Wagon 1
        input << "ECONOMY 60 20" << std::endl; // Wagon 2
        input << "LUXURY 70 30" << std::endl;  // Wagon 3

        // Redirect std::cin to use the input stream.
        std::streambuf* originalCin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        // Create a train and call readFromInput.
        Train train;
        train.readFromInput(3);

        // Restore the original std::cin.
        std::cin.rdbuf(originalCin);

        // Check if the train contains the correct number of wagons.
        REQUIRE(train.getNumWagons() == 3);
        // You may want to add more checks to verify each wagon.
    }

    SECTION("Invalid Input for Train") {
      // Create a stream with invalid input (e.g., a stringstream).
      std::stringstream input;
      input << "-1" << std::endl; // Invalid number of wagons

      // Redirect std::cin to use the input stream.
      std::streambuf* originalCin = std::cin.rdbuf();
      std::cin.rdbuf(input.rdbuf());

      // Create a train and call readFromInput with invalid input.
      Train train;
    
      // Use a try-catch block to catch exceptions thrown by readFromInput.
      try {
        train.readFromInput(-1);
      } catch (const std::bad_array_new_length& e) {
        // Handle the exception (e.g., set a flag to indicate the error).
      }

      // Restore the original std::cin.
      std::cin.rdbuf(originalCin);

      // Check if the train is empty (no wagons added).
      REQUIRE(train.getNumWagons() == 0);
    }
}

TEST_CASE("Train addWagon Method") {
    SECTION("Add Wagon to an Empty Train") {
        // Create an empty train
        Train train;

        // Create a wagon to add
        Wagon wagon(50, 10, WagonType::SITTING);

        // Add the wagon to the train
        train.addWagon(wagon);

        // Check if the train contains the added wagon
        REQUIRE(train.getNumWagons() == 1);
        REQUIRE(train.getWagonByIndex(0) == wagon);
    }

    SECTION("Add Wagon to a Train with Existing Wagons") {
        // Create a train with existing wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);

        // Create a new wagon to add
        Wagon newWagon(70, 30, WagonType::LUXURY);

        // Add the new wagon to the train
        train.addWagon(newWagon);

        // Check if the train contains the new wagon
        REQUIRE(train.getNumWagons() == 3);
        REQUIRE(train.getWagonByIndex(2) == newWagon);
    }
}

TEST_CASE("Train getWagonByIndex Method") {
    SECTION("Get Wagon by Valid Index") {
        // Create a train with some wagons
        Train train;
        Wagon wagon1(50, 10, WagonType::SITTING);
        Wagon wagon2(60, 20, WagonType::ECONOMY);
        train.addWagon(wagon1);
        train.addWagon(wagon2);

        // Retrieve the wagons by index
        const Wagon& retrievedWagon1 = train.getWagonByIndex(0);
        const Wagon& retrievedWagon2 = train.getWagonByIndex(1);

        // Check if the retrieved wagons match the original ones
        REQUIRE(retrievedWagon1 == wagon1);
        REQUIRE(retrievedWagon2 == wagon2);
    }

    SECTION("Get Wagon by Invalid Index") {
        // Create an empty train
        Train train;

        // Try to retrieve a wagon with an invalid index
        // It should throw an exception of type std::out_of_range
        REQUIRE_THROWS_AS(train.getWagonByIndex(0), std::out_of_range);
    }
}
