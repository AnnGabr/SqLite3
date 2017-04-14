//
//  ViewController.m
//  Wheather
//
//  Created by Sergey on 4/13/17.
//  Copyright © 2017 Ann. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *result;
@property (weak, nonatomic) IBOutlet UITextField *cityInfo;
@property (weak, nonatomic) IBOutlet UISegmentedControl *mode;

@end

@implementation ViewController
- (IBAction)refresh:(id)sender {
    NSURL *url = [[NSURL alloc] initWithString:[self createURL]];
    NSData *contents = [[NSData alloc] initWithContentsOfURL:url];
    
    if(contents != nil){
        NSDictionary *forecasting = [NSJSONSerialization JSONObjectWithData:contents options:NSJSONReadingMutableContainers error:nil];
        
        if(forecasting != nil){
            NSString* temp = [[NSString alloc] initWithFormat:(@"%@"), [[forecasting valueForKey:@"main"] valueForKey:@"temp"]];
            [[self result] setText:temp];
            
            [self setResultLableColorByTemperature:[temp floatValue]];
        }
        else [[self result] setText:@"Not found"];
    }else [[self result] setText:@"Not found"];
}

-(NSMutableString*)createURL{
    NSMutableString *info = [[NSMutableString alloc] initWithString:@"http://api.openweathermap.org/data/2.5/weather?"];
    
    switch ([[self mode] selectedSegmentIndex]) {
        case 0:{
            NSArray *words = [[[self cityInfo] text] componentsSeparatedByString: @":"];
            if([words count] >= 2)
                [info appendFormat:(@"lat=%@&lon=%@"),words[0], words[1]];
            break;
        }
        case 1:
            [info appendFormat:(@"q=%@"), [[self cityInfo] text]];
            break;
        default: break;
    }
    [info appendString:@"&units=metric&APPID=cc88852b3fd6a179050fe2d34b8fac6d"];
    
    return info;
}

-(void)setResultLableColorByTemperature: (float)temp{
    if(temp <= 5){
        [[self result] setBackgroundColor:[UIColor blueColor]];
    }else if(temp > 5 && temp <= 10){
        [[self result] setBackgroundColor:[UIColor greenColor]];
    }else if(temp > 10 && temp <= 18){
        [[self result] setBackgroundColor:[UIColor yellowColor]];
    }else if(temp > 18 && temp <=28){
        [[self result] setBackgroundColor:[UIColor orangeColor]];
    }else{
        [[self result] setBackgroundColor:[UIColor redColor]];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
