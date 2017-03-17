//
//  main.c
//  SqLiteExamples
//
//  Created by Ann on 15.03.17.
//  Copyright © 2017 Ann. All rights reserved.
//

#include <stdio.h>
#include <sqlite3.h>

int main(int argc, const char * argv[]) {
    sqlite3 *db;
    int rc;
    
    rc = sqlite3_open("test.db", &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);
    
    return 0;
}
