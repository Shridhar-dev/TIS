# Travel Information System - OOPS Project

## Overview

The Travel Information System is a C++ application designed to manage traveler information for a travel agency or similar organization. It allows users to create, edit, and retrieve traveler records, storing the information in individual text files.

## Features

1. Create new traveler records
2. Edit traveler age
3. Append travel mode to existing records
4. Search for travelers by start or end date of travel
5. Persistent storage of traveler information in text files
6. Unique ID generation for each traveler

## Requirements
- Preferred C++17 or later (for older compilers, check [compatibility](#compatibility) section)

## Compatibility
To make sure the program works on the older C++ compilers, we have also included filesystem.hpp file created by [Steffen Schümann](https://github.com/gulrak).

Filesystem library repo [here](https://github.com/gulrak/filesystem)

Version used: v1.5.14

Tested on:
- g++ (GCC) 6.3.0


## Usage

In bash
```bash
g++ project.cpp -o project && ./project
```
Or in Command Prompt
```cmd
g++ project.cpp -o project && project
```

The program will present a menu with the following options:

1. Enter traveller details
2. Edit traveller age
3. Append travel mode
4. Get travellers by date
5. Exit

Follow the on-screen prompts to navigate through the system and manage traveler information.

## File Structure
- fs    
    -  `filesystem.hpp`: Includes the filesystem library by [Steffen Schümann](https://github.com/gulrak)
- `project.cpp`: Contains the entire source code for the Travel Information System
- `project-compatibility.cpp`: Contains the entire source code for the Travel Information System with compatibility with older C++ compilers
- `state.txt`: Stores the current counter value for generating unique traveler IDs (generated during runtime if not already present)
- `T_<name><id>.txt`: Individual traveler files, where `<name>` is the traveler's name and `<id>` is a unique identifier (generated during runtime if not already present)

## Classes and Functions

### Traveller Class

The `Traveller` class represents a traveler and includes the following information:
- Name
- Age
- Travel dates (start and end)
- Destination address
- Travel mode
- Unique ID

### Main Functions

- `createTravellerFile()`: Creates a new traveler record
- `editTravellerAge()`: Modifies the age of an existing traveler
- `appendTravelMode()`: Adds or updates the travel mode for a traveler
- `getTravellersByDate()`: Searches for travelers based on their start or end travel date

## Error Handling

The system includes basic error handling for file operations and user input validation. Errors are reported to the console.

## Contributers
- Shridhar Kamat - [GitHub](https://github.com/Shridhar-dev)
- Shikhaa Prabhudesai
- Shivam Naik
- Shivam Chandekar
- Vaishnavi Revankar
- Shivaji Naik 

## License

This project is open-source and available under the MIT License.