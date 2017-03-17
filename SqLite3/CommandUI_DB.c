//
//  main.c
//  SqLiteExamples
//
//  Created by Ann on 15.03.17.
//  Copyright © 2017 Ann. All rights reserved.
//

#include <sqlite3.h>
#include <string.h>
#include <stdio.h>

static void ScanfNameAndSurname(char* name, char* surname){
    printf("Enter employee name\n");
    scanf("%s", name);
    getchar();
    printf("Enter employee surname\n");
    scanf("%s", surname);
    getchar();
}

static void PrintOptions(){
    printf("s - select\ni - insert\nd - delete\nf - " \
           "write employee photo to file\nt - transaction check\n" \
           "p - print table\nq - quit\n");
}


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    
    return 0;
}

char* fields[] = {"Name", "Surname", "Birth date", "Country", "City", "Address", "Department", "Position", "Hided date"};

void GetDataToInsert(char data[9][40]){
    printf("Entee employee info:\n");
    for(int i = 0; i < 9; ++i){
        printf("%s:\n", fields[i]);
        scanf("%s", data[i]);
        getchar();
    }
}

void SelectField(char* field){
    printf("Choose field(1 - id, 2 - country, 3 - surname):\n");
    int number;
    scanf("%d", &number);
    getchar();
    
    switch(number){
        case 1:
            strcpy(field, "id");
            break;
        case 2:
            strcpy(field, "country");
            break;
        case 3:
            strcpy(field, "last_name");
            break;
        default:
            printf("Wrong field number\n");
    }
}

void SelectRecordsByField(sqlite3 *db){
    char field[30];
    SelectField(field);
    
    char value[20];
    printf("Enter field value:\n");
    scanf("%s", value);
    getchar();
    
    char sql[256];
    sprintf(sql,"%s %s='%s'", "SELECT * FROM employees where", field, value);
    
    char *zErrMsg = 0;
    printf("\n");
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void InsertRecordToDB(sqlite3 *db){
    char *sql;
    char source[9][40];
    
    GetDataToInsert(source);
    
    sql = "INSERT INTO employees (first_name,last_name, "
    "birth_date, country, city, address, department, position, hired_date)"
    "values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to prepare statement\n");
        return;
    }
    
    for(int i = 1; i <= 9; ++i)
        sqlite3_bind_text(pStmt, i, source[i - 1], \
                          (int)strlen(source[i - 1]), 0);
    
    rc = sqlite3_step(pStmt);
    
    rc = sqlite3_finalize(pStmt);
}

void InsertRecordToDBWithMode(sqlite3 *db){
    printf("Choose mode:\n1 - autocommit\n2 - transaction\n");
    char key;
    scanf("%c", &key);
    getchar();
    
    char *sql;
    switch(key){
        case '1':
            sql = "INSERT INTO employees (first_name,last_name)"
            "values ('Bob', 'Jonson');"
            "INSERT INTO employees (first_name,last_name)"
            "values ('Kete', 'Jonson');"
            "INSERT INTO employees (first_name,last_name)"
            "values ('Alice', 'Jonson');"
            "INSERT INTO employee (first_name,last_name)"//mistake here
            "values ('Nik', 'Jonson');";
            break;
        case '2':
            sql = "BEGIN TRANSACTION;"
            "INSERT INTO employees (first_name,last_name)"
            "values ('Nikita', 'Jonson');"
            "INSERT INTO employees (first_name,last_name)"
            "values ('Mike', 'Jonson');"
            "INSERT INTO employees (first_name,last_name)"
            "values ('Mila', 'Jonson');"
            "INSERT INTO employee (first_name,last_name)"//mistake here
            "values ('Nik', 'Jonson');"
            "COMMIT;";
            break;
        default:
            printf("Invalid option");
            return;
    }
    printf("Command to execute:\n%s", sql);
    
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void DeleteRecordFromDB(sqlite3 *db, char* name, char* surname){
    char *sql;
    sql = "DELETE from employees where first_name = ? and last_name = ?; " \
    "SELECT * from employees";

    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to prepare statement\n");
        return;
    }
    
    sqlite3_bind_text(pStmt, 1, name, (int)strlen(name), 0);
    sqlite3_bind_text(pStmt, 2, surname, (int)strlen(surname), 0);
    
    rc = sqlite3_step(pStmt);
    
    rc = sqlite3_finalize(pStmt);
}

void WritePhotoToFile(sqlite3 *db, char* name, char* surname){
    FILE *fp = fopen("new.jpg", "wb");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open image file\n");
        return;
    }
    
    char *sql = "SELECT photo FROM employees WHERE first_name = ? and last_name = ?";
    
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to prepare statement\n");
        return;
    }
    
    sqlite3_bind_text(pStmt, 1, name, (int)strlen(name), 0);
    sqlite3_bind_text(pStmt, 2, surname, (int)strlen(surname), 0);
    
    rc = sqlite3_step(pStmt);
    if(rc != SQLITE_ROW){
        printf("No photo written");
    }else
        printf("Photo successfully written");
    
    int bytes = sqlite3_column_bytes(pStmt, 0);
    
    fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);
    if (ferror(fp)) {
        fprintf(stderr, "fwrite() failed\n");
    }
    
    int r = fclose(fp);
    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }
    
    rc = sqlite3_finalize(pStmt);
}

void PrintTable(sqlite3 *db){
    char *zErrMsg = 0;
    int rc;
    char *sql;
    
    sql = "SELECT * from employees";
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

int main(void) {
    sqlite3 *db;
    int rc;
    
    rc = sqlite3_open("test.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }else
        fprintf(stderr, "Opened database successfully\n");
    
    int quit = 0;
    while(!quit)
    {
        char option;
        printf("\nChoose option:\n");
        PrintOptions();
        scanf("%c",&option);
        getchar();
        
        switch(option){
            case 's':{
                SelectRecordsByField(db);
                break;
            }
            case 'i':
                InsertRecordToDB(db);
                break;
            case 'd':{
                char name[15], surname[20];
                ScanfNameAndSurname(name, surname);
                DeleteRecordFromDB(db, name, surname);
                break;
            }
            case 'f':{
                char name[15], surname[20];
                ScanfNameAndSurname(name, surname);
                WritePhotoToFile(db, name, surname);
                break;
            }
            case 't':
                InsertRecordToDBWithMode(db);
                break;
            case 'p':
                PrintTable(db);
                break;
            case 'q':
                quit = 1;
                break;
            default:
                printf("Invalid option");
        }
    }
    
    sqlite3_close(db);
    
    return 0;
}
