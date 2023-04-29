#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using std::cout;
using std::endl;
using std::string;

const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "07wd2713"; // �����ͺ��̽� ���� ��й�ȣ

int main()
{
    // MySQL Connector/C++ �ʱ�ȭ
    sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;


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

    // �����ͺ��̽� ���� ����
    stmt = con->createStatement();
    //stmt->execute("DROP TABLE IF EXISTS inventory"); // DROP
    //cout << "Finished dropping table (if existed)" << endl;

    //CREAT
    stmt->execute("CREATE TABLE user\
        (id VARCHAR(50) NOT NULL PRIMARY KEY,\
        pw VARCHAR(50) NOT NULL,\
        name VARCHAR(10) NOT NULL,\
        phone INT NOT NULL,\
        status VARCHAR(50),\
        birth DATE NOT NULL,\
        song VARCHAR(50));");
    cout << "Finished creating user table" << endl;

    stmt->execute("CREATE TABLE chatting (\
    sequence INT NOT NULL PRIMARY KEY AUTO_INCREMENT,\
    chatname VARCHAR(10) NOT NULL,\
    time TIMESTAMP NOT NULL,\
    send VARCHAR(1024),\
    recv VARCHAR(1024),\
    chat_id VARCHAR(50) NOT NULL,\
    foreign key(chat_id) references user(id)\
    ON UPDATE CASCADE ON DELETE CASCADE);");
    // serial 1�� �þ�°�
    cout << "Finished creating chatting table" << endl;

    delete stmt;

    //pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)"); // INSERT
    ////prepareStatement ���߿� ?�� �� �Է�

    //pstmt->setString(1, "banana");
    //pstmt->setInt(2, 150);
    //pstmt->execute();
    //cout << "One row inserted." << endl;

    //pstmt->setString(1, "orange");
    //pstmt->setInt(2, 154);
    //pstmt->execute();
    //cout << "One row inserted." << endl;

    //pstmt->setString(1, "���");
    //pstmt->setInt(2, 100);
    //pstmt->execute();
    //cout << "One row inserted." << endl;

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
    system("pause");
    return 0;
}