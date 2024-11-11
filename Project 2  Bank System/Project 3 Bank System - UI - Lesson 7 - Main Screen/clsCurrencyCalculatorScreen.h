#pragma once // ÊÃßíÏ Úáì ÚÏã ÊÖãíä åĞÇ Çáãáİ ãÑÊíä ÃËäÇÁ ÚãáíÉ ÇáÊÑÌãÉ

#include <iostream>
#include "clsScreen.h" // ÊÖãíä Çáãáİ ÇáÑÃÓí ááæÇÌåÉ clsScreen
#include "clsCurrency.h" // ÊÖãíä Çáãáİ ÇáÑÃÓí áİÆÉ ÇáÚãáÉ clsCurrency
#include "clsInputValidate.h" // ÊÖãíä Çáãáİ ÇáÑÃÓí ááÊÍŞŞ ãä ÇáÅÏÎÇá clsInputValidate

class clsCurrencyCalculatorScreen : protected clsScreen // ÊÚÑíİ ÇáßáÇÓ clsCurrencyCalculatorScreen ÇáĞí íÑË ãä clsScreen
{
private:
    // ÏÇáÉ áŞÑÇÁÉ ÇáãÈáÛ ÇáãÑÇÏ ÊÍæíáå
    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber(); // ÇÓÊÎÏÇã ÏÇáÉ clsInputValidate::ReadFloatNumber() áŞÑÇÁÉ ÇáãÈáÛ ÈÏŞÉ
        return Amount;
    }

    // ÏÇáÉ ááÍÕæá Úáì ÈíÇäÇÊ ÇáÚãáÉ ãä ÇáãÓÊÎÏã
    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString(); // ŞÑÇÁÉ ÑãÒ ÇáÚãáÉ ÇáãÏÎá ãä ÇáãÓÊÎÏã

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString(); // ÇÓÊãÑÇÑ ØáÈ ÑãÒ ÇáÚãáÉ ÍÊì íÊã ÇÎÊíÇÑ ÑãÒ ÕÍíÍ
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode); // ÇáÈÍË Úä ÈíÇäÇÊ ÇáÚãáÉ ÈÇÓÊÎÏÇã ÇáÑãÒ ÇáãÏÎá
        return Currency;
    }

    // ÏÇáÉ áØÈÇÚÉ ÈØÇŞÉ ÇáÚãáÉ
    static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {
        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";
    }

    // ÏÇáÉ áØÈÇÚÉ äÊÇÆÌ ÇáÍÓÇÈÇÊ
    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount); // ÊÍæíá ÇáãÈáÛ Åáì ÏæáÇÑ ÃãÑíßí

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2); // ÊÍæíá ÇáãÈáÛ ãä ÇáÏæáÇÑ Åáì ÇáÚãáÉ ÇáãØáæÈÉ

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();
    }

public:
    // ÏÇáÉ áÚÑÖ ÔÇÔÉ ÍÇÓÈÉ ÇáÚãáÇÊ
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            // ÇáÍÕæá Úáì ÈíÇäÇÊ ÇáÚãáÊíä æÇáãÈáÛ ãä ÇáãÓÊÎÏã
            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            // ØÈÇÚÉ äÊÇÆÌ ÇáÍÓÇÈÇÊ
            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        }
    }
};
