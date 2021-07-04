#include <bits/stdc++.h>
#include <cJSON.h>
#include <cJSON.c>
#include <Windows.h>
#include<sys/stat.h>  //stat
//#include"include/pdflib.h"
//#include"include/pdflib.hpp"

//两个PDF库由于配置原因无法直接使用

// testpdf.cpp : 定义控制台应用程序的入口点。

using namespace std;

const int maxn = 1e3 + 10;
const int inf = 0x3f3f3f3f;

string s;
vector<string> a;
vector<string> b;

//Cjson 的指针结构 我也不知道现在到底怎么去使用这个东西，反正先把他拿下来
typedef struct CJSON {
	struct CJSON *next;
	struct CJSON *prev;
	struct CJSON *child;
	int type;
	char *valuestring;
	int valueint;
	double valuedouble;
	char *string;
} CJSON;

//Cjson获取外面的文件内存以及相关信息
size_t get_file_size(const char *filepath) {

	if(NULL == filepath) return 0;
	struct stat filestat;
	memset(&filestat,0,sizeof(struct stat));
	if(stat(filepath,&filestat) == 0) return filestat.st_size;//获取文件的信息
	else return 0;

}

void read_file(char *filename) {
	FILE *fp;
	/*get file size*/
	size_t size = get_file_size(filename);
	if(0 == size) {
		printf("get_file_size failed!!!\n");
	}
	/*malloc memory*/
	void *buf = malloc(size+1);  //存在问题的 很奇怪就运行了？？？？！！！！！
	if(NULL == buf) {
		printf("malloc failed!!!\n");
	}
	memset(buf,0,size+1);
	fp=fopen(filename,"rb");
	fread(buf,1,size,fp);
	fclose(fp);
	printf("read file %s complete, size=%d.\n",filename,size);
	free(buf);
}

int analylise_cjso() 
{
	// 解析Object
	char text[]="{\"name\":\"Tom\",\"age\":18}";
	cJSON * root = cJSON_Parse(text);
	if(!root) 
	{
		printf("no json\n");
		return -1;
	}
//name
	cJSON *name = cJSON_GetObjectItem(root, "name");
	if (!name) 
	{
		printf("no name!\n");
		return -1;
	}
	 else 
	 {
		printf("%s\n",name->valuestring);
		return 0;
	}
//age
	cJSON *age = cJSON_GetObjectItem(root, "age");
	if (!age) 
	{
		printf("no age!\n");
		return -1;
	} else 
	{
		printf("%d\n",age->valueint);
		return 0;
	}
	cJSON_Delete(root);
}

//重新构建字符串，将单行字符串里面的tab 空格 //注释全部删除
string rebuild(string &s) {
	int start = s.find("//");
//	printf("%d\n",start);
	if(start != -1) s.erase(start,s.length());
	start = s.find("/*");
	int end = s.find("*/");
	if(start != -1) s.erase(start,end+2);
	//删除“//”引导的注释
	while(s[0]==' '&&s.length()>0) s.erase(0,1);
	while(s[0]=='\t'&&s.length()>0) s.erase(0,1);
//	cout<<s<<endl;
	return s;
}

//重新构建字符串，将多行字符串里面的 tab 空格 // 以及/**/注释全部删除

void rebuild_mul_str(vector<string> &a) {
	for(int i=1; i<a.size(); i++) a[i]=rebuild(a[i]);
	int flag = 1; //确保到时候/*的前面还有内容时候不被搞出去
	int id;
	for(int i=0; i<a.size(); i++) {
		id = a[i].find("/*");
		if(id==-1) {
			if(flag==1) b.push_back(a[i]);
		} else {
			string tmp = a[i].substr(0,id);
			tmp = rebuild(tmp);
			b.push_back(tmp);
			flag=0;
		}
		id = a[i].find("*/");
		if(id != -1) {
			string tmp = a[i].substr(id+2);
			tmp = rebuild(tmp);
			b.push_back(tmp);
			flag = 1;
		}
	}
	a = b;
	for(int i=0; i<a.size(); i++) {
		if(a[i].length()==0) {
			a.erase(a.begin()+i);
			i--;
		}
	}
}

void print(vector<string>& a) {
	for(int i=0; i<a.size(); i++) cout<<a[i]<<endl;
}

//提纯字符串 通过变量名规则去过滤一些字符串 ，从而加大字符串在比较时候的重复率
void pure_str(vector<string>& a) {
	for(int i=0; i<a.size(); i++) {
		a[i]=rebuild(a[i]);
		int pos1=a[i].find(" ");
		int pos2=a[i].find("=");
		int pos3=a[i].find(";");
		int pos4=a[i].find("[");
		if(pos1==-1) pos1=inf;
		if(pos2==-1) pos2=inf;
		if(pos3==-1) pos3=inf;
		if(pos4==-1) pos4=inf;
		int len = min(min(pos1,pos2),min(pos3,pos4));
		if(len < inf) a[i]=a[i].substr(0,len);
	}
}

//编写LCS算法从而判断任意两行之中相同字符串的相似度 ,最终返回最长相同字串的长度
int dp[maxn*maxn];
int LCS(string s1,string s2) {
	int len1=s1.length();
	int len2=s2.length();
	int last=0;
	int ans=0;
	memset(dp,0,sizeof dp);
	for(int i=1; i<=len1 ; i++) {
		last = 0;
		for(int j=1; j<=len2; j++) {
			int temp = dp[j];
			if(s1[i-1]==s2[j-1]) dp[j]=last+1;
			else dp[j]=max(dp[j],dp[j-1]);
			last = temp;
		}
		ans=max(ans,dp[len2]);
	}
	return ans;
}

double rate_lcs(string s1,string s2) {
	return (double)LCS(s1,s2)/(double)min(s1.length(),s2.length());
}

int T = 2;
int main() {
	while(T--) {
		getline(cin,s);
		a.push_back(s);
	}
	rebuild_mul_str(a);
	for(int i=0; i<a.size(); i++) cout<<a[i]<<endl;
	pure_str(a);
	//for(int i=0;i<a.size();i++) cout<<i<<"i a[i]:"<<a[i]<<endl;
	printf("%d\n",LCS(a[0],a[1]));
	printf("%.2f\n",rate_lcs(a[0],a[1]));
	//read_file(FILENAME);
	return 0;
}

