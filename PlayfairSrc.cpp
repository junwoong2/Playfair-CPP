#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Playfair {
	char mTable[25];
	string mPair;
	string mKey;
public:
	Playfair(string mKey, string mPair);
	void makeTable();
	void showTable();
	string makeEncryption(string mEncryption);
};

Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
	this->mPair = mPair;
}

void Playfair::makeTable() {
	char key[25] = { 0, };
	char key2[25] = { 0, };
	char A = 'a';
	int count = 0, ck = 0;

	strcpy(key, mKey.c_str());
	int len = mKey.length();
	
	
	cout << "Ű���� : " << key << endl;
	// key���� �ߺ����� ������ �� key2�� ����
	for (int i = 0; i < len; i++) {
		ck = 0;
		for (int j = 0; j < len; j++) {
			if (key[i] == key2[j]) {
				ck = 1;
			}
		}
		if (ck == 0) {
			key2[count++] = key[i];
		}
	}
	cout << "�ߺ� ���ŵ� Ű�� : " << key2 << "\n\n";
	
	strcpy(mTable, key2);//mTable�� �ߺ��� ���ŵ� key2�� ����
	len = strlen(key2);
	//key2 �迭 �ȿ� q,z���� ���� ������ �ν��ϰ� ��
	for (int i = 0; i < len; i++) {
		if (key2[i] == 'q') {
			key2[len] = 'z';
		}
		else if (key2[i] == 'z') {
			key2[len] = 'q';
		}
	}
	//mTable �����
	for (int i = len; i < 25; i++) {
		for (int j = 0; j < len + 1; j++) {
			if (A == key2[j]) {
				A++;
				j=-1;
			}
			else{
				mTable[i] = A;
			}
		}
		if (mTable[i] >= 'a' && mTable[i] <= 'z') {
			A++;
		}
	}
}

void Playfair::showTable(){
	// mTable�� �ִ� ������ 5 X 5 �� ȭ�鿡 ����Ͻÿ�.
	for (int i = 0; i < 25; i++) {
		cout << mTable[i] << " ";
		if (i % 5 == 4) {
			cout << endl;
		}
	}
	cout << endl;
}

string Playfair::makeEncryption(string mEncryption) {
	char txt[100] = { 0, };
	char txt2[100]= { 0, };
	int cnt = 0;
	//������ֱ�
	mEncryption.erase(remove(mEncryption.begin(), mEncryption.end(), ' '), mEncryption.end());
	cout << "\n������������ : "<<mEncryption << "\n\n";
	//���ӵǴ� ���� �����ϱ� + ���ӵǴ� ���� ���̿� X�ֱ�
	strcpy(txt2, mEncryption.c_str());//char�迭�� �־�α�
	cnt = 0;
	int len = strlen(txt2);
	for (int i = 0;i < len+1;i++) {
		if (txt2[i] == txt2[i + 1]) {//���ӵǴ� �����϶�
			txt[cnt++] = txt2[i];
			txt[cnt++] = 'x';
		}
		else {
			txt[cnt++] = txt2[i];
			txt[cnt++] = txt2[i + 1];
			i++;
		}
	}
	len = strlen(txt);
	if (len % 2 == 1) {//���ڰ� Ȧ���� ���
		txt[len] = 'x';
	}
	cout << "X���̰� �ڸ� �� : ";
	for (int i = 0;txt[i] != 0;i++) {
		cout << txt[i];
		if (i % 2 == 1) {
			cout << " ";
		}
	}

	//��ȣȭ ����
	char enc[5][5] = { 0, };
	char arr[100] = { 0, };
	cnt = 0;
	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			enc[i][j] = mTable[cnt++];
		}
	}
	int s[2][2] = { 0, };
	for (int k = 0;k < strlen(txt);k += 2) {
		for (int i = 0;i < 5;i++) {
			for (int j = 0;j < 5;j++) {
				if (enc[i][j] == txt[k]) {
					s[0][0] = i;
					s[0][1] = j;
				}
				if (enc[i][j] == txt[k + 1]) {
					s[1][0] = i;
					s[1][1] = j;
				}
				if (txt[k] == 'z') {//q�� z�� ó��
					if (enc[i][j] == 'q') {
						s[0][0] = i;
						s[0][1] = j;
						break;
					}
				}
				if (txt[k+1] == 'z') {//q�� z�� ó��
					if (enc[i][j] == 'q') {
						s[1][0] = i;
						s[1][1] = j;
						break;
					}
				}
			}
		}
		if (s[0][1] == s[1][1]) {//���� ������
			arr[k] = enc[(s[0][0] + 1) % 5][s[0][1]];
			arr[k + 1] = enc[(s[1][0] + 1) % 5][s[1][1]];
		}
		else if (s[0][0] == s[1][0]) {//���� ������
			arr[k] = enc[s[0][0]][(s[0][1] + 1) % 5];
			arr[k + 1] = enc[s[1][0]][(s[1][1] + 1) % 5];
		}
		else {//�̿� �� ������ �� ��ġ ��ȯ
			arr[k] = enc[s[0][0]][s[1][1]];
			arr[k + 1] = enc[s[1][0]][s[0][1]];
		}
	}
	cout << "\n\n��ȣȭ�� ������ : " << arr<<"\n";
	return mEncryption;
}


int main() {
	Playfair pfair("assinator", "q/z");
	pfair.makeTable();
	pfair.showTable();
	string mEncryption;
	cout << "��ȣȭ�� ������ : ";
	getline(cin, mEncryption);
	pfair.makeEncryption(mEncryption);
}