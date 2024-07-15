/* Author: Caitlin Coulombe, T00756521
 * Date: July 6, 2024
 * Course: COMP 2131
 * Assignment 2: Create a program that can create, read, write, overwritem and delete entries of a binary file. 
 */

// import headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"    // contains the struct for the records as well as all the funciton prototypes

void createNewRecord();

// global variables
FILE *recordsFile = NULL;

//-------------------------------------------------------------------------------------------------------------------
// main() takes user input to determine what action to take and acts accordingly
//-------------------------------------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    // variables
    char mainMenu[] = "\t\tMAIN MENU\n1. Create the Binary File\n2. Display the contents of the file\n3. Seek a specific record\n4. Update the contents of a record\n5. Delete a record for the specific name\n6. Exit\n";
    char input[100];
    int menuChoice;
    int validChoice = 0;    

    struct records rec;

    struct records newRec;
    initRecords(&newRec);

    // display the menu and take input from the user. Make sure the input is a number and that its in the valid range of options
    printf("%s\n", mainMenu);
    printf("Please enter your choice .... ");
    fgets(input, sizeof(input), stdin);
    // Use sscanf to convert input to integer
    if (sscanf(input, "%d", &menuChoice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        return 1;  // or handle error as needed
    }
    printf("\n");

    while(validChoice == 0)
    {

        if(menuChoice < 1|| menuChoice > 6)
        {
            validChoice = 0;
            printf("That is not a valid choice. Please pick an option from 1 to 6.\n");
            printf("Please enter your choice ....");
            fgets(input, sizeof(input), stdin);
            // Use sscanf to convert input to integer
            if (sscanf(input, "%d", &menuChoice) != 1) {
                printf("Invalid input. Please enter a number.\n");
                return 1;  // or handle error as needed
            }
            printf("\n");
        }
        else
        {
            validChoice = 1;
        }
        
    }

    // enter the appropriate function for the input
    while(menuChoice != 6)
    {
        switch (menuChoice)
        {
        case 1:
            // create the file
            createNewFile();
            break;
        case 2:
            // display the contents of the entire file
            displayFile();
            break;
        case 3:
            // seek and display a specific record     
            seekRec();
            break;
        case 4:
            // update a specific record or add a new record to the end of the file
            updateRec();
            break;
        case 5:
            // delete a record for the specific name
            deleteRec();
            break;
        default:
            break;
        }

        // what does the user want to do next
        printf("\n%s\n", mainMenu);
        printf("Please enter what you would like to do next .... ");
        fgets(input, sizeof(input), stdin);
        // Use sscanf to convert input to integer
        if (sscanf(input, "%d", &menuChoice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            return 1;  // or handle error as needed
        }
        printf("\n");
        
        while(menuChoice < 1 || menuChoice > 6)
        {
            printf("That is not a valid choice. Please pick an option from 1 to 6.\n");
            printf("Please enter your choice .... ");
            fgets(input, sizeof(input), stdin);
            // Use sscanf to convert input to integer
            if (sscanf(input, "%d", &menuChoice) != 1) {
                printf("Invalid input. Please enter a number.\n");
                return 1;  // or handle error as needed
            }
            printf("\n");
        }

    }

    printf("Have a good day.");
    exit(0);
}

//-------------------------------------------------------------------------------------------------------------------
// createNewFile() creates a new binary file
//-------------------------------------------------------------------------------------------------------------------
void createNewFile()
{
    recordsFile = fopen("records.bin", "wb");
    if(recordsFile != NULL)
    {
        fclose(recordsFile);
        printf("New file records.bin was successfully created.\n");
    }
    else
    {
        printf("Error in opening the file.\n");
    }
    return;
}

//-------------------------------------------------------------------------------------------------------------------
// accessFile() opens the specified file with the desired action
//-------------------------------------------------------------------------------------------------------------------
void accessFile(const char *action)
{
    recordsFile = fopen("records.bin", action);
    if(recordsFile == NULL)
    {
        printf("An error occured in opening the file.");
        exit(1);
    }
    return;
}

//-------------------------------------------------------------------------------------------------------------------
// initRecords() sets the initial values of the struct so that its not deleted
//-------------------------------------------------------------------------------------------------------------------
void initRecords(struct records *rec)
{
    rec->recNum = 0;
    strcpy(rec->studentID, "");
    strcpy(rec->studentName, "");
    strcpy(rec->emailID, "");
    strcpy(rec->courseID, "");
    strcpy(rec->courseGrade, "");
    rec->deleted = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// readFile() read the data in the file and return an array containing all of the records
//-------------------------------------------------------------------------------------------------------------------
struct records* readFile(int *numRecs)
{
    accessFile("rb");
    *numRecs = numOfRecs();

    struct records *recArray = malloc(sizeof(struct records) * (*numRecs));
    
    if (recArray == NULL) 
    {
        printf("Memory allocation failed.");
        exit(1);
    }

    for(int i = 0; i < *numRecs; i++) 
    {
        fread(&recArray[i], sizeof(struct records), 1, recordsFile);
    }

    fclose(recordsFile);
    return recArray;
}

//-------------------------------------------------------------------------------------------------------------------
// writeFile() writes the entire array of not-deleted records to the file
//-------------------------------------------------------------------------------------------------------------------
void writeFile(struct records *recArray, int numRecs)
{
    if(recordsFile != NULL)
    {
        fclose(recordsFile);
    }
    accessFile("wb");

    fseek(recordsFile, 0, SEEK_END);

    int recNum = 1;

    for(int i = 0; i < numRecs; i++)
    {
        if(recArray[i].deleted == 0)
        {
            recArray[i].recNum = recNum;
            fwrite(&recArray[i], sizeof(struct records), 1, recordsFile);
            recNum++;
        }
    }

    fclose(recordsFile);
}

//-------------------------------------------------------------------------------------------------------------------
// displayContents() reads and prints the contents of the binary file
//-------------------------------------------------------------------------------------------------------------------
void displayFile()
{
    int numRecs = 0;
    struct records *recArray = readFile(&numRecs);

    for(int i = 0; i < numRecs; i++)
    {
        printf(" *** Record Number: %d ***\nStudent ID: %s\nStudent Name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n\n", recArray[i].recNum, recArray[i].studentID, recArray[i].studentName,  recArray[i].emailID, recArray[i].courseID, recArray[i].courseGrade);
    }

    free(recArray);
    return;
}

//-------------------------------------------------------------------------------------------------------------------
//seekRec() seek and print a specific rec (very similar logic to the delete function)
//-------------------------------------------------------------------------------------------------------------------
void seekRec()
{
    int numRecs = 0;
    struct records *recArray = readFile(&numRecs); // Read records into memory
    if (recArray == NULL) 
    {
        printf("Error reading records.\n");
        return;
    }

    char input[100];
    int menuChoice;

    // Determine which entry they want to delete (by record number or by name)
    printf("How would you like to identify the record to print?\n1. Record number\n2. Student name\n");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &menuChoice) != 1) 
    {
        printf("Invalid input. Please enter a number.\n");
        free(recArray);
        return;
    }

    // Validate user input
    while (menuChoice < 1 || menuChoice > 2) {
        printf("That is not a valid choice. Please enter 1 or 2.\n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &menuChoice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            free(recArray);
            return;
        }
    }

    if (menuChoice == 1) 
    {
        // Find the record by record number
        int recNum;
        printf("Enter the number of the record to print (max is %d): ", numRecs);
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &recNum) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            free(recArray);
            return;
        }

        // print the specific record
        int found = 0;
        for (int i = 0; i < numRecs; i++) 
        {
            if (recNum == recArray[i].recNum) 
            {
                printf(" *** Record Number: %d ***\nStudent ID: %s\nStudent Name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n\n", recArray[i].recNum, recArray[i].studentID, recArray[i].studentName,  recArray[i].emailID, recArray[i].courseID, recArray[i].courseGrade);
                found = 1;
                break; // Exit loop once record is found and marked
            }
        }

        if (!found) 
        {
            printf("Record number %d not found.\n", recNum);
        } 
    } 
    else if (menuChoice == 2) 
    {
        // Find the record by name
        char studentName[50];
        printf("Enter the name of the student whose record you want to print: ");
        fgets(studentName, sizeof(studentName), stdin);
        studentName[strcspn(studentName, "\n")] = '\0';

        // print the specific record
        int found = 0;
        for (int i = 0; i < numRecs; i++) 
        {
            if (strcmp(studentName, recArray[i].studentName) == 0) 
            {
                printf(" *** Record Number: %d ***\nStudent ID: %s\nStudent Name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n\n", recArray[i].recNum, recArray[i].studentID, recArray[i].studentName,  recArray[i].emailID, recArray[i].courseID, recArray[i].courseGrade);
                found = 1;
                break; // Exit loop once record is found and marked
            }
        }

        if (!found) 
        {
            printf("Record with name %s not found.\n", studentName);
        } 
    } 
    else 
    {
        printf("Invalid choice.\n");
    }

    free(recArray); // Free allocated memory if function exits without returning
}

//-------------------------------------------------------------------------------------------------------------------
//updateRecords() updates the specified record with the new message OR adds a new record to the file
//-------------------------------------------------------------------------------------------------------------------
void updateRec()
{
    char input[100];
    int menuChoice;

    printf("Do you want to edit an existing record or create a new record?\n1 = Edit an existing record.\n2 = Create a new record.\nPlease enter your choice .... ");
    fgets(input, sizeof(input), stdin);
    // Use sscanf to convert input to integer
    if (sscanf(input, "%d", &menuChoice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        exit(1);  // or handle error as needed
    }

    printf("\n");

    while(menuChoice < 1 || menuChoice > 2)
    {
        printf("That is not a valid choice. Please enter 1 or 2.");
        fgets(input, sizeof(input), stdin);
        // Use sscanf to convert input to integer
        if (sscanf(input, "%d", &menuChoice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            exit(1);  // or handle error as needed
        }
        printf("\n");
    }

    if(menuChoice == 1)
    {
        // edit an existing record
        updateExistingRec();
        return;
    }
    else if(menuChoice == 2)
    {
        // append a new record to the file
        appendFile();
        return;
    }
    else
    {
        printf("Error: somehow didn't enter 1 or 2 and didn't get stopped by the while\n");
        exit(2);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// updateExistingRec() writes over the data in the file
//-------------------------------------------------------------------------------------------------------------------
void updateExistingRec()
{
    int numRecs = 0;
    struct records *recArray = readFile(&numRecs); // Read records into memory
    if (recArray == NULL) 
    {
        printf("Error reading records.\n");
        return;
    }

    char input[100];
    int menuChoice;

    // Determine which entry they want to delete (by record number or by name)
    printf("How would you like to identify the record to update?\n1. Record number\n2. Student name\n");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &menuChoice) != 1) 
    {
        printf("Invalid input. Please enter a number.\n");
        free(recArray);
        return;
    }

    // Validate user input
    while (menuChoice < 1 || menuChoice > 2) {
        printf("That is not a valid choice. Please enter 1 or 2.\n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &menuChoice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            free(recArray);
            return;
        }
    }

    if (menuChoice == 1) 
    {
        // Find the record by record number
        int recNum;
        printf("Enter the number of the record to update (max is %d): ", numRecs);
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &recNum) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            free(recArray);
            return;
        }

        // update and print the specific record
        int found = 0;
        for (int i = 0; i < numRecs; i++) 
        {
            if (recNum == recArray[i].recNum) 
            {
                printf("Please enter the following information for the updated record:\n");
                printf("Student ID: ");
                fgets(recArray[i].studentID, sizeof(recArray[i].studentID), stdin);
                recArray[i].studentID[strcspn(recArray[i].studentID, "\n")] = '\0';
                printf("\nStudent First and Last Name: ");
                fgets(recArray[i].studentName, sizeof(recArray[i].studentName), stdin);
                recArray[i].studentName[strcspn(recArray[i].studentName, "\n")] = '\0';
                printf("\nEmail ID: ");
                fgets(recArray[i].emailID, sizeof(recArray[i].emailID), stdin);
                recArray[i].emailID[strcspn(recArray[i].emailID, "\n")] = '\0';
                printf("\nCourse ID: ");
                fgets(recArray[i].courseID, sizeof(recArray[i].courseID), stdin);
                recArray[i].courseID[strcspn(recArray[i].courseID, "\n")] = '\0';
                printf("\nCourse Grade: ");
                fgets(recArray[i].courseGrade, sizeof(recArray[i].courseGrade), stdin);
                recArray[i].courseGrade[strcspn(recArray[i].courseGrade, "\n")] = '\0';
                
                recArray[i].deleted = 0;

                // to confirm that what is being updated is correct
                printf("\nData being appended: \nRecord number: %d\nStudent ID: %s\nStudent Name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n", recArray[i].recNum, recArray[i].studentID, recArray[i].studentName,  recArray[i].emailID, recArray[i].courseID, recArray[i].courseGrade);
                found = 1;
                break; // Exit loop once record is found and marked
            }
        }

        if (!found) 
        {
            printf("Record number %d not found.\n", recNum);
        } 
        else 
        {
            writeFile(recArray, numRecs); // Write updated records back to file
        }
    } 
    else if (menuChoice == 2) 
    {
        // Find the record by name
        char studentName[50];
        printf("Enter the name of the student whose record you want to print: ");
        fgets(studentName, sizeof(studentName), stdin);
        studentName[strcspn(studentName, "\n")] = '\0';

        // print the specific record
        int found = 0;
        for (int i = 0; i < numRecs; i++) 
        {
            if (strcmp(studentName, recArray[i].studentName) == 0) 
            {
                printf("Please enter the following information for the updated record:\n");
                printf("Student ID: ");
                fgets(recArray[i].studentID, sizeof(recArray[i].studentID), stdin);
                recArray[i].studentID[strcspn(recArray[i].studentID, "\n")] = '\0';
                printf("\nStudent First and Last Name: ");
                fgets(recArray[i].studentName, sizeof(recArray[i].studentName), stdin);
                recArray[i].studentName[strcspn(recArray[i].studentName, "\n")] = '\0';
                printf("\nEmail ID: ");
                fgets(recArray[i].emailID, sizeof(recArray[i].emailID), stdin);
                recArray[i].emailID[strcspn(recArray[i].emailID, "\n")] = '\0';
                printf("\nCourse ID: ");
                fgets(recArray[i].courseID, sizeof(recArray[i].courseID), stdin);
                recArray[i].courseID[strcspn(recArray[i].courseID, "\n")] = '\0';
                printf("\nCourse Grade: ");
                fgets(recArray[i].courseGrade, sizeof(recArray[i].courseGrade), stdin);
                recArray[i].courseGrade[strcspn(recArray[i].courseGrade, "\n")] = '\0';
                
                recArray[i].deleted = 0;

                // to confirm that what is being updated is correct
                printf("\nData being appended: \nRecord number: %d\nStudent ID: %s\nStudent Name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n", recArray[i].recNum, recArray[i].studentID, recArray[i].studentName,  recArray[i].emailID, recArray[i].courseID, recArray[i].courseGrade);
                found = 1;
                break; // Exit loop once record is found and marked
            }
        }

        if (!found) 
        {
            printf("Record with name %s not found.\n", studentName);
        } 
        else 
        {
            writeFile(recArray, numRecs); // Write updated records back to file
        }
    } 
    else 
    {
        printf("Invalid choice.\n");
    }

    free(recArray); // Free allocated memory if function exits without returning
}

//-------------------------------------------------------------------------------------------------------------------
// appendFile() writes over the data in the file
//-------------------------------------------------------------------------------------------------------------------
void appendFile()
{
    // local variables
    struct records appRec;
    accessFile("ab");

    appRec.recNum = numOfRecs() + 1;

    printf("Please enter the following information for the new record:\n");
    printf("Student ID: ");
    fgets(appRec.studentID, sizeof(appRec.studentID), stdin);
    appRec.studentID[strcspn(appRec.studentID, "\n")] = '\0';
    printf("\nStudent First and Last Name: ");
    fgets(appRec.studentName, sizeof(appRec.studentName), stdin);
    appRec.studentName[strcspn(appRec.studentName, "\n")] = '\0';
    printf("\nEmail ID: ");
    fgets(appRec.emailID, sizeof(appRec.emailID), stdin);
    appRec.emailID[strcspn(appRec.emailID, "\n")] = '\0';
    printf("\nCourse ID: ");
    fgets(appRec.courseID, sizeof(appRec.courseID), stdin);
    appRec.courseID[strcspn(appRec.courseID, "\n")] = '\0';
    printf("\nCourse Grade: ");
    fgets(appRec.courseGrade, sizeof(appRec.courseGrade), stdin);
    appRec.courseGrade[strcspn(appRec.courseGrade, "\n")] = '\0';
    
    appRec.deleted = 0;

    // to confirm that what is being appended is correct
    printf("\nData being appended: \nRecord number: %d\nStudent ID: %s\nStudent Name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n", appRec.recNum, appRec.studentID, appRec.studentName,  appRec.emailID, appRec.courseID, appRec.courseGrade);


    fwrite(&appRec, sizeof(struct records), 1, recordsFile);
    fclose(recordsFile);
    return;
}

//-------------------------------------------------------------------------------------------------------------------
//deleteRec() deletes a specific file
//-------------------------------------------------------------------------------------------------------------------
void deleteRec()
{
    int numRecs = 0;
    struct records *recArray = readFile(&numRecs); // Read records into memory
    if (recArray == NULL) 
    {
        printf("Error reading records.\n");
        return;
    }

    char input[100];
    int menuChoice;

    // Determine which entry they want to delete (by record number or by name)
    printf("How would you like to identify the record to delete?\n1. Record number\n2. Student name\n");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &menuChoice) != 1) 
    {
        printf("Invalid input. Please enter a number.\n");
        free(recArray);
        return;
    }

    // Validate user input
    while (menuChoice < 1 || menuChoice > 2) {
        printf("That is not a valid choice. Please enter 1 or 2.\n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &menuChoice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            free(recArray);
            return;
        }
    }

    if (menuChoice == 1) 
    {
        // Find the record by record number
        int recNum;
        printf("Enter the number of the record to delete (max is %d): ", numRecs);
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &recNum) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            free(recArray);
            return;
        }

        // Mark the record as deleted
        int found = 0;
        for (int i = 0; i < numRecs; i++) 
        {
            if (recNum == recArray[i].recNum) 
            {
                recArray[i].deleted = 1;
                printf("Deleted record number %d\n", recArray[i].recNum);
                found = 1;
                break; // Exit loop once record is found and marked
            }
        }

        if (!found) 
        {
            printf("Record number %d not found.\n", recNum);
        } 
        else 
        {
            writeFile(recArray, numRecs); // Write updated records back to file
        }

    } 
    else if (menuChoice == 2) 
    {
        // Find the record by name
        char studentName[50];
        printf("Enter the name of the student whose record you want to delete: ");
        fgets(studentName, sizeof(studentName), stdin);
        studentName[strcspn(studentName, "\n")] = '\0';

        // Mark the record as deleted
        int found = 0;
        for (int i = 0; i < numRecs; i++) 
        {
            if (strcmp(studentName, recArray[i].studentName) == 0) 
            {
                recArray[i].deleted = 1;
                printf("Deleted record named %s\n", recArray[i].studentName);
                found = 1;
                break; // Exit loop once record is found and marked
            }
        }

        if (!found) 
        {
            printf("Record with name %s not found.\n", studentName);
        } else 
        {
            writeFile(recArray, numRecs); // Write updated records back to file
        }
    } 
    else 
    {
        printf("Invalid choice.\n");
    }

    free(recArray); // Free allocated memory if function exits without returning
}

//-------------------------------------------------------------------------------------------------------------------
//numOfRecs() determines how many records are in the file
//-------------------------------------------------------------------------------------------------------------------
int numOfRecs()
{
    if(recordsFile == NULL)
    {
        accessFile("rb");
    }
    
    fseek(recordsFile, 0L, SEEK_END);
    long int size = ftell(recordsFile);
    fseek(recordsFile, 0L, SEEK_SET); // reset file pointer to beginning
    long num = size / sizeof(struct records);
    printf("Number of records in file: %lu\n", num);
    return num;
}
