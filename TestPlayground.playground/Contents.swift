//: Playground - noun: a place where people can play

import UIKit

/*it`s my first playground*/

var j: Int = 2
let s1 = "Minutes in hour: \(60 * 1)"
let s2 = "Weeks in year: \(365 / 7)"
let d: Double = 3.12
var flag: Bool = true

print("I am \(19) years old")

func printDouble(double: Double)->Void{
    print("my double: \(double)")
}

printDouble(double: d)

func kilocalories(fats: Double, proteins: Double,
    carbohydrates:Double) -> Double {
    return 4 * (carbohydrates + proteins) + 9 * fats
}

print("kilocalories == \(kilocalories(fats: 20, proteins: 15, carbohydrates: 32))")
