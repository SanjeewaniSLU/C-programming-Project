#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROOMS 50        //maximum number of rooms
#define MAX_LEN_NAME 50     //maximum length for room name
#define SCALE 0.5           //scale for temperature bar graph

// structure for room data (room name and temperature)
typedef struct {
    char name_room[MAX_LEN_NAME];
    double temperature;
} room_data;

//function to convert a string into lowercase
void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
//function to print a bar graph based on room's temperature
void print_bar_graph(double temperature) {
    if (temperature < 0 || temperature > 30) {
        printf("X\n"); // if the temperature is out of range, print 'X'
    } else {
        int graph_length = (int)(temperature / SCALE); // calculate number of '-' characters
        for (int i = 0; i < graph_length; i++) {
            printf("-");
        }
    }
}

// function to print the temperature and corresponding bar graph for given room
void room_temp_print(room_data rooms[], int room_count, const char *name_room) { //checks the room name against the available rooms and print the temperature if found
    printf("\nTemperature in %s:\n", name_room);

    int print_count = 0;
    for (int i = 0; i < room_count; i++) {  // check all rooms to find a matching room name
        char temp_room[MAX_LEN_NAME];
        strcpy(temp_room, rooms[i].name_room);
        to_lower_case(temp_room); // convert room name to lowercase for comparison

        if (strcmp(temp_room, name_room) == 0) { // if room name matches,print its temperature
            printf("\n  %.1lf: ", rooms[i].temperature);
            print_bar_graph(rooms[i].temperature); // print the bar graph
            print_count++;
        }
    }

    if (print_count == 0) { // if no room is found,display an error message
        printf("\nError! Room '%s' is not found in the file.\n", name_room);
    }
}
//function to check if a room exists in the available rooms list
int room_exists(const char available_rooms[MAX_ROOMS][MAX_LEN_NAME], int available_count, const char *room_name) { // check if a room name exists in the available_rooms list .returns 1 if found,0 if not
    for (int j = 0; j < available_count; j++) {
        if (strcmp(available_rooms[j], room_name) == 0) {
            return 1; // room exists in the list
        }
    }
    return 0;  //room does not exist in the list
}
//function to display all available rooms without duplicating
void display_available_rooms(room_data rooms[], int room_count) {
    char available_rooms[MAX_ROOMS][MAX_LEN_NAME];
    int available_count = 0;

    printf("\nAvailable rooms:\n");

    for (int i = 0; i < room_count; i++) { // check all rooms for duplicating before displaying
        char temp_room[MAX_LEN_NAME];
        strcpy(temp_room, rooms[i].name_room);

        if (!room_exists(available_rooms, available_count, temp_room)) { // if the room is not already available in room list ,add it to list
            strcpy(available_rooms[available_count], temp_room);
            printf("  - %s\n", available_rooms[available_count]);
            available_count++;
        }
    }
}
// function to validate the user's input for the room name
int validate_input(char selected_room[], room_data rooms[], int room_count) { // returns 1 if valid input (room exists),2 if user types 'stop' and 0 if invalid
    to_lower_case(selected_room); // convert user input to lowercase

    if (strcmp(selected_room, "stop") == 0) {
        return 2;  //indicate the user wants to stop
    }

    if (strlen(selected_room) == 0) { // check for empty input
        printf("\nError! Room name cannot be empty. Please enter a valid input.\n");
        return 0;
    }

    for (int i = 0; i < room_count; i++) { // check all rooms and check if the input matches a room name
        char temp_room[MAX_LEN_NAME];
        strcpy(temp_room, rooms[i].name_room);
        to_lower_case(temp_room);

        if (strcmp(temp_room, selected_room) == 0) {
            return 1;// indicate room is found(valid input)
        }
    }

    printf("\nError! Room '%s' does not exist. Please enter a valid room name.\n", selected_room); // if no room matches the input, display an error message
    return 0;
}

int main() {
    room_data rooms[MAX_ROOMS]; // room data array
    FILE *file = fopen("Temperatures.csv", "r"); // open CSV file for reading
    if (file == NULL) {
        printf("\nError! Couldn't open the file.\n");
        return 1;
    }
    char line[100];
    int room_count = 0;
    fgets(line, sizeof(line), file); // skip the header line in the file

    while (fgets(line, sizeof(line), file)) { // read room data(temperature,room name) from each line in the CSV file
        if (sscanf(line, "%lf,%49[^\n]", &rooms[room_count].temperature, rooms[room_count].name_room) == 2) {//parse the line into temperature(double) and room name(string max 49 characters) and if successful returns 2
            room_count++;
            if (room_count >= MAX_ROOMS) { // check if the number of rooms exceeds the maximum allowed
                printf("\nError! Room limit is exceeded.\n");
                fclose(file); // close the file
                return 1; // return an error since the room list is exceeded
            }
        } else {
            printf("\nError! Invalid data format in the file.\n"); // if the lines can't be parsed into expected format,show an error message
            fclose(file); // close the file
            return 1; // return an error indicating invalid data
        }
    }
    fclose(file);  // close the file after reading

    char selected_room[MAX_LEN_NAME];
    int input_status = 0;

    display_available_rooms(rooms, room_count); // display available rooms to user

    do { // main input loop: keep asking for room name until 'stop' is entered by user
        printf("\nPlease enter the name of the room (or type 'stop' to exit): ");
        fgets(selected_room, MAX_LEN_NAME, stdin);
        selected_room[strcspn(selected_room, "\n")] = '\0'; // remove new line character

        input_status = validate_input(selected_room, rooms, room_count); // validate the user's input

        if (input_status == 1) { // if input is valid, print the room's temperature
            room_temp_print(rooms, room_count, selected_room);
        }

    } while (strcmp(selected_room, "stop") != 0); // continue until 'stop' is entered

    printf("\nExiting program.\n");
    return 0;
}
