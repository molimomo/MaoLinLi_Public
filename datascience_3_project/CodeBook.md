---
title: Codebook for Getting and Cleaning Data Project
author: Mao-Lin Li
date: 05/24/2015
output: result.txt
---
 
##Project Description
In this project, we re-organize the UCI HAR dataset to calculate
the average of each variable for each activity and each subject.
 
Collection of the raw data
==================================================================
Human Activity Recognition Using Smartphones Dataset
Version 1.0
==================================================================
Jorge L. Reyes-Ortiz, Davide Anguita, Alessandro Ghio, Luca Oneto.
Smartlab - Non Linear Complex Systems Laboratory
DITEN - Universit‡ degli Studi di Genova.
Via Opera Pia 11A, I-16145, Genoa, Italy.
activityrecognition@smartlab.ws
www.smartlab.ws
==================================================================
The raw data can be downloaded from http://archive.ics.uci.edu/ml/datasets/Human+Activity+Recognition+Using+Smartphones
 
##The dataset includes the following files:
=========================================
- 'README.txt'
- 'features_info.txt': Shows information about the variables used on the feature vector.
- 'features.txt': List of all features.
- 'activity_labels.txt': Links the class labels with their activity name.
- 'train/X_train.txt': Training set.
- 'train/y_train.txt': Training labels.
- 'test/X_test.txt': Test set.
- 'test/y_test.txt': Test labels.
The following files are available for the train and test data. Their descriptions are equivalent. 
- 'train/subject_train.txt': Each row identifies the subject who performed the activity for each window sample. Its range is from 1 to 30. 
- 'train/Inertial Signals/total_acc_x_train.txt': The acceleration signal from the smartphone accelerometer X axis in standard gravity units 'g'. Every row shows a 128 element vector. The same description applies for the 'total_acc_x_train.txt' and 'total_acc_z_train.txt' files for the Y and Z axis. 
- 'train/Inertial Signals/body_acc_x_train.txt': The body acceleration signal obtained by subtracting the gravity from the total acceleration. 
- 'train/Inertial Signals/body_gyro_x_train.txt': The angular velocity vector measured by the gyroscope for each window sample. The units are radians/second. 
- Features are normalized and bounded within [-1,1].
- Each feature vector is a row on the text file.

###Guide to create the tidy data file
Step 1. Extract feature names from feature.txt

Step 2. Load tran data and test data into tables.

Step 3. Merge training/test set and training/test labels.

Step 4. Extract the indice of the measurements on the mean and standard deviation.

Step 5. Extract required column from original dataset.

Step 6. Append subjects and label to target matrix.

Step 7. Extract descriptive activity names from activity label.txt and then mapping it to target dataset.

Step 8. Calcualte the average of each variable for each activity and each subject.

Step 9. Arrange result by subject and then write result to file.

##Description of the variables in result.txt file
There are 180 rows and 81 cols in result.txt.
Each row represents a record that 1 subject with its activity and the average of all mean/std measurement.
The first 79 variables represent the average of all mean/std measurement.
The last 2 variables are "subject" and "activity"