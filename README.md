
*This project has been created as part of the 42 curriculum by mnasimi.*

# Minitalk

## Description

`minitalk` is a small client/server communication project using only UNIX signals.

The goal is to send a message from a **client** process to a **server** process using:

- `SIGUSR1`
- `SIGUSR2`

The server starts first and prints its **PID**.  
Then the client uses that PID to send a string to the server.

In this implementation:

- each character is sent **bit by bit**
- `SIGUSR1` represents bit `1`
- `SIGUSR2` represents bit `0`
- bits are sent from the **least significant bit** to the **most significant bit**
- after each bit, the server sends an **acknowledgment** signal back to the client
- when the full message is finished, the client sends `'\0'`
- when the server receives `'\0'`, it prints a new line

This acknowledgment system makes the transmission more reliable because the client waits for confirmation before sending the next bit.

---

## Files

- `server.c`  
  Starts the server, prints its PID, receives signals, rebuilds characters, and prints the received message.

- `client.c`  
  Sends the message to the server bit by bit and waits for acknowledgment after each signal.

- `util.c`  
  Contains helper functions:
  - `ft_atoi`
  - `ft_get_pid`
  - `ft_init_client_signals`

- `minitalk.h`  
  Header file containing prototypes and required includes.

- `Makefile`  
  Compiles the project and creates:
  - `server`
  - `client`

---

## How the program works

### Server side

The server:

1. prints its PID
2. waits for incoming signals
3. receives one signal per bit
4. rebuilds one character after 8 bits
5. writes the character to standard output
6. sends `SIGUSR1` back to the client as acknowledgment

The server uses `sigaction` with `SA_SIGINFO` to know **which client sent the signal**.

### Client side

The client:

1. checks the number of arguments
2. checks that the PID is valid
3. installs a signal handler for acknowledgment
4. sends each character bit by bit
5. waits after each bit until the server confirms reception
6. sends `'\0'` at the end of the message

---

## Instructions

### Compilation

To compile the project:

```bash
make
```

This creates two executables:

* `server`
* `client`

### Clean object files

```bash
make clean
```

### Clean everything

```bash
make fclean
```

### Recompile everything

```bash
make re
```

---

## Execution

### 1. Start the server

```bash
./server
```

Example output:

```bash
12345
```

This number is the server PID.

### 2. Start the client

Open another terminal and run:

```bash
./client 12345 "Hello from client"
```

The server will display:

```bash
Hello from client
```

---

## Example session

Terminal 1:

```bash
$ ./server
4242
Hello 42
```

Terminal 2:

```bash
$ ./client 4242 "Hello 42"
```

---

## Communication protocol

For each character:

1. the client reads one character
2. the client sends 8 signals
3. for each bit:

   * `SIGUSR1` if the bit is `1`
   * `SIGUSR2` if the bit is `0`
4. the server receives the signal and stores the bit
5. the server sends back `SIGUSR1` as acknowledgment
6. the client waits for this acknowledgment before continuing

At the end of the message, the client sends the null character `'\0'`, which tells the server that the transmission is finished.

---

## Error management

This project includes basic error handling:

### Client

* wrong number of arguments
  prints:

  ```text
  Usage: ./client <PID> <MESSAGE>
  ```

* invalid PID or unreachable process
  prints:

  ```text
  Invalid PID
  ```

* failure while sending a signal
  prints:

  ```text
  Failed to send signal
  ```

* `sigaction` failure
  prints:

  ```text
  sigaction error
  ```

### Server

* wrong usage
  prints:

  ```text
  Wrong usage
  ```

* `sigaction` failure
  prints:

  ```text
  sigaction error
  ```

---

## Technical notes

* The project uses only UNIX signals for communication.
* The server reconstructs characters using bit operations.
* The client uses a global variable of type `volatile sig_atomic_t` to detect acknowledgment safely inside the signal handler.
* The server resets its current byte construction correctly when a new client PID is detected.
* The message is displayed directly on standard output.

---

## Makefile rules

Available rules:

* `make`
* `make clean`
* `make fclean`
* `make re`

---

## Limitations

This implementation is designed for the mandatory part of the project.

Notes:

* it sends standard byte-based characters
* it relies on acknowledgments to improve synchronization
* simultaneous communication from multiple clients is not the main target of this simple version

---

## Resources

The following resources were used to understand and build the project:

* `man 2 kill`
* `man 2 sigaction`
* `man 2 pause`
* `man 3 usleep`
* 42 subject and course materials
* personal testing in terminal

### AI usage

AI was used only as a **learning and writing assistant**, not as a replacement for understanding the code.

It was used for:

* improving the wording and structure of the `README.md`
* correcting grammar and presentation
* helping explain the signal flow in simple words

AI was **not used to blindly generate and submit the project without understanding**.
The project logic, file structure, and behavior are based on the actual code written for this repository.

---

## Author

* **Login:** `mnasimi`
* **Project:** `minitalk`
* **School:** 42

```

I can also make you a second version that is even more “42-evaluator style” and shorter, if you want.
```
