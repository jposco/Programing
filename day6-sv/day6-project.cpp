#include <iostream>
#include <string>
#include <fstream> //������ �а�, �� �� �ֵ��� ���� ����� �����ϴ� ���
#include <vector>
using namespace std;

int main()
{
    string name, pin, num;
    cout << "�̸��� �Է��ϼ��� : ";
    cin >> name;
    cout << endl << "��й�ȣ�� �Է��ϼ��� : ";
    cin >> pin;

    ifstream file("�ǽ�2.txt"); // //file�̶� ������ �ǽ�2�� ������ �ִ�
    string line; //line = ȫ�浿ȣ��ȣ�� ���浿�Ѹ� ����Ʈ����Ʈ
    vector<string> v;

    if (file.is_open()) {
        while (getline(file, line))
        {
            v.push_back(line);//file�� �ִ� �� ���徿�� line �迭�� ����
        }
        //< �ǽ�2.txt >
        //[0] ȫ�浿ȣ��ȣ��
        //[1] ���浿�Ѹ�
        //[2] ����Ʈ����Ʈ
        for (int i = 0; i < v.size(); i++) {
        cout << v.at(i);
    }
        string sum = name + pin;
        for (int i = 0; i < v.size(); i++) {
            if (sum == v[i])
            {//�Ƶ� ��� == �ǽ�2.txt
                cout << "�α��� ����" << endl;
                cout << " ��ȭ��ȣ�� �Է��ϼ���. : ";
                cin >> num;
            }
            else
            {
                cout << "�α��� ����" << endl;
                break;
            }
            return 0;
        }
    }
    file.close();

    ifstream file_v("member_tel.txt");
    vector<string> v1;
    string sum_v = name + num;
    string line_v;
    if (file_v.is_open()) {
        while (getline(file_v, line_v)) {//getline(cin,ifstream), line�̶�� ������ ����)
            v1.push_back(line_v);
        }
        for (int i = 0; i < v1.size(); i++)
        {
            if (v1[i] == sum_v)
            {
                v1[i] = sum_v;
            }
            else {
                v1.push_back(sum_v);
            }
        }

    }
    file_v.close();

    ofstream in("member_tel.txt");
    for (int i = 0; i < v1.size(); i++) {
        in << v1.at(i) << endl;
    }
}