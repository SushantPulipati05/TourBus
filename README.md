# TourBus

TourBus is a simple bus management system built in C++. It allows users to manage buses, book tickets, and handle customer data, providing functionalities to add, display, delete buses, and book tickets. It also supports ticket management for customers.

## Features

- Add new tour buses with details like ID, destination, time, and fare.
- Display details of all available buses or a specific bus by ID.
- Book tickets for a customer and store their details.
- Display all booked tickets.
- Delete a bus from the system or a specific customer ticket.

## Classes

- **TourBus**: Manages bus-related data like ID, destination, time, fare, and seat booking.
- **Ticket**: Manages customer data and associates it with a bus booking.

## Usage

### Compile the code:

```bash
g++ -o tourbus tourbus.cpp
