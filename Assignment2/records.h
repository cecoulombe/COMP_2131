// create a header file for the records struct

#ifndef RECORDS_H
#define RECORDS_H

//-------------------------------------------------------------------------------------------------------------------
// struct records() stores all of the relevant information for the records in a struct
//-------------------------------------------------------------------------------------------------------------------
struct records
{
    int recNum;
    // char studentID[50], studentName[50], emailID[50], courseID[50], courseGrade[50];
    char studentID[50], studentName[50], emailID[50], courseID[50], courseGrade[50];
    int deleted;
};

// function prototypes
void createNewFile();
void accessFile(const char *action);
void initRecords(struct records *rec);
struct records *readFile(int *numRecs);
void writeFile(struct records *recArray, int numRecs);
void displayFile();
void seekRec();
void updateRec();
void updateExistingRec();
void appendFile();
void deleteRec();
int numOfRecs();

#endif // RECORDS_H