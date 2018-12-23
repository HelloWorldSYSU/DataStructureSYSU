#include<fstream>//�ļ���

#include<iostream>

#include<string>

#include<iomanip>

using namespace std;

 

const int D[] = {3,5,8,11,13,14,19,21};//Ԥ���������

const int HASH_MAXSIZE = 50;//��ϣ����

 

//��¼��Ϣ����

class DataInfo

{

public:

	DataInfo();//Ĭ�Ϲ��캯��

	friend ostream& operator<<(ostream& out, const DataInfo& dataInfo); //�������������
//private:

	string name;//����

	string phone;//�绰����

	string studentId;//ѧ��	

	string sex;//�Ա�

	char sign;//��ͻ�ı�־λ��'1'��ʾ��ͻ��'0'��ʾ�޳�ͻ

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

//��ż�¼�Ĺ�ϣ������

class HashTable

{

public:

	HashTable();//Ĭ�Ϲ��캯��

	~HashTable();//��������

	int Random(int key, int i);// α�����̽����ɢ�з������ͻ

	int Hashname(DataInfo *dataInfo);//������Ϊ�ؼ��ֽ�����ϣ��	

	int Rehash(int key, string str);// �ٹ�ϣ�������ͻ   ע�⴦���ͻ��������ַ����

	void Hash(char *fname, int n);// ������ϣ��

	//fname �����ݴ�����ļ������ƣ������������ݣ�n���û�ѡ��Ĳ��ҷ�ʽ	

	int Findname(string name);// �����������ҹ�ϣ���еļ�¼��Ӧ�Ĺؼ���

	void Outhash(int key);// �����ϣ���йؼ������Ӧ��һ����¼

	int deleteHash(int key);


//private:

    DataInfo *value[HASH_MAXSIZE];

	int length;//��ϣ����

};


int HashTable::deleteHash(int key){
	if(value[key]->sign != '0'){
		value[key]->sign = '0';
		length --;
		return 1;
	}
	return 0;
}
 

HashTable::HashTable():length(0)//Ĭ�Ϲ��캯��

{

	//memset(value, NULL, HASH_MAXSIZE*sizeof(DataInfo*));

	for (int i=0; i<HASH_MAXSIZE; i++)

	{

		value[i] = new DataInfo();

	}

}

 

HashTable::~HashTable()//��������

{

	delete[] *value;

}

int HashTable::Random(int key, int i)// α�����̽����ɢ�з������ͻ

{//key�ǳ�ͻʱ�Ĺ�ϣ��ؼ��룬i�ǳ�ͻ�Ĵ�����N�ǹ�ϣ����

	//�ɹ������ͻ�����µĹؼ��룬δ���г�ͻ�����򷵻�-1

	int h;

	if(value[key]->sign == '1')//�г�ͻ

	{

		h = (key + D[i]) % HASH_MAXSIZE;

		return h;

	}

	return -1;

}

int HashTable::Hashname(DataInfo *dataInfo)//������Ϊ�ؼ��ֽ�����ϣ��

{//���ó���ȡ�෨����������Ϊ�ؼ��ֽ����Ĺ�ϣ�������ڷ�����ͻʱ����Random���������ͻ

	int i = 0;	

	int key = 0;

 

    for (int t=0; dataInfo->name[t]!='\0'; t++)   

	{		

		key = key + dataInfo->name[t];

	}

	key = key % 42;

	while(value[key]->sign == '1')//�г�ͻ

	{

		key = Random(key, i++);//�����ͻ
		if(i >= 8){
			return -1;
		}

	}

	if(key == -1) exit(1);//�޳�ͻ

	length++;//��ǰ���ݸ�����

	value[key]->name = dataInfo->name;

	value[key]->studentId = dataInfo->studentId;

	value[key]->phone = dataInfo->phone;

	value[key]->sex = dataInfo->sex;

	value[key]->sign = '1';//��ʾ��λ����ֵ

	//cout << value[key]->name << "  " << value[key]->phone << "  "  << value[key]->studentId << endl;
	return 0;

}

 

int HashTable::Rehash(int key, string str)// �ٹ�ϣ�������ͻ

{//�ٹ�ϣʱʹ�õ����۵���������ϣ����	

	int h;

	int num1 = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');

	int num2 = (str[4] - '0') * 1000 + (str[5] - '0') * 100 + (str[6] - '0') * 10 + (str[7] - '0');

	int num3 = (str[8] - '0') * 100  + (str[9] - '0') * 10  + (str[10] - '0');

	h = num1 + num2 + num3;

	h = (h + key) % HASH_MAXSIZE;

	return h;

}
 
void HashTable::Outhash(int key)//�����ϣ���йؼ������Ӧ�ļ�¼

{  

	if((key==-1)||(value[key]->sign=='0'))

		cout << "û���ҵ�������¼��" << endl;

	else

	{		

		cout << left << setw(15) << value[key]->name;

		cout << left << setw(15) << value[key]->phone;

 		cout << left << setw(15) <<value[key]->studentId;

		cout << left << setw(15) <<value[key]->sex << endl;

	}

}

void HashTable::Hash(char *fname, int n)//������ϣ��

//fname�����ݴ�����ļ������ƣ������������ݣ�n���û�ѡ��Ĳ��ҷ�ʽ

//�����������ݣ�������ѡ�����Hashname��Hashphone�������й�ϣ��Ľ���

{

	ifstream fin;		

	int i;

	fin.open(fname);//���ļ�������

	if(fin.fail())

	{

		cout << "�ļ���ʧ�ܣ�" << endl;

		exit(1);

	}

	while(!fin.eof())//���ж�������

	{

		DataInfo *dataInfo = new DataInfo();

		char* str = new char[100];		

		fin.getline(str, 100, '\n');//��ȡһ������

 

		if(str[0] == '*')//�ж����ݽ���

		{

			break;

		}

 

		i = 0;//��¼�ַ���������±�

		//a-z:97-122     A-Z:65-90    

		//������������͵�ַ��ʹ��Сд��ĸ

		while((str[i] < 97) || (str[i] > 122))//��������

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

 

		for(int j=0; str[i]!=' '; j++,i++)//����绰����

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

 

int HashTable::Findname(string name)//�����������ҹ�ϣ���еļ�¼��Ӧ�Ĺؼ���

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

		system("cls");//cls���������Ļ�����е�����

		cout << "��ӭʹ�ñ�ϵͳ��" << endl << endl;

		cout << "��ѡ������" << endl;

		cout << "1.ʹ�����������ļ�" << endl;

		cout << "0.����" << endl;

		cout << "������Ӧ���ѡ���ܣ�";

		cin >> k;

		switch(k)

		{

		case 0:

			return 0;

		case 1:

			break;

		default:

			cout << "������������˳�����" << endl;	

			return 0;

		}

		ht->Hash(Fname, 1);

		while(1)

		{

			int choice;

			cout << endl << "��ѡ����" << endl;

			cout << "1.����������������" << endl;

			cout << "2.��ʾ��ϣ��" << endl;

			cout << "3.����Ԫ��" << endl;

			cout << "4.ɾ��Ԫ��" << endl;

			cout << "0.�˳�"<<endl;

			cout << "������Ӧ���ѡ���ܣ�";

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

					cout << "������������";

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

					cout << "������������ ";

					cin >> name;

					string sex;					

					cout << "�������Ա� ";

					cin >> sex;

					string sid;					

					cout << "������ѧ�ţ� ";

					cin >> sid;

					string phone;					

					cout << "������绰�� ";

					cin >> phone;	

					cout << endl;			

					DataInfo *temp = new DataInfo(name, sex, phone, sid);

					if(ht->Hashname(temp) == -1) cout << "����ʧ�� " << endl;

					else cout << "���ӳɹ� " << endl;
				}							

				break;

			case 4:	

			{

				int key1;					

				string name;					

				cout << "������������";

				cin >> name;					

				key1 = ht->Findname(name);

				if(ht->deleteHash(key1)){

					cout << "ɾ���ɹ�" << endl;
				
				}	

				else cout << "delete failed! " << endl;

			}

			break;

			default:

				cout << endl << "������������" << endl;				

			}
			if(tag == 1){

				tag = 0;

				break;
			}

		}

	}

	system("pause");	

}

 

 
