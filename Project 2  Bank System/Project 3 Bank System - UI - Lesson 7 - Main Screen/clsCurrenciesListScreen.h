#pragma once // ÊÖãä Ãä åĞÇ Çáãáİ ÇáÑÃÓí íÊã ÊÖãíäå ãÑÉ æÇÍÏÉ İŞØ İí ÚãáíÉ ÇáÊÑÌãÉ

#include <iostream> // ãáİ ÑÃÓí áÚãáíÇÊ ÇáÅÏÎÇá æÇáÅÎÑÇÌ
#include "clsScreen.h" // ãáİ ÑÃÓí ááæÇÌåÉ ÇáÃã
#include "clsCurrency.h" // ãáİ ÑÃÓí áİÆÉ ÇáÚãáÉ
#include <iomanip> // ãáİ ÑÃÓí áÊÍßã İí ÊäÓíŞ ÇáÅÎÑÇÌ

class clsCurrenciesListScreen :protected clsScreen // ÊÚÑíİ ááßáÇÓ clsCurrenciesListScreen ãÔÊŞ ãä clsScreen
{

private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {
        // ÏÇáÉ áØÈÇÚÉ ÓØÑ ÈíÇäÇÊ ÚãáÉ æÇÍÏÉ
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();
    }

public:

    static void ShowCurrenciesListScreen()
    {
        // ÏÇáÉ áÚÑÖ ŞÇÆãÉ ÇáÚãáÇÊ

        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList(); // ÇáÍÕæá Úáì ŞÇÆãÉ ÇáÚãáÇÊ
        string Title = "\t  Currencies List Screen"; // ÚäæÇä ÇáÔÇÔÉ
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency."; // ÚäæÇä İÑÚí íÍÊæí Úáì ÚÏÏ ÇáÚãáÇÊ

        _DrawScreenHeader(Title, SubTitle); // ÚÑÖ ÑÃÓ ÇáÔÇÔÉ
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl; // ØÈÇÚÉ ÎØ İÇÕá

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country"; // ØÈÇÚÉ ÇÓã ÇáÈáÏ
        cout << "| " << left << setw(8) << "Code"; // ØÈÇÚÉ ÑãÒ ÇáÚãáÉ
        cout << "| " << left << setw(45) << "Name"; // ØÈÇÚÉ ÇÓã ÇáÚãáÉ
        cout << "| " << left << setw(10) << "Rate/(1$)"; // ØÈÇÚÉ ÓÚÑ ÇáÚãáÉ
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl; // ØÈÇÚÉ ÎØ İÇÕá

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!"; // ÅĞÇ áã Êßä åäÇß ÚãáÇÊ ãÊÇÍÉ İí ÇáäÙÇã
        else
            for (clsCurrency Currency : vCurrencys)
            {
                PrintCurrencyRecordLine(Currency); // ØÈÇÚÉ ÈíÇäÇÊ ÇáÚãáÉ
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl; // ØÈÇÚÉ ÎØ İÇÕá
    }
};
