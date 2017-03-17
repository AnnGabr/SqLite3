//
//  main.c
//  SqLiteExamples
//
//  Created by Ann on 15.03.17.
//  Copyright © 2017 Ann. All rights reserved.
//

#include <sqlite3.h>
#include <stdio.h>

int main(int argc, char **argv) {
    
    FILE *fp = fopen("f.jpg", "rb");
    
    if (fp == NULL) {
        
        fprintf(stderr, "Cannot open image file\n");
        
        return 1;
    }
    
    fseek(fp, 0, SEEK_END);
    
    if (ferror(fp)) {
        
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        
        return 1;
    }
    
    long flen = ftell(fp);
    
    if (flen == -1) {
        
        perror("error occurred");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        
        return 1;
    }
    
    fseek(fp, 0, SEEK_SET);
    
    if (ferror(fp)) {
        
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        
        return 1;
    }
    
    char data[flen+1];
    
    long size = fread(data, 1, flen, fp);
    
    if (ferror(fp)) {
        
        fprintf(stderr, "fread() failed\n");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        
        return 1;
    }
    
    int r = fclose(fp);
    
    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }
    
    
    sqlite3 *db;
    
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    
    sqlite3_stmt *pStmt;
    
    char *sql = "INSERT INTO Images(Data) VALUES(?)";
    
    rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        
        return 1;
    }
    
    sqlite3_bind_blob(pStmt, 1, data, (int)size, SQLITE_STATIC);
    
    rc = sqlite3_step(pStmt);
    
    if (rc != SQLITE_DONE) {
        
        printf("execution failed: %s", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(pStmt);
    
    sqlite3_close(db);
    
    return 0;
}
