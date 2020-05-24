#include <string.h>
#include<stdlib.h>
#include "intal.h"
#include<stdio.h>
#define MAX(a,b)(((a)>(b))? (a):(b))
#define MIN(a,b)(((a)<(b))? (a):(b))

static void swap1(char **str1_ptr, char **str2_ptr) 
{ 
  char *temp = *str1_ptr; 
  *str1_ptr = *str2_ptr; 
  *str2_ptr = temp; 
}

static char* maxval(char* intal1,char* intal2)
{
    if (strlen(intal1)>strlen(intal2))
        return intal1;
    else if(strlen(intal1)<strlen(intal2))
        return intal2;
    else
    {   int flag=0;
        for(int i=0;i<strlen(intal1);++i)
        {
            int z=intal_compare(intal1,intal2);
            if (z==1)
                flag=1;
            else if(z==-1)
                flag=-1;
        }
        if (flag>=0)
            return intal1;
        else
            return intal2;        
    }
}

char* strrev(char *str)
{
      char *p1, *p2;
      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

int intal_compare(const char* intal1, const char* intal2)
{
    int length1=strlen(intal1);
    int length2=strlen(intal2);
    if (length1>length2)
        return 1;
    else if (length1<length2)
        return -1;
    
    else
    {
        int flag=0;
        for(int i=0;i<length1;++i)
            {
            if ((intal1[i]-'0')>(intal2[i]-'0'))
                {
				    flag=1;
				    break;
                }
            else if ((intal1[i]-'0')<(intal2[i]-'0'))
                {	
                    flag=-1;
				    break;
                }
            }
        return flag;
    }
}

char* intal_add(const char* intal1, const char* intal2)
{	
	int length1=strlen(intal1);
    int length2=strlen(intal2);
    
    char *intal11=malloc(sizeof(char)*(length1+1));
    for(int j=0;j<length1;j++)
    	intal11[j]=intal1[j];
    intal11[length1]='\0';
    char *intal21=malloc(sizeof(char)*(length2+1));
    for(int j=0;j<length2;j++)
    	intal21[j]=intal2[j];
    intal21[length2]='\0';
    
    int loopvar=MIN(length1,length2);
    int lenans=MAX(length1,length2)+2;
    char *ans=malloc(sizeof(char)*lenans);
    strrev(intal11);
    strrev(intal21);
    
    int carry=0;
    int i=0;
    for(;i<loopvar;++i)
    {
        ans[i]=((intal11[i]-'0')+(intal21[i]-'0')+carry)%10+'0';
        carry=((intal11[i]-'0')+(intal21[i]-'0')+carry)/10;
    }
    
    while(i<lenans-2 && intal11[i]!='\0')
    { 
        ans[i]=((intal11[i]-'0')+carry)%10+'0';
        carry=((intal11[i]-'0')+carry)/10;
        ++i;
    }
    while(i<lenans-2 && intal21[i]!='\0')
    {	
	    ans[i]=((intal21[i]-'0')+carry)%10+'0';
        carry=((intal21[i]-'0')+carry)/10;
        ++i;
    }
    if (carry)
    	ans[i++]=carry+'0';
    //printf("ans %s\n",ans);
	ans[i]='\0';
	//printf("ans%s\n",ans);
	free(intal11);
	free(intal21);
	strrev(ans);
    return ans;
}

char* intal_diff(const char* intal1, const char* intal2)
{	
	int res=intal_compare(intal1,intal2);
    int length1=strlen(intal1);
    int length2=strlen(intal2);

    char *intal11=malloc(sizeof(char)*(length1+1));
    for(int j=0;j<length1;j++)
    	intal11[j]=intal1[j];
    intal11[length1]='\0';
    char *intal21=malloc(sizeof(char)*(length2+1));
    for(int j=0;j<length2;j++)
    	intal21[j]=intal2[j];
    intal21[length2]='\0';

	if (res==1)
		swap1(&intal11,&intal21);
    
    strrev(intal11);
    strrev(intal21);

    int lenans=MAX(length1,length2)+1;
    int minans=MIN(length1,length2);
    char *ans=malloc(sizeof(char)*lenans);
    int borrow=0;
    int i=0;
    int l=0;
    
    for(;i<minans;++i)
    {   
        l=(intal21[i]-'0')-(intal11[i]-'0')-borrow;
        if (l>=0)
            {ans[i]=l+'0';borrow=0;}
        else
        {
            l+=10;
            ans[i]=l+'0';
            borrow=1;
        }        
    }
	//printf("%d %s\n",borrow,intal11);
    while(i<lenans-1 && intal11[i]!='\0')
    {	
        l=(intal11[i]-'0')-borrow;
        if (l>=0)
            {ans[i]=l+'0';borrow=0;}
        else
        {
            l+=10;
            ans[i]=l+'0';
            borrow=1;
        }
        ++i;
        //printf("ans %s\n",ans);
    }
    
    while(i<lenans-1 && intal21[i]!='\0')
    {	
		l=(intal21[i]-'0')-borrow;
        if (l>=0)
            {ans[i]=l+'0';borrow=0;}
        else
        {
            l+=10;
            ans[i]=l+'0';
            borrow=1;
        }
		++i;
    }
    ans[i]='\0';  
    strrev(ans);
    i=0;
    while(i<strlen(ans)-1 && ans[i]=='0')
    	++i;
    free(intal11);
    free(intal21);
	char *ress=malloc(sizeof(char)*(strlen(ans+i)+1));
	strcpy(ress,ans+i);
	free(ans);
    return ress;
}

char* intal_mod(const char* intal1, const char* intal2)
{	
	if(intal_compare(intal1,intal2)==-1)
		{
		char* result=malloc(sizeof(char) * (strlen(intal1)+1));
		strcpy(result,intal1);
		return result;
		}
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	int difflen=len1-len2;
	for(int i=0;i<len2;++i)
		{
			if ((intal1[i]-'0')<(intal2[i]-'0'))
				{--difflen;break;}
			else if ((intal1[i]-'0')>(intal2[i]-'0'))
				{break;}
		}
	if(difflen>0)
	{
		char* extended=malloc(sizeof(char) * (difflen+len2+1));
		for(int i=0;i<len2;i++)
			extended[i]=intal2[i];
		int middie=len2;
		for(int i=0;i<difflen;i++)
			extended[i+middie]=48;
		extended[difflen+middie]='\0';
		extended=intal_diff(intal1,extended);
		return intal_mod(extended,intal2);
	}
	return intal_mod(intal_diff(intal1,intal2),intal2);
}

char* intal_gcd(const char* intal1, const char* intal2)
{	
    if (0 == intal_compare(intal2, "0"))
        {
            char *res=malloc((strlen(intal1)+1)*sizeof(char));
            strcpy(res,intal1);
            return res;
        }
    return intal_gcd(intal2,intal_mod(intal1,intal2));
}

static char* findintermediate(int index,const char *intal2,const char* intal1)
{   int fixed=(strlen(intal2)-index);
    int sizeinte=strlen(intal1)+1+fixed;
    char *inte=malloc(sizeof(char)*(sizeinte));
    int carry=0;
    int value=intal2[index]-'0';
    for (int i=strlen(intal1)-1;i>=0;--i)
    {   
        int k=value*(intal1[i]-'0')+carry;
        inte[i+1]=(k%10)+'0';
        carry=k/10;
    }
    
    int flag=0;
    if (carry)
        inte[0]=carry+'0';
    else
    	flag=1;

    for(int i=sizeinte-fixed;i<sizeinte-1;++i)
        inte[i]='0';
    inte[sizeinte-1]='\0';
    if (flag)
    	++inte;
    	
    return inte;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    int length1=strlen(intal1);
    int length2=strlen(intal2);
    
    if ((0 == intal_compare(intal2, "0")) || (0 == intal_compare(intal1, "0")))
        {char *res=malloc(sizeof(char)*2);
res[0]='0';
res[1]='\0';
return res;}
        
    char* intal11=malloc(sizeof(char) * (length1+1));

    for(int j=0;j<length1;j++)
    	intal11[j]=intal1[j];
    intal11[length1]='\0';
    char* intal21=malloc(sizeof(char) * (length2+1));
    for(int j=0;j<length2;j++)
    	intal21[j]=intal2[j];
    intal21[length2]='\0';
    
    char *mainans=malloc(sizeof(char)*(length1+length2+1));
    mainans="0\0";
    for(int i=strlen(intal2)-1;i>=0;--i)
    {
        char *intermediate=findintermediate(i,intal2,intal1);
        mainans=intal_add(mainans,intermediate);
	//free(intermediate);
    }
//printf("here\n");
    free(intal11);
    free(intal21);
    return mainans;
}
/*
static char* divby2(char* dividend)
{
    //printf("dividend %s\n",dividend);
	static char quotient[2000];
    int divisor=2;
    long temp=0;
    int i=0,j=0;
    while(dividend[i]){
         temp = temp*10 + (dividend[i] -48);
         if(temp<divisor){
             quotient[j++] = 48;
         }
         else{
             quotient[j++] = (temp / divisor) + 48;
             temp = temp % divisor;
         }
         i++;
    }
    quotient[j] = '\0';
    //printf("quotient %s\n",quotient);
    return quotient;
}

static char* intal_pow1(char* intal1, char* intal2)
{	
    if (0==intal_compare(intal2,"1"))
        return intal1;
    if (0==intal_compare(intal2,"0"))
        return "1";
    
	char *s=intal_multiply(intal1,intal1);	
    if (0==intal_compare(intal_mod(intal2,"2"),"1"))
    	{
        	char *divv=divby2(intal_diff(intal2,"1"));
			return intal_multiply(intal1,intal_pow1(s,divv));
		}
    else
        {
			char *divv=divby2(intal2);
			return intal_pow1(s,divv);   
		}
}

char* intal_pow(char* intal1, char* intal2)
{	
    if (0==intal_compare(intal1,"0"))
        return "0";
    if (0==intal_compare(intal2,"1"))
        return intal1;
    if (0==intal_compare(intal1,"1"))
        return "1";
    return (intal_pow1(intal1,intal2));
}
*/

static char* intal_pow1(const char* intal1, unsigned int n)
{
    if (n==1)
        {
			char* result=malloc(sizeof(char)*(strlen(intal1)+1));
			strcpy(result,intal1);
			return result;
		}
    if (n==0)
        {char *result=malloc(sizeof(char)*2);
result[0]='1';
result[1]='\0';
return result;}
    char *result = intal_multiply(intal1,intal1);
    if ((n&1)==0)
        {   
            n>>=1;
            return intal_pow1(result,n);
        }
    else
        {
            n-=1;
            n>>=1;
            return intal_multiply(intal1,intal_pow1(result,n));
        }
    
}

char* intal_pow(const char* intal1, unsigned int n)
{	
    if (0==intal_compare(intal1,"0"))
        {char *result=malloc(sizeof(char)*2);
result[0]='0';
result[1]='\0';
return result;}

    if (n==1)
        {
			char* result=malloc(sizeof(char)*(strlen(intal1)+1));
			strcpy(result,intal1);
			return result;
		}

    if (0==intal_compare(intal1,"1"))
        {char *result=malloc(sizeof(char)*2);
         result[0]='1';
         result[1]='\0';
         return result;}
    return (intal_pow1(intal1,n));
}

char* intal_factorial(unsigned int n)
{
    char* answer=malloc(sizeof(char)*2);
    answer[0]='1';
    answer[1]='\0';
    while(n!=0)
        {
            char *nstr=malloc(sizeof(char)*1005);
            sprintf(nstr,"%u",n--);
            //printf("%s\n",nstr);
            answer=intal_multiply(answer,nstr);
        }
    return answer;
}

char* intal_fibonacci(unsigned int n)
{	
	n+=1;
    if (n==1)
    	{char *result=malloc(sizeof(char)*2);
		 result[0]='0';
		 result[1]='\0';
		 return result;}
    else if(n==2)
    	{char *result=malloc(sizeof(char)*2);
		 result[0]='1';
		 result[1]='\0';
		 return result;}
    char *string1=malloc(sizeof(char)*1006);
    char *string2=malloc(sizeof(char)*1006);
    
    strcpy(string1,"0");
    strcpy(string2,"1");
    n-=2;
    char *answer;
    while(n>0)
    {   
		answer=intal_add(string1,string2);
		//printf("%u %s\n",n,answer);
    	--n;
        strcpy(string1,string2);
        strcpy(string2,answer);
    }
    free(string1);
    free(string2);
    return answer;
}
/*
char* intal_bincoeff(unsigned int n, unsigned int k)
{   
    if (k==0 || k==n)
        return "1";
    return intal_add(intal_bincoeff(n-1,k),intal_bincoeff(n-1,k-1));
}
*/
char* intal_bincoeff(unsigned int n, unsigned int k)
{	
    if (n-k<k)
	k=n-k;//very very important
    char** dp=malloc(sizeof(char* ) * (k+1));
    for(int i=0;i<=k;++i)
    	dp[i]="0";
    dp[0]=malloc(sizeof(char)*2);
    dp[0][0]='1';
    dp[0][1]='\0';
    for(int i=1;i<=n;++i)
    {
		int range=i>k?k:i;
    	for(int j=range;j>0;--j)
    	{ 
			dp[j]=intal_add(dp[j],dp[j-1]);
        }
	}
    char* result=malloc(sizeof(char) * (strlen(dp[k])+1));
    strcpy(result,dp[k]);
	for(int i=0;i<=k;++i)
		free(dp[i]);
	free(dp);
    return result;
}

int intal_max(char **arr, int n)
{	
	char *maxi=malloc(sizeof(char)*1006);
    strcpy(maxi,arr[0]);
    int index=0;
    for(int i=1;i<n;++i)
    {	
        if (intal_compare(arr[i],maxi)==1)
        {
            strcpy(maxi,arr[i]);
            index=i;
        }
    }
    free(maxi);
    return index;
}

int intal_min(char **arr, int n)
{
    char *mini=malloc(sizeof(char)*1006);
    strcpy(mini,arr[0]);
    int index=0;
    for(int i=1;i<n;++i)
    {
        if (intal_compare(arr[i],mini)==-1)
        {
            strcpy(mini,arr[i]);
            index=i;
        }
    }
    free(mini);
    return index;
}

int intal_search(char **arr, int n, const char* key)
{
    int index=-1;
    for(int i=0;i<n;++i)
    {//printf("%s\n%s\n",arr[i],key);
        if(intal_compare(key,arr[i])==0)
            return i;
    }
    return index;
}

static int intal_binsearch1(char **arr,int low,int high, const char* key)
{
    int index=-1;
    while(low<=high)
    {   //printf("%d %d ",low,high);
        int mid=low+(high-low)/2;
        int k=intal_compare(arr[mid],key);
        //printf("%d\n",k);
        if (k==0)
            {index=mid;high=mid-1;}
        else if(k==-1)
            low=mid+1;
        else
            high=mid-1;
    }
    return index;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    return intal_binsearch1(arr,0,n-1,key);
}

static void mergeSortedHalfs(char** arr,int start,int mid,int end)
{
    int i=start;int j=mid+1;
	char** a=malloc(1001 * sizeof(char*));
	//for(int l=0;l<end-start+1;++l)
		//a[i]="0";
    int k=0;
    while(i<mid+1 && j<=end)
    {
        int z=intal_compare(arr[i],arr[j]);	
        if (z==-1)
        {a[k++]=arr[i++];}
        else
        {a[k++]=arr[j++];} 
    }       
    //printf("hereeeeeeeee\n");
    while(i<=mid)
        a[k++]=arr[i++];
    while(j<=end)
        a[k++]=arr[j++];
    for(i=start,k=0;i<=end;++i,++k)
        arr[i]=a[k];
    /*for(k=0;k<end-start+1;++k)
    	free(a[k]);*/
    free(a);
    //printf("hereinthe\n");
}

static void MergeSort(char** arr,int start,int end)
{
    if(start<end)
    {
        int mid=start + (end-start)/2;
        MergeSort(arr,start,mid);
        MergeSort(arr,mid+1,end);
        mergeSortedHalfs(arr,start,mid,end);
    }
}

void intal_sort(char **arr, int n)
{
    MergeSort(arr,0,n-1);
}
/*
static char* coin_row(char** arr,int index,int n)
{	//printf("index %d n %d\n",index,n);
    if (index==n)
        return "0";
    if (index==n-1)
        return arr[index];
    if (index==n-2)
        return maxval(arr[index],arr[index+1]);
    //printf("here\n");
    return maxval(intal_add(arr[index],coin_row(arr,index+2,n)),coin_row(arr,index+1,n));
}
265252866478857725302975146666678
char* coin_row_problem(char **arr, int n)
{return coin_row(arr,0,n);}*/

char* coin_row_problem(char **arr, int n)
{
    	if (n==0)
    		return "0";
    	char *prev="0";
    	char *next=malloc(sizeof(char)*(strlen(arr[0])+1));
    	strcpy(next,arr[0]);
        char* result="0";
    	for(int i=1;i<n;++i)
    	{
    		result=maxval(intal_add(prev,arr[i]),next);
    		//printf("%s %s %s\n",prev,next,result);
    		prev=next;
    		next=result;
		}
		//free(result);
		return next;
}
/*
#include<time.h>
int main()
{
	int n = 12;
	char **a = (char**) malloc(n * sizeof(char*));
	for(int i = 0; i < n; i++) {
		a[i] = (char*) malloc(1001 * sizeof(char));
	}
	
	strcpy(a[0], "1234512345123451234512345");
	strcpy(a[1], "1234512345123451234512345");
	strcpy(a[2], "0");
	strcpy(a[3], "1234512345123451234512345");
	strcpy(a[4], "1234512345123451234512344");
	strcpy(a[5], "12");
	strcpy(a[6], "265252859812191058636308480000000");
	strcpy(a[7], "265252859812191058636308480000000");
	strcpy(a[8], "5432154321543215432154321");
	strcpy(a[9], "3");
	strcpy(a[10], "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	strcpy(a[11], "1230231922161117176931558813276752514640713895736833715766118029160058800614672948775360067838593459582429649254051804908512884180898236823585082482065348331234959350355845017413023320111360666922624728239756880416434478315693675013413090757208690376793296658810662941824493488451726505303712916005346747908623702673480919353936813105736620402352744776903840477883651100322409301983488363802930540482487909763484098253940728685132044408863734754271212592471778643949486688511721051561970432780747454823776808464180697103083861812184348565522740195796682622205511845512080552010310050255801589349645928001133745474220715013683413907542779063759833876101354235184245096670042160720629411581502371248008430447184842098610320580417992206662247328722122088513643683907670360209162653670641130936997002170500675501374723998766005827579300723253474890612250135171889174899079911291512399773872178519018229989376");
	char *result1;
intal_sort(a,12);
for(int i=0;i<12;++i)
	printf("%s\n",a[i]);
	printf("%d\n",intal_binsearch(a,12,"1234512345123451234512346"));
}
*/
