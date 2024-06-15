Client-Server-Booking-Application
This repository contains a client-server application for booking movie tickets using shared memory and semaphores on Linux.

Server Code
File: server.cpp
Description:
The server manages movie ticket bookings.
It reads available tickets from movieinfo.txt and updates the booking status in bookinginfo.txt.
It uses shared memory and semaphores for inter-process communication and synchronization.
Upon booking confirmation from the client, it updates the ticket count and stores booking information.

Client Code
File: client.cpp
Description:
The client interacts with the server to book movie tickets.
It allows users to select a movie and specify the number of tickets.
After confirming the booking, it calculates the bill and prompts the user for further actions.
It uses shared memory and semaphores to communicate with the server regarding booking details and confirmation.
Instructions:
1. Setup:
   Ensure you have the necessary libraries (pthread, semaphore.h) installed.
   Compile the server and client codes separately using g++ -o server server.cpp -lpthread -lrt and g++ -o client 
   client.cpp -lpthread -lrt
   
2. Execution:
   Run the server executable: ./server.
   Run the client executable: ./client.
   Follow the prompts on the client interface to book tickets and view billing information.

Files:

server.cpp: Contains the server-side logic for managing movie bookings.
client.cpp: Implements the client-side interface for users to interact with the booking system.
movieinfo.txt: Stores movie information including available tickets.
bookinginfo.txt: Logs booking information.

Important Notes:
Initialize the movieinfo.txt file with 0 to show 0 bookings.
Ensure proper file permissions for movieinfo.txt and bookinginfo.txt to read from and write to.
The system utilizes shared memory and semaphores for communication, ensuring synchronization between client and server processes.
