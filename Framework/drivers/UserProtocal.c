#include "UserProtocal.h"


//规范格式：帧头+数据+分隔符+数据+分隔符+...+帧尾，返回值，包含各个数据的字符二维数组
//返回值：0失败，及dataout二维数
u8 ComProtocal(char*rxbuf,char*head,char*end,char* separater,char dataout[][15])
{
    u8 headlength,endlength,datalength,totallength;
    u8 i=0;//分割计数用
    char temp[50]="";//按需求定义字符串长度
    char*splitchar;//分割用
    headlength=strlen(head);
    endlength=strlen(end);
    totallength=strlen(rxbuf);
		datalength=totallength-headlength-endlength;
    strncpy(temp,rxbuf,headlength);
    temp[headlength]='\0';
    if(strcmp(temp,head))
    {
        return 0;
    }
    strncpy(temp,rxbuf+totallength-endlength,endlength);
    temp[endlength]='\0';
    if(strcmp(temp,end))
    {
        return 0;
    }
    strncpy(temp,rxbuf+headlength,datalength);
    temp[datalength]='\0';

    splitchar=strtok((char*)temp,separater);
    while(splitchar!=NULL)
    {
        sprintf(dataout[i++],"%s",splitchar);
        splitchar=strtok(NULL,separater);
    }
    return i;
}

