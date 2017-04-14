//
//  Tester.m
//  Analyther
//
//  Created by Ann on 14.04.17.
//  Copyright © 2017 Ann. All rights reserved.
//

#import "Tester.h"
#import "Analyzer.h"

@implementation Tester

+(void)test{
    [self test1];
    [self test2];
    [self test3];
}

+(void)test1{
    NSString* input = @"bye       ";
    NSString* expected = @"bye-1|";
    NSString* result = [NSString stringWithFormat:(@"%@"), [Analyzer analyze: input]];
    NSLog(@"Input:%@", input);
    NSLog(@"Expected:%@", expected);
    NSLog(@"Result:%@", result);
    if(![result compare:expected])
        NSLog(@"OK");
    else
        NSLog(@"WRONG");
}

+(void)test2{
    NSString* input = @"a b b g g g h k k k k e e e e y y y y y u u u u u u       ";
    NSString* expected = @"u-6|y-5|k-4|e-4|g-3|";
    NSString* result = [NSString stringWithFormat:(@"%@"), [Analyzer analyze: input]];
    NSLog(@"Input:%@", input);
    NSLog(@"Expected:%@", expected);
    NSLog(@"Result:%@", result);
    if(![result compare:expected])
        NSLog(@"OK");
    else
        NSLog(@"WRONG");
}

+(void)test3{
    NSString* input = @"bye hi hi hi a     a a a r r r r r t t t t t t t gg gg     ";
    NSString* expected = @"t-7|r-5|a-4|hi-3|gg-2|";
    NSString* result = [NSString stringWithFormat:(@"%@"), [Analyzer analyze: input]];
    NSLog(@"Input:%@", input);
    NSLog(@"Expected:%@", expected);
    NSLog(@"Result:%@", result);
    if(![result compare:expected])
        NSLog(@"OK");
    else
        NSLog(@"WRONG");
}

@end
