#include <iostream>
using namespace std;

class Snack
{
protected:
	int price;
	string name;
	string manufacturer;
public:
	Snack(int price, string name, string manufacturer)
	{
		this->price = price;
		this->name = name;
		this->manufacturer = manufacturer;
	}
	string getName() 
	{
		return name;
	}
	void printName()
	{
		cout << "��ǰ �̸� : " <<name<< endl;
	}
};
	
class Candy : public Snack
{
	string taste;
public:
	Candy(string taste, int price, string name, string manufacturer) : Snack(price, name, manufacturer)
	{
		this->taste = taste;
	}
	void printName()
	{
		cout << taste << "�� " << getName() << endl;
	}
};
	
class Chocolate : public Snack
{
	string shape;
public:
	Chocolate(string shape, int price, string name, string manufacturer) : Snack(price, name, manufacturer)
	{
		this->shape = shape;
	}
	void printName()
	{
		cout << shape << " ��� " << getName() << endl;
	}
};
	
int main()
{
			 //Snack snackBasket[2] = { Candy("�����",5000,"������","����"), Chocolate("�׸�",3000,"�������ݸ�","�Ե�����") };
	Snack* snackBasket[] = { new Candy("����",5000,"������","����"), new Chocolate("�׸�",3000,"�������ݸ�","�Ե�����") };
	for (int i = 0; i < 2; i++)
	{
		cout << snackBasket[i]->getName() << endl;

	}
	Candy* can = (Candy*)snackBasket[0];
	can->printName();
	Chocolate* cho = (Chocolate*)snackBasket[1];
	cho->printName();
}

////--------����4 ����--------------------------------------------
//class Snack {
//	int price;
//	string name;
//	string maker;
//public:
//	Snack(string name) {
//		this->name = name;
//	}
//	void printName() {
//		cout <<"��ǰ �̸��� : " << name << endl;
//	}
//
//	string getName() {
//		return name;
//	}
//};
//class Candy : public Snack {
//	string flavor;
//public:
//	Candy(string name) : Snack(name) {
//		this->flavor = "����";
//	}
//
//	void printName() {
//		cout << flavor << "�� " << getName() << endl;
//	}
//};
//
//class Choco : public Snack {
//	string shape;
//public:
//	Choco(string name) : Snack(name) {
//		this->shape = "�׸�";
//	}
//	void printName() {
//		cout << shape << "��� " << getName() << endl;
//	}
//};
//
//int main()
//{
//	Snack* snackBasket[4] = { new Candy("����"), new Candy("�˻���"), new Choco("�������ݸ�"), new Choco("�䷹��") };
//
//	for (int i = 0; i < 4; i++)
//	{
//		snackBasket[i]->printName();
//	}
//	Candy* candy = (Candy*)snackBasket[0];
//	candy->printName();
//	Choco* choco = (Choco*)snackBasket[2];
//	choco->printName();
//}
//
