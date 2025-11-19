#include "housing.h"

void* safeMalloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed (malloc).\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* safeRealloc(void* ptr, size_t size) {
    void* newPtr = realloc(ptr, size);
    if (newPtr == NULL && size > 0) {
        fprintf(stderr, "Error: Memory reallocation failed (realloc).\n");
        free(ptr);
        exit(EXIT_FAILURE);
    }
    return newPtr;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* readDynamicString() {
    char* line = NULL;
    char buffer[128];
    size_t currentSize = 0;

    line = (char*)safeMalloc(1);
    line[0] = '\0';

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        size_t chunkLen = strlen(buffer);
        line = (char*)safeRealloc(line, currentSize + chunkLen + 1);
        strcat(line, buffer);
        currentSize += chunkLen;

        if (line[currentSize - 1] == '\n') {
            line[currentSize - 1] = '\0';
            break;
        }
    }

    return line;
}

User* createUser(int id, char* name, char* university, char* gender,
                 char* semester, char* location, int rent, int quiet)
{
    User* newUser = (User*)safeMalloc(sizeof(User));
    newUser->id = id;
    newUser->messageQueue = NULL;

    newUser->name = name;
    newUser->university = university;
    newUser->gender = gender;
    newUser->availability.semester = semester;
    newUser->prefs.preferredLocation = location;

    newUser->prefs.rentMax = rent;
    newUser->prefs.isQuiet = quiet;

    return newUser;
}

void addUserToSystem(AppSystem* system, User* user) {
    system->users = (User**)safeRealloc(system->users, 
                       (system->userCount + 1) * sizeof(User*));
    system->users[system->userCount] = user;
    system->userCount++;
}

User* findUserById(const AppSystem* system, int id) {
    for (int i = 0; i < system->userCount; i++) {
        if (system->users[i]->id == id) {
            return system->users[i];
        }
    }
    return NULL;
}

void freeUser(User* user) {
    if (user == NULL) return;

    free(user->name);
    free(user->university);
    free(user->gender);
    free(user->availability.semester);
    free(user->prefs.preferredLocation);
    freeMessageQueue(user->messageQueue);
    free(user);
}

void cleanupAndExit(AppSystem* system) {
    for (int i = 0; i < system->userCount; i++) {
        freeUser(system->users[i]);
    }
    free(system->users);
    exit(EXIT_SUCCESS);
}

int calculateCompatibility(const User* user1, const User* user2) {
    if (user1->id == user2->id) return 0;

    if (strcmp(user1->university, user2->university) != 0)
        return 0;

    int score = 0;

    if (strcmp(user1->availability.semester, user2->availability.semester) != 0)
        return 0;

    score += 30;

    if (strcmp(user1->prefs.preferredLocation, user2->prefs.preferredLocation) == 0)
        score += 10;

    if (user1->prefs.isQuiet == user2->prefs.isQuiet)
        score += 20;

    if (strcmp(user1->gender, user2->gender) == 0)
        score += 20;

    if (score > 80) score = 80;

    return score;
}

Message* createMessage(int senderId, const char* content) {
    Message* msg = (Message*)safeMalloc(sizeof(Message));
    msg->senderId = senderId;
    msg->next = NULL;

    msg->content = (char*)safeMalloc(strlen(content) + 1);
    strcpy(msg->content, content);

    return msg;
}

void addMessageToUser(User* receiver, Message* newMsg) {
    newMsg->next = receiver->messageQueue;
    receiver->messageQueue = newMsg;
}

void freeMessageQueue(Message* head) {
    Message* current = head;
    Message* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->content);
        free(temp);
    }
}
