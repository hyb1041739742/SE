#include <cstdio>
#include <cstring>
#include <io.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define pb push_back
#define ull unsigned long long
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 3e7+100;
pair<int,int> a[maxn]; 
pair<ull,ull> cut[maxn];
pair<ull,string> b[maxn], c[maxn];
map<string,string> turn;
map<string,ull> stop, mp, phrase;
string link[maxn];
vector<ull> g[300000];
ull wordNum, cutNum, maxNum = 0, phraseNum = -1, specifiedNum = inf;
string mode = "\\*.*", path = "res/article";
bool allowDown;
//test
void test(){
	freopen("res/article/Taylor.txt", "r", stdout);
//	fclose(stdout);
}
//统计字符使用频率 
void letterFrequency(string p){
	cin.clear();
	string f = "res/article/"+p; 
	freopen(f.c_str(), "r", stdin), freopen("output/letterFrequency.txt", "w", stdout);
	for(int i = 0; i < 26; i++) a[i].second = i;
	char ch; ull sum = 0;
	while(~scanf("%c", &ch)){
		if(ch>='A'&&ch<='Z') a[ch-'A'].first--, sum++;
		else if(ch>='a'&&ch<='z') a[ch-'a'].first--, sum++;
//		printf("%c", ch);
	}
	sort(a, a+26);
	for(int i = 0; i < 26; i++) printf("%c %.2f%\n", a[i].second+'a', -a[i].first*100.0/sum);
	fclose(stdin), fclose(stdout);
}
//单词分析 
void wordAnalyze(string p, string f){
	cin.clear();
//	freopen("res/article/Taylor.txt", "r", stdin);
	string tmp = p + "\\" +f;
	freopen(tmp.c_str(), "r", stdin);
//	cout << "now: " << f << endl;
	string s;
	ull sum = 0, last = 0, k = 0;
	while(cin>>s){
		string tmp;
		for(ull i = 0; i <= s.length(); i++){
			if((s[i]>='a'&&s[i]<='z')||(s[i]>='0'&&s[i]<='9')) tmp += s[i];
			else if(s[i]>='A'&&s[i]<='Z') tmp += s[i]-'A'+'a';
			else {
				if((tmp[0]>='0'&&tmp[0]<='9')||tmp=="") {
					if(sum-last>0) {
						if(sum-1-last>0) cut[k++] = {last, sum-1}, g[sum-last].pb(k-1), maxNum = max(maxNum, sum-last);
						last = sum;
					}
					continue;
				}
				if(turn.find(tmp)!=turn.end()) tmp = turn[tmp];
				if(stop.find(tmp)==stop.end()) {
					mp[tmp]++, link[sum++] = tmp;
					if(tmp.size()!=s.size()&&i!=s.length()) {
						if(sum-1-last>0) cut[k++] = {last, sum-1}, g[sum-last].pb(k-1), maxNum = max(maxNum, sum-last);
						last = sum;
					}
				}
				tmp.clear();
			}
		}
		wordNum = sum-1, cutNum = k-1;
	}
//	cout << sum << endl;
	fclose(stdin);
}
//处理单词 
void commonWord(string f){
	string tmp =  "output/commonWord_"+f;
	freopen(tmp.c_str(), "w", stdout);
	ull t = 0;
	for(map<string,ull>::iterator it = mp.begin(); it != mp.end(); it++)
		b[t++] = {-it->second, it->first};
	sort(b, b+t);
	for(ull i = 0; i < min(specifiedNum, t); i++) printf("%s %llu\n", b[i].second.c_str(), -b[i].first);
	mp.clear();
//	cout << b[i].second << " " << -b[i].first << endl;
	fclose(stdout);
    freopen( "CON", "w", stdout ); //定向输出到控制台
}
//处理短语 
void commonPhrase(string f){
	string tmp =  "output/commonPhrase_"+f;
	freopen(tmp.c_str(), "w", stdout);
//	for(int i = 0; i <= wordNum; i++) printf("%s ", link[i].c_str());
//	for(int i = 0; i <= cutNum; i++) printf("%d %d\n", cut[i].first, cut[i].second);
	int now = phraseNum;
	for(int i = now; i <= maxNum; i++){
		for(int j = 0; j < g[i].size(); j++){
			int p = g[i][j], l = cut[p].first, r = cut[p].second;
			for(int k = l; k <= r+1-now; k++){
				int tmp = now, id = k;
				string str;
				while(tmp--) str = str+link[id++]+" ";
				phrase[str]++;
//				while(tmp--) printf("%s ", link[id++].c_str());
//				printf("\n");
			}
		}
	}
	ull t = 0;
	for(map<string,ull>::iterator it = phrase.begin(); it != phrase.end(); it++)
		c[t++] = {-it->second, it->first};
	sort(c, c+t);
	for(ull i = 0; i < t; i++) printf("%s %llu\n", c[i].second.c_str(), -c[i].first);
	fclose(stdout);
}
void handle(string p, string f){
	wordAnalyze(p, f);
	if(phraseNum==-1) commonWord(f);
	else commonPhrase(f);
}
//动词归一化 
void normalize(string p){
	cin.clear();
//	freopen("res/verbs.txt", "r", stdin);
	string f = "res/"+p;
	freopen(f.c_str(), "r", stdin);
	char ch;
	string s, now;
	while(scanf("%c", &ch)&&cin>>s){
		if(ch=='\n') now = s;
		turn[s] = now;
	}
	fclose(stdin);
}
//过滤stopwords 
void filter(string p){
	cin.clear();
//	freopen("res/stopwords.txt", "r", stdin);
	string f = "res/"+p;
	freopen(f.c_str(), "r", stdin);
	string s;
	while(cin>>s) stop[s] = 1;
	fclose(stdin);
}
//查找文件 
void findfile(string path,string mode){
	_finddata_t file;
	intptr_t HANDLE;
	string Onepath = path + mode;
	HANDLE = _findfirst(Onepath.c_str(), &file);
	if (HANDLE == -1L) 	cout << "can not match the folder path" << endl;
	do {
		//判断是否有子目录  
		if (file.attrib & _A_SUBDIR){
			if(!allowDown) continue;
			//判断是否为"."当前目录，".."上一层目录
			if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0)){
				string newPath = path +"\\" + file.name;
//				cout << newPath << endl;
				findfile(newPath,mode);
			}
		}
		else cout << "Searching >>> " << path << "\\" << file.name <<  endl, handle(path, file.name);
	} while (_findnext(HANDLE, &file) == 0);
	_findclose(HANDLE);
}
//显示用法 
void help(){
	cout << "<Usage>" << endl;
	cout << "-f [file]  输出file中所有不重复的单词" << endl;
	cout << "-d [directory] 对directory下每一个文件执行-f [file]操作" << endl;
	cout << "-s -d [directory] 递归遍历目录下的所有子目录，对其中每个文件执行-f [file]操作" << endl;
	cout << "-n [number] -f [file] 输出file中出现次数最多的前number个单词" << endl;
	cout << "-p [number] -f [file] 输出file中number个词的短语" << endl;
	cout << "-x [stopword_file] -f [file]  在统计file中词汇的时候，跳过stopword_file中的词" << endl;
	cout << "-v [verb_file] 按照verb_file把文件中的动词的各种变形都归为它的原型来统计" << endl;
}

int main(int argc,char **argv){
	if(argc==1) return !printf("Please input the command\n");
	for(ull i = 1; i <= argc-1; i++){
		string s = argv[i];
		if(s[0]=='-') {
			if(s[1]=='h') help();
			else if(s[1]=='s') allowDown = true;
			else {
				if(i+1==argc) return !printf("Invalid command\n");
				string f = argv[++i];
				if(s[1]=='c') letterFrequency(f);
				else if(s[1]=='f') handle(".", f);
				else if(s[1]=='p') phraseNum = stoi(f);
				else if(s[1]=='n') specifiedNum = stoi(f);
				else if(s[1]=='v') normalize(f);
				else if(s[1]=='x') filter(f);
				else if(s[1]=='d') findfile(f, mode);
				else return !printf("Invalid command\n");
			}
		}
		else return !printf("Invalid command\n");
	}
}
