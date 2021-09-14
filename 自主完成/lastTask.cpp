#include<io.h>
#include<bits/stdc++.h>
#include<cstring>
#include<iostream>
#include <sstream>
using namespace std;

struct NODE{
	int num;
	string str;
	bool operator < (const NODE x) const {  
			if(num == x.num) return str < x.str; 
            return num > x.num; 
    }  
}node[100000]; 

void getAllFiles(string path, vector<string>& files, int flag) // flagΪ1��ʾҪ�ݹ� 
{
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
	string p;  //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR) && flag)  //�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files, flag);//�ݹ鵱ǰ�ļ���
				}
			}
			else    //�ļ�����
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));//�ļ���
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		_findclose(hFile);
	}
}

void mySort(int argc, char **argv, int i, int flag = 0)//��ӡ����� 
{
	int loss = 0;
	int count = 1;
	map<string, int> mp;
	for(map<string, int>::iterator z = mp.begin(); z != mp.end(); z++)
	{
		mp.erase(z);
	}
	for(int z = i+1; z < argc; z++)
	{
		if(mp[argv[z]] == 0)
		{
			mp[argv[z]] = count++;
			node[mp[argv[z]]].num=1;
			node[mp[argv[z]]].str=argv[z];
		}
		else 
		{
			node[mp[argv[z]]].num++;
		}
	}
	if(flag)
	{
		string context;
		string str;
		std::ifstream is(argv[i-1], std::ios::in);	
		if(is.is_open())	
		{
			std::stringstream strTemp;
	        strTemp<<is.rdbuf();
	        context =  strTemp.str();
			istringstream istr(context);
			while(!istr.eof())
			{
				istr>>str;
				if(mp[str])
				{
					node[mp[str]].num = 0;
					loss++;
				}
			}
	        is.close();
		}
		else 
		{
			cout << "ʧ��";
		}
	}
	sort(node+1, node+count);
	for(int z = 1; z < count-loss; z++)
	{
		cout << node[z].str << " " ; 
	}
}


void mySort2(int argc, char argv[][100], int i)//��ӡ����� 
{
	int count = 1;
	map<string, int> mp;
	for(map<string, int>::iterator z = mp.begin(); z != mp.end(); z++)
	{
		mp.erase(z);
	}
	
	for(int z = i+1; z < argc; z++)
	{
		if(mp[argv[z]] == 0)
		{
			mp[argv[z]] = count++;
			node[mp[argv[z]]].num=1;
			node[mp[argv[z]]].str=argv[z];
		}
		else 
		{
			node[mp[argv[z]]].num++;
		}
	}
	
	sort(node+1, node+count);
	for(int z = 1; z < count; z++)
	{
		cout << node[z].str << " "; 
	}
}


void solve2(char **argv, int i, int flag)//flag��ʾҪ�ݹ� 
{
//---------------------------�����ȡ��Ŀ¼�µ������ļ�����-------------------------------- 
			string data_dir = argv[i];
			vector<string> files;
			getAllFiles(data_dir, files, flag);
//---------------------------��������ļ����ִ��ļ�--------------------------------------
			for(int z = 0; z < files.size(); z++)
			{	
				string context;  //�ļ������� 
				string str1;
				int argc = 1;
				char argv[10000][100]; //ÿ������ ,���10000�� 
				char c[2000]; 
				for(int g = 0; g < files[z].size(); g++)
					c[g] = files[z][g];
				std::ifstream is(c, std::ios::in);	
//				cout << files[z] << endl;
				if(is.is_open())	
				{
					std::stringstream strTemp;
			        strTemp<<is.rdbuf();
			        context =  strTemp.str();
//			        cout << context;
			        is.close();
				}
				else {
					cout << "ʧ��";
				}
				istringstream istr(context);
				while(!istr.eof())
				{
					istr >> str1;
					for(int g = 0; g < str1.size(); g++)
					{
						argv[argc][g] = str1[g];
					}
					argc++;
				} 
				mySort2(argc, argv, 0);
				cout << endl;
			} 			
}


int main(int argc, char *argv[])
{
	for(int i = 1; i < argc; i++)  //��һ�����ļ������� 
	{
		if(strcmp("-f", argv[i]) == 0)
		{
			mySort(argc, argv, 1);
			break;
		} 
		else if(!strcmp("-d", argv[i]) && !strcmp("-s", argv[i+1]))
		{
			i = i+2;
			solve2(argv, i, 1);
			break;
		}
		else if(!strcmp("-d", argv[i]))
		{
			i = i + 1;
			solve2(argv, i, 0);
			break;
		}
		else if(!strcmp("-x", argv[i]))
		{
			mySort(argc, argv, 3, 1);
			break;
		}
		
	}
	return 0;
} 
