#include <iostream>
#include <fstream> 
#include <string>  
#include <vector>  
#include <iomanip> 

using namespace std;

const string ClientsFileName = "Client.text"; // ÇÓã ãáİ ÇáÚãáÇÁ

void Login(); // ÏÇáÉ áÊÓÌíá ÇáÏÎæá
void ShowTransactionsMenue(); // ÏÇáÉ áÚÑÖ ŞÇÆãÉ ÇáÚãáíÇÊ

struct sClient { // åíßá ÈíÇäÇÊ íãËá ÈíÇäÇÊ ÇáÚãíá
    string AccountNumber;   // ÑŞã ÇáÍÓÇÈ
    string PinCode;         // ÇáÑãÒ ÇáÓÑí
    string Name;            // ÇáÇÓã
    string Phone;           // ÑŞã ÇáåÇÊİ
    double AccountBalance;  // ÑÕíÏ ÇáÍÓÇÈ
    bool MarkForDelete = false;  // ÚáÇãÉ ááÍĞİ
};

sClient CurrentClient; // ÇáÚãíá ÇáÍÇáí

enum TransactionsMenueOptions { // ÎíÇÑÇÊ ŞÇÆãÉ ÇáÚãáíÇÊ
    quickWithdraw = 1, // ÓÍÈ ÓÑíÚ
    NormalWithdraw = 2, // ÓÍÈ ÚÇÏí
    Deposit = 3, // ÅíÏÇÚ
    TotalBalances = 4, // ÑÕíÏ ÇáÍÓÇÈ ÇáÅÌãÇáí
    Exit = 5 // ÇáÎÑæÌ
};

vector<string> SplitString(string S1, string Delim) // ÏÇáÉ áÊŞÓíã ÇáÓáÓáÉ Åáì ÌÒíÆÇÊ
{

    vector<string> vString; // ŞÇÆãÉ áÊÎÒíä ÇáÌÒíÆÇÊ

    short pos = 0;
    string sWord; // ÓáÓáÉ áÊÎÒíä ßá ÌÒÁ ãä ÇáäÕ  

    // ÇÓÊÎÏã ÏÇáÉ find() ááÚËæÑ Úáì ãæÇŞÚ ÇáİæÇÕá  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // Şã ÈÊÎÒíä ÇáÌÒÁ   
        if (sWord != "")
        {
            vString.push_back(sWord); // ÃÖİ ÇáÌÒÁ Åáì ÇáŞÇÆãÉ
        }

        S1.erase(0, pos + Delim.length());  /* Şã ÈÍĞİ ÇáÌÒÁ æÇäÊŞá Åáì ÇáÌÒÁ ÇáÊÇáí. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // ÃÖİ ÇáÌÒÁ ÇáÃÎíÑ ãä ÇáäÕ
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") // ÏÇáÉ áÊÍæíá ÓØÑ äÕ Åáì åíßá sClient
{

    sClient Client; // ÅäÔÇÁ åíßá Úãíá ÌÏíÏ
    vector<string> vClientData; // ŞÇÆãÉ áÊÎÒíä ÈíÇäÇÊ ÇáÚãíá

    vClientData = SplitString(Line, Seperator); // ÊŞÓíã ÇáÓáÓáÉ Åáì ÌÒíÆÇÊ

    Client.AccountNumber = vClientData[0]; // ÊÚííä ÑŞã ÇáÍÓÇÈ
    Client.PinCode = vClientData[1]; // ÊÚííä ÇáÑãÒ ÇáÓÑí
    Client.Name = vClientData[2]; // ÊÚííä ÇáÇÓã
    Client.Phone = vClientData[3]; // ÊÚííä ÑŞã ÇáåÇÊİ
    Client.AccountBalance = stod(vClientData[4]); // ÊÚííä ÑÕíÏ ÇáÍÓÇÈ æÊÍæíáå ãä äÕ Åáì ÑŞã ÚÔÑí

    return Client; // ÅÑÌÇÚ ÇáÚãíá
}

vector <sClient> LoadCleintsDataFromFile(string FileName) // ÏÇáÉ áÊÍãíá ÈíÇäÇÊ ÇáÚãáÇÁ ãä Çáãáİ
{

    vector <sClient> vClients; // ŞÇÆãÉ áÊÎÒíä ÈíÇäÇÊ ÇáÚãáÇÁ

    fstream MyFile;
    MyFile.open(FileName, ios::in); // İÊÍ Çáãáİ ááŞÑÇÁÉ

    if (MyFile.is_open()) // ÇáÊÍŞŞ ãä İÊÍ Çáãáİ ÈäÌÇÍ
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line)) // ŞÑÇÁÉ ÇáÈíÇäÇÊ ãä Çáãáİ ÓØÑÇğ ÓØÑÇğ
        {

            Client = ConvertLinetoRecord(Line); // ÊÍæíá ßá ÓØÑ Åáì åíßá Úãíá

            vClients.push_back(Client); // ÅÖÇİÉ ÇáÚãíá Åáì ÇáŞÇÆãÉ
        }

        MyFile.close(); // ÅÛáÇŞ Çáãáİ ÈÚÏ ÇáÇäÊåÇÁ

    }

    return vClients; // ÅÑÌÇÚ ŞÇÆãÉ ÇáÚãáÇÁ
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") // ÏÇáÉ áÊÍæíá åíßá sClient Åáì ÓØÑ äÕ
{

    string stClientRecord = ""; // ÓáÓáÉ áÊÎÒíä ÓØÑ ÇáäÕ

    stClientRecord += Client.AccountNumber + Seperator; // ÅÖÇİÉ ÑŞã ÇáÍÓÇÈ ãÚ ÇáİÇÕáÉ
    stClientRecord += Client.PinCode + Seperator; // ÅÖÇİÉ ÇáÑãÒ ÇáÓÑí ãÚ ÇáİÇÕáÉ
    stClientRecord += Client.Name + Seperator; // ÅÖÇİÉ ÇáÇÓã ãÚ ÇáİÇÕáÉ
    stClientRecord += Client.Phone + Seperator; // ÅÖÇİÉ ÑŞã ÇáåÇÊİ ãÚ ÇáİÇÕáÉ
    stClientRecord += to_string(Client.AccountBalance); // ÅÖÇİÉ ÑÕíÏ ÇáÍÓÇÈ ãÚ ÇáİÇÕáÉ

    return stClientRecord; // ÅÑÌÇÚ ÓØÑ ÇáäÕ
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients) // ÏÇáÉ áÍİÙ ÈíÇäÇÊ ÇáÚãáÇÁ İí Çáãáİ
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // İÊÍ Çáãáİ ááßÊÇÈÉ

    string DataLine; // ÓáÓáÉ áÊÎÒíä ßá ÓØÑ ãä ÇáäÕ

    if (MyFile.is_open()) // ÇáÊÍŞŞ ãä İÊÍ Çáãáİ ÈäÌÇÍ
    {

        for (sClient C : vClients) // ÇáÇäÊŞÇá ÚÈÑ ŞÇÆãÉ ÇáÚãáÇÁ
        {

            if (C.MarkForDelete == false) // ÇáÊÍŞŞ ãä ÚÏã æÌæÏ ÚáÇãÉ ÍĞİ Úáì ÇáÚãíá
            {
                // äßÊÈ İŞØ ÇáÓÌáÇÊ ÇáÊí áÇ ÊÍãá ÚáÇãÉ ÇáÍĞİ.
                DataLine = ConvertRecordToLine(C); // ÊÍæíá åíßá ÇáÚãíá Åáì ÓØÑ äÕ
                MyFile << DataLine << endl; // ßÊÇÈÉ ÇáÓØÑ Åáì Çáãáİ

            }

        }

        MyFile.close(); // ÅÛáÇŞ Çáãáİ ÈÚÏ ÇáÇäÊåÇÁ

    }

    return vClients; // ÅÑÌÇÚ ŞÇÆãÉ ÇáÚãáÇÁ ÈÚÏ ÇáßÊÇÈÉ
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, short Amount, vector <sClient>& vClients) // ÏÇáÉ áÅíÏÇÚ ÑÕíÏ Åáì ÍÓÇÈ ÇáÚãíá
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? "; // íÌÈ Úáì ÇáãÓÊÎÏã ÊÃßíÏ ÇáÚãáíÉ
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients) // ÇáÇäÊŞÇá ÚÈÑ ŞÇÆãÉ ÇáÚãáÇÁ
        {
            if (C.AccountNumber == AccountNumber) // ÇáÊÍŞŞ ãä ÊØÇÈŞ ÑŞã ÇáÍÓÇÈ
            {
                C.AccountBalance += Amount; // ÅÖÇİÉ ÇáãÈáÛ Åáì ÑÕíÏ ÇáÚãíá
                SaveCleintsDataToFile(ClientsFileName, vClients); // ÍİÙ ÇáÈíÇäÇÊ İí Çáãáİ
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance; // ÅÎÈÇÑ ÇáãÓÊÎÏã ÈäÌÇÍ ÇáÚãáíÉ æÚÑÖ ÇáÑÕíÏ ÇáÌÏíÏ

                return true; // ÅÑÌÇÚ ŞíãÉ ÕÍíÍÉ ááäÌÇÍ
            }

        }


        return false; // ÅÑÌÇÚ ŞíãÉ ÎÇØÆÉ ááİÔá
    }

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients) // ÏÇáÉ ááÈÍË Úä Úãíá ÈÇÓÊÎÏÇã ÑŞã ÇáÍÓÇÈ
{

    for (sClient C : vClients) // ÇáÇäÊŞÇá ÚÈÑ ŞÇÆãÉ ÇáÚãáÇÁ
    {

        if (C.AccountNumber == AccountNumber) // ÇáÊÍŞŞ ãä ÊØÇÈŞ ÑŞã ÇáÍÓÇÈ
        {
            return true; // ÅÑÌÇÚ ŞíãÉ ÕÍíÍÉ ÅĞÇ Êã ÇáÚËæÑ Úáì ÇáÚãíá
        }

    }
    return false; // ÅÑÌÇÚ ŞíãÉ ÎÇØÆÉ ÅĞÇ áã íÊã ÇáÚËæÑ Úáì ÇáÚãíá
}

void RefreshTransactionsScreen() {
    system("cls"); // ãÓÍ ÇáÔÇÔÉ
    ShowTransactionsMenue(); // ÚÑÖ ÔÇÔÉ ÇáãÚÇãáÇÊ
}

void GoBackToLogin() // ÏÇáÉ ááÚæÏÉ Åáì ÔÇÔÉ ÊÓÌíá ÇáÏÎæá
{
    cout << "\n\nPress any key to go back to Transactions Menue..."; // ÑÓÇáÉ ÊØáÈ ãä ÇáãÓÊÎÏã ÇáÖÛØ Úáì Ãí ãİÊÇÍ ááÑÌæÚ
    system("pause>0"); // ÇäÊÙÇÑ ÇáÖÛØ Úáì ãİÊÇÍ
    Login(); // ÇáÚæÏÉ Åáì ÔÇÔÉ ÊÓÌíá ÇáÏÎæá
}

void GoBackToMainMenue() // ÏÇáÉ ááÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
{
    cout << "\n\nPress any key to go back to Transactions Menue..."; // ÑÓÇáÉ ÊØáÈ ãä ÇáãÓÊÎÏã ÇáÖÛØ Úáì Ãí ãİÊÇÍ ááÑÌæÚ
    system("pause>0"); // ÇäÊÙÇÑ ÇáÖÛØ Úáì ãİÊÇÍ
    ShowTransactionsMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
}

void GoBackToManageUsersMenue() // ÏÇáÉ ááÚæÏÉ Åáì ŞÇÆãÉ ÅÏÇÑÉ ÇáãÓÊÎÏãíä
{
    cout << "\n\nPress any key to go back to Transactions Menue..."; // ÑÓÇáÉ ÊØáÈ ãä ÇáãÓÊÎÏã ÇáÖÛØ Úáì Ãí ãİÊÇÍ ááÑÌæÚ
    system("pause>0"); // ÇäÊÙÇÑ ÇáÖÛØ Úáì ãİÊÇÍ
}

void ShowClientTotalBalances() { // ÏÇáÉ áÚÑÖ ÑÕíÏ ÇáÚãíá

    cout << "===========================================\n";
    cout << "\t\tCheck Account Balance\n";
    cout << "===========================================\n";
    short AccountBalance = CurrentClient.AccountBalance; // ÇáÑÕíÏ ÇáÍÇáí ááÚãíá
    system("cls"); // ãÓÍ ÇáÔÇÔÉ
    cout << "Your Balances Is : " << AccountBalance << endl; // ÚÑÖ ÑÕíÏ ÇáÚãíá
}
//-------------------------------------
void ShowNormalWithDrawScreen() // ÏÇáÉ áÚÑÖ ÔÇÔÉ ÓÍÈ ÚÇÏí
{
    cout << "===================================\n";
    cout << "\t NormalWithDraw Screen"; // ÚäæÇä ÇáÔÇÔÉ
    cout << "\n===================================\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ÊÍãíá ÈíÇäÇÊ ÇáÚãáÇÁ
    string AccountNumber = CurrentClient.AccountNumber; // ÑŞã ÇáÍÓÇÈ ÇáÍÇáí

    short Amount = 0;
    do
    {
        cout << "\nEnter Amount Multiple of 5,s ? "; // íØáÈ ãä ÇáãÓÊÎÏã ÅÏÎÇá ÇáãÈáÛ ÈÊÚÏÇÏ 5
        cin >> Amount;

    } while (Amount % 5 != 0); // ÇáÊÍŞŞ ãä Ãä ÇáãÈáÛ ãÖÇÚİ ááÎãÓÉ

    if (Amount > CurrentClient.AccountBalance) // ÇáÊÍŞŞ ãä Ãä ÇáãÈáÛ ÃŞá ãä ÇáÑÕíÏ
    {
        cout << "The Amount exceede Your balance , make another choice "; // ÑÓÇáÉ ÊäÈíå ÅĞÇ ßÇä ÇáãÈáÛ íÊÌÇæÒ ÇáÑÕíÏ

        GoBackToMainMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); // ÓÍÈ ÇáãÈáÛ ãä ÇáÍÓÇÈ
}

void ShowDepositScreen() // ÏÇáÉ áÚÑÖ ÔÇÔÉ ÇáÅíÏÇÚ
{
    cout << "\n===================================\n";
    cout << "\tDeposit Screen"; // ÚäæÇä ÇáÔÇÔÉ
    cout << "\n===================================\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ÊÍãíá ÈíÇäÇÊ ÇáÚãáÇÁ
    string AccountNumber = CurrentClient.AccountNumber; // ÑŞã ÇáÍÓÇÈ ÇáÍÇáí


    double Amount = 0;
    cout << "\Enter A deposit amount? "; // íØáÈ ãä ÇáãÓÊÎÏã ÅÏÎÇá ÇáãÈáÛ
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients); // ÅíÏÇÚ ÇáãÈáÛ İí ÇáÍÓÇÈ

}
//-----------Min-Menue-----------------
short ReadWithDraw() { // ÏÇáÉ áŞÑÇÁÉ ÇáãÈáÛ ÇáãØáæÈ ÓÍÈå
    short WithDraw;
    cout << "Choose What To WithDraw From [1] to [8]? "; // íØáÈ ãä ÇáãÓÊÎÏã ÇÎÊíÇÑ ÇáãÈáÛ ÇáãØáæÈ ÓÍÈå
    cin >> WithDraw;
    return WithDraw;
}

short CheckquickWithdrawOptions() { // ÏÇáÉ ááÊÍŞŞ ãä ÎíÇÑÇÊ ÇáÓÍÈ ÇáÓÑíÚ
    short Choice = ReadWithDraw();
    short Amount = 0;
    switch (Choice)
    {
    case 1:
        return Amount = 20; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 2:
        return Amount = 50; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 3:
        return Amount = 100; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 4:
        return Amount = 200; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 5:
        return Amount = 400; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 6:
        return Amount = 600; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 7:
        return Amount = 800; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 8:
        return Amount = 1000; // ÅÑÌÇÚ ãÈáÛ ÇáÓÍÈ ÇáãÎÊÇÑ
        break;
    case 9:
        ShowTransactionsMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
        break;
    }
}

void ShowWithDrawScreen() // ÏÇáÉ áÚÑÖ ÔÇÔÉ ÇáÓÍÈ ÇáÓÑíÚ
{
    system("cls"); // ãÓÍ ÇáÔÇÔÉ
    cout << "===========================================\n";
    cout << "\t Qucick Withdraw";
    cout << "\n===========================================\n";
    cout << "\t[1]20 \t\t [2]50.\n";
    cout << "\t[3]100\t\t [4]200.\n";
    cout << "\t[5]400\t\t [6]600.\n";
    cout << "\t[7]800\t\t [8]1000.\n";
    cout << "\t[9]Exit\n";
    cout << "===========================================\n";


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ÊÍãíá ÈíÇäÇÊ ÇáÚãáÇÁ
    string AccountNumber = CurrentClient.AccountNumber; // ÑŞã ÇáÍÓÇÈ ÇáÍÇáí

    FindClientByAccountNumber(AccountNumber, vClients); // ÇáÈÍË Úä ÇáÚãíá ÈÇÓÊÎÏÇã ÑŞã ÇáÍÓÇÈ

    cout << "Your Balances Is : " << CurrentClient.AccountBalance << endl; // ÚÑÖ ÇáÑÕíÏ ÇáÍÇáí ááÚãíá

    short Amount = CheckquickWithdrawOptions(); // ÇáÊÍŞŞ ãä ÎíÇÑÇÊ ÇáÓÍÈ ÇáÓÑíÚ

    while (Amount > CurrentClient.AccountBalance) // ÇáÊÍŞŞ ãä Ãä ÇáãÈáÛ ÃŞá ãä ÇáÑÕíÏ
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl; // ÑÓÇáÉ ÊäÈíå ÅĞÇ ßÇä ÇáãÈáÛ íÊÌÇæÒ ÇáÑÕíÏ
        cout << "Please enter another amount? ";
        Amount = CheckquickWithdrawOptions(); // ÇáÊÍŞŞ ãÑÉ ÃÎÑì ãä ÇáãÈáÛ
    };

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); // ÓÍÈ ÇáãÈáÛ ãä ÇáÍÓÇÈ
}

short ReadTransactionsMenueOption() { // ÏÇáÉ áŞÑÇÁÉ ÎíÇÑ ŞÇÆãÉ ÇáÚãáíÇÊ
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromTranactionsMenueOption(TransactionsMenueOptions TransactionMenueOption) { // ÏÇáÉ áÊäİíĞ ÎíÇÑ ŞÇÆãÉ ÇáÚãáíÇÊ
    switch (TransactionMenueOption) {
    case quickWithdraw: {
        system("cls"); // ãÓÍ ÇáÔÇÔÉ
        ShowWithDrawScreen(); // ÚÑÖ ÔÇÔÉ ÇáÓÍÈ ÇáÓÑíÚ
        GoBackToMainMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
        break;
    }
    case NormalWithdraw: {
        system("cls"); // ãÓÍ ÇáÔÇÔÉ
        ShowNormalWithDrawScreen(); // ÚÑÖ ÔÇÔÉ ÓÍÈ ÚÇÏí
        GoBackToMainMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
        break;
    }
    case Deposit: {
        system("cls"); // ãÓÍ ÇáÔÇÔÉ
        ShowDepositScreen(); // ÚÑÖ ÔÇÔÉ ÇáÅíÏÇÚ
        GoBackToMainMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
        break;
    }
    case TotalBalances: {
        system("cls"); // ãÓÍ ÇáÔÇÔÉ
        ShowClientTotalBalances(); // ÚÑÖ ÑÕíÏ ÇáÚãíá
        GoBackToMainMenue(); // ÇáÚæÏÉ Åáì ŞÇÆãÉ ÇáÚãáíÇÊ
        break;
    }
    case Exit: {
        cout << "Thanks for banking with us..bye.\n"; // ÑÓÇáÉ ÇáÎÑæÌ
        Login(); // ÇáÎÑæÌ ãä ÇáÈÑäÇãÌ
    }
    }
}

void ShowTransactionsMenue() { // ÏÇáÉ áÚÑÖ ŞÇÆãÉ ÇáÚãáíÇÊ
    system("cls"); // ãÓÍ ÇáÔÇÔÉ
    cout << "=============================================\n";
    cout << "\t\tMain Menu\n";
    cout << "=============================================\n";
    cout << "\tClient Name : " << CurrentClient.Name << endl; // ÚÑÖ ÇÓã ÇáÚãíá
    cout << "=============================================\n";
    cout << "\t\t1. Quick Withdraw\n"; // ÓÍÈ ÓÑíÚ
    cout << "\t\t2. Normal Withdraw\n"; // ÓÍÈ ÚÇÏí
    cout << "\t\t3. Deposit\n"; // ÅíÏÇÚ
    cout << "\t\t4. Total Balances\n"; // ÑÕíÏ ÇáÍÓÇÈ ÇáÅÌãÇáí
    cout << "\t\t5. Exit\n"; // ÇáÎÑæÌ
    cout << "=============================================\n";

    TransactionsMenueOptions Option = static_cast<TransactionsMenueOptions>(ReadTransactionsMenueOption()); // ŞÑÇÁÉ ÇáÎíÇÑ ÇáãÎÊÇÑ
    PerfromTranactionsMenueOption(Option); // ÊäİíĞ ÇáÎíÇÑ ÇáãÎÊÇÑ
}

void LoadClientInformation(string AccountNumber, string PinCode) { // ÏÇáÉ áÊÍãíá ãÚáæãÇÊ ÇáÚãíá
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName); // ÊÍãíá ÈíÇäÇÊ ÇáÚãáÇÁ ãä Çáãáİ

    for (sClient C : vClients) // ÇáÇäÊŞÇá ÚÈÑ ŞÇÆãÉ ÇáÚãáÇÁ
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode) // ÇáÊÍŞŞ ãä ÊØÇÈŞ ÑŞã ÇáÍÓÇÈ æÇáÑãÒ ÇáÓÑí
        {
            CurrentClient = C; // ÊÚííä ÇáÚãíá ÇáÍÇáí
            ShowTransactionsMenue(); // ÚÑÖ ŞÇÆãÉ ÇáÚãáíÇÊ
        }

    }
    cout << "Client Information Not Found...." << endl; // ÑÓÇáÉ ÅĞÇ áã íÊã ÇáÚËæÑ Úáì ãÚáæãÇÊ ÇáÚãíá
    GoBackToLogin(); // ÇáÚæÏÉ Åáì ÔÇÔÉ ÊÓÌíá ÇáÏÎæá
}

void Login() { // ÏÇáÉ áÔÇÔÉ ÊÓÌíá ÇáÏÎæá
    system("cls"); // ãÓÍ ÇáÔÇÔÉ
    cout << "=======================================\n";
    cout << "\t\tBanking System\n";
    cout << "=======================================\n";

    string AccountNumber, PinCode; // ãÊÛíÑÇÊ áÊÎÒíä ÑŞã ÇáÍÓÇÈ æÇáÑãÒ ÇáÓÑí

    cout << "Enter Your Account Number? "; // íØáÈ ãä ÇáãÓÊÎÏã ÅÏÎÇá ÑŞã ÇáÍÓÇÈ
    cin >> AccountNumber;

    cout << "Enter Your PinCode? "; // íØáÈ ãä ÇáãÓÊÎÏã ÅÏÎÇá ÇáÑãÒ ÇáÓÑí
    cin >> PinCode;

    LoadClientInformation(AccountNumber, PinCode); // ÊÍãíá ãÚáæãÇÊ ÇáÚãíá ÈÇÓÊÎÏÇã ÑŞã ÇáÍÓÇÈ æÇáÑãÒ ÇáÓÑí
}

int main() { // ÇáÏÇáÉ ÇáÑÆíÓíÉ
    Login(); // ÔÇÔÉ ÊÓÌíá ÇáÏÎæá
    return 0;
}
