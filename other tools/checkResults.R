par(mfrow = c(2, 2))
setwd("C:/Projects/standupsaker/SimulateStandup/SimulateStandup")

objTemp<-read.csv("OBJTEMP2.txt", sep=',',header=FALSE,skip=0, stringsAsFactors = FALSE)
objTemp[2]=NULL;
yVector <- 1:length(t(objTemp))
objTemp <- as.numeric(unlist(objTemp));
plot(objTemp)

ambTemp<-read.csv("AMBTEMP2.txt", sep=',',header=FALSE,skip=0, stringsAsFactors = FALSE)
ambTemp[2]=NULL;
yVector <- 1:length(t(ambTemp))
ambTemp <- as.numeric(unlist(ambTemp));
plot(ambTemp)

result<-read.csv("result.txt", sep=' ',header=FALSE,skip=0, stringsAsFactors = FALSE)
result[2]=NULL;
yVector <- 1:length(t(result))
result <- as.numeric(unlist(result));
plot(result)