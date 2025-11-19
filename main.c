#include "housing.h"

int main() {
    // Initialize the system struct. No global variables.
    AppSystem system = {0}; // Zeros all fields
    system.nextUserId = 1; // Start user IDs from 1

    User* loggedInUser = NULL;
    int choice = 0;

    printf("Welcome to the Inter-University Housing Matcher!\n");

    while (1) {
        printMainMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1: // Create Profile
                promptToCreateProfile(&system);
                loggedInUser = NULL; // Force re-login
                break;
            case 2: // Log In
                loggedInUser = promptForLogin(&system);
                if (loggedInUser != NULL) {
                    printf("\nWelcome, %s!\n", loggedInUser->name);
                }
                break;
            case 3: // View My Profile
                if (loggedInUser) {
                    displayUserProfile(loggedInUser);
                } else {
                    printf("You must be logged in to view a profile.\n");
                }
                break;
            case 4: // Find Matches
                if (loggedInUser) {
                    displayMatches(&system, loggedInUser);
                } else {
                    printf("You must be logged in to find matches.\n");
                }
                break;
            case 5: // Send Message
                if (loggedInUser) {
                    promptToSendMessage(&system, loggedInUser->id);
                } else {
                    printf("You must be logged in to send messages.\n");
                }
                break;
            case 6: // View Messages
                if (loggedInUser) {
                    displayMessages(loggedInUser);
                } else {
                    printf("You must be logged in to view messages.\n");
                }
                break;
            case 7: // Exit
                cleanupAndExit(&system);
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 7.\n");
                break;
        }
    }

    // This line is unreachable due to cleanupAndExit()
    return 0;
}
