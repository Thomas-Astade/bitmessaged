//~~ bool operator==(const connection& other) [connection] ~~
return(memcmp(&myAddr,&other.myAddr,sizeof(myAddr)) == 0);