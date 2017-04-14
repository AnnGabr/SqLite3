//
//  FirstViewController.swift
//  Ann
//
//  Created by Sergey on 4/12/17.
//  Copyright © 2017 Ann. All rights reserved.
//

import UIKit

class FirstViewController: UIViewController {

    @IBOutlet weak var button: UIButton!
    @IBOutlet weak var label: UILabel!
    @IBOutlet weak var weightArea: UITextField!
    @IBOutlet weak var ageArea: UITextField!
    @IBOutlet weak var heightArea: UITextField!
    @IBOutlet weak var genderSegment: UISegmentedControl!
    @IBOutlet weak var activitySegmController: UISegmentedControl!
    @IBOutlet weak var resultLabel: UILabel!
    
    @IBAction func calculate(_ sender: Any) {
        var bmr: Double = 0
        var bmi: Double = 0
        if let age: Int = Int(ageArea.text!) {
            if let height: Int = Int(heightArea.text!) {
                if let weight: Int = Int(weightArea.text!) {
                    switch genderSegment.selectedSegmentIndex {
                    case 0:
                        bmr = 88.362 + 13.397 * Double(weight) + 4.799 * Double(height) - 5.677 * Double(age)
                    case 1:
                        bmr = 447.593 + 9.247 * Double(weight) + 3.098 * Double(height) - 4.330 * Double(age)
                    default:
                        bmr = 0
                    }
                    bmi = Double(weight) / pow(Double(height) / 100, 2)
                }
            }
        }
        let factor = [1.375, 1.55, 1.725, 1.9]
        
        let selectedFactor = factor[activitySegmController.selectedSegmentIndex]
        bmr *= selectedFactor
        
        resultLabel.text = "Need to consume \(Int(bmr)) kilocalories weight sustentation.\nBody mass index: \(Int(bmi))."
        
        UIApplication.shared.keyWindow!.endEditing(true)
    }

    
    @IBAction func onClicked(_ sender: Any) {
        label.text = "Test";
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

