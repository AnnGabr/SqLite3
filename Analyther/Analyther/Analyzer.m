//
//  Analyther.m
//  Analyther
//
//  Created by Ann on 11.04.17.
//  Copyright © 2017 Ann. All rights reserved.
//

#import "Analyzer.h"

@implementation Analyzer: NSObject

+ (NSMutableString *)analyze:(NSString *)text{
    NSMutableDictionary* statistics = [[NSMutableDictionary alloc] init];
    [self makeStat:statistics fromString: text];
    [self sortStat:statistics];
    NSArray* sortedKeys = [[NSArray alloc] initWithArray:[self sortStat:statistics]];
    return [self makeResultFromStat:statistics byKeys:sortedKeys];
}

+ (void)makeStat:(NSMutableDictionary*)statistics fromString:(NSString*)text{
    NSArray* words = [text componentsSeparatedByString: @" "];
    for(NSString* word in words){
        if(![word compare:@""])
            continue;
        
        NSNumber *repetitions = [statistics valueForKey: word];
        [statistics setObject:[[NSNumber alloc] initWithLong: ([repetitions integerValue] + 1)] forKey:word];
    }
}

+ (NSArray*)sortStat:(NSMutableDictionary*)statistics{
    return [statistics keysSortedByValueUsingComparator:^NSComparisonResult(NSNumber* a, NSNumber* b){
        return -[ a compare: b];
    }];
}

+ (NSMutableString*)makeResultFromStat: (NSMutableDictionary*)statistics byKeys:(NSArray*)sortedKeys{
    NSMutableString* result = [[NSMutableString alloc] init];
    int counter = 0;
    for(NSString* key in sortedKeys){
        if(counter == 5)
            break;
        ++counter;
        
        [result appendFormat: (@"%@-%@|"), key, [statistics objectForKey: key]];
    }
    return result;
}

@end
