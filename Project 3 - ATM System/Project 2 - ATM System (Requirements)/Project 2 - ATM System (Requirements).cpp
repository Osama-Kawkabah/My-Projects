#include <iostream>
#include <fstream> 
#include <string>  
#include <vector>  
#include <iomanip> 

using namespace std;

const string ClientsFileName = "Client.text"; // ��� ��� �������

void Login(); // ���� ������ ������
void ShowTransactionsMenue(); // ���� ���� ����� ��������

struct sClient { // ���� ������ ���� ������ ������
    string AccountNumber;   // ��� ������
    string PinCode;         // ����� �����
    string Name;            // �����
    string Phone;           // ��� ������
    double AccountBalance;  // ���� ������
    bool MarkForDelete = false;  // ����� �����
};

sClient CurrentClient; // ������ ������

enum TransactionsMenueOptions { // ������ ����� ��������
    quickWithdraw = 1, // ��� ����
    NormalWithdraw = 2, // ��� ����
    Deposit = 3, // �����
    TotalBalances = 4, // ���� ������ ��������
    Exit = 5 // ������
};

vector<string> SplitString(string S1, string Delim) // ���� ������ ������� ��� ������
{

    vector<string> vString; // ����� ������ ��������

    short pos = 0;
    string sWord; // ����� ������ �� ��� �� ����  

    // ������ ���� find() ������ ��� ����� �������  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // �� ������ �����   
        if (sWord != "")
        {
            vString.push_back(sWord); // ��� ����� ��� �������
        }

        S1.erase(0, pos + Delim.length());  /* �� ���� ����� ������ ��� ����� ������. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // ��� ����� ������ �� ����
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") // ���� ������ ��� �� ��� ���� sClient
{

    sClient Client; // ����� ���� ���� ����
    vector<string> vClientData; // ����� ������ ������ ������

    vClientData = SplitString(Line, Seperator); // ����� ������� ��� ������

    Client.AccountNumber = vClientData[0]; // ����� ��� ������
    Client.PinCode = vClientData[1]; // ����� ����� �����
    Client.Name = vClientData[2]; // ����� �����
    Client.Phone = vClientData[3]; // ����� ��� ������
    Client.AccountBalance = stod(vClientData[4]); // ����� ���� ������ ������� �� �� ��� ��� ����

    return Client; // ����� ������
}

vector <sClient> LoadCleintsDataFromFile(string FileName) // ���� ������ ������ ������� �� �����
{

    vector <sClient> vClients; // ����� ������ ������ �������

    fstream MyFile;
    MyFile.open(FileName, ios::in); // ��� ����� �������

    if (MyFile.is_open()) // ������ �� ��� ����� �����
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line)) // ����� �������� �� ����� ����� �����
        {

            Client = ConvertLinetoRecord(Line); // ����� �� ��� ��� ���� ����

            vClients.push_back(Client); // ����� ������ ��� �������
        }

        MyFile.close(); // ����� ����� ��� ��������

    }

    return vClients; // ����� ����� �������
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") // ���� ������ ���� sClient ��� ��� ��
{

    string stClientRecord = ""; // ����� ������ ��� ����

    stClientRecord += Client.AccountNumber + Seperator; // ����� ��� ������ �� �������
    stClientRecord += Client.PinCode + Seperator; // ����� ����� ����� �� �������
    stClientRecord += Client.Name + Seperator; // ����� ����� �� �������
    stClientRecord += Client.Phone + Seperator; // ����� ��� ������ �� �������
    stClientRecord += to_string(Client.AccountBalance); // ����� ���� ������ �� �������

    return stClientRecord; // ����� ��� ����
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients) // ���� ���� ������ ������� �� �����
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // ��� ����� �������

    string DataLine; // ����� ������ �� ��� �� ����

    if (MyFile.is_open()) // ������ �� ��� ����� �����
    {

        for (sClient C : vClients) // �������� ��� ����� �������
        {

            if (C.MarkForDelete == false) // ������ �� ��� ���� ����� ��� ��� ������
            {
                // ���� ��� ������� ���� �� ���� ����� �����.
                DataLine = ConvertRecordToLine(C); // ����� ���� ������ ��� ��� ��
                MyFile << DataLine << endl; // ����� ����� ��� �����

            }

        }

        MyFile.close(); // ����� ����� ��� ��������

    }

    return vClients; // ����� ����� ������� ��� �������
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, short Amount, vector <sClient>& vClients) // ���� ������ ���� ��� ���� ������
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? "; // ��� ��� �������� ����� �������
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients) // �������� ��� ����� �������
        {
            if (C.AccountNumber == AccountNumber) // ������ �� ����� ��� ������
            {
                C.AccountBalance += Amount; // ����� ������ ��� ���� ������
                SaveCleintsDataToFile(ClientsFileName, vClients); // ��� �������� �� �����
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance; // ����� �������� ����� ������� ���� ������ ������

                return true; // ����� ���� ����� ������
            }

        }


        return false; // ����� ���� ����� �����
    }

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients) // ���� ����� �� ���� �������� ��� ������
{

    for (sClient C : vClients) // �������� ��� ����� �������
    {

        if (C.AccountNumber == AccountNumber) // ������ �� ����� ��� ������
        {
            return true; // ����� ���� ����� ��� �� ������ ��� ������
        }

    }
    return false; // ����� ���� ����� ��� �� ��� ������ ��� ������
}

void RefreshTransactionsScreen() {
    system("cls"); // ��� ������
    ShowTransactionsMenue(); // ��� ���� ���������
}

void GoBackToLogin() // ���� ������ ��� ���� ����� ������
{
    cout << "\n\nPress any key to go back to Transactions Menue..."; // ����� ���� �� �������� ����� ��� �� ����� ������
    system("pause>0"); // ������ ����� ��� �����
    Login(); // ������ ��� ���� ����� ������
}

void GoBackToMainMenue() // ���� ������ ��� ����� ��������
{
    cout << "\n\nPress any key to go back to Transactions Menue..."; // ����� ���� �� �������� ����� ��� �� ����� ������
    system("pause>0"); // ������ ����� ��� �����
    ShowTransactionsMenue(); // ������ ��� ����� ��������
}

void GoBackToManageUsersMenue() // ���� ������ ��� ����� ����� ����������
{
    cout << "\n\nPress any key to go back to Transactions Menue..."; // ����� ���� �� �������� ����� ��� �� ����� ������
    system("pause>0"); // ������ ����� ��� �����
}

void ShowClientTotalBalances() { // ���� ���� ���� ������

    cout << "===========================================\n";
    cout << "\t\tCheck Account Balance\n";
    cout << "===========================================\n";
    short AccountBalance = CurrentClient.AccountBalance; // ������ ������ ������
    system("cls"); // ��� ������
    cout << "Your Balances Is : " << AccountBalance << endl; // ��� ���� ������
}
//-------------------------------------
void ShowNormalWithDrawScreen() // ���� ���� ���� ��� ����
{
    cout << "===================================\n";
    cout << "\t NormalWithDraw Screen"; // ����� ������
    cout << "\n===================================\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ����� ������ �������
    string AccountNumber = CurrentClient.AccountNumber; // ��� ������ ������

    short Amount = 0;
    do
    {
        cout << "\nEnter Amount Multiple of 5,s ? "; // ���� �� �������� ����� ������ ������ 5
        cin >> Amount;

    } while (Amount % 5 != 0); // ������ �� �� ������ ����� ������

    if (Amount > CurrentClient.AccountBalance) // ������ �� �� ������ ��� �� ������
    {
        cout << "The Amount exceede Your balance , make another choice "; // ����� ����� ��� ��� ������ ������ ������

        GoBackToMainMenue(); // ������ ��� ����� ��������
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); // ��� ������ �� ������
}

void ShowDepositScreen() // ���� ���� ���� �������
{
    cout << "\n===================================\n";
    cout << "\tDeposit Screen"; // ����� ������
    cout << "\n===================================\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ����� ������ �������
    string AccountNumber = CurrentClient.AccountNumber; // ��� ������ ������


    double Amount = 0;
    cout << "\Enter A deposit amount? "; // ���� �� �������� ����� ������
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients); // ����� ������ �� ������

}
//-----------Min-Menue-----------------
short ReadWithDraw() { // ���� ������ ������ ������� ����
    short WithDraw;
    cout << "Choose What To WithDraw From [1] to [8]? "; // ���� �� �������� ������ ������ ������� ����
    cin >> WithDraw;
    return WithDraw;
}

short CheckquickWithdrawOptions() { // ���� ������ �� ������ ����� ������
    short Choice = ReadWithDraw();
    short Amount = 0;
    switch (Choice)
    {
    case 1:
        return Amount = 20; // ����� ���� ����� �������
        break;
    case 2:
        return Amount = 50; // ����� ���� ����� �������
        break;
    case 3:
        return Amount = 100; // ����� ���� ����� �������
        break;
    case 4:
        return Amount = 200; // ����� ���� ����� �������
        break;
    case 5:
        return Amount = 400; // ����� ���� ����� �������
        break;
    case 6:
        return Amount = 600; // ����� ���� ����� �������
        break;
    case 7:
        return Amount = 800; // ����� ���� ����� �������
        break;
    case 8:
        return Amount = 1000; // ����� ���� ����� �������
        break;
    case 9:
        ShowTransactionsMenue(); // ������ ��� ����� ��������
        break;
    }
}

void ShowWithDrawScreen() // ���� ���� ���� ����� ������
{
    system("cls"); // ��� ������
    cout << "===========================================\n";
    cout << "\t Qucick Withdraw";
    cout << "\n===========================================\n";
    cout << "\t[1]20 \t\t [2]50.\n";
    cout << "\t[3]100\t\t [4]200.\n";
    cout << "\t[5]400\t\t [6]600.\n";
    cout << "\t[7]800\t\t [8]1000.\n";
    cout << "\t[9]Exit\n";
    cout << "===========================================\n";


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ����� ������ �������
    string AccountNumber = CurrentClient.AccountNumber; // ��� ������ ������

    FindClientByAccountNumber(AccountNumber, vClients); // ����� �� ������ �������� ��� ������

    cout << "Your Balances Is : " << CurrentClient.AccountBalance << endl; // ��� ������ ������ ������

    short Amount = CheckquickWithdrawOptions(); // ������ �� ������ ����� ������

    while (Amount > CurrentClient.AccountBalance) // ������ �� �� ������ ��� �� ������
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl; // ����� ����� ��� ��� ������ ������ ������
        cout << "Please enter another amount? ";
        Amount = CheckquickWithdrawOptions(); // ������ ��� ���� �� ������
    };

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); // ��� ������ �� ������
}

short ReadTransactionsMenueOption() { // ���� ������ ���� ����� ��������
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromTranactionsMenueOption(TransactionsMenueOptions TransactionMenueOption) { // ���� ������ ���� ����� ��������
    switch (TransactionMenueOption) {
    case quickWithdraw: {
        system("cls"); // ��� ������
        ShowWithDrawScreen(); // ��� ���� ����� ������
        GoBackToMainMenue(); // ������ ��� ����� ��������
        break;
    }
    case NormalWithdraw: {
        system("cls"); // ��� ������
        ShowNormalWithDrawScreen(); // ��� ���� ��� ����
        GoBackToMainMenue(); // ������ ��� ����� ��������
        break;
    }
    case Deposit: {
        system("cls"); // ��� ������
        ShowDepositScreen(); // ��� ���� �������
        GoBackToMainMenue(); // ������ ��� ����� ��������
        break;
    }
    case TotalBalances: {
        system("cls"); // ��� ������
        ShowClientTotalBalances(); // ��� ���� ������
        GoBackToMainMenue(); // ������ ��� ����� ��������
        break;
    }
    case Exit: {
        cout << "Thanks for banking with us..bye.\n"; // ����� ������
        Login(); // ������ �� ��������
    }
    }
}

void ShowTransactionsMenue() { // ���� ���� ����� ��������
    system("cls"); // ��� ������
    cout << "=============================================\n";
    cout << "\t\tMain Menu\n";
    cout << "=============================================\n";
    cout << "\tClient Name : " << CurrentClient.Name << endl; // ��� ��� ������
    cout << "=============================================\n";
    cout << "\t\t1. Quick Withdraw\n"; // ��� ����
    cout << "\t\t2. Normal Withdraw\n"; // ��� ����
    cout << "\t\t3. Deposit\n"; // �����
    cout << "\t\t4. Total Balances\n"; // ���� ������ ��������
    cout << "\t\t5. Exit\n"; // ������
    cout << "=============================================\n";

    TransactionsMenueOptions Option = static_cast<TransactionsMenueOptions>(ReadTransactionsMenueOption()); // ����� ������ �������
    PerfromTranactionsMenueOption(Option); // ����� ������ �������
}

void LoadClientInformation(string AccountNumber, string PinCode) { // ���� ������ ������� ������
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ����� ������ ������� �� �����

    for (sClient C : vClients) // �������� ��� ����� �������
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode) // ������ �� ����� ��� ������ ������ �����
        {
            CurrentClient = C; // ����� ������ ������
            ShowTransactionsMenue(); // ��� ����� ��������
        }

    }
    cout << "Client Information Not Found...." << endl; // ����� ��� �� ��� ������ ��� ������� ������
    GoBackToLogin(); // ������ ��� ���� ����� ������
}

void Login() { // ���� ����� ����� ������
    system("cls"); // ��� ������
    cout << "=======================================\n";
    cout << "\t\tBanking System\n";
    cout << "=======================================\n";

    string AccountNumber, PinCode; // ������� ������ ��� ������ ������ �����

    cout << "Enter Your Account Number? "; // ���� �� �������� ����� ��� ������
    cin >> AccountNumber;

    cout << "Enter Your PinCode? "; // ���� �� �������� ����� ����� �����
    cin >> PinCode;

    LoadClientInformation(AccountNumber, PinCode); // ����� ������� ������ �������� ��� ������ ������ �����
}

int main() { // ������ ��������
    Login(); // ���� ����� ������
    return 0;
}
