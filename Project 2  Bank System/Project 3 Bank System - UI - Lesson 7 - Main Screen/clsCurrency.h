#pragma once

#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>
class clsCurrency
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Seperator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
            stod(vCurrencyData[3]));

    }

    static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {

        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Seperator;
        stCurrencyRecord += Currency.CurrencyCode() + Seperator;
        stCurrencyRecord += Currency.CurrencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.Rate());

        return stCurrencyRecord;

    }

    static  vector <clsCurrency> _LoadCurrencysDataFromFile()
    {

        vector <clsCurrency> vCurrencys;

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

                vCurrencys.push_back(Currency);
            }

            MyFile.close();

        }

        return vCurrencys;

    }

    static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
    {

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsCurrency C : vCurrencys)
            {
                DataLine = _ConverCurrencyObjectToLine(C);
                MyFile << DataLine << endl;



            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsCurrency> _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (clsCurrency& C : _vCurrencys)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrencys);

    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:

    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    static vector <clsCurrency> GetAllUSDRates()
    {

        return _LoadCurrencysDataFromFile();

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    float Rate()
    {
        return _Rate;
    }


    static   clsCurrency FindByCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static   clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());

    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    float ConvertToUSD(float Amount) // œ«·… · ÕÊÌ· «·„»·€ ≈·Ï «·œÊ·«— «·√„—ÌﬂÌ
    {
        return (float)(Amount / Rate()); // Ì „ ﬁ”„ «·„»·€ ⁄·Ï ”⁄— «·’—› «·Õ«·Ì ··⁄„·… Ê≈—Ã«⁄ «·‰« Ã
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) // œ«·… · ÕÊÌ· «·„»·€ ≈·Ï ⁄„·… √Œ—Ï
    {
        float AmountInUSD = ConvertToUSD(Amount); //  ÕÊÌ· «·„»·€ ≈·Ï «·œÊ·«— «·√„—ÌﬂÌ »«” Œœ«„ «·œ«·… ConvertToUSD

        if (Currency2.CurrencyCode() == "USD") // «· Õﬁﬁ „„« ≈–« ﬂ«‰  «·⁄„·… «·Âœ› ÂÌ «·œÊ·«— «·√„—ÌﬂÌ
        {
            return AmountInUSD; // ≈–« ﬂ«‰  «·⁄„·… «·Âœ› ÂÌ «·œÊ·«— «·√„—ÌﬂÌ° Ì „ ≈—Ã«⁄ «·„»·€ ﬂ„« ÂÊ
        }

        return (float)(AmountInUSD * Currency2.Rate()); // ≈—Ã«⁄ «·„»·€ »⁄œ  ÕÊÌ·Â „‰ «·œÊ·«— «·√„—ÌﬂÌ ≈·Ï «·⁄„·… «·Âœ›
    }


};



