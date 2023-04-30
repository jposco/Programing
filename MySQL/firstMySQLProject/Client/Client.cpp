#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock ������� include. WSADATA �������.��
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <mysql/jdbc.h>
#include <conio.h> 

using std::cout;
using std::cin;
using std::endl;
using std::string;

#define MAX_SIZE 1024


const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "07wd2713"; // �����ͺ��̽� ���� ��й�ȣ

// MySQL Connector/C++ �ʱ�ȭ
sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ �� 
sql::Connection* con; //����
sql::PreparedStatement* pstmt; //���߿� �� �Է�
sql::ResultSet* result;
sql::Statement* stmt;

SOCKET client_sock;
string my_nick;

void mainMenu()
{
    cout << "\n";
    cout << "\t"; cout << "********************************** \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*  *******    *     *     *  *   * \n";
    cout << "\t"; cout << "*     *      * *    *     * *    * \n";
    cout << "\t"; cout << "*     *     *****   *     **     * \n";
    cout << "\t"; cout << "*     *    *     *  *     * *    * \n";
    cout << "\t"; cout << "*     *   *       * ***** *  *   * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*       1.�α���                 * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*       2. ID ã��               * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*       3. PW ã��               * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*       4. ȸ������              * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "*       0. ����                  * \n";
    cout << "\t"; cout << "*                                * \n";
    cout << "\t"; cout << "********************************** \n\n";
}

class SQL
{
private:
    string id, pw, name, phone, status, inBirth, song = "";
public:
    SQL()
    {
        try {
            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException& e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }

        // �����ͺ��̽� ����
        con->setSchema("project1");

        // DB �ѱ� ������ ���� ����
        stmt = con->createStatement();
        stmt->execute("set names euckr");
        if (stmt) { delete stmt; stmt = nullptr; }
    }
    void crateUser()
    {
        cout << "id";
        cin >> id;
        this->id = id;
        cout << "pw";
        char ch = ' ';
        while (ch != 13) { // Enter Ű�� ������ �Է� ����
            ch = getch();
            if (ch == 13) break; // Enter Ű�� ������ �Է� ����
            pw.push_back(ch);
            cout << '*'; // ��ǥ�� ��ü�Ͽ� ���
        }
        cout << endl;

        cout << "name";
        cin >> name;
        cout << "phone";
        cin >> phone;
        cout << "birth 8�ڸ��Է�";
        cin >> inBirth;

        string year = inBirth.substr(0, 4);
        string month = inBirth.substr(4, 2);
        string day = inBirth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("INSERT INTO user(id, pw, name, phone, birth) VALUE(?, ?, ?, ?, ?)");
        pstmt->setString(1, id);
        pstmt->setString(2, pw);
        pstmt->setString(3, name);
        pstmt->setString(4, phone);
        pstmt->setString(5, DATE);
        pstmt->execute();
        cout << "inserted." << endl;
    }
    void myProfile()
    {
        pstmt = con->prepareStatement("SELECT name, status, song, birth, phone FROM user WHERE id = ?;");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        while (result->next())
        {
                cout << "�̸� : " << result->getString("name") << endl;
                // status ���� NULL�� ��� "����"���� ���
                if (result->wasNull()) {
                    cout << "��� : ����" << endl;
                }
                else {
                    cout << "��� : " << result->getString("status") << endl;
                }
                // song ���� NULL�� ��� "����"���� ���
                if (result->wasNull()) {
                    cout << "���� : ����" << endl;
                }
                else {
                    cout << "���� : " << result->getString("song") << endl;
                }
                cout << "���� : " << result->getString("birth") << endl;
                cout << "��ȣ : " << result->getString("phone") << endl;            
        }
    }
    void updateStatus()
    {
        cout << "status";
        cin >> status;
        pstmt = con->prepareStatement("UPDATE user SET status = ? WHERE id = ?");
        pstmt->setString(1, status);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        printf("Status updated\n");
    }
    void updateSong()
    {
        cout << "song";
        cin >> song;
        pstmt = con->prepareStatement("UPDATE user SET song = ? WHERE id = ?");
        pstmt->setString(1, song);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        printf("Song updated\n");
    }
    void friends()
    {
        pstmt = con->prepareStatement("SELECT name, status, song, birth, phone FROM user WHERE id != ?;");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        while (result->next())
        {
            cout << "�̸� : " << result->getString("name") << endl;
            // status ���� NULL�� ��� "����"���� ���
            if (result->wasNull()) {
                cout << "��� : ����" << endl;
            }
            else {
                cout << "��� : " << result->getString("status") << endl;
            }
            // song ���� NULL�� ��� "����"���� ���
            if (result->wasNull()) {
                cout << "���� : ����" << endl;
            }
            else {
                cout << "���� : " << result->getString("song") << endl;
            }
            cout << "���� : " << result->getString("birth") << endl;
            cout << "��ȣ : " << result->getString("phone") << endl;
        }
    }
    void searchBirth()
    {
        string startDay, endDay;
        cout << "startDay";
        cin >> startDay;// 0303
        cout << "endDay";//0505
        cin >> endDay;
        pstmt = con->prepareStatement("SELECT name, birth FROM user \
            WHERE DATE_FORMAT(birth, '%m%d') BETWEEN ? AND ? \
            AND id != ?;");
        pstmt->setString(1, startDay);
        pstmt->setString(2, endDay);
        pstmt->setString(3, id);
        result = pstmt->executeQuery();

        while (result->next())
        {
            cout << "�̸� : " << result->getString("name") << endl;
            cout << "���� : " << result->getString("birth") << endl;
        }
    }
    void modifyPw()
    {
        pstmt = con->prepareStatement("UPDATE user SET pw = ? WHERE id = ?");
        pstmt->setInt(1, 200);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        printf("Row updated\n");
    }
    void deleteUser()
    {
        pstmt = con->prepareStatement("DELETE FROM user WHERE id = ?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();
        printf("Row deleted\n");
    }
};

int chat_recv() {
    char buf[MAX_SIZE] = { };
    string msg;

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            //�г��� : �޽���
            std::stringstream ss(msg);  // ���ڿ��� ��Ʈ��ȭ
            string user;
            ss >> user; // ��Ʈ���� ����, ���ڿ��� ���� �и��� ������ �Ҵ�
            //���⸦ �������� �г��� ����
            if (user != my_nick) cout << buf << endl; // �� �г��Ӱ� ������ �� ���� ���� �� �ƴ� ���(����)���� ����ϵ���.
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

int main()
{
    mainMenu();
    SQL sql;
    sql.crateUser();
//    //system("cls");
//    sql.myProfile();
//    sql.updateStatus();
//    sql.updateSong();
//    sql.friends();
      //sql.searchBirth();
      sql.deleteUser();







    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (!code) {
        cout << "login on";
        client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        SOCKADDR_IN client_addr = {};
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(7777);
        InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);

        while (1) {
            if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
                cout << "Server Connect" << endl;
                send(client_sock, my_nick.c_str(), my_nick.length(), 0);
                break;
            }
            cout << "Connecting..." << endl;
        }

        std::thread th2(chat_recv);

        while (1) {
            string text;
            std::getline(cin, text);
            const char* buffer = text.c_str(); // string���� char* Ÿ������ ��ȯ
            send(client_sock, buffer, strlen(buffer), 0);
        }
        th2.join();
        closesocket(client_sock);
    }

    WSACleanup();
    return 0;
}

////select  
//pstmt = con->prepareStatement("SELECT * FROM inventory;");
//result = pstmt->executeQuery();

//while (result->next())
//    printf("Reading from table=(%d, %s, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getInt(3));

////update
//pstmt = con->prepareStatement("UPDATE inventory SET quantity = ? WHERE name = ?");
//pstmt->setInt(1, 200);
//pstmt->setString(2, "banana");
//pstmt->executeQuery();
//printf("Row updated\n");

////delete
//pstmt = con->prepareStatement("DELETE FROM inventory WHERE name = ?");
//pstmt->setString(1, "orange");
//result = pstmt->executeQuery();
//printf("Row deleted\n");

// MySQL Connector/C++ ����
//delete result;
//delete pstmt;
//delete con;
//system("pause");



//<getch�Լ�>
//����ڰ� �Է��� Ű���� ���ڸ� ��� �������� �Լ��Դϴ�.
//�� �Լ��� Ű�� ������ �ٷ� �� ���� ��ȯ�ϸ�, �Է¹��� Ű�� ȭ�鿡 ������� �ʽ��ϴ�.
//��й�ȣ�� ���� ���ȼ��� �ʿ��� ������ �Է¹��� �� ����ϸ� �����մϴ�
//ch ������ 13�� ������ ������, 13�� Enter Ű�� ��Ÿ���� �����Դϴ�.
//while ���� Enter Ű�� ������ ������ ����ؼ� ������� �Է��� �޽��ϴ�.
//getch() �Լ��� �ֿܼ��� ����ڰ� �Է��� ���� �о���Դϴ�.
//����ڰ� Enter Ű�� ������, while ���� ����˴ϴ�.
//
//��й�ȣ �Է� ��, �Էµ� ���ڿ��� ��ǥ�� ��ü�ϱ� ����,
//�Էµ� ���ڿ��� pw ������ push_back() �Լ��� �����մϴ�.
//push_back() �Լ��� ���ڿ��� �� �ڿ� ���ڸ� �߰��մϴ�.
//
//�׸���, cout << '' �� ����, �Էµ� ���ڿ��� ��ǥ()�� ��ü�Ͽ� ����մϴ�.
//�̷��� �Ǹ�, ����ڰ� �Է��� ��й�ȣ�� ��ǥ�� ��ü�Ǿ� ���ȼ��� �������ϴ�.