#include<fstream>//文件流

#include<iostream>

#include<string>

#include<iomanip>

using namespace std;

 

const int D[] = {3,5,8,11,13,14,19,21};//预定再随机数

const int HASH_MAXSIZE = 50;//哈希表长度

 

//记录信息类型

class DataInfo

{

public:

	DataInfo();//默认构造函数

	friend ostream& operator<<(ostream& out, const DataInfo& dataInfo); //重载输出操作符
//private:

	string name;//姓名

	string phone;//电话号码

	string studentId;//学号	

	string sex;//性别

	char sign;//冲突的标志位，'1'表示冲突，'0'表示无冲突

	DataInfo(string Name, string Phone, string StudentId, string Sex){
		this->name = Name;
		this->phone = Phone;
		this->studentId = StudentId;
		this->sex = Sex;
		this->sign = 0;
	}

};

 

DataInfo::DataInfo():name(""), phone(""), studentId(""), sex(""), sign('0')

{

 

}

//存放记录的哈希表类型

class HashTable

{

public:

	HashTable();//默认构造函数

	~HashTable();//析构函数

	int Random(int key, int i);// 伪随机数探测再散列法处理冲突

	int Hashname(DataInfo *dataInfo);//以名字为关键字建立哈希表	

	int Rehash(int key, string str);// 再哈希法处理冲突   注意处理冲突还有链地址法等

	void Hash(char *fname, int n);// 建立哈希表

	//fname 是数据储存的文件的名称，用于输入数据，n是用户选择的查找方式	

	int Findname(string name);// 根据姓名查找哈希表中的记录对应的关键码

	void Outhash(int key);// 输出哈希表中关键字码对应的一条记录

	int deleteHash(int key);


//private:

    DataInfo *value[HASH_MAXSIZE];

	int length;//哈希表长度

};


int HashTable::deleteHash(int key){
	if(value[key]->sign != '0'){
		value[key]->sign = '0';
		length --;
		return 1;
	}
	return 0;
}
 

HashTable::HashTable():length(0)//默认构造函数

{

	//memset(value, NULL, HASH_MAXSIZE*sizeof(DataInfo*));

	for (int i=0; i<HASH_MAXSIZE; i++)

	{

		value[i] = new DataInfo();

	}

}

 

HashTable::~HashTable()//析构函数

{

	delete[] *value;

}

int HashTable::Random(int key, int i)// 伪随机数探测再散列法处理冲突

{//key是冲突时的哈希表关键码，i是冲突的次数，N是哈希表长度

	//成功处理冲突返回新的关键码，未进行冲突处理则返回-1

	int h;

	if(value[key]->sign == '1')//有冲突

	{

		h = (key + D[i]) % HASH_MAXSIZE;

		return h;

	}

	return -1;

}

int HashTable::Hashname(DataInfo *dataInfo)//以名字为关键字建立哈希表

{//利用除留取余法建立以名字为关键字建立的哈希函数，在发生冲突时调用Random函数处理冲突

	int i = 0;	

	int key = 0;

 

    for (int t=0; dataInfo->name[t]!='\0'; t++)   

	{		

		key = key + dataInfo->name[t];

	}

	key = key % 42;

	while(value[key]->sign == '1')//有冲突

	{

		key = Random(key, i++);//处理冲突
		if(i >= 8){
			return -1;
		}

	}

	if(key == -1) exit(1);//无冲突

	length++;//当前数据个数加

	value[key]->name = dataInfo->name;

	value[key]->studentId = dataInfo->studentId;

	value[key]->phone = dataInfo->phone;

	value[key]->sex = dataInfo->sex;

	value[key]->sign = '1';//表示该位置有值

	//cout << value[key]->name << "  " << value[key]->phone << "  "  << value[key]->studentId << endl;
	return 0;

}

 

int HashTable::Rehash(int key, string str)// 再哈希法处理冲突

{//再哈希时使用的是折叠法建立哈希函数	

	int h;

	int num1 = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');

	int num2 = (str[4] - '0') * 1000 + (str[5] - '0') * 100 + (str[6] - '0') * 10 + (str[7] - '0');

	int num3 = (str[8] - '0') * 100  + (str[9] - '0') * 10  + (str[10] - '0');

	h = num1 + num2 + num3;

	h = (h + key) % HASH_MAXSIZE;

	return h;

}
 
void HashTable::Outhash(int key)//输出哈希表中关键字码对应的记录

{  

	if((key==-1)||(value[key]->sign=='0'))

		cout << "没有找到这条记录！" << endl;

	else

	{		

		cout << left << setw(15) << value[key]->name;

		cout << left << setw(15) << value[key]->phone;

 		cout << left << setw(15) <<value[key]->studentId;

		cout << left << setw(15) <<value[key]->sex << endl;

	}

}

void HashTable::Hash(char *fname, int n)//建立哈希表

//fname是数据储存的文件的名称，用于输入数据，n是用户选择的查找方式

//函数输入数据，并根据选择调用Hashname或Hashphone函数进行哈希表的建立

{

	ifstream fin;		

	int i;

	fin.open(fname);//读文件流对象

	if(fin.fail())

	{

		cout << "文件打开失败！" << endl;

		exit(1);

	}

	while(!fin.eof())//按行读入数据

	{

		DataInfo *dataInfo = new DataInfo();

		char* str = new char[100];		

		fin.getline(str, 100, '\n');//读取一行数据

 

		if(str[0] == '*')//判断数据结束

		{

			break;

		}

 

		i = 0;//记录字符串数组的下标

		//a-z:97-122     A-Z:65-90    

		//本程序的姓名和地址都使用小写字母

		while((str[i] < 97) || (str[i] > 122))//读入名字

		{

			i++;

		}

 

		for(; str[i]!=' '; i++)

		{			

			dataInfo->name += str[i];			

		}

 

		while(str[i] == ' ')

		{

			i++;

		}

 

		for(int j=0; str[i]!=' '; j++,i++)//读入电话号码

		{			

			dataInfo->phone += str[i];

		}

 

		while(str[i] == ' ')

		{

			i++;

		}

 

		for(int j=0; str[i]!=' '; j++,i++)

		{			

			dataInfo->studentId += str[i];

		}

		while(str[i] == ' ')

		{

			i++;

		}

		for(int j=0; str[i]!=','; j++,i++)

		{			

			dataInfo->sex += str[i];

		}
 

		if(n == 1)

		{			

			Hashname(dataInfo);

		}

		delete []str;

		delete dataInfo;

	}	

	fin.close();

}

 

int HashTable::Findname(string name)//根据姓名查找哈希表中的记录对应的关键码

{

	int i = 0;

	int j = 1;

	int t;

	int key = 0;

	

	for(key=0, t=0; name[t] != '\0'; t++)

	{

		key = key + name[t];

	}

	key = key % 42;

	while((value[key]->sign == '1') && (value[key]->name != name))

	{  

		key = Random(key, i++);

		j++;

		if(j >= length) return -1;

	}

	return key;

}

int main()

{

	//WriteToOldTxt();	

	int k, tag = 0;

	int ch;	

	char *Fname = "./old.txt";

	HashTable *ht = new HashTable;

	while(1)

	{

		system("cls");//cls命令清除屏幕上所有的文字

		cout << "欢迎使用本系统！" << endl << endl;

		cout << "请选择数据" << endl;

		cout << "1.使用已有数据文件" << endl;

		cout << "0.结束" << endl;

		cout << "输入相应序号选择功能：";

		cin >> k;

		switch(k)

		{

		case 0:

			return 0;

		case 1:

			break;

		default:

			cout << "输入序号有误，退出程序。" << endl;	

			return 0;

		}

		ht->Hash(Fname, 1);

		while(1)

		{

			int choice;

			cout << endl << "请选择功能" << endl;

			cout << "1.输入姓名查找数据" << endl;

			cout << "2.显示哈希表" << endl;

			cout << "3.增加元素" << endl;

			cout << "4.删除元素" << endl;

			cout << "0.退出"<<endl;

			cout << "输入相应序号选择功能：";

			cin >> choice;

			switch(choice)

			{

			case 0:

				tag = 1;

				break;

			case 1:	

				{

					int key1;					

					string name;					

					cout << "请输入姓名：";

					cin >> name;					

					key1 = ht->Findname(name);

					ht->Outhash(key1);	

				}

				break;

 

			case 2:	

				{

					for(int i=0; i<HASH_MAXSIZE; i++)

					{

						if(ht->value[i]->sign!='0')

						{

							ht->Outhash(i); 

						}

					}	

				}							

				break;

			case 3:	

				{

					int key1;					

					string name;					

					cout << "请输入姓名： ";

					cin >> name;

					string sex;					

					cout << "请输入性别： ";

					cin >> sex;

					string sid;					

					cout << "请输入学号： ";

					cin >> sid;

					string phone;					

					cout << "请输入电话： ";

					cin >> phone;	

					cout << endl;			

					DataInfo *temp = new DataInfo(name, sex, phone, sid);

					if(ht->Hashname(temp) == -1) cout << "增加失败 " << endl;

					else cout << "增加成功 " << endl;
				}							

				break;

			case 4:	

			{

				int key1;					

				string name;					

				cout << "请输入姓名：";

				cin >> name;					

				key1 = ht->Findname(name);

				if(ht->deleteHash(key1)){

					cout << "删除成功" << endl;
				
				}	

				else cout << "delete failed! " << endl;

			}

			break;

			default:

				cout << endl << "您的输入有误！" << endl;				

			}
			if(tag == 1){

				tag = 0;

				break;
			}

		}

	}

	system("pause");	

}

 

 
