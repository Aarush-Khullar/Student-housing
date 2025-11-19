#include "housing.h"

void printMainMenu() {
    printf("\n--- Main Menu ---\n");
    printf("1. Create a new profile\n");
    printf("2. Log in with User ID\n");
    printf("3. View My Profile\n");
    printf("4. Find Matches\n");
    printf("5. Send a Message\n");
    printf("6. View My Messages\n");
    printf("7. Exit\n");
    printf("-------------------\n");
    printf("Enter your choice: ");
}

int getMenuChoice() {
    int choice = 0;
    if (scanf("%d", &choice) != 1) {
        choice = -1;
    }
    clearInputBuffer();
    return choice;
}

User* promptForLogin(AppSystem* system) {
    if (system->userCount == 0) {
        printf("No profiles exist yet. Please create one first.\n");
        return NULL;
    }

    int id;
    printf("Enter your User ID to log in: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID format.\n");
        return NULL;
    }
    clearInputBuffer();

    User* user = findUserById(system, id);
    if (user == NULL) {
        printf("Login failed: User ID %d not found.\n", id);
    }
    return user;
}

void promptToCreateProfile(AppSystem* system) {
    printf("--- Create New Profile ---\n");

    printf("Enter Name: ");
    char* name = readDynamicString();

    printf("Enter University: ");
    char* university = readDynamicString();

    printf("Enter Gender: ");
    char* gender = readDynamicString();

    printf("Enter Availability (e.g., Fall 2025): ");
    char* semester = readDynamicString();

    printf("Enter Preferred Location: ");
    char* location = readDynamicString();

    int rent, quiet;

    printf("Enter Max Rent (e.g., 500): ");
    while (scanf("%d", &rent) != 1 || rent <= 0) {
        printf("Invalid input. Please enter a positive number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    printf("Do you prefer a quiet environment? (1=Yes, 0=No): ");
    while (scanf("%d", &quiet) != 1 || (quiet != 0 && quiet != 1)) {
        printf("Invalid input. Please enter 0 or 1: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    User* newUser = createUser(system->nextUserId++, name, university, gender,
                               semester, location, rent, quiet);

    addUserToSystem(system, newUser);
    
    printf("Profile created successfully! Your User ID is: %d\n", newUser->id);
}

void displayUserProfile(const User* user) {
    if (user == NULL) return;

    printf("\n--- User Profile (ID: %d) ---\n", user->id);
    printf("Name:         %s\n", user->name);
    printf("University:   %s\n", user->university);
    printf("Gender:       %s\n", user->gender);
    printf("Availability: %s\n", user->availability.semester);

    printf("\n--- Preferences ---\n");
    printf("Location:     %s\n", user->prefs.preferredLocation);
    printf("Max Rent:     %d\n", user->prefs.rentMax);
    printf("Quiet Env:    %s\n", user->prefs.isQuiet ? "Yes" : "No");
    printf("-------------------------\n");
}

void displayMatches(const AppSystem* system, const User* currentUser) {
    printf("\n--- Finding Matches for %s (ID: %d) ---\n", currentUser->name, currentUser->id);

    int matchFound = 0;

    for (int i = 0; i < system->userCount; i++) {
        User* potentialMatch = system->users[i];

        if (potentialMatch->id == currentUser->id)
            continue;

        int score = calculateCompatibility(currentUser, potentialMatch);

        if (score > 50) {
            matchFound = 1;
            printf("  -> Match Found! (Score: %d/80)\n", score);
            displayUserProfile(potentialMatch);
        }
    }

    if (!matchFound) {
        printf("Sorry, no high-compatibility matches found at this time.\n");
    }
}

void promptToSendMessage(AppSystem* system, int senderId) {
    printf("Enter the User ID you want to message: ");
    int receiverId;
    if (scanf("%d", &receiverId) != 1) {
         printf("Invalid ID.\n");
         clearInputBuffer();
         return;
    }
    clearInputBuffer();
    
    if (receiverId == senderId) {
        printf("You cannot message yourself.\n");
        return;
    }

    User* receiver = findUserById(system, receiverId);
    if (receiver == NULL) {
        printf("Error: User with ID %d not found. Message not sent.\n", receiverId);
        return;
    }
    
    printf("Enter your message for %s (ID: %d):\n> ", receiver->name, receiverId);
    char* content = readDynamicString();
    if (content == NULL) {
         printf("Error reading message. Sending cancelled.\n");
         return;
    }

    Message* newMsg = createMessage(senderId, content);
    free(content);
    
    addMessageToUser(receiver, newMsg);

    printf("Message sent successfully to %s!\n", receiver->name);
}

void displayMessages(const User* user) {
    printf("\n--- %s's Inbox ---\n", user->name);
    
    if (user->messageQueue == NULL) {
        printf("Your inbox is empty.\n");
        return;
    }

    Message* current = user->messageQueue;
    int count = 1;

    while (current != NULL) {
        printf("Message %d (From ID: %d):\n", count++, current->senderId);
        printf("  \"%s\"\n\n", current->content);
        current = current->next;
    }
}
