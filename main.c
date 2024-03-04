#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>

// Function to set terminal attributes
void set_terminal_attributes() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Signal handler for SIGINT (Ctrl+C)
void sigint_handler(int sig) {
    // Do nothing here
}

// Signal handler for SIGQUIT (Ctrl+\)
void sigquit_handler(int sig) {
    // Do nothing here
}

// Signal handler for SIGTSTP (Ctrl+Z)
void sigtstp_handler(int sig) {
    // Do nothing here
}

int main() {
    // Set terminal attributes
    set_terminal_attributes();

    // Register signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGTSTP, sigtstp_handler);

    // Your program logic goes here
    // For demonstration, let's have a simple loop to read input indefinitely
    while (1) {
        char c = getchar(); // Read a character from stdin
        // Handle the input character as needed
        printf("You entered: %c\n", c);
    }

    return 0;
}
