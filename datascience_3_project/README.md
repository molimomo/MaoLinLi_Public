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
Step 1. Load text files into corresponding tables

Here we read text files into data frames with read.table().
* features : Feature names
* activity: Descriptive activity names
* trainData : Training set
* testData: Test set
* trainLabel: Training labels
* testLabel: Test labels
* trainSubject: Training subjects
* testSubject: Test subjects

Step 2. Merge training/test set

Here we merge traingin set and test test with rbind().
* original: trainOriginal + testOriginal (original dataset)

Step 3. Extract the indice of the measurements on the mean and standard deviation.

Here we extract the indice that variables' name include "mean" anf "std" with grep().
* meanIdx: The indice of the measurements on the mean
* stdIdx: The indice of the measurements on the standard deviation.
* targetIdx : The union of meanIdx and stdIdx

Step 4. Extract required column from original dataset.

Here we extract sub-matrix according to the indices in previous step with select().
* targetMatrix: The sub-matrix we want.

Step 5. Append subjects and label to target matrix.

Here we combine the "label" and "subject" to target matrix with rbind() and cbind().

Step 6. Extract descriptive activity names from activity label.txt and then mapping it to target dataset.

Here we use mutate() to add "activity" variable into target matrix.

Step 7. Calcualte the average of each variable for each activity and each subject.

Here we use two for loop to travese target matrix and calculate the average of all mean/std measurment in each subject with different activity. First we use filter() to find suitable sub-matrix. And then we use apply() to calculat the average of each measurement. Finally we append its object and activity  variables to generate new record. And then use rbind() to accumlate result.

Step 8. Arrange result by subject and then write result to file.

Here we use write.table() to output our result.