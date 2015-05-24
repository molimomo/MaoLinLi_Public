library(dplyr)

##  Step 1. Load text files into corresponding tables
#       features : Feature names
#       activity: Descriptive activity names
#       trainData : Training set
#       testData: Test set
#       trainLabel: Training labels
#       testLabel: Test labels
#       trainSubject: Training subjects
#       testSubject: Test subjects
features<-read.table("./UCI_HAR_Dataset/features.txt")
features<-features$V2
activity<-read.table("./UCI_HAR_Dataset/activity_labels.txt")
trainData<-read.table("./UCI_HAR_Dataset/train/X_train.txt",col.names = features)
testData<-read.table("./UCI_HAR_Dataset/test/X_test.txt",col.names = features)
trainSubject<-read.table("./UCI_HAR_Dataset/train/subject_train.txt",col.names=c("subject"))
testSubject<-read.table("./UCI_HAR_Dataset/test/subject_test.txt",col.names=c("subject"))
trainLabel<-read.table("./UCI_HAR_Dataset/train/y_train.txt", col.names = c("label"))
testLabel<-read.table("./UCI_HAR_Dataset/test/y_test.txt", col.names = c("label"))

##  Step 2. Merge training/test set
#       original: trainOriginal + testOriginal (original dataset)
original<-rbind(trainData, testData)

##  Step 3. Extract the indice of the measurements on the mean and standard deviation.
#       meanIdx: The indice of the measurements on the mean
#       stdIdx: The indice of the measurements on the standard deviation.
#       targetIdx : The union of meanIdx and stdIdx
meanIdx<-grep("mean",names(original))
stdIdx<-grep("std",names(original))
targetIdx<-sort(c(meanIdx, stdIdx))

##  Step 4. Extract required column from original dataset.
targetMatrix<-select(original,targetIdx)

##  Step 5. Append subjects and label to target matrix.
subjects<-rbind(trainSubject, testSubject)
labels<-rbind(trainLabel, testLabel)
targetMatrix<-cbind(targetMatrix,subjects)
targetMatrix<-cbind(targetMatrix,labels)

##  Step 6. Extract descriptive activity names from activity label.txt and then mapping it to target dataset.
#       ac: the vector of characters for descriptive activity names
ac<-as.character(activity$V2)
targetMatrix<-mutate(targetMatrix, activity = ac[targetMatrix$label])

## Step 7. Calcualte the average of each variable for each activity and each subject.
result = data.frame()
for(i in 1:length(ac)){
    for(j in 1:nrow(unique(subjects))){
        data<-filter(targetMatrix, subject==j & label==i)
        data_numeric<-select(data, -(subject:activity))
        oldActivity<-colnames(data_numeric)
        colnames(data_numeric)<-1:ncol(data_numeric)
        rec<-sapply(colnames(data_numeric),function(x){mean(data_numeric[,x])})
        rec = c(rec, j, ac[i])
        names(rec) = c(oldActivity,"subject", "activity")
        rec=t(as.data.frame(rec))
        result<-rbind(result, rec)
    }
}

##  Step 8. Arrange result by subject and then write result to file.
result<-arrange(result, subject)
write.table(result, file="./result.txt", row.name=FALSE)





