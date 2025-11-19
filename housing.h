#ifndef HOUSING_H
#define HOUSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preferredLocation;
    int rentMax;
    int isQuiet;
} HousingPreferences;

typedef struct {
    char* semester;
} Availability;

typedef struct Message {
    int senderId;
    char* content;
    struct Message* next;
} Message;

typedef struct {
    int id;
    char* name;
    char* university;
    char* gender;
    HousingPreferences prefs;
    Availability availability;
    Message* messageQueue;
} User;

typedef struct {
    User** users;
    int userCount;
    int nextUserId;
} AppSystem;

void* safeMalloc(size_t size);
void* safeRealloc(void* ptr, size_t size);
char* readDynamicString();
void clearInputBuffer();

User* createUser(int id, char* name, char* university, char* gender,
                 char* semester, char* location, int rent, int quiet);
void freeUser(User* user);
User* findUserById(const AppSystem* system, int id);
void addUserToSystem(AppSystem* system, User* user);
void cleanupAndExit(AppSystem* system);

int calculateCompatibility(const User* user1, const User* user2);

Message* createMessage(int senderId, const char* content);
void addMessageToUser(User* receiver, Message* newMsg);
void freeMessageQueue(Message* head);

void printMainMenu();
int getMenuChoice();
User* promptForLogin(AppSystem* system);
void promptToCreateProfile(AppSystem* system);
void displayUserProfile(const User* user);
void displayMatches(const AppSystem* system, const User* currentUser);
void promptToSendMessage(AppSystem* system, int senderId);
void displayMessages(const User* user);

#endif
