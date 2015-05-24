---
title: README for Getting and Cleaning Data Project
author: Mao-Lin Li
date: 05/24/2015
output: result.txt
---

#Project Description
In this project, we re-organize the UCI HAR dataset to calculate
the average of each variable for each activity and each subject.

#Input Files
* ./UCI_HAR_Dataset/train/X_train.txt
* ./UCI_HAR_Dataset/train/y_train.txt
* ./UCI_HAR_Dataset/test/X_test.txt
* ./UCI_HAR_Dataset/test/y_test.txt
* ./UCI_HAR_Dataset/train/subject_train.txt
* ./UCI_HAR_Dataset/test/subject_test.txt

#Output File
result.txt

#How to run this script?
Put this script in the same level of directory with UCI HAR dataset, then source("run_analysis.R").
Then the result.txt will be generated.

#The meaning of result.txt
There are 180 (30 objects * 6 activities) rows and 81 (79 mean/std measurements + object + activity) cols in result.txt.
Each row represents a record that 1 subject with its activity and the average of all mean/std measurement.
The first 79 variables represent the average of all mean/std measurement.
The last 2 variables are "subject" and "activity".
The detailed information about variables can be found in feature_info.txt.

#The procedure of data processing
Step 1. Extract feature names from feature.txt
Here we read text file "feature.txt" into features data frame.

Step 2. Load tran data and test data into tables.

Step 3. Merge training/test set and training/test labels.

Step 4. Extract the indice of the measurements on the mean and standard deviation.

Step 5. Extract required column from original dataset.

Step 6. Append subjects and label to target matrix.

Step 7. Extract descriptive activity names from activity label.txt and then mapping it to target dataset.

Step 8. Calcualte the average of each variable for each activity and each subject.

Step 9. Arrange result by subject and then write result to file.