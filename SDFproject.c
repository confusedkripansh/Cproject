#include <stdio.h>
// Tempo Library File//
#include <stdlib.h>
// Standard Library File//
#include <string.h>
// Library File to perform functions on string//
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
// Additional Library Files to use different tools//
    
#define depends 0
// Define Limit of varible depends //
#define MAX_CUSTOMERS 100
// Define Limit by MAX_CUSTOMERS//
#define MAX_NAME_LENGTH 50
// Define limit by MAX_NAME_LENGTH//
#define MAX_CONTACT_LENGTH 15
// Define limit by MAX_CONTACT_LENGTH//
#define MAX_ADDRESS_LENGTH 100
// Define limit by MAX_ADDRESS_LENGTH//
#define MAX_HISTORY_LENGTH 1000
// Define limit by MAX_HISTORY_LENGTH//
    
/* The program is divided into three parts-:
 1) Customer Management
2) Service Management 
3) Billing System */

// Service Management Structure
typedef struct {
    char serviceName[30];
    int cost;
    int hours;
} Service;

// Customer Structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char contact[MAX_CONTACT_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char service_history[MAX_HISTORY_LENGTH];
} Customer;

// Customer Management Structure
typedef struct {
    Customer customers[MAX_CUSTOMERS];
    int total_customers;
} CustomerManager;

// Utility Function of trim the space of the string//
void trim_whitespace(char* str) {
    int start = 0, end = strlen(str) - 1;
    while (isspace(str[start])) start++;
    while (end >= start && isspace(str[end])) end--;
    int j = 0;
    for (int i = start; i <= end; i++) {
        str[j++] = str[i];
    }
    str[j] = '\0';
}

// void function to the capitalise the first letter of the name of the person entered in the string//
void capitalize_name(char* str) {
    bool capitalize_next = true;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            str[i] = capitalize_next ? toupper(str[i]) : tolower(str[i]);
            capitalize_next = false;
        } else if (isspace(str[i])) {
            capitalize_next = true;
        }
    }
}

// Customer Management Function//
// Argument is a pointer to a structure of the name customer manager by the name manager //
void initialize_customer_manager(CustomerManager* manager) {
    manager->total_customers = 0;
}

// A boolean function to check if the customer is a duplicate customer or name //
// If the person A is an existing customer, the function returns true else false //
bool is_duplicate_customer(CustomerManager* manager, const char* name, const char* contact) {
    for (int i = 0; i < manager->total_customers; i++) {
        if (strcmp(manager->customers[i].name, name) == 0 && 
            strcmp(manager->customers[i].contact, contact) == 0) {
            return true;
        }
    }
    return false;
}

// Important function to add the details of a new customer in the customer management customer //

int add_customer(CustomerManager* manager, const char* name, const char* contact, const char* address) {
    if (!name || !contact || !address || strlen(name) == 0 || strlen(contact) == 0 || strlen(address) == 0) {
        printf("Invalid input. All fields are required.\n");
        return -1;
    }
// if any field is unfilled by the user, the program displays an error message of all fields are required //
// Initially we defined max limit of customer count, if total customers exceeeds MAX CUSTOMERS, the limit of program is reached 
    
    if (manager->total_customers >= MAX_CUSTOMERS) {
        printf("Customer list is full.\n");
        return -1;
    }

  // If the customer exists in the directory of the structure, the program returns customer already exists //  

    if (is_duplicate_customer(manager, name, contact)) {
        printf("Customer already exists.\n");
        return -1;
    }

// If all details are correct, the input of address, name and number taken by the user are passes on to the strucure //
    
    Customer* new_customer = &manager->customers[manager->total_customers];
    new_customer->id = manager->total_customers + 1;
    strncpy(new_customer->name, name, MAX_NAME_LENGTH - 1);
    strncpy(new_customer->contact, contact, MAX_CONTACT_LENGTH - 1);
    strncpy(new_customer->address, address, MAX_ADDRESS_LENGTH - 1);

    new_customer->name[MAX_NAME_LENGTH - 1] = '\0'; 
    // append null character in the name string//
    new_customer->contact[MAX_CONTACT_LENGTH - 1] = '\0';
    // append null character in the contact array//
    new_customer->address[MAX_ADDRESS_LENGTH - 1] = '\0';
    // append null character in the address string//
    strcpy(new_customer->service_history, "");

    manager->total_customers++;
    // increase the count of the total customers in the directory by incremenet operator //
    printf("Customer added successfully. ID: %d\n", new_customer->id);
    return new_customer->id;
}

// an important function to update the information of a previously registered customer in the strucure //

bool update_customer(CustomerManager* manager, int customer_id, const char* name, const char* contact, const char* address) {
    if (customer_id < 1 || customer_id > manager->total_customers) {
        printf("Invalid customer ID.\n");
        return false;
    } 
    // return false if the customer id does not exist in the directory of the strucure //

    Customer* customer = &manager->customers[customer_id - 1];
    if (name && strlen(name) > 0) {
        strncpy(customer->name, name, MAX_NAME_LENGTH - 1);
        customer->name[MAX_NAME_LENGTH - 1] = '\0';
        // append null chracter at the end of the string //
    }
    if (contact && strlen(contact) > 0) {
        strncpy(customer->contact, contact, MAX_CONTACT_LENGTH - 1);
        customer->contact[MAX_CONTACT_LENGTH - 1] = '\0';
        // append null character at the end of the array //
    }
    if (address && strlen(address) > 0) {
        strncpy(customer->address, address, MAX_ADDRESS_LENGTH - 1);
        customer->address[MAX_ADDRESS_LENGTH - 1] = '\0';
        // append null character at the end of the string //
    }

    printf("Customer updated successfully.\n");
    return true;
}

// An important function to delete the details of an existing customer in the directory of the strucure //

bool delete_customer(CustomerManager* manager, int customer_id) {
    if (customer_id < 1 || customer_id > manager->total_customers) {
        printf("Invalid customer ID.\n");
        return false;
    } // if the customer id does not exist, it prints an error message //

    for (int i = customer_id - 1; i < manager->total_customers - 1; i++) {
        manager->customers[i] = manager->customers[i + 1];
        manager->customers[i].id = i + 1;
    } // loop to left shift the details of the customers which deletes the details of the customer (i) //

    manager->total_customers--;
    // decrement operator to reduce the number of total customers //
    printf("Customer deleted successfully.\n");
    return true;
}

// Function to view the service history of an existing customer in the directory of the strucure //

void view_service_history(CustomerManager* manager, int customer_id) {
    if (customer_id < 1 || customer_id > manager->total_customers) {
        printf("Invalid customer ID.\n");
        return;
    }  // if the customer id does not exist, it prints an error message //

    Customer* customer = &manager->customers[customer_id - 1];
    printf("\nService History for %s:\n%s\n", customer->name, 
           strlen(customer->service_history) > 0 ? customer->service_history : "No history available.");
    // Conditional operator which prints no history available if the service history integer in the strucure has 0 value //
}

// A function to display the total number of customers in the directory of the strucure //
void display_customers(CustomerManager* manager) {
    if (manager->total_customers == 0) {
        printf("No customers found.\n");
        return; 
    } // If the total customers are 0, no customer found is displayed //

    printf("\nCustomer List:\n");
    printf("%-5s %-25s %-15s %-30s\n", "ID", "Name", "Contact", "Address");
    printf("-------------------------------------------------------------\n");

    // Printing format of the display of the customer list//
    // Loop to print the details of each customer //
    
    for (int i = 0; i < manager->total_customers; i++) {
        Customer* c = &manager->customers[i];
        printf("%-5d %-25s %-15s %-30s\n", c->id, c->name, c->contact, c->address);
    }
}


// Service-related functions
void displayServices(Service services[], int size) {
    printf("\nAvailable services:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s (Cost: $%d, Time: %d hours)\n", 
               i + 1, services[i].serviceName, services[i].cost, services[i].hours);
    }
}

// Display the sub categories of the car wash options //
void displayCarWashOptions(Service carWashOptions[], int size) {
    printf("\nCar Wash Options:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s (Cost: $%d, Time: %d hours)\n", 
               i + 1, carWashOptions[i].serviceName, carWashOptions[i].cost, carWashOptions[i].hours);
    }
}

void update_service_history(Customer* customer, const char* vehicleType, 
                          Service* services, int numServices, int totalCost, int totalTime) {
    char new_entry[200];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", tm);
    
    snprintf(new_entry, sizeof(new_entry), 
             "\nDate: %s\nVehicle Type: %s\nServices: ", date, vehicleType);
    
    size_t current_len = strlen(customer->service_history);
    size_t remaining_space = MAX_HISTORY_LENGTH - current_len - 1;
    
    strncat(customer->service_history, new_entry, remaining_space);
    
    for (int i = 0; i < numServices; i++) {
        char service_entry[50];
        snprintf(service_entry, sizeof(service_entry), "%s ($%d), ", 
                services[i].serviceName, services[i].cost);
        
        remaining_space = MAX_HISTORY_LENGTH - strlen(customer->service_history) - 1;
        if (remaining_space <= 0) break;
        
        strncat(customer->service_history, service_entry, remaining_space);
    }
    
    char summary[100];
    snprintf(summary, sizeof(summary), 
             "\nTotal Cost: $%d, Total Time: %d hours\n------------------------\n", 
             totalCost, totalTime);
    
    remaining_space = MAX_HISTORY_LENGTH - strlen(customer->service_history) - 1;
    if (remaining_space > 0) {
        strncat(customer->service_history, summary, remaining_space);
    }
}

void vehicleService(CustomerManager* manager, int customer_id) {
    if (customer_id < 1 || customer_id > manager->total_customers) {
        printf("Invalid customer ID.\n");
        return;
    }

    Customer* customer = &manager->customers[customer_id - 1];

    // Define services for each vehicle type
    Service suvServices[] = {
        {"Car Wash", depends, depends},
        {"Regular Service", 200, 5},
        {"AC Repair", 150, 3},
        {"Denting", 300, 7},
        {"Paint Job", 500, 10},
        {"Headlight Replacement", 100, 2},
        {"Tail Light Replacement", 90, 2}
    };

    Service sedanServices[] = {
        {"Car Wash", depends, depends},
        {"Regular Service", 180, 4},
        {"AC Repair", 120, 2},
        {"Denting", 250, 6},
        {"Paint Job", 400, 8},
        {"Headlight Replacement", 90, 2},
        {"Tail Light Replacement", 80, 2}
    };

    Service hatchbackServices[] = {
        {"Car Wash", depends, depends},
        {"Regular Service", 150, 3},
        {"AC Repair", 100, 2},
        {"Denting", 200, 5},
        {"Paint Job", 300, 6},
        {"Headlight Replacement", 80, 1},
        {"Tail Light Replacement", 70, 1}
    };

    Service carWashOptionsSUV[] = {
        {"Deep Cleaning Wash", 70, 3},
        {"Normal Wash", 50, 2}
    };

    Service carWashOptionsSedan[] = {
        {"Deep Cleaning Wash", 60, 2},
        {"Normal Wash", 40, 1}
    };

    Service carWashOptionsHatchback[] = {
        {"Deep Cleaning Wash", 50, 2},
        {"Normal Wash", 30, 1}
    };

    // Declaring a string of name vehicle type to allow the user to enter one of the three vehicle types//
    char vehicleType[20];
    printf("\nCustomer: %s\n", customer->name);
    printf("Enter vehicle type (SUV/SEDAN/HATCHBACK): ");
    scanf("%s", vehicleType);
    // Scanning the string//
    getchar(); // Clear buffer of the input
    
    /* We have type defined a structure in the start with the definition service and now we declare two structure variable
       to input the services the user wants and type of car wash he wants */
      
    Service *selectedServices;
    Service *selectedCarWashOptions;
    int serviceCount;
    int carWashOptionCount;

    if (strcasecmp(vehicleType, "SUV") == 0) {
        selectedServices = suvServices;
    // If the vehicle type entered by the user is SUV the selected services displayed is the type of SUV//
        selectedCarWashOptions = carWashOptionsSUV;
        serviceCount = 7;
        carWashOptionCount = 2;

        // Number of Car wash options and services are predefined //
    } else if (strcasecmp(vehicleType, "SEDAN") == 0) {
        selectedServices = sedanServices;
        // If the vehicle type entered by the user is Sedan the selected services displayed is the type of Sedan//
        selectedCarWashOptions = carWashOptionsSedan;
        serviceCount = 7;
        carWashOptionCount = 2;
        // Number of Car wash options and services are predefined //
    } else if (strcasecmp(vehicleType, "HATCHBACK") == 0) {
        selectedServices = hatchbackServices;
        selectedCarWashOptions = carWashOptionsHatchback;
        // If the vehicle type entered by the user is hatchback the selected services displayed is the type of hatchback//
        serviceCount = 7;
        carWashOptionCount = 2;
        // Number of Car wash options and services are predefined //
    } else {
        printf("\nService not available for the entered vehicle type.\n");
        return;
        // IF the car type entered by the user is not available, the above message is displayed//
    }

    displayServices(selectedServices, serviceCount);
   // Calling the Display Services Function and passes the integer selected services and service count as paramateres//
    int choices[7];
    // An array to input the number of services the person wants //
    int carWashChoice = 0;
    int numChoices;
    // Storing the number of choices the person wants//
    printf("\nHow many services would you like to choose? (Max 7): ");
    scanf("%d", &numChoices);

    // An if statement if the number of choices is less than 1 or greater than 7, an error mesage is displayed and the person is redirected back//

    if (numChoices < 1 || numChoices > 7) {
        printf("\nInvalid number of services. Please choose between 1 and 7.\n");
        return;
    }

    printf("\nEnter the numbers corresponding to the services you want, separated by spaces: ");
    for (int i = 0; i < numChoices; i++) {
        scanf("%d", &choices[i]);
    }

    Service selectedServicesList[7];
    int selectedServicesCount = 0;
    int totalCost = 0, totalTime = 0;
    // Initialised two varibles to calculat the total cost and total time of the service //

   // Printing the services selected by the user //
    printf("\nSelected services:\n");
    for (int i = 0; i < numChoices; i++) {
        int choice = choices[i];
        if (choice >= 1 && choice <= serviceCount) {
            if (strcmp(selectedServices[choice - 1].serviceName, "Car Wash") == 0) {
                // If the person selects selected services choice-1, he will be displayed the suboptions for car wash //
                displayCarWashOptions(selectedCarWashOptions, carWashOptionCount);
                printf("\nChoose Car Wash option: ");
                scanf("%d", &carWashChoice);
                // Scanning the preferred cash wash option //
                if (carWashChoice >= 1 && carWashChoice <= carWashOptionCount) {
                    Service selectedCarWash = selectedCarWashOptions[carWashChoice - 1];
                    printf("- %s (Cost: $%d, Time: %d hours)\n", 
                           selectedCarWash.serviceName, selectedCarWash.cost, selectedCarWash.hours);
                    totalCost += selectedCarWash.cost;
                    // Calculating the total cost after considering the car wash type //
                    totalTime += selectedCarWash.hours;
                   // Calculating the total time after considering the car wash type //
                    selectedServicesList[selectedServicesCount++] = selectedCarWash;
                    
                }
            } else {
                Service selectedService = selectedServices[choice - 1];
                // If the person does not select the car wash option, he will not be displayed the subchoices//
                printf("- %s (Cost: $%d, Time: %d hours)\n", 
                       selectedService.serviceName, selectedService.cost, selectedService.hours);
                totalCost += selectedService.cost;
                // Calculating the total cost after considering the service type //
                totalTime += selectedService.hours;
                // Calculating the total time after considering the service type //
                selectedServicesList[selectedServicesCount++] = selectedService;
            }
        }
    }

    // Apply discount if total cost of the service exceeds $500
    if (totalCost > 500) {
        int discount = totalCost * 0.1;
        printf("\nApplying 10%% discount: -$%d\n", discount);
        totalCost -= discount;
        // Store the new value in total cost varible//
    }

    // Print bill
    printf("\n------------------------------------------------------------\n");
    printf("                    CAR WORKSHOP BILL\n");
    printf("------------------------------------------------------------\n");
    printf("Customer Name: %s\n", customer->name);
    printf("Vehicle Type: %s\n", vehicleType);
    printf("------------------------------------------------------------\n");
    printf("| %-30s | %-8s | %-12s |\n", "Service Name", "Cost ($)", "Time (hours)");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < selectedServicesCount; i++) {
        printf("| %-30s | %-8d | %-12d |\n",
               selectedServicesList[i].serviceName, 
               selectedServicesList[i].cost, 
               selectedServicesList[i].hours);
    }

    printf("------------------------------------------------------------\n");
    printf("| %-30s | %-8d |              |\n", "Total Cost:", totalCost);
    printf("| %-30s | %-8d |              |\n", "Total Time:", totalTime);
    printf("------------------------------------------------------------\n");

    // Update service history
    update_service_history(customer, vehicleType, selectedServicesList, 
                         selectedServicesCount, totalCost, totalTime);
}

void displayMainMenu() {
    printf("\nCar Workshop Management System\n");
    printf("1. Customer Management\n");
    printf("2. Vehicle Service\n");
    printf("3. Exit\n");
}

void displayCustomerMenu() {
    printf("\nCustomer Management\n");
    printf("1. Add Customer\n");
    printf("2. Update Customer\n");
    printf("3. Delete Customer\n");
    printf("4. View Service History\n");
    printf("5. Display Customers\n");
    printf("6. Back to Main Menu\n");
}

int main() {
    CustomerManager manager;
    initialize_customer_manager(&manager);
    
    int main_choice, sub_choice;
    do {
        displayMainMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &main_choice);
        getchar();

        switch (main_choice) {
            case 1: // Customer Management
                do {
                    displayCustomerMenu();
                    printf("\nEnter your choice: ");
                    scanf("%d", &sub_choice);
                    getchar();

                    switch (sub_choice) {
                        case 1: {
                            char name[MAX_NAME_LENGTH], contact[MAX_CONTACT_LENGTH], 
                                 address[MAX_ADDRESS_LENGTH];
                            
                            printf("\nEnter Customer Name: ");
                            fgets(name, MAX_NAME_LENGTH, stdin);
                            name[strcspn(name, "\n")] = '\0';
                            
                            printf("Enter Contact Number: ");
                            fgets(contact, MAX_CONTACT_LENGTH, stdin);
                            contact[strcspn(contact, "\n")] = '\0';
                            
                            printf("Enter Address: ");
                            fgets(address, MAX_ADDRESS_LENGTH, stdin);
                            address[strcspn(address, "\n")] = '\0';
                            
                            add_customer(&manager, name, contact, address);
                            break;
                        }
                        case 2: {
                            int customer_id;
                            char name[MAX_NAME_LENGTH], contact[MAX_CONTACT_LENGTH], 
                                 address[MAX_ADDRESS_LENGTH];

                            display_customers(&manager);
                            printf("\nEnter Customer ID to update: ");
                            scanf("%d", &customer_id);
                            getchar();

                            printf("Enter New Name (or press Enter to skip): ");
                            fgets(name, MAX_NAME_LENGTH, stdin);
                            name[strcspn(name, "\n")] = '\0';

                            printf("Enter New Contact (or press Enter to skip): ");
                            fgets(contact, MAX_CONTACT_LENGTH, stdin);
                            contact[strcspn(contact, "\n")] = '\0';

                            printf("Enter New Address (or press Enter to skip): ");
                            fgets(address, MAX_ADDRESS_LENGTH, stdin);
                            address[strcspn(address, "\n")] = '\0';

                            update_customer(&manager, customer_id, 
                                         strlen(name) > 0 ? name : NULL,
                                         strlen(contact) > 0 ? contact : NULL,
                                         strlen(address) > 0 ? address : NULL);
                            break;
                        }
                        case 3: {
                            int customer_id;
                            display_customers(&manager);
                            printf("\nEnter Customer ID to delete: ");
                            scanf("%d", &customer_id);
                            delete_customer(&manager, customer_id);
                            break;
                        }
                        case 4: {
                            int customer_id;
                            display_customers(&manager);
                            printf("\nEnter Customer ID to view service history: ");
                            scanf("%d", &customer_id);
                            view_service_history(&manager, customer_id);
                            break;
                        }
                        case 5:
                            display_customers(&manager);
                            break;
                        case 6:
                            printf("\nReturning to main menu...\n");
                            break;
                        default:
                            printf("\nInvalid choice. Please try again.\n");
                    }
                } while (sub_choice != 6);
                break;

            case 2: // Vehicle Service
                if (manager.total_customers == 0) {
                    printf("\nNo customers registered. Please add a customer first.\n");
                } else {
                    display_customers(&manager);
                    int customer_id;
                    printf("\nEnter Customer ID for service: ");
                    scanf("%d", &customer_id);
                    vehicleService(&manager, customer_id);
                }
                break;

            case 3:
                printf("\nThank you for using Car Workshop Management System!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (main_choice != 3);

    return 0;
}
